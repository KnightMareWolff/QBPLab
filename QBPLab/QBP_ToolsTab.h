#ifndef QBP_TOOLSTAB_H
#define QBP_TOOLSTAB_H

#include "QBP_GlobalDef.h"
#include "QBP_TabPageDataset.h"
#include "QBP_TabPageSVM.h"
#include "QBP_TabPageMusicSearch.h"
#include "QBP_TabPagePlayer.h"

class CQBPToolsTab : public QWidget
{
    Q_OBJECT
public:
    explicit CQBPToolsTab(QWidget *parent = nullptr);
    ~CQBPToolsTab();

    void setEngineReference(CQBPEngine *pQBP_Engine);

    QTabWidget *tabWidget;

    CQBPTabPageDataset     *pQBP_DatasetPage;
    CQBPTabPageSVM         *pQBP_SVMPage;
    CQBPTabPageMusicSearch *pQBP_MusicSearchPage;
    CQBPTabPagePlayer      *pQBP_MusicPlayer;

    QVBoxLayout *TabLayout;

    int    pQBPCurrentTab;

protected:
    void resizeEvent(QResizeEvent *event);


public slots:
    void LoadIndex(int pagina);
};

#endif // QBP_TABWIDGET_H
