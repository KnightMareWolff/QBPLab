#include "QBP_JSymbolicFile.h"

bool invalidJsymChar(char c)
{
    return !(c >= 0 && c <128);
}

bool isSpaceJsymChar(char c)
{
    return (c == 32);
}

bool isPunctJsymChar(char c)
{
    return (c >= 33 && c <= 47);
}

CQBPJSymbolicFile::CQBPJSymbolicFile()
{

}


CQBPJSymbolicFile::~CQBPJSymbolicFile()
{
}

bool CQBPJSymbolicFile::LoadJSymbolicDefinitions()
{
    QString tNome;
    QString tDescricao;
    QString tDimensoes;
    QString tSequencial;

    string fNome;

    CQBPLogQueue::Push(QString("Carregando Definições JSymbolic: \n"));

    QFile file("jsymbolic/FeatureDefinitions.xml");

    //Carrega as Features JSymbolic atraves do arquivo
    file.open(QIODevice::ReadOnly);

    QTextStream      out(&file);
    QString stream = out.readAll();


    pQBP_FeaturesDef = new QXmlStreamReader(stream);


    while (!pQBP_FeaturesDef->atEnd())
    {
       if(pQBP_FeaturesDef->readNextStartElement())
       {
           if(pQBP_FeaturesDef->name() == "feature")
           {
               pQBP_FeaturesDef->readNextStartElement();
               if(pQBP_FeaturesDef->name() == "name")
               {
                   tNome= pQBP_FeaturesDef->readElementText();
               }

               pQBP_FeaturesDef->readNextStartElement();
               if(pQBP_FeaturesDef->name() == "description")
               {
                   tDescricao= pQBP_FeaturesDef->readElementText();
               }

               pQBP_FeaturesDef->readNextStartElement();
               if(pQBP_FeaturesDef->name() == "is_sequential")
               {
                   tSequencial = pQBP_FeaturesDef->readElementText();
               }

               pQBP_FeaturesDef->readNextStartElement();
               if(pQBP_FeaturesDef->name() == "parallel_dimensions")
               {
                   tDimensoes= pQBP_FeaturesDef->readElementText();
               }

               fNome = tNome.toStdString();
               fNome.erase(remove_if(fNome.begin(), fNome.end(), invalidJsymChar), fNome.end());
               fNome.erase(remove_if(fNome.begin(), fNome.end(), isSpaceJsymChar), fNome.end());
               fNome.erase(remove_if(fNome.begin(), fNome.end(), isPunctJsymChar), fNome.end());

               tNome = fNome.c_str();

               vFeatureDefifitions.push_back(CQBPJSymboFeatureDefinition(tNome, tDescricao,tDimensoes,tSequencial));

               //CQBPLogQueue::Push(QString("Definição Carregada: "));
               //CQBPLogQueue::Push(tNome);
               //CQBPLogQueue::Push(QString("\n"));
           }
       }
    }

    CQBPLogQueue::Push(QString("Numero de Definições Carregadas: %1 \n").arg(vFeatureDefifitions.size()));

    return true;
}
bool CQBPJSymbolicFile::LoadJSymbolicDatabase()
{
    string tAbsoluteFileName;
    string tFileName;
    string tSongName;
    string tFeatureName;//nome temporario para identificação do dataset
    string tName;//nome temporario para identificação do dataset

    QFile   *file;

    QString tDatasetID;
    QString sFeatureName;
    QString sFeatureValue;

    int    tFeatureType;
    int    tFeatureDimensions;

    int    npos = -1;

    CQBPLogQueue::Push(QString("Carregando Database JSymbolic: \n"));


    QDirIterator it("jsymbolic/", QDirIterator::Subdirectories);
    while (it.hasNext())
    {
        tAbsoluteFileName = it.next().toStdString();

        //Verifica se não é o arquivo de definições de features
        std::size_t found = tAbsoluteFileName.find("FeatureValues");
        if (found != std::string::npos)
        {
            file = new QFile(tAbsoluteFileName.c_str());

            //Carrega as Features JSymbolic atraves do arquivo
            file->open(QIODevice::ReadOnly);
            CQBPLogQueue::Push(QString("Abriu arquivo \n"));

            QTextStream      out(file);
            QString stream = out.readAll();

            pQBP_FeaturesDoc = new QXmlStreamReader(stream);

            while (!pQBP_FeaturesDoc->atEnd())
            {
               if(pQBP_FeaturesDoc->readNextStartElement())
               {
                  if(pQBP_FeaturesDoc->name() == "data_set_id")
                  {
                      tDatasetID = pQBP_FeaturesDoc->readElementText();
                      //Pega o Valor do dataset Id (Nome do path + nome da musica + extensão "mid")
                      tName      = tDatasetID.toStdString();

                      //Localiza e apaga o primeiro folder do path
                      int nfold;
                      nfold = (int)tName.find("\\");
                      tName.erase(0, tName.substr(0, nfold + 1).size());

                      //Enquanto ainda tiverem folders vai removendo...
                      while (nfold != -1)
                      {
                          nfold = (int)tName.find("\\");
                          tName.erase(0, tName.substr(0, nfold + 1).size());
                      }

                      //remove o .mid , espaços e pontuação do nome
                      npos = (int)tName.find(".mid");
                      if (npos != -1)
                      {
                          tName.erase(npos, 4);
                      }
                      tName.erase(remove_if(tName.begin(), tName.end(), invalidJsymChar), tName.end());
                      tName.erase(remove_if(tName.begin(), tName.end(), isSpaceJsymChar), tName.end());
                      tName.erase(remove_if(tName.begin(), tName.end(), isPunctJsymChar), tName.end());

                      pQBP_FeaturesDoc->readNextStartElement();

                      bool bFimFeatures=false;

                      while(!bFimFeatures)
                      {
                          if(pQBP_FeaturesDoc->name() == "data_set")
                          {
                              bFimFeatures = true;
                              continue;
                          }

                          pQBP_FeaturesDoc->readNextStartElement();

                          if(pQBP_FeaturesDoc->name() == "name")
                          {
                              sFeatureName = pQBP_FeaturesDoc->readElementText();

                              tFeatureName = sFeatureName.toStdString();

                              tFeatureName.erase(remove_if(tFeatureName.begin(), tFeatureName.end(), invalidJsymChar), tFeatureName.end());
                              tFeatureName.erase(remove_if(tFeatureName.begin(), tFeatureName.end(), isSpaceJsymChar), tFeatureName.end());
                              tFeatureName.erase(remove_if(tFeatureName.begin(), tFeatureName.end(), isPunctJsymChar), tFeatureName.end());

                              sFeatureName = tFeatureName.c_str();
                          }

                          pQBP_FeaturesDoc->readNextStartElement();
                          if(pQBP_FeaturesDoc->name() == "v")
                          {
                             sFeatureValue = pQBP_FeaturesDoc->readElementText();

                             //Checa se a feature e um vetor, se for nao inclui ainda(Histograma)
                             GetFeatureTypeId(sFeatureName,tFeatureType);

                             //Pega o numero de dimensoes da feature
                              tFeatureDimensions= vFeatureDefifitions[tFeatureType].sDimensions.toInt();

                              //O sistema esta aceitando apenas features unicas por enquanto
                              if(tFeatureDimensions>1)
                              {
                                  //caso sejam multidimensionais, com o XML do Qt temos que
                                  //ir lendo valor por valor ate o proximo tag...
                                  for(int i=0;i<tFeatureDimensions;i++)
                                  {
                                     pQBP_FeaturesDoc->readNextStartElement();
                                     sFeatureValue = pQBP_FeaturesDoc->readElementText();
                                  }
                                  pQBP_FeaturesDoc->readNextStartElement();
                              }
                              else
                              {
                                  vFeatureDatasets.push_back(CQBPJSymboFeature(tFeatureType,false,sFeatureName,sFeatureValue));

                                  //Sleep(200);
                                  //CQBPLogQueue::Push(QString("Dataset Carregado: "));
                                  //CQBPLogQueue::Push(sFeatureName);
                                  //CQBPLogQueue::Push(QString("\n"));

                                  pQBP_FeaturesDoc->readNextStartElement();
                                  pQBP_FeaturesDoc->readNextStartElement();
                              }
                          }
                      }
                  }
               }
            }
            file->close();
        }
    }

    CQBPLogQueue::Push(QString("Numero de Datasets Carregados: %1 \n").arg(vFeatureDatasets.size()));

    return true;
}


bool CQBPJSymbolicFile::ParseFeatures(vector<CQBPGenre>       &pQBP_GenreList,
                                      vector<CQBPFeatureType> &pQBPFeatureTypeList)
{
    string tName;//nome temporario para identificação do dataset
    string tSongName;
    string tFeatureName;//nome temporario para identificação do dataset
    string tAbsoluteFileName;
    string tFileName;


    QFile   *file;

    QString tDatasetID;
    QString sFeatureName;
    QString sFeatureValue;

    int    tFeatureType;
    int    tFeatureDimensions;

    int    npos = -1;

    for(uint i=0 ; i< pQBP_GenreList.size();i++)
    {
        CQBPLogQueue::Push(QString("Construindo Caracteristicas JSymbolic Genero: "));
        CQBPLogQueue::Push(QString(pQBP_GenreList[i].pQBPGenreName.c_str()));
        CQBPLogQueue::Push(QString("\n"));

        for(uint j=0 ; j < pQBP_GenreList[i].pQBPSongList.size(); j++)
        {
            CQBPLogQueue::Push(QString("Musica: "));
            CQBPLogQueue::Push(QString(pQBP_GenreList[i].pQBPSongList[j].pQBPSongName.c_str()));
            CQBPLogQueue::Push(QString("\n"));

            bool bOk=false;

            //tFileName = GetMusicFeatureFile(QString(pQBP_GenreList[i].pQBPSongList[j].pQBPSongName.c_str()),bOk).toStdString();
            if(!bOk)
            {
                CQBPLogQueue::Push(QString("Não encontrado arquivo com esta musica \n"));
                continue;
            }

            file = new QFile(tFileName.c_str());

            //Carrega as Features JSymbolic atraves do arquivo
            file->open(QIODevice::ReadOnly);

            QTextStream      out(file);
            QString stream = out.readAll();

            pQBP_FeaturesDoc = new QXmlStreamReader(stream);

            while (!pQBP_FeaturesDoc->atEnd())
            {
                if(pQBP_FeaturesDoc->readNextStartElement())
                {
                    if(pQBP_FeaturesDoc->name() == "data_set_id")
                    {
                        tDatasetID = pQBP_FeaturesDoc->readElementText();
                        //Pega o Valor do dataset Id (Nome do path + nome da musica + extensão "mid")
                        tName      = tDatasetID.toStdString();
                        tSongName  = pQBP_GenreList[i].pQBPSongList[j].pQBPSongName.c_str();

                        //Localiza e apaga o primeiro folder do path
                        int nfold;
                        nfold = (int)tName.find("\\");
                        tName.erase(0, tName.substr(0, nfold + 1).size());

                        //Enquanto ainda tiverem folders vai removendo...
                        while (nfold != -1)
                        {
                            nfold = (int)tName.find("\\");
                            tName.erase(0, tName.substr(0, nfold + 1).size());
                        }

                        //remove o .mid , espaços e pontuação do nome
                        npos = (int)tName.find(".mid");
                        if (npos != -1)
                        {
                            tName.erase(npos, 4);
                        }
                        tName.erase(remove_if(tName.begin(), tName.end(), invalidJsymChar), tName.end());
                        tName.erase(remove_if(tName.begin(), tName.end(), isSpaceJsymChar), tName.end());
                        tName.erase(remove_if(tName.begin(), tName.end(), isPunctJsymChar), tName.end());

                        //remove o .mid , espaços e pontuação do nome
                        npos = (int)tSongName.find(".mid");
                        if (npos != -1)
                        {
                            tSongName.erase(npos, 4);
                        }
                        tSongName.erase(remove_if(tSongName.begin(), tSongName.end(), invalidJsymChar), tSongName.end());
                        tSongName.erase(remove_if(tSongName.begin(), tSongName.end(), isSpaceJsymChar), tSongName.end());
                        tSongName.erase(remove_if(tSongName.begin(), tSongName.end(), isPunctJsymChar), tSongName.end());

                        //se não for a musica certa continua lendo
                        if(tName != tSongName)continue;

                        bool bFimFeatures=false;

                        pQBP_FeaturesDoc->readNextStartElement();

                        while(!bFimFeatures)
                        {
                            if(pQBP_FeaturesDoc->name() == "data_set")
                            {
                                bFimFeatures = true;
                                continue;
                            }

                            pQBP_FeaturesDoc->readNextStartElement();

                            if(pQBP_FeaturesDoc->name() == "name")
                            {
                                sFeatureName = pQBP_FeaturesDoc->readElementText();

                                tFeatureName = sFeatureName.toStdString();

                                tFeatureName.erase(remove_if(tFeatureName.begin(), tFeatureName.end(), invalidJsymChar), tFeatureName.end());
                                tFeatureName.erase(remove_if(tFeatureName.begin(), tFeatureName.end(), isSpaceJsymChar), tFeatureName.end());
                                tFeatureName.erase(remove_if(tFeatureName.begin(), tFeatureName.end(), isPunctJsymChar), tFeatureName.end());
                            }

                            pQBP_FeaturesDoc->readNextStartElement();
                            if(pQBP_FeaturesDoc->name() == "v")
                            {
                               sFeatureValue = pQBP_FeaturesDoc->readElementText();

                               //Checa se a feature e um vetor, se for nao inclui ainda(Histograma)
                               //GetParseFTypeIds(tFeatureName,pQBPFeatureTypeList,tFeatureType);
                                //Pega o numero de dimensoes da feature
                                pQBPFeatureTypeList[tFeatureType].GetDimensions(tFeatureDimensions);
                                //O sistema esta aceitando apenas features unicas por enquanto
                                if(tFeatureDimensions>1)
                                {
                                    //caso sejam multidimensionais, com o XML do Qt temos que
                                    //ir lendo valor por valor ate o proximo tag...
                                    for(int i=0;i<tFeatureDimensions;i++)
                                    {
                                       pQBP_FeaturesDoc->readNextStartElement();
                                       sFeatureValue = pQBP_FeaturesDoc->readElementText();
                                    }
                                    pQBP_FeaturesDoc->readNextStartElement();
                                }
                                else
                                {
                                    //caso seja unica repassa valor e continua
                                    double tFeatureVal = atof(sFeatureValue.toStdString().c_str());
                                    //Caso exista um Type desta Feature , Extraimos o ID e continuamos...
                                    pQBP_GenreList[i].pQBPSongList[j].pQBPJSymboFeatures.push_back(CQBPFeature(tFeatureType, tFeatureName, tFeatureVal));

                                    pQBP_FeaturesDoc->readNextStartElement();
                                    pQBP_FeaturesDoc->readNextStartElement();
                                }
                            }
                        }
                    }
                }
            }
            file->close();
        }
    }

    return true;
}

bool CQBPJSymbolicFile::ParseFeatures(vector<CQBPSong>        &pQBP_SongList,
                                      vector<CQBPFeatureType> &pQBPFeatureTypeList)
{
    string tName;//nome temporario para identificação do dataset
    string tFeatureName;//nome temporario para identificação do dataset
    int    tGenre;//ID do Gênero para Parse
    int    tSong;//ID da Musica no Gênero
    string tAbsoluteFileName;
    string tFileName;

    QDirIterator it("jsymbolic/", QDirIterator::Subdirectories);
    while (it.hasNext())
    {
        tAbsoluteFileName = it.next().toStdString();

        //Verifica se não é o arquivo de definições de features
        std::size_t found = tAbsoluteFileName.find("FeatureValues");
        if (found != std::string::npos)
        {
            QFile file(tAbsoluteFileName.c_str());

            //Carrega as Features JSymbolic atraves do arquivo
            file.open(QIODevice::ReadOnly);

            QTextStream      out(&file);
            QString stream = out.readAll();
            QString tag;
            QString value;
            pQBP_FeaturesDoc = new QXmlStreamReader(stream);

            while (!pQBP_FeaturesDoc->atEnd())
            {
               if(pQBP_FeaturesDoc->readNextStartElement())
               {
                   if(pQBP_FeaturesDoc->name() == "pathinst")
                   {
                       value = pQBP_FeaturesDoc->readElementText();
                   }
                   if(pQBP_FeaturesDoc->name() == "pathworld")
                   {
                       value = pQBP_FeaturesDoc->readElementText();
                   }
               }
            }
            /*
            //Faz o parse do xml
            pQBP_FeaturesDoc.parse<0>(xmlFileFeatures.data());

            //Pega a Raiz do Documento
            xml_node<> *Root = pQBP_FeaturesDoc.first_node();

            //Processa cada dataset (Musica)
            for (xml_node<> *pNode = Root->first_node("data_set"); pNode; pNode = pNode->next_sibling())
            {
                //Processa o Dataset Id (Nome do arquivo)
                xml_node<> *pDataSetId = pNode->first_node("data_set_id");

                //Pega o Valor do dataset Id (Nome do path + nome da musica + extensão "mid")
                tName = pDataSetId->value();

                //Localiza e apaga o primeiro folder do path
                int nfold;
                nfold = (int)tName.find("\\");
                tName.erase(0, tName.substr(0, nfold + 1).size());

                //Enquanto ainda tiverem folders vai removendo...
                while (nfold != -1)
                {
                    nfold = (int)tName.find("\\");
                    tName.erase(0, tName.substr(0, nfold + 1).size());
                }

                //remove o .mid , espaços e pontuação do nome
                int npos = (int)tName.find(".mid");
                if (npos != -1)
                {
                    tName.erase(npos, 4);
                }
                tName.erase(remove_if(tName.begin(), tName.end(), invalidJsymChar), tName.end());
                tName.erase(remove_if(tName.begin(), tName.end(), isSpaceJsymChar), tName.end());
                tName.erase(remove_if(tName.begin(), tName.end(), isPunctJsymChar), tName.end());

                //Caso Exista a Musica no DataBase fazemos o Parse das Features na Musica
                if (GetParseIds(tName, pQBP_SongList, tGenre, tSong))
                {
                    //Processa todas as Features do Dataset
                    for (xml_node<> *pFeatures = pNode->first_node("feature"); pFeatures; pFeatures = pFeatures->next_sibling())
                    {
                        //processa o nome e o valor do dataset
                        xml_node<> *pFeatureName = pFeatures->first_node("name");
                        xml_node<> *pFeatureValue = pFeatures->first_node("v");

                        int    tFeatureType;
                        int    tFeatureDimensions;
                        string tFeatureName = pFeatureName->value();

                        tFeatureName.erase(remove_if(tFeatureName.begin(), tFeatureName.end(), invalidJsymChar), tFeatureName.end());
                        tFeatureName.erase(remove_if(tFeatureName.begin(), tFeatureName.end(), isSpaceJsymChar), tFeatureName.end());
                        tFeatureName.erase(remove_if(tFeatureName.begin(), tFeatureName.end(), isPunctJsymChar), tFeatureName.end());

                        //Checa se a feature e um vetor, se for nao inclui ainda(Histograma)
                        GetParseFTypeIds(tFeatureName,pQBPFeatureTypeList,tFeatureType);
                        //Pega o numero de dimensoes da feature
                        pQBPFeatureTypeList[tFeatureType].GetDimensions(tFeatureDimensions);
                        //O sistema esta aceitando apenas features unicas por enquanto
                        if(tFeatureDimensions>1)continue;
                        //caso seja unica repassa valor e continua
                        double tFeatureVal = atof(pFeatureValue->value());
                        //Caso exista um Type desta Feature , Extraimos o ID e continuamos...
                        pQBP_SongList[tSong].pQBPJSymboFeatures.push_back(CQBPFeature(tFeatureType, tFeatureName, tFeatureVal));

                    }
                }
            }
            */
        }
        else
        {
            //Carregar Feature Definitions caso não exista.
            if (pQBPFeatureTypeList.size() == 0)
            {
                ParseFeatureDefinitions(&pQBPFeatureTypeList);
            }
        }
    }

    return true;
}

bool CQBPJSymbolicFile::ParseFeatureDefinitions(vector<CQBPFeatureType> *pQBPFeatureTypeList)
{
    QString tNome;
    QString tDescricao;
    QString tDimensoes;
    QString tSequencial;

    bool   bSequencial=false;
    int    iDimensoes=0;
    string fNome;

    QFile file("jsymbolic/FeatureDefinitions.xml");

    //Carrega as Features JSymbolic atraves do arquivo
    file.open(QIODevice::ReadOnly);

    QTextStream      out(&file);
    QString stream = out.readAll();


    pQBP_FeaturesDef = new QXmlStreamReader(stream);


    while (!pQBP_FeaturesDef->atEnd())
    {
       if(pQBP_FeaturesDef->readNextStartElement())
       {
           if(pQBP_FeaturesDef->name() == "feature")
           {
               pQBP_FeaturesDef->readNextStartElement();
               if(pQBP_FeaturesDef->name() == "name")
               {
                   tNome= pQBP_FeaturesDef->readElementText();
               }

               pQBP_FeaturesDef->readNextStartElement();
               if(pQBP_FeaturesDef->name() == "description")
               {
                   tDescricao= pQBP_FeaturesDef->readElementText();
               }

               pQBP_FeaturesDef->readNextStartElement();
               if(pQBP_FeaturesDef->name() == "is_sequential")
               {
                   tSequencial = pQBP_FeaturesDef->readElementText();
                   bSequencial = (bool)tSequencial.toStdString().c_str();
               }

               pQBP_FeaturesDef->readNextStartElement();
               if(pQBP_FeaturesDef->name() == "parallel_dimensions")
               {
                   tDimensoes= pQBP_FeaturesDef->readElementText();
                   iDimensoes= tDimensoes.toInt();
               }

               fNome = tNome.toStdString();
               fNome.erase(remove_if(fNome.begin(), fNome.end(), invalidJsymChar), fNome.end());
               fNome.erase(remove_if(fNome.begin(), fNome.end(), isSpaceJsymChar), fNome.end());
               fNome.erase(remove_if(fNome.begin(), fNome.end(), isPunctJsymChar), fNome.end());

               pQBPFeatureTypeList->push_back(CQBPFeatureType(fNome, tDescricao.toStdString(), iDimensoes, bSequencial, false));
           }
       }
    }

    return true;
}

bool CQBPJSymbolicFile::GetParseIds(string pQBPDatasetName, vector<CQBPGenre> pQBP_GenreList, int &pGenreId, int &pSongId)
{
    string tName;

    for (int i = 0; i < (int)pQBP_GenreList.size(); i++)
    {
        for (int j = 0; j < (int)pQBP_GenreList[i].pQBPSongList.size(); j++)
        {
            //Repassamos o nome da musica
            tName = pQBP_GenreList[i].pQBPSongList[j].pQBPSongName;

            //remove o .mid , espaços e pontuação do nome
            int npos = (int)tName.find(".mid");
            if (npos != -1)
            {
                tName.erase(npos, 4);
            }
            tName.erase(remove_if(tName.begin(), tName.end(), invalidJsymChar), tName.end());
            tName.erase(remove_if(tName.begin(), tName.end(), isSpaceJsymChar), tName.end());
            tName.erase(remove_if(tName.begin(), tName.end(), isPunctJsymChar), tName.end());

            //Obs:. Estamos fazendo isto com o nome devido a no build full estarmos extraindo estes dados
            //e os mesmos ainda nao foram salvos em arquivo(que ja tem os dados tratados)
            //portanto se formos carregar dados JSymbolic em outro local ja nao teremos este problema...
            if (tName == pQBPDatasetName)
            {
                pGenreId = i;
                pSongId  = j;
                return true;
            }
        }
    }
    return false;
}

bool CQBPJSymbolicFile::GetParseIds(string pQBPDatasetName, vector<CQBPSong> pQBP_SongList, int &pGenreId, int &pSongId)
{
    string tName;

    for (int i = 0; i < (int)pQBP_SongList.size(); i++)
    {
        //Repassamos o nome da musica
        tName = pQBP_SongList[i].pQBPSongName;

        //remove o .mid , espaços e pontuação do nome
        int npos = (int)tName.find(".mid");
        if (npos != -1)
        {
            tName.erase(npos, 4);
        }
        tName.erase(remove_if(tName.begin(), tName.end(), invalidJsymChar), tName.end());
        tName.erase(remove_if(tName.begin(), tName.end(), isSpaceJsymChar), tName.end());
        tName.erase(remove_if(tName.begin(), tName.end(), isPunctJsymChar), tName.end());

        //Obs:. Estamos fazendo isto com o nome devido a no build full estarmos extraindo estes dados
        //e os mesmos ainda nao foram salvos em arquivo(que ja tem os dados tratados)
        //portanto se formos carregar dados JSymbolic em outro local ja nao teremos este problema...
        if (tName == pQBPDatasetName)
        {
            pGenreId = pQBP_SongList[i].pQBPSongCategory;
            pSongId  = i;
            return true;
        }
    }
    return false;
}

bool CQBPJSymbolicFile::GetFeatureTypeId(QString pQBPFeatureName, int &pFTypeId)
{     
    for (uint i = 0; i < (uint)vFeatureDefifitions.size(); i++)
    {
        //Se adquirimos os dados ok...
        if (vFeatureDefifitions[i].sFeatureName == pQBPFeatureName)
        {
            pFTypeId = (int)i;
            return true;
        }
    }
    return false;
}
