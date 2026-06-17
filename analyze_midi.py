import sys
sys.path.append('./mido_pkg')
import mido

def process(filename):
    mid = mido.MidiFile(filename)
    
    # 1. Find used programs
    programs = set()
    for track in mid.tracks:
        for msg in track:
            if msg.type == 'program_change':
                programs.add((msg.channel, msg.program))
            
    print(f"Used programs: {sorted(programs)}")
    
    # 2. Find measure 35
    ticks_per_beat = mid.ticks_per_beat
    print(f"Ticks per beat: {ticks_per_beat}")
    
    time_sig_num = 4
    for track in mid.tracks:
        for msg in track:
            if msg.type == 'time_signature':
                time_sig_num = msg.numerator
                print(f"Time signature found: {msg.numerator}/{msg.denominator}")
                break
                
    ticks_to_keep = 34 * time_sig_num * ticks_per_beat
    print(f"Target ticks to keep: {ticks_to_keep}")
    
if __name__ == '__main__':
    process('th09_00c.mid')
