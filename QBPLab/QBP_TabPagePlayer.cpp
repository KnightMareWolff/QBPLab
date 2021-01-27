#include "QBP_TabPagePlayer.h"

using namespace QtConcurrent;
CQBPEngine * CQBPTabPagePlayer::pQBPEngine=nullptr;
QString      CQBPTabPagePlayer::pQBPPreviewName;

void PlaySongItem()
{
   CQBPTabPagePlayer::pQBPEngine->PlaySongByName(CQBPTabPagePlayer::pQBPPreviewName);
}

void PlayMusicPlayer()
{
   CQBPTabPagePlayer::pQBPEngine->MusicPlayer();
}

CQBPTabPagePlayer::CQBPTabPagePlayer(QWidget *parent) : QWidget(parent)
{
    //Grupo Principal
    QGroupBox   *GrupoPrincipal  = new QGroupBox(tr(""));
    QVBoxLayout *LayoutPrincipal = new QVBoxLayout;

    QPushButton *Play             = new QPushButton(tr("Play Music Item"));
    QPushButton *MusicPlayer      = new QPushButton(tr("Start Music Player"));

    LayoutPrincipal->addWidget(Play);
    LayoutPrincipal->addWidget(MusicPlayer);

    GrupoPrincipal->setLayout(LayoutPrincipal);

    setLayout(LayoutPrincipal);

    connect(Play           , SIGNAL(clicked()), this, SLOT(OnBtnPlay()));
    connect(MusicPlayer    , SIGNAL(clicked()), this, SLOT(OnBtnMusicPlayer()));

}

void CQBPTabPagePlayer::setEngineReference(CQBPEngine *pQBP_Engine)
{
    pQBPEngine = pQBP_Engine;
}

void CQBPTabPagePlayer::OnBtnPlay()
{

   //pQBPPreviewName = EditTreeItemValue->text();
   pQBPPreviewName = "BAR0012WholeLottaLoveMono";
   qQBPDatasetThread = QtConcurrent::run(PlaySongItem);
}

void CQBPTabPagePlayer::OnBtnMusicPlayer()
{
   qQBPDatasetThread = QtConcurrent::run(PlayMusicPlayer);
}
