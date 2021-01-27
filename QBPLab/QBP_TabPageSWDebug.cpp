#include "QBP_TabPageSWDebug.h"
#include "QBP_SWDebugDialog.h"
#include "QBP_SearchResults.h"

CQBPEngine * CQBPTabPageSWDebug::pQBPEngine=nullptr;

CQBPTabPageSWDebug::CQBPTabPageSWDebug(QWidget *parent) : QWidget(parent)
{
   pPlayDebbug = false;

   SWGraph = new CQBPSWDebugGraph(this);

   pQBPDebugGrid   = new QGridLayout(parent);

   QPushButton *LoadCharts   = new QPushButton(tr("Load Search Results"));
   QPushButton *SaveCharts   = new QPushButton(tr("Save Analysis"));
   QPushButton *PlayDebug    = new QPushButton(tr(""));
   QPushButton *RecordDebug  = new QPushButton(tr(""));

   PlayDebug->setIcon(QIcon("Icones/play.png"));
   RecordDebug->setIcon(QIcon("Icones/record.png"));

   SearchsCombo = new QComboBox;
   AlignmentsCombo = new QComboBox;
   TracebacksCombo = new QComboBox;

   //Grupo de Criação
   QGroupBox *GrupoChartParameters = new QGroupBox(tr("Matrix Selection:"));

   QHBoxLayout *LayoutOptCharts = new QHBoxLayout;
   LayoutOptCharts->addWidget(LoadCharts);
   LayoutOptCharts->addWidget(SaveCharts);
   LayoutOptCharts->addWidget(SearchsCombo);
   LayoutOptCharts->addWidget(AlignmentsCombo);
   LayoutOptCharts->addWidget(TracebacksCombo);
   QVBoxLayout *LayoutProgress = new QVBoxLayout;
   LayoutProgress->addLayout(LayoutOptCharts);

   GrupoChartParameters->setLayout(LayoutProgress);

   pQBPFrameSlider = new QSlider(Qt::Horizontal,this);
   pQBPFrameSlider->setTickPosition(QSlider::TicksAbove);
   pQBPFrameSlider->setMinimum(0);
   pQBPFrameSlider->setMaximum(100);
   //Inclui os Grupos no Layout Principal
   QVBoxLayout *LayoutPrincipal = new QVBoxLayout;
   LayoutPrincipal->addWidget(GrupoChartParameters);
   LayoutPrincipal->addLayout(pQBPDebugGrid);

   QHBoxLayout *LayoutPlayer = new QHBoxLayout();
   LayoutPlayer->addWidget(pQBPFrameSlider);
   LayoutPlayer->addWidget(PlayDebug);
   LayoutPlayer->addWidget(RecordDebug);

   LayoutPrincipal->addLayout(LayoutPlayer);
   //Set the Main Layout of the Grid of Charts
   setLayout(LayoutPrincipal);

   //stablish controls connection
   connect(LoadCharts     , SIGNAL(clicked     (   )), this, SLOT(OnBtnLoadMatrix   (   )));
   connect(SaveCharts     , SIGNAL(clicked     (   )), this, SLOT(OnBtnSaveMatrix   (   )));
   connect(PlayDebug      , SIGNAL(clicked     (   )), this, SLOT(OnBtnPlay         (   )));
   connect(RecordDebug    , SIGNAL(clicked     (   )), this, SLOT(OnBtnRecord       (   )));
   connect(SearchsCombo   , SIGNAL(activated   (int)), this, SLOT(OnBoxSearchSel    (int)));
   connect(AlignmentsCombo, SIGNAL(activated   (int)), this, SLOT(OnBoxAlignmentsSel(int)));
   connect(TracebacksCombo, SIGNAL(activated   (int)), this, SLOT(OnBoxTracebacksSel(int)));
   connect(pQBPFrameSlider, SIGNAL(valueChanged(int)), this, SLOT(OnSliderSel       (int)));

   //Add the chart on grid
   pQBPDebugGrid->addWidget(SWGraph);

}

void CQBPTabPageSWDebug::OnBtnSaveMatrix()
{
    for(int i=0;i<pDebbugMovie.size();i++)
    {
        QString fileName = QString("resultados/videos/Record_%1.jpg").arg(i);
        pDebbugMovie[i].save(fileName);
    }

    //Cria Video de entrada com os frames gravados.
    cv::VideoCapture cap("resultados/videos/Record_%d.jpg");

    // if not success, exit program
    if (cap.isOpened() == false)
    {
        return;
        //ERRO
    }

    int frame_width = static_cast<int>(cap.get(cv::CAP_PROP_FRAME_WIDTH)); //get the width of frames of the video
    int frame_height = static_cast<int>(cap.get(cv::CAP_PROP_FRAME_HEIGHT)); //get the height of frames of the video

    cv::Size frame_size(frame_width, frame_height);
    int frames_per_second = 10;

    //cv::VideoWriter::fourcc('M', 'J', 'P', 'G')
    //Create and initialize the VideoWriter object
    cv::VideoWriter oVideoWriter("resultados/videos/Output.avi",
                                 /*cv::VideoWriter::fourcc('M', 'J', 'P', 'G')*/0,
                                 frames_per_second,
                                 frame_size,
                                 true);

    //If the VideoWriter object is not initialized successfully, exit the program
    if (oVideoWriter.isOpened() == false)
    {
        return;
        //Erro!
    }

    while(true)
    {
        cv::Mat frame;
        bool isSuccess = cap.read(frame); // read a new frame from the video camera

        //Breaking the while loop if frames cannot be read from the camera
        if (isSuccess == false)
        {
           //erro!
           break;
        }

        /*
        Make changes to the frame as necessary
        e.g.
        1. Change brightness/contrast of the image
        2. Smooth/Blur image
        3. Crop the image
        4. Rotate the image
        5. Draw shapes on the image
        */

        //write the video frame to the file
        oVideoWriter.write(frame);

        //Wait for for 10 milliseconds until any key is pressed.
        //If the 'Esc' key is pressed, break the while loop.
        //If any other key is pressed, continue the loop
        //If any key is not pressed within 10 milliseconds, continue the loop
        Sleep(10);
    }

    //Flush and close the video file
    oVideoWriter.release();
}
void CQBPTabPageSWDebug::OnBtnLoadMatrix()
{
   SearchsCombo->clear();
   AlignmentsCombo->clear();

   if(pQBPSearchList.size()>0)
   {
       pQBPSearchList.clear();
       //Sempre colocar o reserve zero para economizar memoria(O clear não limpa a reserva de espaço)
       pQBPSearchList.shrink_to_fit();
   }

   pQBPEngine->pQBPComparator->pQBPSearchResults->getSearchList(pQBPSearchList);

   for(uint i=0;i<(uint)pQBPSearchList.size();i++)
   {
       QString SearchType;

       switch(pQBPSearchList[i].iQBPComparatorType)
       {
       case QBP_MATRIX_TYPE_ORIGIN:{SearchType = QString("SW");}break;
       case QBP_MATRIX_TYPE_MUSSUM:{SearchType = QString("MUSSUM");}break;
       case QBP_MATRIX_TYPE_MUSSIX:{SearchType = QString("MUSSIX");}break;
       case QBP_MATRIX_TYPE_MUSSAT:{SearchType = QString("MUSSAT");}break;
       }

       SearchsCombo->addItem(QString("Search %1").arg(pQBPSearchList[i].getId()) + QString(" - ") + SearchType ,pQBPSearchList[i].getId());
   }
}

void CQBPTabPageSWDebug::OnBtnPlay()
{
    pPlayDebbug = true;
    //Connect the Status Loop
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(PlayLoop()));
    timer->start(250);
}

void CQBPTabPageSWDebug::OnBtnRecord()
{
    pPlayDebbug = true;

    pDebbugMovie.clear();
    //Sempre colocar o reserve zero para economizar memoria(O clear não limpa a reserva de espaço)
    pDebbugMovie.shrink_to_fit();

    //Connect the Status Loop
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(RecordLoop()));
    timer->start(250);
}

void CQBPTabPageSWDebug::OnBoxSearchSel(int selection)
{
    CQBPSearch *tSearch;

    AlignmentsCombo->clear();
    tSearch = pQBPEngine->GetSearch(selection);

    for(uint i=0;i<(uint)tSearch->pQBPSearchAlignments.size();i++)
    {
        AlignmentsCombo->addItem(QString("Aligment %1").arg(tSearch->pQBPSearchAlignments[i]->getId()),
                                                            tSearch->pQBPSearchAlignments[i]->getId());
    }
}

void CQBPTabPageSWDebug::OnBoxAlignmentsSel(int selection)
{
    CQBPSearch *tSearch;

    TracebacksCombo->clear();
    tSearch = pQBPEngine->GetSearch(SearchsCombo->currentIndex());

    for(uint j=0;j<(uint)tSearch->pQBPSearchAlignments[selection]->iQBPResultQtdPaths;j++)
    {
       TracebacksCombo->addItem(QString("Traceback %1").arg(j),j);
    }

   SWGraph->FillDebbug(pQBPEngine->GetSearch(SearchsCombo->currentIndex()),selection);
}

void CQBPTabPageSWDebug::OnBoxTracebacksSel(int selection)
{
   SWGraph->FillDebbug(pQBPEngine->GetSearch(SearchsCombo->currentIndex()),AlignmentsCombo->currentIndex(),selection);
}

void CQBPTabPageSWDebug::OnSliderSel(int selection)
{
   SWGraph->SetNodes(selection);
}

void CQBPTabPageSWDebug::setEngineReference(CQBPEngine *pQBP_Engine)
{
    pQBPEngine = pQBP_Engine;
}

void CQBPTabPageSWDebug::PlayLoop()
{
    int pos = pQBPFrameSlider->sliderPosition();

    if(pPlayDebbug)
    {
       if(pos==100)
       {
           if(!disconnect(timer, SIGNAL(timeout()), this, SLOT(PlayLoop())))
           {
               qWarning("Nao desconectou");
           }

           pQBPFrameSlider->setSliderPosition(0);
           pPlayDebbug = false;
       }
       else
       {
          pQBPFrameSlider->setSliderPosition(pos+1);
       }
    }
}

void CQBPTabPageSWDebug::RecordLoop()
{
    QPixmap frame;
    int pos = pQBPFrameSlider->sliderPosition();

    if(pPlayDebbug)
    {
       if(pos==100)
       {
           //frame = SWGraph->grab(SWGraph->sceneRect().toRect());
           frame = grab();
           pDebbugMovie.push_back(frame);

           if(!disconnect(timer, SIGNAL(timeout()), this, SLOT(RecordLoop())))
           {
               qWarning("Nao desconectou");
           }

           pQBPFrameSlider->setSliderPosition(0);
           pPlayDebbug = false;
       }
       else
       {
          //frame = SWGraph->grab(SWGraph->sceneRect().toRect());
          frame = grab();
          pDebbugMovie.push_back(frame);
          pQBPFrameSlider->setSliderPosition(pos+1);
       }
    }
}



