#include "QBP_ToolsTab.h"

CQBPToolsTab::CQBPToolsTab(QWidget *parent) : QWidget(parent)
{
    tabWidget = new QTabWidget;

    pQBP_DatasetPage     = new CQBPTabPageDataset();
    pQBP_MusicSearchPage = new CQBPTabPageMusicSearch();
    pQBP_SVMPage         = new CQBPTabPageSVM();
    pQBP_MusicPlayer     = new CQBPTabPagePlayer();

    tabWidget->addTab(pQBP_DatasetPage    , tr("Dataset"));
    tabWidget->addTab(pQBP_MusicSearchPage, tr("Search"));
    tabWidget->addTab(pQBP_SVMPage        , tr("ML"));
    tabWidget->addTab(pQBP_MusicPlayer    , tr("Player"));

    tabWidget->setUsesScrollButtons(true);
    //tabWidget->setMinimumWidth(300);

    TabLayout = new QVBoxLayout;
    TabLayout->addWidget(tabWidget);
    setLayout(TabLayout);

    pQBPCurrentTab    = QBP_TAB_TYPE_DTS;

    connect(tabWidget, SIGNAL(tabBarClicked(int)), this, SLOT(LoadIndex(int)));
}

CQBPToolsTab::~CQBPToolsTab()
{
    if(pQBP_DatasetPage)
    {
        pQBP_DatasetPage->Kill();
        delete pQBP_DatasetPage;
    }
    if(pQBP_MusicSearchPage)
    {
        pQBP_MusicSearchPage->Kill();
        delete pQBP_MusicSearchPage;
    }
    tabWidget->removeTab(0);
    tabWidget->removeTab(1);
    tabWidget->removeTab(2);
    TabLayout->removeWidget(tabWidget);
    delete tabWidget;
    delete TabLayout;
}

void CQBPToolsTab::setEngineReference(CQBPEngine *pQBP_Engine)
{
    pQBP_DatasetPage->setEngineReference(pQBP_Engine);
    pQBP_MusicSearchPage->setEngineReference(pQBP_Engine);
    pQBP_SVMPage->setEngineReference(pQBP_Engine);
    pQBP_MusicPlayer->setEngineReference(pQBP_Engine);
}

void CQBPToolsTab::LoadIndex(int pagina)
{
    tabWidget->setCurrentIndex(pagina);
    switch(pagina)
    {
    case 0:{pQBPCurrentTab    = QBP_TAB_TYPE_DTS;}break;
    case 1:{pQBPCurrentTab    = QBP_TAB_TYPE_CMP;}break;
    case 2:{pQBPCurrentTab    = QBP_TAB_TYPE_CLS;}break;
    case 3:{pQBPCurrentTab    = QBP_TAB_TYPE_PLY;}break;
    }
}

void CQBPToolsTab::resizeEvent(QResizeEvent *event)
{
    tabWidget->resize(QSize(width(),height()));
}
