#include "QBP_Clusterizer.h"
#include <iostream>

CQBPClusterizer::CQBPClusterizer()
{
   iQBP_ClusterCount = 6;
}

CQBPClusterizer::~CQBPClusterizer()
{

}

void CQBPClusterizer::FillData(vector<CQBPChord> pQBPChords)
{

    iQBP_SampleCount  = pQBPChords.size();

    for(uint i = 0; i< iQBP_SampleCount ;i++)
    {
        mSamplePoints.push_back(Point3f((float)pQBPChords[i].pQBPChordBuffer[0].iQBP_Pitch + (float)pQBPChords[i].pQBPChordBuffer[1].iQBP_Pitch,
                                        (float)pQBPChords[i].pQBPChordBuffer[2].iQBP_Pitch + (float)pQBPChords[i].pQBPChordBuffer[3].iQBP_Pitch,
                                        (float)pQBPChords[i].pQBPChordBuffer[4].iQBP_Pitch + (float)pQBPChords[i].pQBPChordBuffer[5].iQBP_Pitch));
    }
}

void CQBPClusterizer::Clusterize()
{

    double compactness = kmeans(mSamplePoints,
           iQBP_ClusterCount,
           mSampleLabels,
           TermCriteria( TermCriteria::EPS+TermCriteria::COUNT, 10, 1.0),
           3,
           KMEANS_PP_CENTERS,
           mCenters);

    for ( int i=0; i<mSampleLabels.rows; i++ )
    {
        int idx = mSampleLabels.at<int>(i);
        Point3f original_point = mSamplePoints[i];
        Point2f clustered_center;
        clustered_center.x = mCenters.at<float>( idx,0 );
        clustered_center.y = mCenters.at<float>( idx,1 );
        cerr << i << " " << idx << " " << original_point << " " << clustered_center << endl;
    }

}

