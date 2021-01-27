/*************************************************************************/
/*PPGIa - Advanced Topics in Computational Intelligence - PUCPR          */
/*Author: William Wolff                                                  */
/*GlobalDef - Header Global para declaração de componentes Verticais     */
/*************************************************************************/
#ifndef QBP_GLOBALDEF_H_
#define QBP_GLOBALDEF_H_

//Includes da plataforma
#include <QApplication>
#include <QMainWindow>
#include <QMenuBar>
#include <QMenu>
#include <QMessageBox>
#include <QToolBar>
#include <QStatusBar>
#include <QDockWidget>
#include <QPlainTextEdit>
#include <QFileDialog>
#include <QTextStream>
#include <QApplication>
#include <QSettings>
#include <QDesktopWidget>
#include <QSessionManager>
#include <QWidget>
#include <QTabWidget>
#include <QVBoxLayout>
#include <QGroupBox>
#include <QRadioButton>
#include <QPushButton>
#include <QCheckBox>
#include <QLabel>
#include <QLineEdit>
#include <QElapsedTimer>
#include <QTimer>
#include <QtConcurrent>
#include <QProgressBar>
#include <QFileSystemModel>
#include <QTreeWidget>
#include <QStyleFactory>
#include <QQueue>
#include <QVector>
#include <QtCharts>
#include <Qt3DCore>
#include <Qt3DRender>
#include <Qt3DInput>
#include <Qt3DLogic>
#include <Qt3DExtras>
#include <Qt3DAnimation>
#include <QtDataVisualization>
#include <QAbstract3DSeries>
#include <Q3DScatter>
#include <QPainter>
#include <QImage>
//#include "QGuidoWidget.h"
using namespace QtDataVisualization;

#include <windows.h>
#include <mmsystem.h>
#include <stdio.h>
#include <fstream>
#include <vector>
#include <memory>
#include <ctime>
#include <random>
#include <algorithm>
#include <iostream>
#include <string>
#include <regex>
#include <iomanip>
#include <cmath>
#include <ctgmath>
//#include "LibSVM/QBP_Svm.h"        //Componente de Suport Vector Machines
#include "MIDI/QBP_MidiFile.h"   //Componente para parse de arquivos MIDI
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/video.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/ml.hpp>
//#include <opencv2/objdetect.hpp>
//#include <opencv2/calib3d.hpp>
//#include <opencv2/dnn.hpp>
//#include <opencv2/features2d.hpp>
//#include <opencv2/flann.hpp>
//#include <opencv2/photo.hpp>
//#include <opencv2/stitching.hpp>
using namespace std;
using namespace cv;
using namespace cv::ml;

/**************************/
/*Includes da Lua e Tolua */
/**************************/
extern "C" {
#include "LibLUA/lua.h"
#include "LibLUA/lualib.h"
#include "LibLUA/lauxlib.h"
}

#include "LibToLUA/tolua.h"

//Types of search possible
#define QBP_SCH_TYPE_SINGLE 0
#define QBP_SCH_TYPE_SET    1
#define QBP_SCH_TYPE_FULL   2

//Types of search post-processing
#define QBP_SCH_PPROC_SORT        0
#define QBP_SCH_PPROC_QUEUE       1
#define QBP_SCH_PPROC_MULTIQUEUE  2

//Types of Search Classification
#define QBP_SCH_CLASS_TP    0
#define QBP_SCH_CLASS_FP    1
#define QBP_SCH_CLASS_TN    2
#define QBP_SCH_CLASS_FN    3

//Directions used in the algorithm
#define QBP_VAL_DIR_INIT 0 //Inicialização
#define QBP_VAL_DIR_NONE 1 //Blocked
#define QBP_VAL_DIR_TOP  2 //Deleção
#define QBP_VAL_DIR_DIAG 3 //MATCH OU MISMATCH
#define QBP_VAL_DIR_LEFT 4 //INSERÇÃO

//Analisys Nodes para grafico Debbug
#define QBP_ND_DBG_BLK   0 //Nó Bloqueado
#define QBP_ND_DBG_RPH   1 //Root Path Node
#define QBP_ND_DBG_NPH   2 //Node Path
#define QBP_ND_DBG_NIN   3 //Node Inclusão
#define QBP_ND_DBG_NUP   4 //Node Alteração
#define QBP_ND_DBG_NEX   5 //Node Exclusão
#define QBP_ND_DBG_NMA   6 //Node Match/Mismatch
#define QBP_ND_DBG_BRD   7 //Border Node

//Types of Debug Notes in the Debug Graphic
#define QBP_DBG_NOTE      0 //Default Note
#define QBP_DBG_NOTE_EXCL 1 //Note for Exclusion
#define QBP_DBG_NOTE_INCL 2 //Note for Inclusion
#define QBP_DBG_NOTE_UPDT 3 //Note for Update
#define QBP_DBG_NOTE_TARG 4 //Note Target(Usually at Buffer B)

//Algorithm Debug Log Parameters
#define QBP_ALG_DBG_NONE 0 //Sem Log de Debug
#define QBP_ALG_DBG_SONG 1 //Apenas Parametros de Busca
#define QBP_ALG_DBG_MTX  2 //Loga a Substitution Matrix
#define QBP_ALG_DBG_STEP 3 //Loga cada Frame da Mtx

#define QBP_TRACE_DIR_BACKWARD 1
#define QBP_TRACE_DIR_FOWARD   2

#define QBP_LOAD_TYPE_BUILD 1//Carrega/converte e grava datasets
#define QBP_LOAD_TYPE_FULL  2//Carrega apenas dataset full
#define QBP_LOAD_TYPE_MIDI  4//Carrega apenas dataset MIDI
#define QBP_LOAD_TYPE_GENRE 5//Carrega apenas dataset Generos musicais

#define QBP_LOAD_TARGET_DATASET 1//Direciona a carga para o dataset principal
#define QBP_LOAD_TARGET_TESTSET 2//Direciona a carga para o Test Set(Lista de Teste)
#define QBP_LOAD_TARGET_VALISET 3//Direciona a Carga para o Vali Set(Lista de Validação)
#define QBP_LOAD_TARGET_FULLSET 4//Direciona a Carga para o Vali Set(Lista de Validação)
#define QBP_LOAD_TARGET_RANDSET 5//Direciona Carga para set Randomico de musicas
#define QBP_LOAD_TARGET_MUSPLAY 6//Direciona a Carga para o Play Set(Lista de Execução)
#define QBP_LOAD_TARGET_JSYMBOL 7//Direciona a Carga para o dataset principal (Features JSYMBOLIC)

#define QBP_FORM_TYPE_LESS_GENRE 1//Extrai 10% do genero com menor numero de musicas para todos os generos
#define QBP_FORM_TYPE_PERC_10    2//Extrai 10% do genero para o Set especificado do genero atual
#define QBP_FORM_TYPE_PERC_15    3//Extrai 15% do genero para o Set especificado do genero atual
#define QBP_FORM_TYPE_LESS_1015F 4//Extrai 10% do genero para o Set de Teste e 15% para o set de validação

#define QBP_SVM_TRAIN_TESTLIST   1//Grava Arquivo de treino do testlist
#define QBP_SVM_TRAIN_VALILIST   2//Grava Arquivo de treino do valilist
#define QBP_SVM_TRAIN_DATASET    3//Grava Arquivo de treino do dataset principal

#define QBP_STRIP_BEG 0
#define QBP_STRIP_MID 1
#define QBP_STRIP_END 2
#define QBP_STRIP_TOT 3

#define QBP_MATRIX_TYPE_ORIGIN 0//Original Smith Waterman Matrix
#define QBP_MATRIX_TYPE_MUSSUM 1//Music Substitution Matrix
#define QBP_MATRIX_TYPE_MUSSIX 2//New Matrix (Musical Space Matrix)
#define QBP_MATRIX_TYPE_MUSSAT 3//Musical Attitude Space.

#define QBP_PROC_OPT_01 1 //Build Full Dataset.
#define QBP_PROC_OPT_02 2 //Perform User Snippet Search.
#define QBP_PROC_OPT_03 3 //Perform Random Snippet Search.
#define QBP_PROC_OPT_04 4 //Build SVM Classifier Datasets.
#define QBP_PROC_OPT_05 5 //Train SVM Classifier.
#define QBP_PROC_OPT_06 6 //Perform QBP Search.
#define QBP_PROC_OPT_07 7 //Test MIDI Device.

#define QBP_LOG_TYPE_ENG 1 //Log Type Engine.
#define QBP_LOG_TYPE_DTS 2 //Log Type Dataset.
#define QBP_LOG_TYPE_CLS 3 //Log Type Classifier.
#define QBP_LOG_TYPE_CMP 4 //Log Type Comparator.

#define QBP_TAB_TYPE_DTS 0 //Tab Dataset.
#define QBP_TAB_TYPE_CMP 1 //Tab Comparator.
#define QBP_TAB_TYPE_CLS 2 //Tab Classifier.
#define QBP_TAB_TYPE_PLY 3 //Tab Player.

#define QBP_TAB_TYPE_LOG 0 //Tab Log.
#define QBP_TAB_TYPE_AUT 1 //Tab Automation.
#define QBP_TAB_TYPE_CRT 2 //Tab Charts.
#define QBP_TAB_TYPE_C3D 3 //Tab Charts 3D.
#define QBP_TAB_TYPE_DBG 4 //Tab Debbug.

#define QBP_PRC_TYPE_NONE      0  //None Process.
#define QBP_PRC_TYPE_LOAD      1  //Loading Process ID.
#define QBP_PRC_TYPE_GENRE     2  //Loading Process ID.
#define QBP_PRC_TYPE_ML        3  //Machine Learning Process ID.
#define QBP_PRC_TYPE_SCHSINGLE 4  //Music Search Process ID.
#define QBP_PRC_TYPE_PLAY      5  //Playing a Song?.
#define QBP_PRC_TYPE_ASCH      6  //Automatic Music Search Process ID.
#define QBP_PRC_TYPE_LOADTEST  7  //Loading Process ID.
#define QBP_PRC_TYPE_LOADVALI  8  //Loading Process ID.
#define QBP_PRC_TYPE_LOADRAND  9  //Loading Process ID.
#define QBP_PRC_TYPE_LOADFULL  10 //Loading Process ID.
#define QBP_PRC_TYPE_SCHAUTOMA 11 //Music Search Process ID.

#define QBP_PRC_HDR_START  1 //Loading Process ID.
#define QBP_PRC_HDR_END    2 //Music Search Process ID.

#define QBP_STD_TYPE_IDLE  1 //No Process Running.
#define QBP_STD_TYPE_START 2 //The Process Started.
#define QBP_STD_TYPE_RUN   3 //The Process are Running.
#define QBP_STD_TYPE_END   4 //The Process Finished.

#define QBP_BUFFER_TYPE_CHR 0//String
#define QBP_BUFFER_TYPE_STR 1//Structure Buffer

#define QBP_POSTPROC_TYPE_F1 0//The First One Path encountered
#define QBP_POSTPROC_TYPE_B1 1//The Best One Path encountered
#define QBP_POSTPROC_TYPE_G1 2//The Greater One Path encountered
#define QBP_POSTPROC_TYPE_A1 3//ALL the Paths encountered

#define QBP_BUFFER_TYPE_FMAvgByType      0
#define QBP_BUFFER_TYPE_ETAvgByType      1
#define QBP_BUFFER_TYPE_ACAvgByPrecision 2
#define QBP_BUFFER_TYPE_FMAvgByPrecision 3
#define QBP_BUFFER_TYPE_PCAvgByPrecision 4
#define QBP_BUFFER_TYPE_MRAvgByPrecision 5
#define QBP_BUFFER_TYPE_ACAvgByResultSz  6
#define QBP_BUFFER_TYPE_FMAvgByResultSz  7
#define QBP_BUFFER_TYPE_PCAvgByResultSz  8
#define QBP_BUFFER_TYPE_MRAvgByResultSz  9
#define QBP_BUFFER_TYPE_MRAvgByBufferSz  10
#define QBP_BUFFER_TYPE_PCAvgByBufferSz  11
#define QBP_BUFFER_TYPE_CDAvgByBufferSz  12

//Musical Buffer for the Mu6 Algorithm
struct  stQBPMusicBuffer
{
    string    sQBP_Note            ;//Name of the Note
    bool      bQBP_IsBemol         ;
    bool      bQBP_IsSharp         ;
    int       iQBP_Octave          ;//Octave on the Keyboard
    int       iQBP_Pitch           ;//Numeric Pitch Note
    int       iQBP_Contour         ;//Melodic Contour of the Note(Difference in semitones from previous one)
    double    dQBP_Duration        ;//Duration of the Note
    double    dQBP_Frequency       ;//Frequency of the Note
    int       iQBP_MidiShortMessage;//Midi Short Message For Play
};

//Auxiliary Buffer to emulate the limitation of strings related to Scale
struct  stQBPStringBuffer
{
    string    sQBP_Note            ;//Name of the Note
    int       iQBP_Octave          ;//Octave on the Keyboard
};

#endif
