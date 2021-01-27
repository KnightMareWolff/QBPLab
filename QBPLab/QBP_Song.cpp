#include "QBP_Song.h"



CQBPSong::CQBPSong()
{
    pQBPSongCategory=0;//Categoria da musica
    pQBPSongScore   =0;//Score de similaridade da musica
    pQBPSongClassification = QBP_SCH_CLASS_TN;
    //pQBPSongBPM=120;//Beats per minutes da musica
    //pQBPTempoMedioNotas=0.0f;//Tempo medio demandado entre as notas durante a musica.
    //pQBPPitchFrequente=0;//Qual nota é mais frequente na musica
    //pQBPQtdPitchs=0;//Quantas notas sao usadas na musica
    //pQBPRepPitch=0;//Maior numero de repeticoes consecutivas da mesma nota
    //pQBPQtdBemois=0;//Quantidade de Bemois usados na musica
    //pQBPOitavas=0;//Quantidade de Oitavas usadas na musica
    pQBPStripped = false;//indica que houve strip de buffers
    pQBPFeatured = false;//indica que houve calculo de features
}

CQBPSong::CQBPSong(const CQBPSong &obj)
{
    //Dados MIDI
    if(pQBPNotes.size()>0)
    {
        pQBPNotes.clear();
        //Sempre colocar o reserve zero para economizar memoria(O clear não limpa a reserva de espaço)
        pQBPNotes.shrink_to_fit();
    }

    for(uint i=0;i< (uint)obj.pQBPNotes.size();i++)
    {
        pQBPNotes.push_back(CQBPNote(obj.pQBPNotes[i]));
    }

    //Dados Musica para processamento
    pQBPSongName           = obj.pQBPSongName    ;//Nome da musica(filename)
    pQBPOriginalName       = obj.pQBPOriginalName;
    pQBPSongCategoryIndex  = obj.pQBPSongCategoryIndex;//Indice da musica na Categoria
    pQBPSongGlobalIndex    = obj.pQBPSongGlobalIndex;//Indice Global da Musica no Dataset
    pQBPSongCategory       = obj.pQBPSongCategory;//Categoria da musica
    pQBPSongScore          = obj.pQBPSongScore   ;//Score de similaridade da musica
    pQBPSongClassification = obj.pQBPSongClassification;//Classificação na Busca(TN,FN,TP,FP)
    pQBPStripped           = obj.pQBPStripped    ;//indica que houve strip de buffers
    pQBPFeatured           = obj.pQBPFeatured    ;//indica que houve calculo de features

    //Song Buffers
    pQBPSongBuffer  = obj.pQBPSongBuffer   ;//Buffer de notas diatonicas da musica completa
    //Song Buffer Strips
    if(pQBPSongBufferStrip.size()>0)
    {
        pQBPSongBufferStrip.clear();
        //Sempre colocar o reserve zero para economizar memoria(O clear não limpa a reserva de espaço)
        pQBPSongBufferStrip.shrink_to_fit();
    }

    for(uint i=0;i< (uint)obj.pQBPSongBufferStrip.size();i++)
    {
        pQBPSongBufferStrip.push_back(obj.pQBPSongBufferStrip[i]);
    }

    //Song Mussix Buffer
    if(pQBPMusixBuffer.size()>0)
    {
        pQBPMusixBuffer.clear();
        //Sempre colocar o reserve zero para economizar memoria(O clear não limpa a reserva de espaço)
        pQBPMusixBuffer.shrink_to_fit();
    }
    for(uint i=0;i< (uint)obj.pQBPMusixBuffer.size();i++)
    {
        pQBPMusixBuffer.push_back(obj.pQBPMusixBuffer[i]);
    }

    //Song Mussix Begin
    if(pQBPMusixBegin.size()>0)
    {
        pQBPMusixBegin.clear();
        //Sempre colocar o reserve zero para economizar memoria(O clear não limpa a reserva de espaço)
        pQBPMusixBegin.shrink_to_fit();
    }

    for(uint i=0;i< (uint)obj.pQBPMusixBegin.size();i++)
    {
        pQBPMusixBegin.push_back(obj.pQBPMusixBegin[i]);
    }

    //Song Mussix Mid
    if(pQBPMusixMid.size()>0)
    {
        pQBPMusixMid.clear();
        //Sempre colocar o reserve zero para economizar memoria(O clear não limpa a reserva de espaço)
        pQBPMusixMid.shrink_to_fit();
    }
    for(uint i=0;i< (uint)obj.pQBPMusixMid.size();i++)
    {
        pQBPMusixMid.push_back(obj.pQBPMusixMid[i]);
    }

    //Song Mussix End
    if(pQBPMusixEnd.size()>0)
    {
        pQBPMusixEnd.clear();
        //Sempre colocar o reserve zero para economizar memoria(O clear não limpa a reserva de espaço)
        pQBPMusixEnd.shrink_to_fit();
    }

    for(uint i=0;i< (uint)obj.pQBPMusixEnd.size();i++)
    {
        pQBPMusixEnd.push_back(obj.pQBPMusixEnd[i]);
    }

    //Features da Musica
    if(pQBPFeatures.size()>0)
    {
        pQBPFeatures.clear();
        //Sempre colocar o reserve zero para economizar memoria(O clear não limpa a reserva de espaço)
        pQBPFeatures.shrink_to_fit();
    }

    for(uint i=0;i< (uint)obj.pQBPFeatures.size();i++)
    {
        pQBPFeatures.push_back(obj.pQBPFeatures[i]);
    }

    //Custom Features
    if(pQBPCustomFeatures.size()>0)
    {
        pQBPCustomFeatures.clear();
        //Sempre colocar o reserve zero para economizar memoria(O clear não limpa a reserva de espaço)
        pQBPCustomFeatures.shrink_to_fit();
    }

    for(uint i=0;i< (uint)obj.pQBPCustomFeatures.size();i++)
    {
        pQBPCustomFeatures.push_back(obj.pQBPCustomFeatures[i]);
    }

    //JSymbolic Features
    if(pQBPJSymboFeatures.size()>0)
    {
        pQBPJSymboFeatures.clear();
        //Sempre colocar o reserve zero para economizar memoria(O clear não limpa a reserva de espaço)
        pQBPJSymboFeatures.shrink_to_fit();
    }

    for(uint i=0;i< (uint)obj.pQBPJSymboFeatures.size();i++)
    {
        pQBPJSymboFeatures.push_back(obj.pQBPJSymboFeatures[i]);
    }

    //Normal Features
    if(pQBPNormalFeatures.size()>0)
    {
        pQBPNormalFeatures.clear();
        //Sempre colocar o reserve zero para economizar memoria(O clear não limpa a reserva de espaço)
        pQBPNormalFeatures.shrink_to_fit();
    }

    for(uint i=0;i< (uint)obj.pQBPNormalFeatures.size();i++)
    {
        pQBPNormalFeatures.push_back(obj.pQBPNormalFeatures[i]);
    }
}

CQBPSong & CQBPSong::operator = (const CQBPSong& other)
{
    //Dados MIDI
    if(pQBPNotes.size()>0)
    {
        pQBPNotes.clear();
        //Sempre colocar o reserve zero para economizar memoria(O clear não limpa a reserva de espaço)
        pQBPNotes.shrink_to_fit();
    }

    for(uint i=0;i< (uint)other.pQBPNotes.size();i++)
    {
        pQBPNotes.push_back(CQBPNote(other.pQBPNotes[i]));
    }

    //Dados Musica para processamento
    pQBPSongName           = other.pQBPSongName    ;//Nome da musica(filename)
    pQBPOriginalName       = other.pQBPOriginalName;
    pQBPSongCategoryIndex  = other.pQBPSongCategoryIndex;//Indice da musica na Categoria
    pQBPSongGlobalIndex    = other.pQBPSongGlobalIndex;//Indice Global da Musica no Dataset
    pQBPSongCategory       = other.pQBPSongCategory;//Categoria da musica
    pQBPSongScore          = other.pQBPSongScore   ;//Score de similaridade da musica
    pQBPSongClassification = other.pQBPSongClassification;//Classificação na Busca(TN,FN,TP,FP)
    pQBPStripped           = other.pQBPStripped    ;//indica que houve strip de buffers
    pQBPFeatured           = other.pQBPFeatured    ;//indica que houve calculo de features

    //Song Buffers
    pQBPSongBuffer  = other.pQBPSongBuffer   ;//Buffer de notas diatonicas da musica completa

    //Song Buffer Strips
    if(pQBPSongBufferStrip.size()>0)
    {
        pQBPSongBufferStrip.clear();
        //Sempre colocar o reserve zero para economizar memoria(O clear não limpa a reserva de espaço)
        pQBPSongBufferStrip.shrink_to_fit();
    }
    for(uint i=0;i< (uint)other.pQBPSongBufferStrip.size();i++)
    {
        pQBPSongBufferStrip.push_back(other.pQBPSongBufferStrip[i]);
    }

    //Song Mussix Buffer
    if(pQBPMusixBuffer.size()>0)
    {
        pQBPMusixBuffer.clear();
        //Sempre colocar o reserve zero para economizar memoria(O clear não limpa a reserva de espaço)
        pQBPMusixBuffer.shrink_to_fit();
    }

    for(uint i=0;i< (uint)other.pQBPMusixBuffer.size();i++)
    {
        pQBPMusixBuffer.push_back(other.pQBPMusixBuffer[i]);
    }

    //Song Mussix Begin
    if(pQBPMusixBegin.size()>0)
    {
        pQBPMusixBegin.clear();
        //Sempre colocar o reserve zero para economizar memoria(O clear não limpa a reserva de espaço)
        pQBPMusixBegin.shrink_to_fit();
    }
    for(uint i=0;i< (uint)other.pQBPMusixBegin.size();i++)
    {
        pQBPMusixBegin.push_back(other.pQBPMusixBegin[i]);
    }

    //Song Mussix Mid
    if(pQBPMusixMid.size()>0)
    {
        pQBPMusixMid.clear();
        //Sempre colocar o reserve zero para economizar memoria(O clear não limpa a reserva de espaço)
        pQBPMusixMid.shrink_to_fit();
    }

    for(uint i=0;i< (uint)other.pQBPMusixMid.size();i++)
    {
        pQBPMusixMid.push_back(other.pQBPMusixMid[i]);
    }

    //Song Mussix End
    if(pQBPMusixEnd.size()>0)
    {
        pQBPMusixEnd.clear();
        //Sempre colocar o reserve zero para economizar memoria(O clear não limpa a reserva de espaço)
        pQBPMusixEnd.shrink_to_fit();
    }

    for(uint i=0;i< (uint)other.pQBPMusixEnd.size();i++)
    {
        pQBPMusixEnd.push_back(other.pQBPMusixEnd[i]);
    }

    //Features da Musica
    if(pQBPFeatures.size()>0)
    {
        pQBPFeatures.clear();
        //Sempre colocar o reserve zero para economizar memoria(O clear não limpa a reserva de espaço)
        pQBPFeatures.shrink_to_fit();
    }

    for(uint i=0;i< (uint)other.pQBPFeatures.size();i++)
    {
        pQBPFeatures.push_back(other.pQBPFeatures[i]);
    }

    //Custom Features
    if(pQBPCustomFeatures.size()>0)
    {
        pQBPCustomFeatures.clear();
        //Sempre colocar o reserve zero para economizar memoria(O clear não limpa a reserva de espaço)
        pQBPCustomFeatures.shrink_to_fit();
    }

    for(uint i=0;i< (uint)other.pQBPCustomFeatures.size();i++)
    {
        pQBPCustomFeatures.push_back(other.pQBPCustomFeatures[i]);
    }

    //JSymbolic Features
    if(pQBPJSymboFeatures.size()>0)
    {
        pQBPJSymboFeatures.clear();
        //Sempre colocar o reserve zero para economizar memoria(O clear não limpa a reserva de espaço)
        pQBPJSymboFeatures.shrink_to_fit();
    }
    for(uint i=0;i< (uint)other.pQBPJSymboFeatures.size();i++)
    {
        pQBPJSymboFeatures.push_back(other.pQBPJSymboFeatures[i]);
    }

    //Normal Features
    if(pQBPNormalFeatures.size()>0)
    {
        pQBPNormalFeatures.clear();
        //Sempre colocar o reserve zero para economizar memoria(O clear não limpa a reserva de espaço)
        pQBPNormalFeatures.shrink_to_fit();
    }
    for(uint i=0;i< (uint)other.pQBPNormalFeatures.size();i++)
    {
        pQBPNormalFeatures.push_back(other.pQBPNormalFeatures[i]);
    }

    return *this;
}
CQBPSong::~CQBPSong()
{
    //Dados MIDI
    pQBPNotes.clear();
    //Sempre colocar o reserve zero para economizar memoria(O clear não limpa a reserva de espaço)
    pQBPNotes.shrink_to_fit();

    pQBPSongName.clear()          ;//Nome da musica(filename)
    //Sempre colocar o reserve zero para economizar memoria(O clear não limpa a reserva de espaço)
    pQBPSongName.shrink_to_fit();

    pQBPOriginalName.clear()      ;//Nome da musica original(no caso de copia alterada)
    //Sempre colocar o reserve zero para economizar memoria(O clear não limpa a reserva de espaço)
    pQBPOriginalName.shrink_to_fit();

    pQBPSongBuffer.clear()         ;//Buffer de notas diatonicas da musica completa
    //Sempre colocar o reserve zero para economizar memoria(O clear não limpa a reserva de espaço)
    pQBPSongBuffer.shrink_to_fit();

    pQBPSongBufferStrip.clear()    ;//vetor de buffers menores da musica
    //Sempre colocar o reserve zero para economizar memoria(O clear não limpa a reserva de espaço)
    pQBPSongBufferStrip.shrink_to_fit();

    pQBPMusixBuffer.clear();//Buffer de features musical(Features de Notas)
    //Sempre colocar o reserve zero para economizar memoria(O clear não limpa a reserva de espaço)
    pQBPMusixBuffer.shrink_to_fit();

    pQBPMusixBegin.clear();//Buffer de features musical(Features de Notas)
    //Sempre colocar o reserve zero para economizar memoria(O clear não limpa a reserva de espaço)
    pQBPMusixBegin.shrink_to_fit();

    pQBPMusixMid.clear()  ;//Buffer de features musical(Features de Notas)
    //Sempre colocar o reserve zero para economizar memoria(O clear não limpa a reserva de espaço)
    pQBPMusixMid.shrink_to_fit();

    pQBPMusixEnd.clear()  ;//Buffer de features musical(Features de Notas)
    //Sempre colocar o reserve zero para economizar memoria(O clear não limpa a reserva de espaço)
    pQBPMusixEnd.shrink_to_fit();

    pQBPFeatures.clear();
    //Sempre colocar o reserve zero para economizar memoria(O clear não limpa a reserva de espaço)
    pQBPFeatures.shrink_to_fit();

    pQBPCustomFeatures.clear();//QBPLab Custom Features
    //Sempre colocar o reserve zero para economizar memoria(O clear não limpa a reserva de espaço)
    pQBPCustomFeatures.shrink_to_fit();

    pQBPJSymboFeatures.clear();//JSymbolic Imported Features
    //Sempre colocar o reserve zero para economizar memoria(O clear não limpa a reserva de espaço)
    pQBPJSymboFeatures.shrink_to_fit();

    pQBPNormalFeatures.clear();//Normalized Features
    //Sempre colocar o reserve zero para economizar memoria(O clear não limpa a reserva de espaço)
    pQBPNormalFeatures.shrink_to_fit();

}

bool CQBPSong::StripBuffer(int pQBPNotesByStrip)
{
    vector<stQBPStringBuffer> tStrip;
    int                       tCount;
    int                       tMusicSegment=0;//informa se esta no inicio / fim ou meio

    stQBPMusicBuffer tMusixNote;

    //Contador de notas por strip
    tCount = 0;
    //Percorre o buffer preenchendo as strips
    for (int i = 0; i < pQBPSongBuffer.size(); i++)
    {
        tStrip.push_back(pQBPSongBuffer[i]);

        tMusixNote.bQBP_IsBemol          = pQBPMusixBuffer[i].bQBP_IsBemol;
        tMusixNote.bQBP_IsSharp          = pQBPMusixBuffer[i].bQBP_IsSharp;
        tMusixNote.dQBP_Duration         = pQBPMusixBuffer[i].dQBP_Duration;
        tMusixNote.dQBP_Frequency        = pQBPMusixBuffer[i].dQBP_Frequency;
        tMusixNote.iQBP_MidiShortMessage = pQBPMusixBuffer[i].iQBP_MidiShortMessage;
        tMusixNote.iQBP_Octave           = pQBPMusixBuffer[i].iQBP_Octave;
        tMusixNote.iQBP_Pitch            = pQBPMusixBuffer[i].iQBP_Pitch;
        tMusixNote.iQBP_Contour          = pQBPMusixBuffer[i].iQBP_Contour;
        tMusixNote.sQBP_Note             = pQBPMusixBuffer[i].sQBP_Note;

        if(tMusicSegment==0)pQBPMusixBegin.push_back(tMusixNote);
        if(tMusicSegment==1)pQBPMusixMid  .push_back(tMusixNote);
        if(tMusicSegment==2)pQBPMusixEnd  .push_back(tMusixNote);

        tCount++;
        //Caso tenha atingido o num maximo de notas por strip/final do buffer
        if (tCount == pQBPNotesByStrip || i == pQBPSongBuffer.size()-1)
        {
            tCount = 0;
            tMusicSegment++;
            pQBPSongBufferStrip.push_back(tStrip);
            tStrip.clear();
        }
    }

    pQBPStripped = true;
    return true;
}

bool CQBPSong::NormStripBuffer(int pQBPNotesByStrip)
{
    vector<stQBPStringBuffer> tStrip;
    int                       tCount;

    stQBPMusicBuffer tMusixNote;

    vector<stQBPMusicBuffer> tMusixBegin     ;//Buffer de features musical(Features de Notas)
    vector<stQBPMusicBuffer> tMusixMid       ;//Buffer de features musical(Features de Notas)
    vector<stQBPMusicBuffer> tMusixEnd       ;//Buffer de features musical(Features de Notas)

    //Percorre cada buffer strip
    for (int i = 0; i < pQBPSongBufferStrip.size(); i++)
    {
        //Contador de notas por strip
        tCount = 0;
        tStrip.clear();
        for(int j=0;j< (int)pQBPSongBufferStrip[i].size() ;j++)
        {
           tCount++;
           //Caso tenha atingido o num maximo de notas por strip/final do buffer
           if (tCount < pQBPNotesByStrip || i == pQBPSongBufferStrip[i].size()-1)
           {
               if(i==0)
               {
               tMusixNote.bQBP_IsBemol          = pQBPMusixBegin[j].bQBP_IsBemol;
               tMusixNote.bQBP_IsSharp          = pQBPMusixBegin[j].bQBP_IsSharp;
               tMusixNote.dQBP_Duration         = pQBPMusixBegin[j].dQBP_Duration;
               tMusixNote.dQBP_Frequency        = pQBPMusixBegin[j].dQBP_Frequency;
               tMusixNote.iQBP_MidiShortMessage = pQBPMusixBegin[j].iQBP_MidiShortMessage;
               tMusixNote.iQBP_Octave           = pQBPMusixBegin[j].iQBP_Octave;
               tMusixNote.iQBP_Pitch            = pQBPMusixBegin[j].iQBP_Pitch;
               tMusixNote.iQBP_Contour          = pQBPMusixBegin[j].iQBP_Contour;
               tMusixNote.sQBP_Note             = pQBPMusixBegin[j].sQBP_Note;

               tMusixBegin.push_back(tMusixNote);
               }

               if(i==1)
               {
               tMusixNote.bQBP_IsBemol          = pQBPMusixMid[j].bQBP_IsBemol;
               tMusixNote.bQBP_IsSharp          = pQBPMusixMid[j].bQBP_IsSharp;
               tMusixNote.dQBP_Duration         = pQBPMusixMid[j].dQBP_Duration;
               tMusixNote.dQBP_Frequency        = pQBPMusixMid[j].dQBP_Frequency;
               tMusixNote.iQBP_MidiShortMessage = pQBPMusixMid[j].iQBP_MidiShortMessage;
               tMusixNote.iQBP_Octave           = pQBPMusixMid[j].iQBP_Octave;
               tMusixNote.iQBP_Pitch            = pQBPMusixMid[j].iQBP_Pitch;
               tMusixNote.iQBP_Contour          = pQBPMusixMid[j].iQBP_Contour;
               tMusixNote.sQBP_Note             = pQBPMusixMid[j].sQBP_Note;

               tMusixMid.push_back(tMusixNote);
               }

               if(i==2)
               {
               tMusixNote.bQBP_IsBemol          = pQBPMusixEnd[j].bQBP_IsBemol;
               tMusixNote.bQBP_IsSharp          = pQBPMusixEnd[j].bQBP_IsSharp;
               tMusixNote.dQBP_Duration         = pQBPMusixEnd[j].dQBP_Duration;
               tMusixNote.dQBP_Frequency        = pQBPMusixEnd[j].dQBP_Frequency;
               tMusixNote.iQBP_MidiShortMessage = pQBPMusixEnd[j].iQBP_MidiShortMessage;
               tMusixNote.iQBP_Octave           = pQBPMusixEnd[j].iQBP_Octave;
               tMusixNote.iQBP_Pitch            = pQBPMusixEnd[j].iQBP_Pitch;
               tMusixNote.iQBP_Contour          = pQBPMusixEnd[j].iQBP_Contour;
               tMusixNote.sQBP_Note             = pQBPMusixEnd[j].sQBP_Note;

               tMusixEnd.push_back(tMusixNote);
               }

               tStrip.push_back(pQBPSongBufferStrip[i][j]);
           }
        }

        pQBPSongBufferStrip[i].clear();
        pQBPSongBufferStrip[i]=tStrip;
    }

    pQBPMusixBegin.clear();
    pQBPMusixMid  .clear();
    pQBPMusixEnd  .clear();

    pQBPMusixBegin = tMusixBegin;
    pQBPMusixMid   = tMusixMid;
    pQBPMusixEnd   = tMusixEnd;

    return true;
}

/*
bool CQBPSong::RemoveBemol()
{
    int npos = (int)pQBPSongBuffer.find("b");
    while (npos != -1)
    {
        //apaga o b encontrado
        pQBPSongBuffer.erase(npos,1);
        //procura pelo proximo b
        npos = (int)pQBPSongBuffer.find("b");
    }
    return true;
}
*/

bool CQBPSong::ClearSong()
{
    pQBPNotes          .clear();//Dados MIDI
    pQBPSongName       .clear();//Nome da musica(filename)
    pQBPSongBuffer     .clear();//Buffer de notas diatonicas da musica completa
    pQBPSongBufferStrip.clear();//vetor de buffers menores da musica
    //pQBPSongBPM              =0;//Beats per minutes da musica
    return true;
}

int CQBPSong::Distance(CQBPSong pQBPSong)
{
    double tDistance=0;
    vector<double> tDistances;

    //Se o numero de features é diferente retornamos valor grande
    if (pQBPCustomFeatures.size() != pQBPSong.pQBPCustomFeatures.size())return 99999;

    //preenche vetor de distancias
    //deixamos com 7 devido a inclusão do histograma (Separar Attitude do histograma)
    for (int i = 0; i < /*(int)pQBPCustomFeatures.size()*/8; i++)
    {
        tDistances.push_back(         pQBPCustomFeatures[i].GetFeatureValue() -
                             pQBPSong.pQBPCustomFeatures[i].GetFeatureValue());
    }

    //Calcula a Manhattan Distance entre as features.
    for (uint j = 0; j < tDistances.size(); j++)
    {
        tDistance += tDistances[j];
    }

    tDistances.clear();
    //Sempre colocar o reserve zero para economizar memoria(O clear não limpa a reserva de espaço)
    tDistances.shrink_to_fit();

    return (int)tDistance;
}

void CQBPSong::AddNote(stQBPMusicBuffer pQBPNote,int pQBPRecurrency)
{
    vector<stQBPStringBuffer> tSongBuffer ;//Buffer de notas diatonicas da musica completa
    vector<stQBPMusicBuffer>  tMusixBuffer;//Buffer de features musical(Features de Notas)
    int                       tCount=0    ;


    //Adiciona no Buffer Texto
    for(int i=0;i<pQBPSongBuffer.size();i++)
    {
        tCount++;
        if(tCount==pQBPRecurrency)
        {
           //inclui a nota e inclui a do indice
           stQBPStringBuffer         tStringNote ;
           tStringNote.sQBP_Note = pQBPNote.sQBP_Note;
           tStringNote.iQBP_Octave = pQBPNote.iQBP_Octave;
           tSongBuffer.push_back(tStringNote);
           tSongBuffer.push_back(pQBPSongBuffer[i]);
           tCount=0;
        }
        else
        {
           tSongBuffer.push_back(pQBPSongBuffer[i]);
        }
    }

    //Substitui o novo buffer
    pQBPSongBuffer.clear();
    pQBPSongBuffer.shrink_to_fit();
    pQBPSongBuffer = tSongBuffer;

    //Zera o contador de recorrencia
    tCount=0;

    //Adiciona no Buffer Mussix
    for(int i=0;i<pQBPMusixBuffer.size();i++)
    {
        tCount++;
        if(tCount==pQBPRecurrency)
        {
           //inclui a nota e inclui a do indice
           tMusixBuffer.push_back(pQBPNote);
           tMusixBuffer.push_back(pQBPMusixBuffer[i]);
           tCount=0;
        }
        else
        {
           tMusixBuffer.push_back(pQBPMusixBuffer[i]);
        }
    }

    //Substitui o buffer mussix
    pQBPMusixBuffer = tMusixBuffer;

}

void CQBPSong::RemNote(stQBPMusicBuffer pQBPNote,int pQBPPosition)
{
    vector<stQBPStringBuffer> tSongBuffer ;//Buffer de notas diatonicas da musica completa
    vector<stQBPMusicBuffer>  tMusixBuffer;//Buffer de features musical(Features de Notas)

    //Adiciona no Buffer Texto
    for(int i=0;i<pQBPSongBuffer.size();i++)
    {
        if(i==pQBPPosition)
        {
           continue;
        }
        else
        {
           tSongBuffer.push_back(pQBPSongBuffer[i]);
        }
    }

    //Substitui o novo buffer
    pQBPSongBuffer = tSongBuffer;

    //Adiciona no Buffer Mussix
    for(int i=0;i<pQBPMusixBuffer.size();i++)
    {
        if(i==pQBPPosition)
        {
           continue;
        }
        else
        {
           tMusixBuffer.push_back(pQBPMusixBuffer[i]);
        }
    }

    //Substitui o buffer mussix
    pQBPMusixBuffer = tMusixBuffer;
}

void CQBPSong::RemFromPos(int pQBPPosition)
{
    string                   tSongBuffer ;//Buffer de notas diatonicas da musica completa
    vector<stQBPMusicBuffer> tMusixBuffer;//Buffer de features musical(Features de Notas)

    if(pQBPPosition < (int)pQBPSongBuffer .size() &&
       pQBPPosition < (int)pQBPMusixBuffer.size() )
    {
       pQBPSongBuffer.erase(pQBPSongBuffer.begin()+pQBPPosition,pQBPSongBuffer.end());
       pQBPSongBuffer.shrink_to_fit();

       pQBPMusixBuffer.erase(pQBPMusixBuffer.begin()+pQBPPosition,pQBPMusixBuffer.end());
       pQBPMusixBuffer.shrink_to_fit();
    }

}

void CQBPSong::RepNote(stQBPMusicBuffer pQBPNote,int pQBPPosition)
{
    vector<stQBPStringBuffer> tSongBuffer ;//Buffer de notas diatonicas da musica completa
    vector<stQBPMusicBuffer>  tMusixBuffer;//Buffer de features musical(Features de Notas)

    //Adiciona no Buffer Texto
    for(int i=0;i<pQBPSongBuffer.size();i++)
    {
        if(i==pQBPPosition)
        {
           //inclui a nota e inclui a do indice
           stQBPStringBuffer         tStringNote ;
           tStringNote.sQBP_Note = pQBPNote.sQBP_Note;
           tStringNote.iQBP_Octave = pQBPNote.iQBP_Octave;
           tSongBuffer.push_back(tStringNote);
           continue;
        }
        else
        {
            tSongBuffer.push_back(pQBPSongBuffer[i]);
        }
    }

    //Substitui o novo buffer
    pQBPSongBuffer = tSongBuffer;

    //Adiciona no Buffer Mussix
    for(int i=0;i<pQBPMusixBuffer.size();i++)
    {
        if(i==pQBPPosition)
        {
           tMusixBuffer.push_back(pQBPNote);
           continue;
        }
        else
        {
           tMusixBuffer.push_back(pQBPMusixBuffer[i]);
        }
    }

    //Substitui o buffer mussix
    pQBPMusixBuffer = tMusixBuffer;
}

