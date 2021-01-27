#ifndef QBP_CLUSTERIZER_H
#define QBP_CLUSTERIZER_H

#include "QBP_GlobalDef.h"
#include "QBP_LogQueue.h"
#include "QBP_Chord.h"

class CQBPClusterizer
{
public:
     CQBPClusterizer();
    ~CQBPClusterizer();

    void FillData(vector<CQBPChord> pQBPChords);
    void Clusterize();

    int             iQBP_ClusterCount;
    int             iQBP_SampleCount;
    vector<Point3f> mSamplePoints;
    Mat             mSampleLabels;
    Mat             mCenters;


    vector<vector<float> > buffer;
};

#endif // QBP_CLUSTERIZER_H
