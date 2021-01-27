#include "QBP_TabPageDataset.h"

using namespace QtConcurrent;
CQBPEngine * CQBPTabPageDataset::pQBPEngine=nullptr;
QString      CQBPTabPageDataset::pQBPGenreDatasetName;
QString      CQBPTabPageDataset::pQBPChordsDatasetName;
QString      CQBPTabPageDataset::pQBPFullDatasetName;
QString      CQBPTabPageDataset::pQBPDatasetPath;

void CarregaBaseFull()
{
   CQBPTabPageDataset::pQBPEngine->LoadDataset(CQBPTabPageDataset::pQBPFullDatasetName.toStdString(),QBP_LOAD_TYPE_FULL,QBP_LOAD_TARGET_DATASET,false);
}

void CarregaBaseGenre()
{
   CQBPTabPageDataset::pQBPEngine->LoadDataset(CQBPTabPageDataset::pQBPGenreDatasetName.toStdString(),QBP_LOAD_TYPE_GENRE,QBP_LOAD_TARGET_DATASET,false);
}

void CarregaBaseChords()
{
   CQBPTabPageDataset::pQBPEngine->LoadChords(CQBPTabPageDataset::pQBPChordsDatasetName.toStdString());
}

void BuildDatasets()
{
   CQBPTabPageDataset::pQBPEngine->LoadDataset(CQBPTabPageDataset::pQBPDatasetPath.toStdString(),QBP_LOAD_TYPE_BUILD,QBP_LOAD_TARGET_DATASET,false);
}

void ClearDatasets()
{
   CQBPTabPageDataset::pQBPEngine->ClearEngine();
}

CQBPTabPageDataset::CQBPTabPageDataset(QWidget *parent) : QWidget(parent)
{
    //Grupo de Criação
    QGroupBox *GrupoParametrosCarga = new QGroupBox(tr("Pre-Processing Options:"));

    LabelProgress       = new QLabel(tr("Loading Progress:"));
    LoadProgress        = new QProgressBar();
    RadioFullData       = new QRadioButton(tr("Load Dataset"));
    RadioBuildDatasets  = new QRadioButton(tr("Build Dataset"));
    StretchStrips       = new QCheckBox(tr("Stretch Notes?"));
    StretchStripsValue  = new QLineEdit("31");

    //Seta valor maximo de musicas(Vai mudar qdo tiver outros datasets)
    LoadProgress->setMaximum(10198);
    LoadProgress->setMinimum(0);

    //Seta Carregamento de Dataset como padrão
    RadioFullData->setChecked(true);

    LabelDatasetPath    = new QLabel(tr("Dataset File Path:"));
    EditDatasetPath     = new QLineEdit("dataset/Dataset_Begin.txt");
    LabelGenrePath      = new QLabel(tr("Groups File Path:"));
    EditGenrePath       = new QLineEdit("dataset/Genres.txt");
    LabelChordPath      = new QLabel(tr("Chords File Path:"));
    EditChordPath       = new QLineEdit("chords/Chords.txt");

    QPushButton *CarregaDataset   = new QPushButton(tr("Load Dataset"));
    QPushButton *LimpaDataset     = new QPushButton(tr("Clear Dataset"));
    QPushButton *DatasetFile      = new QPushButton(tr("..."));
    QPushButton *GenreFile        = new QPushButton(tr("..."));
    QPushButton *ChordsFile       = new QPushButton(tr("..."));

    QHBoxLayout *LayoutOptCarga = new QHBoxLayout;
    LayoutOptCarga->addWidget(RadioFullData);
    LayoutOptCarga->addWidget(RadioBuildDatasets);
    LayoutOptCarga->addWidget(StretchStrips);
    LayoutOptCarga->addWidget(StretchStripsValue);

    QHBoxLayout *LayoutArqCarga = new QHBoxLayout;
    LayoutArqCarga->addWidget(LabelDatasetPath);
    LayoutArqCarga->addWidget(EditDatasetPath);
    LayoutArqCarga->addWidget(DatasetFile);

    QHBoxLayout *LayoutArqGenre = new QHBoxLayout;
    LayoutArqGenre->addWidget(LabelGenrePath);
    LayoutArqGenre->addWidget(EditGenrePath);
    LayoutArqGenre->addWidget(GenreFile);

    QHBoxLayout *LayoutArqChords = new QHBoxLayout;
    LayoutArqChords->addWidget(LabelChordPath);
    LayoutArqChords->addWidget(EditChordPath);
    LayoutArqChords->addWidget(ChordsFile);

    QHBoxLayout *LayoutBtnCarga   = new QHBoxLayout;
    LayoutBtnCarga->addWidget(CarregaDataset);
    LayoutBtnCarga->addWidget(LimpaDataset);

    //Constroi Arvore de Musicas
    SongTree = new QTreeWidget();
    QStringList HeaderLabels;

    HeaderLabels << "Musical Item" << "Type" << "Description" ;

    SongTree->clear();
    SongTree->setColumnCount(3);
    SongTree->setHeaderLabels(HeaderLabels);

    //Constroi Arvore de Acordes
    ChordsTree = new QTreeWidget();
    QStringList ChordsHeaderLabels;

    ChordsHeaderLabels << "Chord ID" << "Voice01"  << "Voice02"  << "Voice03"  << "Voice04"  << "Voice05" << "Voice06" ;

    ChordsTree->clear();
    ChordsTree->setColumnCount(7);
    ChordsTree->setHeaderLabels(ChordsHeaderLabels);

    QVBoxLayout *LayoutStatus = new QVBoxLayout;
    LayoutStatus->addWidget(LabelProgress);
    LayoutStatus->addWidget(LoadProgress);
    LayoutStatus->addWidget(SongTree);
    LayoutStatus->addWidget(ChordsTree);

    QVBoxLayout *LayoutGrupoCarga = new QVBoxLayout;
    LayoutGrupoCarga->addLayout(LayoutOptCarga);
    LayoutGrupoCarga->addLayout(LayoutArqCarga);
    LayoutGrupoCarga->addLayout(LayoutArqGenre);
    LayoutGrupoCarga->addLayout(LayoutArqChords);
    LayoutGrupoCarga->addLayout(LayoutBtnCarga);
    LayoutGrupoCarga->addLayout(LayoutStatus);

    GrupoParametrosCarga->setLayout(LayoutGrupoCarga);

    //Inclui os Grupos no Layout Principal
    QVBoxLayout *LayoutPrincipal = new QVBoxLayout;
    LayoutPrincipal->addWidget(GrupoParametrosCarga);

    //LayoutPrincipal->addStretch(1);
    setLayout(LayoutPrincipal);

    connect(CarregaDataset , SIGNAL(clicked()), this, SLOT(OnBtnCarregaDataset()));
    connect(LimpaDataset , SIGNAL(clicked()), this, SLOT(OnBtnLimpaDataset()));
    connect(DatasetFile    , SIGNAL(clicked()), this, SLOT(OnBtnDatasetFile()));
    connect(GenreFile      , SIGNAL(clicked()), this, SLOT(OnBtnGenreFile()));


    connect(SongTree       , SIGNAL(currentItemChanged(QTreeWidgetItem *, QTreeWidgetItem *)),
                                    this,
                                    SLOT(OnTreeSelection()));

    pQBPLoopStatus = QBP_STD_TYPE_IDLE;

}

void CQBPTabPageDataset::OnBtnCarregaDataset()
{  
    //Connect the Status Loop
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(Statusloop()));
    timer->start(0);

   //Habilita/Desabilita Stretch de Notas
   if(StretchStrips->isChecked())
   {
       pQBPEngine->pQBPDataset->bQBPStretchStrip=true;
       pQBPEngine->pQBPDataset->iQBPStretchValue=StretchStripsValue->text().toUInt();
   }
   else
   {
       pQBPEngine->pQBPDataset->bQBPStretchStrip=false;
   }

   if(RadioFullData->isChecked())
   {
      pQBPGenreDatasetName=EditGenrePath->text();
      qQBPDatasetThread = QtConcurrent::run(CarregaBaseGenre);
      while(qQBPDatasetThread.isRunning());

      pQBPChordsDatasetName=EditChordPath->text();
      qQBPDatasetThread = QtConcurrent::run(CarregaBaseChords);
      while(qQBPDatasetThread.isRunning());

      pQBPFullDatasetName=EditDatasetPath->text();
      qQBPDatasetThread  = QtConcurrent::run(CarregaBaseFull);
   }

   if(RadioBuildDatasets->isChecked())
   {
      pQBPDatasetPath= "dataset/";
      qQBPDatasetThread = QtConcurrent::run(BuildDatasets);
   }
}

void CQBPTabPageDataset::OnBtnLimpaDataset()
{
    //Connect the Status Loop
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(Statusloop()));
    timer->start(0);

   qQBPDatasetThread = QtConcurrent::run(ClearDatasets);
}

void CQBPTabPageDataset::OnBtnDatasetFile()
{

    QString fileName = QFileDialog::getOpenFileName(this);
    if (!fileName.isEmpty())
    {
       EditDatasetPath->setText(fileName);
    }
}

void CQBPTabPageDataset::OnBtnGenreFile()
{
    QString fileName = QFileDialog::getOpenFileName(this);
    if (!fileName.isEmpty())
    {
       EditGenrePath->setText(fileName);
    }
}

void CQBPTabPageDataset::OnTreeSelection()
{

}

void CQBPTabPageDataset::setEngineReference(CQBPEngine *pQBP_Engine)
{
    pQBPEngine = pQBP_Engine;
}

void CQBPTabPageDataset::Kill()
{
    qQBPDatasetThread.cancel();
}

void CQBPTabPageDataset::Statusloop()
{
    int tDimension;
    int tCompleted;

    if(qQBPDatasetThread.isStarted() && pQBPLoopStatus == QBP_STD_TYPE_IDLE)
    {
        pQBPEngine->GetSearchData(tDimension,tCompleted);
        LoadProgress->setMaximum(tDimension);
        LoadProgress->setMinimum(0);

        pQBPActualTime = time(0);
        pQBPStartSTime = localtime(&pQBPActualTime);

        CQBPLogQueue::Push(QString("*****************************************\n"));
        CQBPLogQueue::Push(QString("*  PROCESSO CARGA INICIADO              *\n"));
        CQBPLogQueue::Push(QString("*****************************************\n"));
        CQBPLogQueue::Push(QString("Tempo Inicial : %1:%2:%3 \n").arg(pQBPStartSTime->tm_hour).arg(pQBPStartSTime->tm_min ).arg(pQBPStartSTime->tm_sec));
        pQBPLoopStatus = QBP_STD_TYPE_START;
    }

    if(qQBPDatasetThread.isRunning() && pQBPLoopStatus == QBP_STD_TYPE_START)
    {
        pQBPEngine->GetSearchData(tDimension,tCompleted);
        //In the case of data loading we cannot estimate the number os registries, use the actual loading values
        if(RadioFullData->isChecked())LoadProgress->setValue(pQBPEngine->SongsLoaded());
    }

    if(qQBPDatasetThread.isFinished() && pQBPLoopStatus == QBP_STD_TYPE_START)
    {
        if(!disconnect(timer, SIGNAL(timeout()), this, SLOT(Statusloop())))
        {
            qWarning("Nao desconectou");
        }
        pQBPActualTime = time(0);
        pQBPFinishTime = localtime(&pQBPActualTime);
        CQBPLogQueue::Push(QString("Tempo Final : %1:%2:%3 \n").arg(pQBPFinishTime->tm_hour).arg(pQBPFinishTime->tm_min ).arg(pQBPFinishTime->tm_sec));
        CQBPLogQueue::Push(QString("*****************************************\n"));
        CQBPLogQueue::Push(QString("*                                       *\n"));
        CQBPLogQueue::Push(QString("*****************************************\n"));
        qQBPDatasetThread.cancel();
        pQBPLoopStatus = QBP_STD_TYPE_IDLE;
        FillMusicTree();
        FillChordTree();
    }
}

bool CQBPTabPageDataset::FillMusicTree()
{
    int tQtdGenres=0;

    QStringList HeaderLabels;

    HeaderLabels << "Item Musical" << "Conteúdo" << "Descrição" ;

    disconnect(SongTree     , SIGNAL(currentItemChanged(QTreeWidgetItem *, QTreeWidgetItem *)),
                                    this,
                                    SLOT(OnTreeSelection()));

    SongTree->clear();
    SongTree->setColumnCount(3);
    SongTree->setHeaderLabels(HeaderLabels);

    tQtdGenres=pQBPEngine->GenresLoaded();
    if(tQtdGenres>0)
    {
       for(int i=0;i<tQtdGenres;i++)
       {
           QString tName;
           int     tQtdSongs;

           pQBPEngine->GetGenreData(i,tName,tQtdSongs);

           QTreeWidgetItem *Genre = addTreeRoot(tName,QString("Musicas: %1").arg(tQtdSongs),QString("Categoria"));

           for(int j=0;j<tQtdSongs;j++)
           {
               QString tSongName;
               int     tQtdNotes;
               int     tQtdFeatures;
               int     tQtdCustomFeatures;

               pQBPEngine->GetSongData(i,j,tSongName,tQtdNotes,tQtdFeatures,tQtdCustomFeatures);

               QTreeWidgetItem *Music      = addRootChild(Genre,tSongName,QString("Notas : %1").arg(tQtdNotes),QString("Música"));


               QTreeWidgetItem *FeaturesJS = addRootChild(Music,"JSymbolic Features",QString("Features: %1").arg(tQtdFeatures),QString("Features"));
               for(int k=0;k<tQtdFeatures;k++)
               {
                   QString tFeatureName;
                   int     tFeatureId;
                   double  tFeatureValue;

                   pQBPEngine->GetFeatureData(i,j,k,tFeatureName,tFeatureId,tFeatureValue);

                   addTreeChild(FeaturesJS,tFeatureName,QString("%1").arg(tFeatureValue),QString("Data"));
               }

               QTreeWidgetItem *FeaturesCS = addRootChild(Music,"Custom Features",QString("Features: %1").arg(tQtdCustomFeatures),QString("Custom Features"));
               for(int k=0;k<tQtdCustomFeatures;k++)
               {
                   QString tFeatureName;
                   int     tFeatureId;
                   double  tFeatureValue;

                   pQBPEngine->GetCustomFeatureData(i,j,k,tFeatureName,tFeatureId,tFeatureValue);

                   addTreeChild(FeaturesCS,tFeatureName,QString("%1").arg(tFeatureValue),QString("Data"));
               }

           }
       }
    }

    connect(SongTree     , SIGNAL(currentItemChanged(QTreeWidgetItem *, QTreeWidgetItem *)),
                                    this,
                                    SLOT(OnTreeSelection()));
    return true;
}

bool CQBPTabPageDataset::FillChordTree()
{
    int tQtdChords=0;
    QTreeWidgetItem *ChordsRoot;

    //Constroi Arvore de Acordes
    QStringList ChordsHeaderLabels;

    ChordsHeaderLabels << "Chord ID" << "Voice01"  << "Voice02"  << "Voice03"  << "Voice04"  << "Voice05" << "Voice06" ;

    ChordsTree->clear();
    ChordsTree->setColumnCount(7);
    ChordsTree->setHeaderLabels(ChordsHeaderLabels);

    tQtdChords = pQBPEngine->ChordsLoaded();
    if(tQtdChords>0)
    {
       for(int i=0;i<tQtdChords;i++)
       {
           QString tChordName;
           int     tChordNote01;
           int     tChordNote02;
           int     tChordNote03;
           int     tChordNote04;
           int     tChordNote05;
           int     tChordNote06;


           pQBPEngine->GetChordData(i,tChordName,tChordNote01,tChordNote02,tChordNote03,tChordNote04,tChordNote05,tChordNote06);
           addChordRoot(tChordName,
                        QString("%1").arg(tChordNote01),
                        QString("%1").arg(tChordNote02),
                        QString("%1").arg(tChordNote03),
                        QString("%1").arg(tChordNote04),
                        QString("%1").arg(tChordNote05),
                        QString("%1").arg(tChordNote06));
       }
    }

    return true;
}

void CQBPTabPageDataset::addChordRoot(QString name, QString note01, QString note02, QString note03, QString note04, QString note05, QString note06)
{
    QTreeWidgetItem *treeItem = new QTreeWidgetItem(ChordsTree);

    treeItem->setText(0, name);
    treeItem->setText(1, note01);
    treeItem->setText(2, note02);
    treeItem->setText(3, note03);
    treeItem->setText(4, note04);
    treeItem->setText(5, note05);
    treeItem->setText(6, note06);
}

QTreeWidgetItem * CQBPTabPageDataset::addTreeRoot(QString name, QString description, QString type)
{
    QTreeWidgetItem *treeItem = new QTreeWidgetItem(SongTree);

    treeItem->setText(0, name);
    treeItem->setText(1, description);
    treeItem->setText(2, type);
    return treeItem;
}

QTreeWidgetItem * CQBPTabPageDataset::addRootChild(QTreeWidgetItem *parent,QString name, QString description, QString type)
{
    QTreeWidgetItem *treeItem = new QTreeWidgetItem(parent);

    treeItem->setText(0, name);
    treeItem->setText(1, description);
    treeItem->setText(2, type);
    return treeItem;
}

void CQBPTabPageDataset::addTreeChild(QTreeWidgetItem *parent,QString name, QString description, QString type)
{
    QTreeWidgetItem *treeItem = new QTreeWidgetItem();

    treeItem->setText(0, name);
    treeItem->setText(1, description);
    treeItem->setText(2, type);
    parent->addChild(treeItem);
}
