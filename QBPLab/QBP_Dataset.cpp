#include "QBP_Dataset.h"

float   CQBPDataset::fQBPDatasetCountTP,
        CQBPDataset::fQBPDatasetCountFP,
        CQBPDataset::fQBPDatasetCountTN,
        CQBPDataset::fQBPDatasetCountFN;
float   CQBPDataset::fQBPDatasetPrecision,
        CQBPDataset::fQBPDatasetRecall,
        CQBPDataset::fQBPDatasetFmeasure,
        CQBPDataset::fQBPDatasetAccuracy;

//vector<CQBPGenre> CQBPDataset::pQBPGenreList  ;//Lista de Musicas do dataset(Subdivididos por genero)
//vector<CQBPSong>  CQBPDataset::pQBPTestList   ;//Lista de Musicas do genero teste
//vector<CQBPSong>  CQBPDataset::pQBPValiList   ;//Lista de Musicas do genero validação
//vector<CQBPSong>  CQBPDataset::pQBPRandomList ;//Lista de Musicas do genero validação
//vector<CQBPSong>  CQBPDataset::pQBPMusicPlayer;//Lista de Musicas do player de musica

bool invalidChar(char c)
{
    return !(c >= 0 && c <128);
}

bool isSpaceChar(char c)
{
    return (c == 32);
}

bool isPunctChar(char c)
{
    return (c >= 33 && c <= 47);
}

CQBPDataset::CQBPDataset()
{
    //pQBPMaxFeatures = 156;
    pQBPMaxFeatures = 9;
    bQBPSetLock     = false;
    bQBPStretchStrip= false;
    iQBPStretchValue= 31;
}


CQBPDataset::~CQBPDataset()
{
}

bool CQBPDataset::LoadChords(string pQBPath)
{
    string    tAbsoluteFileName;
    string    tSongname;

    //Abre arquivo para leitura
    std::filebuf fb;
    fb.open(pQBPath, std::ios::in);

    //Grava dados na stream de arquivo
    std::istream is(&fb);
    int     tChordCount = 0;

    while(!is.eof())
    {
        int     tChordID;
        int     tChordVoice01;
        int     tChordVoice02;
        int     tChordVoice03;
        int     tChordVoice04;
        int     tChordVoice05;
        int     tChordVoice06;

        CQBPChord tChord;

        is >> tChordID
           >> tChordVoice01
           >> tChordVoice02
           >> tChordVoice03
           >> tChordVoice04
           >> tChordVoice05
           >> tChordVoice06;

        tChord.SetName(QString("Chord %1").arg(tChordID));
        //Para cada voz do acorde...
        for(uint i=0;i<6;i++)
        {
            DiatonicNote tDial;
            stQBPMusicBuffer tBuffer;

            switch(i)
            {
            case 0:{tDial = pQBPKeyboard.GetNoteByPitch(tChordVoice01);}break;
            case 1:{tDial = pQBPKeyboard.GetNoteByPitch(tChordVoice02);}break;
            case 2:{tDial = pQBPKeyboard.GetNoteByPitch(tChordVoice03);}break;
            case 3:{tDial = pQBPKeyboard.GetNoteByPitch(tChordVoice04);}break;
            case 4:{tDial = pQBPKeyboard.GetNoteByPitch(tChordVoice05);}break;
            case 5:{tDial = pQBPKeyboard.GetNoteByPitch(tChordVoice06);}break;
            }

            tBuffer.sQBP_Note             = tDial.NoteName        ;
            tBuffer.bQBP_IsBemol          = tDial.bIsbemol        ;
            tBuffer.bQBP_IsSharp          = tDial.bIssharp        ;
            tBuffer.iQBP_Octave           = tDial.Octave          ;//Octave on the Keyboard
            tBuffer.iQBP_Pitch            = tDial.NotePith        ;//Numeric Pitch Note
            tBuffer.iQBP_Contour          = 0                     ;//Melodic Contour of the Note(Difference in semitones from previous one)
            tBuffer.dQBP_Duration         = 0.5                   ;//Duration of the Note
            tBuffer.dQBP_Frequency        = tDial.Frequency       ;//Frequency of the Note
            tBuffer.iQBP_MidiShortMessage = tDial.MidiShortMessage;//Midi Short Message For Play

            //adiciona nota ao acorde
            tChord.AddNote(tBuffer);
        }

        //adiciona acorde na lista
        pQBPChords.push_back(tChord);
        tChordCount++;
    }

    //Fecha o arquivo
    fb.close();

}
bool CQBPDataset::LoadDataset(string pQBPath,int pQBPLoadType, int pQBPTargetList)
{
    CQBPSong  tSong;
    CQBPGenre tGenre;
    string    tAbsoluteFileName;
    string    tSongname;
    int       tActualGenre = 0;

    //Se estiver processando uma busca retorna sem fazer nada.
    if(GetLock())return false;

    //Se chegou aqui é porque o caminho esta livre para novas consultas, portanto travar a engine para outras consultas
    //isto é necessário pois ainda não estamos controlando as buscas através de eventQueue e devido a chamada estar
    //sendo feita em uma Thread vinda da interface para não travar o aplicativo.
    //Isto será um controle temporario de processamento!
    SetLock(true);

    switch (pQBPLoadType)
    {
    case QBP_LOAD_TYPE_BUILD:
    {
        //Limpa Lista de gêneros
        if(pQBPGenreList.size()>0)
        {
            pQBPGenreList.clear();
            //Sempre colocar o reserve zero para economizar memoria(O clear não limpa a reserva de espaço)
            pQBPGenreList.shrink_to_fit();
        }

        QDirIterator it(pQBPath.c_str(), QDir::NoFilter, QDirIterator::Subdirectories);

        while (it.hasNext())
        {

            tAbsoluteFileName = it.next().toStdString();

            tSongname = it.fileName().toStdString();
            std::size_t found = tAbsoluteFileName.find(".mid");
            if (found != std::string::npos)
            {
                pArqMidi.read(tAbsoluteFileName);

                //Atribui o nome da musica
                tSong.pQBPSongName = tSongname;

                //Atribui o gênero da musica
                tSong.pQBPSongCategory = tActualGenre;

                //Carrega dados da musica(eventos)
                LoadSong(tSong);

                switch (pQBPTargetList)
                {
                case QBP_LOAD_TARGET_DATASET:{pQBPGenreList[tActualGenre].pQBPSongList.push_back(tSong);}break;//Adiciona a musica na lista
                case QBP_LOAD_TARGET_TESTSET:{pQBPTestList.push_back(tSong);}break;//Adiciona a musica na lista teste
                case QBP_LOAD_TARGET_VALISET:{pQBPValiList.push_back(tSong);}break;//Adiciona a musica na lista validacao
                case QBP_LOAD_TARGET_RANDSET:{pQBPRandomList.push_back(tSong);}break;//Adiciona a musica na lista randomica
                case QBP_LOAD_TARGET_MUSPLAY:{pQBPMusicPlayer.push_back(tSong); }break;//Adiciona a musica na lista validacao
                }
                //CQBPLogQueue::Push(QString("Musica ") + QString(tSong.pQBPSongName.c_str()) + QString(" Importada com sucesso! \n"));
            }
            else
            {
                std::size_t found = tAbsoluteFileName.find(".txt");
                if (found != std::string::npos)continue;

                //Localiza e apaga raiz de folder para pegar o nome do gênero
                int nfold;
                nfold = (int)tAbsoluteFileName.find("/");

                tAbsoluteFileName.erase(0, tAbsoluteFileName.substr(0, nfold + 1).size());

                found = tAbsoluteFileName.find(".");
                if (found != std::string::npos)continue;

                found = tAbsoluteFileName.find("..");
                if (found != std::string::npos)continue;

                CQBPLogQueue::Push(QString("Importando folder: "));
                CQBPLogQueue::Push(QString(tAbsoluteFileName.c_str()));
                CQBPLogQueue::Push(QString(" \n"));

                //Adiciona o nome do folder como um gênero
                pQBPGenreList.push_back(CQBPGenre(tAbsoluteFileName));

                tActualGenre = (int)pQBPGenreList.size() - 1;

            }
        }

        CQBPLogQueue::Push(QString("Construindo Music Buffers... \n"));
        BuildMusicBuffers(QBP_LOAD_TARGET_DATASET);
        CQBPLogQueue::Push(QString("Construindo Music Stripped Buffers... \n"));
        BuildStrippedDts(QBP_LOAD_TARGET_DATASET);
        CQBPLogQueue::Push(QString("Construindo Music Feature Buffers(Custom Buffers)... \n"));
        BuildFeaturesDts(QBP_LOAD_TARGET_DATASET);
        CQBPLogQueue::Push(QString("Calculando estatisticas da Base... \n"));
        BuildStatistics();


        CQBPLogQueue::Push(QString("Gravando arquivo .Dts Full... \n"));
        WriteDts("dataset/Dataset_Full.txt", QBP_STRIP_TOT);

        CQBPLogQueue::Push(QString("Gravando arquivo .Dts Begin... \n"));
        WriteDts("dataset/Dataset_Begin.txt", QBP_STRIP_BEG);

        CQBPLogQueue::Push(QString("Gravando arquivo .Dts Middle... \n"));
        WriteDts("dataset/Dataset_Midle.txt", QBP_STRIP_MID);

        CQBPLogQueue::Push(QString("Gravando arquivo .Dts End... \n"));
        WriteDts("dataset/Dataset_End.txt", QBP_STRIP_END);

        CQBPLogQueue::Push(QString("Gravando arquivo .train SVM  \n"));
        WriteSvm("svm/qbpSVM.train", QBP_SVM_TRAIN_DATASET);

        CQBPLogQueue::Push(QString("Gravando arquivo .train SVM Normalizado  \n"));
        WriteSvmNorm("svm/qbpSVMNorm.train", QBP_SVM_TRAIN_DATASET);

        CQBPLogQueue::Push(QString("Gravando arquivo .gen QBP  \n"));
        WriteGen("dataset/Genres.txt");
    }break;
    case QBP_LOAD_TYPE_FULL:
    {
        //Caso Não tenha sido carregado a lista de generos
        if (pQBPGenreList.size() <= 0)return false;

        //Abre arquivo para leitura
        std::filebuf fb;
        fb.open(pQBPath, std::ios::in);

        //Grava dados na stream de arquivo
        std::istream is(&fb);
        int     tSongCount = 0;

        //Carrega o nome e buffer para pesquisa
        while(!is.eof())
        {
            string  tSongName    ,
                    tSongBuffer  ;
            int     tSongCategory;
            int     tFeaturesSize;
            int     tFeatureId   ;
            double  tFeatureValue;
            string  tFeatureName;
            int     tSongSize;

            CQBPSong tSong;

            is >> tSongName
               >> tSongCategory
               >> tFeaturesSize;

            if (tSongName != "")
            {
                tSong.pQBPSongName        = tSongName;
                tSong.pQBPSongCategory    = tSongCategory;

                //Carrega as features
                for (int i = 0; i < tFeaturesSize; i++)
                {
                    is >> tFeatureId >> tFeatureName >> tFeatureValue;
                    tSong.pQBPCustomFeatures.push_back(CQBPFeature(tFeatureId, tFeatureName, tFeatureValue));
                }

                //Carrega as features Normalizadas
                for (int i = 0; i < tFeaturesSize; i++)
                {
                    is >> tFeatureId >> tFeatureName >> tFeatureValue;
                    tSong.pQBPNormalFeatures.push_back(CQBPFeature(tFeatureId, tFeatureName, tFeatureValue));
                }
                //le a quantidade de notas do buffer
                is >> tSongSize;

                for (int l = 0; l < tSongSize; l++)
                {
                    stQBPMusicBuffer tMusixNote;

                    is >> tMusixNote.bQBP_IsBemol
                       >> tMusixNote.bQBP_IsSharp
                       >> tMusixNote.dQBP_Duration
                       >> tMusixNote.dQBP_Frequency
                       >> tMusixNote.iQBP_MidiShortMessage
                       >> tMusixNote.iQBP_Octave
                       >> tMusixNote.iQBP_Pitch
                       >> tMusixNote.iQBP_Contour
                       >> tMusixNote.sQBP_Note ;

                    tSong.pQBPMusixBuffer.push_back(tMusixNote);
                }

                //Para podrmos simular o problema de transposição na string passei a usar uma estrutura
                for (int l = 0; l < tSongSize; l++)
                {
                    stQBPStringBuffer tStringNote;

                    is >> tStringNote.sQBP_Note
                       >> tStringNote.iQBP_Octave;

                    tSong.pQBPSongBuffer.push_back(tStringNote);
                }

                //Já marcamos como featured pois o build principal sempre gera features.
                tSong.pQBPFeatured = true;

                switch (pQBPTargetList)
                {
                case QBP_LOAD_TARGET_DATASET: {pQBPGenreList[tSongCategory].pQBPSongList.push_back(tSong); }break;//Adiciona a musica na lista
                case QBP_LOAD_TARGET_TESTSET: {pQBPTestList.push_back(tSong); }break;//Adiciona a musica na lista teste
                case QBP_LOAD_TARGET_VALISET: {pQBPValiList.push_back(tSong); }break;//Adiciona a musica na lista validacao
                case QBP_LOAD_TARGET_RANDSET: {pQBPRandomList.push_back(tSong); }break;//Adiciona a musica na lista randomica
                case QBP_LOAD_TARGET_MUSPLAY: {pQBPMusicPlayer.push_back(tSong); }break;//Adiciona a musica na lista validacao
                }

                //Atualiza o numero maximo de features
                if((int)tSong.pQBPCustomFeatures.size()>pQBPMaxFeatures)pQBPMaxFeatures = (int)tSong.pQBPCustomFeatures.size();

            }
            tSongCount++;
            pQBPQtdSongs = tSongCount;
            //CQBPLogQueue::Push(QString("Musica %1 Carregada!  \n").arg(tSongCount));
        }

        //Fecha o arquivo
        fb.close();
    }break;
    case QBP_LOAD_TYPE_GENRE:
    {
        //Checa se a base esta com algum genero e limpa...
        if (pQBPGenreList.size() > 0)
        {
            pQBPGenreList.clear();
            //Sempre colocar o reserve zero para economizar memoria(O clear não limpa a reserva de espaço)
            pQBPGenreList.shrink_to_fit();
        }

        //Abre arquivo para leitura
        std::filebuf fb;
        fb.open(pQBPath, std::ios::in);

        //Grava dados na stream de arquivo
        std::istream is(&fb);

        //Carrega o nome e buffer para pesquisa
        while (!is.eof())
        {
            string    tGenreName;
            CQBPGenre tGenre;

            is >> tGenreName ;

            if (tGenreName != "")
            {
                tGenre.pQBPGenreName = tGenreName;
                pQBPGenreList.push_back(tGenre);
            }
        }

        //Fecha o arquivo
        fb.close();
    }break;

    case QBP_LOAD_TYPE_MIDI:
    {
        QDirIterator it(pQBPath.c_str(), QDirIterator::Subdirectories);

        while (it.hasNext())
        {

            tAbsoluteFileName = it.next().toStdString();

            tSongname = it.fileName().toStdString();

            std::size_t found = tAbsoluteFileName.find(".mid");
            if (found != std::string::npos)
            {
                pArqMidi.read(tAbsoluteFileName);

                //Atribui o nome da musica
                //remove o .mid , espaços e pontuação do nome
                int npos = (int)tSongname.find(".mid");
                if (npos != -1)
                {
                    tSongname.erase(npos, 4);
                }
                tSongname.erase(remove_if(tSongname.begin(), tSongname.end(), invalidChar), tSongname.end());
                tSongname.erase(remove_if(tSongname.begin(), tSongname.end(), isSpaceChar), tSongname.end());
                tSongname.erase(remove_if(tSongname.begin(), tSongname.end(), isPunctChar), tSongname.end());

                tSong.pQBPSongName = tSongname;

                //Atribui o gênero da musica
                tSong.pQBPSongCategory = tActualGenre;

                //Carrega dados da musica(eventos)
                LoadSong(tSong);

                //Adiciona musica na lista
                switch (pQBPTargetList)
                {
                case QBP_LOAD_TARGET_DATASET: {pQBPGenreList[tActualGenre].pQBPSongList.push_back(tSong); }break;//Adiciona a musica na lista
                case QBP_LOAD_TARGET_TESTSET: {pQBPTestList.push_back(tSong); }break;//Adiciona a musica na lista teste
                case QBP_LOAD_TARGET_VALISET: {pQBPValiList.push_back(tSong); }break;//Adiciona a musica na lista validacao
                case QBP_LOAD_TARGET_RANDSET: {pQBPRandomList.push_back(tSong); }break;//Adiciona a musica na lista randomica
                case QBP_LOAD_TARGET_MUSPLAY: {pQBPMusicPlayer.push_back(tSong); }break;//Adiciona a musica na lista validacao
                }

            }
            else
            {
                std::size_t found = tAbsoluteFileName.find(".txt");
                if (found != std::string::npos)continue;

                //Localiza e apaga raiz de folder para pegar o nome do gênero
                int nfold;
                nfold = (int)tAbsoluteFileName.find("\\");

                tAbsoluteFileName.erase(0, tAbsoluteFileName.substr(0, nfold + 1).size());

                //pega o indice atual do genero
                tActualGenre = (int)pQBPGenreList.size() - 1;

            }
        }
    }break;
    }

    //libera a engine para novas consultas
    SetLock(false);

    return true;
}

bool CQBPDataset::LoadSong(CQBPSong &pQBPSong)
{
    CQBPNote mtemp;
    int      track = 0;
    int      biggest = 0;
    int      numEvents = 0;
    int      maxevents = 0;
    int      command;
    int      pitch;
    int      velocity;


    //converte para tempo absoluto o arquivo
    pArqMidi.absoluteTicks();

    //Apenas alerta se encontrou arquivo multitrack
    if (pArqMidi.getNumTracks() > 1)
    {
       //pega o indice que contem o maior indice de eventos
       for (int i = 0; i < pArqMidi.getNumTracks(); i++)
       {
           if (maxevents < pArqMidi.getNumEvents(i))
           {
               maxevents = pArqMidi.getNumEvents(i);
               biggest = i;
           }
       }
    }

    //Extrai o numero de eventos do track(Ira se converter em notas)
    if(biggest==0)numEvents = pArqMidi.getNumEvents(0);
    else
    {
        numEvents = pArqMidi.getNumEvents(biggest);
    }

    //informa o indice do maior track
    track = biggest;

    //Vetor auxiliar para mapear qual nota foi pressionada(cada valor representa a tecla pressionada)
    vector<int> state(128);

    int i;
    for (i = 0; i<128; i++) {
        state[i] = -1;
    }


    pQBPSong.pQBPNotes.reserve(numEvents);
    pQBPSong.pQBPNotes.clear();


    for (i = 0; i<numEvents; i++)
    {
        command = pArqMidi[track][i][0] & 0xf0;

        //Comando de tecla pressionada
        if (command == 0x90)
        {
            pitch    = pArqMidi[track][i][1];
            velocity = pArqMidi[track][i][2];

            //Se a velocidade é 0 a tecla nao esta pressionada
            if (velocity == 0)
            {
                // note off
                goto noteoff;
            }
            else
            {
                // tecla pressionada
                state[pitch] = pArqMidi[track][i].tick;
            }
        }
        //Tecla nao pressionada
        else if (command == 0x80)
        {
            // note off
            pitch = pArqMidi[track][i][1];

        noteoff:
            if (state[pitch] == -1)
            {
                continue;
            }

            mtemp.tick     = state[pitch];
            mtemp.duration = pArqMidi[track][i].tick - state[pitch];
            mtemp.pitch    = pitch;
            mtemp.command  = command;

            pQBPSong.pQBPNotes.push_back(mtemp);

            state[pitch] = -1;
        }
    }
    return true;
}

bool CQBPDataset::BuildStatistics()
{
    int tNumMaxMusicas = 0;
    int tNumMaxNotas   = 0;
    int tNumMaxStrips  = 0;
    int tMusMaxNotas   = 0;
    int tIndexMusMax   = 0;
    int tIndexGenMax   = 0;

    string tMusName;

    CheckDataHealth();
    //Calcula estatisticas do Dataset carregado
    for (int i = 0; i < pQBPGenreList.size(); i++)
    {
        for (int j = 0; j < pQBPGenreList[i].pQBPSongList.size(); j++)
        {
            tNumMaxNotas  += (int)pQBPGenreList[i].pQBPSongList[j].pQBPSongBuffer.size();
            tNumMaxStrips += (int)pQBPGenreList[i].pQBPSongList[j].pQBPSongBufferStrip.size();

            tNumMaxMusicas++;

            //Calcula numero de notas da maior musica
            if (tMusMaxNotas < pQBPGenreList[i].pQBPSongList[j].pQBPSongBuffer.size())
            {
                tMusMaxNotas = (int)pQBPGenreList[i].pQBPSongList[j].pQBPSongBuffer.size();
                tMusName     = pQBPGenreList[i].pQBPSongList[j].pQBPSongName;
                tIndexMusMax = j;
                tIndexGenMax = i;
            }
        }
    }

    pQBPQtdSongs           = tNumMaxMusicas;
    pQBPAvrgNotesBySong    = tNumMaxNotas / tNumMaxMusicas;
    pQBPBiggerSongName     = tMusName;
    pQBPBiggerSongQtdNotes = tMusMaxNotas;
    pQBPQtdStrips          = tNumMaxStrips;

    CQBPLogQueue::Push(QString("============================================================\n"));
    CQBPLogQueue::Push(QString("=                ESTATISTICAS DO DATASET                   =\n"));
    CQBPLogQueue::Push(QString("============================================================\n"));
    CQBPLogQueue::Push(QString("Numero de Musicas: %1 \n").arg(pQBPQtdSongs));
    CQBPLogQueue::Push(QString("Media de Notas por Musica: %1 \n").arg(pQBPAvrgNotesBySong));
    CQBPLogQueue::Push(QString("Maior Nome de Musica: ") + QString(pQBPBiggerSongName.c_str()) + QString(" \n"));
    CQBPLogQueue::Push(QString("Maior Numero de Notas: %1 \n").arg(pQBPBiggerSongQtdNotes));

    return true;
}

bool CQBPDataset::CheckDataHealth()
{
    int tNumGlobalFeatures=0;
    int tNumFeatures = 0;
    bool tFistTime = true;

    CQBPLogQueue::Push(QString("Checando Consistencia da Base de Features:   \n"));
    //Calcula estatisticas do Dataset carregado
    for (int i = 0; i < pQBPGenreList.size(); i++)
    {
        for (int j = 0; j < pQBPGenreList[i].pQBPSongList.size(); j++)
        {
            if (tFistTime)
            {
                tNumGlobalFeatures = (int)pQBPGenreList[i].pQBPSongList[j].pQBPCustomFeatures.size();
                CQBPLogQueue::Push(QString("Numero Fixo de Features: %1 \n").arg(tNumGlobalFeatures));
                tFistTime = false;
            }
            else
            {
                tNumFeatures = (int)pQBPGenreList[i].pQBPSongList[j].pQBPCustomFeatures.size();
                if (tNumFeatures != tNumGlobalFeatures)return false;
            }
        }
    }

    CQBPLogQueue::Push(QString("Consistencia Ok!!!: %1 \n").arg(tNumFeatures));
    pQBPMaxFeatures = tNumFeatures;
    return true;
}

bool CQBPDataset::Print()
{
    CQBPLogQueue::Push(QString("Numero de musicas carregadas:  %1 \n").arg(pQBPQtdSongs));
    CQBPLogQueue::Push(QString("Numero de notas medio por musica:  %1 \n").arg(pQBPAvrgNotesBySong));
    CQBPLogQueue::Push(QString("Musica com Mais Notas: "));
    CQBPLogQueue::Push(QString(pQBPBiggerSongName.c_str()));
    CQBPLogQueue::Push(QString(" NumNotas: %1 \n").arg(pQBPBiggerSongQtdNotes));
    CQBPLogQueue::Push(QString("Numero de strips gerados: %1 \n").arg(pQBPQtdStrips));
    return true;
}

bool CQBPDataset::WriteDts(string    pQBPath, int pQBPWrtOption)
{
    std::filebuf fb;
    fb.open(pQBPath, std::ios::out);

    //Grava dados na stream de arquivo
    std::ostream os(&fb);

    //Formata e grava dados para o arquivo Dts
    for (int i = 0; i < pQBPGenreList.size(); i++)
    {
        for (int j = 0; j < pQBPGenreList[i].pQBPSongList.size(); j++)
        {
            //Carrega o nome e genero da musica vindo da base de arquivos MIDI
            string tName        = pQBPGenreList[i].pQBPSongList[j].pQBPSongName;
            int    tCategory    = pQBPGenreList[i].pQBPSongList[j].pQBPSongCategory;
            //int    tNumFeatures = (int)pQBPGenreList[i].pQBPSongList[j].pQBPJSymboFeatures.size();
            int    tNumFeatures = (int)pQBPGenreList[i].pQBPSongList[j].pQBPCustomFeatures.size();

            //Caso ja esteja estripada, não deve-se adequar os nomes mais...
            //remove o .mid , espaços e pontuação do nome
            int npos = (int)tName.find(".mid");
            if (npos != -1)
            {
                tName.erase(npos, 4);
            }
            tName.erase(remove_if(tName.begin(), tName.end(), invalidChar), tName.end());
            tName.erase(remove_if(tName.begin(), tName.end(), isSpaceChar), tName.end());
            tName.erase(remove_if(tName.begin(), tName.end(), isPunctChar), tName.end());

            switch (pQBPWrtOption)
            {
            case QBP_STRIP_BEG:
            {
                if (pQBPGenreList[i].pQBPSongList[j].pQBPSongBufferStrip.size() >= 1)
                {
                    os << tName << " " << tCategory << " " << tNumFeatures << " ";
                    //Grava Features
                    for (int k = 0; k < tNumFeatures; k++)
                    {
                        double pQBPFeatureTypeId;
                        string pQBPFeatureName;
                        double pQBPFeatureValue;
                        pQBPGenreList[i].pQBPSongList[j].pQBPCustomFeatures[k].GetFeatureData(pQBPFeatureTypeId,
                                                                                              pQBPFeatureName,
                                                                                              pQBPFeatureValue);

                        //remove espaços e pontuação do nome da feature
                        pQBPFeatureName.erase(remove_if(pQBPFeatureName.begin(), pQBPFeatureName.end(), invalidChar), pQBPFeatureName.end());
                        pQBPFeatureName.erase(remove_if(pQBPFeatureName.begin(), pQBPFeatureName.end(), isSpaceChar), pQBPFeatureName.end());
                        pQBPFeatureName.erase(remove_if(pQBPFeatureName.begin(), pQBPFeatureName.end(), isPunctChar), pQBPFeatureName.end());

                        os  << pQBPFeatureTypeId << " "
                            << pQBPFeatureName   << " "
                            << pQBPFeatureValue  << " ";
                    }

                    //Grava Features Normalizadas
                    for (int k = 0; k < tNumFeatures; k++)
                    {
                        double pQBPFeatureTypeId;
                        string pQBPFeatureName;
                        double pQBPFeatureValue;
                        pQBPGenreList[i].pQBPSongList[j].pQBPNormalFeatures[k].GetFeatureData(pQBPFeatureTypeId,
                                                                                              pQBPFeatureName,
                                                                                              pQBPFeatureValue);

                        //remove espaços e pontuação do nome da feature
                        pQBPFeatureName.erase(remove_if(pQBPFeatureName.begin(), pQBPFeatureName.end(), invalidChar), pQBPFeatureName.end());
                        pQBPFeatureName.erase(remove_if(pQBPFeatureName.begin(), pQBPFeatureName.end(), isSpaceChar), pQBPFeatureName.end());
                        pQBPFeatureName.erase(remove_if(pQBPFeatureName.begin(), pQBPFeatureName.end(), isPunctChar), pQBPFeatureName.end());

                        os  << pQBPFeatureTypeId << " "
                            << pQBPFeatureName   << " "
                            << pQBPFeatureValue  << " ";
                    }
                    //Grava a quantidade de notas do buffer
                    int tSongSize = (int)pQBPGenreList[i].pQBPSongList[j].pQBPMusixBegin.size();
                    os << tSongSize << " ";

                    for (int l = 0; l < tSongSize; l++)
                    {
                        stQBPMusicBuffer tMusixNote;

                        tMusixNote.bQBP_IsBemol          = pQBPGenreList[i].pQBPSongList[j].pQBPMusixBegin[l].bQBP_IsBemol;
                        tMusixNote.bQBP_IsSharp          = pQBPGenreList[i].pQBPSongList[j].pQBPMusixBegin[l].bQBP_IsSharp;
                        tMusixNote.dQBP_Duration         = pQBPGenreList[i].pQBPSongList[j].pQBPMusixBegin[l].dQBP_Duration;
                        tMusixNote.dQBP_Frequency        = pQBPGenreList[i].pQBPSongList[j].pQBPMusixBegin[l].dQBP_Frequency;
                        tMusixNote.iQBP_MidiShortMessage = pQBPGenreList[i].pQBPSongList[j].pQBPMusixBegin[l].iQBP_MidiShortMessage;
                        tMusixNote.iQBP_Octave           = pQBPGenreList[i].pQBPSongList[j].pQBPMusixBegin[l].iQBP_Octave;
                        tMusixNote.iQBP_Pitch            = pQBPGenreList[i].pQBPSongList[j].pQBPMusixBegin[l].iQBP_Pitch;
                        tMusixNote.iQBP_Contour          = pQBPGenreList[i].pQBPSongList[j].pQBPMusixBegin[l].iQBP_Contour;
                        tMusixNote.sQBP_Note             = pQBPGenreList[i].pQBPSongList[j].pQBPMusixBegin[l].sQBP_Note;

                        os  << tMusixNote.bQBP_IsBemol          << " "
                            << tMusixNote.bQBP_IsSharp          << " "
                            << tMusixNote.dQBP_Duration         << " "
                            << tMusixNote.dQBP_Frequency        << " "
                            << tMusixNote.iQBP_MidiShortMessage << " "
                            << tMusixNote.iQBP_Octave           << " "
                            << tMusixNote.iQBP_Pitch            << " "
                            << tMusixNote.iQBP_Contour          << " "
                            << tMusixNote.sQBP_Note             << " ";
                    }

                    for (int l = 0; l < tSongSize; l++)
                    {
                        stQBPStringBuffer tStringNote;

                        tStringNote.sQBP_Note   = pQBPGenreList[i].pQBPSongList[j].pQBPSongBufferStrip[QBP_STRIP_BEG][l].sQBP_Note;
                        tStringNote.iQBP_Octave = pQBPGenreList[i].pQBPSongList[j].pQBPSongBufferStrip[QBP_STRIP_BEG][l].iQBP_Octave;

                        os  << tStringNote.sQBP_Note          << " "
                            << tStringNote.iQBP_Octave        << " ";
                    }

                    os << "\n";
                }
            }break;
            case QBP_STRIP_MID:
            {
                if (pQBPGenreList[i].pQBPSongList[j].pQBPSongBufferStrip.size() >= 2)
                {
                    os << tName << " " << tCategory << " " << tNumFeatures << " ";

                    //Grava Features
                    for (int k = 0; k < tNumFeatures; k++)
                    {
                        double pQBPFeatureTypeId;
                        string pQBPFeatureName;
                        double pQBPFeatureValue;
                        pQBPGenreList[i].pQBPSongList[j].pQBPCustomFeatures[k].GetFeatureData(pQBPFeatureTypeId,
                                                                                              pQBPFeatureName,
                                                                                              pQBPFeatureValue);

                        //remove espaços e pontuação do nome da feature
                        pQBPFeatureName.erase(remove_if(pQBPFeatureName.begin(), pQBPFeatureName.end(), invalidChar), pQBPFeatureName.end());
                        pQBPFeatureName.erase(remove_if(pQBPFeatureName.begin(), pQBPFeatureName.end(), isSpaceChar), pQBPFeatureName.end());
                        pQBPFeatureName.erase(remove_if(pQBPFeatureName.begin(), pQBPFeatureName.end(), isPunctChar), pQBPFeatureName.end());

                        os << pQBPFeatureTypeId << " "
                            << pQBPFeatureName  << " "
                            << pQBPFeatureValue << " ";
                    }

                    //Grava Features Normalizadas
                    for (int k = 0; k < tNumFeatures; k++)
                    {
                        double pQBPFeatureTypeId;
                        string pQBPFeatureName;
                        double pQBPFeatureValue;
                        pQBPGenreList[i].pQBPSongList[j].pQBPNormalFeatures[k].GetFeatureData(pQBPFeatureTypeId,
                                                                                              pQBPFeatureName,
                                                                                              pQBPFeatureValue);

                        //remove espaços e pontuação do nome da feature
                        pQBPFeatureName.erase(remove_if(pQBPFeatureName.begin(), pQBPFeatureName.end(), invalidChar), pQBPFeatureName.end());
                        pQBPFeatureName.erase(remove_if(pQBPFeatureName.begin(), pQBPFeatureName.end(), isSpaceChar), pQBPFeatureName.end());
                        pQBPFeatureName.erase(remove_if(pQBPFeatureName.begin(), pQBPFeatureName.end(), isPunctChar), pQBPFeatureName.end());

                        os << pQBPFeatureTypeId << " "
                            << pQBPFeatureName  << " "
                            << pQBPFeatureValue << " ";
                    }

                    //Grava a quantidade de notas do buffer
                    int tSongSize = (int)pQBPGenreList[i].pQBPSongList[j].pQBPMusixMid.size();
                    os << tSongSize << " ";

                    for (int l = 0; l < tSongSize; l++)
                    {
                        stQBPMusicBuffer tMusixNote;

                        tMusixNote.bQBP_IsBemol          = pQBPGenreList[i].pQBPSongList[j].pQBPMusixMid[l].bQBP_IsBemol;
                        tMusixNote.bQBP_IsSharp          = pQBPGenreList[i].pQBPSongList[j].pQBPMusixMid[l].bQBP_IsSharp;
                        tMusixNote.dQBP_Duration         = pQBPGenreList[i].pQBPSongList[j].pQBPMusixMid[l].dQBP_Duration;
                        tMusixNote.dQBP_Frequency        = pQBPGenreList[i].pQBPSongList[j].pQBPMusixMid[l].dQBP_Frequency;
                        tMusixNote.iQBP_MidiShortMessage = pQBPGenreList[i].pQBPSongList[j].pQBPMusixMid[l].iQBP_MidiShortMessage;
                        tMusixNote.iQBP_Octave           = pQBPGenreList[i].pQBPSongList[j].pQBPMusixMid[l].iQBP_Octave;
                        tMusixNote.iQBP_Pitch            = pQBPGenreList[i].pQBPSongList[j].pQBPMusixMid[l].iQBP_Pitch;
                        tMusixNote.iQBP_Contour          = pQBPGenreList[i].pQBPSongList[j].pQBPMusixMid[l].iQBP_Contour;
                        tMusixNote.sQBP_Note             = pQBPGenreList[i].pQBPSongList[j].pQBPMusixMid[l].sQBP_Note;

                        os  << tMusixNote.bQBP_IsBemol          << " "
                            << tMusixNote.bQBP_IsSharp          << " "
                            << tMusixNote.dQBP_Duration         << " "
                            << tMusixNote.dQBP_Frequency        << " "
                            << tMusixNote.iQBP_MidiShortMessage << " "
                            << tMusixNote.iQBP_Octave           << " "
                            << tMusixNote.iQBP_Pitch            << " "
                            << tMusixNote.iQBP_Contour          << " "
                            << tMusixNote.sQBP_Note             << " ";
                    }

                    for (int l = 0; l < tSongSize; l++)
                    {
                        stQBPStringBuffer tStringNote;

                        tStringNote.sQBP_Note   = pQBPGenreList[i].pQBPSongList[j].pQBPSongBufferStrip[QBP_STRIP_MID][l].sQBP_Note;
                        tStringNote.iQBP_Octave = pQBPGenreList[i].pQBPSongList[j].pQBPSongBufferStrip[QBP_STRIP_MID][l].iQBP_Octave;

                        os  << tStringNote.sQBP_Note          << " "
                            << tStringNote.iQBP_Octave        << " ";
                    }

                    os << "\n";
                }
            }break;
            case QBP_STRIP_END:
            {
                if (pQBPGenreList[i].pQBPSongList[j].pQBPSongBufferStrip.size() >= 3)
                {
                    os << tName << " " << tCategory << " " << tNumFeatures << " ";

                    //Grava Features
                    for (int k = 0; k < tNumFeatures; k++)
                    {
                        double pQBPFeatureTypeId;
                        string pQBPFeatureName;
                        double pQBPFeatureValue;
                        pQBPGenreList[i].pQBPSongList[j].pQBPCustomFeatures[k].GetFeatureData(pQBPFeatureTypeId,
                                                                                              pQBPFeatureName,
                                                                                              pQBPFeatureValue);

                        //remove espaços e pontuação do nome da feature
                        pQBPFeatureName.erase(remove_if(pQBPFeatureName.begin(), pQBPFeatureName.end(), invalidChar), pQBPFeatureName.end());
                        pQBPFeatureName.erase(remove_if(pQBPFeatureName.begin(), pQBPFeatureName.end(), isSpaceChar), pQBPFeatureName.end());
                        pQBPFeatureName.erase(remove_if(pQBPFeatureName.begin(), pQBPFeatureName.end(), isPunctChar), pQBPFeatureName.end());

                        os << pQBPFeatureTypeId << " "
                            << pQBPFeatureName  << " "
                            << pQBPFeatureValue << " ";
                    }

                    //Grava Features Normalizadas
                    for (int k = 0; k < tNumFeatures; k++)
                    {
                        double pQBPFeatureTypeId;
                        string pQBPFeatureName;
                        double pQBPFeatureValue;
                        pQBPGenreList[i].pQBPSongList[j].pQBPNormalFeatures[k].GetFeatureData(pQBPFeatureTypeId,
                                                                                              pQBPFeatureName,
                                                                                              pQBPFeatureValue);

                        //remove espaços e pontuação do nome da feature
                        pQBPFeatureName.erase(remove_if(pQBPFeatureName.begin(), pQBPFeatureName.end(), invalidChar), pQBPFeatureName.end());
                        pQBPFeatureName.erase(remove_if(pQBPFeatureName.begin(), pQBPFeatureName.end(), isSpaceChar), pQBPFeatureName.end());
                        pQBPFeatureName.erase(remove_if(pQBPFeatureName.begin(), pQBPFeatureName.end(), isPunctChar), pQBPFeatureName.end());

                        os << pQBPFeatureTypeId << " "
                            << pQBPFeatureName  << " "
                            << pQBPFeatureValue << " ";
                    }

                    //Grava a quantidade de notas do buffer
                    int tSongSize = (int)pQBPGenreList[i].pQBPSongList[j].pQBPMusixEnd.size();
                    os << tSongSize << " ";

                    for (int l = 0; l < tSongSize; l++)
                    {
                        stQBPMusicBuffer tMusixNote;

                        tMusixNote.bQBP_IsBemol          = pQBPGenreList[i].pQBPSongList[j].pQBPMusixEnd[l].bQBP_IsBemol;
                        tMusixNote.bQBP_IsSharp          = pQBPGenreList[i].pQBPSongList[j].pQBPMusixEnd[l].bQBP_IsSharp;
                        tMusixNote.dQBP_Duration         = pQBPGenreList[i].pQBPSongList[j].pQBPMusixEnd[l].dQBP_Duration;
                        tMusixNote.dQBP_Frequency        = pQBPGenreList[i].pQBPSongList[j].pQBPMusixEnd[l].dQBP_Frequency;
                        tMusixNote.iQBP_MidiShortMessage = pQBPGenreList[i].pQBPSongList[j].pQBPMusixEnd[l].iQBP_MidiShortMessage;
                        tMusixNote.iQBP_Octave           = pQBPGenreList[i].pQBPSongList[j].pQBPMusixEnd[l].iQBP_Octave;
                        tMusixNote.iQBP_Pitch            = pQBPGenreList[i].pQBPSongList[j].pQBPMusixEnd[l].iQBP_Pitch;
                        tMusixNote.iQBP_Contour          = pQBPGenreList[i].pQBPSongList[j].pQBPMusixEnd[l].iQBP_Contour;
                        tMusixNote.sQBP_Note             = pQBPGenreList[i].pQBPSongList[j].pQBPMusixEnd[l].sQBP_Note;

                        os  << tMusixNote.bQBP_IsBemol          << " "
                            << tMusixNote.bQBP_IsSharp          << " "
                            << tMusixNote.dQBP_Duration         << " "
                            << tMusixNote.dQBP_Frequency        << " "
                            << tMusixNote.iQBP_MidiShortMessage << " "
                            << tMusixNote.iQBP_Octave           << " "
                            << tMusixNote.iQBP_Pitch            << " "
                            << tMusixNote.iQBP_Contour          << " "
                            << tMusixNote.sQBP_Note             << " ";
                    }

                    for (int l = 0; l < tSongSize; l++)
                    {
                        stQBPStringBuffer tStringNote;

                        tStringNote.sQBP_Note   = pQBPGenreList[i].pQBPSongList[j].pQBPSongBufferStrip[QBP_STRIP_END][l].sQBP_Note;
                        tStringNote.iQBP_Octave = pQBPGenreList[i].pQBPSongList[j].pQBPSongBufferStrip[QBP_STRIP_END][l].iQBP_Octave;

                        os  << tStringNote.sQBP_Note          << " "
                            << tStringNote.iQBP_Octave        << " ";
                    }

                    os << "\n";
                }
            }break;
            case QBP_STRIP_TOT:
            {
                os << tName << " " << tCategory << " " << tNumFeatures << " ";

                //Grava Features
                for (int k = 0; k < tNumFeatures; k++)
                {
                    double pQBPFeatureTypeId;
                    string pQBPFeatureName;
                    double pQBPFeatureValue;
                    pQBPGenreList[i].pQBPSongList[j].pQBPCustomFeatures[k].GetFeatureData(pQBPFeatureTypeId,
                                                                                          pQBPFeatureName,
                                                                                          pQBPFeatureValue);

                    //remove espaços e pontuação do nome da feature
                    pQBPFeatureName.erase(remove_if(pQBPFeatureName.begin(), pQBPFeatureName.end(), invalidChar), pQBPFeatureName.end());
                    pQBPFeatureName.erase(remove_if(pQBPFeatureName.begin(), pQBPFeatureName.end(), isSpaceChar), pQBPFeatureName.end());
                    pQBPFeatureName.erase(remove_if(pQBPFeatureName.begin(), pQBPFeatureName.end(), isPunctChar), pQBPFeatureName.end());

                    os << pQBPFeatureTypeId << " "
                        << pQBPFeatureName  << " "
                        << pQBPFeatureValue << " ";
                }

                //Grava Features Normalizadas
                for (int k = 0; k < tNumFeatures; k++)
                {
                    double pQBPFeatureTypeId;
                    string pQBPFeatureName;
                    double pQBPFeatureValue;
                    pQBPGenreList[i].pQBPSongList[j].pQBPNormalFeatures[k].GetFeatureData(pQBPFeatureTypeId,
                                                                                          pQBPFeatureName,
                                                                                          pQBPFeatureValue);

                    //remove espaços e pontuação do nome da feature
                    pQBPFeatureName.erase(remove_if(pQBPFeatureName.begin(), pQBPFeatureName.end(), invalidChar), pQBPFeatureName.end());
                    pQBPFeatureName.erase(remove_if(pQBPFeatureName.begin(), pQBPFeatureName.end(), isSpaceChar), pQBPFeatureName.end());
                    pQBPFeatureName.erase(remove_if(pQBPFeatureName.begin(), pQBPFeatureName.end(), isPunctChar), pQBPFeatureName.end());

                    os << pQBPFeatureTypeId << " "
                        << pQBPFeatureName  << " "
                        << pQBPFeatureValue << " ";
                }

                //Grava a quantidade de notas do buffer
                int tSongSize = (int)pQBPGenreList[i].pQBPSongList[j].pQBPMusixBuffer.size();
                os << tSongSize << " ";

                for (int l = 0; l < tSongSize; l++)
                {
                    stQBPMusicBuffer tMusixNote;

                    tMusixNote.bQBP_IsBemol          = pQBPGenreList[i].pQBPSongList[j].pQBPMusixBuffer[l].bQBP_IsBemol;
                    tMusixNote.bQBP_IsSharp          = pQBPGenreList[i].pQBPSongList[j].pQBPMusixBuffer[l].bQBP_IsSharp;
                    tMusixNote.dQBP_Duration         = pQBPGenreList[i].pQBPSongList[j].pQBPMusixBuffer[l].dQBP_Duration;
                    tMusixNote.dQBP_Frequency        = pQBPGenreList[i].pQBPSongList[j].pQBPMusixBuffer[l].dQBP_Frequency;
                    tMusixNote.iQBP_MidiShortMessage = pQBPGenreList[i].pQBPSongList[j].pQBPMusixBuffer[l].iQBP_MidiShortMessage;
                    tMusixNote.iQBP_Octave           = pQBPGenreList[i].pQBPSongList[j].pQBPMusixBuffer[l].iQBP_Octave;
                    tMusixNote.iQBP_Pitch            = pQBPGenreList[i].pQBPSongList[j].pQBPMusixBuffer[l].iQBP_Pitch;
                    tMusixNote.iQBP_Contour          = pQBPGenreList[i].pQBPSongList[j].pQBPMusixBuffer[l].iQBP_Contour;
                    tMusixNote.sQBP_Note             = pQBPGenreList[i].pQBPSongList[j].pQBPMusixBuffer[l].sQBP_Note;

                    os  << tMusixNote.bQBP_IsBemol          << " "
                        << tMusixNote.bQBP_IsSharp          << " "
                        << tMusixNote.dQBP_Duration         << " "
                        << tMusixNote.dQBP_Frequency        << " "
                        << tMusixNote.iQBP_MidiShortMessage << " "
                        << tMusixNote.iQBP_Octave           << " "
                        << tMusixNote.iQBP_Pitch            << " "
                        << tMusixNote.iQBP_Contour          << " "
                        << tMusixNote.sQBP_Note             << " ";
                }

                for (int l = 0; l < tSongSize; l++)
                {
                    stQBPStringBuffer tStringNote;

                    tStringNote.sQBP_Note   = pQBPGenreList[i].pQBPSongList[j].pQBPSongBuffer[l].sQBP_Note;
                    tStringNote.iQBP_Octave = pQBPGenreList[i].pQBPSongList[j].pQBPSongBuffer[l].iQBP_Octave;

                    os  << tStringNote.sQBP_Note          << " "
                        << tStringNote.iQBP_Octave        << " ";
                }

                os << "\n";
            }break;
            }
        }
    }
    //Fecha o arquivo
    fb.close();
    return true;
}

bool CQBPDataset::WriteSvm(string    pQBPath, int pQBPWrtOption)
{
    std::filebuf fb;
    fb.open(pQBPath, std::ios::out);

    //Grava dados na stream de arquivo
    std::ostream os(&fb);

    switch (pQBPWrtOption)
    {
    case QBP_SVM_TRAIN_DATASET:
    {
        //Formata e grava dados para o arquivo Dts
        for (int i = 0; i < pQBPGenreList.size(); i++)
        {
            for (int j = 0; j < pQBPGenreList[i].pQBPSongList.size(); j++)
            {
                //Caso, por algum motivo as features estejam vazias ignora a musica
                if (pQBPGenreList[i].pQBPSongList[j].pQBPCustomFeatures.size() == 0)continue;

                //Carrega as features da musica
                int     tCategory = pQBPGenreList[i].pQBPSongList[j].pQBPSongCategory;
                //Grava o label da classe(categoria)
                os << tCategory << "|";
                //Para cada feature gravamos apenas as que existem (f>0)
                for (int f = 0; f < pQBPMaxFeatures; f++)
                {
                    double featval = pQBPGenreList[i].pQBPSongList[j].pQBPCustomFeatures[f].GetFeatureValue();
                    //É pre-requisito de consistencia da base manter nfeatutes da svm iguais para todas as musicas
                    //com isto eliminamos memory leaks de processamento na SVM!!!
                    os << f+1 << ":" << featval << "|";
                }

                //grava a quebra de linha
                os << "\n";

            }
        }
    }break;
    case QBP_SVM_TRAIN_VALILIST:
    {
        //Formata e grava dados para o arquivo Dts
        for (int i = 0; i < pQBPValiList.size(); i++)
        {
            //Caso, por algum motivo as features estejam vazias ignora a musica
            if (pQBPValiList[i].pQBPCustomFeatures.size() == 0)continue;

            //Carrega as features da musica
            int     tCategory = pQBPValiList[i].pQBPSongCategory;
            //Grava o label da classe(categoria)
            os << tCategory << "|";

            //Para cada feature gravamos apenas as que existem (f>0)
            for (int f = 0; f < pQBPMaxFeatures; f++)
            {
                double featval = pQBPValiList[i].pQBPCustomFeatures[f].GetFeatureValue();
                //É pre-requisito de consistencia da base manter nfeatutes da svm iguais para todas as musicas
                //com isto eliminamos memory leaks de processamento na SVM!!!
                os << f+1 << ":" << featval << "|";
            }
            //grava a quebra de linha
            os << "\n";
        }
    }break;
    case QBP_SVM_TRAIN_TESTLIST:
    {
        //Formata e grava dados para o arquivo Dts
        for (int i = 0; i < pQBPTestList.size(); i++)
        {
            //Caso, por algum motivo as features estejam vazias ignora a musica
            if (pQBPTestList[i].pQBPCustomFeatures.size() == 0)continue;

            //Carrega as features da musica
            int     tCategory = pQBPTestList[i].pQBPSongCategory;

            //Grava o label da classe(categoria)
            os << tCategory << "|";

            //Para cada feature gravamos apenas as que existem (f>0)
            for (int f = 0; f < pQBPMaxFeatures; f++)
            {
                double featval = pQBPTestList[i].pQBPCustomFeatures[f].GetFeatureValue();
                //É pre-requisito de consistencia da base manter nfeatutes da svm iguais para todas as musicas
                //com isto eliminamos memory leaks de processamento na SVM!!!
                os << f+1 << ":" << featval << "|";
            }

            //grava a quebra de linha
            os << "\n";
        }
    }break;
    }


    //Fecha o arquivo
    fb.close();
    return true;
}

bool CQBPDataset::WriteSvmNorm(string    pQBPath, int pQBPWrtOption)
{
    std::filebuf fb;
    fb.open(pQBPath, std::ios::out);

    //Grava dados na stream de arquivo
    std::ostream os(&fb);

    switch (pQBPWrtOption)
    {
    case QBP_SVM_TRAIN_DATASET:
    {
        //Formata e grava dados para o arquivo Dts
        for (int i = 0; i < pQBPGenreList.size(); i++)
        {
            for (int j = 0; j < pQBPGenreList[i].pQBPSongList.size(); j++)
            {
                //Caso, por algum motivo as features estejam vazias ignora a musica
                if (pQBPGenreList[i].pQBPSongList[j].pQBPNormalFeatures.size() == 0)continue;

                //Carrega as features da musica
                int     tCategory = pQBPGenreList[i].pQBPSongList[j].pQBPSongCategory;

                //Grava o label da classe(categoria)
                os << tCategory << "|";
                //Para cada feature gravamos apenas as que existem (f>0)
                for (int f = 0; f < pQBPMaxFeatures; f++)
                {
                    double featval = pQBPGenreList[i].pQBPSongList[j].pQBPNormalFeatures[f].GetFeatureValue();
                    //É pre-requisito de consistencia da base manter nfeatutes da svm iguais para todas as musicas
                    //com isto eliminamos memory leaks de processamento na SVM!!!
                    os << f+1 << ":" << featval << "|";
                }

                //grava a quebra de linha
                os << "\n";

            }
        }
    }break;
    case QBP_SVM_TRAIN_VALILIST:
    {
        //Formata e grava dados para o arquivo Dts
        for (int i = 0; i < pQBPValiList.size(); i++)
        {
            //Caso, por algum motivo as features estejam vazias ignora a musica
            if (pQBPValiList[i].pQBPNormalFeatures.size() == 0)continue;

            //Carrega as features da musica
            int     tCategory = pQBPValiList[i].pQBPSongCategory;
            //Grava o label da classe(categoria)
            os << tCategory << "|";

            //Para cada feature gravamos apenas as que existem (f>0)
            for (int f = 0; f < pQBPMaxFeatures; f++)
            {
                double featval = pQBPValiList[i].pQBPNormalFeatures[f].GetFeatureValue();
                //É pre-requisito de consistencia da base manter nfeatutes da svm iguais para todas as musicas
                //com isto eliminamos memory leaks de processamento na SVM!!!
                os << f+1 << ":" << featval << "|";
            }
            //grava a quebra de linha
            os << "\n";
        }
    }break;
    case QBP_SVM_TRAIN_TESTLIST:
    {
        //Formata e grava dados para o arquivo Dts
        for (int i = 0; i < pQBPTestList.size(); i++)
        {
            //Caso, por algum motivo as features estejam vazias ignora a musica
            if (pQBPTestList[i].pQBPNormalFeatures.size() == 0)continue;

            //Carrega as features da musica
            int     tCategory = pQBPTestList[i].pQBPSongCategory;

            //Grava o label da classe(categoria)
            os << tCategory << "|";

            //Para cada feature gravamos apenas as que existem (f>0)
            for (int f = 0; f < pQBPMaxFeatures; f++)
            {
                double featval = pQBPTestList[i].pQBPNormalFeatures[f].GetFeatureValue();
                //É pre-requisito de consistencia da base manter nfeatutes da svm iguais para todas as musicas
                //com isto eliminamos memory leaks de processamento na SVM!!!
                os << f+1 << ":" << featval << "|";
            }

            //grava a quebra de linha
            os << "\n";
        }
    }break;
    }


    //Fecha o arquivo
    fb.close();
    return true;
}

bool CQBPDataset::WriteSvmCat(string    pQBPath , int pQBPWrtOption,int pQBPCategory)
{
    std::filebuf fb;
    fb.open(pQBPath, std::ios::out);

    //Grava dados na stream de arquivo
    std::ostream os(&fb);

    switch (pQBPWrtOption)
    {
    case QBP_SVM_TRAIN_DATASET:
    {
        //Formata e grava dados para o arquivo Dts
        for (int i = 0; i < pQBPGenreList.size(); i++)
        {
            for (int j = 0; j < pQBPGenreList[i].pQBPSongList.size(); j++)
            {
                //Caso, por algum motivo as features estejam vazias ignora a musica
                if (pQBPGenreList[i].pQBPSongList[j].pQBPNormalFeatures.size() == 0)continue;

                //Carrega as features da musica
                int     tCategory = pQBPGenreList[i].pQBPSongList[j].pQBPSongCategory;

                //transforma o arquivo em duas classes (0 - Verdadeiro | 1 - Falso)
                if(tCategory != pQBPCategory)
                {
                    tCategory = -1;
                }
                else
                {
                    tCategory =  1;
                }

                //Grava o label da classe(categoria)
                os << tCategory << "|";
                //Para cada feature gravamos apenas as que existem (f>0)
                for (int f = 0; f < pQBPMaxFeatures; f++)
                {
                    double featval = pQBPGenreList[i].pQBPSongList[j].pQBPNormalFeatures[f].GetFeatureValue();
                    //É pre-requisito de consistencia da base manter nfeatutes da svm iguais para todas as musicas
                    //com isto eliminamos memory leaks de processamento na SVM!!!
                    os << f+1 << ":" << featval << "|";
                }

                //grava a quebra de linha
                os << "\n";


            }
        }
    }break;
    case QBP_SVM_TRAIN_VALILIST:
    {
        //Formata e grava dados para o arquivo Dts
        for (int i = 0; i < pQBPValiList.size(); i++)
        {
            //Caso, por algum motivo as features estejam vazias ignora a musica
            if (pQBPValiList[i].pQBPNormalFeatures.size() == 0)continue;

            //Carrega as features da musica
            int     tCategory = pQBPValiList[i].pQBPSongCategory;

            //transforma o arquivo em duas classes (0 - Verdadeiro | 1 - Falso)
            //transforma o arquivo em duas classes (0 - Verdadeiro | 1 - Falso)
            if(tCategory != pQBPCategory)
            {
                tCategory = -1;
            }
            else
            {
                tCategory =  1;
            }


            //Grava o label da classe(categoria)
            os << tCategory << "|";

            //Para cada feature gravamos apenas as que existem (f>0)
            for (int f = 0; f < pQBPMaxFeatures; f++)
            {
                double featval = pQBPValiList[i].pQBPNormalFeatures[f].GetFeatureValue();
                //É pre-requisito de consistencia da base manter nfeatutes da svm iguais para todas as musicas
                //com isto eliminamos memory leaks de processamento na SVM!!!
                os << f+1 << ":" << featval << "|";
            }
            //grava a quebra de linha
            os << "\n";

        }
    }break;
    case QBP_SVM_TRAIN_TESTLIST:
    {
        //Formata e grava dados para o arquivo Dts
        for (int i = 0; i < pQBPTestList.size(); i++)
        {
            //Caso, por algum motivo as features estejam vazias ignora a musica
            if (pQBPTestList[i].pQBPNormalFeatures.size() == 0)continue;

            //Carrega as features da musica
            int     tCategory = pQBPTestList[i].pQBPSongCategory;

            //transforma o arquivo em duas classes (0 - Verdadeiro | 1 - Falso)
            //transforma o arquivo em duas classes (0 - Verdadeiro | 1 - Falso)
            if(tCategory != pQBPCategory)
            {
                tCategory = -1;
            }
            else
            {
                tCategory =  1;
            }

            //Grava o label da classe(categoria)
            os << tCategory << "|";

            //Para cada feature gravamos apenas as que existem (f>0)
            for (int f = 0; f < pQBPMaxFeatures; f++)
            {
                double featval = pQBPTestList[i].pQBPNormalFeatures[f].GetFeatureValue();
                //É pre-requisito de consistencia da base manter nfeatutes da svm iguais para todas as musicas
                //com isto eliminamos memory leaks de processamento na SVM!!!
                os << f+1 << ":" << featval << "|";
            }

            //grava a quebra de linha
            os << "\n";

        }
    }break;
    }


    //Fecha o arquivo
    fb.close();
    return true;
}

bool CQBPDataset::WriteGen(string    pQBPath)
{
    std::filebuf fb;
    fb.open(pQBPath, std::ios::out);

    //Grava dados na stream de arquivo
    std::ostream os(&fb);

    //Formata e grava dados para o arquivo Dts
    for (int i = 0; i < pQBPGenreList.size(); i++)
    {
        //Carrega o nome e genero da musica vindo da base de arquivos MIDI
        string tName = pQBPGenreList[i].pQBPGenreName;
        os  << tName << "\n";
    }

    //Fecha o arquivo
    fb.close();
    return true;
}

bool CQBPDataset::BuildMusicBuffers(int  pQBPTargetList)
{
    switch (pQBPTargetList)
    {
    case QBP_LOAD_TARGET_DATASET:
    {
        for (uint i = 0; i < pQBPGenreList.size(); i++)
        {
            for (uint j = 0; j < pQBPGenreList[i].pQBPSongList.size(); j++)
            {
                //Pede para o teclado enviar um buffer de notas em escala diatonica
                pQBPGenreList[i].pQBPSongList[j].pQBPSongBuffer = pQBPKeyboard.GetNoteBufferByDnt(pQBPGenreList[i].pQBPSongList[j].pQBPNotes,true,5);

                //Pede para o teclado enviar um buffer de notas em estrutura de notas Mussix
                pQBPGenreList[i].pQBPSongList[j].pQBPMusixBuffer = pQBPKeyboard.GetMusicBufferByDnt(pQBPGenreList[i].pQBPSongList[j].pQBPNotes,true,5);

                //Remove os bemois da lista de buffer textual para comparação
                //Esta função será removida pois viu-se que a utilização apenas de caracteres foi bom apenas no inicio...
                //após evoluir com o algoritmo esta limitação tornou-se inviável de progredir com o trablho , onde foi alterado para uma
                //estrutura e assim podermos simular os problemas na utilização de apenas strings
                //pQBPGenreList[i].pQBPSongList[j].RemoveBemol();
            }
        }
    }break;
    case QBP_LOAD_TARGET_TESTSET:
    {
        for (uint i = 0; i < pQBPTestList.size(); i++)
        {
            //Pede para o teclado enviar um buffer de notas em escala diatonica
            pQBPTestList[i].pQBPSongBuffer = pQBPKeyboard.GetNoteBufferByDnt(pQBPTestList[i].pQBPNotes,true,5);

            //Pede para o teclado enviar um buffer de notas em estrutura de notas Mussix
            pQBPTestList[i].pQBPMusixBuffer = pQBPKeyboard.GetMusicBufferByDnt(pQBPTestList[i].pQBPNotes,true,5);

            //Remove os bemois da lista de buffer textual para comparação
            //Esta função será removida pois viu-se que a utilização apenas de caracteres foi bom apenas no inicio...
            //após evoluir com o algoritmo esta limitação tornou-se inviável de progredir com o trablho , onde foi alterado para uma
            //estrutura e assim podermos simular os problemas na utilização de apenas strings
            //pQBPGenreList[i].pQBPSongList[j].RemoveBemol();
        }
    }break;
    case QBP_LOAD_TARGET_VALISET:
    {
        for (uint i = 0; i < pQBPValiList.size(); i++)
        {
            //Pede para o teclado enviar um buffer de notas em escala diatonica
            pQBPValiList[i].pQBPSongBuffer = pQBPKeyboard.GetNoteBufferByDnt(pQBPValiList[i].pQBPNotes,true,5);

            //Pede para o teclado enviar um buffer de notas em estrutura de notas Mussix
            pQBPValiList[i].pQBPMusixBuffer = pQBPKeyboard.GetMusicBufferByDnt(pQBPValiList[i].pQBPNotes,true,5);

            //Remove os bemois da lista de buffer textual para comparação
            //Esta função será removida pois viu-se que a utilização apenas de caracteres foi bom apenas no inicio...
            //após evoluir com o algoritmo esta limitação tornou-se inviável de progredir com o trablho , onde foi alterado para uma
            //estrutura e assim podermos simular os problemas na utilização de apenas strings
            //pQBPGenreList[i].pQBPSongList[j].RemoveBemol();
        }
    }break;
    case QBP_LOAD_TARGET_RANDSET:
    {
        for (int i = 0; i < pQBPRandomList.size(); i++)
        {
            //Pede para o teclado enviar um buffer de notas em escala diatonica
            pQBPRandomList[i].pQBPSongBuffer = pQBPKeyboard.GetNoteBufferByDnt(pQBPRandomList[i].pQBPNotes,true,5);

            //Pede para o teclado enviar um buffer de notas em estrutura de notas Mussix
            pQBPRandomList[i].pQBPMusixBuffer = pQBPKeyboard.GetMusicBufferByDnt(pQBPRandomList[i].pQBPNotes,true,5);

            //Remove os bemois da lista de buffer textual para comparação
            //Esta função será removida pois viu-se que a utilização apenas de caracteres foi bom apenas no inicio...
            //após evoluir com o algoritmo esta limitação tornou-se inviável de progredir com o trablho , onde foi alterado para uma
            //estrutura e assim podermos simular os problemas na utilização de apenas strings
            //pQBPGenreList[i].pQBPSongList[j].RemoveBemol();
        }
    }break;
    }


    return true;
}

bool CQBPDataset::BuildStrippedDts(int  pQBPTargetList)
{
    switch (pQBPTargetList)
    {
    case QBP_LOAD_TARGET_DATASET:
    {
        for (int i = 0; i < pQBPGenreList.size(); i++)
        {
            for (int j = 0; j < pQBPGenreList[i].pQBPSongList.size(); j++)
            {
                //Calcula o numero de notas por strip(Divide por 3 - Inicio/Meio/Fim Musica
                int tQtdNotas = abs((int)(pQBPGenreList[i].pQBPSongList[j].pQBPNotes.size() / 3));
                //Divide o Buffer em 3 strips
                pQBPGenreList[i].pQBPSongList[j].StripBuffer(tQtdNotas);
                //Normaliza os strips em 30 notas por strip.
                if(bQBPStretchStrip)pQBPGenreList[i].pQBPSongList[j].NormStripBuffer(iQBPStretchValue);
            }
        }
    }break;
    case QBP_LOAD_TARGET_TESTSET:
    {
        for (int i = 0; i < pQBPTestList.size(); i++)
        {
            //Calcula o numero de notas por strip(Divide por 3 - Inicio/Meio/Fim Musica
            int tQtdNotas = abs((int)(pQBPTestList[i].pQBPNotes.size() / 3));
            //Divide o Buffer em 3 strips
            pQBPTestList[i].StripBuffer(tQtdNotas);
            //Normaliza os strips em 30 notas por strip.
            if(bQBPStretchStrip)pQBPTestList[i].NormStripBuffer(iQBPStretchValue);
        }
    }break;
    case QBP_LOAD_TARGET_VALISET:
    {
        for (int i = 0; i < pQBPValiList.size(); i++)
        {
            //Calcula o numero de notas por strip(Divide por 3 - Inicio/Meio/Fim Musica
            int tQtdNotas = abs((int)(pQBPValiList[i].pQBPNotes.size() / 3));
            //Divide o Buffer em 3 strips
            pQBPValiList[i].StripBuffer(tQtdNotas);
            //Normaliza os strips em 30 notas por strip.
            if(bQBPStretchStrip)pQBPValiList[i].NormStripBuffer(iQBPStretchValue);
        }
    }break;
    case QBP_LOAD_TARGET_RANDSET:
    {
        for (int i = 0; i < pQBPRandomList.size(); i++)
        {
            //Calcula o numero de notas por strip(Divide por 3 - Inicio/Meio/Fim Musica
            int tQtdNotas = abs((int)(pQBPRandomList[i].pQBPNotes.size() / 3));
            //Divide o Buffer em 3 strips
            pQBPRandomList[i].StripBuffer(tQtdNotas);
            //Normaliza os strips em 30 notas por strip.
            if(bQBPStretchStrip)pQBPRandomList[i].NormStripBuffer(iQBPStretchValue);
        }
    }break;
    case QBP_LOAD_TARGET_FULLSET:
    {
        for (int i = 0; i < pQBPFullList.size(); i++)
        {
            //Calcula o numero de notas por strip(Divide por 3 - Inicio/Meio/Fim Musica
            int tQtdNotas = abs((int)(pQBPFullList[i].pQBPNotes.size() / 3));
            //Divide o Buffer em 3 strips
            pQBPFullList[i].StripBuffer(tQtdNotas);
            //Normaliza os strips em 30 notas por strip.
            if(bQBPStretchStrip)pQBPFullList[i].NormStripBuffer(iQBPStretchValue);
        }
    }break;
    }


    return true;
}

bool CQBPDataset::BuildFeaturesDts(int  pQBPTargetList)
{
    //BuildJSymboFeatType();
    //BuildJSymboFeatures(pQBPTargetList);
    BuildCustomFeatType();
    BuildCustomFeatures(pQBPTargetList);
    BuildNormalFeatures(pQBPTargetList);
    return true;
}

CQBPFeatureType CQBPDataset::GetFeatureType(string sQBP_FeatureName, int &iQBP_FeatureId)
{
    for (int i = 0; i < (int)pQBP_FeatureTypeList.size(); i++)
    {
        string tQBPFeatureName;
        string tQBPFeatureDescription;
        int    tQBPFeatureDimensions;
        bool   tQBPFeatureSequential;
        bool   tQBPFeatureCustom;
        pQBP_FeatureTypeList[i].GetFeatureTypeData(tQBPFeatureName,
                                                   tQBPFeatureDescription,
                                                   tQBPFeatureDimensions,
                                                   tQBPFeatureSequential,
                                                   tQBPFeatureCustom);
        if (sQBP_FeatureName == tQBPFeatureName)
        {
            iQBP_FeatureId = i;
            return CQBPFeatureType(tQBPFeatureName,
                tQBPFeatureDescription,
                tQBPFeatureDimensions,
                tQBPFeatureSequential,
                tQBPFeatureCustom);
        }
    }

    iQBP_FeatureId = 0;
    return pQBP_FeatureTypeList[0];
}

bool CQBPDataset::GetFeatureDimensions(string sQBP_FeatureName, int &iQBP_FeatureDimensions)
{
    for (int i = 0; i < (int)pQBP_FeatureTypeList.size(); i++)
    {
        string tQBPFeatureName;
        string tQBPFeatureDescription;
        int    tQBPFeatureDimensions;
        bool   tQBPFeatureSequential;
        bool   tQBPFeatureCustom;
        pQBP_FeatureTypeList[i].GetFeatureTypeData(tQBPFeatureName,
                                                   tQBPFeatureDescription,
                                                   tQBPFeatureDimensions,
                                                   tQBPFeatureSequential,
                                                   tQBPFeatureCustom);
        if (sQBP_FeatureName == tQBPFeatureName)
        {
            iQBP_FeatureDimensions = tQBPFeatureDimensions;
            return tQBPFeatureSequential;
        }
    }

    iQBP_FeatureDimensions=0;
    return false;
}

bool CQBPDataset::GetSongByName (string sQBP_SongName, CQBPSong &pQBPSong, int pQBPTargetList)
{
    switch(pQBPTargetList)
    {
    case QBP_LOAD_TARGET_DATASET:
    {
        for (int i = 0; i < pQBPGenreList.size(); i++)
        {
            for (int j = 0; j < pQBPGenreList[i].pQBPSongList.size(); j++)
            {
                if(pQBPGenreList[i].pQBPSongList[j].pQBPSongName==sQBP_SongName)
                {
                    pQBPSong = CQBPSong(pQBPGenreList[i].pQBPSongList[j]);
                    return true;
                }
            }
        }
    }break;
    case QBP_LOAD_TARGET_FULLSET:
    {
        for (int i = 0; i < pQBPFullList.size(); i++)
        {
            if(pQBPFullList[i].pQBPSongName==sQBP_SongName)
            {
                pQBPSong = CQBPSong(pQBPFullList[i]);
                return true;
            }
        }
    }break;
    case QBP_LOAD_TARGET_TESTSET:
    {
        for (int i = 0; i < pQBPTestList.size(); i++)
        {
            if(pQBPTestList[i].pQBPSongName==sQBP_SongName)
            {
                pQBPSong = CQBPSong(pQBPTestList[i]);
                return true;
            }
        }
    }break;
    case QBP_LOAD_TARGET_VALISET:
    {
        for (int i = 0; i < pQBPValiList.size(); i++)
        {
            if(pQBPValiList[i].pQBPSongName==sQBP_SongName)
            {
                pQBPSong = CQBPSong(pQBPValiList[i]);
                return true;
            }
        }
    }break;
    case QBP_LOAD_TARGET_RANDSET:
    {
        for (int i = 0; i < pQBPRandomList.size(); i++)
        {
            if(pQBPRandomList[i].pQBPSongName==sQBP_SongName)
            {
                pQBPSong = CQBPSong(pQBPRandomList[i]);
                return true;
            }
        }
    }break;
    }
    return false;
}

bool CQBPDataset::PlaySong(CQBPSong pQBPSong)
{
    pQBPKeyboard.Play(pQBPSong.pQBPMusixBuffer);
    return true;
}

DiatonicNote CQBPDataset::GetRandomNote(int pQBPOctave)
{
    return pQBPKeyboard.GetRandomNote(pQBPOctave);
}

bool CQBPDataset::BuildNormalFeatures(int  pQBPTargetList)
{
    vector<double> min;
    vector<double> max;

    //inicializa vetores (apenas por preciosidade...)
    for(uint i=0;i<(uint)pQBPMaxFeatures;i++)min.push_back(999);
    for(uint i=0;i<(uint)pQBPMaxFeatures;i++)max.push_back(0);

    for (uint i = 0; i < pQBPGenreList.size(); i++)
    {
        for (uint j = 0; j < pQBPGenreList[i].pQBPSongList.size(); j++)
        {
            for (uint k = 0; k < pQBPGenreList[i].pQBPSongList[j].pQBPCustomFeatures.size(); k++)
            {
                double tFeatVal = pQBPGenreList[i].pQBPSongList[j].pQBPCustomFeatures[k].GetFeatureValue();
                if(tFeatVal > max[k])max[k]=tFeatVal;
                if(tFeatVal < min[k])min[k]=tFeatVal;
            }
        }
    }

    switch (pQBPTargetList)
    {
    case QBP_LOAD_TARGET_DATASET:
    {
        CQBPLogQueue::Push(QString("Normalizando Caracteristicas QBP - Dataset! \n"));

        for (uint i = 0; i < pQBPGenreList.size(); i++)
        {
            for (uint j = 0; j < pQBPGenreList[i].pQBPSongList.size(); j++)
            {
                //apenas garante lista limpa de normais...
                if(pQBPGenreList[i].pQBPSongList[j].pQBPCustomFeatures.size()>0)
                {
                    pQBPGenreList[i].pQBPSongList[j].pQBPNormalFeatures.clear();
                    //Sempre colocar o reserve zero para economizar memoria(O clear não limpa a reserva de espaço)
                    pQBPGenreList[i].pQBPSongList[j].pQBPNormalFeatures.shrink_to_fit();
                }

                for (uint k = 0; k < pQBPGenreList[i].pQBPSongList[j].pQBPCustomFeatures.size(); k++)
                {
                    CQBPFeature     tFeature;
                    CQBPFeatureType tFeatureType;
                    double          tFeatureTypeId;
                    double          tFeatureValue;
                    string          tFeatureName;
                    double          tNormalValue;

                    pQBPGenreList[i].pQBPSongList[j].pQBPCustomFeatures[k].GetFeatureData(tFeatureTypeId,tFeatureName,tFeatureValue);

                    //Calcula o valor Normalizado
                    tNormalValue = (tFeatureValue - min[k])/(max[k]-min[k]);
                    //Constroi Feature Normalizada
                    tFeature      = CQBPFeature(tFeatureTypeId, tFeatureName, tNormalValue);
                    //Inclui a feature normalizada na Musica
                    pQBPGenreList[i].pQBPSongList[j].pQBPNormalFeatures.push_back(tFeature);

                }
            }
        }
    }break;
    case QBP_LOAD_TARGET_TESTSET:
    {
        CQBPLogQueue::Push(QString("Normalizando Caracteristicas QBP - TestList! \n"));

        for (uint i = 0; i < pQBPTestList.size(); i++)
        {
            //apenas garante lista limpa de normais...
            if(pQBPTestList[i].pQBPCustomFeatures.size()>0)
            {
                pQBPTestList[i].pQBPNormalFeatures.clear();
                //Sempre colocar o reserve zero para economizar memoria(O clear não limpa a reserva de espaço)
                pQBPTestList[i].pQBPNormalFeatures.shrink_to_fit();
            }

            for (uint j = 0; j < pQBPTestList[i].pQBPCustomFeatures.size(); j++)
            {
                CQBPFeature     tFeature;
                CQBPFeatureType tFeatureType;
                double          tFeatureTypeId;
                double          tFeatureValue;
                string          tFeatureName;
                double          tNormalValue;

                pQBPTestList[i].pQBPCustomFeatures[j].GetFeatureData(tFeatureTypeId,tFeatureName,tFeatureValue);

                //Calcula o valor Normalizado
                tNormalValue = (tFeatureValue - min[j])/(max[j]-min[j]);
                //Constroi Feature Normalizada
                tFeature      = CQBPFeature(tFeatureTypeId, tFeatureName, tNormalValue);
                //Inclui a feature normalizada na Musica
                pQBPTestList[i].pQBPNormalFeatures.push_back(tFeature);

            }
        }
    }break;
    case QBP_LOAD_TARGET_VALISET:
    {
        CQBPLogQueue::Push(QString("Normalizando Caracteristicas QBP - ValiList! \n"));

        for (uint i = 0; i < pQBPValiList.size(); i++)
        {
            //apenas garante lista limpa de normais...
            if(pQBPValiList[i].pQBPCustomFeatures.size()>0)
            {
                pQBPValiList[i].pQBPNormalFeatures.clear();
                //Sempre colocar o reserve zero para economizar memoria(O clear não limpa a reserva de espaço)
                pQBPValiList[i].pQBPNormalFeatures.shrink_to_fit();
            }

            for (uint j = 0; j < pQBPValiList[i].pQBPCustomFeatures.size(); j++)
            {
                CQBPFeature     tFeature;
                CQBPFeatureType tFeatureType;
                double          tFeatureTypeId;
                double          tFeatureValue;
                string          tFeatureName;
                double          tNormalValue;

                pQBPValiList[i].pQBPCustomFeatures[j].GetFeatureData(tFeatureTypeId,tFeatureName,tFeatureValue);

                //Calcula o valor Normalizado
                tNormalValue = (tFeatureValue - min[j])/(max[j]-min[j]);
                //Constroi Feature Normalizada
                tFeature      = CQBPFeature(tFeatureTypeId, tFeatureName, tNormalValue);
                //Inclui a feature normalizada na Musica
                pQBPValiList[i].pQBPNormalFeatures.push_back(tFeature);
            }
        }
    }break;
    case QBP_LOAD_TARGET_RANDSET:
    {
        CQBPLogQueue::Push(QString("Normalizando Caracteristicas QBP - ValiList! \n"));

        for (uint i = 0; i < pQBPRandomList.size(); i++)
        {
            //apenas garante lista limpa de normais...
            if(pQBPRandomList[i].pQBPCustomFeatures.size()>0)
            {
                pQBPRandomList[i].pQBPNormalFeatures.clear();
                //Sempre colocar o reserve zero para economizar memoria(O clear não limpa a reserva de espaço)
                pQBPRandomList[i].pQBPNormalFeatures.shrink_to_fit();
            }

            for (uint j = 0; j < pQBPRandomList[i].pQBPCustomFeatures.size(); j++)
            {
                CQBPFeature     tFeature;
                CQBPFeatureType tFeatureType;
                double          tFeatureTypeId;
                double          tFeatureValue;
                string          tFeatureName;
                double          tNormalValue;

                pQBPRandomList[i].pQBPCustomFeatures[j].GetFeatureData(tFeatureTypeId,tFeatureName,tFeatureValue);

                //Calcula o valor Normalizado
                tNormalValue = (tFeatureValue - min[j])/(max[j]-min[j]);
                //Constroi Feature Normalizada
                tFeature      = CQBPFeature(tFeatureTypeId, tFeatureName, tNormalValue);
                //Inclui a feature normalizada na Musica
                pQBPRandomList[i].pQBPNormalFeatures.push_back(tFeature);
            }
        }
    }break;
    }

    return true;
}

bool CQBPDataset::BuildCustomFeatures(int  pQBPTargetList)
{
    switch (pQBPTargetList)
    {
    case QBP_LOAD_TARGET_DATASET:
    {
        for (int i = 0; i < pQBPGenreList.size(); i++)
        {
            for (int j = 0; j < pQBPGenreList[i].pQBPSongList.size(); j++)
            {
                if (!pQBPGenreList[i].pQBPSongList[j].pQBPFeatured)
                {
                    CQBPFeature     tFeature;
                    CQBPFeatureType tFeatureType;
                    int             tFeatureId;
                    double          tFeatureValue;

                    //CQBPLogQueue::Push(QString("Construindo Caracteristicas QBP Musica: "));
                    //CQBPLogQueue::Push(QString(pQBPGenreList[i].pQBPSongList[j].pQBPSongName.c_str()));
                    //CQBPLogQueue::Push(QString("\n"));

                    //extrai o numero de oitavas usada na musica
                    tFeatureValue= pQBPKeyboard.ExtractOctaveFeature(pQBPGenreList[i].pQBPSongList[j].pQBPNotes);
                    tFeatureType = GetFeatureType("OitavasCustom", tFeatureId);
                    tFeature = CQBPFeature(tFeatureId, tFeatureType.GetFeatureName(), tFeatureValue);
                    pQBPGenreList[i].pQBPSongList[j].pQBPCustomFeatures.push_back(tFeature);

                    //extrai o numero de bemois utilizados na musica.
                    tFeatureValue = pQBPKeyboard.ExtractBemoisFeature(pQBPGenreList[i].pQBPSongList[j].pQBPNotes);
                    tFeatureType = GetFeatureType("BemoisCustom", tFeatureId);
                    tFeature = CQBPFeature(tFeatureId, tFeatureType.GetFeatureName(), tFeatureValue);
                    pQBPGenreList[i].pQBPSongList[j].pQBPCustomFeatures.push_back(tFeature);

                    //extrai o tempo medio entre as notas da musica
                    tFeatureValue = pQBPKeyboard.ExtractTMedioFeature(pQBPGenreList[i].pQBPSongList[j].pQBPNotes);
                    tFeatureType = GetFeatureType("TempoMédioCustom", tFeatureId);
                    tFeature = CQBPFeature(tFeatureId, tFeatureType.GetFeatureName(), tFeatureValue);
                    pQBPGenreList[i].pQBPSongList[j].pQBPCustomFeatures.push_back(tFeature);

                    //extrai a nota mais usada na musica
                    tFeatureValue = pQBPKeyboard.ExtractFPitchFeature(pQBPGenreList[i].pQBPSongList[j].pQBPNotes);
                    tFeatureType = GetFeatureType("PitchFrequente", tFeatureId);
                    tFeature = CQBPFeature(tFeatureId, tFeatureType.GetFeatureName(), tFeatureValue);
                    pQBPGenreList[i].pQBPSongList[j].pQBPCustomFeatures.push_back(tFeature);

                    //extrai a quantidade de notas unicas usada na musica
                    tFeatureValue = pQBPKeyboard.ExtractNPitchFeature(pQBPGenreList[i].pQBPSongList[j].pQBPNotes);
                    tFeatureType = GetFeatureType("NumerodePitchs", tFeatureId);
                    tFeature = CQBPFeature(tFeatureId, tFeatureType.GetFeatureName(), tFeatureValue);
                    pQBPGenreList[i].pQBPSongList[j].pQBPCustomFeatures.push_back(tFeature);

                    //extrai o maior numero de repeticoes consecutivas da mesma nota
                    tFeatureValue = pQBPKeyboard.ExtractRPitchFeature(pQBPGenreList[i].pQBPSongList[j].pQBPNotes);
                    tFeatureType = GetFeatureType("RepeticoesdePitchFrequente", tFeatureId);
                    tFeature = CQBPFeature(tFeatureId, tFeatureType.GetFeatureName(), tFeatureValue);
                    pQBPGenreList[i].pQBPSongList[j].pQBPCustomFeatures.push_back(tFeature);

                    //extrai a atitude da musica pelas features(Tempo medio entre as notas / pelo maior numero de notas repetidas)
                    tFeatureValue = pQBPKeyboard.ExtractAttituFeature(pQBPGenreList[i].pQBPSongList[j].pQBPNotes);
                    tFeatureType = GetFeatureType("AtitudedoMusico", tFeatureId);
                    tFeature = CQBPFeature(tFeatureId, tFeatureType.GetFeatureName(), tFeatureValue);
                    pQBPGenreList[i].pQBPSongList[j].pQBPCustomFeatures.push_back(tFeature);

                    //extrai o BPM medio da musica
                    tFeatureValue = pQBPKeyboard.ExtractBpmmedFeature(pQBPGenreList[i].pQBPSongList[j].pQBPNotes);
                    tFeatureType = GetFeatureType("BPMMedio", tFeatureId);
                    tFeature = CQBPFeature(tFeatureId, tFeatureType.GetFeatureName(), tFeatureValue);
                    pQBPGenreList[i].pQBPSongList[j].pQBPCustomFeatures.push_back(tFeature);

                    //extrai o numero de notas usada na musica
                    tFeatureValue = (double)pQBPGenreList[i].pQBPSongList[j].pQBPNotes.size();
                    tFeatureType  = GetFeatureType("NumeroNotas", tFeatureId);
                    tFeature      = CQBPFeature(tFeatureId, tFeatureType.GetFeatureName(), tFeatureValue);
                    pQBPGenreList[i].pQBPSongList[j].pQBPCustomFeatures.push_back(tFeature);

                    //extrai duração em milisegundos total da música
                    tFeatureValue = pQBPKeyboard.ExtractTTotalFeature(pQBPGenreList[i].pQBPSongList[j].pQBPNotes);
                    tFeatureType  = GetFeatureType("TempoTotal", tFeatureId);
                    tFeature      = CQBPFeature(tFeatureId, tFeatureType.GetFeatureName(), tFeatureValue);
                    pQBPGenreList[i].pQBPSongList[j].pQBPCustomFeatures.push_back(tFeature);

                    //extrai o HISTOGRAMA DIATONICO da musica(cada nota vira uma feature)
                    int C,CS,D,DS,E,F,FS,G,GS,A,AS,B;
                    pQBPKeyboard.ExtractDtncHistogram(pQBPGenreList[i].pQBPSongList[j].pQBPNotes,C,CS,D,DS,E,F,FS,G,GS,A,AS,B);

                    tFeatureValue = C;
                    tFeatureType  = GetFeatureType("HSTNotaC", tFeatureId);
                    tFeature = CQBPFeature(tFeatureId, tFeatureType.GetFeatureName(), tFeatureValue);
                    pQBPGenreList[i].pQBPSongList[j].pQBPCustomFeatures.push_back(tFeature);

                    tFeatureValue = CS;
                    tFeatureType  = GetFeatureType("HSTNotaCS", tFeatureId);
                    tFeature = CQBPFeature(tFeatureId, tFeatureType.GetFeatureName(), tFeatureValue);
                    pQBPGenreList[i].pQBPSongList[j].pQBPCustomFeatures.push_back(tFeature);

                    tFeatureValue = D;
                    tFeatureType  = GetFeatureType("HSTNotaD", tFeatureId);
                    tFeature = CQBPFeature(tFeatureId, tFeatureType.GetFeatureName(), tFeatureValue);
                    pQBPGenreList[i].pQBPSongList[j].pQBPCustomFeatures.push_back(tFeature);

                    tFeatureValue = DS;
                    tFeatureType  = GetFeatureType("HSTNotaDS", tFeatureId);
                    tFeature = CQBPFeature(tFeatureId, tFeatureType.GetFeatureName(), tFeatureValue);
                    pQBPGenreList[i].pQBPSongList[j].pQBPCustomFeatures.push_back(tFeature);

                    tFeatureValue = E;
                    tFeatureType  = GetFeatureType("HSTNotaE", tFeatureId);
                    tFeature = CQBPFeature(tFeatureId, tFeatureType.GetFeatureName(), tFeatureValue);
                    pQBPGenreList[i].pQBPSongList[j].pQBPCustomFeatures.push_back(tFeature);

                    tFeatureValue = F;
                    tFeatureType  = GetFeatureType("HSTNotaF", tFeatureId);
                    tFeature = CQBPFeature(tFeatureId, tFeatureType.GetFeatureName(), tFeatureValue);
                    pQBPGenreList[i].pQBPSongList[j].pQBPCustomFeatures.push_back(tFeature);

                    tFeatureValue = FS;
                    tFeatureType  = GetFeatureType("HSTNotaFS", tFeatureId);
                    tFeature = CQBPFeature(tFeatureId, tFeatureType.GetFeatureName(), tFeatureValue);
                    pQBPGenreList[i].pQBPSongList[j].pQBPCustomFeatures.push_back(tFeature);

                    tFeatureValue = G;
                    tFeatureType  = GetFeatureType("HSTNotaG", tFeatureId);
                    tFeature = CQBPFeature(tFeatureId, tFeatureType.GetFeatureName(), tFeatureValue);
                    pQBPGenreList[i].pQBPSongList[j].pQBPCustomFeatures.push_back(tFeature);

                    tFeatureValue = GS;
                    tFeatureType  = GetFeatureType("HSTNotaGS", tFeatureId);
                    tFeature = CQBPFeature(tFeatureId, tFeatureType.GetFeatureName(), tFeatureValue);
                    pQBPGenreList[i].pQBPSongList[j].pQBPCustomFeatures.push_back(tFeature);

                    tFeatureValue = A;
                    tFeatureType  = GetFeatureType("HSTNotaA", tFeatureId);
                    tFeature = CQBPFeature(tFeatureId, tFeatureType.GetFeatureName(), tFeatureValue);
                    pQBPGenreList[i].pQBPSongList[j].pQBPCustomFeatures.push_back(tFeature);

                    tFeatureValue = AS;
                    tFeatureType  = GetFeatureType("HSTNotaAS", tFeatureId);
                    tFeature = CQBPFeature(tFeatureId, tFeatureType.GetFeatureName(), tFeatureValue);
                    pQBPGenreList[i].pQBPSongList[j].pQBPCustomFeatures.push_back(tFeature);

                    tFeatureValue = B;
                    tFeatureType  = GetFeatureType("HSTNotaB", tFeatureId);
                    tFeature = CQBPFeature(tFeatureId, tFeatureType.GetFeatureName(), tFeatureValue);
                    pQBPGenreList[i].pQBPSongList[j].pQBPCustomFeatures.push_back(tFeature);

                    pQBPMaxFeatures = (uint)pQBPGenreList[i].pQBPSongList[j].pQBPCustomFeatures.size();
                    pQBPGenreList[i].pQBPSongList[j].pQBPFeatured = true;
                }
            }
        }
    }break;
    case QBP_LOAD_TARGET_TESTSET:
    {
        for (int i = 0; i < pQBPTestList.size(); i++)
        {
            if (!pQBPTestList[i].pQBPFeatured)
            {
                CQBPFeature     tFeature;
                CQBPFeatureType tFeatureType;
                int             tFeatureId;
                double          tFeatureValue;

                //CQBPLogQueue::Push(QString("Construindo Caracteristicas QBP Musica: "));
                //CQBPLogQueue::Push(QString(pQBPTestList[i].pQBPSongName.c_str()));
                //CQBPLogQueue::Push(QString("\n"));

                //extrai o numero de oitavas usada na musica
                tFeatureValue = pQBPKeyboard.ExtractOctaveFeature(pQBPTestList[i].pQBPNotes);
                tFeatureType = GetFeatureType("OitavasCustom", tFeatureId);
                tFeature = CQBPFeature(tFeatureId, tFeatureType.GetFeatureName(), tFeatureValue);
                pQBPTestList[i].pQBPCustomFeatures.push_back(tFeature);

                //extrai o numero de bemois utilizados na musica.
                tFeatureValue = pQBPKeyboard.ExtractBemoisFeature(pQBPTestList[i].pQBPNotes);
                tFeatureType = GetFeatureType("BemoisCustom", tFeatureId);
                tFeature = CQBPFeature(tFeatureId, tFeatureType.GetFeatureName(), tFeatureValue);
                pQBPTestList[i].pQBPCustomFeatures.push_back(tFeature);

                //extrai o tempo medio entre as notas da musica
                tFeatureValue = pQBPKeyboard.ExtractTMedioFeature(pQBPTestList[i].pQBPNotes);
                tFeatureType = GetFeatureType("TempoMédioCustom", tFeatureId);
                tFeature = CQBPFeature(tFeatureId, tFeatureType.GetFeatureName(), tFeatureValue);
                pQBPTestList[i].pQBPCustomFeatures.push_back(tFeature);

                //extrai a nota mais usada na musica
                tFeatureValue = pQBPKeyboard.ExtractFPitchFeature(pQBPTestList[i].pQBPNotes);
                tFeatureType = GetFeatureType("PitchFrequente", tFeatureId);
                tFeature = CQBPFeature(tFeatureId, tFeatureType.GetFeatureName(), tFeatureValue);
                pQBPTestList[i].pQBPCustomFeatures.push_back(tFeature);

                //extrai a quantidade de notas unicas usada na musica
                tFeatureValue = pQBPKeyboard.ExtractNPitchFeature(pQBPTestList[i].pQBPNotes);
                tFeatureType = GetFeatureType("NumerodePitchs", tFeatureId);
                tFeature = CQBPFeature(tFeatureId, tFeatureType.GetFeatureName(), tFeatureValue);
                pQBPTestList[i].pQBPCustomFeatures.push_back(tFeature);

                //extrai o maior numero de repeticoes consecutivas da mesma nota
                tFeatureValue = pQBPKeyboard.ExtractRPitchFeature(pQBPTestList[i].pQBPNotes);
                tFeatureType = GetFeatureType("RepeticoesdePitchFrequente", tFeatureId);
                tFeature = CQBPFeature(tFeatureId, tFeatureType.GetFeatureName(), tFeatureValue);
                pQBPTestList[i].pQBPCustomFeatures.push_back(tFeature);

                //extrai a atitude da musica pelas features(Tempo medio entre as notas / pelo maior numero de notas repetidas)
                tFeatureValue = pQBPKeyboard.ExtractAttituFeature(pQBPTestList[i].pQBPNotes);
                tFeatureType = GetFeatureType("AtitudedoMusico", tFeatureId);
                tFeature = CQBPFeature(tFeatureId, tFeatureType.GetFeatureName(), tFeatureValue);
                pQBPTestList[i].pQBPCustomFeatures.push_back(tFeature);

                //extrai o BPM medio da musica
                tFeatureValue = pQBPKeyboard.ExtractBpmmedFeature(pQBPTestList[i].pQBPNotes);
                tFeatureType = GetFeatureType("BPMMedio", tFeatureId);
                tFeature = CQBPFeature(tFeatureId, tFeatureType.GetFeatureName(), tFeatureValue);
                pQBPTestList[i].pQBPCustomFeatures.push_back(tFeature);

                pQBPTestList[i].pQBPFeatured = true;
            }
        }
    }break;
    case QBP_LOAD_TARGET_VALISET:
    {
        for (int i = 0; i < pQBPValiList.size(); i++)
        {
            if (!pQBPValiList[i].pQBPFeatured)
            {
                CQBPFeature     tFeature;
                CQBPFeatureType tFeatureType;
                int             tFeatureId;
                double          tFeatureValue;

                //CQBPLogQueue::Push(QString("Construindo Caracteristicas QBP Musica: "));
                //CQBPLogQueue::Push(QString(pQBPValiList[i].pQBPSongName.c_str()));
                //CQBPLogQueue::Push(QString("\n"));

                //extrai o numero de oitavas usada na musica
                tFeatureValue = pQBPKeyboard.ExtractOctaveFeature(pQBPValiList[i].pQBPNotes);
                tFeatureType = GetFeatureType("OitavasCustom", tFeatureId);
                tFeature = CQBPFeature(tFeatureId, tFeatureType.GetFeatureName(), tFeatureValue);
                pQBPValiList[i].pQBPCustomFeatures.push_back(tFeature);

                //extrai o numero de bemois utilizados na musica.
                tFeatureValue = pQBPKeyboard.ExtractBemoisFeature(pQBPValiList[i].pQBPNotes);
                tFeatureType = GetFeatureType("BemoisCustom", tFeatureId);
                tFeature = CQBPFeature(tFeatureId, tFeatureType.GetFeatureName(), tFeatureValue);
                pQBPValiList[i].pQBPCustomFeatures.push_back(tFeature);

                //extrai o tempo medio entre as notas da musica
                tFeatureValue = pQBPKeyboard.ExtractTMedioFeature(pQBPValiList[i].pQBPNotes);
                tFeatureType = GetFeatureType("TempoMédioCustom", tFeatureId);
                tFeature = CQBPFeature(tFeatureId, tFeatureType.GetFeatureName(), tFeatureValue);
                pQBPValiList[i].pQBPCustomFeatures.push_back(tFeature);

                //extrai a nota mais usada na musica
                tFeatureValue = pQBPKeyboard.ExtractFPitchFeature(pQBPValiList[i].pQBPNotes);
                tFeatureType = GetFeatureType("PitchFrequente", tFeatureId);
                tFeature = CQBPFeature(tFeatureId, tFeatureType.GetFeatureName(), tFeatureValue);
                pQBPValiList[i].pQBPCustomFeatures.push_back(tFeature);

                //extrai a quantidade de notas unicas usada na musica
                tFeatureValue = pQBPKeyboard.ExtractNPitchFeature(pQBPValiList[i].pQBPNotes);
                tFeatureType = GetFeatureType("NumerodePitchs", tFeatureId);
                tFeature = CQBPFeature(tFeatureId, tFeatureType.GetFeatureName(), tFeatureValue);
                pQBPValiList[i].pQBPCustomFeatures.push_back(tFeature);

                //extrai o maior numero de repeticoes consecutivas da mesma nota
                tFeatureValue = pQBPKeyboard.ExtractRPitchFeature(pQBPValiList[i].pQBPNotes);
                tFeatureType = GetFeatureType("RepeticoesdePitchFrequente", tFeatureId);
                tFeature = CQBPFeature(tFeatureId, tFeatureType.GetFeatureName(), tFeatureValue);
                pQBPValiList[i].pQBPCustomFeatures.push_back(tFeature);

                //extrai a atitude da musica pelas features(Tempo medio entre as notas / pelo maior numero de notas repetidas)
                tFeatureValue = pQBPKeyboard.ExtractAttituFeature(pQBPValiList[i].pQBPNotes);
                tFeatureType = GetFeatureType("AtitudedoMusico", tFeatureId);
                tFeature = CQBPFeature(tFeatureId, tFeatureType.GetFeatureName(), tFeatureValue);
                pQBPValiList[i].pQBPCustomFeatures.push_back(tFeature);

                //extrai o BPM medio da musica
                tFeatureValue = pQBPKeyboard.ExtractBpmmedFeature(pQBPValiList[i].pQBPNotes);
                tFeatureType = GetFeatureType("BPMMedio", tFeatureId);
                tFeature = CQBPFeature(tFeatureId, tFeatureType.GetFeatureName(), tFeatureValue);
                pQBPValiList[i].pQBPCustomFeatures.push_back(tFeature);

                pQBPValiList[i].pQBPFeatured = true;
            }
        }
    }break;
    case QBP_LOAD_TARGET_RANDSET:
    {
        for (int i = 0; i < pQBPRandomList.size(); i++)
        {
            if (!pQBPRandomList[i].pQBPFeatured)
            {
                CQBPFeature     tFeature;
                CQBPFeatureType tFeatureType;
                int             tFeatureId;
                double          tFeatureValue;

                //CQBPLogQueue::Push(QString("Construindo Caracteristicas QBP Musica: "));
                //CQBPLogQueue::Push(QString(pQBPRandomList[i].pQBPSongName.c_str()));
                //CQBPLogQueue::Push(QString("\n"));

                //extrai o numero de oitavas usada na musica
                tFeatureValue = pQBPKeyboard.ExtractOctaveFeature(pQBPRandomList[i].pQBPNotes);
                tFeatureType = GetFeatureType("OitavasCustom", tFeatureId);
                tFeature = CQBPFeature(tFeatureId, tFeatureType.GetFeatureName(), tFeatureValue);
                pQBPRandomList[i].pQBPCustomFeatures.push_back(tFeature);

                //extrai o numero de bemois utilizados na musica.
                tFeatureValue = pQBPKeyboard.ExtractBemoisFeature(pQBPRandomList[i].pQBPNotes);
                tFeatureType = GetFeatureType("BemoisCustom", tFeatureId);
                tFeature = CQBPFeature(tFeatureId, tFeatureType.GetFeatureName(), tFeatureValue);
                pQBPRandomList[i].pQBPCustomFeatures.push_back(tFeature);

                //extrai o tempo medio entre as notas da musica
                tFeatureValue = pQBPKeyboard.ExtractTMedioFeature(pQBPRandomList[i].pQBPNotes);
                tFeatureType = GetFeatureType("TempoMédioCustom", tFeatureId);
                tFeature = CQBPFeature(tFeatureId, tFeatureType.GetFeatureName(), tFeatureValue);
                pQBPRandomList[i].pQBPCustomFeatures.push_back(tFeature);

                //extrai a nota mais usada na musica
                tFeatureValue = pQBPKeyboard.ExtractFPitchFeature(pQBPRandomList[i].pQBPNotes);
                tFeatureType = GetFeatureType("PitchFrequente", tFeatureId);
                tFeature = CQBPFeature(tFeatureId, tFeatureType.GetFeatureName(), tFeatureValue);
                pQBPRandomList[i].pQBPCustomFeatures.push_back(tFeature);

                //extrai a quantidade de notas unicas usada na musica
                tFeatureValue = pQBPKeyboard.ExtractNPitchFeature(pQBPRandomList[i].pQBPNotes);
                tFeatureType = GetFeatureType("NumerodePitchs", tFeatureId);
                tFeature = CQBPFeature(tFeatureId, tFeatureType.GetFeatureName(), tFeatureValue);
                pQBPRandomList[i].pQBPCustomFeatures.push_back(tFeature);

                //extrai o maior numero de repeticoes consecutivas da mesma nota
                tFeatureValue = pQBPKeyboard.ExtractRPitchFeature(pQBPRandomList[i].pQBPNotes);
                tFeatureType = GetFeatureType("RepeticoesdePitchFrequente", tFeatureId);
                tFeature = CQBPFeature(tFeatureId, tFeatureType.GetFeatureName(), tFeatureValue);
                pQBPRandomList[i].pQBPCustomFeatures.push_back(tFeature);

                //extrai a atitude da musica pelas features(Tempo medio entre as notas / pelo maior numero de notas repetidas)
                tFeatureValue = pQBPKeyboard.ExtractAttituFeature(pQBPRandomList[i].pQBPNotes);
                tFeatureType = GetFeatureType("AtitudedoMusico", tFeatureId);
                tFeature = CQBPFeature(tFeatureId, tFeatureType.GetFeatureName(), tFeatureValue);
                pQBPRandomList[i].pQBPCustomFeatures.push_back(tFeature);

                //extrai o BPM medio da musica
                tFeatureValue = pQBPKeyboard.ExtractBpmmedFeature(pQBPRandomList[i].pQBPNotes);
                tFeatureType = GetFeatureType("BPMMedio", tFeatureId);
                tFeature = CQBPFeature(tFeatureId, tFeatureType.GetFeatureName(), tFeatureValue);
                pQBPRandomList[i].pQBPCustomFeatures.push_back(tFeature);

                pQBPRandomList[i].pQBPFeatured = true;
            }
        }
    }break;
    }

    return true;
}

bool CQBPDataset::BuildJSymboFeatures(int  pQBPTargetList)
{
    switch (pQBPTargetList)
    {
    case QBP_LOAD_TARGET_DATASET:
    {
        pArqJSymbolic.LoadJSymbolicDefinitions();
        pArqJSymbolic.LoadJSymbolicDatabase();
        //pArqJSymbolic.ParseFeatures(pQBPGenreList, pQBP_FeatureTypeList);
    }break;
    case QBP_LOAD_TARGET_TESTSET:
    {
        pArqJSymbolic.ParseFeatures(pQBPTestList , pQBP_FeatureTypeList);
    }break;
    case QBP_LOAD_TARGET_VALISET:
    {
        pArqJSymbolic.ParseFeatures(pQBPValiList , pQBP_FeatureTypeList);
    }break;
    case QBP_LOAD_TARGET_RANDSET:
    {
        pArqJSymbolic.ParseFeatures(pQBPRandomList , pQBP_FeatureTypeList);
    }break;
    }

    return true;
}

bool CQBPDataset::BuildCustomFeatType()
{
    CQBPFeature tFeature;
    CQBPFeatureType tFeatureType;

    //extrai o numero de oitavas usada na musica
    tFeatureType = CQBPFeatureType("OitavasCustom","Numero de Oitavas utilizadas na musica.",1,false,true);
    pQBP_FeatureTypeList.push_back(tFeatureType);
    //extrai o numero de bemois utilizados na musica.
    tFeatureType = CQBPFeatureType("BemoisCustom", "Numero de bemois utilizadas na musica.", 1, false, true);
    pQBP_FeatureTypeList.push_back(tFeatureType);
    //extrai o tempo medio entre as notas da musica
    tFeatureType = CQBPFeatureType("TempoMédioCustom", "extrai o tempo medio entre as notas da musica.", 1, false, true);
    pQBP_FeatureTypeList.push_back(tFeatureType);
    //extrai a nota mais usada na musica
    tFeatureType = CQBPFeatureType("PitchFrequente", "extrai a nota mais usada na musica.", 1, false, true);
    pQBP_FeatureTypeList.push_back(tFeatureType);
    //extrai a quantidade de notas unicas usada na musica
    tFeatureType = CQBPFeatureType("NumerodePitchs", "extrai a quantidade de notas unicas usada na musica.", 1, false, true);
    pQBP_FeatureTypeList.push_back(tFeatureType);
    //extrai o maior numero de repeticoes consecutivas da mesma nota
    tFeatureType = CQBPFeatureType("RepeticoesdePitchFrequente", "extrai o maior numero de repeticoes consecutivas da mesma nota.", 1, false, true);
    pQBP_FeatureTypeList.push_back(tFeatureType);
    //extrai a atitude da musica pelas features(Tempo medio entre as notas / pelo maior numero de notas repetidas)
    tFeatureType = CQBPFeatureType("AtitudedoMusico", "extrai a atitude da musica pelas features(Tempo medio entre as notas / pelo maior numero de notas repetidas).", 1, false, true);
    pQBP_FeatureTypeList.push_back(tFeatureType);
    //extrai o BPM medio da musica
    tFeatureType = CQBPFeatureType("BPMMedio", "extrai o BPM medio da musica", 1, false, true);
    pQBP_FeatureTypeList.push_back(tFeatureType);
    //extrai o numero de notas da musica
    tFeatureType = CQBPFeatureType("NumeroNotas", "extrai o numero de notas da musica", 1, false, true);
    pQBP_FeatureTypeList.push_back(tFeatureType);
    //Tempo Total da Musica
    tFeatureType = CQBPFeatureType("TempoTotal", "extrai o Tempo Total da musica", 1, false, true);
    pQBP_FeatureTypeList.push_back(tFeatureType);
    //Histograma Diatonico
    tFeatureType = CQBPFeatureType("HSTNotaC", "Qtd Notas C do Histograma Diatônico", 1, false, true);
    pQBP_FeatureTypeList.push_back(tFeatureType);
    tFeatureType = CQBPFeatureType("HSTNotaCS", "Qtd Notas CS do Histograma Diatônico", 1, false, true);
    pQBP_FeatureTypeList.push_back(tFeatureType);
    tFeatureType = CQBPFeatureType("HSTNotaD", "Qtd Notas D do Histograma Diatônico", 1, false, true);
    pQBP_FeatureTypeList.push_back(tFeatureType);
    tFeatureType = CQBPFeatureType("HSTNotaDS", "Qtd Notas DS do Histograma Diatônico", 1, false, true);
    pQBP_FeatureTypeList.push_back(tFeatureType);
    tFeatureType = CQBPFeatureType("HSTNotaE", "Qtd Notas E do Histograma Diatônico", 1, false, true);
    pQBP_FeatureTypeList.push_back(tFeatureType);
    tFeatureType = CQBPFeatureType("HSTNotaF", "Qtd Notas F do Histograma Diatônico", 1, false, true);
    pQBP_FeatureTypeList.push_back(tFeatureType);
    tFeatureType = CQBPFeatureType("HSTNotaFS", "Qtd Notas FS do Histograma Diatônico", 1, false, true);
    pQBP_FeatureTypeList.push_back(tFeatureType);
    tFeatureType = CQBPFeatureType("HSTNotaG", "Qtd Notas G do Histograma Diatônico", 1, false, true);
    pQBP_FeatureTypeList.push_back(tFeatureType);
    tFeatureType = CQBPFeatureType("HSTNotaGS", "Qtd Notas GS do Histograma Diatônico", 1, false, true);
    pQBP_FeatureTypeList.push_back(tFeatureType);
    tFeatureType = CQBPFeatureType("HSTNotaA", "Qtd Notas A do Histograma Diatônico", 1, false, true);
    pQBP_FeatureTypeList.push_back(tFeatureType);
    tFeatureType = CQBPFeatureType("HSTNotaAS", "Qtd Notas AS do Histograma Diatônico", 1, false, true);
    pQBP_FeatureTypeList.push_back(tFeatureType);
    tFeatureType = CQBPFeatureType("HSTNotaB", "Qtd Notas B do Histograma Diatônico", 1, false, true);
    pQBP_FeatureTypeList.push_back(tFeatureType);

    return true;
}

bool CQBPDataset::BuildJSymboFeatType()
{
    //Carrega Features JSymbolic
    //pArqJSymbolic.ParseFeatureDefinitions(&pQBP_FeatureTypeList);
    return true;
}

bool CQBPDataset::ClearDataset(int  pQBPTargetList)
{
    switch (pQBPTargetList)
    {
    case QBP_LOAD_TARGET_DATASET:
    {
        pQBPGenreList.clear();//Lista de Musicas do dataset
        //Sempre colocar o reserve zero para economizar memoria(O clear não limpa a reserva de espaço)
        pQBPGenreList.shrink_to_fit();

        pQBPQtdSongs = 0;

        pQBPBiggerSongName.clear();
        //Sempre colocar o reserve zero para economizar memoria(O clear não limpa a reserva de espaço)
        pQBPBiggerSongName.shrink_to_fit();

        pQBPBiggerSongQtdNotes = 0;
        pQBPAvrgNotesBySong = 0;
        pQBPQtdStrips = 0;
    }break;
    case QBP_LOAD_TARGET_TESTSET:
    {
        pQBPTestList.clear();//Lista de Musicas do testset
        //Sempre colocar o reserve zero para economizar memoria(O clear não limpa a reserva de espaço)
        pQBPTestList.shrink_to_fit();
    }break;
    case QBP_LOAD_TARGET_VALISET:
    {
        pQBPValiList.clear();//Lista de Musicas do valiset
        //Sempre colocar o reserve zero para economizar memoria(O clear não limpa a reserva de espaço)
        pQBPValiList.shrink_to_fit();
    }break;
    case QBP_LOAD_TARGET_RANDSET:
    {
        pQBPRandomList.clear();//Lista de Musicas do valiset
        //Sempre colocar o reserve zero para economizar memoria(O clear não limpa a reserva de espaço)
        pQBPRandomList.shrink_to_fit();
    }break;
    case QBP_LOAD_TARGET_FULLSET:
    {
        pQBPFullList.clear();//Lista de Musicas do FullSet
        //Sempre colocar o reserve zero para economizar memoria(O clear não limpa a reserva de espaço)
        pQBPFullList.shrink_to_fit();
    }break;
    }


    return true;
}

bool CQBPDataset::SearchSongByName(string pQBPSongName, CQBPSong &pQBPSong)
{
    for (uint i = 0; i < pQBPGenreList.size(); i++)
    {
        for (uint j = 0; j < pQBPGenreList[i].pQBPSongList.size(); j++)
        {
            if (pQBPGenreList[i].pQBPSongList[j].pQBPSongName == pQBPSongName)
            {
                pQBPSong.pQBPSongName        = pQBPGenreList[i].pQBPSongList[j].pQBPSongName;//Nome da musica(filename)
                pQBPSong.pQBPSongCategory    = pQBPGenreList[i].pQBPSongList[j].pQBPSongCategory;//Categoria da musica
                pQBPSong.pQBPSongScore       = pQBPGenreList[i].pQBPSongList[j].pQBPSongScore;//Score de similaridade da musica
                pQBPSong.pQBPSongBuffer      = pQBPGenreList[i].pQBPSongList[j].pQBPSongBuffer;//Buffer de notas diatonicas da musica completa
                pQBPSong.pQBPSongBufferStrip = pQBPGenreList[i].pQBPSongList[j].pQBPSongBufferStrip;//vetor de buffers menores da musica
                pQBPSong.pQBPMusixBuffer     = pQBPGenreList[i].pQBPSongList[j].pQBPMusixBuffer;
                pQBPSong.pQBPMusixBegin      = pQBPGenreList[i].pQBPSongList[j].pQBPMusixBegin;
                pQBPSong.pQBPMusixMid        = pQBPGenreList[i].pQBPSongList[j].pQBPMusixMid;
                pQBPSong.pQBPMusixEnd        = pQBPGenreList[i].pQBPSongList[j].pQBPMusixEnd;
                pQBPSong.pQBPStripped        = pQBPGenreList[i].pQBPSongList[j].pQBPStripped;//indica que houve strip de buffers
                pQBPSong.pQBPCustomFeatures  = pQBPGenreList[i].pQBPSongList[j].pQBPCustomFeatures;
                pQBPSong.pQBPJSymboFeatures  = pQBPGenreList[i].pQBPSongList[j].pQBPJSymboFeatures;
                pQBPSong.pQBPFeatured        = pQBPGenreList[i].pQBPSongList[j].pQBPFeatured;
                return true;
            }
        }
    }
    return false;
}

bool CQBPDataset::GetLessGenre(int   &pQBPGenreIndex, int      &pQBPQtdSongs)
{
    int tLessQtdSongs  = 1000000;
    int tLessIndex     = 0;

    for (uint i = 0; i < pQBPGenreList.size(); i++)
    {
        for (uint j = 0; j < pQBPGenreList[i].pQBPSongList.size(); j++)
        {
            if ((uint)pQBPGenreList[i].pQBPSongList.size() < (uint)tLessQtdSongs)
            {
                tLessQtdSongs = (int)pQBPGenreList[i].pQBPSongList.size();
                tLessIndex = i;
            }
        }
    }

    pQBPGenreIndex = tLessIndex;
    pQBPQtdSongs   = tLessQtdSongs;

    return true;
}

bool CQBPDataset::GetGreaterGenre(int   &pQBPGenreIndex, int      &pQBPQtdSongs)
{
    int tGreaterQtdSongs = 0;
    int tGreaterIndex = 0;

    for (uint i = 0; i < pQBPGenreList.size(); i++)
    {
        for (uint j = 0; j < pQBPGenreList[i].pQBPSongList.size(); j++)
        {
            if ((uint)pQBPGenreList[i].pQBPSongList.size() > (uint)tGreaterQtdSongs)
            {
                tGreaterQtdSongs = (int)pQBPGenreList[i].pQBPSongList.size();
                tGreaterIndex = i;
            }
        }
    }

    pQBPGenreIndex = tGreaterIndex;
    pQBPQtdSongs = tGreaterQtdSongs;

    return true;
}

bool CQBPDataset::CheckTestSet()
{
    for (uint i = 0; i < pQBPTestList.size(); i++)
    {
        //busca a musica na base principal e pega features
        SearchSongByName(pQBPTestList[i].pQBPSongName, pQBPTestList[i]);
    }

    BuildFeaturesDts(QBP_LOAD_TARGET_TESTSET);
    BuildStrippedDts(QBP_LOAD_TARGET_TESTSET);

    return true;
}

bool CQBPDataset::CreateSet(int pQBPTargetList, int pQBPFormType, int  pQBPBufferSize)
{
    int tLessQtdSongs  ,tGreaterQtdSongs;
    int tLessGenreIndex,tGreaterGenreIndex;

    int tCopyPct;

    //Neste form Type 10% da base principal do menor genero vai para o test set e 15% para o Valiset.
    if (pQBPFormType == QBP_FORM_TYPE_LESS_1015F)
    {
        GetLessGenre(tLessGenreIndex, tLessQtdSongs);
        //Calcula 10% do Set
        tCopyPct = (int)((tLessQtdSongs * 10) / 100);
        //Copia musicas para o Set
        CopySet(QBP_LOAD_TARGET_TESTSET, tCopyPct , pQBPBufferSize);
        //Calcula 15% do Set
        tCopyPct = (int)((tLessQtdSongs * 15) / 100);
        //Copia musicas para o Set
        CopySet(QBP_LOAD_TARGET_VALISET, tCopyPct , pQBPBufferSize);
        //Calcula 10% do Set
        tCopyPct = (int)((tLessQtdSongs * 10) / 100);
        //Copia musicas para o Set
        CopySet(QBP_LOAD_TARGET_RANDSET, tCopyPct , pQBPBufferSize);
    }

    //Caso sejam as outras formulas vemos o target list especifico
    switch (pQBPTargetList)
    {
    case QBP_LOAD_TARGET_TESTSET:
    {
        switch (pQBPFormType)
        {
        case QBP_FORM_TYPE_LESS_GENRE:
        {
            //Copia o total de musicas do menor genero para conterem numeros iguais de musicas
            GetLessGenre(tLessGenreIndex, tLessQtdSongs);
            CopySet(QBP_LOAD_TARGET_TESTSET, tLessQtdSongs , pQBPBufferSize);
        }break;
        case QBP_FORM_TYPE_PERC_10:
        {
            GetGreaterGenre(tGreaterGenreIndex , tGreaterQtdSongs);
            //Calcula 10% do maior set
            tCopyPct = (int)((tGreaterQtdSongs * 10) / 100);
            //Copia musicas para o Set
            CopySet(QBP_LOAD_TARGET_TESTSET, tCopyPct , pQBPBufferSize);
        }break;
        case QBP_FORM_TYPE_PERC_15:
        {
            GetGreaterGenre(tGreaterGenreIndex, tGreaterQtdSongs);
            //Calcula 10% do maior set
            tCopyPct = (int)((tGreaterQtdSongs * 15) / 100);
            //Copia musicas para o Set
            CopySet(QBP_LOAD_TARGET_TESTSET, tCopyPct , pQBPBufferSize);
            //mistura os registros de generos
            //ShuffleSet(QBP_LOAD_TARGET_TESTSET);
        }break;
        }
    }break;
    case QBP_LOAD_TARGET_VALISET:
    {
        switch (pQBPFormType)
        {
        case QBP_FORM_TYPE_LESS_GENRE:
        {
            //Copia o total de musicas do menor genero para conterem numeros iguais de musicas
            GetLessGenre(tLessGenreIndex, tLessQtdSongs);
            CopySet(QBP_LOAD_TARGET_VALISET, tLessQtdSongs , pQBPBufferSize);
        }break;
        case QBP_FORM_TYPE_PERC_10:
        {
            GetGreaterGenre(tGreaterGenreIndex, tGreaterQtdSongs);
            //Calcula 10% do maior set
            tCopyPct = (int)((tGreaterQtdSongs * 10) / 100);
            //Copia musicas para o Set
            CopySet(QBP_LOAD_TARGET_VALISET, tCopyPct , pQBPBufferSize);
        }break;
        case QBP_FORM_TYPE_PERC_15:
        {
            GetGreaterGenre(tGreaterGenreIndex, tGreaterQtdSongs);
            //Calcula 10% do maior set
            tCopyPct = (int)((tGreaterQtdSongs * 15) / 100);
            //Copia musicas para o Set
            CopySet(QBP_LOAD_TARGET_VALISET, tCopyPct , pQBPBufferSize);
        }break;
        }
    }break;
    case QBP_LOAD_TARGET_FULLSET:
    {
        //Copia musicas para o Set
        CopySet(QBP_LOAD_TARGET_FULLSET, pQBPQtdSongs , pQBPBufferSize);
    }break;
    case QBP_LOAD_TARGET_RANDSET:
    {
        switch (pQBPFormType)
        {
        case QBP_FORM_TYPE_LESS_GENRE:
        {
            //Copia o total de musicas do menor genero para conterem numeros iguais de musicas
            GetLessGenre(tLessGenreIndex, tLessQtdSongs);
            CopySetRandom(QBP_LOAD_TARGET_RANDSET, tLessQtdSongs,pQBPBufferSize);
        }break;
        case QBP_FORM_TYPE_PERC_10:
        {
            GetGreaterGenre(tGreaterGenreIndex, tGreaterQtdSongs);
            //Calcula 10% do maior set
            tCopyPct = (int)((tGreaterQtdSongs * 10) / 100);
            //Copia musicas para o Set
            CopySetRandom(QBP_LOAD_TARGET_RANDSET, tCopyPct,pQBPBufferSize);
        }break;
        case QBP_FORM_TYPE_PERC_15:
        {
            GetGreaterGenre(tGreaterGenreIndex, tGreaterQtdSongs);
            //Calcula 10% do maior set
            tCopyPct = (int)((tGreaterQtdSongs * 15) / 100);
            //Copia musicas para o Set
            CopySetRandom(QBP_LOAD_TARGET_RANDSET, tCopyPct,pQBPBufferSize);
        }break;
        }
    }break;
    }

    return true;
}

bool CQBPDataset::ShuffleSet(int pQBPTargetList)
{
    //Se o Target List for o principal não pode
    if (pQBPTargetList == QBP_LOAD_TARGET_DATASET)
    {
        return false;
    }

    random_device rd;
    mt19937 g(rd());

    switch (pQBPTargetList)
    {
    case QBP_LOAD_TARGET_TESTSET:
    {
        shuffle(pQBPTestList.begin(), pQBPTestList.end(), g);
    }break;
    case QBP_LOAD_TARGET_VALISET:
    {
        shuffle(pQBPValiList.begin(), pQBPValiList.end(), g);
    }break;
    case QBP_LOAD_TARGET_RANDSET:
    {
        shuffle(pQBPRandomList.begin(), pQBPRandomList.end(), g);
    }break;
    }
    return true;
}

bool CQBPDataset::CopySet(int pQBPTargetList, int pQBPQtdSongs, int pQBPBufferSize)
{
    switch (pQBPTargetList)
    {
    case QBP_LOAD_TARGET_TESTSET:
    {
        pQBPTestList.clear();
        //Sempre colocar o reserve zero para economizar memoria(O clear não limpa a reserva de espaço)
        pQBPTestList.shrink_to_fit();

        for (uint i = 0; i < pQBPGenreList.size(); i++)
        {
            for (uint j = 0; j < pQBPGenreList[i].pQBPSongList.size(); j++)
            {
                if (j < (uint)pQBPQtdSongs)
                {
                    CQBPSong tSong = pQBPGenreList[i].pQBPSongList[j];

                    //Remove tudo a partir do tamanho do buffer
                    tSong.RemFromPos(pQBPBufferSize);

                    pQBPTestList.push_back(tSong);

                }
            }
        }
    }break;
    case QBP_LOAD_TARGET_VALISET:
    {
        pQBPValiList.clear();
        //Sempre colocar o reserve zero para economizar memoria(O clear não limpa a reserva de espaço)
        pQBPValiList.shrink_to_fit();

        for (uint i = 0; i < pQBPGenreList.size(); i++)
        {
            for (uint j = 0; j < pQBPGenreList[i].pQBPSongList.size(); j++)
            {
                if (j < (uint)pQBPQtdSongs)
                {
                    CQBPSong tSong = pQBPGenreList[i].pQBPSongList[j];

                    //Remove tudo a partir do tamanho do buffer
                    tSong.RemFromPos(pQBPBufferSize);


                    pQBPValiList.push_back(tSong);
                }
            }
        }
    }break;
    case QBP_LOAD_TARGET_FULLSET:
    {
        pQBPFullList.clear();
        //Sempre colocar o reserve zero para economizar memoria(O clear não limpa a reserva de espaço)
        pQBPFullList.shrink_to_fit();

        for (uint i = 0; i < pQBPGenreList.size(); i++)
        {
            for (uint j = 0; j < pQBPGenreList[i].pQBPSongList.size(); j++)
            {
                if (j < (uint)pQBPQtdSongs)
                {
                    CQBPSong tSong = pQBPGenreList[i].pQBPSongList[j];

                    //Remove tudo a partir do tamanho do buffer
                    tSong.RemFromPos(pQBPBufferSize);

                    pQBPFullList.push_back(tSong);
                }
            }
        }
    }break;
    case QBP_LOAD_TARGET_RANDSET:
    {
        pQBPRandomList.clear();
        //Sempre colocar o reserve zero para economizar memoria(O clear não limpa a reserva de espaço)
        pQBPRandomList.shrink_to_fit();

        for (uint i = 0; i < pQBPGenreList.size(); i++)
        {
            for (uint j = 0; j < pQBPGenreList[i].pQBPSongList.size(); j++)
            {
                if (j < (uint)pQBPQtdSongs)
                {
                    CQBPSong tSong = pQBPGenreList[i].pQBPSongList[j];

                    //Remove tudo a partir do tamanho do buffer
                    tSong.RemFromPos(pQBPBufferSize);


                    pQBPRandomList.push_back(tSong);
                }
            }
        }
    }break;
    }
    return true;
}

bool CQBPDataset::CopySetRandom(int pQBPTargetList, int pQBPQtdSongs, int pQBPBufferSize)
{
    //Se o Target List for o principal não pode
    if (pQBPTargetList == QBP_LOAD_TARGET_DATASET)
    {
        return false;
    }

    switch (pQBPTargetList)
    {
    case QBP_LOAD_TARGET_TESTSET:
    {
        pQBPTestList.clear();
        //Sempre colocar o reserve zero para economizar memoria(O clear não limpa a reserva de espaço)
        pQBPTestList.shrink_to_fit();

        int cont=0;
        for (uint i = 0; i < pQBPGenreList.size(); i++)
        {
            for (uint j = 0; j < pQBPGenreList[i].pQBPSongList.size(); j++)
            {
                if (j < (uint)pQBPQtdSongs)
                {
                    CQBPSong tSong(pQBPGenreList[i].pQBPSongList[j]);

                    tSong.pQBPOriginalName     = tSong.pQBPSongName;
                    tSong.pQBPSongName         = QString("Random %1").arg(cont).toStdString();
                    tSong.pQBPOriginalCategory = tSong.pQBPSongCategory;
                    cont++;

                    DiatonicNote tRandomNote;
                    stQBPMusicBuffer tRandomNoteBufferItem;

                    //Pega nota randomica na escala de C
                    tRandomNote = GetRandomNote(5);

                    //Repassa valores da nota no item de buffer
                    tRandomNoteBufferItem.sQBP_Note             = tRandomNote.NoteName;
                    tRandomNoteBufferItem.iQBP_Pitch            = tRandomNote.NotePith;
                    tRandomNoteBufferItem.iQBP_Contour          = 0;
                    tRandomNoteBufferItem.iQBP_Octave           = tRandomNote.Octave;
                    tRandomNoteBufferItem.bQBP_IsBemol          = tRandomNote.bIsbemol;
                    tRandomNoteBufferItem.bQBP_IsSharp          = tRandomNote.bIssharp;
                    tRandomNoteBufferItem.dQBP_Duration         = 0;
                    tRandomNoteBufferItem.dQBP_Frequency        = tRandomNote.Frequency;
                    tRandomNoteBufferItem.iQBP_MidiShortMessage = tRandomNote.MidiShortMessage;

                    //Adiciona nota randomica a cada 3 notas do buffer
                    tSong.AddNote(tRandomNoteBufferItem,3);

                    //Remove tudo a partir do tamanho do buffer
                    tSong.RemFromPos(pQBPBufferSize);

                    pQBPTestList.push_back(tSong);
                }
            }
        }
    }break;
    case QBP_LOAD_TARGET_VALISET:
    {
        pQBPValiList.clear();
        //Sempre colocar o reserve zero para economizar memoria(O clear não limpa a reserva de espaço)
        pQBPValiList.shrink_to_fit();

        int cont=0;
        for (uint i = 0; i < pQBPGenreList.size(); i++)
        {
            for (uint j = 0; j < pQBPGenreList[i].pQBPSongList.size(); j++)
            {
                if (j < (uint)pQBPQtdSongs)
                {
                    CQBPSong tSong(pQBPGenreList[i].pQBPSongList[j]);

                    tSong.pQBPOriginalName     = tSong.pQBPSongName;
                    tSong.pQBPSongName         = QString("Random %1").arg(cont).toStdString();
                    tSong.pQBPOriginalCategory = tSong.pQBPSongCategory;
                    cont++;

                    DiatonicNote tRandomNote;
                    stQBPMusicBuffer tRandomNoteBufferItem;

                    //Pega nota randomica na escala de C
                    tRandomNote = GetRandomNote(5);

                    //Repassa valores da nota no item de buffer
                    tRandomNoteBufferItem.sQBP_Note             = tRandomNote.NoteName;
                    tRandomNoteBufferItem.iQBP_Pitch            = tRandomNote.NotePith;
                    tRandomNoteBufferItem.iQBP_Contour          = 0;
                    tRandomNoteBufferItem.iQBP_Octave           = tRandomNote.Octave;
                    tRandomNoteBufferItem.bQBP_IsBemol          = tRandomNote.bIsbemol;
                    tRandomNoteBufferItem.bQBP_IsSharp          = tRandomNote.bIssharp;
                    tRandomNoteBufferItem.dQBP_Duration         = 0;
                    tRandomNoteBufferItem.dQBP_Frequency        = tRandomNote.Frequency;
                    tRandomNoteBufferItem.iQBP_MidiShortMessage = tRandomNote.MidiShortMessage;

                    //Adiciona nota randomica a cada 3 notas do buffer
                    tSong.AddNote(tRandomNoteBufferItem,3);

                    //Remove tudo a partir do tamanho do buffer
                    tSong.RemFromPos(pQBPBufferSize);


                    pQBPValiList.push_back(tSong);
                }
            }
        }
    }break;
    case QBP_LOAD_TARGET_RANDSET:
    {
        pQBPRandomList.clear();
        //Sempre colocar o reserve zero para economizar memoria(O clear não limpa a reserva de espaço)
        pQBPRandomList.shrink_to_fit();

        int cont=0;
        for (uint i = 0; i < pQBPGenreList.size(); i++)
        {
            for (uint j = 0; j < pQBPGenreList[i].pQBPSongList.size(); j++)
            {
                if (j < (uint)pQBPQtdSongs)
                {
                    CQBPSong tSong(pQBPGenreList[i].pQBPSongList[j]);

                    tSong.pQBPOriginalName     = tSong.pQBPSongName;
                    tSong.pQBPSongName         = QString("Random %1").arg(cont).toStdString();
                    tSong.pQBPOriginalCategory = tSong.pQBPSongCategory;
                    cont++;

                    DiatonicNote tRandomNote;
                    stQBPMusicBuffer tRandomNoteBufferItem;

                    //Pega nota randomica na escala de C
                    tRandomNote = GetRandomNote(5);

                    //Repassa valores da nota no item de buffer
                    tRandomNoteBufferItem.sQBP_Note             = tRandomNote.NoteName;
                    tRandomNoteBufferItem.iQBP_Pitch            = tRandomNote.NotePith;
                    tRandomNoteBufferItem.iQBP_Contour          = 0;
                    tRandomNoteBufferItem.iQBP_Octave           = tRandomNote.Octave;
                    tRandomNoteBufferItem.bQBP_IsBemol          = tRandomNote.bIsbemol;
                    tRandomNoteBufferItem.bQBP_IsSharp          = tRandomNote.bIssharp;
                    tRandomNoteBufferItem.dQBP_Duration         = 0;
                    tRandomNoteBufferItem.dQBP_Frequency        = tRandomNote.Frequency;
                    tRandomNoteBufferItem.iQBP_MidiShortMessage = tRandomNote.MidiShortMessage;

                    //Adiciona nota randomica a cada 3 notas do buffer
                    tSong.AddNote(tRandomNoteBufferItem,3);

                    //Remove tudo a partir do tamanho do buffer
                    tSong.RemFromPos(pQBPBufferSize);


                    pQBPRandomList.push_back(tSong);
                }
            }
        }
    }break;
    }
    return true;
}

bool CQBPDataset::ExtractSet(int    pQBPTargetList ,vector<CQBPSong *> &pQBPTarget)
{
    //Se o Target List for o principal não pode
    if (pQBPTargetList == QBP_LOAD_TARGET_DATASET)
    {
        return false;
    }

    if(pQBPTarget.size()>0)
    {
        pQBPTarget.clear();
        //Sempre colocar o reserve zero para economizar memoria(O clear não limpa a reserva de espaço)
        pQBPTarget.shrink_to_fit();
    }

    switch (pQBPTargetList)
    {
    case QBP_LOAD_TARGET_TESTSET:
    {
        for (uint j = 0; j < pQBPTestList.size(); j++)
        {
            if (j < (uint)pQBPQtdSongs)
            {
                CQBPSong *tSong = new CQBPSong(pQBPTestList[j]);
                pQBPTarget.push_back(tSong);
            }
         }
    }break;
    case QBP_LOAD_TARGET_VALISET:
    {
        for (uint j = 0; j < pQBPValiList.size(); j++)
        {
            if (j < (uint)pQBPQtdSongs)
            {
                CQBPSong *tSong = new CQBPSong(pQBPValiList[j]);
                pQBPTarget.push_back(tSong);
            }
         }
    }break;
    case QBP_LOAD_TARGET_RANDSET:
    {
        for (uint j = 0; j < pQBPRandomList.size(); j++)
        {
            if (j < (uint)pQBPQtdSongs)
            {
                CQBPSong *tSong = new CQBPSong(pQBPRandomList[j]);
                pQBPTarget.push_back(tSong);
            }
         }
    }break;
    }
    return true;
}

bool CQBPDataset::ExtractSetRandom(int    pQBPTargetList ,vector<CQBPSong *> &pQBPTarget)
{
    //Se o Target List for o principal não pode
    if (pQBPTargetList == QBP_LOAD_TARGET_DATASET)
    {
        return false;
    }

    if(pQBPTarget.size()>0)
    {
        pQBPTarget.clear();
        //Sempre colocar o reserve zero para economizar memoria(O clear não limpa a reserva de espaço)
        pQBPTarget.shrink_to_fit();
    }

    switch (pQBPTargetList)
    {
    case QBP_LOAD_TARGET_TESTSET:
    {
        for (uint j = 0; j < pQBPTestList.size(); j++)
        {
            if (j < (uint)pQBPQtdSongs)
            {
                CQBPSong *tSong = new CQBPSong(pQBPTestList[j]);

                DiatonicNote tRandomNote;
                stQBPMusicBuffer tRandomNoteBufferItem;

                //Pega nota randomica na escala de C
                tRandomNote = GetRandomNote(5);

                //Repassa valores da nota no item de buffer
                tRandomNoteBufferItem.sQBP_Note             = tRandomNote.NoteName;
                tRandomNoteBufferItem.iQBP_Pitch            = tRandomNote.NotePith;
                tRandomNoteBufferItem.iQBP_Contour          = 0;
                tRandomNoteBufferItem.iQBP_Octave           = tRandomNote.Octave;
                tRandomNoteBufferItem.bQBP_IsBemol          = tRandomNote.bIsbemol;
                tRandomNoteBufferItem.bQBP_IsSharp          = tRandomNote.bIssharp;
                tRandomNoteBufferItem.dQBP_Duration         = 0;
                tRandomNoteBufferItem.dQBP_Frequency        = tRandomNote.Frequency;
                tRandomNoteBufferItem.iQBP_MidiShortMessage = tRandomNote.MidiShortMessage;

                //Adiciona nota randomica a cada 3 notas do buffer
                tSong->AddNote(tRandomNoteBufferItem,3);

                pQBPTarget.push_back(tSong);
            }
         }
    }break;
    case QBP_LOAD_TARGET_VALISET:
    {
        for (uint j = 0; j < pQBPValiList.size(); j++)
        {
            if (j < (uint)pQBPQtdSongs)
            {
                CQBPSong *tSong = new CQBPSong(pQBPValiList[j]);

                DiatonicNote tRandomNote;
                stQBPMusicBuffer tRandomNoteBufferItem;

                //Pega nota randomica na escala de C
                tRandomNote = GetRandomNote(5);

                //Repassa valores da nota no item de buffer
                tRandomNoteBufferItem.sQBP_Note             = tRandomNote.NoteName;
                tRandomNoteBufferItem.iQBP_Pitch            = tRandomNote.NotePith;
                tRandomNoteBufferItem.iQBP_Contour          = 0;
                tRandomNoteBufferItem.iQBP_Octave           = tRandomNote.Octave;
                tRandomNoteBufferItem.bQBP_IsBemol          = tRandomNote.bIsbemol;
                tRandomNoteBufferItem.bQBP_IsSharp          = tRandomNote.bIssharp;
                tRandomNoteBufferItem.dQBP_Duration         = 0;
                tRandomNoteBufferItem.dQBP_Frequency        = tRandomNote.Frequency;
                tRandomNoteBufferItem.iQBP_MidiShortMessage = tRandomNote.MidiShortMessage;

                //Adiciona nota randomica a cada 3 notas do buffer
                tSong->AddNote(tRandomNoteBufferItem,3);

                pQBPTarget.push_back(tSong);
            }
         }
    }break;
    case QBP_LOAD_TARGET_RANDSET:
    {
        for (uint j = 0; j < pQBPRandomList.size(); j++)
        {
            if (j < (uint)pQBPQtdSongs)
            {
                CQBPSong *tSong = new CQBPSong(pQBPRandomList[j]);

                DiatonicNote tRandomNote;
                stQBPMusicBuffer tRandomNoteBufferItem;

                //Pega nota randomica na escala de C
                tRandomNote = GetRandomNote(5);

                //Repassa valores da nota no item de buffer
                tRandomNoteBufferItem.sQBP_Note             = tRandomNote.NoteName;
                tRandomNoteBufferItem.iQBP_Pitch            = tRandomNote.NotePith;
                tRandomNoteBufferItem.iQBP_Contour          = 0;
                tRandomNoteBufferItem.iQBP_Octave           = tRandomNote.Octave;
                tRandomNoteBufferItem.bQBP_IsBemol          = tRandomNote.bIsbemol;
                tRandomNoteBufferItem.bQBP_IsSharp          = tRandomNote.bIssharp;
                tRandomNoteBufferItem.dQBP_Duration         = 0;
                tRandomNoteBufferItem.dQBP_Frequency        = tRandomNote.Frequency;
                tRandomNoteBufferItem.iQBP_MidiShortMessage = tRandomNote.MidiShortMessage;

                //Adiciona nota randomica a cada 3 notas do buffer
                tSong->AddNote(tRandomNoteBufferItem,3);

                pQBPTarget.push_back(tSong);
            }
         }
    }break;
    }
    return true;
}
