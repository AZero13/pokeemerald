import sys
import re

def trim_and_mute_s_file(filename):
    with open(filename, 'r') as f:
        lines = f.readlines()

    out_lines = []
    
    current_track = None
    skipping = False

    for line in lines:
        if line.startswith("mus_title_"):
            if "mus_title_pri" in line or "mus_title_grp" in line or "mus_title_rev" in line:
                pass
            elif ":" in line:
                current_track = line.strip().replace(":", "")
                skipping = False
                
                # If we are on Track 3 or Track 6, we want to skip everything and just output FINE
                if current_track in ["mus_title_3", "mus_title_6"]:
                    out_lines.append(line)
                    out_lines.append("\t.byte\tFINE\n")
                    skipping = True
                    continue

        if skipping:
            # We are skipping until the next track or end of track data
            if line.startswith("mus_title_") and ":" in line:
                pass # This shouldn't happen because we catch it above
            elif line.startswith("@******************************************************@"):
                skipping = False
                out_lines.append(line)
            continue
            
        if line.startswith("@ 035"):
            out_lines.append(line)
            out_lines.append("\t.byte\tFINE\n")
            skipping = True
            continue
            
        out_lines.append(line)

    with open(filename, 'w') as f:
        f.writelines(out_lines)

if __name__ == '__main__':
    if len(sys.argv) > 1:
        trim_and_mute_s_file(sys.argv[1])
    else:
        trim_and_mute_s_file('sound/songs/midi/mus_title.s')
