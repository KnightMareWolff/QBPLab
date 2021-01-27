/*************************************************************************/
/*PPGIa - Advanced Topics in Computational Intelligence - PUCPR          */
/*Author: William Wolff                                                  */
/*Classe Keyboard - O objetivo principal da classe Keyboard é facilitar  */
/*a identificação das notas musicais já que arquivos MIDI Não armazenam  */
/*Notas, mas sim comandos que sao armazenados ao pressionar/soltar teclas*/
/*de um teclado MIDI, portanto os valores de pitch devem ser convertidos */
/*pelos seus valores de acordo com a tecla pressionada gerando assim a   */
/*nota na escala diatônica de acordo com a oitava do teclado.            */
/*************************************************************************/
#ifndef QBP_KEYBOARD_H_
#define QBP_KEYBOARD_H_

#include "QBP_GlobalDef.h"
#include "QBP_Note.h"
#include "QBP_MidiDevice.h"

class CQBPKeyboard
{
public:
     CQBPKeyboard();
    ~CQBPKeyboard();

    //Data Retrieve
    DiatonicNote              GetNoteByPitch     (double            pQBPNotePith                );
    DiatonicNote              GetNoteByOctave    (double            pQBPNotePith, int pQBPOctave);
    DiatonicNote              GetRandomNote      (                                int pQBPOctave);
    string                    GetNoteNameByPitch (double            pQBPNotePith                );
    vector<stQBPStringBuffer> GetNoteBufferByDnt (vector<CQBPNote>  pQBPNotes   , bool pQBPTranspose , int pQBPOctave );
    vector<stQBPMusicBuffer>  GetMusicBufferByDnt(vector<CQBPNote>  pQBPNotes   , bool pQBPTranspose , int pQBPOctave );

    //Play & Notes Manipulation
    bool         Play                (vector<CQBPNote>          pQBPNotes                           );
    bool         Play                (vector<stQBPMusicBuffer>  pQBPNotes                           );
    bool         Contour             (vector<stQBPMusicBuffer> &pQBPNotes        ,bool bLastZeroNote);
    bool         Transpose           (vector<CQBPNote> &pQBPNotes, int pQBPOctave);
    bool         TuneUp              (vector<CQBPNote> &pQBPNotes, int pQBPQtdSmt);
    bool         TuneDown            (vector<CQBPNote> &pQBPNotes, int pQBPQtdSmt);

    //Notes Feature Extraction
    int          ExtractOctaveFeature(vector<CQBPNote> &pQBPNotes);
    int          ExtractBemoisFeature(vector<CQBPNote> &pQBPNotes);
    int          ExtractFPitchFeature(vector<CQBPNote> &pQBPNotes);
    int          ExtractNPitchFeature(vector<CQBPNote> &pQBPNotes);
    int          ExtractRPitchFeature(vector<CQBPNote> &pQBPNotes);
    int          ExtractAttituFeature(vector<CQBPNote> &pQBPNotes);

    int          ExtractDtncHistogram(vector<CQBPNote> &pQBPNotes,int &C ,int &CS,int &D ,
                                                                  int &DS,int &E ,int &F ,
                                                                  int &FS,int &G ,int &GS,
                                                                  int &A ,int &AS,int &B );

    int          ExtractBpmmedFeature(vector<CQBPNote> &pQBPNotes);
    double       ExtractTMedioFeature(vector<CQBPNote> &pQBPNotes);
    double       ExtractTTotalFeature(vector<CQBPNote> &pQBPNotes);



private:
    vector<DiatonicNote>      pQBPNoteTable;
    vector<stQBPStringBuffer> pQBPNoteBuffer;
    vector<stQBPMusicBuffer>  pQBPMusixBuffer;
    CQBPMidiDevice           *pQBPMidiDevice;
};

#endif

