#ifndef QBP_TABPAGECHARTS_H
#define QBP_TABPAGECHARTS_H

#include "QBP_GlobalDef.h"
#include "QBP_Engine.h"
#include "QBP_LogQueue.h"

struct stFileSearch
{
    uint    stQBPSearchID;
    QString stQBPSearchName;
    QString stQBPSongName;
    uint    stQBPSearchAlignments;
    uint    stQBPPrecisionBalance;
    uint    stQBPResultSetBalance;
    uint    stQBPBufferSize;
    uint    stQBPComparatorType;
    float   stQBPPrecision;
    float   stQBPRecall;
    float   stQBPFmeasure;
    float   stQBPAccuracy;
    float   stQBPReciprocalRank;
    float   stQBPMSCD;
    float   stQBPSearchElapsed;
    float   stQBPSearchElapsedPre;
    float   stQBPSearchElapsedPro;
    float   stQBPSearchElapsedPos;
};

class CQBPTabPageCharts : public QWidget
{
    Q_OBJECT
public:
    explicit CQBPTabPageCharts(QWidget *parent = nullptr);
    void setEngineReference(CQBPEngine *pQBP_Engine);

    //Static Definitios for Engine Information access
    static CQBPEngine *pQBPEngine;

    //Extraction Data
    vector<stFileSearch> pSWBuscas;
    vector<stFileSearch> pMSBuscas;
    vector<stFileSearch> pMXBuscas;
    vector<stFileSearch> pATBuscas;
    vector<stFileSearch> pSWBuscasMedias;
    vector<stFileSearch> pMSBuscasMedias;
    vector<stFileSearch> pMXBuscasMedias;
    vector<stFileSearch> pATBuscasMedias;

    stFileSearch         pavgSWBuscas;
    stFileSearch         pavgMSBuscas;
    stFileSearch         pavgMXBuscas;
    stFileSearch         pavgATBuscas;

    vector<int>          pSWDataHistogram;
    vector<int>          pMSDataHistogram;
    vector<int>          pMXDataHistogram;
    vector<int>          pATDataHistogram;

    vector<stFileSearch> FileSearchList;

    //Normalization MinMaxCountour
    double  pMinContour;
    double  pMaxContour;

    void LoadFmeasureAverageByTypeChart   (int pQBP_ReportType);
    void LoadElapsedTimeAverageByTypeChart(int pQBP_ReportType);
    void LoadFmeasureByPrecisionChart     (int pQBP_ReportType);
    void LoadAccuracyByPrecisionChart     (int pQBP_ReportType);
    void LoadPrecisionByPrecisionChart    (int pQBP_ReportType);
    void LoadMRRByPrecisionChart          (int pQBP_ReportType);
    void LoadFmeasureByResultSizeChart    (int pQBP_ReportType);
    void LoadAccuracyByResultSizeChart    (int pQBP_ReportType);
    void LoadPrecisionByResultSizeChart   (int pQBP_ReportType);
    void LoadMRRByResultSizeChart         (int pQBP_ReportType);
    void LoadMRRByBufferSizeChart         (int pQBP_ReportType);
    void LoadPrecisionByBufferSizeChart   (int pQBP_ReportType);
    void LoadMSCDByBufferSizeChart        (int pQBP_ReportType);

    //Help Functions
    void ExtractSearchsByType(int pQBP_ReportType                     );
    void CalcHisSearchsByType(int pQBP_ReportType                     );
    void CalcMeanValuesByType(int pQBP_ReportType                     );
    void CalcMeanValuesByFiel(int pQBP_ReportType, int pQBP_FieldType );
    void CalcMeanValuesByHist(int pQBP_ReportType, int pQBP_HistType  );

//protected:
//    void resizeEvent(QResizeEvent *event);

signals:

public slots:
    void OnBtnClearCharts();
    void OnBtnSaveCharts();
    void OnBtnLoadCharts();
    void OnBoxChartSel(int selection);


private:

    //Layout
    QHBoxLayout *LayoutOptCharts;
    QVBoxLayout *LayoutPrincipal;
    QComboBox   *ChartsCombo;

    //Reports
    QChartView * pQBPFmeasureAverageByType;
    QChartView * pQBPElapsedTimeAverageByType;

    QChartView * pQBPFmeasureByPrecision;
    QChartView * pQBPFmeasureByResultSize;

    QChartView * pQBPPrecisionByResultSize;
    QChartView * pQBPPrecisionByPrecision;
    QChartView * pQBPPrecisionByBufferSize;

    QChartView * pQBPAccuracyByPrecision;
    QChartView * pQBPAccuracyByResultSize;

    QChartView * pQBPMRRByPrecision;
    QChartView * pQBPMRRByResultSize;
    QChartView * pQBPMRRByBufferSize;

    QChartView * pQBPMSCDByPrecision;
    QChartView * pQBPMSCDByResultSize;
    QChartView * pQBPMSCDByBufferSize;

    QChartView * pQBPActualReport;

    //Create Functions
    QChart *createElapsedTimeAverageByType(int pQBP_ReportType);
    QChart *createFmeasureAverageByType(int pQBP_ReportType);

    QChart *createPrecisionByPrecision(int pQBP_ReportType);
    QChart *createPrecisionByResultSize(int pQBP_ReportType);
    QChart *createPrecisionByBufferSize(int pQBP_ReportType);

    QChart *createFmeasureByPrecision(int pQBP_ReportType);
    QChart *createFmeasureByResultSize(int pQBP_ReportType);
    QChart *createFmeasureByBufferSize(int pQBP_ReportType);

    QChart *createAccuracyByPrecision(int pQBP_ReportType);
    QChart *createAccuracyByResultSize(int pQBP_ReportType);
    QChart *createAccuracyByBufferSize(int pQBP_ReportType);


    QChart *createMRRByPrecision(int pQBP_ReportType);
    QChart *createMRRByResultSize(int pQBP_ReportType);
    QChart *createMRRByBufferSize(int pQBP_ReportType);

    QChart *createMSCDByBufferSize(int pQBP_ReportType);



};

#endif // QBP_TABPAGECHARTS_H
