#include "QBP_TabPage3DCharts.h"

CQBPEngine * CQBPTabPage3DCharts::pQBPEngine=nullptr;

CQBPTabPage3DCharts::CQBPTabPage3DCharts(QWidget *parent) : QWidget(parent)
{
    pQBPChartsGrid   = new QGridLayout(parent);
    pQBPLoadProgress = new QProgressBar();
    pQBPClusterizer  = new CQBPClusterizer();


    m_fontSize= 40.0f;
    m_style = QAbstract3DSeries::MeshSphere;
    m_smooth = true;

    QPushButton *LoadCharts   = new QPushButton(tr("Load Charts"));
    QPushButton *SaveCharts   = new QPushButton(tr("Save Charts"));

    //Grupo de Criação
    QGroupBox *GrupoChartParameters = new QGroupBox(tr("Chart Options:"));

    QHBoxLayout *LayoutOptCharts = new QHBoxLayout;
    LayoutOptCharts->addWidget(LoadCharts);
    LayoutOptCharts->addWidget(SaveCharts);
    QVBoxLayout *LayoutProgress = new QVBoxLayout;
    LayoutProgress->addLayout(LayoutOptCharts);
    LayoutProgress->addWidget(pQBPLoadProgress);

    GrupoChartParameters->setLayout(LayoutProgress);

    //Inclui os Grupos no Layout Principal
    QVBoxLayout *LayoutPrincipal = new QVBoxLayout;
    LayoutPrincipal->addWidget(GrupoChartParameters);
    LayoutPrincipal->addLayout(pQBPChartsGrid);

    //Set the Main Layout of the Grid of Charts
    setLayout(LayoutPrincipal);

    //stablish controls connection
    connect(LoadCharts , SIGNAL(clicked()), this, SLOT(OnBtnLoadCharts()));
    connect(SaveCharts , SIGNAL(clicked()), this, SLOT(OnBtnSaveCharts()));

    pQBPScatter    = new Q3DScatter();

    pQBPScatterContainer = QWidget::createWindowContainer(pQBPScatter);
    if (!pQBPScatter->hasContext()) {
        QMessageBox msgBox;
        msgBox.setText("Couldn't initialize the OpenGL context.");
        msgBox.exec();
    }

    QSize screenSize = size();
    pQBPScatterContainer->setMinimumSize(QSize(screenSize.width() / 2, screenSize.height() / 1.5));
    pQBPScatterContainer->setMaximumSize(screenSize);
    pQBPScatterContainer->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    pQBPScatterContainer->setFocusPolicy(Qt::StrongFocus);


    pQBPScatter->activeTheme()->setType(Q3DTheme::ThemeStoneMoss);
    QFont font = pQBPScatter->activeTheme()->font();

    font.setPointSize(m_fontSize);
    pQBPScatter->activeTheme()->setFont(font);
    pQBPScatter->setShadowQuality(QAbstract3DGraph::ShadowQualitySoftLow);
    pQBPScatter->scene()->activeCamera()->setCameraPreset(Q3DCamera::CameraPresetFront);


    QScatterDataProxy *proxy00 = new QScatterDataProxy;
    QScatterDataProxy *proxy01 = new QScatterDataProxy;
    QScatterDataProxy *proxy02 = new QScatterDataProxy;
    QScatterDataProxy *proxy03 = new QScatterDataProxy;
    QScatterDataProxy *proxy04 = new QScatterDataProxy;
    QScatterDataProxy *proxy05 = new QScatterDataProxy;

    QScatter3DSeries *series00 = new QScatter3DSeries(proxy00);
    QScatter3DSeries *series01 = new QScatter3DSeries(proxy01);
    QScatter3DSeries *series02 = new QScatter3DSeries(proxy02);
    QScatter3DSeries *series03 = new QScatter3DSeries(proxy03);
    QScatter3DSeries *series04 = new QScatter3DSeries(proxy04);
    QScatter3DSeries *series05 = new QScatter3DSeries(proxy05);

    series00->setItemLabelFormat(QStringLiteral("@xTitle: @xLabel @yTitle: @yLabel @zTitle: @zLabel"));
    series00->setMeshSmooth(m_smooth);
    pQBPScatter->addSeries(series00);

    series01->setItemLabelFormat(QStringLiteral("@xTitle: @xLabel @yTitle: @yLabel @zTitle: @zLabel"));
    series01->setMeshSmooth(m_smooth);
    pQBPScatter->addSeries(series01);

    series02->setItemLabelFormat(QStringLiteral("@xTitle: @xLabel @yTitle: @yLabel @zTitle: @zLabel"));
    series02->setMeshSmooth(m_smooth);
    pQBPScatter->addSeries(series02);

    series03->setItemLabelFormat(QStringLiteral("@xTitle: @xLabel @yTitle: @yLabel @zTitle: @zLabel"));
    series03->setMeshSmooth(m_smooth);
    pQBPScatter->addSeries(series03);

    series04->setItemLabelFormat(QStringLiteral("@xTitle: @xLabel @yTitle: @yLabel @zTitle: @zLabel"));
    series04->setMeshSmooth(m_smooth);
    pQBPScatter->addSeries(series04);

    series05->setItemLabelFormat(QStringLiteral("@xTitle: @xLabel @yTitle: @yLabel @zTitle: @zLabel"));
    series05->setMeshSmooth(m_smooth);
    pQBPScatter->addSeries(series05);

    //Change the mesh model
    m_style = QAbstract3DSeries::Mesh(int(m_style));
    for(int i=0;i<pQBPScatter->seriesList().size();i++)
    {
        pQBPScatter->seriesList().at(i)->setMesh(m_style);

        switch(i)
        {
            case 0:{pQBPScatter->seriesList().at(0)->setBaseColor(QColor(150,50,10 ));}break;
            case 1:{pQBPScatter->seriesList().at(1)->setBaseColor(QColor(10 ,50,150));}break;
            case 2:{pQBPScatter->seriesList().at(2)->setBaseColor(QColor(150,150,10));}break;
            case 3:{pQBPScatter->seriesList().at(3)->setBaseColor(QColor(150,150,150));}break;
            case 4:{pQBPScatter->seriesList().at(4)->setBaseColor(QColor(50,50,50));}break;
            case 5:{pQBPScatter->seriesList().at(5)->setBaseColor(QColor(10,10,10));}break;
        }

    }

    //Add the chart on grid
    pQBPChartsGrid->addWidget(pQBPScatterContainer);

}

void CQBPTabPage3DCharts::setEngineReference(CQBPEngine *pQBP_Engine)
{
    pQBPEngine = pQBP_Engine;
}

void CQBPTabPage3DCharts::OnBtnSaveCharts()
{
    QString fileName = "sauve.jpg";
    fileName = QFileDialog::getSaveFileName(this,"Sauve...","..."," (*.jpg)");
    if(!fileName.isEmpty())
    {
    QPixmap picture;
    //picture = QPixmap::grabWidget(pQBPScatterContainer);
    picture = grab();
    picture.save(fileName);
    }
}
void CQBPTabPage3DCharts::OnBtnLoadCharts()
{
    //addData();
    addChordsData();
}

void CQBPTabPage3DCharts::addData()
{
    int tQtdGenres=0;
    int tQtdSongs=0;
    int tProgress=0;
    int tQtdValues=0;
    // Configure the axes according to the data
    pQBPScatter->axisX()->setTitle("BPMMedio");
    pQBPScatter->axisY()->setTitle("Attitude");
    pQBPScatter->axisZ()->setTitle("NumberOfPitchs");

    tQtdGenres = pQBPEngine->GenresLoaded();
    tQtdSongs  = pQBPEngine->SongsLoaded();

    for (float x = 0; x < tQtdGenres; x++)
    {
        QString tGenreName;
        int     tGenreQtdSongs;

        pQBPEngine->GetGenreData(x,tGenreName,tGenreQtdSongs);

        for (float y = 0; y < tGenreQtdSongs; y++)
        {
            tQtdValues++;
        }
    }

    pQBPLoadProgress->setMinimum(0);
    QScatterDataArray *dataArray = new QScatterDataArray;
    dataArray->resize(tQtdValues);
    QScatterDataItem *ptrToDataArray = &dataArray->first();
    pQBPLoadProgress->setMaximum(tQtdValues);

    for (float x = 0; x < tQtdGenres; x++)
    {
        QString tGenreName;
        int     tGenreQtdSongs;

        pQBPEngine->GetGenreData(x,tGenreName,tGenreQtdSongs);

        for (float y = 0; y < tGenreQtdSongs; y++)
        {
            QString tSongName;
            int     tQtdSongNotes;
            int     tQtdSongFeatures;
            int     tQtdSongCustomFeatures;
            QString tQBPFeatureName;
            int     tQBPFeatureType;
            double  tQBPFeatureValue;

            int tBPMMedio;
            int tAttitude;
            int tNumberOfPitchs;

            pQBPEngine->GetSongData(x,y,tSongName,tQtdSongNotes,tQtdSongFeatures,tQtdSongCustomFeatures);

            for(int k=0;k<tQtdSongCustomFeatures;k++)
            {
                pQBPEngine->GetFeatureData(x,y,k,tQBPFeatureName,tQBPFeatureType,tQBPFeatureValue);
                if(tQBPFeatureName=="NumerodePitchs"  )
                {
                    tNumberOfPitchs       = tQBPFeatureValue;
                }
                if(tQBPFeatureName=="BPMMedio" )
                {
                    tBPMMedio = tQBPFeatureValue;
                }
                if(tQBPFeatureName=="AtitudedoMusico")
                {
                    tAttitude      = tQBPFeatureValue;
                }
            }
            ptrToDataArray->setPosition(QVector3D(tBPMMedio,tAttitude,tNumberOfPitchs));
            ptrToDataArray++;
            tProgress++;
            pQBPLoadProgress->setValue(tProgress);
        }
    }

    pQBPScatter->seriesList().at(0)->dataProxy()->resetArray(dataArray);

}

void CQBPTabPage3DCharts::addChordsData()
{
    //quantos acordes por cluster?
    int tQtdChords=0;
    int tQtdChords0=0;
    int tQtdChords1=0;
    int tQtdChords2=0;
    int tQtdChords3=0;
    int tQtdChords4=0;
    int tQtdChords5=0;

    QScatterDataArray *dataArray00=nullptr;
    QScatterDataArray *dataArray01=nullptr;
    QScatterDataArray *dataArray02=nullptr;
    QScatterDataArray *dataArray03=nullptr;
    QScatterDataArray *dataArray04=nullptr;
    QScatterDataArray *dataArray05=nullptr;

    int tProgress=0;
    int tQtdValues=0;
    // Configure the axes according to the data
    pQBPScatter->axisX()->setTitle("Min");
    pQBPScatter->axisY()->setTitle("Mid");
    pQBPScatter->axisZ()->setTitle("Max");

    //Clusteriza todos os acordes (6 Clusters)
    pQBPClusterizer->FillData(pQBPEngine->pQBPDataset->pQBPChords);
    pQBPClusterizer->Clusterize();

    tQtdChords = pQBPEngine->ChordsLoaded();
    for(int i=0;i<tQtdChords;i++)
    {
        //Identifica o Cluster do Acorde
        int idx = pQBPClusterizer->mSampleLabels.at<int>(i);
        switch(idx)
        {
            case 0:{tQtdChords0++;}break;
            case 1:{tQtdChords1++;}break;
            case 2:{tQtdChords2++;}break;
            case 3:{tQtdChords3++;}break;
            case 4:{tQtdChords4++;}break;
            case 5:{tQtdChords5++;}break;
        }
    }

    pQBPLoadProgress->setMinimum(0);
    pQBPLoadProgress->setMaximum(tQtdChords);

    dataArray00= new QScatterDataArray;
    dataArray01= new QScatterDataArray;
    dataArray02= new QScatterDataArray;
    dataArray03= new QScatterDataArray;
    dataArray04= new QScatterDataArray;
    dataArray05= new QScatterDataArray;

    dataArray00->resize(tQtdChords0);
    dataArray01->resize(tQtdChords1);
    dataArray02->resize(tQtdChords2);
    dataArray03->resize(tQtdChords3);
    dataArray04->resize(tQtdChords4);
    dataArray05->resize(tQtdChords5);

    QScatterDataItem *ptrToDataArray00 = &dataArray00->first();
    QScatterDataItem *ptrToDataArray01 = &dataArray01->first();
    QScatterDataItem *ptrToDataArray02 = &dataArray02->first();
    QScatterDataItem *ptrToDataArray03 = &dataArray03->first();
    QScatterDataItem *ptrToDataArray04 = &dataArray04->first();
    QScatterDataItem *ptrToDataArray05 = &dataArray05->first();

    for(int i=0;i<tQtdChords;i++)
    {
        QString tChordName;
        int     tChordNote01;
        int     tChordNote02;
        int     tChordNote03;
        int     tChordNote04;
        int     tChordNote05;
        int     tChordNote06;

        int     tValMin,tValMid,tValMax;

        pQBPEngine->GetChordData(i,tChordName,tChordNote01,tChordNote02,tChordNote03,tChordNote04,tChordNote05,tChordNote06);

        tValMin = tChordNote01 + tChordNote02;
        tValMid = tChordNote03 + tChordNote04;
        tValMax = tChordNote05 + tChordNote06;

        //Identifica o Cluster do Acorde
        int idx = pQBPClusterizer->mSampleLabels.at<int>(i);
        switch(idx)
        {
            case 0:{ptrToDataArray00->setPosition(QVector3D(tValMin,tValMid,tValMax));  ptrToDataArray00++;}break;
            case 1:{ptrToDataArray01->setPosition(QVector3D(tValMin,tValMid,tValMax));  ptrToDataArray01++;}break;
            case 2:{ptrToDataArray02->setPosition(QVector3D(tValMin,tValMid,tValMax));  ptrToDataArray02++;}break;
            case 3:{ptrToDataArray03->setPosition(QVector3D(tValMin,tValMid,tValMax));  ptrToDataArray03++;}break;
            case 4:{ptrToDataArray04->setPosition(QVector3D(tValMin,tValMid,tValMax));  ptrToDataArray04++;}break;
            case 5:{ptrToDataArray05->setPosition(QVector3D(tValMin,tValMid,tValMax));  ptrToDataArray05++;}break;
        }

        tProgress++;
        pQBPLoadProgress->setValue(tProgress);

    }

    pQBPScatter->seriesList().at(0)->dataProxy()->resetArray(dataArray00);
    pQBPScatter->seriesList().at(1)->dataProxy()->resetArray(dataArray01);
    pQBPScatter->seriesList().at(2)->dataProxy()->resetArray(dataArray02);
    pQBPScatter->seriesList().at(3)->dataProxy()->resetArray(dataArray03);
    pQBPScatter->seriesList().at(4)->dataProxy()->resetArray(dataArray04);
    pQBPScatter->seriesList().at(5)->dataProxy()->resetArray(dataArray05);

}

void CQBPTabPage3DCharts::resizeEvent(QResizeEvent *event)
{
    if(pQBPScatter     ==nullptr ||
       pQBPScatterContainer ==nullptr )
    {
        return;
    }

    QSize screenSize = size();
    pQBPScatterContainer->setMinimumSize(QSize(screenSize.width() / 2, screenSize.height() / 1.5));
    pQBPScatterContainer->setMaximumSize(screenSize);
    pQBPScatterContainer->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    pQBPScatterContainer->setFocusPolicy(Qt::StrongFocus);
}


