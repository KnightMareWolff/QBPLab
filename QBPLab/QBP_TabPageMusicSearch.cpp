#include "QBP_TabPageMusicSearch.h"
using namespace QtConcurrent;
CQBPEngine * CQBPTabPageMusicSearch::pQBPEngine=nullptr;
QString      CQBPTabPageMusicSearch::pQBPSingleSearchName;
QString      CQBPTabPageMusicSearch::pQBPSongAName;
QString      CQBPTabPageMusicSearch::pQBPSongBName;
QString      CQBPTabPageMusicSearch::pQBPSearchName;
int          CQBPTabPageMusicSearch::pQBPListType=QBP_LOAD_TARGET_TESTSET;
int          CQBPTabPageMusicSearch::pQBPComparatorType=QBP_MATRIX_TYPE_ORIGIN;
bool         CQBPTabPageMusicSearch::pQBPUseAttitude=false;
bool         CQBPTabPageMusicSearch::pQBPUseDebbug=false;

void QBPSingleSearch()
{
    CQBPTabPageMusicSearch::pQBPEngine->Search(CQBPTabPageMusicSearch::pQBPSearchName.toStdString(),
                                               CQBPTabPageMusicSearch::pQBPSongAName.toStdString(),
                                               CQBPTabPageMusicSearch::pQBPSongBName.toStdString(),
                                               CQBPTabPageMusicSearch::pQBPListType                      ,
                                               CQBPTabPageMusicSearch::pQBPComparatorType                ,
                                               CQBPTabPageMusicSearch::pQBPUseAttitude                  );
}

void QBPAutomaticSearch()
{
    CQBPTabPageMusicSearch::pQBPEngine->Search(CQBPTabPageMusicSearch::pQBPSearchName.toStdString(),
                                               CQBPTabPageMusicSearch::pQBPSingleSearchName.toStdString(),
                                               CQBPTabPageMusicSearch::pQBPListType                      ,
                                               CQBPTabPageMusicSearch::pQBPComparatorType                ,
                                               CQBPTabPageMusicSearch::pQBPUseAttitude                  );
}

CQBPTabPageMusicSearch::CQBPTabPageMusicSearch(QWidget *parent) : QWidget(parent)
{
    //Grupo de Criação
    QGroupBox *GrupoParametrosBusca = new QGroupBox(tr("Search Dimensions:"));
    //QGroupBox *GrupoSelectionTarget = new QGroupBox(tr("Selection Target:"));
    QGroupBox *GrupoPrincipal = new QGroupBox(tr("TESTE"));

    RadioTestSet        = new QRadioButton(tr("Test Set"));
    RadioValidationSet  = new QRadioButton(tr("Validation Set"));
    RadioRandomSet      = new QRadioButton(tr("Random Set"));
    RadioFullSet        = new QRadioButton(tr("Full Set"));
    CheckDebbugMode     = new QCheckBox(tr("Debbug Mode"));
    RadioSWMatrix       = new QRadioButton(tr("SW Matrix"));
    RadioMussum         = new QRadioButton(tr("Mussum Matrix"));
    RadioMussix         = new QRadioButton(tr("Mussix Matrix"));
    RadioAttitude       = new QRadioButton(tr("Attitude-Gram"));
    RadioPostQueueProc      = new QRadioButton(tr("Single-Queue"));
    RadioPostMultiQueueProc = new QRadioButton(tr("Multi-Queue"));
    RadioSelectTargetSelection= new QRadioButton(tr("Selection"));
    RadioSelectTargetSongA    = new QRadioButton(tr("Song A"));
    RadioSelectTargetSongB    = new QRadioButton(tr("Song B"));
    SearchSong                = new QComboBox;


    //Configura Grupo Precisão
    QGroupBox *GrupoPrecisao = new QGroupBox(tr("Precision Balance"));
    QGroupBox *GrupoBuffer   = new QGroupBox(tr("Buffer Size"));
    QGroupBox *GrupoResult   = new QGroupBox(tr("Result Size Balance"));
    QGroupBox *GrupoFilter   = new QGroupBox(tr("Filtering Type"));

    QHBoxLayout *LayoutPrecisao = new QHBoxLayout;
    LabelPrecision      = new QLabel(tr("50%"));
    pQBPPrecisionSlider = new QSlider(Qt::Horizontal,this);
    pQBPPrecisionSlider->setTickPosition(QSlider::TicksAbove);
    pQBPPrecisionSlider->setMinimum(0);
    pQBPPrecisionSlider->setMaximum(100);
    pQBPPrecisionSlider->setValue(50);

    QHBoxLayout *LayoutResultSize = new QHBoxLayout;
    LabelResultSize = new QLabel(tr("20"));
    pQBPResultSizeSlider = new QSlider(Qt::Horizontal,this);
    pQBPResultSizeSlider->setTickPosition(QSlider::TicksAbove);
    pQBPResultSizeSlider->setMinimum(20);
    pQBPResultSizeSlider->setMaximum(100);
    pQBPResultSizeSlider->setValue(20);

    QHBoxLayout *LayoutBufferSize = new QHBoxLayout;
    LabelBufferSize = new QLabel(tr("10"));
    pQBPBufferSizeSlider = new QSlider(Qt::Horizontal,this);
    pQBPBufferSizeSlider->setTickPosition(QSlider::TicksAbove);
    pQBPBufferSizeSlider->setMinimum(1);
    pQBPBufferSizeSlider->setMaximum(100);
    pQBPBufferSizeSlider->setValue(10);

    LayoutPrecisao->addWidget(pQBPPrecisionSlider);
    LayoutPrecisao->addWidget(LabelPrecision);

    LayoutResultSize->addWidget(pQBPResultSizeSlider);
    LayoutResultSize->addWidget(LabelResultSize);

    LayoutBufferSize->addWidget(pQBPBufferSizeSlider);
    LayoutBufferSize->addWidget(LabelBufferSize);

    GrupoPrecisao->setLayout(LayoutPrecisao);
    GrupoBuffer->setLayout(LayoutBufferSize);
    GrupoResult->setLayout(LayoutResultSize);


    RadioTestSet->setChecked(true);
    RadioSWMatrix->setChecked(true);
    CheckDebbugMode->setChecked(false);
    RadioSelectTargetSelection->setChecked(true);
    RadioPostQueueProc->setChecked(true);

    LabelTreeItemName   = new QLabel(tr("Selected Item:"));
    EditTreeItemValue   = new QLineEdit("");

    LabelTreeItemSongAName= new QLabel(tr("Song A:"));
    EditTreeItemSongAValue= new QLineEdit("");
    LabelTreeItemSongBName= new QLabel(tr("Song B:"));
    EditTreeItemSongBValue= new QLineEdit("");

    LabelSearchName       = new QLabel(tr("Search Name:"));;
    EditSearchNameValue   = new QLineEdit("");

    QPushButton *CarregaDataset   = new QPushButton(tr("Load SongSet"));
    QPushButton *Search           = new QPushButton(tr("QBP Compare"));
    QPushButton *AutoSearch       = new QPushButton(tr("QBP Search"));

    QHBoxLayout *LayoutOptLista = new QHBoxLayout;
    LayoutOptLista->addWidget(RadioTestSet);
    LayoutOptLista->addWidget(RadioValidationSet);
    LayoutOptLista->addWidget(RadioRandomSet);
    LayoutOptLista->addWidget(RadioFullSet);
    LayoutOptLista->addWidget(CheckDebbugMode);
    LayoutOptLista->addWidget(CarregaDataset);

    QHBoxLayout *LayoutOptFilter = new QHBoxLayout;
    LayoutOptFilter->addWidget(RadioPostQueueProc);
    LayoutOptFilter->addWidget(RadioPostMultiQueueProc);

    GrupoFilter->setLayout(LayoutOptFilter);

    //QHBoxLayout *LayoutSelectionTarget = new QHBoxLayout;
    //LayoutSelectionTarget->addWidget(RadioSelectTargetSelection);
    //LayoutSelectionTarget->addWidget(RadioSelectTargetSongA);
    //LayoutSelectionTarget->addWidget(RadioSelectTargetSongB);
    //GrupoSelectionTarget->setLayout(LayoutSelectionTarget);

    QVBoxLayout *LayoutStatus = new QVBoxLayout;

    //LayoutStatus->addWidget(GrupoSelectionTarget);

    //Search Name
    QHBoxLayout *LayoutHSearchName = new QHBoxLayout;
    LayoutHSearchName->addWidget(LabelSearchName);
    LayoutHSearchName->addWidget(EditSearchNameValue);
    LayoutStatus->addLayout(LayoutHSearchName);

    //Song Selection
    QHBoxLayout *LayoutHStatusItemName = new QHBoxLayout;
    LayoutHStatusItemName->addWidget(LabelTreeItemName);
    LayoutHStatusItemName->addWidget(EditTreeItemValue);
    LayoutStatus->addLayout(LayoutHStatusItemName);

    //Song Names A & B
    QHBoxLayout *LayoutHStatusSongAName = new QHBoxLayout;
    LayoutHStatusSongAName->addWidget(LabelTreeItemSongAName);
    LayoutHStatusSongAName->addWidget(EditTreeItemSongAValue);
    //LayoutStatus->addLayout(LayoutHStatusSongAName);

    QHBoxLayout *LayoutHStatusSongBName = new QHBoxLayout;
    LayoutHStatusSongBName->addWidget(LabelTreeItemSongBName);
    LayoutHStatusSongBName->addWidget(EditTreeItemSongBValue);
    //LayoutStatus->addLayout(LayoutHStatusSongBName);

    QHBoxLayout *LayoutBtnBusca = new QHBoxLayout;
    //LayoutBtnBusca->addWidget(Search);
    LayoutBtnBusca->addWidget(AutoSearch);

    LayoutStatus->addLayout(LayoutBtnBusca);

    QVBoxLayout *LayoutGrupoBusca = new QVBoxLayout;
    LayoutGrupoBusca->addLayout(LayoutOptLista);

    GrupoParametrosBusca->setLayout(LayoutGrupoBusca);

    QHBoxLayout *LayoutOptMatrix = new QHBoxLayout;
    LayoutOptMatrix->addWidget(RadioSWMatrix);
    LayoutOptMatrix->addWidget(RadioMussum);
    LayoutOptMatrix->addWidget(RadioMussix);
    LayoutOptMatrix->addWidget(RadioAttitude);

    QGroupBox *GrupoParametrosMTX   = new QGroupBox(tr("Substitution Matrix Options:"));
    GrupoParametrosMTX->setLayout(LayoutOptMatrix);

    //Inclui os Grupos no Layout Principal
    QVBoxLayout *LayoutPrincipal = new QVBoxLayout;
    LayoutPrincipal->addWidget(GrupoParametrosBusca);
    LayoutPrincipal->addWidget(GrupoParametrosMTX);
    LayoutPrincipal->addWidget(GrupoFilter);
    LayoutPrincipal->addWidget(GrupoBuffer);
    LayoutPrincipal->addWidget(GrupoPrecisao);
    LayoutPrincipal->addWidget(GrupoResult);
    LayoutPrincipal->addWidget(SearchSong);
    LayoutPrincipal->addLayout(LayoutStatus);
    LayoutPrincipal->addStretch(1);

    GrupoPrincipal->setLayout(LayoutPrincipal);

    setLayout(LayoutPrincipal);

    connect(CarregaDataset , SIGNAL(clicked()), this, SLOT(OnBtnCarregaDataset()));
    connect(Search         , SIGNAL(clicked()), this, SLOT(OnBtnSearch()));
    connect(AutoSearch     , SIGNAL(clicked()), this, SLOT(OnBtnAutoSearch()));

    connect(pQBPPrecisionSlider, SIGNAL(valueChanged(int)), this, SLOT(OnSliderSel       (int)));
    connect(pQBPResultSizeSlider, SIGNAL(valueChanged(int)), this, SLOT(OnSliderResultSel(int)));
    connect(pQBPBufferSizeSlider, SIGNAL(valueChanged(int)), this, SLOT(OnSliderBufferSel(int)));


    connect(RadioTestSet      , SIGNAL(toggled (bool)), this, SLOT(OnRadioTestToggle       (bool)));
    connect(RadioValidationSet, SIGNAL(toggled (bool)), this, SLOT(OnRadioValidationToggle (bool)));
    connect(RadioFullSet, SIGNAL(toggled (bool)), this, SLOT(OnRadioFullToggle (bool)));
    connect(RadioRandomSet, SIGNAL(toggled (bool)), this, SLOT(OnRadioRandomToggle (bool)));
    connect(RadioPostQueueProc, SIGNAL(toggled (bool)), this, SLOT(OnRadioQueueToggle       (bool)));
    connect(RadioPostMultiQueueProc, SIGNAL(toggled (bool)), this, SLOT(OnRadioMultiQueueToggle (bool)));
    connect(CheckDebbugMode   , SIGNAL(stateChanged(int)), this, SLOT(OnCheckDebbugMode(int)));
    connect(SearchSong        , SIGNAL(activated(int)), this, SLOT(OnBoxMusicSel           (int )));

    pQBPLoopStatus = QBP_STD_TYPE_IDLE;
    pQBPProcess=QBP_PRC_TYPE_NONE;

}

void CQBPTabPageMusicSearch::OnBtnCarregaDataset()
{
   if(RadioTestSet->isChecked())
   {
       pQBPProcess=QBP_PRC_TYPE_LOADTEST;
       pQBPListType=QBP_LOAD_TARGET_TESTSET;
       pQBPEngine->BuildTestSet(QBP_FORM_TYPE_LESS_1015F);
       //Preenche o Set de Busca(Limpa o anterior se necessário)
       pQBPEngine->FillTestSet(pQBPListType);
   }

   if(RadioValidationSet->isChecked())
   {
      pQBPProcess=QBP_PRC_TYPE_LOADVALI;
      pQBPListType=QBP_LOAD_TARGET_VALISET;
      pQBPEngine->BuildValiSet(QBP_FORM_TYPE_LESS_1015F);
      //Preenche o Set de Busca(Limpa o anterior se necessário)
      pQBPEngine->FillTestSet(pQBPListType);
   }

   if(RadioFullSet->isChecked())
   {
      pQBPProcess=QBP_PRC_TYPE_LOADFULL;
      pQBPListType=QBP_LOAD_TARGET_FULLSET;
      pQBPEngine->BuildFullSet();
      //Preenche o Set de Busca(Limpa o anterior se necessário)
      pQBPEngine->FillTestSet(pQBPListType);
   }


   if(RadioRandomSet->isChecked())
   {
       pQBPProcess=QBP_PRC_TYPE_LOADRAND;
       pQBPListType=QBP_LOAD_TARGET_RANDSET;
       pQBPEngine->BuildRandomSet(QBP_FORM_TYPE_LESS_1015F);
       //Preenche o Set de Busca(Limpa o anterior se necessário)
       pQBPEngine->FillTestSet(pQBPListType);
   }

   FillMusicCombo();
}

void CQBPTabPageMusicSearch::OnBtnSearch()
{
    //apenas para garantir uso apenas quando solicitado
    pQBPUseAttitude=false;

    if(RadioSWMatrix->isChecked())
    {
        pQBPComparatorType=QBP_MATRIX_TYPE_ORIGIN;
    }
    if(RadioMussum->isChecked())
    {
        pQBPComparatorType=QBP_MATRIX_TYPE_MUSSUM;
    }
    if(RadioMussix->isChecked())
    {
        pQBPComparatorType=QBP_MATRIX_TYPE_MUSSIX;
    }
    if(RadioAttitude->isChecked())
    {
        pQBPComparatorType=QBP_MATRIX_TYPE_MUSSAT;
        pQBPUseAttitude=true;
    }

    pQBPProcess=QBP_PRC_TYPE_SCHSINGLE;
    pQBPSearchName = EditSearchNameValue->text();
    pQBPSongAName  = EditTreeItemSongAValue->text();
    pQBPSongBName  = EditTreeItemSongBValue->text();

    //QBPSingleSearch();
    qQBPSearchThread     = QtConcurrent::run(QBPSingleSearch);

    //Connect the Status Loop
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(Statusloop()));
    timer->start(0);
}

void CQBPTabPageMusicSearch::OnBtnAutoSearch()
{

    //apenas para garantir uso apenas quando solicitado
    pQBPUseAttitude=false;

    if(RadioSWMatrix->isChecked())
    {
        pQBPComparatorType=QBP_MATRIX_TYPE_ORIGIN;
    }
    if(RadioMussum->isChecked())
    {
        pQBPComparatorType=QBP_MATRIX_TYPE_MUSSUM;
    }
    if(RadioMussix->isChecked())
    {
        pQBPComparatorType=QBP_MATRIX_TYPE_MUSSIX;
    }
    if(RadioAttitude->isChecked())
    {
        pQBPComparatorType=QBP_MATRIX_TYPE_MUSSAT;
        pQBPUseAttitude=true;
    }

    pQBPProcess=QBP_PRC_TYPE_SCHAUTOMA;
    pQBPSearchName = EditSearchNameValue->text();
    pQBPSingleSearchName = EditTreeItemValue->text();

    //QBPAutomaticSearch();
    qQBPSearchThread     = QtConcurrent::run(QBPAutomaticSearch);

}

void CQBPTabPageMusicSearch::OnSliderSel(int selection)
{
   pQBPEngine->SetPrecision(selection);
   LabelPrecision->setText(QString("%1 %").arg(selection));
}

void CQBPTabPageMusicSearch::OnSliderResultSel(int selection)
{
   pQBPEngine->SetResultSize(selection);
   LabelResultSize->setText(QString("%1").arg(selection));
}

void CQBPTabPageMusicSearch::OnSliderBufferSel(int selection)
{
   pQBPEngine->SetBufferSize(selection);
   LabelBufferSize->setText(QString("%1").arg(selection));
}

void CQBPTabPageMusicSearch::OnRadioTestToggle(bool checked)
{
   if(checked)
   {
       pQBPListType = QBP_LOAD_TARGET_TESTSET;
   }
}

void CQBPTabPageMusicSearch::OnRadioValidationToggle(bool checked)
{
    if(checked)
    {
        pQBPListType = QBP_LOAD_TARGET_VALISET;
    }
}

void CQBPTabPageMusicSearch::OnRadioFullToggle(bool checked)
{
    if(checked)
    {
        pQBPListType = QBP_LOAD_TARGET_DATASET;
    }
}

void CQBPTabPageMusicSearch::OnRadioRandomToggle(bool checked)
{
    if(checked)
    {
        pQBPListType = QBP_LOAD_TARGET_RANDSET;
    }
}

void CQBPTabPageMusicSearch::OnRadioQueueToggle(bool checked)
{
   if(checked)
   {
       pQBPEngine->SetPosProc(QBP_SCH_PPROC_QUEUE);
   }
}

void CQBPTabPageMusicSearch::OnRadioMultiQueueToggle(bool checked)
{
    if(checked)
    {
        pQBPEngine->SetPosProc(QBP_SCH_PPROC_MULTIQUEUE);
    }
}

void CQBPTabPageMusicSearch::OnCheckDebbugMode(int state)
{
    if(state == Qt::Unchecked)pQBPEngine->SetDebbugMode(false);
    if(state == Qt::Checked  )pQBPEngine->SetDebbugMode(true);
}

void CQBPTabPageMusicSearch::setEngineReference(CQBPEngine *pQBP_Engine)
{
    pQBPEngine = pQBP_Engine;
}

void CQBPTabPageMusicSearch::Kill()
{
    qQBPSearchThread.cancel();
}

void CQBPTabPageMusicSearch::OnBoxMusicSel(int selection)
{
    QString tName;
    int     tQtdNotes;
    int     tSearchScore;
    int     tSearchClassification;
    QString tClassificationDescription;

    pQBPEngine->GetTestData(selection,tName,tQtdNotes,tSearchScore,tSearchClassification);

    if(RadioSelectTargetSelection->isChecked())
    {
       EditTreeItemValue->setText(tName);
    }
    if(RadioSelectTargetSongA->isChecked())
    {
       EditTreeItemSongAValue->setText(tName);
    }
    if(RadioSelectTargetSongB->isChecked())
    {
       EditTreeItemSongBValue->setText(tName);
    }

}

bool CQBPTabPageMusicSearch::FillMusicCombo()
{
    int tQtdSongs=0;

    SearchSong->clear();

    tQtdSongs=pQBPEngine->TestGetSize();

    if(tQtdSongs>0)
    {
       for(int i=0;i<tQtdSongs;i++)
       {
           QString tName;
           int     tQtdNotes;
           int     tSearchScore;
           int     tSearchClassification;
           QString tClassificationDescription;

           pQBPEngine->GetTestData(i,tName,tQtdNotes,tSearchScore,tSearchClassification);

           switch(tSearchClassification)
           {
           case QBP_SCH_CLASS_TP:{tClassificationDescription = "TP - True  Positive";}break;
           case QBP_SCH_CLASS_FP:{tClassificationDescription = "FP - False Positive";}break;
           case QBP_SCH_CLASS_TN:{tClassificationDescription = "TN - True  Negative";}break;
           case QBP_SCH_CLASS_FN:{tClassificationDescription = "FN - False Negative";}break;
           }

           SearchSong->addItem(QString("Music %1 - ").arg(i) + QString(tName),i);
       }
    }
    return true;
}
