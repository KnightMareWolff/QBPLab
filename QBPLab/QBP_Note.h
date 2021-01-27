/*************************************************************************/
/*PPGIa - Advanced Topics in Computational Intelligence - PUCPR          */
/*Author: William Wolff                                                  */
/*Classe Note - O objetivo principal da classe Note é armazenar features */
/*contidas em uma nota pertencente a uma musica                          */
/*************************************************************************/
#ifndef QBP_NOTE_H_
#define QBP_NOTE_H_

#include "QBP_GlobalDef.h"

class CQBPNote
{
public:
     CQBPNote(                    );
     CQBPNote( const CQBPNote &obj);
    ~CQBPNote(                    );

     CQBPNote & operator = (const CQBPNote& other);

    double tick;
    double duration;
    int    pitch;
    int    command;

};

#endif

