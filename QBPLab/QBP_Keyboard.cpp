#include "QBP_Keyboard.h"


CQBPKeyboard::CQBPKeyboard()
{

    //Cria um device de I/O MIDI
    pQBPMidiDevice = new CQBPMidiDevice();

    for (int i = 0; i < 128; i++)
    {

        DiatonicNote tNote;
        switch (i)
        {

        case  0 : {tNote.NoteName = "C" ; tNote.bIsbemol = false; tNote.bIssharp = false; tNote.NotePith = i; tNote.Octave = -1; tNote.Frequency = 8.1757; tNote.MidiShortMessage = 0x00400090;   }break;
        case  1 : {tNote.NoteName = "Db"; tNote.bIsbemol = true ; tNote.bIssharp = false; tNote.NotePith = i; tNote.Octave = -1; tNote.Frequency = 8.6619; tNote.MidiShortMessage = 0x00400190;   }break;
        case  2 : {tNote.NoteName = "D" ; tNote.bIsbemol = false; tNote.bIssharp = false; tNote.NotePith = i; tNote.Octave = -1; tNote.Frequency = 9.1770; tNote.MidiShortMessage = 0x00400290;   }break;
        case  3 : {tNote.NoteName = "Eb"; tNote.bIsbemol = true ; tNote.bIssharp = false; tNote.NotePith = i; tNote.Octave = -1; tNote.Frequency = 9.7227; tNote.MidiShortMessage = 0x00400390;   }break;
        case  4 : {tNote.NoteName = "E" ; tNote.bIsbemol = false; tNote.bIssharp = false; tNote.NotePith = i; tNote.Octave = -1; tNote.Frequency = 10.300; tNote.MidiShortMessage = 0x00400490;   }break;
        case  5 : {tNote.NoteName = "F" ; tNote.bIsbemol = false; tNote.bIssharp = false; tNote.NotePith = i; tNote.Octave = -1; tNote.Frequency = 10.913; tNote.MidiShortMessage = 0x00400590;   }break;
        case  6 : {tNote.NoteName = "Gb"; tNote.bIsbemol = true ; tNote.bIssharp = false; tNote.NotePith = i; tNote.Octave = -1; tNote.Frequency = 11.562; tNote.MidiShortMessage = 0x00400690;   }break;
        case  7 : {tNote.NoteName = "G" ; tNote.bIsbemol = false; tNote.bIssharp = false; tNote.NotePith = i; tNote.Octave = -1; tNote.Frequency = 12.249; tNote.MidiShortMessage = 0x00400790;   }break;
        case  8 : {tNote.NoteName = "Ab"; tNote.bIsbemol = true ; tNote.bIssharp = false; tNote.NotePith = i; tNote.Octave = -1; tNote.Frequency = 12.978; tNote.MidiShortMessage = 0x00400890;   }break;
        case  9 : {tNote.NoteName = "A" ; tNote.bIsbemol = false; tNote.bIssharp = false; tNote.NotePith = i; tNote.Octave = -1; tNote.Frequency = 13.750; tNote.MidiShortMessage = 0x00400990;   }break;
        case 10 : {tNote.NoteName = "Bb"; tNote.bIsbemol = true ; tNote.bIssharp = false; tNote.NotePith = i; tNote.Octave = -1; tNote.Frequency = 14.567; tNote.MidiShortMessage = 0x00400A90;   }break;
        case 11 : {tNote.NoteName = "B" ; tNote.bIsbemol = false; tNote.bIssharp = false; tNote.NotePith = i; tNote.Octave = -1; tNote.Frequency = 15.433; tNote.MidiShortMessage = 0x00400B90;   }break;
        case 12 : {tNote.NoteName = "C" ; tNote.bIsbemol = false; tNote.bIssharp = false; tNote.NotePith = i; tNote.Octave =  0; tNote.Frequency = 16.351; tNote.MidiShortMessage = 0x00400C90;   }break;
        case 13 : {tNote.NoteName = "Db"; tNote.bIsbemol = true ; tNote.bIssharp = false; tNote.NotePith = i; tNote.Octave =  0; tNote.Frequency = 17.323; tNote.MidiShortMessage = 0x00400D90;   }break;
        case 14 : {tNote.NoteName = "D" ; tNote.bIsbemol = false; tNote.bIssharp = false; tNote.NotePith = i; tNote.Octave =  0; tNote.Frequency = 18.354; tNote.MidiShortMessage = 0x00400E90;   }break;
        case 15 : {tNote.NoteName = "Eb"; tNote.bIsbemol = true ; tNote.bIssharp = false; tNote.NotePith = i; tNote.Octave =  0; tNote.Frequency = 19.445; tNote.MidiShortMessage = 0x00400F90;   }break;
        case 16 : {tNote.NoteName = "E" ; tNote.bIsbemol = false; tNote.bIssharp = false; tNote.NotePith = i; tNote.Octave =  0; tNote.Frequency = 20.601; tNote.MidiShortMessage = 0x00401090;   }break;
        case 17 : {tNote.NoteName = "F" ; tNote.bIsbemol = false; tNote.bIssharp = false; tNote.NotePith = i; tNote.Octave =  0; tNote.Frequency = 21.826; tNote.MidiShortMessage = 0x00401190;   }break;
        case 18 : {tNote.NoteName = "Gb"; tNote.bIsbemol = true ; tNote.bIssharp = false; tNote.NotePith = i; tNote.Octave =  0; tNote.Frequency = 23.124; tNote.MidiShortMessage = 0x00401290;   }break;
        case 19 : {tNote.NoteName = "G" ; tNote.bIsbemol = false; tNote.bIssharp = false; tNote.NotePith = i; tNote.Octave =  0; tNote.Frequency = 24.499; tNote.MidiShortMessage = 0x00401390;   }break;
        case 20 : {tNote.NoteName = "Ab"; tNote.bIsbemol = true ; tNote.bIssharp = false; tNote.NotePith = i; tNote.Octave =  0; tNote.Frequency = 25.956; tNote.MidiShortMessage = 0x00401490;   }break;
        case 21 : {tNote.NoteName = "A" ; tNote.bIsbemol = false; tNote.bIssharp = false; tNote.NotePith = i; tNote.Octave =  0; tNote.Frequency = 27.500; tNote.MidiShortMessage = 0x00401590;   }break;
        case 22 : {tNote.NoteName = "Bb"; tNote.bIsbemol = true ; tNote.bIssharp = false; tNote.NotePith = i; tNote.Octave =  0; tNote.Frequency = 29.135; tNote.MidiShortMessage = 0x00401690;   }break;
        case 23 : {tNote.NoteName = "B" ; tNote.bIsbemol = false; tNote.bIssharp = false; tNote.NotePith = i; tNote.Octave =  0; tNote.Frequency = 30.868; tNote.MidiShortMessage = 0x00401790;   }break;
        case 24 : {tNote.NoteName = "C" ; tNote.bIsbemol = false; tNote.bIssharp = false; tNote.NotePith = i; tNote.Octave =  1; tNote.Frequency = 32.703; tNote.MidiShortMessage = 0x00401890;   }break;
        case 25 : {tNote.NoteName = "Db"; tNote.bIsbemol = true ; tNote.bIssharp = false; tNote.NotePith = i; tNote.Octave =  1; tNote.Frequency = 34.648; tNote.MidiShortMessage = 0x00401990;   }break;
        case 26 : {tNote.NoteName = "D" ; tNote.bIsbemol = false; tNote.bIssharp = false; tNote.NotePith = i; tNote.Octave =  1; tNote.Frequency = 36.708; tNote.MidiShortMessage = 0x00401A90;   }break;
        case 27 : {tNote.NoteName = "Eb"; tNote.bIsbemol = true ; tNote.bIssharp = false; tNote.NotePith = i; tNote.Octave =  1; tNote.Frequency = 38.891; tNote.MidiShortMessage = 0x00401B90;   }break;
        case 28 : {tNote.NoteName = "E" ; tNote.bIsbemol = false; tNote.bIssharp = false; tNote.NotePith = i; tNote.Octave =  1; tNote.Frequency = 41.203; tNote.MidiShortMessage = 0x00401C90;   }break;
        case 29 : {tNote.NoteName = "F" ; tNote.bIsbemol = false; tNote.bIssharp = false; tNote.NotePith = i; tNote.Octave =  1; tNote.Frequency = 43.654; tNote.MidiShortMessage = 0x00401D90;   }break;
        case 30 : {tNote.NoteName = "Gb"; tNote.bIsbemol = true ; tNote.bIssharp = false; tNote.NotePith = i; tNote.Octave =  1; tNote.Frequency = 46.249; tNote.MidiShortMessage = 0x00401E90;   }break;
        case 31 : {tNote.NoteName = "G" ; tNote.bIsbemol = false; tNote.bIssharp = false; tNote.NotePith = i; tNote.Octave =  1; tNote.Frequency = 48.999; tNote.MidiShortMessage = 0x00401F90;   }break;
        case 32 : {tNote.NoteName = "Ab"; tNote.bIsbemol = true ; tNote.bIssharp = false; tNote.NotePith = i; tNote.Octave =  1; tNote.Frequency = 51.913; tNote.MidiShortMessage = 0x00402090;   }break;
        case 33 : {tNote.NoteName = "A" ; tNote.bIsbemol = false; tNote.bIssharp = false; tNote.NotePith = i; tNote.Octave =  1; tNote.Frequency = 55.000; tNote.MidiShortMessage = 0x00402190;   }break;
        case 34 : {tNote.NoteName = "Bb"; tNote.bIsbemol = true ; tNote.bIssharp = false; tNote.NotePith = i; tNote.Octave =  1; tNote.Frequency = 58.270; tNote.MidiShortMessage = 0x00402290;   }break;
        case 35 : {tNote.NoteName = "B" ; tNote.bIsbemol = false; tNote.bIssharp = false; tNote.NotePith = i; tNote.Octave =  1; tNote.Frequency = 61.735; tNote.MidiShortMessage = 0x00402390;   }break;
        case 36 : {tNote.NoteName = "C" ; tNote.bIsbemol = false; tNote.bIssharp = false; tNote.NotePith = i; tNote.Octave =  2; tNote.Frequency = 65.406; tNote.MidiShortMessage = 0x00402490;   }break;
        case 37 : {tNote.NoteName = "Db"; tNote.bIsbemol = true ; tNote.bIssharp = false; tNote.NotePith = i; tNote.Octave =  2; tNote.Frequency = 69.296; tNote.MidiShortMessage = 0x00402590;   }break;
        case 38 : {tNote.NoteName = "D" ; tNote.bIsbemol = false; tNote.bIssharp = false; tNote.NotePith = i; tNote.Octave =  2; tNote.Frequency = 73.416; tNote.MidiShortMessage = 0x00402690;   }break;
        case 39 : {tNote.NoteName = "Eb"; tNote.bIsbemol = true ; tNote.bIssharp = false; tNote.NotePith = i; tNote.Octave =  2; tNote.Frequency = 77.782; tNote.MidiShortMessage = 0x00402790;   }break;
        case 40 : {tNote.NoteName = "E" ; tNote.bIsbemol = false; tNote.bIssharp = false; tNote.NotePith = i; tNote.Octave =  2; tNote.Frequency = 82.407; tNote.MidiShortMessage = 0x00402890;   }break;
        case 41 : {tNote.NoteName = "F" ; tNote.bIsbemol = false; tNote.bIssharp = false; tNote.NotePith = i; tNote.Octave =  2; tNote.Frequency = 87.307; tNote.MidiShortMessage = 0x00402990;   }break;
        case 42 : {tNote.NoteName = "Gb"; tNote.bIsbemol = true ; tNote.bIssharp = false; tNote.NotePith = i; tNote.Octave =  2; tNote.Frequency = 92.499; tNote.MidiShortMessage = 0x00402A90;   }break;
        case 43 : {tNote.NoteName = "G" ; tNote.bIsbemol = false; tNote.bIssharp = false; tNote.NotePith = i; tNote.Octave =  2; tNote.Frequency = 97.999; tNote.MidiShortMessage = 0x00402B90;   }break;
        case 44 : {tNote.NoteName = "Ab"; tNote.bIsbemol = true ; tNote.bIssharp = false; tNote.NotePith = i; tNote.Octave =  2; tNote.Frequency = 103.83; tNote.MidiShortMessage = 0x00402C90;   }break;
        case 45 : {tNote.NoteName = "A" ; tNote.bIsbemol = false; tNote.bIssharp = false; tNote.NotePith = i; tNote.Octave =  2; tNote.Frequency = 110.00; tNote.MidiShortMessage = 0x00402D90;   }break;
        case 46 : {tNote.NoteName = "Bb"; tNote.bIsbemol = true ; tNote.bIssharp = false; tNote.NotePith = i; tNote.Octave =  2; tNote.Frequency = 116.54; tNote.MidiShortMessage = 0x00402E90;   }break;
        case 47 : {tNote.NoteName = "B" ; tNote.bIsbemol = false; tNote.bIssharp = false; tNote.NotePith = i; tNote.Octave =  2; tNote.Frequency = 123.47; tNote.MidiShortMessage = 0x00402F90;   }break;
        case 48 : {tNote.NoteName = "C" ; tNote.bIsbemol = false; tNote.bIssharp = false; tNote.NotePith = i; tNote.Octave =  3; tNote.Frequency = 130.81; tNote.MidiShortMessage = 0x00403090;   }break;
        case 49 : {tNote.NoteName = "Db"; tNote.bIsbemol = true ; tNote.bIssharp = false; tNote.NotePith = i; tNote.Octave =  3; tNote.Frequency = 138.59; tNote.MidiShortMessage = 0x00403190;   }break;
        case 50 : {tNote.NoteName = "D" ; tNote.bIsbemol = false; tNote.bIssharp = false; tNote.NotePith = i; tNote.Octave =  3; tNote.Frequency = 146.83; tNote.MidiShortMessage = 0x00403290;   }break;
        case 51 : {tNote.NoteName = "Eb"; tNote.bIsbemol = true ; tNote.bIssharp = false; tNote.NotePith = i; tNote.Octave =  3; tNote.Frequency = 155.56; tNote.MidiShortMessage = 0x00403390;   }break;
        case 52 : {tNote.NoteName = "E" ; tNote.bIsbemol = false; tNote.bIssharp = false; tNote.NotePith = i; tNote.Octave =  3; tNote.Frequency = 164.81; tNote.MidiShortMessage = 0x00403490;   }break;
        case 53 : {tNote.NoteName = "F" ; tNote.bIsbemol = false; tNote.bIssharp = false; tNote.NotePith = i; tNote.Octave =  3; tNote.Frequency = 174.61; tNote.MidiShortMessage = 0x00403590;   }break;
        case 54 : {tNote.NoteName = "Gb"; tNote.bIsbemol = true ; tNote.bIssharp = false; tNote.NotePith = i; tNote.Octave =  3; tNote.Frequency = 185.00; tNote.MidiShortMessage = 0x00403690;   }break;
        case 55 : {tNote.NoteName = "G" ; tNote.bIsbemol = false; tNote.bIssharp = false; tNote.NotePith = i; tNote.Octave =  3; tNote.Frequency = 196.00; tNote.MidiShortMessage = 0x00403790;   }break;
        case 56 : {tNote.NoteName = "Ab"; tNote.bIsbemol = true ; tNote.bIssharp = false; tNote.NotePith = i; tNote.Octave =  3; tNote.Frequency = 207.65; tNote.MidiShortMessage = 0x00403890;   }break;
        case 57 : {tNote.NoteName = "A" ; tNote.bIsbemol = false; tNote.bIssharp = false; tNote.NotePith = i; tNote.Octave =  3; tNote.Frequency = 220.00; tNote.MidiShortMessage = 0x00403990;   }break;
        case 58 : {tNote.NoteName = "Bb"; tNote.bIsbemol = true ; tNote.bIssharp = false; tNote.NotePith = i; tNote.Octave =  3; tNote.Frequency = 233.08; tNote.MidiShortMessage = 0x00403A90;   }break;
        case 59 : {tNote.NoteName = "B" ; tNote.bIsbemol = false; tNote.bIssharp = false; tNote.NotePith = i; tNote.Octave =  3; tNote.Frequency = 246.94; tNote.MidiShortMessage = 0x00403B90;   }break;
        case 60 : {tNote.NoteName = "C" ; tNote.bIsbemol = false; tNote.bIssharp = false; tNote.NotePith = i; tNote.Octave =  4; tNote.Frequency = 261.63; tNote.MidiShortMessage = 0x00403C90;   }break;
        case 61 : {tNote.NoteName = "Db"; tNote.bIsbemol = true ; tNote.bIssharp = false; tNote.NotePith = i; tNote.Octave =  4; tNote.Frequency = 277.18; tNote.MidiShortMessage = 0x00403D90;   }break;
        case 62 : {tNote.NoteName = "D" ; tNote.bIsbemol = false; tNote.bIssharp = false; tNote.NotePith = i; tNote.Octave =  4; tNote.Frequency = 293.67; tNote.MidiShortMessage = 0x00403E90;   }break;
        case 63 : {tNote.NoteName = "Eb"; tNote.bIsbemol = true ; tNote.bIssharp = false; tNote.NotePith = i; tNote.Octave =  4; tNote.Frequency = 311.13; tNote.MidiShortMessage = 0x00403F90;   }break;
        case 64 : {tNote.NoteName = "E" ; tNote.bIsbemol = false; tNote.bIssharp = false; tNote.NotePith = i; tNote.Octave =  4; tNote.Frequency = 329.63; tNote.MidiShortMessage = 0x00404090;   }break;
        case 65 : {tNote.NoteName = "F" ; tNote.bIsbemol = false; tNote.bIssharp = false; tNote.NotePith = i; tNote.Octave =  4; tNote.Frequency = 349.23; tNote.MidiShortMessage = 0x00404190;   }break;
        case 66 : {tNote.NoteName = "Gb"; tNote.bIsbemol = true ; tNote.bIssharp = false; tNote.NotePith = i; tNote.Octave =  4; tNote.Frequency = 369.99; tNote.MidiShortMessage = 0x00404290;   }break;
        case 67 : {tNote.NoteName = "G" ; tNote.bIsbemol = false; tNote.bIssharp = false; tNote.NotePith = i; tNote.Octave =  4; tNote.Frequency = 392.00; tNote.MidiShortMessage = 0x00404390;   }break;
        case 68 : {tNote.NoteName = "Ab"; tNote.bIsbemol = true ; tNote.bIssharp = false; tNote.NotePith = i; tNote.Octave =  4; tNote.Frequency = 415.30; tNote.MidiShortMessage = 0x00404490;   }break;
        case 69 : {tNote.NoteName = "A" ; tNote.bIsbemol = false; tNote.bIssharp = false; tNote.NotePith = i; tNote.Octave =  4; tNote.Frequency = 440.00; tNote.MidiShortMessage = 0x00404590;   }break;
        case 70 : {tNote.NoteName = "Bb"; tNote.bIsbemol = true ; tNote.bIssharp = false; tNote.NotePith = i; tNote.Octave =  4; tNote.Frequency = 466.16; tNote.MidiShortMessage = 0x00404690;   }break;
        case 71 : {tNote.NoteName = "B" ; tNote.bIsbemol = false; tNote.bIssharp = false; tNote.NotePith = i; tNote.Octave =  4; tNote.Frequency = 493.88; tNote.MidiShortMessage = 0x00404790;   }break;
        case 72 : {tNote.NoteName = "C" ; tNote.bIsbemol = false; tNote.bIssharp = false; tNote.NotePith = i; tNote.Octave =  5; tNote.Frequency = 523.25; tNote.MidiShortMessage = 0x00404890;   }break;
        case 73 : {tNote.NoteName = "Db"; tNote.bIsbemol = true ; tNote.bIssharp = false; tNote.NotePith = i; tNote.Octave =  5; tNote.Frequency = 554.37; tNote.MidiShortMessage = 0x00404990;   }break;
        case 74 : {tNote.NoteName = "D" ; tNote.bIsbemol = false; tNote.bIssharp = false; tNote.NotePith = i; tNote.Octave =  5; tNote.Frequency = 587.33; tNote.MidiShortMessage = 0x00404A90;   }break;
        case 75 : {tNote.NoteName = "Eb"; tNote.bIsbemol = true ; tNote.bIssharp = false; tNote.NotePith = i; tNote.Octave =  5; tNote.Frequency = 622.25; tNote.MidiShortMessage = 0x00404B90;   }break;
        case 76 : {tNote.NoteName = "E" ; tNote.bIsbemol = false; tNote.bIssharp = false; tNote.NotePith = i; tNote.Octave =  5; tNote.Frequency = 659.26; tNote.MidiShortMessage = 0x00404C90;   }break;
        case 77 : {tNote.NoteName = "F" ; tNote.bIsbemol = false; tNote.bIssharp = false; tNote.NotePith = i; tNote.Octave =  5; tNote.Frequency = 698.46; tNote.MidiShortMessage = 0x00404D90;   }break;
        case 78 : {tNote.NoteName = "Gb"; tNote.bIsbemol = true ; tNote.bIssharp = false; tNote.NotePith = i; tNote.Octave =  5; tNote.Frequency = 739.99; tNote.MidiShortMessage = 0x00404E90;   }break;
        case 79 : {tNote.NoteName = "G" ; tNote.bIsbemol = false; tNote.bIssharp = false; tNote.NotePith = i; tNote.Octave =  5; tNote.Frequency = 783.99; tNote.MidiShortMessage = 0x00404F90;   }break;
        case 80 : {tNote.NoteName = "Ab"; tNote.bIsbemol = true ; tNote.bIssharp = false; tNote.NotePith = i; tNote.Octave =  5; tNote.Frequency = 830.61; tNote.MidiShortMessage = 0x00405090;   }break;
        case 81 : {tNote.NoteName = "A" ; tNote.bIsbemol = false; tNote.bIssharp = false; tNote.NotePith = i; tNote.Octave =  5; tNote.Frequency = 880.00; tNote.MidiShortMessage = 0x00405190;   }break;
        case 82 : {tNote.NoteName = "Bb"; tNote.bIsbemol = true ; tNote.bIssharp = false; tNote.NotePith = i; tNote.Octave =  5; tNote.Frequency = 932.33; tNote.MidiShortMessage = 0x00405290;   }break;
        case 83 : {tNote.NoteName = "B" ; tNote.bIsbemol = false; tNote.bIssharp = false; tNote.NotePith = i; tNote.Octave =  5; tNote.Frequency = 987.77; tNote.MidiShortMessage = 0x00405390;   }break;
        case 84 : {tNote.NoteName = "C" ; tNote.bIsbemol = false; tNote.bIssharp = false; tNote.NotePith = i; tNote.Octave =  6; tNote.Frequency = 1046.5; tNote.MidiShortMessage = 0x00405490;   }break;
        case 85 : {tNote.NoteName = "Db"; tNote.bIsbemol = true ; tNote.bIssharp = false; tNote.NotePith = i; tNote.Octave =  6; tNote.Frequency = 1108.7; tNote.MidiShortMessage = 0x00405590;   }break;
        case 86 : {tNote.NoteName = "D" ; tNote.bIsbemol = false; tNote.bIssharp = false; tNote.NotePith = i; tNote.Octave =  6; tNote.Frequency = 1174.7; tNote.MidiShortMessage = 0x00405690;   }break;
        case 87 : {tNote.NoteName = "Eb"; tNote.bIsbemol = false; tNote.bIssharp = false; tNote.NotePith = i; tNote.Octave =  6; tNote.Frequency = 1244.5; tNote.MidiShortMessage = 0x00405790;   }break;
        case 88 : {tNote.NoteName = "E" ; tNote.bIsbemol = false; tNote.bIssharp = false; tNote.NotePith = i; tNote.Octave =  6; tNote.Frequency = 1318.5; tNote.MidiShortMessage = 0x00405890;   }break;
        case 89 : {tNote.NoteName = "F" ; tNote.bIsbemol = false; tNote.bIssharp = false; tNote.NotePith = i; tNote.Octave =  6; tNote.Frequency = 1396.9; tNote.MidiShortMessage = 0x00405990;   }break;
        case 90 : {tNote.NoteName = "Gb"; tNote.bIsbemol = true ; tNote.bIssharp = false; tNote.NotePith = i; tNote.Octave =  6; tNote.Frequency = 1480.0; tNote.MidiShortMessage = 0x00405A90;   }break;
        case 91 : {tNote.NoteName = "G" ; tNote.bIsbemol = false; tNote.bIssharp = false; tNote.NotePith = i; tNote.Octave =  6; tNote.Frequency = 1568.0; tNote.MidiShortMessage = 0x00405B90;   }break;
        case 92 : {tNote.NoteName = "Ab"; tNote.bIsbemol = true ; tNote.bIssharp = false; tNote.NotePith = i; tNote.Octave =  6; tNote.Frequency = 1661.2; tNote.MidiShortMessage = 0x00405C90;   }break;
        case 93 : {tNote.NoteName = "A" ; tNote.bIsbemol = false; tNote.bIssharp = false; tNote.NotePith = i; tNote.Octave =  6; tNote.Frequency = 1760.0; tNote.MidiShortMessage = 0x00405D90;   }break;
        case 94 : {tNote.NoteName = "Bb"; tNote.bIsbemol = true ; tNote.bIssharp = false; tNote.NotePith = i; tNote.Octave =  6; tNote.Frequency = 1864.7; tNote.MidiShortMessage = 0x00405E90;   }break;
        case 95 : {tNote.NoteName = "B" ; tNote.bIsbemol = false; tNote.bIssharp = false; tNote.NotePith = i; tNote.Octave =  6; tNote.Frequency = 1975.5; tNote.MidiShortMessage = 0x00405F90;   }break;
        case 96 : {tNote.NoteName = "C" ; tNote.bIsbemol = false; tNote.bIssharp = false; tNote.NotePith = i; tNote.Octave =  7; tNote.Frequency = 2093.0; tNote.MidiShortMessage = 0x00406090;   }break;
        case 97 : {tNote.NoteName = "Db"; tNote.bIsbemol = true ; tNote.bIssharp = false; tNote.NotePith = i; tNote.Octave =  7; tNote.Frequency = 2217.5; tNote.MidiShortMessage = 0x00406190;   }break;
        case 98 : {tNote.NoteName = "D" ; tNote.bIsbemol = false; tNote.bIssharp = false; tNote.NotePith = i; tNote.Octave =  7; tNote.Frequency = 2349.3; tNote.MidiShortMessage = 0x00406290;   }break;
        case 99 : {tNote.NoteName = "Eb"; tNote.bIsbemol = true ; tNote.bIssharp = false; tNote.NotePith = i; tNote.Octave =  7; tNote.Frequency = 2489.0; tNote.MidiShortMessage = 0x00406390;   }break;
        case 100: {tNote.NoteName = "E" ; tNote.bIsbemol = false; tNote.bIssharp = false; tNote.NotePith = i; tNote.Octave =  7; tNote.Frequency = 2637.0; tNote.MidiShortMessage = 0x00406490;   }break;
        case 101: {tNote.NoteName = "F" ; tNote.bIsbemol = false; tNote.bIssharp = false; tNote.NotePith = i; tNote.Octave =  7; tNote.Frequency = 2793.0; tNote.MidiShortMessage = 0x00406590;   }break;
        case 102: {tNote.NoteName = "Gb"; tNote.bIsbemol = true ; tNote.bIssharp = false; tNote.NotePith = i; tNote.Octave =  7; tNote.Frequency = 2960.0; tNote.MidiShortMessage = 0x00406690;   }break;
        case 103: {tNote.NoteName = "G" ; tNote.bIsbemol = false; tNote.bIssharp = false; tNote.NotePith = i; tNote.Octave =  7; tNote.Frequency = 3136.0; tNote.MidiShortMessage = 0x00406790;   }break;
        case 104: {tNote.NoteName = "Ab"; tNote.bIsbemol = true ; tNote.bIssharp = false; tNote.NotePith = i; tNote.Octave =  7; tNote.Frequency = 3322.4; tNote.MidiShortMessage = 0x00406890;   }break;
        case 105: {tNote.NoteName = "A" ; tNote.bIsbemol = false; tNote.bIssharp = false; tNote.NotePith = i; tNote.Octave =  7; tNote.Frequency = 3520.0; tNote.MidiShortMessage = 0x00406990;   }break;
        case 106: {tNote.NoteName = "Bb"; tNote.bIsbemol = true ; tNote.bIssharp = false; tNote.NotePith = i; tNote.Octave =  7; tNote.Frequency = 3729.3; tNote.MidiShortMessage = 0x00406A90;   }break;
        case 107: {tNote.NoteName = "B" ; tNote.bIsbemol = false; tNote.bIssharp = false; tNote.NotePith = i; tNote.Octave =  7; tNote.Frequency = 3951.1; tNote.MidiShortMessage = 0x00406B90;   }break;
        case 108: {tNote.NoteName = "C" ; tNote.bIsbemol = false; tNote.bIssharp = false; tNote.NotePith = i; tNote.Octave =  8; tNote.Frequency = 4186.0; tNote.MidiShortMessage = 0x00406C90;   }break;
        case 109: {tNote.NoteName = "Db"; tNote.bIsbemol = true ; tNote.bIssharp = false; tNote.NotePith = i; tNote.Octave =  8; tNote.Frequency = 4434.9; tNote.MidiShortMessage = 0x00406D90;   }break;
        case 110: {tNote.NoteName = "D" ; tNote.bIsbemol = false; tNote.bIssharp = false; tNote.NotePith = i; tNote.Octave =  8; tNote.Frequency = 4698.6; tNote.MidiShortMessage = 0x00406E90;   }break;
        case 111: {tNote.NoteName = "Eb"; tNote.bIsbemol = true ; tNote.bIssharp = false; tNote.NotePith = i; tNote.Octave =  8; tNote.Frequency = 4978.0; tNote.MidiShortMessage = 0x00406F90;   }break;
        case 112: {tNote.NoteName = "E" ; tNote.bIsbemol = false; tNote.bIssharp = false; tNote.NotePith = i; tNote.Octave =  8; tNote.Frequency = 5274.0; tNote.MidiShortMessage = 0x00407090;   }break;
        case 113: {tNote.NoteName = "F" ; tNote.bIsbemol = false; tNote.bIssharp = false; tNote.NotePith = i; tNote.Octave =  8; tNote.Frequency = 5587.6; tNote.MidiShortMessage = 0x00407190;   }break;
        case 114: {tNote.NoteName = "Gb"; tNote.bIsbemol = true ; tNote.bIssharp = false; tNote.NotePith = i; tNote.Octave =  8; tNote.Frequency = 5919.9; tNote.MidiShortMessage = 0x00407290;   }break;
        case 115: {tNote.NoteName = "G" ; tNote.bIsbemol = false; tNote.bIssharp = false; tNote.NotePith = i; tNote.Octave =  8; tNote.Frequency = 6271.9; tNote.MidiShortMessage = 0x00407390;   }break;
        case 116: {tNote.NoteName = "Ab"; tNote.bIsbemol = true ; tNote.bIssharp = false; tNote.NotePith = i; tNote.Octave =  8; tNote.Frequency = 6644.8; tNote.MidiShortMessage = 0x00407490;   }break;
        case 117: {tNote.NoteName = "A" ; tNote.bIsbemol = false; tNote.bIssharp = false; tNote.NotePith = i; tNote.Octave =  8; tNote.Frequency = 7040.0; tNote.MidiShortMessage = 0x00407590;   }break;
        case 118: {tNote.NoteName = "Bb"; tNote.bIsbemol = true ; tNote.bIssharp = false; tNote.NotePith = i; tNote.Octave =  8; tNote.Frequency = 7458.6; tNote.MidiShortMessage = 0x00407690;   }break;
        case 119: {tNote.NoteName = "B" ; tNote.bIsbemol = false; tNote.bIssharp = false; tNote.NotePith = i; tNote.Octave =  8; tNote.Frequency = 7902.1; tNote.MidiShortMessage = 0x00407790;   }break;
        case 120: {tNote.NoteName = "C" ; tNote.bIsbemol = false; tNote.bIssharp = false; tNote.NotePith = i; tNote.Octave =  9; tNote.Frequency = 8372.0; tNote.MidiShortMessage = 0x00407890;   }break;
        case 121: {tNote.NoteName = "Db"; tNote.bIsbemol = true ; tNote.bIssharp = false; tNote.NotePith = i; tNote.Octave =  9; tNote.Frequency = 8869.8; tNote.MidiShortMessage = 0x00407990;   }break;
        case 122: {tNote.NoteName = "D" ; tNote.bIsbemol = false; tNote.bIssharp = false; tNote.NotePith = i; tNote.Octave =  9; tNote.Frequency = 9397.2; tNote.MidiShortMessage = 0x00407A90;   }break;
        case 123: {tNote.NoteName = "Eb"; tNote.bIsbemol = true ; tNote.bIssharp = false; tNote.NotePith = i; tNote.Octave =  9; tNote.Frequency = 9956.0; tNote.MidiShortMessage = 0x00407B90;   }break;
        case 124: {tNote.NoteName = "E" ; tNote.bIsbemol = false; tNote.bIssharp = false; tNote.NotePith = i; tNote.Octave =  9; tNote.Frequency = 10548.0; tNote.MidiShortMessage = 0x00407C90;   }break;
        case 125: {tNote.NoteName = "F" ; tNote.bIsbemol = false; tNote.bIssharp = false; tNote.NotePith = i; tNote.Octave =  9; tNote.Frequency = 11175.3; tNote.MidiShortMessage = 0x00407D90;   }break;
        case 126: {tNote.NoteName = "Gb"; tNote.bIsbemol = true ; tNote.bIssharp = false; tNote.NotePith = i; tNote.Octave =  9; tNote.Frequency = 11839.8; tNote.MidiShortMessage = 0x00407E90;   }break;
        case 127: {tNote.NoteName = "G" ; tNote.bIsbemol = false; tNote.bIssharp = false; tNote.NotePith = i; tNote.Octave =  9; tNote.Frequency = 12543.8; tNote.MidiShortMessage = 0x00407F90;   }break;

        }

        pQBPNoteTable.push_back(tNote);
    }
}


CQBPKeyboard::~CQBPKeyboard()
{
}

DiatonicNote CQBPKeyboard::GetNoteByPitch(double pQBPNotePith)
{
    for (int i = 0; i < pQBPNoteTable.size(); i++)
    {
        if (pQBPNoteTable[i].NotePith == pQBPNotePith)
        {
            return pQBPNoteTable[i];
        }
    }

    //retorna frequencia baixissima caso nao encontre
    return pQBPNoteTable[0];
}

DiatonicNote CQBPKeyboard::GetNoteByOctave(double pQBPNotePith, int pQBPOctave)
{
    DiatonicNote tNote;

    //Retorna a nota pelo Pitch
    tNote = GetNoteByPitch(pQBPNotePith);

    //Busca a mesma nota na oitava desejada!
    for (int i = 0; i < pQBPNoteTable.size(); i++)
    {
        if (pQBPNoteTable[i].NoteName == tNote.NoteName &&
            pQBPNoteTable[i].Octave   == pQBPOctave)
        {
            return pQBPNoteTable[i];
        }
    }

    //retorna frequencia baixissima caso nao encontre
    return pQBPNoteTable[0];
}

DiatonicNote CQBPKeyboard::GetRandomNote(int pQBPOctave)
{
    DiatonicNote tNote;
    int          tRandomNote;

    /*Inicializa a semente random*/
    srand (time(NULL));

    /*gera pith randomico entre as notas da oitava*/
    switch(pQBPOctave)
    {
    case -1:{tRandomNote = rand() % 0  + 12;}break;
    case  0:{tRandomNote = rand() % 12  + 12;}break;
    case  1:{tRandomNote = rand() % 24 + 12;}break;
    case  2:{tRandomNote = rand() % 36 + 12;}break;
    case  3:{tRandomNote = rand() % 48 + 12;}break;
    case  4:{tRandomNote = rand() % 60 + 12;}break;
    case  5:{tRandomNote = rand() % 72 + 12;}break;
    case  6:{tRandomNote = rand() % 84 + 12;}break;
    case  7:{tRandomNote = rand() % 96 + 12;}break;
    case  8:{tRandomNote = rand() % 108 + 12;}break;
    case  9:{tRandomNote = rand() % 120 + 12;}break;
    }

    //Retorna a nota pelo Pitch
    tNote = GetNoteByPitch(tRandomNote);

    //Busca a mesma nota na oitava desejada!
    for (int i = 0; i < pQBPNoteTable.size(); i++)
    {
        if (pQBPNoteTable[i].NoteName == tNote.NoteName &&
            pQBPNoteTable[i].Octave   == pQBPOctave)
        {
            return pQBPNoteTable[i];
        }
    }

    //retorna frequencia baixissima caso nao encontre
    return pQBPNoteTable[0];
}

string CQBPKeyboard::GetNoteNameByPitch(double pQBPNotePith)
{
    for (int i = 0; i < pQBPNoteTable.size(); i++)
    {
        if (pQBPNoteTable[i].NotePith == pQBPNotePith)
        {
            return pQBPNoteTable[i].NoteName;
        }
    }

    return "C";
}

vector<stQBPMusicBuffer> CQBPKeyboard::GetMusicBufferByDnt(vector<CQBPNote>  pQBPNotes, bool pQBPTranspose, int pQBPOctave)
{
    //Limpa o buffer de notas
    pQBPMusixBuffer.clear();
    //Sempre colocar o reserve zero para economizar memoria(O clear não limpa a reserva de espaço)
    pQBPMusixBuffer.shrink_to_fit();

    if(pQBPTranspose)
    {
        Transpose(pQBPNotes,pQBPOctave);
    }

    for (int i = 0; i < pQBPNotes.size(); i++)
    {
        for (int j = 0; j < pQBPNoteTable.size(); j++)
        {
            if (pQBPNoteTable[j].NotePith == pQBPNotes[i].pitch)
            {
                stQBPMusicBuffer tMusixNote;

                tMusixNote.bQBP_IsBemol          = pQBPNoteTable[j].bIsbemol;
                tMusixNote.bQBP_IsSharp          = pQBPNoteTable[j].bIssharp;
                tMusixNote.dQBP_Duration         = pQBPNotes[i].duration;
                tMusixNote.dQBP_Frequency        = pQBPNoteTable[j].Frequency;
                tMusixNote.iQBP_MidiShortMessage = pQBPNoteTable[j].MidiShortMessage;
                tMusixNote.iQBP_Octave           = pQBPNoteTable[j].Octave;
                tMusixNote.iQBP_Pitch            = pQBPNotes[i].pitch;

                //Calcula o contorno durante a construção do Buffer
                //Recomendação: Se tens um buffer e precisa calcular somente o contorno use a função Contour.
                if((i+1)==pQBPNotes.size())
                {
                   tMusixNote.iQBP_Contour = 0;
                }
                else
                {
                   tMusixNote.iQBP_Contour = abs(pQBPNotes[i+1].pitch - pQBPNotes[i].pitch);
                }

                tMusixNote.sQBP_Note             = pQBPNoteTable[j].NoteName;

                pQBPMusixBuffer.push_back(tMusixNote);
            }
        }
    }

    return pQBPMusixBuffer;
}
vector<stQBPStringBuffer> CQBPKeyboard::GetNoteBufferByDnt(vector<CQBPNote> pQBPNotes, bool pQBPTranspose , int pQBPOctave )
{
    //Limpa o buffer de notas
    pQBPNoteBuffer.clear();
    //Sempre colocar o reserve zero para economizar memoria(O clear não limpa a reserva de espaço)
    pQBPNoteBuffer.shrink_to_fit();


    if(pQBPTranspose)
    {
        Transpose(pQBPNotes,pQBPOctave);
    }

    for (int i = 0; i < pQBPNotes.size(); i++)
    {
        for (int j = 0; j < pQBPNoteTable.size(); j++)
        {
            if (pQBPNoteTable[j].NotePith == pQBPNotes[i].pitch)
            {
                stQBPStringBuffer tStringNote;
                tStringNote.sQBP_Note = pQBPNoteTable[j].NoteName;
                tStringNote.iQBP_Octave = pQBPNoteTable[j].Octave;
                pQBPNoteBuffer.push_back(tStringNote);
            }
        }
    }

    return pQBPNoteBuffer;
}

bool CQBPKeyboard::Play(vector<CQBPNote> pQBPNotes)
{
    for (int i = 0; i < pQBPNotes.size(); i++)
    {
        DiatonicNote tNote;

        tNote = GetNoteByPitch(pQBPNotes[i].pitch);
        //Agora envia diretamente para um MIDI Output na Maquina!
        pQBPMidiDevice->PlayNote(tNote, pQBPNotes[i].duration);
    }

    return true;
}

bool CQBPKeyboard::Play(vector<stQBPMusicBuffer>  pQBPNotes)
{
    for (int i = 0; i < pQBPNotes.size(); i++)
    {
        DiatonicNote tNote;

        tNote = GetNoteByPitch(pQBPNotes[i].iQBP_Pitch);
        //Agora envia diretamente para um MIDI Output na Maquina!
        pQBPMidiDevice->PlayNote(tNote, pQBPNotes[i].dQBP_Duration);
    }

    return true;
}

bool CQBPKeyboard::Transpose(vector<CQBPNote> &pQBPNotes, int pQBPOctave)
{
    //Testa se é uma oitava valida
    if (pQBPOctave < -1 || pQBPOctave > 9)return false;

    //Pega a nota diatonica e realiza a transposição para a nova oitava
    for (int i = 0; i < pQBPNotes.size(); i++)
    {
        DiatonicNote tNote;

        //Retorna a nota enviada na oitava desejada.
        tNote = GetNoteByOctave(pQBPNotes[i].pitch, pQBPOctave);

        //Atualiza a nota com o novo pitch
        pQBPNotes[i].pitch = (int)tNote.NotePith;
    }

    return true;
}

bool CQBPKeyboard::Contour(vector<stQBPMusicBuffer> &pQBPNotes,bool bLastZeroNote)
{
    if(bLastZeroNote)
    {
        //Pega a nota diatonica e realiza a transposição para a nova oitava
        for (int i = 0; i < pQBPNotes.size(); i++)
        {
            //Nota final tem contorno 0
            if((i+1)==pQBPNotes.size())
            {
                pQBPNotes[i].iQBP_Contour = 0;
            }
            else
            {
                pQBPNotes[i].iQBP_Contour = abs(pQBPNotes[i+1].iQBP_Pitch - pQBPNotes[i].iQBP_Pitch);
            }
        }
    }
    else
    {
        //Pega a nota diatonica e realiza a transposição para a nova oitava
        for (int i = 0; i < pQBPNotes.size(); i++)
        {
            //Nota inicial tem contorno 0
            if(i==0)
            {
                pQBPNotes[i].iQBP_Contour = 0;
            }
            else
            {
                pQBPNotes[i].iQBP_Contour = abs(pQBPNotes[i].iQBP_Pitch - pQBPNotes[i-1].iQBP_Pitch);
            }
        }
    }

    return true;
}

bool CQBPKeyboard::TuneUp(vector<CQBPNote> &pQBPNotes, int pQBPQtdSmt)
{
    //Pega a nota diatonica e realiza a transposição para a nova oitava
    for (int i = 0; i < pQBPNotes.size(); i++)
    {
        //Atualiza a nota com um semitom a mais
        pQBPNotes[i].pitch+= pQBPQtdSmt;
    }

    return true;
}

bool CQBPKeyboard::TuneDown(vector<CQBPNote> &pQBPNotes, int pQBPQtdSmt)
{
    //Pega a nota diatonica e realiza a transposição para a nova oitava
    for (int i = 0; i < pQBPNotes.size(); i++)
    {
        //Atualiza a nota com um semitom a mais
        pQBPNotes[i].pitch-= pQBPQtdSmt;
    }

    return true;
}

// sort pela oitava da nota
struct {
    bool operator()(DiatonicNote a, DiatonicNote b) const
    {
        return a.Octave < b.Octave;
    }
} QBPOctaveLess;

int CQBPKeyboard::ExtractOctaveFeature(vector<CQBPNote> &pQBPNotes)
{
    int tQtdOctaves=0;
    int iTempOctave=0;

    DiatonicNote          tNote;
    int                   tNoteOctave;
    vector<DiatonicNote>  pQBPSortedNotes;

    //Percorre descobrindo todas as oitavas
    for (int i = 0; i < pQBPNotes.size(); i++)
    {
        //Pega a oitava pelo Pitch
        tNote        = GetNoteByPitch(pQBPNotes[i].pitch);
        //Insere o valor na lista de sort
        pQBPSortedNotes.push_back(tNote);
    }

    //faz o sort pelas oitavas da lista
    std::sort(pQBPSortedNotes.begin(), pQBPSortedNotes.end(), QBPOctaveLess);

    //Percorre descobrindo todas as oitavas
    for (int i = 0; i < pQBPSortedNotes.size(); i++)
    {
        //Pega a oitava pelo Pitch
        tNoteOctave = pQBPSortedNotes[i].Octave;
        if (tNoteOctave != iTempOctave)
        {
            iTempOctave = tNoteOctave;
            tQtdOctaves++;
        }
    }

    pQBPSortedNotes.clear();
    //Sempre colocar o reserve zero para economizar memoria(O clear não limpa a reserva de espaço)
    pQBPSortedNotes.shrink_to_fit();

    return tQtdOctaves;
}

int CQBPKeyboard::ExtractBemoisFeature(vector<CQBPNote> &pQBPNotes)
{
    int tQtdBemois = 0;

    DiatonicNote      tNote;

    //Percorre descobrindo todas as oitavas
    for (int i = 0; i < pQBPNotes.size(); i++)
    {
        //Pega a oitava pelo Pitch
        tNote = GetNoteByPitch(pQBPNotes[i].pitch);

        if (tNote.bIsbemol)tQtdBemois++;
    }

    return tQtdBemois;
}

// sort pelo pitch
struct {
    bool operator()(DiatonicNote a, DiatonicNote b) const
    {
        return a.NotePith < b.NotePith;
    }
} QBPPitchLess;

int CQBPKeyboard::ExtractFPitchFeature(vector<CQBPNote> &pQBPNotes)
{
    int tQtdPitch   = 0;
    int tMaxPitch   = 0;
    int tFrePitch   = 0;
    int tPitch      = 0;
    int iTempPich   = 0;

    DiatonicNote tNote;
    vector<DiatonicNote>  pQBPSortedNotes;

    //Percorre descobrindo todas as oitavas
    for (int i = 0; i < pQBPNotes.size(); i++)
    {
        //Pega a oitava pelo Pitch
        tNote = GetNoteByPitch(pQBPNotes[i].pitch);
        //Insere o valor na lista de sort
        pQBPSortedNotes.push_back(tNote);
    }

    //faz o sort pelo pitch da lista
    std::sort(pQBPSortedNotes.begin(), pQBPSortedNotes.end(), QBPPitchLess);

    //Percorre descobrindo todas as oitavas
    for (int i = 0; i < pQBPSortedNotes.size(); i++)
    {
        //Pega a oitava pelo Pitch
        tPitch = (int)pQBPSortedNotes[i].NotePith;
        if (tPitch != iTempPich)
        {
            iTempPich = tPitch;
            tQtdPitch++;
            if (tQtdPitch > tMaxPitch)
            {
                tMaxPitch = tQtdPitch;
                tFrePitch = tPitch;
            }
        }
    }

    pQBPSortedNotes.clear();
    //Sempre colocar o reserve zero para economizar memoria(O clear não limpa a reserva de espaço)
    pQBPSortedNotes.shrink_to_fit();

    return tFrePitch;
}

int CQBPKeyboard::ExtractNPitchFeature(vector<CQBPNote> &pQBPNotes)
{
    int tQtdPitch = 0;
    int tPitch = 0;
    int iTempPich = 0;

    DiatonicNote tNote;
    vector<DiatonicNote>  pQBPSortedNotes;

    //Percorre descobrindo todas as notas
    for (int i = 0; i < pQBPNotes.size(); i++)
    {
        //Pega a oitava pelo Pitch
        tNote = GetNoteByPitch(pQBPNotes[i].pitch);
        //Insere o valor na lista de sort
        pQBPSortedNotes.push_back(tNote);
    }

    //faz o sort pelo pitch da lista
    std::sort(pQBPSortedNotes.begin(), pQBPSortedNotes.end(), QBPPitchLess);

    //Percorre descobrindo todas as oitavas
    for (int i = 0; i < pQBPSortedNotes.size(); i++)
    {
        //Pega a oitava pelo Pitch
        tPitch = (int)pQBPSortedNotes[i].NotePith;
        if (tPitch != iTempPich)
        {
            iTempPich = tPitch;
            tQtdPitch++;
        }
    }

    pQBPSortedNotes.clear();
    //Sempre colocar o reserve zero para economizar memoria(O clear não limpa a reserva de espaço)
    pQBPSortedNotes.shrink_to_fit();

    return tQtdPitch;
}

// sort pelo pitch
struct QBPRPitch
{
    DiatonicNote pRepeatedNote;
    int          pQtdRepetitions;
} ;

// sort pelo numero de repetições
struct {
    bool operator()(QBPRPitch a, QBPRPitch b) const
    {
        return a.pQtdRepetitions > b.pQtdRepetitions;
    }
} QBPRPitchGreater;

int CQBPKeyboard::ExtractRPitchFeature(vector<CQBPNote> &pQBPNotes)
{
    int                   tQtdRepetitions = 0;
    int                   tFinalPitchRep  = 0;
    int                   tMaxRepetitions = 0;
    QBPRPitch             tRepeatedNote      ;
    DiatonicNote          tNote              ;
    vector<DiatonicNote>  pQBPExecutedNotes  ;
    vector<QBPRPitch>     pQBPRepeatedNotes  ;
    bool                  pRepeatingNote     ;

    //Percorre descobrindo todas as notas
    for (int i = 0; i < pQBPNotes.size(); i++)
    {
        //Pega a oitava pelo Pitch
        tNote = GetNoteByPitch(pQBPNotes[i].pitch);
        //Insere o valor na lista de sort
        pQBPExecutedNotes.push_back(tNote);
    }

    //Percorre descobrindo as notas repetidas consecutivamente
    for (int i = 0; i < pQBPExecutedNotes.size(); i++)
    {
        tNote = pQBPExecutedNotes[i];
        tQtdRepetitions=0;
        pRepeatingNote = false;
        for (int j = 0; j < pQBPExecutedNotes.size()-1; j++)
        {
            if (tNote.NotePith == pQBPExecutedNotes[j    ].NotePith &&
                tNote.NotePith == pQBPExecutedNotes[j + 1].NotePith)
            {
                tQtdRepetitions++;
                if (tMaxRepetitions < tQtdRepetitions)
                {
                    tMaxRepetitions = tQtdRepetitions;
                    tRepeatedNote.pRepeatedNote = tNote;
                    tRepeatedNote.pQtdRepetitions = tQtdRepetitions;

                    pQBPRepeatedNotes.push_back(tRepeatedNote);
                }

            }
            else
            {
                tQtdRepetitions = 0;
            }
        }
    }

    //faz o sort pelo maior numero de repetições
    std::sort(pQBPRepeatedNotes.begin(), pQBPRepeatedNotes.end(), QBPRPitchGreater);

    //checa se houve repetições consecutivas
    if (pQBPRepeatedNotes.size() == 0)return 0;

    //Se Houve, o primeiro indice é a nota com o maior numero de repetições!
    tFinalPitchRep = (int)pQBPRepeatedNotes[0].pQtdRepetitions;

    //limpa vetores auxiliares
    pQBPRepeatedNotes.clear();
    //Sempre colocar o reserve zero para economizar memoria(O clear não limpa a reserva de espaço)
    pQBPRepeatedNotes.shrink_to_fit();

    pQBPExecutedNotes.clear();
    //Sempre colocar o reserve zero para economizar memoria(O clear não limpa a reserva de espaço)
    pQBPExecutedNotes.shrink_to_fit();

    //retorna a feature finalmente...
    return tFinalPitchRep;
}

int CQBPKeyboard::ExtractAttituFeature(vector<CQBPNote> &pQBPNotes)
{
    int                   tQBPTempoMedioNotas = 0;
    int                   tQBPRepPitch = 0;
    int                   pQBPQtdPitchs = 0;
    int                   tAttitude = 0;

    //extrai o tempo medio
    tQBPTempoMedioNotas = (int)ExtractTMedioFeature(pQBPNotes);

    //Se não houver não há atitude alguma...
    if (tQBPTempoMedioNotas == 0)return 0;

    //Extraimos as execuções repetitivas!
    tQBPRepPitch = ExtractRPitchFeature(pQBPNotes);

    //Caso não haja repetições consecutivas
    if (tQBPRepPitch==0)
    {
        //confrontamos com a quantidade de notas unicas usadas na musica
        pQBPQtdPitchs=ExtractNPitchFeature(pQBPNotes);

        //dificil de acontecer maasss...se não houver atitude alguma...
        if (pQBPQtdPitchs == 0)
        {
            return 0;
        }

        //Atribui a atitude pelo numero de notas..
        tAttitude = tQBPTempoMedioNotas / pQBPQtdPitchs;

    }
    else
    {
        //Atribui a atituda pelo numero de repeticoes
        tAttitude = tQBPTempoMedioNotas / tQBPRepPitch;
    }

    //retorna a feature finalmente...
    return tAttitude;
}

int CQBPKeyboard::ExtractDtncHistogram(vector<CQBPNote> &pQBPNotes,int &C,int &CS,int &D,
                                                                   int &DS,int &E,int &F,
                                                                   int &FS,int &G,int &GS,
                                                                   int &A,int &AS,int &B)
{

    DiatonicNote          tNote                ;
    vector<DiatonicNote>  pQBPExecutedNotes    ;
    vector<int>           pQBPDiatonicHistogram;
    vector<CQBPNote>      pQBPTransposedNotes  ;

    //Tranpoe as notas para a escala 5 e garantir o histograma
    pQBPTransposedNotes = pQBPNotes;

    Transpose(pQBPTransposedNotes,5);

    //Inicializa o Histograma
    for (int i = 0; i < 12; i++)pQBPDiatonicHistogram.push_back(0);

    //Percorre descobrindo todas as notas
    for (int i = 0; i < pQBPTransposedNotes.size(); i++)
    {
        //Pega a oitava pelo Pitch
        tNote = GetNoteByPitch(pQBPTransposedNotes[i].pitch);
        //Insere o valor na lista de sort
        pQBPExecutedNotes.push_back(tNote);
    }

    //Percorre descobrindo as notas repetidas consecutivamente
    for (int i = 0; i < pQBPExecutedNotes.size(); i++)
    {
        tNote = pQBPExecutedNotes[i];
        switch((int)tNote.NotePith)
        {
        case 72:{pQBPDiatonicHistogram[ 0]++;}break;
        case 73:{pQBPDiatonicHistogram[ 1]++;}break;
        case 74:{pQBPDiatonicHistogram[ 2]++;}break;
        case 75:{pQBPDiatonicHistogram[ 3]++;}break;
        case 76:{pQBPDiatonicHistogram[ 4]++;}break;
        case 77:{pQBPDiatonicHistogram[ 5]++;}break;
        case 78:{pQBPDiatonicHistogram[ 6]++;}break;
        case 79:{pQBPDiatonicHistogram[ 7]++;}break;
        case 80:{pQBPDiatonicHistogram[ 8]++;}break;
        case 81:{pQBPDiatonicHistogram[ 9]++;}break;
        case 82:{pQBPDiatonicHistogram[10]++;}break;
        case 83:{pQBPDiatonicHistogram[11]++;}break;
        }
    }

    //repassa os contadores do histograma
    C  = pQBPDiatonicHistogram[ 0];
    CS = pQBPDiatonicHistogram[ 1];
    D  = pQBPDiatonicHistogram[ 2];
    DS = pQBPDiatonicHistogram[ 3];
    E  = pQBPDiatonicHistogram[ 4];
    F  = pQBPDiatonicHistogram[ 5];
    FS = pQBPDiatonicHistogram[ 6];
    G  = pQBPDiatonicHistogram[ 7];
    GS = pQBPDiatonicHistogram[ 8];
    A  = pQBPDiatonicHistogram[ 9];
    AS = pQBPDiatonicHistogram[10];
    B  = pQBPDiatonicHistogram[11];
    //limpa vetores auxiliares
    pQBPExecutedNotes.clear();
    //Sempre colocar o reserve zero para economizar memoria(O clear não limpa a reserva de espaço)
    pQBPExecutedNotes.shrink_to_fit();

    //Por enquanto retorna zero... (A ideia é retornar algo como a nota de maior frequencia)
    return 0;
}
int CQBPKeyboard::ExtractBpmmedFeature(vector<CQBPNote> &pQBPNotes)
{
    double                tQBPTempoTotalNotas = 0;
    double                tQBPTempoMedioNotas = 0;
    int                   tQBPBPM = 0;

    //extrai o tempo total
    tQBPTempoTotalNotas = ExtractTTotalFeature(pQBPNotes);
    tQBPTempoMedioNotas = ExtractTMedioFeature(pQBPNotes);

    tQBPBPM = (int)60000 / (int)tQBPTempoMedioNotas;

    //retorna a feature finalmente...
    return tQBPBPM;
}

double CQBPKeyboard::ExtractTMedioFeature(vector<CQBPNote> &pQBPNotes)
{
    double tTMedio = 0;
    double tTTotal = 0;

    //Percorre somando o tempo de cada nota
    for (int i = 0; i < pQBPNotes.size(); i++)
    {
        //soma a duração da nota
        tTTotal += pQBPNotes[i].duration;
    }

    //calcula a media de tempo
    tTMedio = tTTotal / pQBPNotes.size();

    return tTMedio;
}

double CQBPKeyboard::ExtractTTotalFeature(vector<CQBPNote> &pQBPNotes)
{
    double tTTotal = 0;

    //Percorre somando o tempo de cada nota
    for (int i = 0; i < pQBPNotes.size(); i++)
    {
        //soma a duração da nota
        tTTotal += pQBPNotes[i].duration;
    }

    return tTTotal;
}
