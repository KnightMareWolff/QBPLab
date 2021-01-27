/*************************************************************************/
/*PPGIa - Advanced Topics in Computational Intelligence - PUCPR          */
/*Author: William Wolff                                                  */
/*Classe MidiDevice - O objetivo principal da classe MidiDevice é        */
/*facilitar a conexao com um device MIDI para envio e recebimento de     */
/*Mensagens de entrada e saida MIDI dos buffers gerados pelo Keyboard    */
/*************************************************************************/
#ifndef QBP_MIDIDEVICE_H_
#define QBP_MIDIDEVICE_H_

#include "QBP_GlobalDef.h"

//Estabelece os valores para uma nota na escala diatonica dentro das oitavas possiveis do teclado
struct DiatonicNote
{
    string NoteName;
    double NotePith;
    int    Octave;
    double Frequency;
    bool   bIsbemol;
    bool   bIssharp;
    int    MidiShortMessage;
};

class CQBPMidiDevice
{
public:
     CQBPMidiDevice();
    ~CQBPMidiDevice();

    bool PlayNote(DiatonicNote pQBPKeyboardNote,double pQBPDuration);

private:
    HMIDIOUT  pQBPMidiOut;
    HMIDIIN   pQBPMidiIn;
    HMIDI     pQBPMidiInterface;
    int       pQBPError;
};

#endif
