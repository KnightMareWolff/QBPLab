#include "QBP_Chord.h"

CQBPChord::CQBPChord()
{
   sQBPChordName = "Default";
}

CQBPChord::CQBPChord(const CQBPChord &obj)
{
    //Dados Acorde
    if(pQBPChordBuffer.size()>0)
    {
        pQBPChordBuffer.clear();
        //Sempre colocar o reserve zero para economizar memoria(O clear não limpa a reserva de espaço)
        pQBPChordBuffer.shrink_to_fit();
    }

    for(uint i=0;i< (uint)obj.pQBPChordBuffer.size();i++)
    {
        pQBPChordBuffer.push_back(obj.pQBPChordBuffer[i]);
    }

    sQBPChordName = obj.sQBPChordName;
}

CQBPChord & CQBPChord::operator = (const CQBPChord& other)
{
    //Dados Acorde
    if(pQBPChordBuffer.size()>0)
    {
        pQBPChordBuffer.clear();
        //Sempre colocar o reserve zero para economizar memoria(O clear não limpa a reserva de espaço)
        pQBPChordBuffer.shrink_to_fit();
    }

    for(uint i=0;i< (uint)other.pQBPChordBuffer.size();i++)
    {
        pQBPChordBuffer.push_back(other.pQBPChordBuffer[i]);
    }

    sQBPChordName = other.sQBPChordName;

    return *this;
}

CQBPChord::~CQBPChord()
{
    //Dados MIDI
    pQBPChordBuffer.clear();
    //Sempre colocar o reserve zero para economizar memoria(O clear não limpa a reserva de espaço)
    pQBPChordBuffer.shrink_to_fit();

}

void CQBPChord::AddNote(stQBPMusicBuffer pQBPNote)
{
    pQBPChordBuffer.push_back(pQBPNote);
}

void CQBPChord::SetName(QString pQBPChordName)
{
    sQBPChordName=pQBPChordName;
}
