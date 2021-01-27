/*************************************************************************/
/*PPGIa - Advanced Topics in Computational Intelligence - PUCPR          */
/*Author: William Wolff                                                  */
/*Classe Song - O objetivo principal da classe Song é armazenar features */
/*contidas em uma musica, incluindo a lista de notas musicais            */
/*************************************************************************/
#ifndef QBP_GENRE_H_
#define QBP_GENRE_H_

#include "QBP_GlobalDef.h"
#include "QBP_Song.h"

class CQBPGenre
{
public:
     CQBPGenre(                     );
     CQBPGenre( const CQBPGenre &obj);
     CQBPGenre(string pQBPName      );
    ~CQBPGenre(                     );

//private:
    string            pQBPGenreName;//Nome do Gênero
    vector<CQBPSong>  pQBPSongList;//Lista de Musicas do genero principal
};

#endif
