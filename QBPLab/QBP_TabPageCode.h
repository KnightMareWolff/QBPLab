#ifndef QBP_TABPAGECODE_H
#define QBP_TABPAGECODE_H

#include "QBP_GlobalDef.h"
#include "QBP_Engine.h"
#include "QBP_LogQueue.h"
#include "QBP_ScriptObjectsBind.h"

class CQBPTabPageCode : public QWidget
{
    Q_OBJECT
public:
    explicit CQBPTabPageCode(QWidget *parent = nullptr);

    virtual ~CQBPTabPageCode(){}

    void setEngineReference(CQBPEngine *pQBP_Engine);

    //Static Definitios for Engine Information access
    static CQBPEngine *pQBPEngine;
    //Dados Para execução Lua
    static lua_State*  L;
    static QTextEdit   *pQBP_Program;

public slots:
    void OnBtnExecSelection();
    void OnBtnAbortExec();

private:

    QPushButton  *ExecSelection;
    QPushButton  *ExecAbort;
    QComboBox    *ExecuttnCombo;

    //Dados Do Programa e Formato do Texto
    QTextCharFormat pQBPProgramFormat;

    //Calculo do Timer de Eventos
    QTimer        *timer;

    //Para calculos de tempo de Processo
    time_t          pQBPActualTime;
    struct tm      *pQBPStartSTime;
    struct tm      *pQBPFinishTime;

    QFuture<void> qQBPScriptThread;

};

#endif // QBP_TABPAGECODE_H
