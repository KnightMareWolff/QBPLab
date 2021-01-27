#include "QBP_MidiDevice.h"



CQBPMidiDevice::CQBPMidiDevice()
{
    int    MidiShortMessage=0x004001C0;

    pQBPError = midiOutOpen(&pQBPMidiOut,0, 0, 0, CALLBACK_NULL);
    if (pQBPError != MMSYSERR_NOERROR)
        printf("error opening MIDI Mapper: %d\n", pQBPError);
    //else
        //printf("successfully opened MIDI Mapper\n");
    midiOutShortMsg(pQBPMidiOut, MidiShortMessage);

    pQBPError = midiInOpen(&pQBPMidiIn,0, 0, 0, CALLBACK_NULL);

}


CQBPMidiDevice::~CQBPMidiDevice()
{
    midiOutClose(pQBPMidiOut);
}

bool CQBPMidiDevice::PlayNote(DiatonicNote pQBPKeyboardNote, double pQBPDuration)
{
    midiOutShortMsg(pQBPMidiOut, pQBPKeyboardNote.MidiShortMessage);
    Sleep((DWORD)pQBPDuration);
    return true;
}
