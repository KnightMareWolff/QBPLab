#ifndef QBP_TABPAGESVM_H
#define QBP_TABPAGESVM_H

#include "QBP_GlobalDef.h"
#include "QBP_Engine.h"

class CQBPTabPageSVM : public QWidget
{
    Q_OBJECT
public:
    explicit CQBPTabPageSVM(QWidget *parent = nullptr);
    void setEngineReference(CQBPEngine *pQBP_Engine);

    //Engine Members
    static CQBPEngine *pQBPEngine;

signals:

public slots:
    void OnBtnModelFile();
    void OnBtnTrainFile();
    void OnBtnBuildPool();
    void OnBtnLoadCategory();
    void OnBoxSVMSel(int selection);
    void OnBoxKrlSel(int selection);
    void OnEdtGamma();
    void OnEdtDegree();
    void OnEdtCoef0();
    void OnEdtCacheSize();
    void OnEdtEPS();
    void OnEdtC();
    void OnEdtWeight();
    void OnEdtShrinking();
    void OnEdtProbability();
    void OnEdtFolds();
protected:
    void resizeEvent(QResizeEvent *event);

private:

    //Model File Loading
    QLabel       *SVMModelFileLabel;
    QLineEdit    *SVMModelFileEdit;
    QPushButton  *SVMModelFileButton;
    //Model Parameters
    QLabel       *SVMModelSVMTypeLabel;
    QLineEdit    *SVMModelSVMTypeEdit;
    QComboBox    *SVMModelSVMTypeCombo;
    QLabel       *SVMModelSVMKernelTypeLabel;
    QLineEdit    *SVMModelSVMKernelTypeEdit;
    QComboBox    *SVMModelSVMKernelTypeCombo;
    QLabel       *SVMModelSVMGammaLabel;
    QLineEdit    *SVMModelSVMGammaEdit;
    QLabel       *SVMModelSVMDegreeLabel;
    QLineEdit    *SVMModelSVMDegreeEdit;
    QLabel       *SVMModelSVMCoef0Label;
    QLineEdit    *SVMModelSVMCoef0Edit;
    //Train File Generation
    QLabel       *SVMTrainFileLabel;
    QLineEdit    *SVMTrainFileEdit;
    QPushButton  *SVMTrainFileButton;
    QRadioButton *SVMTrainFileRadioTestSet;
    QRadioButton *SVMTrainFileRadioValiSet;
    QRadioButton *SVMTrainFileRadioDataSet;
    QCheckBox    *SVMTrainFileCheckNorm;
    //Train Parameters
    QLabel       *SVMTrainCacheSizeLabel;
    QLineEdit    *SVMTrainCacheSizeEdit;
    QLabel       *SVMTrainEPSLabel;
    QLineEdit    *SVMTrainEPSEdit;
    QLabel       *SVMTrainCLabel;
    QLineEdit    *SVMTrainCEdit;
    QLabel       *SVMTrainWeightLabel;
    QLineEdit    *SVMTrainWeightEdit;
    QLabel       *SVMTrainShrinkingLabel;
    QLineEdit    *SVMTrainShrinkingEdit;
    QLabel       *SVMTrainProbabilityLabel;
    QLineEdit    *SVMTrainProbabilityEdit;
    QLabel       *SVMTrainCrossValidFoldsLabel;
    QLineEdit    *SVMTrainCrossValidFoldsEdit;
    QLabel       *SVMTrainSVMCategoryLabel;
    QComboBox    *SVMTrainSVMCategoryCombo;
    QCheckBox    *SVMTrainSVMCategoryCheck;
    QPushButton  *SVMTrainSVMCategoryButton;
    //Classifier Pool Generation
    QLabel       *SVMPoolFileLabel;
    QLineEdit    *SVMPoolFileEdit;
    QPushButton  *SVMPoolFileButton;
    QPushButton  *SVMPoolBuildButton;
    QTreeWidget  *SVMPoolTree;

    //Thread
    QFuture<void> qQBPSVMThread;

};

#endif // QBP_TABPAGESVM_H
