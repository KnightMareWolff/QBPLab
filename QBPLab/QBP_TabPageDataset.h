#ifndef QBP_TABPAGEDATASET_H
#define QBP_TABPAGEDATASET_H

#include "QBP_GlobalDef.h"
#include "QBP_Engine.h"
#include "QBP_LogQueue.h"

class CQBPTabPageDataset : public QWidget
{
    Q_OBJECT
public:
    CQBPTabPageDataset(QWidget *parent = nullptr);
    void setEngineReference(CQBPEngine *pQBP_Engine);
    void UpdateStatusBar();
    void Kill();

    //Engine Members
    static CQBPEngine *pQBPEngine;
    static QString     pQBPGenreDatasetName;
    static QString     pQBPChordsDatasetName;
    static QString     pQBPFullDatasetName;
    static QString     pQBPDatasetPath;

    bool FillMusicTree();
    bool FillChordTree();

    QTreeWidgetItem * addTreeRoot (QString name, QString description, QString type);
    void              addChordRoot(QString name, QString note01, QString note02, QString note03, QString note04, QString note05, QString note06);

    QTreeWidgetItem * addRootChild     (QTreeWidgetItem *parent,QString name, QString description, QString type);

    void              addTreeChild(QTreeWidgetItem *parent,QString name, QString description, QString type);

public slots:
    void OnBtnCarregaDataset();
    void OnBtnLimpaDataset();
    void OnBtnDatasetFile();
    void OnBtnGenreFile();
    void OnTreeSelection();
    void Statusloop();

private:
    QRadioButton *RadioFullData;
    QRadioButton *RadioBuildDatasets;
    QLabel       *LabelDatasetPath;
    QLineEdit    *EditDatasetPath;
    QLabel       *LabelGenrePath;
    QLineEdit    *EditGenrePath;
    QLabel       *LabelChordPath;
    QLineEdit    *EditChordPath;
    QLabel       *LabelProgress;
    QProgressBar *LoadProgress;
    QTreeWidget  *SongTree;
    QTreeWidget  *ChordsTree;
    QCheckBox    *StretchStrips;
    QLineEdit    *StretchStripsValue;

    QFuture<void> qQBPDatasetThread;

    //Calculo do Timer de Eventos
    QTimer        *timer;

    //Para calculos de tempo de Processo
    time_t          pQBPActualTime;
    struct tm      *pQBPStartSTime;
    struct tm      *pQBPFinishTime;

    int pQBPLoopStatus;

};

#endif // QBP_TABPAGEDATASET_H
