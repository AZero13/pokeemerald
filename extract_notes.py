import sys

def parse_midi_notes(filename):
    with open(filename, 'rb') as f:
        data = f.read()

    # Find "MTrk" chunks
    pos = 0
    track_idx = 0
    
    notes_per_channel = {i: set() for i in range(16)}
    
    while True:
        pos = data.find(b'MTrk', pos)
        if pos == -1:
            break
        
        length = int.from_bytes(data[pos+4:pos+8], 'big')
        track_data = data[pos+8:pos+8+length]
        
        tpos = 0
        running_status = 0
        while tpos < len(track_data):
            # read var-length delta
            delta = 0
            while True:
                if tpos >= len(track_data): break
                b = track_data[tpos]
                tpos += 1
                delta = (delta << 7) | (b & 0x7F)
                if not (b & 0x80):
                    break
            
            if tpos >= len(track_data): break
            status = track_data[tpos]
            
            if status >= 0x80:
                tpos += 1
                running_status = status
            else:
                status = running_status
            
            if status == 0xFF:
                # meta
                if tpos >= len(track_data): break
                type_ = track_data[tpos]
                tpos += 1
                length = 0
                while True:
                    if tpos >= len(track_data): break
                    b = track_data[tpos]
                    tpos += 1
                    length = (length << 7) | (b & 0x7F)
                    if not (b & 0x80): break
                tpos += length
            elif status in (0xF0, 0xF7):
                # sysex
                length = 0
                while True:
                    if tpos >= len(track_data): break
                    b = track_data[tpos]
                    tpos += 1
                    length = (length << 7) | (b & 0x7F)
                    if not (b & 0x80): break
                tpos += length
            elif status >= 0x80 and status < 0xF0:
                event = status >> 4
                channel = status & 0x0F
                
                if event == 0x9 or event == 0x8: # Note On/Off
                    note = track_data[tpos]
                    velocity = track_data[tpos+1]
                    tpos += 2
                    if event == 0x9 and velocity > 0:
                        notes_per_channel[channel].add(note)
                elif event == 0xA or event == 0xB or event == 0xE:
                    tpos += 2
                elif event == 0xC or event == 0xD:
                    tpos += 1
                
        pos += 8 + length
        track_idx += 1

    for ch, notes in notes_per_channel.items():
        if notes:
            print(f"Channel {ch}: {sorted(list(notes))}")

if __name__ == '__main__':
    parse_midi_notes('th09_00c.mid')
