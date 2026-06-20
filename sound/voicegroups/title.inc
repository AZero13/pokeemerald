voice_group title
	@ --- PIANOS (0-7) ---
	@ 000: Acoustic Grand Piano
	voice_directsound 60, 0, DirectSoundWaveData_steinway_b_piano, 255, 200, 100, 80
	@ 001: Bright Acoustic Piano
	voice_directsound 60, 0, DirectSoundWaveData_sc88pro_piano1_60, 255, 220, 110, 80
	@ 002: Electric Grand Piano
	voice_directsound 60, 0, DirectSoundWaveData_sd90_classical_detuned_ep1_high, 255, 230, 120, 80
	@ 003: Honky-tonk Piano
	voice_directsound 60, 0, DirectSoundWaveData_sc88pro_piano1_60, 255, 200, 100, 80
	@ 004: Electric Piano 1
	voice_directsound 60, 0, DirectSoundWaveData_sd90_classical_detuned_ep1_low, 255, 210, 130, 80
	@ 005: Electric Piano 2
	voice_directsound 60, 0, DirectSoundWaveData_sd90_classical_detuned_ep1_high, 255, 210, 130, 80
	@ 006: Harpsichord (Proxy: Koto High)
	voice_directsound 60, 0, DirectSoundWaveData_unknown_koto_high, 255, 200, 100, 80
	@ 007: Clavinet (Proxy: Koto Low)
	voice_directsound 60, 0, DirectSoundWaveData_unknown_koto_low, 255, 230, 50, 70

	@ --- CHROMATIC PERCUSSION (8-15) ---
	@ 008: Celesta (Proxy: Bell)
	voice_directsound 60, 0, DirectSoundWaveData_unknown_bell, 255, 230, 50, 70
	@ 009: Glockenspiel
	voice_directsound 60, 0, DirectSoundWaveData_sc88pro_glockenspiel, 255, 240, 50, 80
	@ 010: Music Box (Proxy: Jingle Bell)
	voice_directsound 60, 0, DirectSoundWaveData_sc88pro_jingle_bell, 255, 230, 50, 80
	@ 011: Vibraphone (Proxy: Gamelan)
	voice_directsound 60, 0, DirectSoundWaveData_heart_of_asia_gamelan, 255, 210, 100, 90
	@ 012: Marimba (Proxy: Gamelan)
	voice_directsound 60, 0, DirectSoundWaveData_heart_of_asia_gamelan, 255, 240, 50, 70
	@ 013: Xylophone
	voice_directsound 60, 0, DirectSoundWaveData_sc88pro_xylophone, 255, 250, 20, 60
	@ 014: Tubular Bells
	voice_directsound 60, 0, DirectSoundWaveData_sc88pro_tubular_bell, 255, 216, 90, 242
	@ 015: Dulcimer (Proxy: Koto High)
	voice_directsound 60, 0, DirectSoundWaveData_unknown_koto_high, 255, 230, 80, 70

	@ --- ORGANS (16-23) ---
	@ 016: Drawbar Organ -> Drumset for mus_title
	voice_keysplit_all voicegroup_th09_drumset
	@ 017: Percussive Organ
	voice_directsound 60, 0, DirectSoundWaveData_sc88pro_organ2, 255, 220, 200, 100
	@ 018: Rock Organ
	voice_directsound 60, 0, DirectSoundWaveData_sc88pro_organ2, 255, 255, 255, 100
	@ 019: Church Organ
	voice_directsound 60, 0, DirectSoundWaveData_sc88pro_church_organ3_high, 200, 255, 255, 120
	@ 020: Reed Organ (Proxy: Organ Low)
	voice_directsound 60, 0, DirectSoundWaveData_sc88pro_church_organ3_low, 230, 255, 255, 100
	@ 021: Accordion
	voice_directsound 60, 0, DirectSoundWaveData_sc88pro_accordion, 240, 255, 255, 100
	@ 022: Harmonica (Proxy: Accordion Dup)
	voice_directsound 60, 0, DirectSoundWaveData_sc88pro_accordion_duplicate, 255, 255, 255, 100
	@ 023: Tango Accordion
	voice_directsound 60, 0, DirectSoundWaveData_sc88pro_accordion, 255, 255, 255, 100

	@ --- GUITARS (24-31) ---
	@ 024: NylonGtr
	voice_directsound 60, 0, DirectSoundWaveData_sc88pro_nylon_str_guitar, 255, 249, 25, 76
	@ 025: Acoustic Guitar (Steel - Proxy: Nylon)
	voice_directsound 60, 0, DirectSoundWaveData_sc88pro_nylon_str_guitar, 255, 240, 40, 80
	@ 026: Electric Guitar (Jazz - Proxy: EP1)
	voice_directsound 60, 0, DirectSoundWaveData_sd90_classical_detuned_ep1_low, 255, 255, 100, 80
	@ 027: Electric Guitar (Clean - Proxy: Power Chord)
	voice_directsound 60, 0, DirectSoundWaveData_unused_guitar_separates_power_chord, 255, 255, 100, 80
	@ 028: Electric Guitar (Muted - Proxy: Pizzicato)
	voice_directsound 60, 0, DirectSoundWaveData_sc88pro_pizzicato_strings, 255, 255, 0, 40
	@ 029: Overdriven Guitar
	voice_directsound 60, 0, DirectSoundWaveData_sd90_classical_overdrive_guitar, 255, 255, 200, 80
	@ 030: Distortion Guitar
	voice_directsound 60, 0, DirectSoundWaveData_sd90_classical_distortion_guitar_high, 255, 255, 255, 90
	@ 031: Guitar Harmonics (Proxy: Koto High)
	voice_directsound 60, 0, DirectSoundWaveData_unknown_koto_high, 255, 240, 20, 60

	@ --- BASSES (32-39) ---
	@ 032: Acoustic Bass (Proxy: Fretless)
	voice_directsound 60, 0, DirectSoundWaveData_sc88pro_fretless_bass, 255, 240, 100, 80
	@ 033: Electric Bass (Finger)
	voice_directsound 60, 0, DirectSoundWaveData_sc88pro_fingered_bass, 255, 240, 150, 80
	@ 034: Electric Bass (Pick - Proxy: Slap)
	voice_directsound 60, 0, DirectSoundWaveData_sc88pro_slap_bass, 255, 230, 100, 80
	@ 035: Fretless Bass
	voice_directsound 60, 0, DirectSoundWaveData_sc88pro_fretless_bass, 255, 240, 150, 80
	@ 036: Slap Bass 1
	voice_directsound 60, 0, DirectSoundWaveData_sc88pro_slap_bass, 255, 235, 128, 99
	@ 037: Slap Bass 2 (Unison)
	voice_directsound 60, 0, DirectSoundWaveData_sc88pro_slap_bass, 255, 230, 100, 99
	@ 038: Synth Bass 1
	voice_directsound 60, 0, DirectSoundWaveData_sc88pro_synth_bass, 255, 255, 150, 80
	@ 039: Synth Bass 2 (Mega Bass)
	voice_directsound 60, 0, DirectSoundWaveData_trinity_30303_mega_bass, 255, 255, 150, 80

	@ --- STRINGS (40-47) ---
	@ 040: Violin (Proxy: Ensemble 84)
	voice_directsound 60, 0, DirectSoundWaveData_sc88pro_string_ensemble_84, 230, 255, 255, 110
	@ 041: Viola (Proxy: Ensemble 72)
	voice_directsound 60, 0, DirectSoundWaveData_sc88pro_string_ensemble_72, 220, 255, 255, 110
	@ 042: Cello (Proxy: Ensemble 60)
	voice_directsound 60, 0, DirectSoundWaveData_sc88pro_string_ensemble_60, 220, 255, 255, 110
	@ 043: Contrabass (Proxy: Fretless)
	voice_directsound 60, 0, DirectSoundWaveData_sc88pro_fretless_bass, 220, 255, 200, 110
	@ 044: Tremolo Strings (Proxy: Ensemble 72)
	voice_directsound 60, 0, DirectSoundWaveData_sc88pro_string_ensemble_72, 240, 255, 255, 110
	@ 045: Pizzicato Strings
	voice_directsound 60, 0, DirectSoundWaveData_sc88pro_pizzicato_strings, 255, 230, 0, 60
	@ 046: Orchestral Harp
	voice_directsound 60, 0, DirectSoundWaveData_sc88pro_harp, 255, 246, 0, 235
	@ 047: Timpani
	voice_directsound 60, 0, DirectSoundWaveData_sc88pro_timpani, 255, 0, 193, 153

	@ --- ENSEMBLES (48-55) ---
	@ 048: String Ensemble 1
	voice_keysplit voicegroup_strings_keysplit, keysplit_strings
	@ 049: String Ensemble 2
	voice_directsound 60, 0, DirectSoundWaveData_sc88pro_string_ensemble_72, 220, 255, 255, 120
	@ 050: SynthStrings 1 (Proxy: Ensemble 60)
	voice_directsound 60, 0, DirectSoundWaveData_sc88pro_string_ensemble_60, 240, 255, 255, 100
	@ 051: SynthStrings 2 (Proxy: Ensemble 84)
	voice_directsound 60, 0, DirectSoundWaveData_sc88pro_string_ensemble_84, 240, 255, 255, 100
	@ 052: Choir Aahs
	voice_directsound 60, 0, DirectSoundWaveData_classical_choir_voice_ahhs, 200, 255, 255, 120
	@ 053: Voice Oohs (Proxy: Unknown Female)
	voice_directsound 60, 0, DirectSoundWaveData_unknown_female_voice, 220, 255, 255, 120
	@ 054: Synth Voice (Proxy: Unknown Male)
	voice_directsound 60, 0, DirectSoundWaveData_unused_unknown_male_voice, 240, 255, 255, 120
	@ 055: Orchestra Hit (Proxy: Timpani w/ Snare)
	voice_directsound 60, 0, DirectSoundWaveData_sc88pro_timpani_with_snare, 255, 220, 100, 80

	@ --- BRASS (56-63) ---
	@ 056: Trumpet
	voice_directsound 60, 0, DirectSoundWaveData_sc88pro_trumpet_60, 240, 255, 255, 100
	@ 057: Trombone (Proxy: Trumpet 48/60)
	voice_directsound 60, 0, DirectSoundWaveData_sc88pro_trumpet_60, 240, 255, 255, 100
	@ 058: Tuba
	voice_directsound 60, 0, DirectSoundWaveData_sc88pro_tuba_51, 220, 255, 255, 100
	@ 059: Muted Trumpet (Proxy: Trumpet 72)
	voice_directsound 60, 0, DirectSoundWaveData_sc88pro_trumpet_72, 240, 255, 255, 100
	@ 060: French Horn
	voice_directsound 60, 0, DirectSoundWaveData_sc88pro_french_horn_60, 220, 255, 255, 100
	@ 061: Brass Section (Proxy: French Horn 72)
	voice_directsound 60, 0, DirectSoundWaveData_sc88pro_french_horn_72, 240, 255, 255, 100
	@ 062: SynthBrass 1 -> Trumpet Keysplit
	voice_keysplit voicegroup_french_horn_keysplit, keysplit_french_horn
	@ 063: SynthBrass 2 (Proxy: Tuba 39 pitched)
	voice_directsound 60, 0, DirectSoundWaveData_sc88pro_tuba_39, 240, 255, 255, 100

	@ --- REED & PIPE (64-79) ---
	@ 064: Soprano Sax (Proxy: Oboe)
	voice_directsound 60, 0, DirectSoundWaveData_sd90_classical_oboe, 240, 255, 255, 100
	@ 065: Alto Sax (Proxy: Oboe 2)
	voice_directsound 60, 0, DirectSoundWaveData_unused_sd90_oboe, 240, 255, 255, 100
	@ 066: Tenor Sax (Proxy: Oboe)
	voice_directsound 60, 0, DirectSoundWaveData_sd90_classical_oboe, 240, 255, 255, 100
	@ 067: Baritone Sax (Proxy: Oboe)
	voice_directsound 60, 0, DirectSoundWaveData_sd90_classical_oboe, 240, 255, 255, 100
	@ 068: Oboe
	voice_directsound 60, 0, DirectSoundWaveData_sd90_classical_oboe, 240, 255, 255, 100
	@ 069: English Horn (Proxy: Unused Oboe)
	voice_directsound 60, 0, DirectSoundWaveData_unused_sd90_oboe, 240, 255, 255, 100
	@ 070: Bassoon (Proxy: Oboe)
	voice_directsound 60, 0, DirectSoundWaveData_sd90_classical_oboe, 240, 255, 255, 100
	@ 071: Clarinet (Proxy: Flute)
	voice_directsound 60, 0, DirectSoundWaveData_sc88pro_flute, 240, 255, 255, 100
	@ 072: Piccolo (Proxy: Flute)
	voice_directsound 60, 0, DirectSoundWaveData_sc88pro_flute, 255, 255, 255, 90
	@ 073: Flute
	voice_directsound 60, 0, DirectSoundWaveData_sc88pro_flute, 240, 255, 255, 100
	@ 074: Recorder (Proxy: Flute)
	voice_directsound 60, 0, DirectSoundWaveData_sc88pro_flute, 240, 255, 255, 100
	@ 075: Pan Flute (Proxy: Shaku)
	voice_directsound 60, 0, DirectSoundWaveData_sd90_classical_shakuhachi, 240, 255, 255, 100
	@ 076: Blown Bottle (Proxy: Delay Shaku)
	voice_directsound 60, 0, DirectSoundWaveData_sd90_enhanced_delay_shaku, 240, 255, 255, 100
	@ 077: Shakuhachi
	voice_directsound 60, 0, DirectSoundWaveData_sd90_classical_shakuhachi, 240, 255, 255, 100
	@ 078: Whistle
	voice_directsound 60, 0, DirectSoundWaveData_sd90_classical_whistle, 255, 255, 255, 90
	@ 079: Ocarina (Proxy: Whistle)
	voice_directsound 60, 0, DirectSoundWaveData_sd90_classical_whistle, 240, 255, 255, 100

	@ --- SYNTH LEADS, PADS & FX (80-126) ---
	@ 080: Square Lead
	voice_directsound 60, 0, DirectSoundWaveData_sc88pro_square_wave, 255, 204, 231, 127
	@ 081: Sawtooth Lead (Proxy: Scream Drive)
	voice_directsound 60, 0, DirectSoundWaveData_sd90_special_scream_drive, 255, 0, 255, 195
	@ 082: Calliope (Proxy: Unknown 1)
	voice_directsound 60, 0, DirectSoundWaveData_unknown_1, 255, 204, 231, 127
	@ 083: Chiff (Proxy: Unknown 2)
	voice_directsound 60, 0, DirectSoundWaveData_unknown_2, 255, 204, 231, 127
	@ 084: Charang (Proxy: Unknown 3)
	voice_directsound 60, 0, DirectSoundWaveData_unknown_3, 255, 204, 231, 127
	@ 085: Voice (Proxy: Choir Ahhs)
	voice_directsound 60, 0, DirectSoundWaveData_classical_choir_voice_ahhs, 200, 255, 255, 120
	@ 086: Fifths Lead (Proxy: Unknown 4)
	voice_directsound 60, 0, DirectSoundWaveData_unknown_4, 255, 204, 231, 127
	@ 087: Bass & Lead (Proxy: Trinity Big Boned)
	voice_directsound 60, 0, DirectSoundWaveData_trinity_big_boned, 255, 165, 154, 127
	@ 088: New Age (Proxy: Unknown 5)
	voice_directsound 60, 0, DirectSoundWaveData_unknown_5, 255, 204, 231, 127
	@ 089: Warm (Proxy: Unknown 6)
	voice_directsound 60, 0, DirectSoundWaveData_unknown_6, 255, 255, 255, 100
	@ 090: Polysynth (Proxy: Unknown 7)
	voice_directsound 60, 0, DirectSoundWaveData_unknown_7, 255, 255, 255, 100
	@ 091: Choir (Proxy: Unknown 8)
	voice_directsound 60, 0, DirectSoundWaveData_unknown_8, 255, 255, 255, 100
	@ 092: Bowed (Proxy: Unknown 9)
	voice_directsound 60, 0, DirectSoundWaveData_unknown_9, 255, 255, 255, 100
	@ 093: Metallic (Proxy: Unknown 10)
	voice_directsound 60, 0, DirectSoundWaveData_unknown_10, 255, 255, 255, 100
	@ 094: Halo (Proxy: Unknown 11)
	voice_directsound 60, 0, DirectSoundWaveData_unknown_11, 255, 255, 255, 100
	@ 095: Sweep (Proxy: Unknown 12)
	voice_directsound 60, 0, DirectSoundWaveData_unknown_12, 255, 255, 255, 100
	@ 096: Rain (Proxy: Unknown 13)
	voice_directsound 60, 0, DirectSoundWaveData_unknown_13, 255, 255, 255, 100
	@ 097: Soundtrack (Proxy: Unknown 14)
	voice_directsound 60, 0, DirectSoundWaveData_unknown_14, 255, 255, 255, 100
	@ 098: Crystal (Proxy: Unknown 15)
	voice_directsound 60, 0, DirectSoundWaveData_unknown_15, 255, 255, 255, 100
	@ 099: Atmosphere (Proxy: Unknown 16)
	voice_directsound 60, 0, DirectSoundWaveData_unknown_16, 255, 255, 255, 100
	@ 100: Brightness (Proxy: Unknown 17)
	voice_directsound 60, 0, DirectSoundWaveData_unknown_17, 255, 255, 255, 100
	@ 101: Goblins (Proxy: Unknown 18)
	voice_directsound 60, 0, DirectSoundWaveData_unknown_18, 255, 255, 255, 100
	@ 102: Echoes (Proxy: Phoneme 1)
	voice_directsound 60, 0, DirectSoundWaveData_Phoneme_1, 255, 255, 255, 100
	@ 103: Sci-Fi (Proxy: Phoneme 2)
	voice_directsound 60, 0, DirectSoundWaveData_Phoneme_2, 255, 255, 255, 100
	@ 104: Sitar (Proxy: Koto High)
	voice_directsound 60, 0, DirectSoundWaveData_unknown_koto_high, 255, 255, 255, 100
	@ 105: Banjo (Proxy: Koto Low)
	voice_directsound 60, 0, DirectSoundWaveData_unknown_koto_low, 255, 255, 255, 100
	@ 106: Shamisen (Proxy: Hyoushigi)
	voice_directsound 60, 0, DirectSoundWaveData_ethnic_flavours_hyoushigi, 255, 255, 255, 100
	@ 107: Koto (Proxy: Koto High)
	voice_directsound 60, 0, DirectSoundWaveData_unknown_koto_high, 255, 255, 255, 100
	@ 108: Kalimba (Proxy: Ohtsuzumi)
	voice_directsound 60, 0, DirectSoundWaveData_ethnic_flavours_ohtsuzumi, 255, 255, 255, 100
	@ 109: Bag pipe (Proxy: Kotsuzumi)
	voice_directsound 60, 0, DirectSoundWaveData_ethnic_flavours_kotsuzumi, 255, 255, 255, 100
	@ 110: Fiddle (Proxy: Atarigane)
	voice_directsound 60, 0, DirectSoundWaveData_ethnic_flavours_atarigane, 255, 255, 255, 100
	@ 111: Shanai (Proxy: Phoneme 3)
	voice_directsound 60, 0, DirectSoundWaveData_Phoneme_3, 255, 255, 255, 100
	@ 112: Tinkle Bell (Proxy: Jingle Bell)
	voice_directsound 60, 0, DirectSoundWaveData_sc88pro_jingle_bell, 255, 255, 255, 100
	@ 113: Agogo (Proxy: Cowbell)
	voice_directsound 60, 0, DirectSoundWaveData_sd90_cowbell, 255, 255, 255, 100
	@ 114: Steel Drums (Proxy: Taiko)
	voice_directsound 60, 0, DirectSoundWaveData_sc88pro_taiko, 255, 255, 255, 100
	@ 115: Woodblock (Proxy: Tom)
	voice_directsound 60, 0, DirectSoundWaveData_unused_sc55_tom, 255, 255, 255, 100
	@ 116: Taiko Drum
	voice_directsound 60, 0, DirectSoundWaveData_sc88pro_taiko, 255, 255, 255, 100
	@ 117: Melodic Tom (Proxy: Ambient Tom)
	voice_directsound 60, 0, DirectSoundWaveData_sd90_ambient_tom, 255, 255, 255, 100
	@ 118: Synth Drum (Proxy: Synth Snare)
	voice_directsound 60, 0, DirectSoundWaveData_unknown_synth_snare, 255, 255, 255, 100
	@ 119: Reverse Cymbal (Proxy: Cymbal Crash)
	voice_directsound 60, 0, DirectSoundWaveData_sc88pro_orchestra_cymbal_crash, 255, 255, 255, 100
	@ 120: Guitar Fret Noise (Proxy: Register Noise)
	voice_directsound 60, 0, DirectSoundWaveData_register_noise, 255, 255, 255, 100
	@ 121: Breath Noise (Proxy: Wind)
	voice_directsound 60, 0, DirectSoundWaveData_sc88pro_wind, 255, 255, 255, 100
	@ 122: Seashore (Proxy: Wind)
	voice_directsound 60, 0, DirectSoundWaveData_sc88pro_wind, 255, 255, 255, 100
	@ 123: Bird Tweet (Proxy: Whistle)
	voice_directsound 60, 0, DirectSoundWaveData_sd90_classical_whistle, 255, 255, 255, 100
	@ 124: Telephone Ring (Proxy: Bicycle Bell)
	voice_directsound 60, 0, DirectSoundWaveData_bicycle_bell, 255, 255, 255, 100
	@ 125: Helicopter (Proxy: Phoneme 4)
	voice_directsound 60, 0, DirectSoundWaveData_Phoneme_4, 255, 255, 255, 100
	@ 126: Applause -> Timpani
	voice_directsound 60, 0, DirectSoundWaveData_sc88pro_timpani, 255, 0, 193, 153

	@ --- DRUMSET (127) ---
	@ 127: RS Drumset (Channel 10)
	voice_keysplit_all voicegroup_rs_drumset

	.align 2

voice_group th09_drumset, 36
	@ note 36: Bass Drum 1
	voice_directsound_no_resample 60, 64, DirectSoundWaveData_sc88pro_rnd_kick, 255, 0, 255, 242
	@ note 37: (unused)
	voice_square_1 60, 0, 0, 2, 0, 0, 15, 0
	@ note 38: (unused)
	voice_square_1 60, 0, 0, 2, 0, 0, 15, 0
	@ note 39: (unused)
	voice_square_1 60, 0, 0, 2, 0, 0, 15, 0
	@ note 40: (unused)
	voice_square_1 60, 0, 0, 2, 0, 0, 15, 0
	@ note 41: (unused)
	voice_square_1 60, 0, 0, 2, 0, 0, 15, 0
	@ note 42: Closed Hi-Hat
	voice_directsound_no_resample 60, 79, DirectSoundWaveData_unknown_close_hihat, 255, 127, 0, 188
	@ note 43: (unused)
	voice_square_1 60, 0, 0, 2, 0, 0, 15, 0
	@ note 44: (unused)
	voice_square_1 60, 0, 0, 2, 0, 0, 15, 0
	@ note 45: (unused)
	voice_square_1 60, 0, 0, 2, 0, 0, 15, 0
	@ note 46: Open Hi-Hat
	voice_directsound_no_resample 60, 79, DirectSoundWaveData_unknown_open_hihat, 255, 242, 141, 0
