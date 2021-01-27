#ifndef QBP_TABPAGE3DCHARTS_H
#define QBP_TABPAGE3DCHARTS_H

#include "QBP_GlobalDef.h"
#include "QBP_Engine.h"
#include "QBP_LogQueue.h"
#include "QBP_Clusterizer.h"

class CQBPTabPage3DCharts : public QWidget
{
    Q_OBJECT
public:
    explicit CQBPTabPage3DCharts(QWidget *parent = nullptr);
    void setEngineReference(CQBPEngine *pQBP_Engine);

    //Static Definitios for Engine Information access
    static CQBPEngine *pQBPEngine;

    void resizeEvent(QResizeEvent *event);
    void addData();
    void addChordsData();

signals:

public slots:
    void OnBtnLoadCharts();
    void OnBtnSaveCharts();

private:
    Q3DScatter      * pQBPScatter;
    QWidget         * pQBPScatterContainer;//we need this container becouse scatter inherits from QWindow
    QGridLayout     * pQBPChartsGrid;
    QProgressBar    * pQBPLoadProgress;
    CQBPClusterizer * pQBPClusterizer;

    int   m_fontSize;
    QAbstract3DSeries::Mesh m_style;
    bool  m_smooth;
};

#endif // QBP_TABPAGE3DCHARTS_H
