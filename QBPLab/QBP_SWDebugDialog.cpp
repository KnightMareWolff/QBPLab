#include "QBP_SWDebugDialog.h"

CQBPSWDebugDialog::CQBPSWDebugDialog()
{

}

CQBPSWDebugDialog::CQBPSWDebugDialog(CQBPSWDebugGraph *pGraph)
{
   pQBPDebugGrid   = new QGridLayout(this);
   pQBPDebugGrid->addWidget(pGraph);
   setLayout(pQBPDebugGrid);
   show();
}
