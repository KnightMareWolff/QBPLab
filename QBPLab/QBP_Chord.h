#ifndef QBP_CHORD_H
#define QBP_CHORD_H

#include "QBP_GlobalDef.h"
#include "QBP_Note.h"
#include "QBP_Feature.h"

class CQBPChord
{
public:
    CQBPChord(                     );
    CQBPChord( const CQBPChord &obj);
   ~CQBPChord(                     );

    CQBPChord & operator = (const CQBPChord& other);

    void AddNote(stQBPMusicBuffer pQBPNote     );
    void SetName(QString          pQBPChordName);

    vector<stQBPMusicBuffer > pQBPChordBuffer;
    QString sQBPChordName;
};

#endif // QBP_CHORD_H
