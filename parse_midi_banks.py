import sys

def parse_midi(filename):
    with open(filename, 'rb') as f:
        data = f.read()

    # Very naive parser just looking for CC 0, CC 32, and Program Change
    # A status byte for CC is 0xB0 to 0xBF
    # A status byte for PC is 0xC0 to 0xCF
    
    # Actually, writing a full MIDI parser is hard. 
    # Let's try to patch mido first to ignore the meta message error!
    pass

if __name__ == '__main__':
    parse_midi('th09_00c.mid')
