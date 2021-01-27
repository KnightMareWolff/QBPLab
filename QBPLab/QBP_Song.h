/*************************************************************************/
/*PPGIa - Advanced Topics in Computational Intelligence - PUCPR          */
/*Author: William Wolff                                                  */
/*Classe Song - O objetivo principal da classe Song é armazenar features */
/*contidas em uma musica, incluindo a lista de notas musicais            */
/*************************************************************************/
#ifndef QBP_SONG_H_
#define QBP_SONG_H_

#include "QBP_GlobalDef.h"
#include "QBP_Note.h"
#include "QBP_Feature.h"

class CQBPSong
{
public:
     CQBPSong(                    );
     CQBPSong( const CQBPSong &obj);
    ~CQBPSong(                    );

     CQBPSong & operator = (const CQBPSong& other);

    bool StripBuffer    (int pQBPNotesByStrip);
    bool NormStripBuffer(int pQBPNotesByStrip);
    //bool RemoveBemol    (                    );
    bool ClearSong      (                    );

    int  Distance   (CQBPSong         pQBPSong);
    void AddNote    (stQBPMusicBuffer pQBPNote,int pQBPRecurrency);
    void RemNote    (stQBPMusicBuffer pQBPNote,int pQBPPosition  );
    void RemFromPos (int pQBPPosition  );
    void RepNote    (stQBPMusicBuffer pQBPNote,int pQBPPosition  );

    //Dados MIDI
    vector<CQBPNote> pQBPNotes;

    //Dados Musica para processamento
    string           pQBPSongName          ;//Nome da musica(filename)
    int              pQBPSongCategory      ;//Categoria da musica
    int              pQBPSongCategoryIndex ;//Indice da musica na Categoria
    int              pQBPSongGlobalIndex   ;//Indice Global da Musica no Dataset
    int              pQBPSongScore         ;//Score de similaridade da musica
    int              pQBPSongClassification;//classificação de similaridade de musica(TP,FP,TN,FN)

    //Dados auxiliares em casos de cópia alterada(Musicas Randomicas)
    string           pQBPOriginalName      ;//Nome da musica original(no caso de copia alterada)
    int              pQBPOriginalCategory  ;//Categoria Original da Musica(no caso de copia alterada)

    bool             pQBPStripped       ;//indica que houve strip de buffers
    bool             pQBPFeatured       ;//indica que houve calculo de features

    //Song Buffers
    vector<stQBPStringBuffer>         pQBPSongBuffer     ;//Buffer de notas diatonicas da musica completa
    vector<vector<stQBPStringBuffer>> pQBPSongBufferStrip;//vetor de buffers menores da musica

    vector<stQBPMusicBuffer > pQBPMusixBuffer    ;//Buffer de features musical(Features de Notas)
    vector<stQBPMusicBuffer > pQBPMusixBegin     ;//Buffer de features musical(Features de Notas)
    vector<stQBPMusicBuffer > pQBPMusixMid       ;//Buffer de features musical(Features de Notas)
    vector<stQBPMusicBuffer > pQBPMusixEnd       ;//Buffer de features musical(Features de Notas)

    //Features da Musica
    vector<CQBPFeature> pQBPFeatures;
    vector<CQBPFeature> pQBPCustomFeatures;//QBPLab Custom Features
    vector<CQBPFeature> pQBPJSymboFeatures;//JSymbolic Imported Features
    vector<CQBPFeature> pQBPNormalFeatures;//Normalized Features
};

#endif
