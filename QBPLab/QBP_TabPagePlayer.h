#ifndef QBP_TABPAGEPLAYER_H
#define QBP_TABPAGEPLAYER_H

#include "QBP_GlobalDef.h"
#include "QBP_Engine.h"

class CQBPTabPagePlayer : public QWidget
{
    Q_OBJECT
public:
    explicit CQBPTabPagePlayer(QWidget *parent = nullptr);
    void setEngineReference(CQBPEngine *pQBP_Engine);

    //Engine Members
    static CQBPEngine *pQBPEngine;
    static QString     pQBPPreviewName;

signals:

public slots:
    void OnBtnPlay();
    void OnBtnMusicPlayer();

private:

    QFuture<void> qQBPDatasetThread;

    //Calculo do Timer de Eventos
    QTimer        *timer;

    //Para calculos de tempo de Processo
    time_t          pQBPActualTime;
    struct tm      *pQBPStartSTime;
    struct tm      *pQBPFinishTime;

};

#endif // QBP_TABPAGEPLAYER_H
