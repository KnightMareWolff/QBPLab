#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "QBP_GlobalDef.h"
#include "QBP_ToolsTab.h"
#include "QBP_VisualizationTab.h"
#include "QBP_Engine.h"
#include "QBP_LogQueue.h"

class CQBPMainWindow : public QMainWindow
{
    Q_OBJECT

public:
     CQBPMainWindow(QWidget *parent = 0);
    ~CQBPMainWindow();

     /**************************************************************/
     /*Rotinas para Criação da estrutura principal de Menus e Telas*/
     /**************************************************************/
     void        CriaAcoes      ();
     void        CriaMenus      ();
     void        CriaBarras     ();
     void        CriaBarraStatus();
     void        CriaDocking    ();

     void loadFile(const QString &fileName);

protected:
    void closeEvent(QCloseEvent *event) override;
    void resizeEvent(QResizeEvent *event);

protected slots:
    void UpdateProcessingLog();

private slots:
    void newFile();
    void open();
    bool save();
    bool saveAs();
    void about();
    void documentWasModified();
#ifndef QT_NO_SESSIONMANAGER
    void commitData(QSessionManager &);
#endif

private:
    //Instancia Barra de Menu
    QMenuBar *mBarraMenu  ;
    QMenu    *mMenuArquivo;
    QMenu    *mMenuEditar ;
    QMenu    *mMenuSobre  ;

    QDockWidget          *pQBPToolsDock;
    QDockWidget          *pQBPCentralDock;
    CQBPToolsTab         *pQBPToolsTab;
    CQBPVisualizationTab *pQBPVisualizationTab;

    QToolBar *mToolBarArquivo;
    QToolBar *mToolBarEditar;

    QAction *mAcaoNovo;
    QAction *mAcaoAbrir;
    QAction *mAcaoSalvar;
    QAction *mAcaoSalvarComo;
    QAction *mAcaoSair;
    QAction *mAcaoCortar;
    QAction *mAcaoCopiar;
    QAction *mAcaoColar;
    QAction *mAcaoSobre;



    QString curFile;

    void readSettings();
    void writeSettings();
    bool saveFile(const QString &fileName);
    void setCurrentFile(const QString &fileName);
    QString strippedName(const QString &fullFileName);

    //Calculo do Timer de Eventos
    QTimer        *timer;
    QElapsedTimer *elapsedtimer;
    float         TimeElapsed;

    //Para calculos de tempo de Processo
    time_t          pQBPActualTime;
    struct tm      *pQBPStartSTime;
    struct tm      *pQBPFinishTime;

    //Engine Members
    static CQBPEngine   *pQBPEngine;
    static CQBPLogQueue *pQBPLogQueue;

};


#endif // MAINWINDOW_H
