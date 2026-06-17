import mido

def dump_midi(filename):
    mid = mido.MidiFile()
    with open(filename, 'rb') as f:
        mid._load(f)
    
    for i, track in enumerate(mid.tracks):
        print(f"Track {i}")
        for msg in track:
            if msg.type == 'program_change':
                print(f"  Program Change: {msg.program} on Channel {msg.channel}")
            elif msg.type == 'control_change' and msg.control in (0, 32):
                print(f"  Bank Select {msg.control}: {msg.value} on Channel {msg.channel}")

if __name__ == '__main__':
    try:
        dump_midi('th09_00c.mid')
    except Exception as e:
        print(f"Exception: {e}")
