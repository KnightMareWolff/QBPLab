#ifndef QBP_TABPAGESWDEBUG_H
#define QBP_TABPAGESWDEBUG_H

#include "QBP_GlobalDef.h"
#include "QBP_Engine.h"
#include "QBP_LogQueue.h"
#include "QBP_SWDebugGraph.h"

class CQBPTabPageSWDebug : public QWidget
{
    Q_OBJECT
public:

    virtual ~CQBPTabPageSWDebug(){}

    explicit CQBPTabPageSWDebug(QWidget *parent = nullptr);
    void setEngineReference(CQBPEngine *pQBP_Engine);

    //Static Definitios for Engine Information access
    static CQBPEngine *pQBPEngine;

    //void resizeEvent(QResizeEvent *event);
    void addData();
public slots:
    void OnBtnLoadMatrix();
    void OnBtnSaveMatrix();
    void OnBtnPlay();
    void OnBtnRecord();
    void OnBoxSearchSel (int selection);
    void OnBoxAlignmentsSel (int selection);
    void OnBoxTracebacksSel (int selection);
    void OnSliderSel(int selection);
    void PlayLoop();
    void RecordLoop();
private:
    CQBPSWDebugGraph   *  SWGraph;
    QGridLayout        *  pQBPDebugGrid;
    QComboBox          *  SearchsCombo;
    QComboBox          *  AlignmentsCombo;
    QComboBox          *  TracebacksCombo;
    QVector<CQBPSearch >  pQBPSearchList;
    CQBPSearch         *  pQBPCurrentSelection;
    QSlider            *  pQBPFrameSlider;
    QVector<QPointF>  pPointPath;
    QVector<QPixmap>  pDebbugMovie;
    QString           pBufferA;
    QString           pBufferB;
    bool              pPlayDebbug;

    //Calculo do Timer de Eventos
    QTimer        *timer;

    //Para calculos de tempo de Processo
    time_t          pQBPActualTime;
    struct tm      *pQBPStartSTime;
    struct tm      *pQBPFinishTime;

};

#endif // QBP_TABPAGESWDEBUG_H
