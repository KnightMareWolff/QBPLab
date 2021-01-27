#include "QBP_Genre.h"

CQBPGenre::CQBPGenre()
{
    pQBPGenreName = "Undefined";
}

CQBPGenre::CQBPGenre(const CQBPGenre &obj)
{
    pQBPGenreName = obj.pQBPGenreName;

    if(pQBPSongList.size()>0)
    {
        pQBPSongList.clear();
        //Sempre colocar o reserve zero para economizar memoria(O clear não limpa a reserva de espaço)
        pQBPSongList.shrink_to_fit();
    }

    for(uint i=0;i< (uint)obj.pQBPSongList.size();i++)
    {
        pQBPSongList.push_back(CQBPSong(obj.pQBPSongList[i]));
    }
}

CQBPGenre::CQBPGenre(string pQBPName)
{
    pQBPGenreName = pQBPName;
}

CQBPGenre::~CQBPGenre()
{
}
