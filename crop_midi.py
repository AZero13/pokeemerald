import sys

def crop_s_file(input_path, output_path, target_measure="035"):
    with open(input_path, 'r') as f:
        lines = f.readlines()

    new_lines = []
    skip = False
    
    measure_marker = f"@ {target_measure}   -"
    track_marker = "@**************** Track"
    end_marker = "@******************************************************@"
    
    for line in lines:
        if line.startswith(track_marker):
            skip = False
        elif line.startswith(end_marker):
            skip = False
            
        if not skip:
            new_lines.append(line)
            if line.startswith(measure_marker):
                new_lines.append('\t.byte\tFINE\n\n')
                skip = True

    with open(output_path, 'w') as f:
        f.writelines(new_lines)
        
if __name__ == '__main__':
    crop_s_file('mus_title.s', 'sound/songs/midi/mus_title.s')
