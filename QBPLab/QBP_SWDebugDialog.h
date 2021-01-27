#ifndef QBP_SWDEBUGDIALOG_H
#define QBP_SWDEBUGDIALOG_H
#include "QBP_GlobalDef.h"
#include "QBP_SWDebugGraph.h"

class CQBPSWDebugDialog : public QDialog
{
    Q_OBJECT
public:
    CQBPSWDebugDialog();
    CQBPSWDebugDialog(CQBPSWDebugGraph *pGraph);
private:
    CQBPSWDebugGraph *pGraph;
    QGridLayout      *pQBPDebugGrid;
};

#endif // QBP_SWDEBUGDIALOG_H
