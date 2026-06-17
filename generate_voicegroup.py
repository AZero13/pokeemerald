def generate_voicegroup():
    lines = ["voice_group title\n"]
    for i in range(63):
        if i == 16:
            lines.append("\tvoice_keysplit_all voicegroup_rs_drumset\n")
        elif i == 24:
            lines.append("\tvoice_directsound 60, 0, DirectSoundWaveData_sc88pro_nylon_str_guitar, 255, 249, 25, 76\n")
        elif i == 37:
            lines.append("\tvoice_directsound 60, 0, DirectSoundWaveData_sc88pro_slap_bass, 255, 235, 128, 99\n")
        elif i == 48:
            lines.append("\tvoice_directsound 60, 0, DirectSoundWaveData_sc88pro_timpani, 255, 0, 193, 153\n")
        elif i == 62:
            lines.append("\tvoice_keysplit voicegroup_trumpet_keysplit, keysplit_trumpet\n")
        else:
            lines.append("\tvoice_square_1 60, 0, 0, 2, 0, 0, 15, 0\n")
            
    with open('sound/voicegroups/title.inc', 'w') as f:
        f.writelines(lines)

if __name__ == '__main__':
    generate_voicegroup()
