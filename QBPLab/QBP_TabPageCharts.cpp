#include "QBP_TabPageCharts.h"

CQBPEngine * CQBPTabPageCharts::pQBPEngine=nullptr;

CQBPTabPageCharts::CQBPTabPageCharts(QWidget *parent) : QWidget(parent)
{
    pQBPFmeasureByPrecision      =nullptr;
    pQBPAccuracyByPrecision      =nullptr;
    pQBPPrecisionByPrecision     =nullptr;
    pQBPFmeasureByResultSize     =nullptr;
    pQBPAccuracyByResultSize     =nullptr;
    pQBPPrecisionByResultSize    =nullptr;
    pQBPFmeasureAverageByType    =nullptr;
    pQBPElapsedTimeAverageByType =nullptr;
    pQBPMRRByPrecision           =nullptr;
    pQBPMRRByResultSize          =nullptr;
    pQBPMRRByBufferSize          =nullptr;
    pQBPPrecisionByBufferSize    =nullptr;
    pQBPMSCDByBufferSize         =nullptr;

    //Create the area Chart
    pQBPFmeasureByPrecision      = new QChartView();
    pQBPAccuracyByPrecision      = new QChartView();
    pQBPPrecisionByPrecision     = new QChartView();
    pQBPFmeasureByResultSize     = new QChartView();
    pQBPAccuracyByResultSize     = new QChartView();
    pQBPPrecisionByResultSize    = new QChartView();
    pQBPFmeasureAverageByType    = new QChartView();
    pQBPElapsedTimeAverageByType = new QChartView();
    pQBPMRRByPrecision           = new QChartView();
    pQBPMRRByResultSize          = new QChartView();
    pQBPMRRByBufferSize          = new QChartView();
    pQBPPrecisionByBufferSize    = new QChartView();
    pQBPMSCDByBufferSize         = new QChartView();

    QPushButton *ClearCharts  = new QPushButton(tr("Clear Charts"));
    QPushButton *LoadCharts   = new QPushButton(tr("Load From File"));
    QPushButton *SaveCharts   = new QPushButton(tr("Save Charts"));

    ChartsCombo = new QComboBox;
    ChartsCombo->addItem(QString("Mean Evaluation Metrics"),0);
    ChartsCombo->addItem(QString("Time Evaluation Metrics"),1);
    ChartsCombo->addItem(QString("Accuracy by Precision Balance Evolution Metrics"),2);
    ChartsCombo->addItem(QString("FMeasure by Precision Balance Evolution Metrics"),3);
    ChartsCombo->addItem(QString("Precision by Precision Balance Evolution Metrics"),4);
    ChartsCombo->addItem(QString("Reciprocal Rank by Precision Balance Evolution Metrics"),5);
    ChartsCombo->addItem(QString("Accuracy by ResultSize Balance Evolution Metrics"),6);
    ChartsCombo->addItem(QString("FMeasure by ResultSize Balance Evolution Metrics"),7);
    ChartsCombo->addItem(QString("Precision by ResultSize Balance Evolution Metrics"),8);
    ChartsCombo->addItem(QString("Reciprocal Rank by ResultSize Evolution Metrics"),9);
    ChartsCombo->addItem(QString("Reciprocal Rank by Buffer Size Evolution Metrics"),10);
    ChartsCombo->addItem(QString("Precision by Buffer Size Evolution Metrics"),11);
    ChartsCombo->addItem(QString("MSCD by Buffer Size Evolution Metrics"),12);

    //Grupo de Criação
    QGroupBox *GrupoChartParameters = new QGroupBox(tr("Chart Options:"));

    LayoutOptCharts = new QHBoxLayout;
    LayoutOptCharts->addWidget(ClearCharts);
    LayoutOptCharts->addWidget(SaveCharts);
    LayoutOptCharts->addWidget(LoadCharts);
    LayoutOptCharts->addWidget(ChartsCombo);

    GrupoChartParameters->setLayout(LayoutOptCharts);

    pQBPActualReport = pQBPFmeasureAverageByType;

    //Inclui os Grupos no Layout Principal
    LayoutPrincipal = new QVBoxLayout;
    LayoutPrincipal->addWidget(GrupoChartParameters);
    LayoutPrincipal->addWidget(pQBPActualReport);

    //Set the Main Layout of the Grid of Charts
    setLayout(LayoutPrincipal);

    //stablish controls connection
    connect(ClearCharts , SIGNAL(clicked()), this, SLOT(OnBtnClearCharts()));
    connect(SaveCharts , SIGNAL(clicked()), this, SLOT(OnBtnSaveCharts()));
    connect(LoadCharts , SIGNAL(clicked()), this, SLOT(OnBtnLoadCharts()));
    connect(ChartsCombo   , SIGNAL(activated   (int)), this, SLOT(OnBoxChartSel(int)));

}

void CQBPTabPageCharts::setEngineReference(CQBPEngine *pQBP_Engine)
{
    pQBPEngine = pQBP_Engine;
}

void CQBPTabPageCharts::OnBtnSaveCharts()
{
    QString fileName = "sauve.jpg";
    fileName = QFileDialog::getSaveFileName(this,"Sauve...","..."," (*.jpg)");
    if(!fileName.isEmpty())
    {
    QPixmap picture;
    //picture = QPixmap::grabWidget(this);
    picture = grab();
    picture.save(fileName);
    }
}

void CQBPTabPageCharts::OnBtnLoadCharts()
{

    string comma,searchname,songname;
    std::filebuf fb;

    QString fileName = "sauve.jpg";
    fileName = QFileDialog::getOpenFileName(this,"Load...",NULL," (*.txt)");
    if(!fileName.isEmpty())
    {
        //Abre arquivo para leitura
        fb.open(fileName.toStdString(), std::ios::in);
    }
    else
    {
        return;
    }

    //Grava dados na stream de arquivo
    std::istream is(&fb);

    while(!is.eof())
    {

        stFileSearch Record;

       is  >> Record.stQBPSearchID                >> comma //identificador da busca
           >> searchname                          >> comma //Nome da Busca
           >> songname                            >> comma //Nome da Musica de Consulta
           >> Record.stQBPSearchAlignments        >> comma //Numero de alinhamentos realizados(Obs:. apenas para Debbug)
           >> Record.stQBPPrecisionBalance        >> comma //Balanço de Precisão Utilizado
           >> Record.stQBPResultSetBalance        >> comma //Numero de Musicas no result set
           >> Record.stQBPBufferSize              >> comma //Tamanho do Buffer(por enquanto pega daqui sem atualizar na busca...)
           >> Record.stQBPComparatorType          >> comma //Algoritmo usado
           >> Record.stQBPPrecision               >> comma //Precisão da busca
           >> Record.stQBPRecall                  >> comma //Cobertura da Busca
           >> Record.stQBPFmeasure                >> comma //Media harmonica da busca
           >> Record.stQBPAccuracy                >> comma //acuracia da busca
           >> Record.stQBPReciprocalRank          >> comma //MRR da busca
           >> Record.stQBPMSCD                    >> comma //MSCD da busca
           >> Record.stQBPSearchElapsed           >> comma //Tempo total
           >> Record.stQBPSearchElapsedPre        >> comma //Tempo pre-processamento
           >> Record.stQBPSearchElapsedPro        >> comma //Tempo Processamento
           >> Record.stQBPSearchElapsedPos        ;//Tempo Pos-Processamento

          Record.stQBPSearchName = QString(searchname.c_str());
          Record.stQBPSongName   = QString(songname.c_str());

          FileSearchList.push_back(Record);
    }

    QMessageBox msgBox;
    msgBox.setText("O Arquivo de Buscas foi carregado Corretamente.");
    msgBox.exec();
}

void CQBPTabPageCharts::OnBtnClearCharts()
{
    FileSearchList.clear();
    FileSearchList.shrink_to_fit();  
    pSWBuscas.clear();
    pSWBuscas.shrink_to_fit();
    pMSBuscas.clear();
    pMSBuscas.shrink_to_fit();
    pMXBuscas.clear();
    pMXBuscas.shrink_to_fit();
    pATBuscas.clear();
    pATBuscas.shrink_to_fit();
    pSWBuscasMedias.clear();
    pSWBuscasMedias.shrink_to_fit();
    pMSBuscasMedias.clear();
    pMSBuscasMedias.shrink_to_fit();
    pMXBuscasMedias.clear();
    pMXBuscasMedias.shrink_to_fit();
    pATBuscasMedias.clear();
    pATBuscasMedias.shrink_to_fit();
    pSWDataHistogram.clear();
    pSWDataHistogram.shrink_to_fit();
    pMSDataHistogram.clear();
    pMSDataHistogram.shrink_to_fit();
    pMXDataHistogram.clear();
    pMXDataHistogram.shrink_to_fit();
    pATDataHistogram.clear();
    pATDataHistogram.shrink_to_fit();
}

void  CQBPTabPageCharts::LoadFmeasureAverageByTypeChart(int pQBP_ReportType)
{
    //There is no data to be loaded...affff
    if(FileSearchList.size() <= 0 )
    {
        return;
    }

    QPalette pal = palette();
    //Setup the theme color pallete.
    pal.setColor(QPalette::Window, QRgb(0x121218));
    pal.setColor(QPalette::WindowText, QRgb(0xd6d6d6));
    setPalette(pal);

    //Create the FmeasureAverageByType Chart
    pQBPFmeasureAverageByType = new QChartView(createFmeasureAverageByType(pQBP_ReportType));
    pQBPFmeasureAverageByType->chart()->setTheme(QChart::ChartThemeLight);
    pQBPFmeasureAverageByType->setRenderHint(QPainter::Antialiasing, true);
    pQBPFmeasureAverageByType->chart()->setAnimationOptions(QChart::AllAnimations);


    LayoutPrincipal->removeWidget(pQBPActualReport);

    pQBPActualReport = pQBPFmeasureAverageByType;

    LayoutPrincipal->addWidget(pQBPActualReport);
}

void  CQBPTabPageCharts::LoadElapsedTimeAverageByTypeChart(int pQBP_ReportType)
{
    //There is no data to be loaded...affff
    if(FileSearchList.size() <= 0 )
    {
        return;
    }

    QPalette pal = palette();
    //Setup the theme color pallete.
    pal.setColor(QPalette::Window, QRgb(0x121218));
    pal.setColor(QPalette::WindowText, QRgb(0xd6d6d6));
    setPalette(pal);

    //Create the Elapsed Time Chart
    pQBPElapsedTimeAverageByType = new QChartView(createElapsedTimeAverageByType(pQBP_ReportType));
    pQBPElapsedTimeAverageByType->chart()->setTheme(QChart::ChartThemeLight);
    pQBPElapsedTimeAverageByType->setRenderHint(QPainter::Antialiasing, true);
    pQBPElapsedTimeAverageByType->chart()->setAnimationOptions(QChart::AllAnimations);

    LayoutPrincipal->removeWidget(pQBPActualReport);

    pQBPActualReport = pQBPElapsedTimeAverageByType;

    LayoutPrincipal->addWidget(pQBPActualReport);
}

void  CQBPTabPageCharts::LoadFmeasureByPrecisionChart(int pQBP_ReportType)
{
    //There is no data to be loaded...affff
    if(FileSearchList.size() <= 0 )
    {
        return;
    }

    QPalette pal = palette();
    //Setup the theme color pallete.
    pal.setColor(QPalette::Window, QRgb(0x121218));
    pal.setColor(QPalette::WindowText, QRgb(0xd6d6d6));
    setPalette(pal);

    //Create the FmeasureByPrecision Chart
    pQBPFmeasureByPrecision = new QChartView(createFmeasureByPrecision(pQBP_ReportType));
    pQBPFmeasureByPrecision->chart()->setTheme(QChart::ChartThemeLight);
    pQBPFmeasureByPrecision->setRenderHint(QPainter::Antialiasing, true);
    pQBPFmeasureByPrecision->chart()->setAnimationOptions(QChart::AllAnimations);

    LayoutPrincipal->removeWidget(pQBPActualReport);

    pQBPActualReport = pQBPFmeasureByPrecision;

    LayoutPrincipal->addWidget(pQBPActualReport);
}

void  CQBPTabPageCharts::LoadAccuracyByPrecisionChart(int pQBP_ReportType)
{
    //There is no data to be loaded...affff
    if(FileSearchList.size() <= 0 )
    {
        return;
    }

    QPalette pal = palette();
    //Setup the theme color pallete.
    pal.setColor(QPalette::Window, QRgb(0x121218));
    pal.setColor(QPalette::WindowText, QRgb(0xd6d6d6));
    setPalette(pal);

    //Create the Genre Bar Chart
    pQBPAccuracyByPrecision = new QChartView(createAccuracyByPrecision(pQBP_ReportType));
    pQBPAccuracyByPrecision->chart()->setTheme(QChart::ChartThemeLight);
    pQBPAccuracyByPrecision->setRenderHint(QPainter::Antialiasing, true);
    pQBPAccuracyByPrecision->chart()->setAnimationOptions(QChart::AllAnimations);


    LayoutPrincipal->removeWidget(pQBPActualReport);

    pQBPActualReport = pQBPAccuracyByPrecision;

    LayoutPrincipal->addWidget(pQBPActualReport);
}

void  CQBPTabPageCharts::LoadPrecisionByPrecisionChart(int pQBP_ReportType)
{
    //There is no data to be loaded...affff
    if(FileSearchList.size() <= 0 )
    {
        return;
    }

    QPalette pal = palette();
    //Setup the theme color pallete.
    pal.setColor(QPalette::Window, QRgb(0x121218));
    pal.setColor(QPalette::WindowText, QRgb(0xd6d6d6));
    setPalette(pal);

    //Create the Genre Bar Chart
    pQBPPrecisionByPrecision = new QChartView(createPrecisionByPrecision(pQBP_ReportType));
    pQBPPrecisionByPrecision->chart()->setTheme(QChart::ChartThemeLight);
    pQBPPrecisionByPrecision->setRenderHint(QPainter::Antialiasing, true);
    pQBPPrecisionByPrecision->chart()->setAnimationOptions(QChart::AllAnimations);


    LayoutPrincipal->removeWidget(pQBPActualReport);

    pQBPActualReport = pQBPPrecisionByPrecision;

    LayoutPrincipal->addWidget(pQBPActualReport);
}

void  CQBPTabPageCharts::LoadMRRByPrecisionChart(int pQBP_ReportType)
{
    //There is no data to be loaded...affff
    if(FileSearchList.size() <= 0 )
    {
        return;
    }

    QPalette pal = palette();
    //Setup the theme color pallete.
    pal.setColor(QPalette::Window, QRgb(0x121218));
    pal.setColor(QPalette::WindowText, QRgb(0xd6d6d6));
    setPalette(pal);

    //Create the Genre Bar Chart
    pQBPMRRByPrecision = new QChartView(createMRRByPrecision(pQBP_ReportType));
    pQBPMRRByPrecision->chart()->setTheme(QChart::ChartThemeLight);
    pQBPMRRByPrecision->setRenderHint(QPainter::Antialiasing, true);
    pQBPMRRByPrecision->chart()->setAnimationOptions(QChart::AllAnimations);


    LayoutPrincipal->removeWidget(pQBPActualReport);

    pQBPActualReport = pQBPMRRByPrecision;

    LayoutPrincipal->addWidget(pQBPActualReport);
}

void  CQBPTabPageCharts::LoadFmeasureByResultSizeChart(int pQBP_ReportType)
{
    //There is no data to be loaded...affff
    if(FileSearchList.size() <= 0 )
    {
        return;
    }

    QPalette pal = palette();
    //Setup the theme color pallete.
    pal.setColor(QPalette::Window, QRgb(0x121218));
    pal.setColor(QPalette::WindowText, QRgb(0xd6d6d6));
    setPalette(pal);

    //Create the FmeasureByPrecision Chart
    pQBPFmeasureByResultSize = new QChartView(createFmeasureByResultSize(pQBP_ReportType));
    pQBPFmeasureByResultSize->chart()->setTheme(QChart::ChartThemeLight);
    pQBPFmeasureByResultSize->setRenderHint(QPainter::Antialiasing, true);
    pQBPFmeasureByResultSize->chart()->setAnimationOptions(QChart::AllAnimations);

    LayoutPrincipal->removeWidget(pQBPActualReport);

    pQBPActualReport = pQBPFmeasureByResultSize;

    LayoutPrincipal->addWidget(pQBPActualReport);
}

void  CQBPTabPageCharts::LoadAccuracyByResultSizeChart(int pQBP_ReportType)
{
    //There is no data to be loaded...affff
    if(FileSearchList.size() <= 0 )
    {
        return;
    }

    QPalette pal = palette();
    //Setup the theme color pallete.
    pal.setColor(QPalette::Window, QRgb(0x121218));
    pal.setColor(QPalette::WindowText, QRgb(0xd6d6d6));
    setPalette(pal);

    //Create the Genre Bar Chart
    pQBPAccuracyByResultSize = new QChartView(createAccuracyByResultSize(pQBP_ReportType));
    pQBPAccuracyByResultSize->chart()->setTheme(QChart::ChartThemeLight);
    pQBPAccuracyByResultSize->setRenderHint(QPainter::Antialiasing, true);
    pQBPAccuracyByResultSize->chart()->setAnimationOptions(QChart::AllAnimations);

    LayoutPrincipal->removeWidget(pQBPActualReport);

    pQBPActualReport = pQBPAccuracyByResultSize;

    LayoutPrincipal->addWidget(pQBPActualReport);
}

void  CQBPTabPageCharts::LoadPrecisionByResultSizeChart(int pQBP_ReportType)
{
    //There is no data to be loaded...affff
    if(FileSearchList.size() <= 0 )
    {
        return;
    }

    QPalette pal = palette();
    //Setup the theme color pallete.
    pal.setColor(QPalette::Window, QRgb(0x121218));
    pal.setColor(QPalette::WindowText, QRgb(0xd6d6d6));
    setPalette(pal);

    //Create the Genre Bar Chart
    pQBPPrecisionByResultSize = new QChartView(createPrecisionByResultSize(pQBP_ReportType));
    pQBPPrecisionByResultSize->chart()->setTheme(QChart::ChartThemeLight);
    pQBPPrecisionByResultSize->setRenderHint(QPainter::Antialiasing, true);
    pQBPPrecisionByResultSize->chart()->setAnimationOptions(QChart::AllAnimations);


    LayoutPrincipal->removeWidget(pQBPActualReport);

    pQBPActualReport = pQBPPrecisionByResultSize;

    LayoutPrincipal->addWidget(pQBPActualReport);
}

void  CQBPTabPageCharts::LoadMRRByResultSizeChart(int pQBP_ReportType)
{
    //There is no data to be loaded...affff
    if(FileSearchList.size() <= 0 )
    {
        return;
    }

    QPalette pal = palette();
    //Setup the theme color pallete.
    pal.setColor(QPalette::Window, QRgb(0x121218));
    pal.setColor(QPalette::WindowText, QRgb(0xd6d6d6));
    setPalette(pal);

    //Create the Genre Bar Chart
    pQBPMRRByResultSize = new QChartView(createMRRByResultSize(pQBP_ReportType));
    pQBPMRRByResultSize->chart()->setTheme(QChart::ChartThemeLight);
    pQBPMRRByResultSize->setRenderHint(QPainter::Antialiasing, true);
    pQBPMRRByResultSize->chart()->setAnimationOptions(QChart::AllAnimations);


    LayoutPrincipal->removeWidget(pQBPActualReport);

    pQBPActualReport = pQBPMRRByResultSize;

    LayoutPrincipal->addWidget(pQBPActualReport);
}

void  CQBPTabPageCharts::LoadMRRByBufferSizeChart(int pQBP_ReportType)
{
    //There is no data to be loaded...affff
    if(FileSearchList.size() <= 0 )
    {
        return;
    }

    QPalette pal = palette();
    //Setup the theme color pallete.
    pal.setColor(QPalette::Window, QRgb(0x121218));
    pal.setColor(QPalette::WindowText, QRgb(0xd6d6d6));
    setPalette(pal);

    //Create the Genre Bar Chart
    pQBPMRRByBufferSize = new QChartView(createMRRByBufferSize(pQBP_ReportType));
    pQBPMRRByBufferSize->chart()->setTheme(QChart::ChartThemeLight);
    pQBPMRRByBufferSize->setRenderHint(QPainter::Antialiasing, true);
    pQBPMRRByBufferSize->chart()->setAnimationOptions(QChart::AllAnimations);


    LayoutPrincipal->removeWidget(pQBPActualReport);

    pQBPActualReport = pQBPMRRByBufferSize;

    LayoutPrincipal->addWidget(pQBPActualReport);
}

void  CQBPTabPageCharts::LoadPrecisionByBufferSizeChart(int pQBP_ReportType)
{
    //There is no data to be loaded...affff
    if(FileSearchList.size() <= 0 )
    {
        return;
    }

    QPalette pal = palette();
    //Setup the theme color pallete.
    pal.setColor(QPalette::Window, QRgb(0x121218));
    pal.setColor(QPalette::WindowText, QRgb(0xd6d6d6));
    setPalette(pal);

    //Create the Genre Bar Chart
    pQBPPrecisionByBufferSize = new QChartView(createPrecisionByBufferSize(pQBP_ReportType));
    pQBPPrecisionByBufferSize->chart()->setTheme(QChart::ChartThemeLight);
    pQBPPrecisionByBufferSize->setRenderHint(QPainter::Antialiasing, true);
    pQBPPrecisionByBufferSize->chart()->setAnimationOptions(QChart::AllAnimations);


    LayoutPrincipal->removeWidget(pQBPActualReport);

    pQBPActualReport = pQBPPrecisionByBufferSize;

    LayoutPrincipal->addWidget(pQBPActualReport);
}

void  CQBPTabPageCharts::LoadMSCDByBufferSizeChart(int pQBP_ReportType)
{
    //There is no data to be loaded...affff
    if(FileSearchList.size() <= 0 )
    {
        return;
    }

    QPalette pal = palette();
    //Setup the theme color pallete.
    pal.setColor(QPalette::Window, QRgb(0x121218));
    pal.setColor(QPalette::WindowText, QRgb(0xd6d6d6));
    setPalette(pal);

    //Create the Genre Bar Chart
    pQBPMSCDByBufferSize = new QChartView(createMSCDByBufferSize(pQBP_ReportType));
    pQBPMSCDByBufferSize->chart()->setTheme(QChart::ChartThemeLight);
    pQBPMSCDByBufferSize->setRenderHint(QPainter::Antialiasing, true);
    pQBPMSCDByBufferSize->chart()->setAnimationOptions(QChart::AllAnimations);


    LayoutPrincipal->removeWidget(pQBPActualReport);

    pQBPActualReport = pQBPMSCDByBufferSize;

    LayoutPrincipal->addWidget(pQBPActualReport);
}


void CQBPTabPageCharts::OnBoxChartSel(int selection)
{
    switch(selection)
    {
    case QBP_BUFFER_TYPE_FMAvgByType     :{LoadFmeasureAverageByTypeChart   (selection);}break;
    case QBP_BUFFER_TYPE_ETAvgByType     :{LoadElapsedTimeAverageByTypeChart(selection);}break;
    case QBP_BUFFER_TYPE_ACAvgByPrecision:{LoadAccuracyByPrecisionChart     (selection);}break;
    case QBP_BUFFER_TYPE_FMAvgByPrecision:{LoadFmeasureByPrecisionChart     (selection);}break;
    case QBP_BUFFER_TYPE_PCAvgByPrecision:{LoadPrecisionByPrecisionChart    (selection);}break;
    case QBP_BUFFER_TYPE_MRAvgByPrecision:{LoadMRRByPrecisionChart          (selection);}break;
    case QBP_BUFFER_TYPE_ACAvgByResultSz :{LoadAccuracyByResultSizeChart    (selection);}break;
    case QBP_BUFFER_TYPE_FMAvgByResultSz :{LoadFmeasureByResultSizeChart    (selection);}break;
    case QBP_BUFFER_TYPE_PCAvgByResultSz :{LoadPrecisionByResultSizeChart   (selection);}break;
    case QBP_BUFFER_TYPE_MRAvgByResultSz :{LoadMRRByResultSizeChart         (selection);}break;
    case QBP_BUFFER_TYPE_MRAvgByBufferSz :{LoadMRRByBufferSizeChart         (selection);}break;
    case QBP_BUFFER_TYPE_PCAvgByBufferSz :{LoadPrecisionByBufferSizeChart   (selection);}break;
    case QBP_BUFFER_TYPE_CDAvgByBufferSz :{LoadMSCDByBufferSizeChart        (selection);}break;
    }
}

QChart *CQBPTabPageCharts::createElapsedTimeAverageByType(int pQBP_ReportType)
{
    QChart *chart = new QChart();
    chart->setTitle("Average Elapsed Time");

    CQBPLogQueue::Push(QString("====================================================\n"));
    CQBPLogQueue::Push(QString("Relatório Elapsed Time Average: \n"));
    CQBPLogQueue::Push(QString("====================================================\n"));

    QString tSearchName;
    float   tSearchElapsed   =0.0f;//Search Elapsed Time
    float   tSearchElapsedPre=0.0f;//Search Preprocessing Time
    float   tSearchElapsedPro=0.0f;//Search Processing Time
    float   tSearchElapsedPos=0.0f;//Search Pos-Processing Time
    float   tSearchElapsedMax=0.0f;//Maximum average time for all of them

    ExtractSearchsByType(pQBP_ReportType);

    //Calcula as medias por tipo de busca
    for (int i=0;i<4;i++)
    {
        switch(i)
        {
        case QBP_MATRIX_TYPE_ORIGIN:
        {
            if(pSWBuscas.size()>0)
            {
               pavgSWBuscas.stQBPSearchName       ="";
               pavgSWBuscas.stQBPSearchElapsed    =0.0f;
               pavgSWBuscas.stQBPSearchElapsedPre =0.0f;
               pavgSWBuscas.stQBPSearchElapsedPro =0.0f;
               pavgSWBuscas.stQBPSearchElapsedPos =0.0f;
               pavgSWBuscas.stQBPComparatorType   =0;
               for (int j=0;j<pSWBuscas.size();j++)
               {
                   pavgSWBuscas.stQBPSearchElapsed    += pSWBuscas[j].stQBPSearchElapsed;
                   pavgSWBuscas.stQBPSearchElapsedPre += pSWBuscas[j].stQBPSearchElapsedPre;
                   pavgSWBuscas.stQBPSearchElapsedPro += pSWBuscas[j].stQBPSearchElapsedPro;
                   pavgSWBuscas.stQBPSearchElapsedPos += pSWBuscas[j].stQBPSearchElapsedPos;
               }

               pavgSWBuscas.stQBPSearchElapsed    = pavgSWBuscas.stQBPSearchElapsed    /(uint)pSWBuscas.size();
               pavgSWBuscas.stQBPSearchElapsedPre = pavgSWBuscas.stQBPSearchElapsedPre /(uint)pSWBuscas.size();
               pavgSWBuscas.stQBPSearchElapsedPro = pavgSWBuscas.stQBPSearchElapsedPro /(uint)pSWBuscas.size();
               pavgSWBuscas.stQBPSearchElapsedPos = pavgSWBuscas.stQBPSearchElapsedPos /(uint)pSWBuscas.size();

               if(pavgSWBuscas.stQBPSearchElapsed   >tSearchElapsedMax)tSearchElapsedMax=pavgSWBuscas.stQBPSearchElapsed;
               if(pavgSWBuscas.stQBPSearchElapsedPre>tSearchElapsedMax)tSearchElapsedMax=pavgSWBuscas.stQBPSearchElapsedPre;
               if(pavgSWBuscas.stQBPSearchElapsedPro>tSearchElapsedMax)tSearchElapsedMax=pavgSWBuscas.stQBPSearchElapsedPro;
               if(pavgSWBuscas.stQBPSearchElapsedPos>tSearchElapsedMax)tSearchElapsedMax=pavgSWBuscas.stQBPSearchElapsedPos;
            }
        }break;
        case QBP_MATRIX_TYPE_MUSSUM:
        {
            if(pMSBuscas.size()>0)
            {
                pavgMSBuscas.stQBPSearchName       ="";
                pavgMSBuscas.stQBPSearchElapsed    =0.0f;
                pavgMSBuscas.stQBPSearchElapsedPre =0.0f;
                pavgMSBuscas.stQBPSearchElapsedPro =0.0f;
                pavgMSBuscas.stQBPSearchElapsedPos =0.0f;
                pavgMSBuscas.stQBPComparatorType   =0;
               for (int j=0;j<pMSBuscas.size();j++)
               {
                   pavgMSBuscas.stQBPSearchElapsed    += pMSBuscas[j].stQBPSearchElapsed;
                   pavgMSBuscas.stQBPSearchElapsedPre += pMSBuscas[j].stQBPSearchElapsedPre;
                   pavgMSBuscas.stQBPSearchElapsedPro += pMSBuscas[j].stQBPSearchElapsedPro;
                   pavgMSBuscas.stQBPSearchElapsedPos += pMSBuscas[j].stQBPSearchElapsedPos;
               }

               pavgMSBuscas.stQBPSearchElapsed    = pavgMSBuscas.stQBPSearchElapsed    /(uint)pMSBuscas.size();
               pavgMSBuscas.stQBPSearchElapsedPre = pavgMSBuscas.stQBPSearchElapsedPre /(uint)pMSBuscas.size();
               pavgMSBuscas.stQBPSearchElapsedPro = pavgMSBuscas.stQBPSearchElapsedPro /(uint)pMSBuscas.size();
               pavgMSBuscas.stQBPSearchElapsedPos = pavgMSBuscas.stQBPSearchElapsedPos /(uint)pMSBuscas.size();

               if(pavgMSBuscas.stQBPSearchElapsed   >tSearchElapsedMax)tSearchElapsedMax=pavgMSBuscas.stQBPSearchElapsed;
               if(pavgMSBuscas.stQBPSearchElapsedPre>tSearchElapsedMax)tSearchElapsedMax=pavgMSBuscas.stQBPSearchElapsedPre;
               if(pavgMSBuscas.stQBPSearchElapsedPro>tSearchElapsedMax)tSearchElapsedMax=pavgMSBuscas.stQBPSearchElapsedPro;
               if(pavgMSBuscas.stQBPSearchElapsedPos>tSearchElapsedMax)tSearchElapsedMax=pavgMSBuscas.stQBPSearchElapsedPos;
            }
        }break;
        case QBP_MATRIX_TYPE_MUSSIX:
        {
            if(pMXBuscas.size()>0)
            {
               pavgMXBuscas.stQBPSearchName       ="";
               pavgMXBuscas.stQBPSearchElapsed    =0.0f;
               pavgMXBuscas.stQBPSearchElapsedPre =0.0f;
               pavgMXBuscas.stQBPSearchElapsedPro =0.0f;
               pavgMXBuscas.stQBPSearchElapsedPos =0.0f;
               pavgMXBuscas.stQBPComparatorType   =0;
               for (int j=0;j<pMXBuscas.size();j++)
               {
                   pavgMXBuscas.stQBPSearchElapsed    += pMXBuscas[j].stQBPSearchElapsed;
                   pavgMXBuscas.stQBPSearchElapsedPre += pMXBuscas[j].stQBPSearchElapsedPre;
                   pavgMXBuscas.stQBPSearchElapsedPro += pMXBuscas[j].stQBPSearchElapsedPro;
                   pavgMXBuscas.stQBPSearchElapsedPos += pMXBuscas[j].stQBPSearchElapsedPos;
               }

               pavgMXBuscas.stQBPSearchElapsed    = pavgMXBuscas.stQBPSearchElapsed    /(uint)pMXBuscas.size();
               pavgMXBuscas.stQBPSearchElapsedPre = pavgMXBuscas.stQBPSearchElapsedPre /(uint)pMXBuscas.size();
               pavgMXBuscas.stQBPSearchElapsedPro = pavgMXBuscas.stQBPSearchElapsedPro /(uint)pMXBuscas.size();
               pavgMXBuscas.stQBPSearchElapsedPos = pavgMXBuscas.stQBPSearchElapsedPos /(uint)pMXBuscas.size();

               if(pavgMXBuscas.stQBPSearchElapsed   >tSearchElapsedMax)tSearchElapsedMax=pavgMXBuscas.stQBPSearchElapsed;
               if(pavgMXBuscas.stQBPSearchElapsedPre>tSearchElapsedMax)tSearchElapsedMax=pavgMXBuscas.stQBPSearchElapsedPre;
               if(pavgMXBuscas.stQBPSearchElapsedPro>tSearchElapsedMax)tSearchElapsedMax=pavgMXBuscas.stQBPSearchElapsedPro;
               if(pavgMXBuscas.stQBPSearchElapsedPos>tSearchElapsedMax)tSearchElapsedMax=pavgMXBuscas.stQBPSearchElapsedPos;
            }
        }break;
        case QBP_MATRIX_TYPE_MUSSAT:
        {
            if(pATBuscas.size()>0)
            {
               pavgATBuscas.stQBPSearchName       ="";
               pavgATBuscas.stQBPSearchElapsed    =0.0f;
               pavgATBuscas.stQBPSearchElapsedPre =0.0f;
               pavgATBuscas.stQBPSearchElapsedPro =0.0f;
               pavgATBuscas.stQBPSearchElapsedPos =0.0f;
               pavgATBuscas.stQBPComparatorType   =0;
               for (int j=0;j<pATBuscas.size();j++)
               {
                   pavgATBuscas.stQBPSearchElapsed    += pATBuscas[j].stQBPSearchElapsed;
                   pavgATBuscas.stQBPSearchElapsedPre += pATBuscas[j].stQBPSearchElapsedPre;
                   pavgATBuscas.stQBPSearchElapsedPro += pATBuscas[j].stQBPSearchElapsedPro;
                   pavgATBuscas.stQBPSearchElapsedPos += pATBuscas[j].stQBPSearchElapsedPos;
               }

               pavgATBuscas.stQBPSearchElapsed    = pavgATBuscas.stQBPSearchElapsed    /(uint)pATBuscas.size();
               pavgATBuscas.stQBPSearchElapsedPre = pavgATBuscas.stQBPSearchElapsedPre /(uint)pATBuscas.size();
               pavgATBuscas.stQBPSearchElapsedPro = pavgATBuscas.stQBPSearchElapsedPro /(uint)pATBuscas.size();
               pavgATBuscas.stQBPSearchElapsedPos = pavgATBuscas.stQBPSearchElapsedPos /(uint)pATBuscas.size();

               if(pavgATBuscas.stQBPSearchElapsed   >tSearchElapsedMax)tSearchElapsedMax=pavgATBuscas.stQBPSearchElapsed;
               if(pavgATBuscas.stQBPSearchElapsedPre>tSearchElapsedMax)tSearchElapsedMax=pavgATBuscas.stQBPSearchElapsedPre;
               if(pavgATBuscas.stQBPSearchElapsedPro>tSearchElapsedMax)tSearchElapsedMax=pavgATBuscas.stQBPSearchElapsedPro;
               if(pavgATBuscas.stQBPSearchElapsedPos>tSearchElapsedMax)tSearchElapsedMax=pavgATBuscas.stQBPSearchElapsedPos;
            }
        }break;
        }
    }

    //Cria o Grafico das medias
    QBarSeries *series = new QBarSeries(chart);

    for (int i=0;i<4;i++)
    {
        switch(i)
        {
        case QBP_MATRIX_TYPE_ORIGIN:
        {
            tSearchName = "SW";
            tSearchElapsed    = pavgSWBuscas.stQBPSearchElapsed;
            tSearchElapsedPre = pavgSWBuscas.stQBPSearchElapsedPre;
            tSearchElapsedPro = pavgSWBuscas.stQBPSearchElapsedPro;
            tSearchElapsedPos = pavgSWBuscas.stQBPSearchElapsedPos;

            CQBPLogQueue::Push(QString("Busca : ") + tSearchName + " ");
            CQBPLogQueue::Push(QString("Elapsed : %1 PreProcess: %2 Process: %3 PosProcess: %4\n").arg(tSearchElapsed).arg(tSearchElapsedPre).arg(tSearchElapsedPro).arg(tSearchElapsedPos));

            //create the unique bar set(can be more in future)
            QBarSet *set = new QBarSet(tSearchName);

            *set << tSearchElapsed << tSearchElapsedPre << tSearchElapsedPro << tSearchElapsedPos;
            //for stacked bar just create another loop with a new set and append...
            series->append(set);
        }break;
        case QBP_MATRIX_TYPE_MUSSUM:
        {
            tSearchName = "Mussum";
            tSearchElapsed    = pavgMSBuscas.stQBPSearchElapsed;
            tSearchElapsedPre = pavgMSBuscas.stQBPSearchElapsedPre;
            tSearchElapsedPro = pavgMSBuscas.stQBPSearchElapsedPro;
            tSearchElapsedPos = pavgMSBuscas.stQBPSearchElapsedPos;

            CQBPLogQueue::Push(QString("Busca : ") + tSearchName + " ");
            CQBPLogQueue::Push(QString("Elapsed : %1 PreProcess: %2 Process: %3 PosProcess: %4\n").arg(tSearchElapsed).arg(tSearchElapsedPre).arg(tSearchElapsedPro).arg(tSearchElapsedPos));

            //create the unique bar set(can be more in future)
            QBarSet *set = new QBarSet(tSearchName);

            *set << tSearchElapsed << tSearchElapsedPre << tSearchElapsedPro << tSearchElapsedPos;
            //for stacked bar just create another loop with a new set and append...
            series->append(set);
        }break;
        case QBP_MATRIX_TYPE_MUSSIX:
        {
            tSearchName = "Mussix";
            tSearchElapsed    = pavgMXBuscas.stQBPSearchElapsed;
            tSearchElapsedPre = pavgMXBuscas.stQBPSearchElapsedPre;
            tSearchElapsedPro = pavgMXBuscas.stQBPSearchElapsedPro;
            tSearchElapsedPos = pavgMXBuscas.stQBPSearchElapsedPos;

            CQBPLogQueue::Push(QString("Busca : ") + tSearchName + " ");
            CQBPLogQueue::Push(QString("Elapsed : %1 PreProcess: %2 Process: %3 PosProcess: %4\n").arg(tSearchElapsed).arg(tSearchElapsedPre).arg(tSearchElapsedPro).arg(tSearchElapsedPos));

            //create the unique bar set(can be more in future)
            QBarSet *set = new QBarSet(tSearchName);

            *set << tSearchElapsed << tSearchElapsedPre << tSearchElapsedPro << tSearchElapsedPos;
            //for stacked bar just create another loop with a new set and append...
            series->append(set);
        }break;
        case QBP_MATRIX_TYPE_MUSSAT:
        {
            tSearchName = "Attitude-Gram";
            tSearchElapsed    = pavgATBuscas.stQBPSearchElapsed;
            tSearchElapsedPre = pavgATBuscas.stQBPSearchElapsedPre;
            tSearchElapsedPro = pavgATBuscas.stQBPSearchElapsedPro;
            tSearchElapsedPos = pavgATBuscas.stQBPSearchElapsedPos;

            CQBPLogQueue::Push(QString("Busca : ") + tSearchName + " ");
            CQBPLogQueue::Push(QString("Elapsed : %1 PreProcess: %2 Process: %3 PosProcess: %4\n").arg(tSearchElapsed).arg(tSearchElapsedPre).arg(tSearchElapsedPro).arg(tSearchElapsedPos));

            //create the unique bar set(can be more in future)
            QBarSet *set = new QBarSet(tSearchName);

            *set << tSearchElapsed << tSearchElapsedPre << tSearchElapsedPro << tSearchElapsedPos;
            //for stacked bar just create another loop with a new set and append...
            series->append(set);
        }break;
        }
    }


    QStringList categories;
    categories << "Total" << "Pre-Process" << "Process" << "Post-Process";
    QBarCategoryAxis *axis = new QBarCategoryAxis();
    axis->append(categories);

    chart->addSeries(series);
    chart->createDefaultAxes();
    chart->axisY()->setRange(0,tSearchElapsedMax);
    chart->setAxisX(axis, series);
    // Add space to label to add space between labels and axis
    static_cast<QValueAxis *>(chart->axisY())->setLabelFormat("%.2f  ");

    CQBPLogQueue::Push(QString("=========================================\n"));

    return chart;
}

QChart *CQBPTabPageCharts::createFmeasureAverageByType(int pQBP_ReportType)
{
    QChart *chart = new QChart();
    chart->setTitle("Mean Metrics Report");

    CQBPLogQueue::Push(QString("=================================================================\n"));
    CQBPLogQueue::Push(QString("Relatório Precision , Recall , FMeasure , Accuracy , MRR , MSCD  \n"));
    CQBPLogQueue::Push(QString("=================================================================\n"));

    QString tSearchName;
    double  tPrecision;
    double  tRecall;
    double  tFMeasure;
    double  tAccuracy;
    double  tReciprocalRank;
    double  tMeanScoreContour;


    ExtractSearchsByType(pQBP_ReportType);

    //Calcula as medias por tipo de busca
    for (int i=0;i<4;i++)
    {
        switch(i)
        {
        case QBP_MATRIX_TYPE_ORIGIN:
        {
            pavgSWBuscas.stQBPSearchName       ="SW";
            pavgSWBuscas.stQBPPrecision        =0;
            pavgSWBuscas.stQBPRecall           =0;
            pavgSWBuscas.stQBPFmeasure         =0;
            pavgSWBuscas.stQBPAccuracy         =0;
            pavgSWBuscas.stQBPReciprocalRank   =0;
            pavgSWBuscas.stQBPMSCD             =0;
            if(pSWBuscas.size()>0)
            {
               for (uint j=0;j<pSWBuscas.size();j++)
               {
                   pavgSWBuscas.stQBPPrecision        += pSWBuscas[j].stQBPPrecision;
                   pavgSWBuscas.stQBPRecall           += pSWBuscas[j].stQBPRecall;
                   pavgSWBuscas.stQBPFmeasure         += pSWBuscas[j].stQBPFmeasure;
                   pavgSWBuscas.stQBPAccuracy         += pSWBuscas[j].stQBPAccuracy;
                   pavgSWBuscas.stQBPReciprocalRank   += pSWBuscas[j].stQBPReciprocalRank;
                   pavgSWBuscas.stQBPMSCD             += pSWBuscas[j].stQBPMSCD;
               }

               pavgSWBuscas.stQBPPrecision        =pavgSWBuscas.stQBPPrecision        /(uint)pSWBuscas.size();
               pavgSWBuscas.stQBPRecall           =pavgSWBuscas.stQBPRecall           /(uint)pSWBuscas.size();
               pavgSWBuscas.stQBPFmeasure         =pavgSWBuscas.stQBPFmeasure         /(uint)pSWBuscas.size();
               pavgSWBuscas.stQBPAccuracy         =pavgSWBuscas.stQBPAccuracy         /(uint)pSWBuscas.size();
               pavgSWBuscas.stQBPReciprocalRank   =pavgSWBuscas.stQBPReciprocalRank   /(uint)pSWBuscas.size();
               pavgSWBuscas.stQBPMSCD             =pavgSWBuscas.stQBPMSCD /(uint)pSWBuscas.size();
            }
        }break;
        case QBP_MATRIX_TYPE_MUSSUM:
        {
            pavgMSBuscas.stQBPSearchName       ="Mussum";
            pavgMSBuscas.stQBPPrecision        =0;
            pavgMSBuscas.stQBPRecall           =0;
            pavgMSBuscas.stQBPFmeasure         =0;
            pavgMSBuscas.stQBPAccuracy         =0;
            pavgMSBuscas.stQBPReciprocalRank   =0;
            pavgMSBuscas.stQBPMSCD             =0;

            if(pMSBuscas.size()>0)
            {
               for (uint j=0;j<pMSBuscas.size();j++)
               {
                   pavgMSBuscas.stQBPPrecision += pMSBuscas[j].stQBPPrecision;
                   pavgMSBuscas.stQBPRecall    += pMSBuscas[j].stQBPRecall;
                   pavgMSBuscas.stQBPFmeasure  += pMSBuscas[j].stQBPFmeasure;
                   pavgMSBuscas.stQBPAccuracy  += pMSBuscas[j].stQBPAccuracy;
                   pavgMSBuscas.stQBPReciprocalRank  += pMSBuscas[j].stQBPReciprocalRank;
                   pavgMSBuscas.stQBPMSCD  += pMSBuscas[j].stQBPMSCD;
               }

               pavgMSBuscas.stQBPPrecision =pavgMSBuscas.stQBPPrecision/(uint)pMSBuscas.size();
               pavgMSBuscas.stQBPRecall    =pavgMSBuscas.stQBPRecall   /(uint)pMSBuscas.size();
               pavgMSBuscas.stQBPFmeasure  =pavgMSBuscas.stQBPFmeasure /(uint)pMSBuscas.size();
               pavgMSBuscas.stQBPAccuracy  =pavgMSBuscas.stQBPAccuracy /(uint)pMSBuscas.size();
               pavgMSBuscas.stQBPReciprocalRank  =pavgMSBuscas.stQBPReciprocalRank /(uint)pMSBuscas.size();
               pavgMSBuscas.stQBPMSCD  =pavgMSBuscas.stQBPMSCD /(uint)pMSBuscas.size();
            }
        }break;
        case QBP_MATRIX_TYPE_MUSSIX:
        {
            pavgMXBuscas.stQBPSearchName       ="Mussix";
            pavgMXBuscas.stQBPPrecision        =0;
            pavgMXBuscas.stQBPRecall           =0;
            pavgMXBuscas.stQBPFmeasure         =0;
            pavgMXBuscas.stQBPAccuracy         =0;
            pavgMXBuscas.stQBPReciprocalRank   =0;
            pavgMXBuscas.stQBPMSCD =0;

            if(pMXBuscas.size()>0)
            {
               for (uint j=0;j<pMXBuscas.size();j++)
               {
                   pavgMXBuscas.stQBPPrecision += pMXBuscas[j].stQBPPrecision;
                   pavgMXBuscas.stQBPRecall    += pMXBuscas[j].stQBPRecall;
                   pavgMXBuscas.stQBPFmeasure  += pMXBuscas[j].stQBPFmeasure;
                   pavgMXBuscas.stQBPAccuracy  += pMXBuscas[j].stQBPAccuracy;
                   pavgMXBuscas.stQBPReciprocalRank  += pMXBuscas[j].stQBPReciprocalRank;
                   pavgMXBuscas.stQBPMSCD  += pMXBuscas[j].stQBPMSCD;
               }

               pavgMXBuscas.stQBPPrecision =pavgMXBuscas.stQBPPrecision/(uint)pMXBuscas.size();
               pavgMXBuscas.stQBPRecall    =pavgMXBuscas.stQBPRecall   /(uint)pMXBuscas.size();
               pavgMXBuscas.stQBPFmeasure  =pavgMXBuscas.stQBPFmeasure /(uint)pMXBuscas.size();
               pavgMXBuscas.stQBPAccuracy  =pavgMXBuscas.stQBPAccuracy /(uint)pMXBuscas.size();
               pavgMXBuscas.stQBPReciprocalRank  =pavgMXBuscas.stQBPReciprocalRank /(uint)pMXBuscas.size();
               pavgMXBuscas.stQBPMSCD  =pavgMXBuscas.stQBPMSCD /(uint)pMXBuscas.size();
            }
        }break;
        case QBP_MATRIX_TYPE_MUSSAT:
        {
            pavgATBuscas.stQBPSearchName       ="Attitude-Gram";
            pavgATBuscas.stQBPPrecision        =0;
            pavgATBuscas.stQBPRecall           =0;
            pavgATBuscas.stQBPFmeasure         =0;
            pavgATBuscas.stQBPAccuracy         =0;
            pavgATBuscas.stQBPReciprocalRank   =0;
            pavgATBuscas.stQBPMSCD =0;

            if(pATBuscas.size()>0)
            {
               for (uint j=0;j<pATBuscas.size();j++)
               {
                   pavgATBuscas.stQBPPrecision += pATBuscas[j].stQBPPrecision;
                   pavgATBuscas.stQBPRecall    += pATBuscas[j].stQBPRecall;
                   pavgATBuscas.stQBPFmeasure  += pATBuscas[j].stQBPFmeasure;
                   pavgATBuscas.stQBPAccuracy  += pATBuscas[j].stQBPAccuracy;
                   pavgATBuscas.stQBPReciprocalRank  += pATBuscas[j].stQBPReciprocalRank;
                   pavgATBuscas.stQBPMSCD  += pATBuscas[j].stQBPMSCD;
               }

               pavgATBuscas.stQBPPrecision =pavgATBuscas.stQBPPrecision/(uint)pATBuscas.size();
               pavgATBuscas.stQBPRecall    =pavgATBuscas.stQBPRecall   /(uint)pATBuscas.size();
               pavgATBuscas.stQBPFmeasure  =pavgATBuscas.stQBPFmeasure /(uint)pATBuscas.size();
               pavgATBuscas.stQBPAccuracy  =pavgATBuscas.stQBPAccuracy /(uint)pATBuscas.size();
               pavgATBuscas.stQBPReciprocalRank  =pavgATBuscas.stQBPReciprocalRank /(uint)pATBuscas.size();
               pavgATBuscas.stQBPMSCD  =pavgATBuscas.stQBPMSCD /(uint)pATBuscas.size();
            }
        }break;
        }
    }

    //Cria o Grafico das medias
    QBarSeries *series = new QBarSeries(chart);

    for (int i=0;i<4;i++)
    {
        switch(i)
        {
        case QBP_MATRIX_TYPE_ORIGIN:
        {
            tSearchName = pavgSWBuscas.stQBPSearchName;
            tPrecision  = pavgSWBuscas.stQBPPrecision;
            tRecall     = pavgSWBuscas.stQBPRecall;
            tFMeasure   = pavgSWBuscas.stQBPFmeasure;
            tAccuracy   = pavgSWBuscas.stQBPAccuracy;
            tReciprocalRank   = pavgSWBuscas.stQBPReciprocalRank;
            tMeanScoreContour = pavgSWBuscas.stQBPMSCD;

            CQBPLogQueue::Push(QString("Busca : ") + tSearchName + " ");
            CQBPLogQueue::Push(QString("Precision : %1 Recall: %2 FMeasure: %3 Accuracy: %4 MRR: %5 MSCD: %6 \n")
                               .arg(tPrecision)
                               .arg(tRecall)
                               .arg(tFMeasure)
                               .arg(tAccuracy)
                               .arg(tReciprocalRank)
                               .arg(tMeanScoreContour));

            //create the unique bar set(can be more in future)
            QBarSet *set = new QBarSet(tSearchName);

            *set << tPrecision << tRecall << tFMeasure << tAccuracy << tReciprocalRank << tMeanScoreContour;
            //for stacked bar just create another loop with a new set and append...
            series->append(set);
        }break;
        case QBP_MATRIX_TYPE_MUSSUM:
        {
            tSearchName = pavgMSBuscas.stQBPSearchName;
            tPrecision  = pavgMSBuscas.stQBPPrecision;
            tRecall     = pavgMSBuscas.stQBPRecall;
            tFMeasure   = pavgMSBuscas.stQBPFmeasure;
            tAccuracy   = pavgMSBuscas.stQBPAccuracy;
            tReciprocalRank   = pavgMSBuscas.stQBPReciprocalRank;
            tMeanScoreContour = pavgMSBuscas.stQBPMSCD;

            CQBPLogQueue::Push(QString("Busca : ") + tSearchName + " ");
            CQBPLogQueue::Push(QString("Precision : %1 Recall: %2 FMeasure: %3 Accuracy: %4 MRR: %5 MSCD: %6 \n")
                               .arg(tPrecision)
                               .arg(tRecall)
                               .arg(tFMeasure)
                               .arg(tAccuracy)
                               .arg(tReciprocalRank)
                               .arg(tMeanScoreContour));

            //create the unique bar set(can be more in future)
            QBarSet *set = new QBarSet(tSearchName);

            *set << tPrecision << tRecall << tFMeasure << tAccuracy << tReciprocalRank << tMeanScoreContour;
            //for stacked bar just create another loop with a new set and append...
            series->append(set);
        }break;
        case QBP_MATRIX_TYPE_MUSSIX:
        {
            tSearchName = pavgMXBuscas.stQBPSearchName;
            tPrecision  = pavgMXBuscas.stQBPPrecision;
            tRecall     = pavgMXBuscas.stQBPRecall;
            tFMeasure   = pavgMXBuscas.stQBPFmeasure;
            tAccuracy   = pavgMXBuscas.stQBPAccuracy;
            tReciprocalRank   = pavgMXBuscas.stQBPReciprocalRank;
            tMeanScoreContour = pavgMXBuscas.stQBPMSCD;

            CQBPLogQueue::Push(QString("Busca : ") + tSearchName + " ");
            CQBPLogQueue::Push(QString("Precision : %1 Recall: %2 FMeasure: %3 Accuracy: %4 MRR: %5 MSCD: %6 \n")
                               .arg(tPrecision)
                               .arg(tRecall)
                               .arg(tFMeasure)
                               .arg(tAccuracy)
                               .arg(tReciprocalRank)
                               .arg(tMeanScoreContour));

            //create the unique bar set(can be more in future)
            QBarSet *set = new QBarSet(tSearchName);

            *set << tPrecision << tRecall << tFMeasure << tAccuracy << tReciprocalRank << tMeanScoreContour;
            //for stacked bar just create another loop with a new set and append...
            series->append(set);
        }break;
        case QBP_MATRIX_TYPE_MUSSAT:
        {
            tSearchName = pavgATBuscas.stQBPSearchName;
            tPrecision  = pavgATBuscas.stQBPPrecision;
            tRecall     = pavgATBuscas.stQBPRecall;
            tFMeasure   = pavgATBuscas.stQBPFmeasure;
            tAccuracy   = pavgATBuscas.stQBPAccuracy;
            tReciprocalRank   = pavgATBuscas.stQBPReciprocalRank;
            tMeanScoreContour = pavgATBuscas.stQBPMSCD;

            CQBPLogQueue::Push(QString("Busca : ") + tSearchName + " ");
            CQBPLogQueue::Push(QString("Precision : %1 Recall: %2 FMeasure: %3 Accuracy: %4 MRR: %5 MSCD: %6 \n")
                               .arg(tPrecision)
                               .arg(tRecall)
                               .arg(tFMeasure)
                               .arg(tAccuracy)
                               .arg(tReciprocalRank)
                               .arg(tMeanScoreContour));

            //create the unique bar set(can be more in future)
            QBarSet *set = new QBarSet(tSearchName);

            *set << tPrecision << tRecall << tFMeasure << tAccuracy << tReciprocalRank << tMeanScoreContour;
            //for stacked bar just create another loop with a new set and append...
            series->append(set);
        }break;
        }
    }


    QStringList categories;
    categories << "Precision" << "Recall" << "FMeasure" << "Accuracy" << "MRR" << "MSCD";
    QBarCategoryAxis *axis = new QBarCategoryAxis();
    axis->append(categories);

    chart->addSeries(series);
    chart->createDefaultAxes();
    chart->axisY()->setRange(0,1);
    chart->setAxisX(axis, series);
    // Add space to label to add space between labels and axis
    static_cast<QValueAxis *>(chart->axisY())->setLabelFormat("%.4f  ");

    CQBPLogQueue::Push(QString("=========================================\n"));

    return chart;
}

QChart *CQBPTabPageCharts::createAccuracyByPrecision(int pQBP_ReportType)
{

    QString tSearchName;

    ExtractSearchsByType(pQBP_ReportType);

    /****************************************************************/
    /*Agora que temos todas as listas quebradas vamos ao report     */
    /****************************************************************/
    QChart *chart = new QChart();
    chart->setTitle("Accuracy by Precision Balance");

    for (int i=0;i<4;i++)
    {
        switch(i)
        {
        case QBP_MATRIX_TYPE_ORIGIN:
        {
            if(pSWBuscasMedias.size()>0)
            {
               //Cria uma serie nova
               QLineSeries *series = new QLineSeries();
               series->setName("SW");
               for (int j=0;j<pSWBuscasMedias.size();j++)
               {
                  series->append(pSWBuscasMedias[j].stQBPPrecisionBalance,pSWBuscasMedias[j].stQBPAccuracy);
               }

               chart->addSeries(series);
            }
        }break;
        case QBP_MATRIX_TYPE_MUSSUM:
        {
            if(pMSBuscasMedias.size()>0)
            {
               //Cria uma serie nova
               QLineSeries *series = new QLineSeries();
               series->setName("MUSSUM");
               for (int j=0;j<pMSBuscasMedias.size();j++)
               {
                  series->append(pMSBuscasMedias[j].stQBPPrecisionBalance,pMSBuscasMedias[j].stQBPAccuracy);
               }

               chart->addSeries(series);
            }
        }break;
        case QBP_MATRIX_TYPE_MUSSIX:
        {
            if(pMXBuscasMedias.size()>0)
            {
               //Cria uma serie nova
               QLineSeries *series = new QLineSeries();
               series->setName("MUSSIX");
               for (int j=0;j<pMXBuscasMedias.size();j++)
               {
                  series->append(pMXBuscasMedias[j].stQBPPrecisionBalance,pMXBuscasMedias[j].stQBPAccuracy);
               }

               chart->addSeries(series);
            }
        }break;
        case QBP_MATRIX_TYPE_MUSSAT:
        {
            if(pATBuscasMedias.size()>0)
            {
               //Cria uma serie nova
               QLineSeries *series = new QLineSeries();
               series->setName("Attitude-Gram");
               for (int j=0;j<pATBuscasMedias.size();j++)
               {
                  series->append(pATBuscasMedias[j].stQBPPrecisionBalance,pATBuscasMedias[j].stQBPAccuracy);
               }

               chart->addSeries(series);
            }
        }break;
        }
    }

    chart->createDefaultAxes();
    chart->axisX()->setRange(0, 100);
    chart->axisX()->setTitleText("Precision Balance");
    static_cast<QValueAxis *>(chart->axisX())->setTickCount(11);

    chart->axisY()->setRange(0, 1);
    chart->axisY()->setTitleText("Accuracy");


    // Add space to label to add space between labels and axis
    static_cast<QValueAxis *>(chart->axisY())->setLabelFormat("%.1f  ");
    // Add space to label to add space between labels and axis
    static_cast<QValueAxis *>(chart->axisX())->setLabelFormat("%d  ");


    return chart;
}

QChart *CQBPTabPageCharts::createPrecisionByPrecision(int pQBP_ReportType)
{
    QString tSearchName;

    ExtractSearchsByType(pQBP_ReportType);

    /****************************************************************/
    /*Agora que temos todas as listas quebradas vamos ao report     */
    /****************************************************************/
    QChart *chart = new QChart();
    chart->setTitle("Precision by Precision Balance");

    for (int i=0;i<4;i++)
    {
        switch(i)
        {
        case QBP_MATRIX_TYPE_ORIGIN:
        {
            if(pSWBuscasMedias.size()>0)
            {
               //Cria uma serie nova
               QLineSeries *series = new QLineSeries();
               series->setName("SW");
               for (int j=0;j<pSWBuscasMedias.size();j++)
               {
                  series->append(pSWBuscasMedias[j].stQBPPrecisionBalance,pSWBuscasMedias[j].stQBPPrecision);
               }

               chart->addSeries(series);
            }
        }break;
        case QBP_MATRIX_TYPE_MUSSUM:
        {
            if(pMSBuscasMedias.size()>0)
            {
               //Cria uma serie nova
               QLineSeries *series = new QLineSeries();
               series->setName("MUSSUM");
               for (int j=0;j<pMSBuscasMedias.size();j++)
               {
                  series->append(pMSBuscasMedias[j].stQBPPrecisionBalance,pMSBuscasMedias[j].stQBPPrecision);
               }

               chart->addSeries(series);
            }
        }break;
        case QBP_MATRIX_TYPE_MUSSIX:
        {
            if(pMXBuscas.size()>0)
            {
               //Cria uma serie nova
               QLineSeries *series = new QLineSeries();
               series->setName("MUSSIX");
               for (int j=0;j<pMXBuscasMedias.size();j++)
               {
                  series->append(pMXBuscasMedias[j].stQBPPrecisionBalance,pMXBuscasMedias[j].stQBPPrecision);
               }

               chart->addSeries(series);
            }
        }break;
        case QBP_MATRIX_TYPE_MUSSAT:
        {
            if(pATBuscas.size()>0)
            {
               //Cria uma serie nova
               QLineSeries *series = new QLineSeries();
               series->setName("Attitude-Gram");
               for (int j=0;j<pATBuscasMedias.size();j++)
               {
                  series->append(pATBuscasMedias[j].stQBPPrecisionBalance,pATBuscasMedias[j].stQBPPrecision);
               }

               chart->addSeries(series);
            }
        }break;
        }
    }

    chart->createDefaultAxes();
    chart->axisX()->setRange(0, 100);
    chart->axisX()->setTitleText("Precision Balance");
    static_cast<QValueAxis *>(chart->axisX())->setTickCount(11);

    chart->axisY()->setRange(0, 1);
    chart->axisY()->setTitleText("Precision");


    // Add space to label to add space between labels and axis
    static_cast<QValueAxis *>(chart->axisY())->setLabelFormat("%.1f  ");
    // Add space to label to add space between labels and axis
    static_cast<QValueAxis *>(chart->axisX())->setLabelFormat("%d  ");


    return chart;
}

QChart *CQBPTabPageCharts::createMRRByPrecision(int pQBP_ReportType)
{

    QString tSearchName;


    ExtractSearchsByType(pQBP_ReportType);


    /****************************************************************/
    /*Agora que temos todas as listas quebradas vamos ao report     */
    /****************************************************************/
    QChart *chart = new QChart();
    chart->setTitle("Precision by Precision Balance");

    for (int i=0;i<4;i++)
    {
        switch(i)
        {
        case QBP_MATRIX_TYPE_ORIGIN:
        {
            if(pSWBuscasMedias.size()>0)
            {
               //Cria uma serie nova
               QLineSeries *series = new QLineSeries();
               series->setName("SW");
               for (int j=0;j<pSWBuscasMedias.size();j++)
               {
                  series->append(pSWBuscasMedias[j].stQBPPrecisionBalance,pSWBuscasMedias[j].stQBPReciprocalRank);
               }

               chart->addSeries(series);
            }
        }break;
        case QBP_MATRIX_TYPE_MUSSUM:
        {
            if(pMSBuscasMedias.size()>0)
            {
               //Cria uma serie nova
               QLineSeries *series = new QLineSeries();
               series->setName("MUSSUM");
               for (int j=0;j<pMSBuscasMedias.size();j++)
               {
                  series->append(pMSBuscasMedias[j].stQBPPrecisionBalance,pMSBuscasMedias[j].stQBPReciprocalRank);
               }

               chart->addSeries(series);
            }
        }break;
        case QBP_MATRIX_TYPE_MUSSIX:
        {
            if(pMXBuscas.size()>0)
            {
               //Cria uma serie nova
               QLineSeries *series = new QLineSeries();
               series->setName("MUSSIX");
               for (int j=0;j<pMXBuscasMedias.size();j++)
               {
                  series->append(pMXBuscasMedias[j].stQBPPrecisionBalance,pMXBuscasMedias[j].stQBPReciprocalRank);
               }

               chart->addSeries(series);
            }
        }break;
        case QBP_MATRIX_TYPE_MUSSAT:
        {
            if(pATBuscas.size()>0)
            {
               //Cria uma serie nova
               QLineSeries *series = new QLineSeries();
               series->setName("Attitude-Gram");
               for (int j=0;j<pATBuscasMedias.size();j++)
               {
                  series->append(pATBuscasMedias[j].stQBPPrecisionBalance,pATBuscasMedias[j].stQBPReciprocalRank);
               }

               chart->addSeries(series);
            }
        }break;
        }
    }

    chart->createDefaultAxes();
    chart->axisX()->setRange(0, 100);
    chart->axisX()->setTitleText("Precision Balance");
    static_cast<QValueAxis *>(chart->axisX())->setTickCount(11);

    chart->axisY()->setRange(0, 1);
    chart->axisY()->setTitleText("Precision");


    // Add space to label to add space between labels and axis
    static_cast<QValueAxis *>(chart->axisY())->setLabelFormat("%.1f  ");
    // Add space to label to add space between labels and axis
    static_cast<QValueAxis *>(chart->axisX())->setLabelFormat("%d  ");


    return chart;
}

QChart *CQBPTabPageCharts::createFmeasureByPrecision(int pQBP_ReportType)
{

    QString tSearchName;


    ExtractSearchsByType(pQBP_ReportType);


    /****************************************************************/
    /*Agora que temos todas as listas quebradas vamos ao report     */
    /****************************************************************/
    QChart *chart = new QChart();
    chart->setTitle("Fmeasure by Precision Balance");

    for (int i=0;i<4;i++)
    {
        switch(i)
        {
        case QBP_MATRIX_TYPE_ORIGIN:
        {
            if(pSWBuscasMedias.size()>0)
            {
               //Cria uma serie nova
               QLineSeries *series = new QLineSeries();
               series->setName("SW");
               for (int j=0;j<pSWBuscasMedias.size();j++)
               {
                  series->append(pSWBuscasMedias[j].stQBPPrecisionBalance,pSWBuscasMedias[j].stQBPFmeasure);
               }

               chart->addSeries(series);
            }
        }break;
        case QBP_MATRIX_TYPE_MUSSUM:
        {
            if(pMSBuscasMedias.size()>0)
            {
               //Cria uma serie nova
               QLineSeries *series = new QLineSeries();
               series->setName("MUSSUM");
               for (int j=0;j<pMSBuscasMedias.size();j++)
               {
                  series->append(pMSBuscasMedias[j].stQBPPrecisionBalance,pMSBuscasMedias[j].stQBPFmeasure);
               }

               chart->addSeries(series);
            }
        }break;
        case QBP_MATRIX_TYPE_MUSSIX:
        {
            if(pMXBuscasMedias.size()>0)
            {
               //Cria uma serie nova
               QLineSeries *series = new QLineSeries();
               series->setName("MUSSIX");
               for (int j=0;j<pMXBuscasMedias.size();j++)
               {
                  series->append(pMXBuscasMedias[j].stQBPPrecisionBalance,pMXBuscasMedias[j].stQBPFmeasure);
               }

               chart->addSeries(series);
            }
        }break;
        case QBP_MATRIX_TYPE_MUSSAT:
        {
            if(pATBuscasMedias.size()>0)
            {
               //Cria uma serie nova
               QLineSeries *series = new QLineSeries();
               series->setName("Attitude-Gram");
               for (int j=0;j<pATBuscasMedias.size();j++)
               {
                  series->append(pATBuscasMedias[j].stQBPPrecisionBalance,pATBuscasMedias[j].stQBPFmeasure);
               }

               chart->addSeries(series);
            }
        }break;
        }
    }

    chart->createDefaultAxes();
    chart->axisX()->setRange(0, 100);
    static_cast<QValueAxis *>(chart->axisX())->setTickCount(11);

    chart->axisY()->setRange(0, 1);
    chart->axisY()->setTitleText("Fmeasure");
    chart->axisX()->setTitleText("Precision Balance");

    // Add space to label to add space between labels and axis
    static_cast<QValueAxis *>(chart->axisY())->setLabelFormat("%.1f  ");
    // Add space to label to add space between labels and axis
    static_cast<QValueAxis *>(chart->axisX())->setLabelFormat("%d  ");


    return chart;
}

QChart *CQBPTabPageCharts::createAccuracyByResultSize(int pQBP_ReportType)
{


    QString tSearchName;


    ExtractSearchsByType(pQBP_ReportType);


    /****************************************************************/
    /*Agora que temos todas as listas quebradas vamos ao report     */
    /****************************************************************/
    QChart *chart = new QChart();
    chart->setTitle("Accuracy by ResultSize Balance");

    for (int i=0;i<4;i++)
    {
        switch(i)
        {
        case QBP_MATRIX_TYPE_ORIGIN:
        {
            if(pSWBuscasMedias.size()>0)
            {
               //Cria uma serie nova
               QLineSeries *series = new QLineSeries();
               series->setName("SW");
               for (int j=0;j<pSWBuscasMedias.size();j++)
               {
                  series->append(pSWBuscasMedias[j].stQBPResultSetBalance,pSWBuscasMedias[j].stQBPAccuracy);
               }

               chart->addSeries(series);
            }
        }break;
        case QBP_MATRIX_TYPE_MUSSUM:
        {
            if(pMSBuscasMedias.size()>0)
            {
               //Cria uma serie nova
               QLineSeries *series = new QLineSeries();
               series->setName("MUSSUM");
               for (int j=0;j<pMSBuscasMedias.size();j++)
               {
                  series->append(pMSBuscasMedias[j].stQBPResultSetBalance,pMSBuscasMedias[j].stQBPAccuracy);
               }

               chart->addSeries(series);
            }
        }break;
        case QBP_MATRIX_TYPE_MUSSIX:
        {
            if(pMXBuscasMedias.size()>0)
            {
               //Cria uma serie nova
               QLineSeries *series = new QLineSeries();
               series->setName("MUSSIX");
               for (int j=0;j<pMXBuscasMedias.size();j++)
               {
                  series->append(pMXBuscasMedias[j].stQBPResultSetBalance,pMXBuscasMedias[j].stQBPAccuracy);
               }

               chart->addSeries(series);
            }
        }break;
        case QBP_MATRIX_TYPE_MUSSAT:
        {
            if(pATBuscasMedias.size()>0)
            {
               //Cria uma serie nova
               QLineSeries *series = new QLineSeries();
               series->setName("Attitude-Gram");
               for (int j=0;j<pATBuscas.size();j++)
               {
                  series->append(pATBuscasMedias[j].stQBPResultSetBalance,pATBuscasMedias[j].stQBPAccuracy);
               }

               chart->addSeries(series);
            }
        }break;
        }
    }

    chart->createDefaultAxes();
    chart->axisX()->setRange(20 , 100);
    chart->axisX()->setTitleText("ResultSize Balance");
    static_cast<QValueAxis *>(chart->axisX())->setTickCount(11);

    chart->axisY()->setRange(0, 1);
    chart->axisY()->setTitleText("Accuracy");


    // Add space to label to add space between labels and axis
    static_cast<QValueAxis *>(chart->axisY())->setLabelFormat("%.1f  ");
    // Add space to label to add space between labels and axis
    static_cast<QValueAxis *>(chart->axisX())->setLabelFormat("%d  ");


    return chart;
}

QChart *CQBPTabPageCharts::createPrecisionByResultSize(int pQBP_ReportType)
{


    QString tSearchName;


    ExtractSearchsByType(pQBP_ReportType);


    /****************************************************************/
    /*Agora que temos todas as listas quebradas vamos ao report     */
    /****************************************************************/
    QChart *chart = new QChart();
    chart->setTitle("Precision by ResultSize Balance");

    for (int i=0;i<4;i++)
    {
        switch(i)
        {
        case QBP_MATRIX_TYPE_ORIGIN:
        {
            if(pSWBuscasMedias.size()>0)
            {
               //Cria uma serie nova
               QLineSeries *series = new QLineSeries();
               series->setName("SW");
               for (int j=0;j<pSWBuscasMedias.size();j++)
               {
                  series->append(pSWBuscasMedias[j].stQBPResultSetBalance,pSWBuscasMedias[j].stQBPPrecision);
               }

               chart->addSeries(series);
            }
        }break;
        case QBP_MATRIX_TYPE_MUSSUM:
        {
            if(pMSBuscasMedias.size()>0)
            {
               //Cria uma serie nova
               QLineSeries *series = new QLineSeries();
               series->setName("MUSSUM");
               for (int j=0;j<pMSBuscasMedias.size();j++)
               {
                  series->append(pMSBuscasMedias[j].stQBPResultSetBalance,pMSBuscasMedias[j].stQBPPrecision);
               }

               chart->addSeries(series);
            }
        }break;
        case QBP_MATRIX_TYPE_MUSSIX:
        {
            if(pMXBuscasMedias.size()>0)
            {
               //Cria uma serie nova
               QLineSeries *series = new QLineSeries();
               series->setName("MUSSIX");
               for (int j=0;j<pMXBuscasMedias.size();j++)
               {
                  series->append(pMXBuscasMedias[j].stQBPResultSetBalance,pMXBuscasMedias[j].stQBPPrecision);
               }

               chart->addSeries(series);
            }
        }break;
        case QBP_MATRIX_TYPE_MUSSAT:
        {
            if(pATBuscasMedias.size()>0)
            {
               //Cria uma serie nova
               QLineSeries *series = new QLineSeries();
               series->setName("Attitude-Gram");
               for (int j=0;j<pATBuscasMedias.size();j++)
               {
                  series->append(pATBuscasMedias[j].stQBPResultSetBalance,pATBuscasMedias[j].stQBPPrecision);
               }

               chart->addSeries(series);
            }
        }break;
        }
    }

    chart->createDefaultAxes();
    chart->axisX()->setRange(20 , 100);
    chart->axisX()->setTitleText("ResultSize Balance");
    static_cast<QValueAxis *>(chart->axisX())->setTickCount(11);

    chart->axisY()->setRange(0, 1);
    chart->axisY()->setTitleText("Precision");


    // Add space to label to add space between labels and axis
    static_cast<QValueAxis *>(chart->axisY())->setLabelFormat("%.1f  ");
    // Add space to label to add space between labels and axis
    static_cast<QValueAxis *>(chart->axisX())->setLabelFormat("%d  ");


    return chart;
}

QChart *CQBPTabPageCharts::createMRRByResultSize(int pQBP_ReportType)
{

    QString tSearchName;

    ExtractSearchsByType(pQBP_ReportType);

    /****************************************************************/
    /*Agora que temos todas as listas quebradas vamos ao report     */
    /****************************************************************/
    QChart *chart = new QChart();
    chart->setTitle("Precision by ResultSize Balance");

    for (int i=0;i<4;i++)
    {
        switch(i)
        {
        case QBP_MATRIX_TYPE_ORIGIN:
        {
            if(pSWBuscasMedias.size()>0)
            {
               //Cria uma serie nova
               QLineSeries *series = new QLineSeries();
               series->setName("SW");
               for (int j=0;j<pSWBuscasMedias.size();j++)
               {
                  series->append(pSWBuscasMedias[j].stQBPResultSetBalance,(float)pSWBuscasMedias[j].stQBPReciprocalRank);
               }

               chart->addSeries(series);
            }
        }break;
        case QBP_MATRIX_TYPE_MUSSUM:
        {
            if(pMSBuscasMedias.size()>0)
            {
               //Cria uma serie nova
               QLineSeries *series = new QLineSeries();
               series->setName("MUSSUM");
               for (int j=0;j<pMSBuscasMedias.size();j++)
               {
                  series->append(pMSBuscasMedias[j].stQBPResultSetBalance,(float)pMSBuscasMedias[j].stQBPReciprocalRank);
               }

               chart->addSeries(series);
            }
        }break;
        case QBP_MATRIX_TYPE_MUSSIX:
        {
            if(pMXBuscasMedias.size()>0)
            {
               //Cria uma serie nova
               QLineSeries *series = new QLineSeries();
               series->setName("MUSSIX");
               for (int j=0;j<pMXBuscasMedias.size();j++)
               {
                  series->append(pMXBuscasMedias[j].stQBPResultSetBalance,(float)pMXBuscasMedias[j].stQBPReciprocalRank);
               }

               chart->addSeries(series);
            }
        }break;
        case QBP_MATRIX_TYPE_MUSSAT:
        {
            if(pATBuscasMedias.size()>0)
            {
               //Cria uma serie nova
               QLineSeries *series = new QLineSeries();
               series->setName("Attitude-Gram");
               for (int j=0;j<pATBuscasMedias.size();j++)
               {
                  series->append(pATBuscasMedias[j].stQBPResultSetBalance,(float)pATBuscasMedias[j].stQBPReciprocalRank);
               }

               chart->addSeries(series);
            }
        }break;
        }
    }

    chart->createDefaultAxes();
    chart->axisX()->setRange(20 , 100);
    chart->axisX()->setTitleText("ResultSize Balance");
    static_cast<QValueAxis *>(chart->axisX())->setTickCount(11);

    chart->axisY()->setRange(0, 1);
    chart->axisY()->setTitleText("Precision");


    // Add space to label to add space between labels and axis
    static_cast<QValueAxis *>(chart->axisY())->setLabelFormat("%.1f  ");
    // Add space to label to add space between labels and axis
    static_cast<QValueAxis *>(chart->axisX())->setLabelFormat("%d  ");


    return chart;
}

QChart *CQBPTabPageCharts::createPrecisionByBufferSize(int pQBP_ReportType)
{


    QString tSearchName;

    ExtractSearchsByType(pQBP_ReportType);

    /****************************************************************/
    /*Agora que temos todas as listas quebradas vamos ao report     */
    /****************************************************************/
    QChart *chart = new QChart();
    chart->setTitle("Mean Precision by Buffer Size");

    for (int i=0;i<4;i++)
    {
        switch(i)
        {
        case QBP_MATRIX_TYPE_ORIGIN:
        {
            if(pSWBuscasMedias.size()>0)
            {
               //Cria uma serie nova
               QLineSeries *series = new QLineSeries();
               series->setName("SW");
               for (int j=0;j<pSWBuscasMedias.size();j++)
               {
                  series->append(pSWBuscasMedias[j].stQBPBufferSize,pSWBuscasMedias[j].stQBPPrecision);
               }

               chart->addSeries(series);
            }
        }break;
        case QBP_MATRIX_TYPE_MUSSUM:
        {
            if(pMSBuscasMedias.size()>0)
            {
               //Cria uma serie nova
               QLineSeries *series = new QLineSeries();
               series->setName("MUSSUM");
               for (int j=0;j<pMSBuscasMedias.size();j++)
               {
                  series->append(pMSBuscasMedias[j].stQBPBufferSize,pMSBuscasMedias[j].stQBPPrecision);
               }

               chart->addSeries(series);
            }
        }break;
        case QBP_MATRIX_TYPE_MUSSIX:
        {
            if(pMXBuscasMedias.size()>0)
            {
               //Cria uma serie nova
               QLineSeries *series = new QLineSeries();
               series->setName("MUSSIX");
               for (int j=0;j<pMXBuscasMedias.size();j++)
               {
                  series->append(pMXBuscasMedias[j].stQBPBufferSize,pMXBuscasMedias[j].stQBPPrecision);
               }

               chart->addSeries(series);
            }
        }break;
        case QBP_MATRIX_TYPE_MUSSAT:
        {
            if(pATBuscasMedias.size()>0)
            {
               //Cria uma serie nova
               QLineSeries *series = new QLineSeries();
               series->setName("Attitude-Gram");
               for (int j=0;j<pATBuscasMedias.size();j++)
               {
                  series->append(pATBuscasMedias[j].stQBPBufferSize,pATBuscasMedias[j].stQBPPrecision);
               }

               chart->addSeries(series);
            }
        }break;
        }
    }

    chart->createDefaultAxes();
    chart->axisX()->setRange(10 , 100);
    chart->axisX()->setTitleText("Buffer Size");
    static_cast<QValueAxis *>(chart->axisX())->setTickCount(17);

    chart->axisY()->setRange(0, 1);
    chart->axisY()->setTitleText("Mean Reciprocal Rank");


    // Add space to label to add space between labels and axis
    static_cast<QValueAxis *>(chart->axisY())->setLabelFormat("%.1f  ");
    // Add space to label to add space between labels and axis
    static_cast<QValueAxis *>(chart->axisX())->setLabelFormat("%d  ");


    return chart;
}

QChart *CQBPTabPageCharts::createMRRByBufferSize(int pQBP_ReportType)
{


    QString tSearchName;

    ExtractSearchsByType(pQBP_ReportType);

    /****************************************************************/
    /*Agora que temos todas as listas quebradas vamos ao report     */
    /****************************************************************/
    QChart *chart = new QChart();
    chart->setTitle("Mean Reciprocal Rank by Buffer Size");

    for (int i=0;i<4;i++)
    {
        switch(i)
        {
        case QBP_MATRIX_TYPE_ORIGIN:
        {
            if(pSWBuscasMedias.size()>0)
            {
               //Cria uma serie nova
               QLineSeries *series = new QLineSeries();
               series->setName("SW");
               for (int j=0;j<pSWBuscasMedias.size();j++)
               {
                  series->append(pSWBuscasMedias[j].stQBPBufferSize,pSWBuscasMedias[j].stQBPReciprocalRank);
               }

               chart->addSeries(series);
            }
        }break;
        case QBP_MATRIX_TYPE_MUSSUM:
        {
            if(pMSBuscasMedias.size()>0)
            {
               //Cria uma serie nova
               QLineSeries *series = new QLineSeries();
               series->setName("MUSSUM");
               for (int j=0;j<pMSBuscasMedias.size();j++)
               {
                  series->append(pMSBuscasMedias[j].stQBPBufferSize,pMSBuscasMedias[j].stQBPReciprocalRank);
               }

               chart->addSeries(series);
            }
        }break;
        case QBP_MATRIX_TYPE_MUSSIX:
        {
            if(pMXBuscasMedias.size()>0)
            {
               //Cria uma serie nova
               QLineSeries *series = new QLineSeries();
               series->setName("MUSSIX");
               for (int j=0;j<pMXBuscasMedias.size();j++)
               {
                  series->append(pMXBuscasMedias[j].stQBPBufferSize,pMXBuscasMedias[j].stQBPReciprocalRank);
               }

               chart->addSeries(series);
            }
        }break;
        case QBP_MATRIX_TYPE_MUSSAT:
        {
            if(pATBuscasMedias.size()>0)
            {
               //Cria uma serie nova
               QLineSeries *series = new QLineSeries();
               series->setName("Attitude-Gram");
               for (int j=0;j<pATBuscasMedias.size();j++)
               {
                  series->append(pATBuscasMedias[j].stQBPBufferSize,pATBuscasMedias[j].stQBPReciprocalRank);
               }

               chart->addSeries(series);
            }
        }break;
        }
    }

    chart->createDefaultAxes();
    chart->axisX()->setRange(10 , 100);
    chart->axisX()->setTitleText("Buffer Size");
    static_cast<QValueAxis *>(chart->axisX())->setTickCount(17);

    chart->axisY()->setRange(0, 1);
    chart->axisY()->setTitleText("Mean Reciprocal Rank");


    // Add space to label to add space between labels and axis
    static_cast<QValueAxis *>(chart->axisY())->setLabelFormat("%.1f  ");
    // Add space to label to add space between labels and axis
    static_cast<QValueAxis *>(chart->axisX())->setLabelFormat("%d  ");


    return chart;
}

QChart *CQBPTabPageCharts::createMSCDByBufferSize(int pQBP_ReportType)
{


    QString tSearchName;

    ExtractSearchsByType(pQBP_ReportType);

    /****************************************************************/
    /*Agora que temos todas as listas quebradas vamos ao report     */
    /****************************************************************/
    QChart *chart = new QChart();
    chart->setTitle("Mean Score Contour Distance by Buffer Size");

    for (int i=0;i<4;i++)
    {
        switch(i)
        {
        case QBP_MATRIX_TYPE_ORIGIN:
        {
            if(pSWBuscasMedias.size()>0)
            {
               //Cria uma serie nova
               QLineSeries *series = new QLineSeries();
               series->setName("SW");
               for (int j=0;j<pSWBuscasMedias.size();j++)
               {
                  series->append(pSWBuscasMedias[j].stQBPBufferSize,pSWBuscasMedias[j].stQBPMSCD);
               }

               chart->addSeries(series);
            }
        }break;
        case QBP_MATRIX_TYPE_MUSSUM:
        {
            if(pMSBuscasMedias.size()>0)
            {
               //Cria uma serie nova
               QLineSeries *series = new QLineSeries();
               series->setName("MUSSUM");
               for (int j=0;j<pMSBuscasMedias.size();j++)
               {
                  series->append(pMSBuscasMedias[j].stQBPBufferSize,pMSBuscasMedias[j].stQBPMSCD);
               }

               chart->addSeries(series);
            }
        }break;
        case QBP_MATRIX_TYPE_MUSSIX:
        {
            if(pMXBuscasMedias.size()>0)
            {
               //Cria uma serie nova
               QLineSeries *series = new QLineSeries();
               series->setName("MUSSIX");
               for (int j=0;j<pMXBuscasMedias.size();j++)
               {
                  series->append(pMXBuscasMedias[j].stQBPBufferSize,pMXBuscasMedias[j].stQBPMSCD);
               }

               chart->addSeries(series);
            }
        }break;
        case QBP_MATRIX_TYPE_MUSSAT:
        {
            if(pATBuscasMedias.size()>0)
            {
               //Cria uma serie nova
               QLineSeries *series = new QLineSeries();
               series->setName("Attitude-Gram");
               for (int j=0;j<pATBuscasMedias.size();j++)
               {
                  series->append(pATBuscasMedias[j].stQBPBufferSize,pATBuscasMedias[j].stQBPMSCD);
               }

               chart->addSeries(series);
            }
        }break;
        }
    }

    chart->createDefaultAxes();
    chart->axisX()->setRange(10 , 100);
    chart->axisX()->setTitleText("Buffer Size");
    static_cast<QValueAxis *>(chart->axisX())->setTickCount(17);

    chart->axisY()->setRange(0, 1);
    chart->axisY()->setTitleText("Mean Reciprocal Rank");


    // Add space to label to add space between labels and axis
    static_cast<QValueAxis *>(chart->axisY())->setLabelFormat("%.1f  ");
    // Add space to label to add space between labels and axis
    static_cast<QValueAxis *>(chart->axisX())->setLabelFormat("%d  ");


    return chart;
}

QChart *CQBPTabPageCharts::createFmeasureByResultSize(int pQBP_ReportType)
{

    QString tSearchName;

    ExtractSearchsByType(pQBP_ReportType);

    /****************************************************************/
    /*Agora que temos todas as listas quebradas vamos ao report     */
    /****************************************************************/
    QChart *chart = new QChart();
    chart->setTitle("Fmeasure by Precision Balance");

    for (int i=0;i<4;i++)
    {
        switch(i)
        {
        case QBP_MATRIX_TYPE_ORIGIN:
        {
            if(pSWBuscasMedias.size()>0)
            {
               //Cria uma serie nova
               QLineSeries *series = new QLineSeries();
               series->setName("SW");
               for (int j=0;j<pSWBuscasMedias.size();j++)
               {
                  series->append(pSWBuscasMedias[j].stQBPResultSetBalance,pSWBuscasMedias[j].stQBPFmeasure);
               }

               chart->addSeries(series);
            }
        }break;
        case QBP_MATRIX_TYPE_MUSSUM:
        {
            if(pMSBuscasMedias.size()>0)
            {
               //Cria uma serie nova
               QLineSeries *series = new QLineSeries();
               series->setName("MUSSUM");
               for (int j=0;j<pMSBuscasMedias.size();j++)
               {
                  series->append(pMSBuscasMedias[j].stQBPResultSetBalance,pMSBuscasMedias[j].stQBPFmeasure);
               }

               chart->addSeries(series);
            }
        }break;
        case QBP_MATRIX_TYPE_MUSSIX:
        {
            if(pMXBuscasMedias.size()>0)
            {
               //Cria uma serie nova
               QLineSeries *series = new QLineSeries();
               series->setName("MUSSIX");
               for (int j=0;j<pMXBuscasMedias.size();j++)
               {
                  series->append(pMXBuscasMedias[j].stQBPResultSetBalance,pMXBuscasMedias[j].stQBPFmeasure);
               }

               chart->addSeries(series);
            }
        }break;
        case QBP_MATRIX_TYPE_MUSSAT:
        {
            if(pATBuscasMedias.size()>0)
            {
               //Cria uma serie nova
               QLineSeries *series = new QLineSeries();
               series->setName("Attitude-Gram");
               for (int j=0;j<pATBuscasMedias.size();j++)
               {
                  series->append(pATBuscasMedias[j].stQBPResultSetBalance,pATBuscasMedias[j].stQBPFmeasure);
               }

               chart->addSeries(series);
            }
        }break;
        }
    }

    chart->createDefaultAxes();
    chart->axisX()->setRange(20 , 100);
    static_cast<QValueAxis *>(chart->axisX())->setTickCount(11);

    chart->axisY()->setRange(0, 1);
    chart->axisY()->setTitleText("Fmeasure");
    chart->axisX()->setTitleText("ResultSize Balance");

    // Add space to label to add space between labels and axis
    static_cast<QValueAxis *>(chart->axisY())->setLabelFormat("%.1f  ");
    // Add space to label to add space between labels and axis
    static_cast<QValueAxis *>(chart->axisX())->setLabelFormat("%d  ");


    return chart;
}

/*
void CQBPTabPageCharts::resizeEvent(QResizeEvent *event)
{
    if(pQBPFmeasureAverageByType    ==nullptr ||
       pQBPFmeasureByPrecision      ==nullptr ||
       pQBPAccuracyByPrecision      ==nullptr ||
       pQBPElapsedTimeAverageByType ==nullptr)
    {
        return;
    }

    //Check if the size REeeALLlllY CHANGES (Bug...)
    if(Width == width() && Height==height())return;

    Width  = width();
    Height = height();

    pQBPFmeasureByPrecision     ->setFixedSize(QSize(width() / 2,height() / 2));
    pQBPAccuracyByPrecision     ->setFixedSize(QSize(width() / 2,height() / 2));
    pQBPFmeasureAverageByType   ->setFixedSize(QSize(width() / 2,height() / 2));
    pQBPElapsedTimeAverageByType->setFixedSize(QSize(width() / 2,height() / 2));

}
*/

struct {
    bool operator()(stFileSearch a, stFileSearch b) const
    {
        return a.stQBPResultSetBalance < b.stQBPResultSetBalance;
    }
} QBPResultSizeLess;

struct {
    bool operator()(stFileSearch a, stFileSearch b) const
    {
        return a.stQBPBufferSize < b.stQBPBufferSize;
    }
} QBPBufferSizeLess;

struct {
    bool operator()(stFileSearch a, stFileSearch b) const
    {
        return a.stQBPPrecisionBalance < b.stQBPPrecisionBalance;
    }
} QBPPrecisionBalanceLess;

struct {
    bool operator()(stFileSearch a, stFileSearch b) const
    {
        return a.stQBPSearchElapsed < b.stQBPSearchElapsed;
    }
} QBPTimeLess;

void CQBPTabPageCharts::ExtractSearchsByType(int pQBP_ReportType)
{
    //Calcula os valores MinMax do Contorno de Scores
    for (int i=0;i<FileSearchList.size();i++)
    {
        if(FileSearchList[i].stQBPMSCD > pMaxContour)pMaxContour=FileSearchList[i].stQBPMSCD;
        if(FileSearchList[i].stQBPMSCD < pMinContour)pMinContour=FileSearchList[i].stQBPMSCD;
    }

    //Atualiza valores que precisam ser normalizados
    for (int i=0;i<FileSearchList.size();i++)
    {
        FileSearchList[i].stQBPMSCD =(double)(FileSearchList[i].stQBPMSCD - pMinContour)/(pMaxContour - pMinContour);
    }

    for (int i=0;i<FileSearchList.size();i++)
    {
        stFileSearch tSearch = FileSearchList[i];

        switch(tSearch.stQBPComparatorType)
        {
        case QBP_MATRIX_TYPE_ORIGIN:
        {
            pSWBuscas.push_back(tSearch);
        }break;
        case QBP_MATRIX_TYPE_MUSSUM:
        {
            pMSBuscas.push_back(tSearch);
        }break;
        case QBP_MATRIX_TYPE_MUSSIX:
        {
            pMXBuscas.push_back(tSearch);
        }break;
        case QBP_MATRIX_TYPE_MUSSAT:
        {
            pATBuscas.push_back(tSearch);
        }break;
        }
    }

    //faz o sort pelas Precisões de Balanceamento da lista
    switch(pQBP_ReportType)
    {
    case QBP_BUFFER_TYPE_FMAvgByType:
    {
        std::sort(pSWBuscas.begin(), pSWBuscas.end(), QBPResultSizeLess);
        std::sort(pMSBuscas.begin(), pMSBuscas.end(), QBPResultSizeLess);
        std::sort(pMXBuscas.begin(), pMXBuscas.end(), QBPResultSizeLess);
        std::sort(pATBuscas.begin(), pATBuscas.end(), QBPResultSizeLess);
        CalcHisSearchsByType(pQBP_ReportType);
    }break;
    case QBP_BUFFER_TYPE_ETAvgByType:
    {
        std::sort(pSWBuscas.begin(), pSWBuscas.end(), QBPTimeLess);
        std::sort(pMSBuscas.begin(), pMSBuscas.end(), QBPTimeLess);
        std::sort(pMXBuscas.begin(), pMXBuscas.end(), QBPTimeLess);
        std::sort(pATBuscas.begin(), pATBuscas.end(), QBPTimeLess);
        CalcHisSearchsByType(pQBP_ReportType);
    }break;
    case QBP_BUFFER_TYPE_ACAvgByPrecision:
    {
        std::sort(pSWBuscas.begin(), pSWBuscas.end(), QBPPrecisionBalanceLess);
        std::sort(pMSBuscas.begin(), pMSBuscas.end(), QBPPrecisionBalanceLess);
        std::sort(pMXBuscas.begin(), pMXBuscas.end(), QBPPrecisionBalanceLess);
        std::sort(pATBuscas.begin(), pATBuscas.end(), QBPPrecisionBalanceLess);
        CalcHisSearchsByType(pQBP_ReportType);
    }break;
    case QBP_BUFFER_TYPE_FMAvgByPrecision:
    {
        std::sort(pSWBuscas.begin(), pSWBuscas.end(), QBPPrecisionBalanceLess);
        std::sort(pMSBuscas.begin(), pMSBuscas.end(), QBPPrecisionBalanceLess);
        std::sort(pMXBuscas.begin(), pMXBuscas.end(), QBPPrecisionBalanceLess);
        std::sort(pATBuscas.begin(), pATBuscas.end(), QBPPrecisionBalanceLess);
        CalcHisSearchsByType(pQBP_ReportType);
    }break;
    case QBP_BUFFER_TYPE_PCAvgByPrecision:
    {
        std::sort(pSWBuscas.begin(), pSWBuscas.end(), QBPPrecisionBalanceLess);
        std::sort(pMSBuscas.begin(), pMSBuscas.end(), QBPPrecisionBalanceLess);
        std::sort(pMXBuscas.begin(), pMXBuscas.end(), QBPPrecisionBalanceLess);
        std::sort(pATBuscas.begin(), pATBuscas.end(), QBPPrecisionBalanceLess);
        CalcHisSearchsByType(pQBP_ReportType);
    }break;
    case QBP_BUFFER_TYPE_MRAvgByPrecision:
    {
        std::sort(pSWBuscas.begin(), pSWBuscas.end(), QBPPrecisionBalanceLess);
        std::sort(pMSBuscas.begin(), pMSBuscas.end(), QBPPrecisionBalanceLess);
        std::sort(pMXBuscas.begin(), pMXBuscas.end(), QBPPrecisionBalanceLess);
        std::sort(pATBuscas.begin(), pATBuscas.end(), QBPPrecisionBalanceLess);
        CalcHisSearchsByType(pQBP_ReportType);
    }break;
    case QBP_BUFFER_TYPE_ACAvgByResultSz:
    {
        std::sort(pSWBuscas.begin(), pSWBuscas.end(), QBPResultSizeLess);
        std::sort(pMSBuscas.begin(), pMSBuscas.end(), QBPResultSizeLess);
        std::sort(pMXBuscas.begin(), pMXBuscas.end(), QBPResultSizeLess);
        std::sort(pATBuscas.begin(), pATBuscas.end(), QBPResultSizeLess);
        CalcHisSearchsByType(pQBP_ReportType);
    }break;
    case QBP_BUFFER_TYPE_FMAvgByResultSz:
    {
        std::sort(pSWBuscas.begin(), pSWBuscas.end(), QBPResultSizeLess);
        std::sort(pMSBuscas.begin(), pMSBuscas.end(), QBPResultSizeLess);
        std::sort(pMXBuscas.begin(), pMXBuscas.end(), QBPResultSizeLess);
        std::sort(pATBuscas.begin(), pATBuscas.end(), QBPResultSizeLess);
        CalcHisSearchsByType(pQBP_ReportType);
    }break;
    case QBP_BUFFER_TYPE_PCAvgByResultSz:
    {
        std::sort(pSWBuscas.begin(), pSWBuscas.end(), QBPResultSizeLess);
        std::sort(pMSBuscas.begin(), pMSBuscas.end(), QBPResultSizeLess);
        std::sort(pMXBuscas.begin(), pMXBuscas.end(), QBPResultSizeLess);
        std::sort(pATBuscas.begin(), pATBuscas.end(), QBPResultSizeLess);
        CalcHisSearchsByType(pQBP_ReportType);
    }break;
    case QBP_BUFFER_TYPE_MRAvgByResultSz:
    {
        std::sort(pSWBuscas.begin(), pSWBuscas.end(), QBPResultSizeLess);
        std::sort(pMSBuscas.begin(), pMSBuscas.end(), QBPResultSizeLess);
        std::sort(pMXBuscas.begin(), pMXBuscas.end(), QBPResultSizeLess);
        std::sort(pATBuscas.begin(), pATBuscas.end(), QBPResultSizeLess);
        CalcHisSearchsByType(pQBP_ReportType);
    }break;
    case QBP_BUFFER_TYPE_MRAvgByBufferSz:
    {
        std::sort(pSWBuscas.begin(), pSWBuscas.end(), QBPBufferSizeLess);
        std::sort(pMSBuscas.begin(), pMSBuscas.end(), QBPBufferSizeLess);
        std::sort(pMXBuscas.begin(), pMXBuscas.end(), QBPBufferSizeLess);
        std::sort(pATBuscas.begin(), pATBuscas.end(), QBPBufferSizeLess);
        CalcHisSearchsByType(pQBP_ReportType);
    }break;
    case QBP_BUFFER_TYPE_PCAvgByBufferSz:
    {
        std::sort(pSWBuscas.begin(), pSWBuscas.end(), QBPBufferSizeLess);
        std::sort(pMSBuscas.begin(), pMSBuscas.end(), QBPBufferSizeLess);
        std::sort(pMXBuscas.begin(), pMXBuscas.end(), QBPBufferSizeLess);
        std::sort(pATBuscas.begin(), pATBuscas.end(), QBPBufferSizeLess);
        CalcHisSearchsByType(pQBP_ReportType);
    }break;
    case QBP_BUFFER_TYPE_CDAvgByBufferSz:
    {
        std::sort(pSWBuscas.begin(), pSWBuscas.end(), QBPBufferSizeLess);
        std::sort(pMSBuscas.begin(), pMSBuscas.end(), QBPBufferSizeLess);
        std::sort(pMXBuscas.begin(), pMXBuscas.end(), QBPBufferSizeLess);
        std::sort(pATBuscas.begin(), pATBuscas.end(), QBPBufferSizeLess);
        CalcHisSearchsByType(pQBP_ReportType);
    }break;
    }
}

void CQBPTabPageCharts::CalcHisSearchsByType(int pQBP_ReportType)
{
    //Calcula a media do valor nos casos de repetição
    //Criar Histograma e elimina duplicidades para o SW
    //Por enquanto as variaveis que usam vão de 0 a 100 e nao da problema...VERIFICAR!!!
    pSWDataHistogram.clear();
    pSWDataHistogram.shrink_to_fit();
    pMSDataHistogram.clear();
    pMSDataHistogram.shrink_to_fit();
    pMXDataHistogram.clear();
    pMXDataHistogram.shrink_to_fit();
    pATDataHistogram.clear();
    pATDataHistogram.shrink_to_fit();

    switch(pQBP_ReportType)
    {
    case QBP_BUFFER_TYPE_FMAvgByType:
    {
        for(int i=0 ; i<4 ; i++)pSWDataHistogram.push_back(0);
        for(int i=0 ; i<4 ; i++)pMSDataHistogram.push_back(0);
        for(int i=0 ; i<4 ; i++)pMXDataHistogram.push_back(0);
        for(int i=0 ; i<4 ; i++)pATDataHistogram.push_back(0);
    }break;
    case QBP_BUFFER_TYPE_ETAvgByType:
    {
        for(int i=0 ; i<4 ; i++)pSWDataHistogram.push_back(0);
        for(int i=0 ; i<4 ; i++)pMSDataHistogram.push_back(0);
        for(int i=0 ; i<4 ; i++)pMXDataHistogram.push_back(0);
        for(int i=0 ; i<4 ; i++)pATDataHistogram.push_back(0);
    }break;
    case QBP_BUFFER_TYPE_ACAvgByPrecision:
    {
        for(int i=0 ; i<101 ; i++)pSWDataHistogram.push_back(0);
        for(int i=0 ; i<101 ; i++)pMSDataHistogram.push_back(0);
        for(int i=0 ; i<101 ; i++)pMXDataHistogram.push_back(0);
        for(int i=0 ; i<101 ; i++)pATDataHistogram.push_back(0);
    }break;
    case QBP_BUFFER_TYPE_FMAvgByPrecision:
    {
        for(int i=0 ; i<101 ; i++)pSWDataHistogram.push_back(0);
        for(int i=0 ; i<101 ; i++)pMSDataHistogram.push_back(0);
        for(int i=0 ; i<101 ; i++)pMXDataHistogram.push_back(0);
        for(int i=0 ; i<101 ; i++)pATDataHistogram.push_back(0);
    }break;
    case QBP_BUFFER_TYPE_PCAvgByPrecision:
    {
        for(int i=0 ; i<101 ; i++)pSWDataHistogram.push_back(0);
        for(int i=0 ; i<101 ; i++)pMSDataHistogram.push_back(0);
        for(int i=0 ; i<101 ; i++)pMXDataHistogram.push_back(0);
        for(int i=0 ; i<101 ; i++)pATDataHistogram.push_back(0);
    }break;
    case QBP_BUFFER_TYPE_MRAvgByPrecision:
    {
        for(int i=0 ; i<101 ; i++)pSWDataHistogram.push_back(0);
        for(int i=0 ; i<101 ; i++)pMSDataHistogram.push_back(0);
        for(int i=0 ; i<101 ; i++)pMXDataHistogram.push_back(0);
        for(int i=0 ; i<101 ; i++)pATDataHistogram.push_back(0);
    }break;
    case QBP_BUFFER_TYPE_ACAvgByResultSz:
    {
        for(int i=0 ; i<101 ; i++)pSWDataHistogram.push_back(0);
        for(int i=0 ; i<101 ; i++)pMSDataHistogram.push_back(0);
        for(int i=0 ; i<101 ; i++)pMXDataHistogram.push_back(0);
        for(int i=0 ; i<101 ; i++)pATDataHistogram.push_back(0);
    }break;
    case QBP_BUFFER_TYPE_FMAvgByResultSz:
    {
        for(int i=0 ; i<101 ; i++)pSWDataHistogram.push_back(0);
        for(int i=0 ; i<101 ; i++)pMSDataHistogram.push_back(0);
        for(int i=0 ; i<101 ; i++)pMXDataHistogram.push_back(0);
        for(int i=0 ; i<101 ; i++)pATDataHistogram.push_back(0);
    }break;
    case QBP_BUFFER_TYPE_PCAvgByResultSz:
    {
        for(int i=0 ; i<101 ; i++)pSWDataHistogram.push_back(0);
        for(int i=0 ; i<101 ; i++)pMSDataHistogram.push_back(0);
        for(int i=0 ; i<101 ; i++)pMXDataHistogram.push_back(0);
        for(int i=0 ; i<101 ; i++)pATDataHistogram.push_back(0);
    }break;
    case QBP_BUFFER_TYPE_MRAvgByResultSz:
    {
        for(int i=0 ; i<101 ; i++)pSWDataHistogram.push_back(0);
        for(int i=0 ; i<101 ; i++)pMSDataHistogram.push_back(0);
        for(int i=0 ; i<101 ; i++)pMXDataHistogram.push_back(0);
        for(int i=0 ; i<101 ; i++)pATDataHistogram.push_back(0);
    }break;
    case QBP_BUFFER_TYPE_MRAvgByBufferSz:
    {
        for(int i=0 ; i<101 ; i++)pSWDataHistogram.push_back(0);
        for(int i=0 ; i<101 ; i++)pMSDataHistogram.push_back(0);
        for(int i=0 ; i<101 ; i++)pMXDataHistogram.push_back(0);
        for(int i=0 ; i<101 ; i++)pATDataHistogram.push_back(0);
    }break;
    case QBP_BUFFER_TYPE_PCAvgByBufferSz:
    {
        for(int i=0 ; i<101 ; i++)pSWDataHistogram.push_back(0);
        for(int i=0 ; i<101 ; i++)pMSDataHistogram.push_back(0);
        for(int i=0 ; i<101 ; i++)pMXDataHistogram.push_back(0);
        for(int i=0 ; i<101 ; i++)pATDataHistogram.push_back(0);
    }break;
    case QBP_BUFFER_TYPE_CDAvgByBufferSz:
    {
        for(int i=0 ; i<101 ; i++)pSWDataHistogram.push_back(0);
        for(int i=0 ; i<101 ; i++)pMSDataHistogram.push_back(0);
        for(int i=0 ; i<101 ; i++)pMXDataHistogram.push_back(0);
        for(int i=0 ; i<101 ; i++)pATDataHistogram.push_back(0);
    }break;
    }

    //faz o preenchimento pelas Precisões de Balanceamento da lista
    switch(pQBP_ReportType)
    {
    case QBP_BUFFER_TYPE_FMAvgByType:
    {
        for(int i=0 ; i<pSWBuscas.size();i++)pSWDataHistogram[pSWBuscas[i].stQBPComparatorType]++;
        for(int i=0 ; i<pMSBuscas.size();i++)pMSDataHistogram[pMSBuscas[i].stQBPComparatorType]++;
        for(int i=0 ; i<pMXBuscas.size();i++)pMXDataHistogram[pMXBuscas[i].stQBPComparatorType]++;
        for(int i=0 ; i<pATBuscas.size();i++)pATDataHistogram[pATBuscas[i].stQBPComparatorType]++;
    }break;
    case QBP_BUFFER_TYPE_ETAvgByType:
    {
        for(int i=0 ; i<pSWBuscas.size();i++)pSWDataHistogram[pSWBuscas[i].stQBPComparatorType]++;
        for(int i=0 ; i<pMSBuscas.size();i++)pMSDataHistogram[pMSBuscas[i].stQBPComparatorType]++;
        for(int i=0 ; i<pMXBuscas.size();i++)pMXDataHistogram[pMXBuscas[i].stQBPComparatorType]++;
        for(int i=0 ; i<pATBuscas.size();i++)pATDataHistogram[pATBuscas[i].stQBPComparatorType]++;
    }break;
    case QBP_BUFFER_TYPE_ACAvgByPrecision:
    {
        for(int i=0 ; i<pSWBuscas.size();i++)pSWDataHistogram[pSWBuscas[i].stQBPPrecisionBalance]++;
        for(int i=0 ; i<pMSBuscas.size();i++)pMSDataHistogram[pMSBuscas[i].stQBPPrecisionBalance]++;
        for(int i=0 ; i<pMXBuscas.size();i++)pMXDataHistogram[pMXBuscas[i].stQBPPrecisionBalance]++;
        for(int i=0 ; i<pATBuscas.size();i++)pATDataHistogram[pATBuscas[i].stQBPPrecisionBalance]++;
    }break;
    case QBP_BUFFER_TYPE_FMAvgByPrecision:
    {
        for(int i=0 ; i<pSWBuscas.size();i++)pSWDataHistogram[pSWBuscas[i].stQBPPrecisionBalance]++;
        for(int i=0 ; i<pMSBuscas.size();i++)pMSDataHistogram[pMSBuscas[i].stQBPPrecisionBalance]++;
        for(int i=0 ; i<pMXBuscas.size();i++)pMXDataHistogram[pMXBuscas[i].stQBPPrecisionBalance]++;
        for(int i=0 ; i<pATBuscas.size();i++)pATDataHistogram[pATBuscas[i].stQBPPrecisionBalance]++;
    }break;
    case QBP_BUFFER_TYPE_PCAvgByPrecision:
    {
        for(int i=0 ; i<pSWBuscas.size();i++)pSWDataHistogram[pSWBuscas[i].stQBPPrecisionBalance]++;
        for(int i=0 ; i<pMSBuscas.size();i++)pMSDataHistogram[pMSBuscas[i].stQBPPrecisionBalance]++;
        for(int i=0 ; i<pMXBuscas.size();i++)pMXDataHistogram[pMXBuscas[i].stQBPPrecisionBalance]++;
        for(int i=0 ; i<pATBuscas.size();i++)pATDataHistogram[pATBuscas[i].stQBPPrecisionBalance]++;
    }break;
    case QBP_BUFFER_TYPE_MRAvgByPrecision:
    {
        for(int i=0 ; i<pSWBuscas.size();i++)pSWDataHistogram[pSWBuscas[i].stQBPPrecisionBalance]++;
        for(int i=0 ; i<pMSBuscas.size();i++)pMSDataHistogram[pMSBuscas[i].stQBPPrecisionBalance]++;
        for(int i=0 ; i<pMXBuscas.size();i++)pMXDataHistogram[pMXBuscas[i].stQBPPrecisionBalance]++;
        for(int i=0 ; i<pATBuscas.size();i++)pATDataHistogram[pATBuscas[i].stQBPPrecisionBalance]++;
    }break;
    case QBP_BUFFER_TYPE_ACAvgByResultSz:
    {
        for(int i=0 ; i<pSWBuscas.size();i++)pSWDataHistogram[pSWBuscas[i].stQBPResultSetBalance]++;
        for(int i=0 ; i<pMSBuscas.size();i++)pMSDataHistogram[pMSBuscas[i].stQBPResultSetBalance]++;
        for(int i=0 ; i<pMXBuscas.size();i++)pMXDataHistogram[pMXBuscas[i].stQBPResultSetBalance]++;
        for(int i=0 ; i<pATBuscas.size();i++)pATDataHistogram[pATBuscas[i].stQBPResultSetBalance]++;
    }break;
    case QBP_BUFFER_TYPE_FMAvgByResultSz:
    {
        for(int i=0 ; i<pSWBuscas.size();i++)pSWDataHistogram[pSWBuscas[i].stQBPResultSetBalance]++;
        for(int i=0 ; i<pMSBuscas.size();i++)pMSDataHistogram[pMSBuscas[i].stQBPResultSetBalance]++;
        for(int i=0 ; i<pMXBuscas.size();i++)pMXDataHistogram[pMXBuscas[i].stQBPResultSetBalance]++;
        for(int i=0 ; i<pATBuscas.size();i++)pATDataHistogram[pATBuscas[i].stQBPResultSetBalance]++;
    }break;
    case QBP_BUFFER_TYPE_PCAvgByResultSz:
    {
        for(int i=0 ; i<pSWBuscas.size();i++)pSWDataHistogram[pSWBuscas[i].stQBPResultSetBalance]++;
        for(int i=0 ; i<pMSBuscas.size();i++)pMSDataHistogram[pMSBuscas[i].stQBPResultSetBalance]++;
        for(int i=0 ; i<pMXBuscas.size();i++)pMXDataHistogram[pMXBuscas[i].stQBPResultSetBalance]++;
        for(int i=0 ; i<pATBuscas.size();i++)pATDataHistogram[pATBuscas[i].stQBPResultSetBalance]++;
    }break;
    case QBP_BUFFER_TYPE_MRAvgByResultSz:
    {
        for(int i=0 ; i<pSWBuscas.size();i++)pSWDataHistogram[pSWBuscas[i].stQBPResultSetBalance]++;
        for(int i=0 ; i<pMSBuscas.size();i++)pMSDataHistogram[pMSBuscas[i].stQBPResultSetBalance]++;
        for(int i=0 ; i<pMXBuscas.size();i++)pMXDataHistogram[pMXBuscas[i].stQBPResultSetBalance]++;
        for(int i=0 ; i<pATBuscas.size();i++)pATDataHistogram[pATBuscas[i].stQBPResultSetBalance]++;
    }break;
    case QBP_BUFFER_TYPE_MRAvgByBufferSz:
    {
        for(int i=0 ; i<pSWBuscas.size();i++)pSWDataHistogram[pSWBuscas[i].stQBPBufferSize]++;
        for(int i=0 ; i<pMSBuscas.size();i++)pMSDataHistogram[pMSBuscas[i].stQBPBufferSize]++;
        for(int i=0 ; i<pMXBuscas.size();i++)pMXDataHistogram[pMXBuscas[i].stQBPBufferSize]++;
        for(int i=0 ; i<pATBuscas.size();i++)pATDataHistogram[pATBuscas[i].stQBPBufferSize]++;
    }break;
    case QBP_BUFFER_TYPE_PCAvgByBufferSz:
    {
        for(int i=0 ; i<pSWBuscas.size();i++)pSWDataHistogram[pSWBuscas[i].stQBPBufferSize]++;
        for(int i=0 ; i<pMSBuscas.size();i++)pMSDataHistogram[pMSBuscas[i].stQBPBufferSize]++;
        for(int i=0 ; i<pMXBuscas.size();i++)pMXDataHistogram[pMXBuscas[i].stQBPBufferSize]++;
        for(int i=0 ; i<pATBuscas.size();i++)pATDataHistogram[pATBuscas[i].stQBPBufferSize]++;
    }break;
    case QBP_BUFFER_TYPE_CDAvgByBufferSz:
    {
        for(int i=0 ; i<pSWBuscas.size();i++)pSWDataHistogram[pSWBuscas[i].stQBPBufferSize]++;
        for(int i=0 ; i<pMSBuscas.size();i++)pMSDataHistogram[pMSBuscas[i].stQBPBufferSize]++;
        for(int i=0 ; i<pMXBuscas.size();i++)pMXDataHistogram[pMXBuscas[i].stQBPBufferSize]++;
        for(int i=0 ; i<pATBuscas.size();i++)pATDataHistogram[pATBuscas[i].stQBPBufferSize]++;
    }break;
    }

    //Calcula os valores medios de acordo com o relatorio
    CalcMeanValuesByType(pQBP_ReportType);

}

void CQBPTabPageCharts::CalcMeanValuesByType(int pQBP_ReportType)
{
    //Informa qual o campo de balanceamento sera usado para o calculo.
    switch(pQBP_ReportType)
    {
    case QBP_BUFFER_TYPE_FMAvgByType     :{CalcMeanValuesByFiel(pQBP_ReportType,0);}break;
    case QBP_BUFFER_TYPE_ETAvgByType     :{CalcMeanValuesByFiel(pQBP_ReportType,5);}break;
    case QBP_BUFFER_TYPE_ACAvgByPrecision:{CalcMeanValuesByFiel(pQBP_ReportType,2);}break;
    case QBP_BUFFER_TYPE_FMAvgByPrecision:{CalcMeanValuesByFiel(pQBP_ReportType,0);}break;
    case QBP_BUFFER_TYPE_PCAvgByPrecision:{CalcMeanValuesByFiel(pQBP_ReportType,1);}break;
    case QBP_BUFFER_TYPE_MRAvgByPrecision:{CalcMeanValuesByFiel(pQBP_ReportType,3);}break;
    case QBP_BUFFER_TYPE_ACAvgByResultSz: {CalcMeanValuesByFiel(pQBP_ReportType,2);}break;
    case QBP_BUFFER_TYPE_FMAvgByResultSz: {CalcMeanValuesByFiel(pQBP_ReportType,0);}break;
    case QBP_BUFFER_TYPE_PCAvgByResultSz: {CalcMeanValuesByFiel(pQBP_ReportType,1);}break;
    case QBP_BUFFER_TYPE_MRAvgByResultSz: {CalcMeanValuesByFiel(pQBP_ReportType,3);}break;
    case QBP_BUFFER_TYPE_MRAvgByBufferSz: {CalcMeanValuesByFiel(pQBP_ReportType,3);}break;
    case QBP_BUFFER_TYPE_PCAvgByBufferSz: {CalcMeanValuesByFiel(pQBP_ReportType,1);}break;
    case QBP_BUFFER_TYPE_CDAvgByBufferSz: {CalcMeanValuesByFiel(pQBP_ReportType,4);}break;
    }
}

void CQBPTabPageCharts::CalcMeanValuesByFiel(int pQBP_ReportType , int pQBP_FieldType)
{

    //Calcula a media do campo para cada histograma
    switch(pQBP_FieldType)
    {
    case 0://FMeasure
    {
       CalcMeanValuesByHist(pQBP_ReportType,0);
       CalcMeanValuesByHist(pQBP_ReportType,1);
       CalcMeanValuesByHist(pQBP_ReportType,2);
       CalcMeanValuesByHist(pQBP_ReportType,3);
    }break;
    case 1://Precision
    {
        CalcMeanValuesByHist(pQBP_ReportType,0);
        CalcMeanValuesByHist(pQBP_ReportType,1);
        CalcMeanValuesByHist(pQBP_ReportType,2);
        CalcMeanValuesByHist(pQBP_ReportType,3);
    }break;
    case 2://Accuracy
    {
        CalcMeanValuesByHist(pQBP_ReportType,0);
        CalcMeanValuesByHist(pQBP_ReportType,1);
        CalcMeanValuesByHist(pQBP_ReportType,2);
        CalcMeanValuesByHist(pQBP_ReportType,3);
    }break;
    case 3://MRR
    {
        CalcMeanValuesByHist(pQBP_ReportType,0);
        CalcMeanValuesByHist(pQBP_ReportType,1);
        CalcMeanValuesByHist(pQBP_ReportType,2);
        CalcMeanValuesByHist(pQBP_ReportType,3);
    }break;
    case 4://MSCD
    {
        CalcMeanValuesByHist(pQBP_ReportType,0);
        CalcMeanValuesByHist(pQBP_ReportType,1);
        CalcMeanValuesByHist(pQBP_ReportType,2);
        CalcMeanValuesByHist(pQBP_ReportType,3);
    }break;
    case 5://Elapsed Time
    {
        CalcMeanValuesByHist(pQBP_ReportType,0);
        CalcMeanValuesByHist(pQBP_ReportType,1);
        CalcMeanValuesByHist(pQBP_ReportType,2);
        CalcMeanValuesByHist(pQBP_ReportType,3);
    }break;
    }
}

void CQBPTabPageCharts::CalcMeanValuesByHist(int pQBP_ReportType , int pQBP_HistType)
{
    //utilizando qual é a lista e qual o campo para calculo finaliza o preenchimento.
    switch(pQBP_HistType)
    {
    case 0://SW
    {
        float Accum=0.0f;
        for(int i=0 ; i<pSWDataHistogram.size(); i++)
        {
            //Caso seja valor zerado nao tem precison balance
            if(pSWDataHistogram[i]==0)continue;

            for(int j=0;j<pSWBuscas.size();j++)
            {
                switch(pQBP_ReportType)
                {
                case QBP_BUFFER_TYPE_FMAvgByType     :{if(pSWBuscas[j].stQBPComparatorType   == i){ Accum += pSWBuscas[j].stQBPFmeasure;}}break;
                case QBP_BUFFER_TYPE_ETAvgByType     :{if(pSWBuscas[j].stQBPComparatorType   == i){ Accum += pSWBuscas[j].stQBPSearchElapsed;}}break;
                case QBP_BUFFER_TYPE_ACAvgByPrecision:{if(pSWBuscas[j].stQBPPrecisionBalance == i){ Accum += pSWBuscas[j].stQBPAccuracy;}}break;
                case QBP_BUFFER_TYPE_FMAvgByPrecision:{if(pSWBuscas[j].stQBPPrecisionBalance == i){ Accum += pSWBuscas[j].stQBPFmeasure;}}break;
                case QBP_BUFFER_TYPE_PCAvgByPrecision:{if(pSWBuscas[j].stQBPPrecisionBalance == i){ Accum += pSWBuscas[j].stQBPPrecision;}}break;
                case QBP_BUFFER_TYPE_MRAvgByPrecision:{if(pSWBuscas[j].stQBPPrecisionBalance == i){ Accum += pSWBuscas[j].stQBPReciprocalRank;}}break;
                case QBP_BUFFER_TYPE_ACAvgByResultSz :{if(pSWBuscas[j].stQBPResultSetBalance == i){ Accum += pSWBuscas[j].stQBPAccuracy;}}break;
                case QBP_BUFFER_TYPE_FMAvgByResultSz :{if(pSWBuscas[j].stQBPResultSetBalance == i){ Accum += pSWBuscas[j].stQBPFmeasure;}}break;
                case QBP_BUFFER_TYPE_PCAvgByResultSz :{if(pSWBuscas[j].stQBPResultSetBalance == i){ Accum += pSWBuscas[j].stQBPPrecision;}}break;
                case QBP_BUFFER_TYPE_MRAvgByResultSz :{if(pSWBuscas[j].stQBPResultSetBalance == i){ Accum += pSWBuscas[j].stQBPReciprocalRank;}}break;
                case QBP_BUFFER_TYPE_MRAvgByBufferSz :{if(pSWBuscas[j].stQBPBufferSize       == i){ Accum += pSWBuscas[j].stQBPReciprocalRank;}}break;
                case QBP_BUFFER_TYPE_PCAvgByBufferSz :{if(pSWBuscas[j].stQBPBufferSize       == i){ Accum += pSWBuscas[j].stQBPPrecision;}}break;
                case QBP_BUFFER_TYPE_CDAvgByBufferSz :{if(pSWBuscas[j].stQBPBufferSize       == i){ Accum += pSWBuscas[j].stQBPMSCD;}}break;
                }
            }

            stFileSearch item;

            switch(pQBP_ReportType)
            {
            case QBP_BUFFER_TYPE_FMAvgByType     :{item.stQBPComparatorType   = i; item.stQBPFmeasure       = (float)(Accum / pSWDataHistogram[i]);}break;
            case QBP_BUFFER_TYPE_ETAvgByType     :{item.stQBPComparatorType   = i; item.stQBPSearchElapsed  = (float)(Accum / pSWDataHistogram[i]);}break;
            case QBP_BUFFER_TYPE_ACAvgByPrecision:{item.stQBPPrecisionBalance = i; item.stQBPAccuracy       = (float)(Accum / pSWDataHistogram[i]);}break;
            case QBP_BUFFER_TYPE_FMAvgByPrecision:{item.stQBPPrecisionBalance = i; item.stQBPFmeasure       = (float)(Accum / pSWDataHistogram[i]);}break;
            case QBP_BUFFER_TYPE_PCAvgByPrecision:{item.stQBPPrecisionBalance = i; item.stQBPPrecision      = (float)(Accum / pSWDataHistogram[i]);}break;
            case QBP_BUFFER_TYPE_MRAvgByPrecision:{item.stQBPPrecisionBalance = i; item.stQBPReciprocalRank = (float)(Accum / pSWDataHistogram[i]);}break;
            case QBP_BUFFER_TYPE_ACAvgByResultSz :{item.stQBPResultSetBalance = i; item.stQBPAccuracy       = (float)(Accum / pSWDataHistogram[i]);}break;
            case QBP_BUFFER_TYPE_FMAvgByResultSz :{item.stQBPResultSetBalance = i; item.stQBPFmeasure       = (float)(Accum / pSWDataHistogram[i]);}break;
            case QBP_BUFFER_TYPE_PCAvgByResultSz :{item.stQBPResultSetBalance = i; item.stQBPPrecision      = (float)(Accum / pSWDataHistogram[i]);}break;
            case QBP_BUFFER_TYPE_MRAvgByResultSz :{item.stQBPResultSetBalance = i; item.stQBPReciprocalRank = (float)(Accum / pSWDataHistogram[i]);}break;
            case QBP_BUFFER_TYPE_MRAvgByBufferSz :{item.stQBPBufferSize       = i; item.stQBPReciprocalRank = (float)(Accum / pSWDataHistogram[i]);}break;
            case QBP_BUFFER_TYPE_PCAvgByBufferSz :{item.stQBPBufferSize       = i; item.stQBPPrecision      = (float)(Accum / pSWDataHistogram[i]);}break;
            case QBP_BUFFER_TYPE_CDAvgByBufferSz :{item.stQBPBufferSize       = i; item.stQBPMSCD           = (float)(Accum / pSWDataHistogram[i]);}break;
            }


            pSWBuscasMedias.push_back(item);

            Accum = 0.0f;
        }

    }break;
    case 1://MS
    {
        float Accum=0.0f;

        for(int i=0 ; i<pMSDataHistogram.size(); i++)
        {
            //Caso seja valor zerado nao tem precison balance
            if(pMSDataHistogram[i]==0)continue;

            for(int j=0;j<pMSBuscas.size();j++)
            {
                switch(pQBP_ReportType)
                {
                case QBP_BUFFER_TYPE_FMAvgByType     :{if(pMSBuscas[j].stQBPComparatorType   == i){ Accum += pMSBuscas[j].stQBPFmeasure;}}break;
                case QBP_BUFFER_TYPE_ETAvgByType     :{if(pMSBuscas[j].stQBPComparatorType   == i){ Accum += pMSBuscas[j].stQBPSearchElapsed;}}break;
                case QBP_BUFFER_TYPE_ACAvgByPrecision:{if(pMSBuscas[j].stQBPPrecisionBalance == i){ Accum += pMSBuscas[j].stQBPAccuracy;}}break;
                case QBP_BUFFER_TYPE_FMAvgByPrecision:{if(pMSBuscas[j].stQBPPrecisionBalance == i){ Accum += pMSBuscas[j].stQBPFmeasure;}}break;
                case QBP_BUFFER_TYPE_PCAvgByPrecision:{if(pMSBuscas[j].stQBPPrecisionBalance == i){ Accum += pMSBuscas[j].stQBPPrecision;}}break;
                case QBP_BUFFER_TYPE_MRAvgByPrecision:{if(pMSBuscas[j].stQBPPrecisionBalance == i){ Accum += pMSBuscas[j].stQBPReciprocalRank;}}break;
                case QBP_BUFFER_TYPE_ACAvgByResultSz :{if(pMSBuscas[j].stQBPResultSetBalance == i){ Accum += pMSBuscas[j].stQBPAccuracy;}}break;
                case QBP_BUFFER_TYPE_FMAvgByResultSz :{if(pMSBuscas[j].stQBPResultSetBalance == i){ Accum += pMSBuscas[j].stQBPFmeasure;}}break;
                case QBP_BUFFER_TYPE_PCAvgByResultSz :{if(pMSBuscas[j].stQBPResultSetBalance == i){ Accum += pMSBuscas[j].stQBPPrecision;}}break;
                case QBP_BUFFER_TYPE_MRAvgByResultSz :{if(pMSBuscas[j].stQBPResultSetBalance == i){ Accum += pMSBuscas[j].stQBPReciprocalRank;}}break;
                case QBP_BUFFER_TYPE_MRAvgByBufferSz :{if(pMSBuscas[j].stQBPBufferSize       == i){ Accum += pMSBuscas[j].stQBPReciprocalRank;}}break;
                case QBP_BUFFER_TYPE_PCAvgByBufferSz :{if(pMSBuscas[j].stQBPBufferSize       == i){ Accum += pMSBuscas[j].stQBPPrecision;}}break;
                case QBP_BUFFER_TYPE_CDAvgByBufferSz :{if(pMSBuscas[j].stQBPBufferSize       == i){ Accum += pMSBuscas[j].stQBPMSCD;}}break;
                }
            }

            stFileSearch item;

            switch(pQBP_ReportType)
            {
            case QBP_BUFFER_TYPE_FMAvgByType     :{item.stQBPComparatorType   = i; item.stQBPFmeasure       = (float)(Accum / pMSDataHistogram[i]);}break;
            case QBP_BUFFER_TYPE_ETAvgByType     :{item.stQBPComparatorType   = i; item.stQBPSearchElapsed  = (float)(Accum / pMSDataHistogram[i]);}break;
            case QBP_BUFFER_TYPE_ACAvgByPrecision:{item.stQBPPrecisionBalance = i; item.stQBPAccuracy       = (float)(Accum / pMSDataHistogram[i]);}break;
            case QBP_BUFFER_TYPE_FMAvgByPrecision:{item.stQBPPrecisionBalance = i; item.stQBPFmeasure       = (float)(Accum / pMSDataHistogram[i]);}break;
            case QBP_BUFFER_TYPE_PCAvgByPrecision:{item.stQBPPrecisionBalance = i; item.stQBPPrecision      = (float)(Accum / pMSDataHistogram[i]);}break;
            case QBP_BUFFER_TYPE_MRAvgByPrecision:{item.stQBPPrecisionBalance = i; item.stQBPReciprocalRank = (float)(Accum / pMSDataHistogram[i]);}break;
            case QBP_BUFFER_TYPE_ACAvgByResultSz :{item.stQBPResultSetBalance = i; item.stQBPAccuracy       = (float)(Accum / pMSDataHistogram[i]);}break;
            case QBP_BUFFER_TYPE_FMAvgByResultSz :{item.stQBPResultSetBalance = i; item.stQBPFmeasure       = (float)(Accum / pMSDataHistogram[i]);}break;
            case QBP_BUFFER_TYPE_PCAvgByResultSz :{item.stQBPResultSetBalance = i; item.stQBPPrecision      = (float)(Accum / pMSDataHistogram[i]);}break;
            case QBP_BUFFER_TYPE_MRAvgByResultSz :{item.stQBPResultSetBalance = i; item.stQBPReciprocalRank = (float)(Accum / pMSDataHistogram[i]);}break;
            case QBP_BUFFER_TYPE_MRAvgByBufferSz :{item.stQBPBufferSize       = i; item.stQBPReciprocalRank = (float)(Accum / pMSDataHistogram[i]);}break;
            case QBP_BUFFER_TYPE_PCAvgByBufferSz :{item.stQBPBufferSize       = i; item.stQBPPrecision      = (float)(Accum / pMSDataHistogram[i]);}break;
            case QBP_BUFFER_TYPE_CDAvgByBufferSz :{item.stQBPBufferSize       = i; item.stQBPMSCD           = (float)(Accum / pMSDataHistogram[i]);}break;
            }

            pMSBuscasMedias.push_back(item);

            Accum = 0.0f;

        }

    }break;
    case 2://MX
    {
        float Accum=0.0f;

        for(int i=0 ; i<pMXDataHistogram.size(); i++)
        {
            //Caso seja valor zerado nao tem precison balance
            if(pMXDataHistogram[i]==0)continue;

            for(int j=0;j<pMXBuscas.size();j++)
            {
                switch(pQBP_ReportType)
                {
                case QBP_BUFFER_TYPE_FMAvgByType     :{if(pMXBuscas[j].stQBPComparatorType   == i){ Accum += pMXBuscas[j].stQBPFmeasure;}}break;
                case QBP_BUFFER_TYPE_ETAvgByType     :{if(pMXBuscas[j].stQBPComparatorType   == i){ Accum += pMXBuscas[j].stQBPSearchElapsed;}}break;
                case QBP_BUFFER_TYPE_ACAvgByPrecision:{if(pMXBuscas[j].stQBPPrecisionBalance == i){ Accum += pMXBuscas[j].stQBPAccuracy;}}break;
                case QBP_BUFFER_TYPE_FMAvgByPrecision:{if(pMXBuscas[j].stQBPPrecisionBalance == i){ Accum += pMXBuscas[j].stQBPFmeasure;}}break;
                case QBP_BUFFER_TYPE_PCAvgByPrecision:{if(pMXBuscas[j].stQBPPrecisionBalance == i){ Accum += pMXBuscas[j].stQBPPrecision;}}break;
                case QBP_BUFFER_TYPE_MRAvgByPrecision:{if(pMXBuscas[j].stQBPPrecisionBalance == i){ Accum += pMXBuscas[j].stQBPReciprocalRank;}}break;
                case QBP_BUFFER_TYPE_ACAvgByResultSz :{if(pMXBuscas[j].stQBPResultSetBalance == i){ Accum += pMXBuscas[j].stQBPAccuracy;}}break;
                case QBP_BUFFER_TYPE_FMAvgByResultSz :{if(pMXBuscas[j].stQBPResultSetBalance == i){ Accum += pMXBuscas[j].stQBPFmeasure;}}break;
                case QBP_BUFFER_TYPE_PCAvgByResultSz :{if(pMXBuscas[j].stQBPResultSetBalance == i){ Accum += pMXBuscas[j].stQBPPrecision;}}break;
                case QBP_BUFFER_TYPE_MRAvgByResultSz :{if(pMXBuscas[j].stQBPResultSetBalance == i){ Accum += pMXBuscas[j].stQBPReciprocalRank;}}break;
                case QBP_BUFFER_TYPE_MRAvgByBufferSz :{if(pMXBuscas[j].stQBPBufferSize       == i){ Accum += pMXBuscas[j].stQBPReciprocalRank;}}break;
                case QBP_BUFFER_TYPE_PCAvgByBufferSz :{if(pMXBuscas[j].stQBPBufferSize       == i){ Accum += pMXBuscas[j].stQBPPrecision;}}break;
                case QBP_BUFFER_TYPE_CDAvgByBufferSz :{if(pMXBuscas[j].stQBPBufferSize       == i){ Accum += pMXBuscas[j].stQBPMSCD;}}break;
                }
            }

            stFileSearch item;

            switch(pQBP_ReportType)
            {
            case QBP_BUFFER_TYPE_FMAvgByType     :{item.stQBPComparatorType   = i; item.stQBPFmeasure       = (float)(Accum / pMXDataHistogram[i]);}break;
            case QBP_BUFFER_TYPE_ETAvgByType     :{item.stQBPComparatorType   = i; item.stQBPSearchElapsed  = (float)(Accum / pMXDataHistogram[i]);}break;
            case QBP_BUFFER_TYPE_ACAvgByPrecision:{item.stQBPPrecisionBalance = i; item.stQBPAccuracy       = (float)(Accum / pMXDataHistogram[i]);}break;
            case QBP_BUFFER_TYPE_FMAvgByPrecision:{item.stQBPPrecisionBalance = i; item.stQBPFmeasure       = (float)(Accum / pMXDataHistogram[i]);}break;
            case QBP_BUFFER_TYPE_PCAvgByPrecision:{item.stQBPPrecisionBalance = i; item.stQBPPrecision      = (float)(Accum / pMXDataHistogram[i]);}break;
            case QBP_BUFFER_TYPE_MRAvgByPrecision:{item.stQBPPrecisionBalance = i; item.stQBPReciprocalRank = (float)(Accum / pMXDataHistogram[i]);}break;
            case QBP_BUFFER_TYPE_ACAvgByResultSz :{item.stQBPResultSetBalance = i; item.stQBPAccuracy       = (float)(Accum / pMXDataHistogram[i]);}break;
            case QBP_BUFFER_TYPE_FMAvgByResultSz :{item.stQBPResultSetBalance = i; item.stQBPFmeasure       = (float)(Accum / pMXDataHistogram[i]);}break;
            case QBP_BUFFER_TYPE_PCAvgByResultSz :{item.stQBPResultSetBalance = i; item.stQBPPrecision      = (float)(Accum / pMXDataHistogram[i]);}break;
            case QBP_BUFFER_TYPE_MRAvgByResultSz :{item.stQBPResultSetBalance = i; item.stQBPReciprocalRank = (float)(Accum / pMXDataHistogram[i]);}break;
            case QBP_BUFFER_TYPE_MRAvgByBufferSz :{item.stQBPBufferSize       = i; item.stQBPReciprocalRank = (float)(Accum / pMXDataHistogram[i]);}break;
            case QBP_BUFFER_TYPE_PCAvgByBufferSz :{item.stQBPBufferSize       = i; item.stQBPPrecision      = (float)(Accum / pMXDataHistogram[i]);}break;
            case QBP_BUFFER_TYPE_CDAvgByBufferSz :{item.stQBPBufferSize       = i; item.stQBPMSCD           = (float)(Accum / pMXDataHistogram[i]);}break;
            }

            pMXBuscasMedias.push_back(item);

            Accum = 0.0f;
        }

    }break;
    case 3://AT
    {
        float Accum=0.0f;

        for(int i=0 ; i<pATDataHistogram.size(); i++)
        {
            //Caso seja valor zerado nao tem precison balance
            if(pATDataHistogram[i]==0)continue;

            for(int j=0;j<pATBuscas.size();j++)
            {
                switch(pQBP_ReportType)
                {
                case QBP_BUFFER_TYPE_FMAvgByType     :{if(pATBuscas[j].stQBPComparatorType   == i){ Accum += pATBuscas[j].stQBPFmeasure;}}break;
                case QBP_BUFFER_TYPE_ETAvgByType     :{if(pATBuscas[j].stQBPComparatorType   == i){ Accum += pATBuscas[j].stQBPSearchElapsed;}}break;
                case QBP_BUFFER_TYPE_ACAvgByPrecision:{if(pATBuscas[j].stQBPPrecisionBalance == i){ Accum += pATBuscas[j].stQBPAccuracy;}}break;
                case QBP_BUFFER_TYPE_FMAvgByPrecision:{if(pATBuscas[j].stQBPPrecisionBalance == i){ Accum += pATBuscas[j].stQBPFmeasure;}}break;
                case QBP_BUFFER_TYPE_PCAvgByPrecision:{if(pATBuscas[j].stQBPPrecisionBalance == i){ Accum += pATBuscas[j].stQBPPrecision;}}break;
                case QBP_BUFFER_TYPE_MRAvgByPrecision:{if(pATBuscas[j].stQBPPrecisionBalance == i){ Accum += pATBuscas[j].stQBPReciprocalRank;}}break;
                case QBP_BUFFER_TYPE_ACAvgByResultSz :{if(pATBuscas[j].stQBPResultSetBalance == i){ Accum += pATBuscas[j].stQBPAccuracy;}}break;
                case QBP_BUFFER_TYPE_FMAvgByResultSz :{if(pATBuscas[j].stQBPResultSetBalance == i){ Accum += pATBuscas[j].stQBPFmeasure;}}break;
                case QBP_BUFFER_TYPE_PCAvgByResultSz :{if(pATBuscas[j].stQBPResultSetBalance == i){ Accum += pATBuscas[j].stQBPPrecision;}}break;
                case QBP_BUFFER_TYPE_MRAvgByResultSz :{if(pATBuscas[j].stQBPResultSetBalance == i){ Accum += pATBuscas[j].stQBPReciprocalRank;}}break;
                case QBP_BUFFER_TYPE_MRAvgByBufferSz :{if(pATBuscas[j].stQBPBufferSize       == i){ Accum += pATBuscas[j].stQBPReciprocalRank;}}break;
                case QBP_BUFFER_TYPE_PCAvgByBufferSz :{if(pATBuscas[j].stQBPBufferSize       == i){ Accum += pATBuscas[j].stQBPPrecision;}}break;
                case QBP_BUFFER_TYPE_CDAvgByBufferSz :{if(pATBuscas[j].stQBPBufferSize       == i){ Accum += pATBuscas[j].stQBPMSCD;}}break;
                }
            }

            stFileSearch item;

            switch(pQBP_ReportType)
            {
            case QBP_BUFFER_TYPE_FMAvgByType     :{item.stQBPComparatorType   = i; item.stQBPFmeasure       = (float)(Accum / pATDataHistogram[i]);}break;
            case QBP_BUFFER_TYPE_ETAvgByType     :{item.stQBPComparatorType   = i; item.stQBPSearchElapsed  = (float)(Accum / pATDataHistogram[i]);}break;
            case QBP_BUFFER_TYPE_ACAvgByPrecision:{item.stQBPPrecisionBalance = i; item.stQBPAccuracy       = (float)(Accum / pATDataHistogram[i]);}break;
            case QBP_BUFFER_TYPE_FMAvgByPrecision:{item.stQBPPrecisionBalance = i; item.stQBPFmeasure       = (float)(Accum / pATDataHistogram[i]);}break;
            case QBP_BUFFER_TYPE_PCAvgByPrecision:{item.stQBPPrecisionBalance = i; item.stQBPPrecision      = (float)(Accum / pATDataHistogram[i]);}break;
            case QBP_BUFFER_TYPE_MRAvgByPrecision:{item.stQBPPrecisionBalance = i; item.stQBPReciprocalRank = (float)(Accum / pATDataHistogram[i]);}break;
            case QBP_BUFFER_TYPE_ACAvgByResultSz :{item.stQBPResultSetBalance = i; item.stQBPAccuracy       = (float)(Accum / pATDataHistogram[i]);}break;
            case QBP_BUFFER_TYPE_FMAvgByResultSz :{item.stQBPResultSetBalance = i; item.stQBPFmeasure       = (float)(Accum / pATDataHistogram[i]);}break;
            case QBP_BUFFER_TYPE_PCAvgByResultSz :{item.stQBPResultSetBalance = i; item.stQBPPrecision      = (float)(Accum / pATDataHistogram[i]);}break;
            case QBP_BUFFER_TYPE_MRAvgByResultSz :{item.stQBPResultSetBalance = i; item.stQBPReciprocalRank = (float)(Accum / pATDataHistogram[i]);}break;
            case QBP_BUFFER_TYPE_MRAvgByBufferSz :{item.stQBPBufferSize       = i; item.stQBPReciprocalRank = (float)(Accum / pATDataHistogram[i]);}break;
            case QBP_BUFFER_TYPE_PCAvgByBufferSz :{item.stQBPBufferSize       = i; item.stQBPPrecision      = (float)(Accum / pATDataHistogram[i]);}break;
            case QBP_BUFFER_TYPE_CDAvgByBufferSz :{item.stQBPBufferSize       = i; item.stQBPMSCD           = (float)(Accum / pATDataHistogram[i]);}break;
            }

            pATBuscasMedias.push_back(item);

            Accum = 0.0f;
        }

    }break;
    }
}
