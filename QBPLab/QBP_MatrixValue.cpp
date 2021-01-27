#include "QBP_MatrixValue.h"



CQBPMatrixValue::CQBPMatrixValue()
{
    iQBPRefX     = 0;
    iQBPRefY     = 0;
    iQBPValue     = 0;
    iQBPDirection = 0;
    bQBPMatch = false;

    //debug values
    iQBPTopo      = 0;
    iQBPDiagonal  = 0;
    iQBPLado      = 0;
    iQBPMatch     = 0;
    iQBPMissMatch = 0;
    iQBPGap       = 0;
}

CQBPMatrixValue::CQBPMatrixValue(const CQBPMatrixValue &obj)
{
    iQBPRefX      = obj.iQBPRefX;
    iQBPRefY      = obj.iQBPRefY;
    iQBPValue     = obj.iQBPValue;
    iQBPDirection = obj.iQBPDirection;
    bQBPMatch     = obj.bQBPMatch;

    //debug values
    iQBPTopo      = obj.iQBPTopo;
    iQBPDiagonal  = obj.iQBPDiagonal;
    iQBPLado      = obj.iQBPLado;
    iQBPMatch     = obj.iQBPMatch;
    iQBPMissMatch = obj.iQBPMissMatch;
    iQBPGap       = obj.iQBPGap;
}

CQBPMatrixValue & CQBPMatrixValue::operator = (const CQBPMatrixValue& other)
{
    iQBPRefX      = other.iQBPRefX;
    iQBPRefY      = other.iQBPRefY;
    iQBPValue     = other.iQBPValue;
    iQBPDirection = other.iQBPDirection;
    bQBPMatch     = other.bQBPMatch;

    //debug values
    iQBPTopo      = other.iQBPTopo;
    iQBPDiagonal  = other.iQBPDiagonal;
    iQBPLado      = other.iQBPLado;
    iQBPMatch     = other.iQBPMatch;
    iQBPMissMatch = other.iQBPMissMatch;
    iQBPGap       = other.iQBPGap;

    return *this;
}

CQBPMatrixValue::CQBPMatrixValue(int pQBPValue, int pQBPDirection , bool pQBPMatch )
{
    iQBPRefX      = 0;
    iQBPRefY      = 0;
    iQBPValue     = pQBPValue;
    iQBPDirection = pQBPDirection;
    bQBPMatch     = pQBPMatch;
}

CQBPMatrixValue::CQBPMatrixValue(int pQBPValue, int pQBPDirection , bool pQBPMatch , int pRefX,int pRefY)
{
    iQBPRefX       = pRefX;
    iQBPRefY       = pRefY;
    iQBPValue      = pQBPValue;
    iQBPDirection  = pQBPDirection;
    bQBPMatch      = pQBPMatch;
}

CQBPMatrixValue::~CQBPMatrixValue()
{
}

void CQBPMatrixValue::RegisterDebugInfo(int    piQBPTopo     ,
                                        int    piQBPDiagonal ,
                                        int    piQBPLado     ,
                                        int    piQBPMatch    ,
                                        int    piQBPMissMatch,
                                        int    piQBPGap      )
{
    iQBPTopo      =piQBPTopo;
    iQBPDiagonal  =piQBPDiagonal;
    iQBPLado      =piQBPLado;
    iQBPMatch     =piQBPMatch;
    iQBPMissMatch =piQBPMissMatch;
    iQBPGap       =piQBPGap;
}
