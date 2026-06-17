import re
from collections import defaultdict

def analyze_s(filename):
    tracks = {}
    current_track = None
    
    # regex for Nxx , NOTE , vYY
    note_re = re.compile(r'\.byte\s+N\d+\s+,\s+([A-Ga-gs][ns]?\d?)\s*(?:,\s*v\d+)?')
    voice_re = re.compile(r'\.byte\s+VOICE\s+,\s+(\d+)')
    
    with open(filename, 'r') as f:
        for line in f:
            if line.startswith('@**************** Track'):
                current_track = line.strip()
                tracks[current_track] = {'notes': defaultdict(int), 'voices': set()}
            elif current_track:
                v_match = voice_re.search(line)
                if v_match:
                    tracks[current_track]['voices'].add(int(v_match.group(1)))
                    
                n_match = note_re.search(line)
                if n_match:
                    tracks[current_track]['notes'][n_match.group(1).strip()] += 1

    for track, data in tracks.items():
        print(f"--- {track} ---")
        print(f"Voices: {data['voices']}")
        print(f"Notes used ({len(data['notes'])} unique):")
        # Sort notes alphabetically for now
        sorted_notes = sorted(data['notes'].items(), key=lambda x: x[1], reverse=True)
        for note, count in sorted_notes:
            print(f"  {note}: {count}")

if __name__ == '__main__':
    analyze_s('sound/songs/midi/mus_title.s')
