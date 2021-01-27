#ifndef QBP_TABPAGEMUSICSEARCH_H
#define QBP_TABPAGEMUSICSEARCH_H

#include "QBP_GlobalDef.h"
#include "QBP_Engine.h"

class CQBPTabPageMusicSearch : public QWidget
{
    Q_OBJECT
public:
    explicit CQBPTabPageMusicSearch(QWidget *parent = nullptr);
    void setEngineReference(CQBPEngine *pQBP_Engine);
    void Kill();

    //Engine Members
    static CQBPEngine *pQBPEngine;
    static QString     pQBPSingleSearchName;
    static QString     pQBPSongAName;
    static QString     pQBPSongBName;
    static QString     pQBPSearchName;
    static int         pQBPListType;
    static int         pQBPComparatorType;
    static bool        pQBPUseAttitude;
    static bool        pQBPUseDebbug;

    bool FillMusicCombo();

signals:

public slots:
    void OnBtnCarregaDataset();
    void OnBtnSearch();
    void OnBtnAutoSearch();
    void OnSliderSel(int selection);
    void OnSliderResultSel(int selection);
    void OnSliderBufferSel(int selection);
    void OnRadioTestToggle(bool check);
    void OnRadioValidationToggle(bool check);
    void OnRadioRandomToggle(bool check);
    void OnRadioFullToggle(bool check);
    void OnRadioQueueToggle(bool check);
    void OnRadioMultiQueueToggle(bool check);
    void OnCheckDebbugMode(int state);
    void OnBoxMusicSel (int selection);
private:
    QRadioButton *RadioTestSet;
    QRadioButton *RadioValidationSet;
    QRadioButton *RadioRandomSet;
    QRadioButton *RadioFullSet;
    QCheckBox    *CheckDebbugMode;
    QRadioButton *RadioSWMatrix;
    QRadioButton *RadioMussum;
    QRadioButton *RadioMussix;
    QRadioButton *RadioAttitude;
    QRadioButton *RadioSelectTargetSelection;
    QRadioButton *RadioSelectTargetSongA;
    QRadioButton *RadioSelectTargetSongB;
    QLabel       *LabelTreeItemName;
    QLineEdit    *EditTreeItemValue;
    QLabel       *LabelTreeItemSongAName;
    QLineEdit    *EditTreeItemSongAValue;
    QLabel       *LabelTreeItemSongBName;
    QLineEdit    *EditTreeItemSongBValue;
    QLabel       *LabelSearchName;
    QLineEdit    *EditSearchNameValue;
    QFuture<void> qQBPSearchThread;
    QSlider      *pQBPPrecisionSlider;
    QLabel       *LabelPrecision;
    QSlider      *pQBPResultSizeSlider;
    QLabel       *LabelResultSize;
    QSlider      *pQBPBufferSizeSlider;
    QLabel       *LabelBufferSize;
    QComboBox    *SearchSong;
    QRadioButton *RadioPostQueueProc;
    QRadioButton *RadioPostMultiQueueProc;

    //Calculo do Timer de Eventos
    QTimer        *timer;

    //Para calculos de tempo de Processo
    time_t          pQBPActualTime;
    struct tm      *pQBPStartSTime;
    struct tm      *pQBPFinishTime;

    int pQBPLoopStatus;
    int pQBPProcess;

};

#endif // QBP_TABPAGEMUSICSEARCH_H
