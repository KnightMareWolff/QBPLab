#include "QBP_VisualizationTab.h"

QTextEdit * CQBPVisualizationTab::pQBP_OutputLog=nullptr;

CQBPVisualizationTab::CQBPVisualizationTab(QWidget *parent)
{
    tabWidget = new QTabWidget;

    pQBP_OutputLog = new QTextEdit(parent);
    pQBPTextFormat.setFont(QFont("Courier New",8, QFont::Courier));
    pQBP_OutputLog->setCurrentCharFormat(pQBPTextFormat);
    pQBP_OutputLog->setTextColor(QColor(0,0,0));
    pQBP_OutputLog->setTextBackgroundColor(QColor(0,0,0));

    pQBPTabPageCode   = new CQBPTabPageCode(parent);
    pQBPTabPageCharts = new CQBPTabPageCharts(parent);
    pQBPTabPage3DCharts = new CQBPTabPage3DCharts(parent);
    pQBPTabPageSWDebug  = new CQBPTabPageSWDebug(parent);

    tabWidget->addTab(pQBP_OutputLog     , tr("QBP Console"));
    tabWidget->addTab(pQBPTabPageCode    , tr("QBP Automation"));
    tabWidget->addTab(pQBPTabPageCharts  , tr("QBP Charts"));
    tabWidget->addTab(pQBPTabPage3DCharts, tr("QBP Spatial Visualization"));
    tabWidget->addTab(pQBPTabPageSWDebug , tr("QBP Matrix Analysis"));

    tabWidget->setUsesScrollButtons(true);
    //tabWidget->setMinimumWidth(300);

    TabLayout = new QVBoxLayout;
    TabLayout->addWidget(tabWidget);
    setLayout(TabLayout);

    pQBPCurrentTab    = QBP_TAB_TYPE_LOG;

    connect(tabWidget, SIGNAL(tabBarClicked(int)), this, SLOT(LoadIndex(int)));

}

void CQBPVisualizationTab::LoadIndex(int pagina)
{
    tabWidget->setCurrentIndex(pagina);
    switch(pagina)
    {
    case 0:{pQBPCurrentTab    = QBP_TAB_TYPE_LOG;}break;
    case 1:{pQBPCurrentTab    = QBP_TAB_TYPE_AUT;}break;
    case 2:{pQBPCurrentTab    = QBP_TAB_TYPE_CRT;}break;
    case 3:{pQBPCurrentTab    = QBP_TAB_TYPE_C3D;}break;
    case 4:{pQBPCurrentTab    = QBP_TAB_TYPE_DBG;}break;
    }
}

void CQBPVisualizationTab::setEngineReference(CQBPEngine *pQBP_Engine)
{
    pQBPTabPageCode->setEngineReference(pQBP_Engine);
    pQBPTabPageCharts->setEngineReference(pQBP_Engine);
    pQBPTabPage3DCharts->setEngineReference(pQBP_Engine);
    pQBPTabPageSWDebug->setEngineReference(pQBP_Engine);
}

void CQBPVisualizationTab::resizeEvent(QResizeEvent *event)
{
    tabWidget->resize(QSize(width(),height()));
}
