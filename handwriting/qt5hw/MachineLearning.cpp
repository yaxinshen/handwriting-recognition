#include "stdafx.h"
#include "MachineLearning.h"
#include <highgui.h>
#include <iostream>
#include <fstream>


MachineLearning::MachineLearning(void)
{
    is_load_training_model = false;
}

void MachineLearning::ExtractDFT(float pcadata[],const int featureData[],const int &dataWidth,const int &DFTwidth )
{
    CvMat* Fourier = cvCreateMat(1,dataWidth,CV_32FC1);
    memcpy(Fourier->data.i,featureData,sizeof(featureData));
    for(int i=0;i<dataWidth;i++)
        cvSetReal2D(Fourier,0,i,featureData[i]);

    CvMat* dst = cvCreateMat(1,dataWidth,CV_32FC1);
    cvDFT(Fourier,dst,CV_DXT_FORWARD|CV_DXT_SCALE);

    for(int i=0;i<DFTwidth;i++)
    {
        pcadata[i] = (float)cvGetReal2D(dst,0,i);
    }

    cvReleaseMat(&Fourier);
    cvReleaseMat(&dst);
}


int MachineLearning::read_num_class_data( const char* filename, int var_count,CvMat** data, CvMat** responses )
{
    const int M = 1024;
    FILE* f = fopen( filename, "rt" );
    CvMemStorage* storage;
    CvSeq* seq;
    char buf[M+2];
    float* el_ptr;
    CvSeqReader reader;
    int i, j;

    if( !f )
        return 0;

    el_ptr = new float[var_count+1];
    storage = cvCreateMemStorage();
    seq = cvCreateSeq( 0, sizeof(*seq), (var_count+1)*sizeof(float), storage );

    for(;;)
    {
        char* ptr;
        if( !fgets( buf, M, f ) || !strchr( buf, ',' ) )
            break;
        el_ptr[0] = buf[0];
        ptr = buf+2;
        for( i = 1; i <= var_count; i++ )
        {
            int n = 0;
            sscanf( ptr, "%f%n", el_ptr + i, &n );
            ptr += n + 1;
        }
        if( i <= var_count )
            break;
        cvSeqPush( seq, el_ptr );
    }
    fclose(f);

    *data = cvCreateMat( seq->total, var_count, CV_32F );
    *responses = cvCreateMat( seq->total, 1, CV_32F );

    cvStartReadSeq( seq, &reader );

    for( i = 0; i < seq->total; i++ )
    {
        const float* sdata = (float*)reader.ptr + 1;
        float* ddata = data[0]->data.fl + var_count*i;
        float* dr = responses[0]->data.fl + i;

        for( j = 0; j < var_count; j++ )
            ddata[j] = sdata[j];
        *dr = sdata[-1];
        CV_NEXT_SEQ_ELEM( seq->elem_size, reader );
    }

    cvReleaseMemStorage( &storage );
    delete el_ptr;
    return 1;
}

int MachineLearning::build_rtrees_classifier(const char* data_filename,
    char* filename_to_load )
{
    CvMat* data = 0;
    CvMat* responses = 0;
    CvMat* var_type = 0;
    CvMat* sample_idx = 0;
    // Create or load Random Trees classifier
    if( filename_to_load )
    {
        // load classifier from the specified file
        forest.load( filename_to_load );
        if( forest.get_tree_count() == 0 )
        {
            printf( "Could not read the classifier %s\n", filename_to_load );
            return -1;
        }
        printf( "The classifier %s is loaded.\n", filename_to_load  );
    }
    else
    {
        int canread = read_num_class_data( data_filename, DataCount, &data, &responses );
        int numdata = 0, numtrain = 0, numtest = -1;
        double train_hr = 0, test_hr = 0;

        if( !canread )
        {
            printf( "Could not read the database %s\n", data_filename );
            return -1;
        }

        printf( "The database %s is loaded.\n", data_filename );

        numdata = data->rows;
        numtrain = (int)(numdata*0.8);
        printf( "sample=%d.\n", numdata );

        // create classifier by using <data> and <responses>
        printf( "Training the classifier ...");

        // 1. create type mask
        var_type = cvCreateMat( data->cols + 1, 1, CV_8U );
        cvSet( var_type, cvScalarAll(CV_VAR_ORDERED) );
        cvSetReal1D( var_type, data->cols, CV_VAR_CATEGORICAL );

        // 2. create sample_idx
        sample_idx = cvCreateMat( 1, numdata, CV_8UC1 );
        CvMat mat;
        cvGetCols( sample_idx, &mat, 0, numdata );
        cvSet( &mat, cvRealScalar(1) );

        for(int i=0;i<numdata;i++)
        {
            if((i%5)==0)
            {
                cvSet2D(sample_idx,0,i,cvRealScalar(0));
                numtest++;
            }
        }

        // 3. train classifier
        forest.train( data, CV_ROW_SAMPLE, responses, 0, sample_idx, var_type, 0,
            CvRTParams(10,10,0,false,15,0,true,4,100,0.01f,CV_TERMCRIT_ITER));
        printf( "\n");
       // forest.save("CharacterClassifier.txt");
        // compute prediction error on train and test data

        for(int i = 0; i < numdata; i++ )
        {
            double r;
            CvMat sample;
            cvGetRow( data, &sample, i );

            r = forest.predict( &sample );
            double abs_r = fabs((float)r - responses->data.fl[i]) <= FLT_EPSILON ? 1.0 : 0.0;

            if(abs_r < FLT_EPSILON)
            {
                printf( "test error %d '%c' %f \n",i,(char)responses->data.fl[i],fabs((float)r - responses->data.fl[i]));
            }

            if((i%5)==0)test_hr += abs_r;
            else train_hr += abs_r;

        }
        test_hr /= (double)(numtest);
        train_hr /= (double)(numdata-numtest);
        printf( "Recognition rate: train = %.1f%%, test = %.1f%%\n",
            train_hr*100., test_hr*100. );

        //printf( "Number of trees: %d\n", forest.get_tree_count() );
    }

    //// Save Random Trees classifier to file if needed

    cvReleaseMat( &sample_idx );
    cvReleaseMat( &var_type );
    cvReleaseMat( &data );
    cvReleaseMat( &responses );

    return 0;
}


bool MachineLearning::load( char *training_filename)
{
    forest.clear();
    if(build_rtrees_classifier(NULL,training_filename)==-1) return false;
    is_load_training_model = true;

    return true;
}
bool MachineLearning::train(const  char *data_filename)
{
    forest.clear();
    build_rtrees_classifier(data_filename,NULL);
    is_load_training_model = true;
    return true;
}
bool MachineLearning::predict(char &shape_type,float featureData[])
{
    if(is_load_training_model)
    {
        //to do build sample
        CvMat *sample_data= cvCreateMat( 1, DataCount, CV_32F );
        //cvSet2D(sample_data,0,0,cvRealScalar(0));
        for(int i=0;i<DataCount;i++)
        {
            cvSet2D(sample_data,0,i,cvRealScalar(featureData[i]));
        }
        predict_rtrees_classifier(sample_data,shape_type);
        cvReleaseMat(&sample_data);
        return true;
    }
    else
        return false;
}

int MachineLearning::predict_rtrees_classifier(CvMat *sample_data,char &shape_type)
{
    double r = forest.predict( sample_data );
    shape_type = (char)r;
    return 0;
}


