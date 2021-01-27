/*************************************************************************/
/*PPGIa - Advanced Topics in Computational Intelligence - PUCPR          */
/*Author: William Wolff                                                  */
/*Classe Dataset - O objetivo principal da classe Dataset é realizar e   */
/*Criar/converter as informações de musicas extraidas dos arquivos MIDI  */
/*contidos no diretorio dataset utilizado pelo projeto.                  */
/*Inicialmente esta classe sera utilizada para carregar todos os arquivos*/
/*MIDI e criar uma base em memória das musicas com as devidas notas e    */
/*Criação dos buffers de comparação para serem utilizados pelo algoritmo */
/*de alinhamento global e o classificador SVM.                           */
/*Esta classe também sera utilizada por enquanto para a exportação e     */
/*carregamento dos dados de treinamento e validação da base              */
/*************************************************************************/
#ifndef QBP_DATASET_H_
#define QBP_DATASET_H_

#include "QBP_GlobalDef.h"
#include "QBP_Song.h"
#include "QBP_Genre.h"
#include "QBP_Keyboard.h"
#include "QBP_JSymbolicFile.h"
#include "QBP_LogQueue.h"
#include "QBP_Chord.h"

class CQBPDataset
{
public:
     CQBPDataset();
    ~CQBPDataset();

    bool LoadDataset      (string    pQBPath , int pQBPLoadType ,int pQBPTargetList);
    bool LoadSong         (CQBPSong &pQBPSong                   );
    bool LoadChords       (string    pQBPath                    );

    bool WriteDts         (string    pQBPath , int pQBPWrtOption);
    bool WriteSvm         (string    pQBPath , int pQBPWrtOption);
    bool WriteSvmNorm     (string    pQBPath , int pQBPWrtOption);
    bool WriteSvmCat      (string    pQBPath , int pQBPWrtOption,int pQBPCategory);
    bool WriteGen         (string    pQBPath );

    bool BuildMusicBuffers  (int  pQBPTargetList);
    bool BuildStrippedDts   (int  pQBPTargetList);
    bool BuildFeaturesDts   (int  pQBPTargetList);
    bool BuildStatistics    (                   );
    bool BuildCustomFeatures(int  pQBPTargetList);
    bool BuildNormalFeatures(int  pQBPTargetList);
    bool BuildCustomFeatType(                   );
    bool BuildJSymboFeatType(                   );
    bool BuildJSymboFeatures(int  pQBPTargetList);

    bool Print            (                                              );
    bool ClearDataset     (int    pQBPTargetList                         );
    bool SearchSongByName (string pQBPSongName   , CQBPSong &pQBPSong    );
    bool GetLessGenre     (int   &pQBPGenreIndex , int      &pQBPQtdSongs);
    bool GetGreaterGenre  (int   &pQBPGenreIndex , int      &pQBPQtdSongs);
    bool CheckTestSet     (                                              );

    bool CreateSet        (int    pQBPTargetList , int       pQBPFormType, int       pQBPBufferSize);

    bool ShuffleSet       (int    pQBPTargetList                         );

    bool CopySet          (int    pQBPTargetList , int       pQBPQtdSongs       , int       pQBPBufferSize);
    bool ExtractSet       (int    pQBPTargetList ,vector<CQBPSong *> &pQBPTarget);

    bool CopySetRandom    (int    pQBPTargetList , int       pQBPQtdSongs       , int       pQBPBufferSize);
    bool ExtractSetRandom (int    pQBPTargetList ,vector<CQBPSong *> &pQBPTarget);

    bool CheckDataHealth  (                                              );

    void SetLock(bool pQBPLock){bQBPSetLock = pQBPLock;}
    bool GetLock(             ){return     bQBPSetLock;}

    CQBPFeatureType GetFeatureType      (string sQBP_FeatureName, int &iQBP_FeatureId);
    bool            GetFeatureDimensions(string sQBP_FeatureName, int &iQBP_FeatureDimensions);
    bool            GetSongByName       (string sQBP_SongName, CQBPSong &pQBPSong ,int    pQBPTargetList);
    bool            PlaySong            (CQBPSong pQBPSong);
    DiatonicNote    GetRandomNote       (int pQBPOctave);

public:

    //Definições de Features
    vector<CQBPFeatureType> pQBP_FeatureTypeList;//Definições de Features globais do sistema

    //Parsers de arquivos MIDI e JSymbolic
    MidiFile          pArqMidi       ;//Objeto de Parser MIDI
    CQBPJSymbolicFile pArqJSymbolic  ;//Objeto de Parser JSymbolic

    //Este teclado Virtual sera utilizado no futuro com interface a disp. MIDI
    CQBPKeyboard      pQBPKeyboard   ;//Teclado virtual de apoio

    //Informações Estatisticas da Base Criada(Apenas para otimização)
    int              pQBPQtdSongs;
    string           pQBPBiggerSongName;
    int              pQBPBiggerSongQtdNotes;
    int              pQBPAvrgNotesBySong;
    int              pQBPQtdStrips;
    int              pQBPMaxFeatures;

    //Controladores de Processo
    bool             bQBPSetLock;//Pseudo-Semáforo de processamento
    bool             bQBPStretchStrip;//Normaliza o Numero de Notas para valor definido
    uint             iQBPStretchValue;//Corta o Numero de notas até este valor

    //Informações estáticas utilizadas para as metricas(Futuramente sera migrado tudo para cá)
    static float   fQBPDatasetCountTP,
                   fQBPDatasetCountFP,
                   fQBPDatasetCountTN,
                   fQBPDatasetCountFN;
    static float   fQBPDatasetPrecision,
                   fQBPDatasetRecall,
                   fQBPDatasetFmeasure,
                   fQBPDatasetAccuracy;

    //Datasets de musica
    vector<CQBPGenre> pQBPGenreList  ;//Lista de Musicas do dataset(Subdivididos por genero)
    vector<CQBPSong>  pQBPTestList   ;//Lista de Musicas do genero teste
    vector<CQBPSong>  pQBPValiList   ;//Lista de Musicas do genero validação
    vector<CQBPSong>  pQBPRandomList ;//Lista de Musicas Randomica
    vector<CQBPSong>  pQBPFullList   ;//Lista Full de Musicas para Experimentos
    vector<CQBPSong>  pQBPMusicPlayer;//Lista de Musicas do player de musica
    vector<CQBPChord> pQBPChords     ;//Lista de Acordes do dataset(Instrumento de 6 vozes)
};

#endif

