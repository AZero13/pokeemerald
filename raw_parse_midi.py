import sys

def parse_midi(filename):
    with open(filename, 'rb') as f:
        data = f.read()

    # Find "MTrk" chunks
    pos = 0
    track_idx = 0
    while True:
        pos = data.find(b'MTrk', pos)
        if pos == -1:
            break
        
        length = int.from_bytes(data[pos+4:pos+8], 'big')
        track_data = data[pos+8:pos+8+length]
        
        print(f"\n--- Track {track_idx} ---")
        
        # very simple parser for PC / CC
        tpos = 0
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
            tpos += 1
            
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
                
                sysex_data = track_data[tpos:tpos+length]
                print(f"SysEx: {sysex_data.hex()}")
                tpos += length
            elif status >= 0x80 and status < 0xF0:
                event = status >> 4
                channel = status & 0x0F
                
                if event == 0xC: # PC
                    pc = track_data[tpos]
                    print(f"Program Change (Ch {channel}): {pc}")
                    tpos += 1
                elif event == 0xB: # CC
                    cc = track_data[tpos]
                    val = track_data[tpos+1]
                    if cc in (0, 32):
                        print(f"Bank Select CC{cc} (Ch {channel}): {val}")
                    tpos += 2
                elif event in (0x8, 0x9, 0xA, 0xE): # 2 bytes
                    tpos += 2
                elif event in (0xC, 0xD): # 1 byte
                    tpos += 1
            else:
                # running status (ignore for now, we assume Touhou midi has explicit status or this parser will break)
                pass
                
        pos += 8 + length
        track_idx += 1

if __name__ == '__main__':
    parse_midi('th09_00c.mid')
