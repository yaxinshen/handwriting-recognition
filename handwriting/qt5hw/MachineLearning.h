#include <cxcore.h>
#include <cv.h>
#include <ml.h>
#include <string>
using namespace std ;
class MachineLearning
{

public:

    bool predict(char &shape_type,float featureData[]);
    bool load( char *training_filename);
    bool train(const  char *data_filename);
    MachineLearning(void);
    void ExtractDFT(float pcadata[],const int featureData[],const int &dataWidth,const int &DFTwidth);
    int DataCount;

private:

    void ExtractPCA(float pcadata[],const int featureData[],const int &dataWidth );

    bool is_load_training_model;

    int read_num_class_data( const char* filename, int var_count,CvMat** data, CvMat** responses);
    int build_rtrees_classifier(const char* data_filename,char* filename_to_load);


    CvRTrees forest;
    CvSVM svm;
    int predict_rtrees_classifier(CvMat *sample_data,char &shape_type);

};
