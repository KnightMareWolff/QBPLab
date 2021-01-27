#ifndef QBP_VISUALIZATIONTAB_H
#define QBP_VISUALIZATIONTAB_H

#include "QBP_GlobalDef.h"
#include "QBP_TabPageCharts.h"
#include "QBP_TabPage3DCharts.h"
#include "QBP_TabPageSWDebug.h"
#include "QBP_TabPageCode.h"


class CQBPVisualizationTab : public QTabWidget
{
    Q_OBJECT
public:
    explicit CQBPVisualizationTab(QWidget *parent = nullptr);
    void setEngineReference(CQBPEngine *pQBP_Engine);

    QTabWidget *tabWidget;

    static QTextEdit *pQBP_OutputLog;
           QTextCharFormat pQBPTextFormat;

    CQBPTabPageCode       *pQBPTabPageCode;
    CQBPTabPageCharts     *pQBPTabPageCharts;
    CQBPTabPage3DCharts   *pQBPTabPage3DCharts;
    CQBPTabPageSWDebug    *pQBPTabPageSWDebug;

    QVBoxLayout *TabLayout;
    int          pQBPCurrentTab;

protected:
    void resizeEvent(QResizeEvent *event);

signals:

public slots:
    void LoadIndex(int pagina);
};

#endif // QBP_VISUALIZATIONTAB_H
