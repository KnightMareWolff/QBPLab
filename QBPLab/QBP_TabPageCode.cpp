#include "QBP_TabPageCode.h"
#include "QBP_ScriptObjects.h"

using namespace QtConcurrent;

CQBPEngine * CQBPTabPageCode::pQBPEngine=nullptr;
lua_State  * CQBPTabPageCode::L;
QTextEdit  * CQBPTabPageCode::pQBP_Program;

void FireUpScript()
{
    string selection = CQBPTabPageCode::pQBP_Program->toPlainText().toStdString();

    CQBPTabPageCode::L = luaL_newstate();
    if(CQBPTabPageCode::L == NULL)
    {
        QMessageBox::information(0, "QBPLab",
                                    "Scripting Interface Error.");
    }

    //Inicializa todas as bibliotecas Lua
    luaL_openlibs(CQBPTabPageCode::L);

    //Faz o Bind dos objetos exportados para o Contexto Lua Criado
    tolua_ObjetosExportados_open(CQBPTabPageCode::L);

    //Executa o Script Principal
    luaL_dostring(CQBPTabPageCode::L, selection.c_str());

    const char * str = lua_tostring(CQBPTabPageCode::L, -1);

    CQBPTabPageCode::pQBP_Program->insertPlainText("\n \n");
    CQBPTabPageCode::pQBP_Program->insertPlainText("=====================================================\n");
    CQBPTabPageCode::pQBP_Program->insertPlainText("Resultado: \n");
    CQBPTabPageCode::pQBP_Program->insertPlainText(str);
    CQBPTabPageCode::pQBP_Program->insertPlainText("=====================================================\n");

    //Fecha o contexto de execução do script
    lua_close (CQBPTabPageCode::L);
}

bool QBPSearchEngine::Search(char *SearchName     ,
                             char *SongAName      ,
                             int   DatasetType    ,
                             int   ComparatorType ,
                             bool  UseAttitude    )
{
    switch(DatasetType)
    {
    case QBP_LIST_TESTSET:{return CQBPTabPageCode::pQBPEngine->Search(SearchName,SongAName,QBP_LOAD_TARGET_TESTSET,ComparatorType,UseAttitude);}break;
    case QBP_LIST_VALISET:{return CQBPTabPageCode::pQBPEngine->Search(SearchName,SongAName,QBP_LOAD_TARGET_VALISET,ComparatorType,UseAttitude);}break;
    case QBP_LIST_RANDSET:{return CQBPTabPageCode::pQBPEngine->Search(SearchName,SongAName,QBP_LOAD_TARGET_RANDSET,ComparatorType,UseAttitude);}break;
    case QBP_LIST_FULLSET:{return CQBPTabPageCode::pQBPEngine->Search(SearchName,SongAName,QBP_LOAD_TARGET_FULLSET,ComparatorType,UseAttitude);}break;
    }

    return false;
}

bool QBPSearchEngine::Search(char *SearchName     ,
                             int   SongAId        ,
                             int   DatasetType    ,
                             int   ComparatorType ,
                             bool  UseAttitude    )
{
    QString Name;
    int     QtdNotes;
    int     Score;

    switch(DatasetType)
    {
    case QBP_LIST_TESTSET:{CQBPTabPageCode::pQBPEngine->GetListData(QBP_LOAD_TARGET_TESTSET,SongAId,Name,QtdNotes,Score);}break;
    case QBP_LIST_VALISET:{CQBPTabPageCode::pQBPEngine->GetListData(QBP_LOAD_TARGET_VALISET,SongAId,Name,QtdNotes,Score);}break;
    case QBP_LIST_RANDSET:{CQBPTabPageCode::pQBPEngine->GetListData(QBP_LOAD_TARGET_RANDSET,SongAId,Name,QtdNotes,Score);}break;
    case QBP_LIST_FULLSET:{CQBPTabPageCode::pQBPEngine->GetListData(QBP_LOAD_TARGET_FULLSET,SongAId,Name,QtdNotes,Score);}break;
    }

    switch(DatasetType)
    {
    case QBP_LIST_TESTSET:{return CQBPTabPageCode::pQBPEngine->Search(SearchName,Name.toStdString(),QBP_LOAD_TARGET_TESTSET,ComparatorType,UseAttitude);}break;
    case QBP_LIST_VALISET:{return CQBPTabPageCode::pQBPEngine->Search(SearchName,Name.toStdString(),QBP_LOAD_TARGET_VALISET,ComparatorType,UseAttitude);}break;
    case QBP_LIST_RANDSET:{return CQBPTabPageCode::pQBPEngine->Search(SearchName,Name.toStdString(),QBP_LOAD_TARGET_RANDSET,ComparatorType,UseAttitude);}break;
    case QBP_LIST_FULLSET:{return CQBPTabPageCode::pQBPEngine->Search(SearchName,Name.toStdString(),QBP_LOAD_TARGET_FULLSET,ComparatorType,UseAttitude);}break;
    }

    return false;
}

void QBPSearchEngine::SetPrecisionBalance(int Precision)
{
    CQBPTabPageCode::pQBPEngine->SetPrecision(Precision);
}

void QBPSearchEngine::SetResultSizeBalance(int ResultSize)
{
    CQBPTabPageCode::pQBPEngine->SetResultSize(ResultSize);
}

void QBPSearchEngine::SetBufferSize(int BufferSize)
{
    CQBPTabPageCode::pQBPEngine->SetBufferSize(BufferSize);
}

void QBPSearchEngine::SetPProcType(int PProcType)
{
    CQBPTabPageCode::pQBPEngine->SetAlgPosProc(PProcType);
}

void QBPSearchEngine::CreateList(int DatasetType , int CreationFormula)
{
    switch(DatasetType)
    {
    case QBP_LIST_TESTSET:{CQBPTabPageCode::pQBPEngine->BuildTestSet  (CreationFormula);CQBPTabPageCode::pQBPEngine->FillTestSet(QBP_LOAD_TARGET_TESTSET);}break;
    case QBP_LIST_VALISET:{CQBPTabPageCode::pQBPEngine->BuildValiSet  (CreationFormula);CQBPTabPageCode::pQBPEngine->FillTestSet(QBP_LOAD_TARGET_VALISET);}break;
    case QBP_LIST_RANDSET:{CQBPTabPageCode::pQBPEngine->BuildRandomSet(CreationFormula);CQBPTabPageCode::pQBPEngine->FillTestSet(QBP_LOAD_TARGET_RANDSET);}break;
    case QBP_LIST_FULLSET:{CQBPTabPageCode::pQBPEngine->BuildFullSet  (               );CQBPTabPageCode::pQBPEngine->FillTestSet(QBP_LOAD_TARGET_FULLSET);}break;
    }
}

int QBPSearchEngine::GetListSize(int DatasetType)
{

    switch(DatasetType)
    {
    case QBP_LIST_TESTSET:{return CQBPTabPageCode::pQBPEngine->ListGetSize(QBP_LOAD_TARGET_TESTSET);}break;
    case QBP_LIST_VALISET:{return CQBPTabPageCode::pQBPEngine->ListGetSize(QBP_LOAD_TARGET_VALISET);}break;
    case QBP_LIST_RANDSET:{return CQBPTabPageCode::pQBPEngine->ListGetSize(QBP_LOAD_TARGET_RANDSET);}break;
    case QBP_LIST_FULLSET:{return CQBPTabPageCode::pQBPEngine->ListGetSize(QBP_LOAD_TARGET_FULLSET);}break;
    }
}

char *QBPSearchEngine::GetListSongName(int DatasetType, int pQBPMusicId)
{
    QString Name;
    int     QtdNotes;
    int     Score;
    char*   ReturnName;

    switch(DatasetType)
    {
    case QBP_LIST_TESTSET:{CQBPTabPageCode::pQBPEngine->GetListData(QBP_LOAD_TARGET_TESTSET,pQBPMusicId,Name,QtdNotes,Score);}break;
    case QBP_LIST_VALISET:{CQBPTabPageCode::pQBPEngine->GetListData(QBP_LOAD_TARGET_VALISET,pQBPMusicId,Name,QtdNotes,Score);}break;
    case QBP_LIST_RANDSET:{CQBPTabPageCode::pQBPEngine->GetListData(QBP_LOAD_TARGET_RANDSET,pQBPMusicId,Name,QtdNotes,Score);}break;
    case QBP_LIST_FULLSET:{CQBPTabPageCode::pQBPEngine->GetListData(QBP_LOAD_TARGET_FULLSET,pQBPMusicId,Name,QtdNotes,Score);}break;
    }

    ReturnName = new char[Name.size()];

    for(int i=0;i<Name.size();i++)ReturnName[i]=(char)Name.at(i).cell();

    ReturnName[Name.size()]= '\0';

    return ReturnName;
}

int QBPSearchEngine::GetListSongNotes(int DatasetType, int pQBPMusicId)
{
    QString Name;
    int     QtdNotes;
    int     Score;

    switch(DatasetType)
    {
    case QBP_LIST_TESTSET:{CQBPTabPageCode::pQBPEngine->GetListData(QBP_LOAD_TARGET_TESTSET,pQBPMusicId,Name,QtdNotes,Score);}break;
    case QBP_LIST_VALISET:{CQBPTabPageCode::pQBPEngine->GetListData(QBP_LOAD_TARGET_VALISET,pQBPMusicId,Name,QtdNotes,Score);}break;
    case QBP_LIST_RANDSET:{CQBPTabPageCode::pQBPEngine->GetListData(QBP_LOAD_TARGET_RANDSET,pQBPMusicId,Name,QtdNotes,Score);}break;
    case QBP_LIST_FULLSET:{CQBPTabPageCode::pQBPEngine->GetListData(QBP_LOAD_TARGET_FULLSET,pQBPMusicId,Name,QtdNotes,Score);}break;
    }

    return QtdNotes;
}

int QBPSearchEngine::GetListSongScore(int DatasetType, int pQBPMusicId)
{
    QString Name;
    int     QtdNotes;
    int     Score;

    switch(DatasetType)
    {
    case QBP_LIST_TESTSET:{CQBPTabPageCode::pQBPEngine->GetListData(QBP_LOAD_TARGET_TESTSET,pQBPMusicId,Name,QtdNotes,Score);}break;
    case QBP_LIST_VALISET:{CQBPTabPageCode::pQBPEngine->GetListData(QBP_LOAD_TARGET_VALISET,pQBPMusicId,Name,QtdNotes,Score);}break;
    case QBP_LIST_RANDSET:{CQBPTabPageCode::pQBPEngine->GetListData(QBP_LOAD_TARGET_RANDSET,pQBPMusicId,Name,QtdNotes,Score);}break;
    case QBP_LIST_FULLSET:{CQBPTabPageCode::pQBPEngine->GetListData(QBP_LOAD_TARGET_FULLSET,pQBPMusicId,Name,QtdNotes,Score);}break;
    }

    return Score;
}

void QBPSearchEngine::PushLog(char* pQBPLogString)
{
    CQBPLogQueue::Push(QString(pQBPLogString));
}

QBPSearchEngine::QBPSearchEngine()
{

}

QBPSearchEngine::~QBPSearchEngine()
{

}

CQBPTabPageCode::CQBPTabPageCode(QWidget *parent) : QWidget(parent)
{

    //Grupo de Criação
    QGroupBox *GrupoComandos = new QGroupBox(tr("Automation Commands:"));
    QGroupBox *GrupoPrincipal = new QGroupBox(tr("TESTE"));

    QHBoxLayout *LayoutComandos = new QHBoxLayout;
    ExecSelection = new QPushButton(tr("Execute Code"));
    ExecAbort     = new QPushButton(tr("Abort Execution"));

    ExecuttnCombo = new QComboBox;
    ExecuttnCombo->addItem(QString("Execute Selection"),0);
    ExecuttnCombo->addItem(QString("Execute Program"),1);

    LayoutComandos->addWidget(ExecSelection);
    LayoutComandos->addWidget(ExecAbort);
    LayoutComandos->addWidget(ExecuttnCombo);

    GrupoComandos->setLayout(LayoutComandos);

    pQBP_Program = new QTextEdit(this);
    pQBPProgramFormat.setFont(QFont("Courier New",8, QFont::Courier));
    pQBP_Program->setCurrentCharFormat(pQBPProgramFormat);

    //Inclui os Grupos no Layout Principal
    QVBoxLayout *LayoutPrincipal = new QVBoxLayout;
    LayoutPrincipal->addWidget(GrupoComandos);
    LayoutPrincipal->addWidget(pQBP_Program);

    GrupoPrincipal->setLayout(LayoutPrincipal);

    setLayout(LayoutPrincipal);


    connect(ExecSelection , SIGNAL(clicked()), this, SLOT(OnBtnExecSelection()));
    connect(ExecAbort , SIGNAL(clicked()), this, SLOT(OnBtnAbortExec()));


}

void CQBPTabPageCode::setEngineReference(CQBPEngine *pQBP_Engine)
{
    pQBPEngine = pQBP_Engine;
}

void CQBPTabPageCode::OnBtnExecSelection()
{
   qQBPScriptThread = QtConcurrent::run(FireUpScript);
}

void CQBPTabPageCode::OnBtnAbortExec()
{
   qQBPScriptThread.cancel();
}
