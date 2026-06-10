#!/usr/bin/env python3
"""Convert boss3.mmd into GBA mus_title.mid with loop-safe tail."""
import mido
from collections import defaultdict

SRC = "Touhou 2 (SoEW) - 09 - Love-Coloured Magic (boss3.mmd).mid"
DST = "sound/songs/midi/mus_title.mid"
LOOP_END = 7200
TAIL_FADE_START = 7056
TAIL_DRUM_STOP = 7104
TAIL_MELODY_STOP = 7104
RELEASE_AT = LOOP_END - 24
KEEP_CHANNELS = {0, 1, 2, 3, 9}
KEEP_CC = {1, 7, 10}
DRUM_REMAP = {37: 38, 49: 57, 51: 46}
DRUM_VEL_SCALE = 0.68
DRUM_VEL_CAP = 90
DRUM_CH_VOL = 88
CLAP_NOTE = 39
CLAP_VEL_SCALE = 0.55
LOOP_RESET = {
    0: [("program", 18), ("cc7", 95)],
    1: [("program", 1), ("cc7", 120)],
    2: [("program", 39), ("cc7", 103)],
    3: [("program", 49), ("cc7", 80)],
}


def remap_drum_note(note):
    return DRUM_REMAP.get(note, note)


def scale_drum_vel(note, vel, tick):
    vel = min(DRUM_VEL_CAP, max(1, int(vel * DRUM_VEL_SCALE)))
    if note == CLAP_NOTE:
        vel = max(1, int(vel * CLAP_VEL_SCALE))
    if tick >= 6912:
        vel = max(1, int(vel * 0.75))
    return vel


def load_events():
    src = mido.MidiFile(SRC)
    chan_evs = defaultdict(list)
    tempo = None
    for tr in src.tracks:
        tick = 0
        for msg in tr:
            tick += msg.time
            if msg.type == "set_tempo" and tempo is None:
                tempo = msg.tempo
            elif msg.type in ("note_on", "note_off", "control_change", "program_change"):
                if msg.channel in KEEP_CHANNELS and tick < LOOP_END:
                    chan_evs[msg.channel].append((tick, msg.copy()))
    if 9 in chan_evs:
        chan_evs[9].append((0, mido.Message("control_change", channel=9, control=7, value=DRUM_CH_VOL)))
    for ch, settings in LOOP_RESET.items():
        for kind, val in settings:
            if kind == "program":
                chan_evs[ch].append((RELEASE_AT, mido.Message("program_change", channel=ch, program=val)))
            else:
                chan_evs[ch].append((RELEASE_AT, mido.Message("control_change", channel=ch, control=7, value=val)))
    return src.ticks_per_beat, tempo, chan_evs


def build_track(ch, events):
    evs = []
    active = {}
    for tick, msg in sorted(events, key=lambda item: item[0]):
        if ch == 9 and tick >= TAIL_DRUM_STOP:
            if msg.type == "note_on" and msg.velocity > 0:
                continue
            if msg.type == "note_off" or (msg.type == "note_on" and msg.velocity == 0):
                note = remap_drum_note(msg.note)
                if active.get(note, 0) > 0:
                    active[note] -= 1
                    evs.append((tick, 0, mido.Message("note_off", channel=9, note=note, velocity=0)))
                continue
        if ch == 9 and msg.type in ("note_on", "note_off"):
            note = remap_drum_note(msg.note)
            if msg.type == "note_on" and msg.velocity > 0:
                vel = scale_drum_vel(note, msg.velocity, tick)
                msg = mido.Message("note_on", channel=9, note=note, velocity=vel)
            else:
                msg = mido.Message("note_off", channel=9, note=note, velocity=0)
        if msg.type == "note_on" and msg.velocity > 0:
            if tick >= TAIL_MELODY_STOP:
                continue
            if ch != 9 and tick >= TAIL_FADE_START:
                msg = msg.copy(velocity=max(1, int(msg.velocity * 0.5)))
            note = msg.note
            active[note] = active.get(note, 0) + 1
            evs.append((tick, 1, msg))
        elif msg.type == "note_off" or (msg.type == "note_on" and msg.velocity == 0):
            note = msg.note
            if active.get(note, 0) > 0:
                active[note] -= 1
                evs.append((tick, 0, mido.Message("note_off", channel=ch, note=note, velocity=0)))
        elif msg.type == "control_change" and msg.control in KEEP_CC:
            if msg.control == 7 and ch != 9 and tick >= TAIL_FADE_START:
                msg = msg.copy(value=min(msg.value, 85))
            evs.append((tick, 0, msg))
        elif msg.type == "program_change":
            evs.append((tick, 0, msg))
    for note, count in list(active.items()):
        for _ in range(count):
            evs.append((RELEASE_AT, 0, mido.Message("note_off", channel=ch, note=note, velocity=0)))
    evs.sort(key=lambda item: (item[0], item[1]))
    trk = mido.MidiTrack()
    last = 0
    for tick, _, msg in evs:
        trk.append(msg.copy(time=tick - last))
        last = tick
    trk.append(mido.MetaMessage("end_of_track", time=LOOP_END - last))
    return trk


def main():
    tpb, tempo, chan_evs = load_events()
    out = mido.MidiFile(type=1, ticks_per_beat=tpb)
    meta = mido.MidiTrack()
    meta.append(mido.MetaMessage("track_name", name="Love-Coloured Magic", time=0))
    meta.append(mido.MetaMessage("time_signature", numerator=4, denominator=4, time=0))
    meta.append(mido.MetaMessage("set_tempo", tempo=tempo, time=0))
    meta.append(mido.MetaMessage("marker", text="[", time=0))
    meta.append(mido.MetaMessage("marker", text="]", time=LOOP_END))
    meta.append(mido.MetaMessage("end_of_track", time=0))
    out.tracks.append(meta)
    for ch in sorted(chan_evs):
        out.tracks.append(build_track(ch, chan_evs[ch]))
    out.save(DST)
    print("wrote", DST)


if __name__ == "__main__":
    main()
