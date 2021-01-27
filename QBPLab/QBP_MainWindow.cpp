#include "QBP_MainWindow.h"

CQBPEngine     * CQBPMainWindow::pQBPEngine=nullptr;
CQBPLogQueue   * CQBPMainWindow::pQBPLogQueue=nullptr;

CQBPMainWindow::CQBPMainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    CriaAcoes();
    CriaMenus();
    CriaBarras();
    CriaBarraStatus();
    CriaDocking();

    setMenuBar(mBarraMenu);


    connect(pQBPVisualizationTab->pQBP_OutputLog->document(), &QTextDocument::contentsChanged,
            this, &CQBPMainWindow::documentWasModified);

#ifndef QT_NO_SESSIONMANAGER
    QGuiApplication::setFallbackSessionManagementEnabled(false);
    connect(qApp, &QGuiApplication::commitDataRequest,
            this, &CQBPMainWindow::commitData);
#endif

    setCurrentFile(QString());

    setUnifiedTitleAndToolBarOnMac(true);

    this->setWindowIcon(QIcon("Icones/insicon.png"));


    pQBPEngine   = new CQBPEngine();
    pQBPLogQueue = new CQBPLogQueue();

    pQBPToolsTab->setEngineReference(pQBPEngine);
    pQBPVisualizationTab->setEngineReference(pQBPEngine);

    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(UpdateProcessingLog()));
    timer->start(5);

    elapsedtimer = new QElapsedTimer();
    elapsedtimer->start();

}

CQBPMainWindow::~CQBPMainWindow()
{
   delete pQBPEngine;
}

void CQBPMainWindow::CriaAcoes()
{

    mAcaoNovo = new QAction(QIcon("Icones/new.png"), tr("&Novo"), this);
    mAcaoNovo->setShortcuts(QKeySequence::New);
    mAcaoNovo->setStatusTip(tr("Cria Novo Cenário"));
    connect(mAcaoNovo, &QAction::triggered, this, &CQBPMainWindow::newFile);

    mAcaoAbrir = new QAction(QIcon("Icones/open.png"), tr("&Abrir"), this);
    mAcaoAbrir->setShortcuts(QKeySequence::Open);
    mAcaoAbrir->setStatusTip(tr("Carrega Novo Cenário"));
    connect(mAcaoAbrir, &QAction::triggered, this, &CQBPMainWindow::open);


    mAcaoSalvar = new QAction(QIcon("Icones/save.png"), tr("&Salvar"), this);
    mAcaoSalvar->setShortcuts(QKeySequence::Save);
    mAcaoSalvar->setStatusTip(tr("Salva Cenário Atual"));
    connect(mAcaoSalvar, &QAction::triggered, this, &CQBPMainWindow::save);


    mAcaoSalvarComo = new QAction(QIcon("Icones/save.png"), tr("&Salvar Como..."), this);
    mAcaoSalvarComo->setShortcuts(QKeySequence::SaveAs);
    mAcaoSalvarComo->setStatusTip(tr("Salva Cenário Atual Com Outro Nome"));
    connect(mAcaoSalvarComo, &QAction::triggered, this, &CQBPMainWindow::saveAs);


    mAcaoSair = new QAction(tr("S&air"), this);
    mAcaoSair->setShortcuts(QKeySequence::Quit);
    mAcaoSair->setStatusTip(tr("Fechar a Aplicação"));
    connect(mAcaoSair, SIGNAL(triggered()), this, SLOT(close()));


    mAcaoCortar = new QAction(QIcon("Icones/cut.png"), tr("&Cortar"), this);
    mAcaoCortar->setShortcuts(QKeySequence::Cut);
    mAcaoCortar->setStatusTip(tr("Recortar Objeto"));
    //connect(mAcaoCortar, &QAction::triggered, pQBPVisualizationTab->pQBP_OutputLog, &QTextEdit::cut);


    mAcaoCopiar = new QAction(QIcon("Icones/copy.png"), tr("Co&piar"), this);
    mAcaoCopiar->setShortcuts(QKeySequence::Cut);
    mAcaoCopiar->setStatusTip(tr("Copiar Objeto"));
    //connect(mAcaoCortar,&QAction::triggered, pQBPVisualizationTab->pQBP_OutputLog, &QTextEdit::copy);


    mAcaoColar = new QAction(QIcon("Icones/paste.png"), tr("Co&lar"), this);
    mAcaoColar->setShortcuts(QKeySequence::Paste);
    mAcaoColar->setStatusTip(tr("Colar Objeto"));
    //connect(mAcaoCortar, &QAction::triggered, pQBPVisualizationTab->pQBP_OutputLog, &QTextEdit::paste);


    mAcaoSobre = new QAction(tr("&Sobre..."), this);
    mAcaoSobre->setStatusTip(tr("Exibe Informações sobre a Ferramenta"));
    connect(mAcaoSobre, SIGNAL(triggered()), this, SLOT(about()));
}
void CQBPMainWindow::CriaMenus()
{
    //Instancia Barra de Menu
    mBarraMenu     = new QMenuBar;

    //Cria o Menu Arquivo e inclui as ações
    mMenuArquivo   = mBarraMenu->addMenu(tr("&Arquivo"));
    mMenuArquivo->addAction(mAcaoNovo);
    mMenuArquivo->addAction(mAcaoAbrir);
    mMenuArquivo->addAction(mAcaoSalvar);
    mMenuArquivo->addAction(mAcaoSalvarComo);
    mMenuArquivo->addSeparator();
    mMenuArquivo->addAction(mAcaoSair);

    //Cria o Menu Editar e inclui as ações
    mMenuEditar    = mBarraMenu->addMenu(tr("&Editar"));
    mMenuEditar->addAction(mAcaoCortar);
    mMenuEditar->addAction(mAcaoCopiar);
    mMenuEditar->addAction(mAcaoColar);

    //Cria o Menu Sobre e inclui as ações
    mMenuSobre     = mBarraMenu->addMenu(tr("&Sobre"));
    mMenuSobre->addAction(mAcaoSobre);
}
void CQBPMainWindow::CriaBarras()
{
    mToolBarArquivo = addToolBar(tr("Arquivo"));
    mToolBarArquivo->addAction(mAcaoNovo);
    mToolBarArquivo->addAction(mAcaoAbrir);
    mToolBarArquivo->addAction(mAcaoSalvar);
    mToolBarArquivo->setIconSize(QSize(50,50));

    mToolBarEditar = addToolBar(tr("Editar"));
    mToolBarEditar->addAction(mAcaoCortar);
    mToolBarEditar->addAction(mAcaoCopiar);
    mToolBarEditar->addAction(mAcaoColar);
    mToolBarEditar->setIconSize(QSize(50,50));
}
void CQBPMainWindow::CriaBarraStatus()
{
   statusBar()->showMessage(tr("Pronto para Uso!"));
}

void CQBPMainWindow::CriaDocking()
{
    //Configura o Dock de Tools
    pQBPToolsDock = new QDockWidget(tr("Ferramentas"), this);
    pQBPToolsDock->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
    pQBPToolsTab = new CQBPToolsTab(pQBPToolsDock);
    pQBPToolsDock->setWidget(pQBPToolsTab);
    addDockWidget(Qt::LeftDockWidgetArea, pQBPToolsDock);

    //Cria o Dock Central
    //Configura o Dock de Tools
    pQBPCentralDock = new QDockWidget(tr("Visualização"), this);
    //pQBPCentralDock->setAllowedAreas(Qt::AllDockWidgetAreas);
    pQBPVisualizationTab = new CQBPVisualizationTab(pQBPCentralDock);
    pQBPCentralDock->setWidget(pQBPVisualizationTab);
    //addDockWidget(Qt::AllDockWidgetAreas, pQBPCentralDock);

    //Configura Tab de Visualização
    //pQBPVisualizationTab = new CQBPVisualizationTab();
    setCentralWidget(pQBPCentralDock);

}

void CQBPMainWindow::newFile()
{
    pQBPVisualizationTab->pQBP_OutputLog->clear();
    setCurrentFile(QString());
}
void CQBPMainWindow::open()
{
    QString fileName = QFileDialog::getOpenFileName(this);
    if (!fileName.isEmpty())
    {
       loadFile(fileName);
    }
}

bool CQBPMainWindow::save()
{
    if (curFile.isEmpty()) {
        return saveAs();
    } else {
        return saveFile(curFile);
    }
}

bool CQBPMainWindow::saveAs()
{
    QFileDialog dialog(this);
    dialog.setWindowModality(Qt::WindowModal);
    dialog.setAcceptMode(QFileDialog::AcceptSave);
    if (dialog.exec() != QDialog::Accepted)
        return false;
    return saveFile(dialog.selectedFiles().first());
}

void CQBPMainWindow::about()
{
   QMessageBox::about(this, tr("About Application"),
            tr("The <b>Application</b> example demonstrates how to "
               "write modern GUI applications using Qt, with a menu bar, "
               "toolbars, and a status bar."));
}

void CQBPMainWindow::documentWasModified()
{
    setWindowModified(pQBPVisualizationTab->pQBP_OutputLog->document()->isModified());
}

void CQBPMainWindow::loadFile(const QString &fileName)
{
    QFile file(fileName);
    if (!file.open(QFile::ReadOnly | QFile::Text)) {
        QMessageBox::warning(this, tr("Application"),
                             tr("Cannot read file %1:\n%2.")
                             .arg(QDir::toNativeSeparators(fileName), file.errorString()));
        return;
    }

    QTextStream in(&file);
#ifndef QT_NO_CURSOR
    QApplication::setOverrideCursor(Qt::WaitCursor);
#endif
    pQBPVisualizationTab->pQBP_OutputLog->setPlainText(in.readAll());
#ifndef QT_NO_CURSOR
    QApplication::restoreOverrideCursor();
#endif

    setCurrentFile(fileName);
    statusBar()->showMessage(tr("File loaded"), 2000);
}

bool CQBPMainWindow::saveFile(const QString &fileName)
{
    /*
    QFile file(fileName);
    if (!file.open(QFile::WriteOnly | QFile::Text)) {
        QMessageBox::warning(this, tr("Application"),
                             tr("Cannot write file %1:\n%2.")
                             .arg(QDir::toNativeSeparators(fileName),
                                  file.errorString()));
        return false;
    }


    QTextStream out(&file);
#ifndef QT_NO_CURSOR
    QApplication::setOverrideCursor(Qt::WaitCursor);
#endif
    out << pQBPVisualizationTab->pQBP_OutputLog->toPlainText();
#ifndef QT_NO_CURSOR
    QApplication::restoreOverrideCursor();
#endif

    setCurrentFile(fileName);
    statusBar()->showMessage(tr("File saved"), 2000);
    */
    QString fileName2 = "sauve.jpg";
    fileName2 = QFileDialog::getSaveFileName(this,"Sauve...","..."," (*.jpg)");
    if(!fileName2.isEmpty())
    {
    QPixmap picture;
    //picture = QPixmap::grabWidget(pQBPVisualizationTab->pQBP_OutputLog);
    picture = grab();
    picture.save(fileName2);
    }

    return true;
}

void CQBPMainWindow::setCurrentFile(const QString &fileName)
{
    curFile = fileName;
    pQBPVisualizationTab->pQBP_OutputLog->document()->setModified(false);
    setWindowModified(false);

    QString shownName = curFile;
    if (curFile.isEmpty())
        shownName = "untitled.txt";
    setWindowFilePath(shownName);
}

QString CQBPMainWindow::strippedName(const QString &fullFileName)
{
    return QFileInfo(fullFileName).fileName();
}

void CQBPMainWindow::closeEvent(QCloseEvent *event)
{
    writeSettings();
    event->accept();
}

void CQBPMainWindow::writeSettings()
{
    QSettings settings(QCoreApplication::organizationName(), QCoreApplication::applicationName());
    settings.setValue("geometry", saveGeometry());
}

void CQBPMainWindow::readSettings()
{
    QSettings settings(QCoreApplication::organizationName(), QCoreApplication::applicationName());
    const QByteArray geometry = settings.value("geometry", QByteArray()).toByteArray();
    if (geometry.isEmpty()) {
        const QRect availableGeometry = QApplication::desktop()->availableGeometry(this);
        resize(availableGeometry.width() / 3, availableGeometry.height() / 2);
        move((availableGeometry.width() - width()) / 2,
             (availableGeometry.height() - height()) / 2);
    } else {
        restoreGeometry(geometry);
    }
}

#ifndef QT_NO_SESSIONMANAGER
void CQBPMainWindow::commitData(QSessionManager &manager)
{
    if (manager.allowsInteraction())
    {
        manager.cancel();
    }
    else
    {
        // Non-interactive: save without asking
        if (pQBPVisualizationTab->pQBP_OutputLog->document()->isModified())
            save();
    }
}
#endif

void CQBPMainWindow::UpdateProcessingLog()
{
   QColor  pColor;
   QColor  pBack ;
   int     pSize;
   bool    pBold;
   QFont   pFont;

   TimeElapsed  = elapsedtimer->restart();
   TimeElapsed /= 1000;

   pQBPActualTime = time(0);
   pQBPStartSTime = localtime(&pQBPActualTime);


   if(!CQBPLogQueue::Empty() && !CQBPLogQueue::Locked())
   {
      CQBPQueueItem pLog   = CQBPLogQueue::Pop();

      pColor = pLog.pQBP_Color;
      pBack  = pLog.pQBP_BackGround;
      pBold  = pLog.pQBP_Bold;
      pSize  = pLog.pQBP_Size;

      pFont = QFont("Courier New",pSize, QFont::Courier);
      pFont.setBold(pBold);

      pQBPVisualizationTab->pQBP_OutputLog->setTextColor(pColor);
      pQBPVisualizationTab->pQBP_OutputLog->setTextBackgroundColor(pBack);
      pQBPVisualizationTab->pQBP_OutputLog->setCurrentFont(pFont);

      pQBPVisualizationTab->pQBP_OutputLog->insertPlainText(pLog.pQBP_Message);
   }

}

void CQBPMainWindow::resizeEvent(QResizeEvent *event)
{
    pQBPToolsTab->resize(QSize(width()/2,height()));
    pQBPVisualizationTab->resize(QSize(width()/2,height()));
}
