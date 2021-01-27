#include "QBP_TabPageSVM.h"
using namespace QtConcurrent;

CQBPEngine * CQBPTabPageSVM::pQBPEngine=nullptr;

CQBPTabPageSVM::CQBPTabPageSVM(QWidget *parent) : QWidget(parent)
{
    QGroupBox   *GrupoPrincipal     = new QGroupBox(tr("Machine Learning"));
    QGroupBox   *GrupoSVM           = new QGroupBox(tr("SVM"));
    QGroupBox   *GrupoSVMTrainSet   = new QGroupBox(tr("Train Set Type"));
    QGroupBox   *GrupoSVMModelParms = new QGroupBox(tr("Model Parameters"));
    QGroupBox   *GrupoSVMTrainParms = new QGroupBox(tr("Training Parameters"));
    QGroupBox   *GrupoPool          = new QGroupBox(tr("Classifier Pool"));
    QVBoxLayout *LayoutPrincipal    = new QVBoxLayout;

    SVMModelFileLabel    = new QLabel(tr("Model File:"));
    SVMModelFileEdit     = new QLineEdit("svm/qbpSVM.model");
    SVMModelFileButton   = new QPushButton(tr(" Load Model "));

    //Model Parameters
    SVMModelSVMTypeLabel      = new QLabel(tr("SVM Type:"));
    SVMModelSVMTypeEdit       = new QLineEdit("");
    SVMModelSVMTypeCombo      = new QComboBox();
    SVMModelSVMKernelTypeLabel= new QLabel(tr("Kernel Type:"));
    SVMModelSVMKernelTypeEdit = new QLineEdit("");
    SVMModelSVMKernelTypeCombo= new QComboBox();
    SVMModelSVMGammaLabel     = new QLabel(tr("Gamma:"));
    SVMModelSVMGammaEdit      = new QLineEdit(QString("%1").arg(0));
    SVMModelSVMDegreeLabel    = new QLabel(tr("Degree:"));
    SVMModelSVMDegreeEdit     = new QLineEdit(QString("%1").arg(3));
    SVMModelSVMCoef0Label     = new QLabel(tr("Coef0:"));
    SVMModelSVMCoef0Edit      = new QLineEdit(QString("%1").arg(0));

    SVMTrainFileLabel    = new QLabel(tr("Train File:"));
    SVMTrainFileEdit     = new QLineEdit("svm/qbpSVM.train");
    SVMTrainFileButton   = new QPushButton(tr(" Generate Train "));

    SVMTrainFileRadioTestSet  = new QRadioButton(tr("Test Set"));
    SVMTrainFileRadioValiSet  = new QRadioButton(tr("Validation Set"));
    SVMTrainFileRadioDataSet  = new QRadioButton(tr("Full Set"));
    SVMTrainFileCheckNorm     = new QCheckBox(tr("Normalize?"));
    SVMTrainSVMCategoryCheck  = new QCheckBox(tr("Use Category?"));


    //Train Parameters
    SVMTrainCacheSizeLabel  = new QLabel(tr("Cache Size:"));
    SVMTrainCacheSizeEdit   = new QLineEdit(QString("%1").arg(100));
    SVMTrainEPSLabel        = new QLabel(tr("EPS:"));
    SVMTrainEPSEdit         = new QLineEdit(QString("%1").arg(0.001));
    SVMTrainCLabel          = new QLabel(tr("C:"));
    SVMTrainCEdit           = new QLineEdit(QString("%1").arg(1));
    SVMTrainWeightLabel     = new QLabel(tr("Weight:"));
    SVMTrainWeightEdit      = new QLineEdit("");
    SVMTrainShrinkingLabel  = new QLabel(tr("Shrinking:"));
    SVMTrainShrinkingEdit   = new QLineEdit(QString("%1").arg(1));
    SVMTrainProbabilityLabel= new QLabel(tr("Probability:"));
    SVMTrainProbabilityEdit = new QLineEdit(QString("%1").arg(0));
    SVMTrainCrossValidFoldsLabel = new QLabel(tr("Cross-Validation Folds:"));
    SVMTrainCrossValidFoldsEdit  = new QLineEdit(QString("%1").arg(2));
    SVMTrainSVMCategoryLabel     = new QLabel(tr("Category:"));
    SVMTrainSVMCategoryCombo     = new QComboBox();
    SVMTrainSVMCategoryButton    = new QPushButton(tr(" Load Categories "));

    SVMPoolFileLabel    = new QLabel(tr("Pool File:"));
    SVMPoolFileEdit     = new QLineEdit("");
    SVMPoolFileButton   = new QPushButton(tr(" Save Pool "));
    SVMPoolBuildButton  = new QPushButton(tr(" Build Pool "));
    //Inicializa Lista de Resultados
    SVMPoolTree = new QTreeWidget();
    QStringList ResultLabels;

    ResultLabels << "Classifier" << "Category" << "Accuracy" << "Model File";

    SVMPoolTree->clear();
    SVMPoolTree->setColumnCount(4);
    SVMPoolTree->setHeaderLabels(ResultLabels);
    SVMPoolTree->setMaximumHeight(80);
    /****************************************/
    /*Inicializa as ComboBoxes              */
    /****************************************/

    SVMModelSVMTypeCombo->addItem(QString("C_SVC"),100);
    SVMModelSVMTypeCombo->addItem(QString("NU_SVC"),101);
    SVMModelSVMTypeCombo->addItem(QString("ONE_CLASS"),102);
    SVMModelSVMTypeCombo->addItem(QString("EPSILON_SVR"),103);
    SVMModelSVMTypeCombo->addItem(QString("NU_SVR"),104);

    SVMModelSVMKernelTypeCombo->addItem(QString("LINEAR"),0);
    SVMModelSVMKernelTypeCombo->addItem(QString("POLY"),1);
    SVMModelSVMKernelTypeCombo->addItem(QString("RBF"),2);
    SVMModelSVMKernelTypeCombo->addItem(QString("SIGMOID"),3);
    SVMModelSVMKernelTypeCombo->addItem(QString("CHI2"),4);
    SVMModelSVMKernelTypeCombo->addItem(QString("INTER"),5);
    SVMModelSVMKernelTypeCombo->setCurrentIndex(2);

    /******************************/
    /*Inicializa Radios e Checks  */
    /******************************/
    SVMTrainFileRadioDataSet->setChecked(true);
    SVMTrainFileCheckNorm->setChecked(true);
    SVMTrainSVMCategoryCheck->setChecked(true);
    /************************************************************/
    /*Grupo SVM                                                 */
    /************************************************************/
    //Layout Load Model (Linha 01)
    QHBoxLayout *LayoutLoadModel    = new QHBoxLayout;
    LayoutLoadModel->addWidget(SVMModelFileLabel);
    LayoutLoadModel->addWidget(SVMModelFileEdit);
    LayoutLoadModel->addWidget(SVMModelFileButton);
    //grupo de parametros do modelo(L1 , L2 e L3)
    QHBoxLayout *LayoutModelParmsL1    = new QHBoxLayout;
    LayoutModelParmsL1->addWidget(SVMModelSVMTypeLabel);
    LayoutModelParmsL1->addWidget(SVMModelSVMTypeCombo);
    LayoutModelParmsL1->addWidget(SVMModelSVMKernelTypeLabel);
    LayoutModelParmsL1->addWidget(SVMModelSVMKernelTypeCombo);
    QHBoxLayout *LayoutModelParmsL2    = new QHBoxLayout;
    LayoutModelParmsL2->addWidget(SVMModelSVMGammaLabel);
    LayoutModelParmsL2->addWidget(SVMModelSVMGammaEdit);
    LayoutModelParmsL2->addWidget(SVMTrainCLabel);
    LayoutModelParmsL2->addWidget(SVMTrainCEdit);
    //LayoutModelParmsL2->addWidget(SVMModelSVMDegreeLabel);
    //LayoutModelParmsL2->addWidget(SVMModelSVMDegreeEdit);
    QHBoxLayout *LayoutModelParmsL3    = new QHBoxLayout;
    //LayoutModelParmsL3->addWidget(SVMModelSVMCoef0Label);
    //LayoutModelParmsL3->addWidget(SVMModelSVMCoef0Edit);
    LayoutModelParmsL3->addWidget(SVMTrainCrossValidFoldsLabel);
    LayoutModelParmsL3->addWidget(SVMTrainCrossValidFoldsEdit);
    //Grupo Parametros SVM
    QVBoxLayout *LayoutModelParms    = new QVBoxLayout;
    LayoutModelParms->addLayout(LayoutModelParmsL1);
    LayoutModelParms->addLayout(LayoutModelParmsL2);
    LayoutModelParms->addLayout(LayoutModelParmsL3);
    GrupoSVMModelParms->setLayout(LayoutModelParms);

    //Layout Load Model (Linha 02)
    QHBoxLayout *LayoutTrainType    = new QHBoxLayout;
    LayoutTrainType->addWidget(SVMTrainFileRadioTestSet);
    LayoutTrainType->addWidget(SVMTrainFileRadioValiSet);
    LayoutTrainType->addWidget(SVMTrainFileRadioDataSet);
    LayoutTrainType->addWidget(SVMTrainFileCheckNorm);
    LayoutTrainType->addWidget(SVMTrainSVMCategoryCheck);
    GrupoSVMTrainSet->setLayout(LayoutTrainType);

    //grupo de parametros de treinamento(L1 , L2 e L3)
    QHBoxLayout *LayoutTrainParmsL1    = new QHBoxLayout;
    //LayoutTrainParmsL1->addWidget(SVMTrainSVMCategoryLabel);
    LayoutTrainParmsL1->addWidget(SVMTrainSVMCategoryCombo);
    LayoutTrainParmsL1->addWidget(SVMTrainSVMCategoryButton);
    //LayoutTrainParmsL1->addWidget(SVMTrainEPSEdit);
    //QHBoxLayout *LayoutTrainParmsL2    = new QHBoxLayout;
    //LayoutTrainParmsL2->addWidget(SVMTrainCLabel);
    //LayoutTrainParmsL2->addWidget(SVMTrainCEdit);
    //LayoutTrainParmsL2->addWidget(SVMTrainWeightLabel);
    //LayoutTrainParmsL2->addWidget(SVMTrainWeightEdit);
    //QHBoxLayout *LayoutTrainParmsL3    = new QHBoxLayout;
    //LayoutTrainParmsL3->addWidget(SVMTrainShrinkingLabel);
    //LayoutTrainParmsL3->addWidget(SVMTrainShrinkingEdit);
    //LayoutTrainParmsL3->addWidget(SVMTrainProbabilityLabel);
    //LayoutTrainParmsL3->addWidget(SVMTrainProbabilityEdit);

    //Grupo Parametros Train
    QVBoxLayout *LayoutTrainParms    = new QVBoxLayout;
    LayoutTrainParms->addLayout(LayoutTrainParmsL1);
    //LayoutTrainParms->addLayout(LayoutTrainParmsL2);
    //LayoutTrainParms->addLayout(LayoutTrainParmsL3);
    GrupoSVMTrainParms->setLayout(LayoutTrainParms);

    //Layout Load Model (Linha 03)
    QHBoxLayout *LayoutTrainFile    = new QHBoxLayout;
    LayoutTrainFile->addWidget(SVMTrainFileLabel);
    LayoutTrainFile->addWidget(SVMTrainFileEdit);
    LayoutTrainFile->addWidget(SVMTrainFileButton);

    //atribui os layouts ao grupo SVM
    QVBoxLayout *LayoutSVM    = new QVBoxLayout;
    LayoutSVM->addLayout(LayoutLoadModel);
    LayoutSVM->addWidget(GrupoSVMModelParms);
    LayoutSVM->addWidget(GrupoSVMTrainSet);
    LayoutSVM->addWidget(GrupoSVMTrainParms);
    LayoutSVM->addLayout(LayoutTrainFile);

    GrupoSVM->setLayout(LayoutSVM);
    /************************************************************/
    /*Grupo Classifier Pool                                     */
    /************************************************************/
    QHBoxLayout *LayoutPoolL1    = new QHBoxLayout;
    LayoutPoolL1->addWidget(SVMPoolFileLabel);
    LayoutPoolL1->addWidget(SVMPoolFileEdit);
    LayoutPoolL1->addWidget(SVMPoolFileButton);
    LayoutPoolL1->addWidget(SVMPoolBuildButton);

    QVBoxLayout *LayoutPool    = new QVBoxLayout;
    LayoutPool->addLayout(LayoutPoolL1);
    LayoutPool->addWidget(SVMPoolTree,1);
    LayoutPool->addStretch(1);

    GrupoPool->setLayout(LayoutPool);

    /****************************************************/
    /*Atribui a um Layout vertical cada grupo criado    */
    /****************************************************/
    QVBoxLayout *LayoutML    = new QVBoxLayout;
    LayoutML->addWidget(GrupoSVM);
    LayoutML->addWidget(GrupoPool);

    /************************************************/
    /*Atribui a tela principal todo o layout criado */
    /************************************************/
    GrupoPrincipal ->setLayout(LayoutML);
    LayoutPrincipal->addWidget(GrupoPrincipal);
    setLayout(LayoutPrincipal);
    /********************************/
    /*Slots de funcionamento do Qt  */
    /********************************/
    connect(SVMModelFileButton          , SIGNAL(clicked())        , this, SLOT(OnBtnModelFile()));
    connect(SVMTrainFileButton          , SIGNAL(clicked())        , this, SLOT(OnBtnTrainFile()));
    connect(SVMPoolBuildButton          , SIGNAL(clicked())        , this, SLOT(OnBtnBuildPool()));
    connect(SVMTrainSVMCategoryButton   , SIGNAL(clicked())        , this, SLOT(OnBtnLoadCategory()));
    connect(SVMModelSVMTypeCombo        , SIGNAL(activated(int))   , this, SLOT(OnBoxSVMSel(int )));
    connect(SVMModelSVMKernelTypeCombo  , SIGNAL(activated(int))   , this, SLOT(OnBoxKrlSel(int )));
    connect(SVMModelSVMGammaEdit        , SIGNAL(editingFinished()), this, SLOT(OnEdtGamma()));
    connect(SVMModelSVMDegreeEdit       , SIGNAL(editingFinished()), this, SLOT(OnEdtDegree()));
    connect(SVMModelSVMCoef0Edit        , SIGNAL(editingFinished()), this, SLOT(OnEdtCoef0()));
    connect(SVMTrainCacheSizeEdit       , SIGNAL(editingFinished()), this, SLOT(OnEdtCacheSize()));
    connect(SVMTrainEPSEdit             , SIGNAL(editingFinished()), this, SLOT(OnEdtEPS()));
    connect(SVMTrainCEdit               , SIGNAL(editingFinished()), this, SLOT(OnEdtC()));
    connect(SVMTrainWeightEdit          , SIGNAL(editingFinished()), this, SLOT(OnEdtWeight()));
    connect(SVMTrainShrinkingEdit       , SIGNAL(editingFinished()), this, SLOT(OnEdtShrinking()));
    connect(SVMTrainProbabilityEdit     , SIGNAL(editingFinished()), this, SLOT(OnEdtProbability()));
    connect(SVMTrainCrossValidFoldsEdit , SIGNAL(editingFinished()), this, SLOT(OnEdtFolds()));
}

void CQBPTabPageSVM::OnBtnModelFile()
{
   //pQBPEngine->LoadSVMModel(SVMModelFileEdit->text().toStdString());
   pQBPEngine->LoadPool();
}

void CQBPTabPageSVM::OnBtnBuildPool()
{
   pQBPEngine->CreateDefaultPool();
}

void CQBPTabPageSVM::OnBtnTrainFile()
{
    bool bNorm = SVMTrainFileCheckNorm->isChecked();
    bool bCat  = SVMTrainSVMCategoryCheck->isChecked();
    int  iCat  = SVMTrainSVMCategoryCombo->currentIndex();

    if(SVMTrainFileRadioTestSet->isChecked())
    {
        pQBPEngine->TrainSVM(SVMTrainFileEdit->text().toStdString(),QBP_SVM_TRAIN_TESTLIST,bNorm,bCat,iCat);
    }
    if(SVMTrainFileRadioValiSet->isChecked())
    {
        pQBPEngine->TrainSVM(SVMTrainFileEdit->text().toStdString(),QBP_SVM_TRAIN_VALILIST,bNorm,bCat,iCat);
    }
    if(SVMTrainFileRadioDataSet->isChecked())
    {
        pQBPEngine->TrainSVM(SVMTrainFileEdit->text().toStdString(),QBP_SVM_TRAIN_DATASET,bNorm,bCat,iCat);
    }
}

void CQBPTabPageSVM::OnBtnLoadCategory()
{
    SVMTrainSVMCategoryCombo->clear();
    for(int i=0 ; i< pQBPEngine->GenresLoaded();i++)
    {
        QString tCategoryName;
        int     tQtdSongs;
        pQBPEngine->GetGenreData(i,tCategoryName,tQtdSongs);

        SVMTrainSVMCategoryCombo->addItem(QString("Category %1 - ").arg(i) + tCategoryName , i);
    }
}


void CQBPTabPageSVM::OnBoxSVMSel(int selection)
{
   int SVMType = SVMModelSVMTypeCombo->itemData(selection).toInt();
   pQBPEngine->pQBPClassifier->SetType(SVMType);
}

void CQBPTabPageSVM::OnBoxKrlSel(int selection)
{
   pQBPEngine->pQBPClassifier->SetKernel(selection);
}

void CQBPTabPageSVM::OnEdtGamma()
{
   double gamma = SVMModelSVMGammaEdit->text().toDouble();
   pQBPEngine->pQBPClassifier->SetGamma(gamma);
}

void CQBPTabPageSVM::OnEdtDegree()
{
   int degree = SVMModelSVMDegreeEdit->text().toInt();
   pQBPEngine->pQBPClassifier->SetDegree(degree);
}

void CQBPTabPageSVM::OnEdtCoef0()
{
   double Coef0 = SVMModelSVMCoef0Edit->text().toDouble();
   pQBPEngine->pQBPClassifier->SetCoef0(Coef0);
}

void CQBPTabPageSVM::OnEdtCacheSize()
{
   double cachesize = SVMTrainCacheSizeEdit->text().toDouble();
   //pQBPEngine->pQBPClassifier->SetCacheSize(cachesize);
}

void CQBPTabPageSVM::OnEdtEPS()
{
   double EPS = SVMTrainEPSEdit->text().toDouble();
   //pQBPEngine->pQBPClassifier->SetEPS(EPS);
}

void CQBPTabPageSVM::OnEdtC()
{
   double C = SVMTrainCEdit->text().toDouble();
   pQBPEngine->pQBPClassifier->SetC(C);
}

void CQBPTabPageSVM::OnEdtWeight()
{
   int weight = SVMTrainWeightEdit->text().toInt();
   //pQBPEngine->pQBPClassifier->SetWeight(weight);
}

void CQBPTabPageSVM::OnEdtShrinking()
{
   int shrinking = SVMTrainShrinkingEdit->text().toInt();
   //pQBPEngine->pQBPClassifier->SetShrinking(shrinking);
}

void CQBPTabPageSVM::OnEdtProbability()
{
   int probability = SVMTrainProbabilityEdit->text().toInt();
   //pQBPEngine->pQBPClassifier->SetProbability(probability);
}

void CQBPTabPageSVM::OnEdtFolds()
{
   int folds = SVMTrainCrossValidFoldsEdit->text().toInt();
   pQBPEngine->pQBPClassifier->SetFolds(folds);
}

void CQBPTabPageSVM::resizeEvent(QResizeEvent *event)
{
    SVMPoolTree->resize(QSize(width(),height()));
}

void CQBPTabPageSVM::setEngineReference(CQBPEngine *pQBP_Engine)
{
    pQBPEngine = pQBP_Engine;
}
