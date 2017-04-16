#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "stdafx.h"
#include "windows.h"
#include <iostream>
#include <string.h>
#include <cxcore.h>
#include <cv.h>
#include <highgui.h>
#include <fstream>
#include "Finger.h"
#include "MachineLearning.h"

#pragma comment(lib,"opencv_core2411d.lib")
#pragma comment(lib,"opencv_highgui2411d.lib")
#pragma comment(lib,"opencv_ml2411d.lib")
#pragma comment(lib,"opencv_imgproc2411.lib")

using namespace std;

const int SCALE_MAX = 500;
const int SAMPLE_COUNT = 50; //50 points for each stroke
const int SAMPLE_COUNT_OPT = 5; //for fourier
char pre_letter =0;
MachineLearning ml;

std::vector< FingerTrack > Stroke;
std::vector< FingerTrack > StrokeOpt;

bool inTrack =false;
int traing_data =0;
char letter='A';


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    image = QImage(this->size(), QImage::Format_RGB32);
    image.fill(Qt::white);

    drawing = false;
    brushColour = Qt::blue;
    brushSize = 5;

    ml.DataCount = 1 + SAMPLE_COUNT_OPT*2*3;
    if(!ml.load("./CharacterClassifier.txt"))
        QMessageBox::about(this, "error","Do not find classifier!" );

    ui->recognitionDisplay->setText("Help:to make sure the rule\nBrush:to change color and size");

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::toNormalSize()
{
    int xmax=0;
    int ymax=0;
    int xmin=10000;
    int ymin=10000;
    for(int i=0;i<(int)StrokeOpt.size();i++)
    {
        int ListObjSize = (int)StrokeOpt[i].track.size();
        for(int j=0;j<(int)ListObjSize;j++)
        {
            xmax = max((StrokeOpt[i].track[j].center.x),xmax);
            ymax = max((StrokeOpt[i].track[j].center.y),ymax);
            xmin = min((StrokeOpt[i].track[j].center.x),xmin);
            ymin = min((StrokeOpt[i].track[j].center.y),ymin);
        }
    }


    for(int i=0;i<(int)StrokeOpt.size();i++)
    {
        int ListObjSize = (int)StrokeOpt[i].track.size();
        for(int j=0;j<(int)ListObjSize;j++)
        {
            StrokeOpt[i].track[j].center.x -=xmin;
            StrokeOpt[i].track[j].center.y -=ymin;
        }
    }

    int MaxW = max(xmax-xmin,ymax-ymin); //aspect ratio
    for(int i=0;i<(int)StrokeOpt.size();i++)
    {
        int ListObjSize = (int)StrokeOpt[i].track.size();
        for(int j=0;j<(int)ListObjSize;j++)
        {
            StrokeOpt[i].track[j].center.x =(int)((float)StrokeOpt[i].track[j].center.x/MaxW*SCALE_MAX);
            StrokeOpt[i].track[j].center.y =(int)((float)StrokeOpt[i].track[j].center.y/MaxW*SCALE_MAX);
        }
    }

}

bool MainWindow::analysis()
{
    StrokeOpt.clear();
    for(int i=0;i<(int)Stroke.size();i++)
    {
        FingerTrack ft;
        StrokeOpt.push_back(ft);
        CvPoint start_pt = Stroke[i].track[0].center;
        Finger fg;
        fg.center  = start_pt;
        StrokeOpt[i].track.push_back(fg);

        //total_distance
        long total_dis =0;
        int ListObjSize = (int)Stroke[i].track.size();

        for(int j=0;j<ListObjSize-1;j++)
        {
            CvPoint pt = Stroke[i].track[j].center;
            CvPoint pt_next = Stroke[i].track[j+1].center;
            long distance = (pt_next.x - pt.x)*(pt_next.x - pt.x) +  (pt_next.y - pt.y)*(pt_next.y - pt.y);
            total_dis+=(long)sqrt((float)distance);
        }

        int search_len;
        search_len = total_dis/(SAMPLE_COUNT+2);

        //else search_len = total_dis/35;
        if (search_len==0)
        {Stroke.clear();StrokeOpt.clear();return false;}
        //cout << "total_dis"<<total_dis<<"search_len" << search_len;
        assert(search_len>0);

        //if (ListObjSize > 60){
        for(int j=0;j<ListObjSize;j++)
        {

            CvPoint pt = Stroke[i].track[j].center;
            long distance = (start_pt.x - pt.x)*(start_pt.x - pt.x) +  (start_pt.y - pt.y)*(start_pt.y - pt.y);
            distance = (long)sqrt((float)distance);
            if(distance>search_len)
            {
                float radio = (float)search_len/distance;
                start_pt.x = (int)(start_pt.x + (pt.x - start_pt.x)*radio);
                start_pt.y = (int)(start_pt.y + (pt.y - start_pt.y)*radio);
                Finger fg;
                fg.center  = start_pt;//cout <<"wrong1";
                StrokeOpt[i].track.push_back(fg);	//cout<<"wrong2";
                //add++;
                j--;
            }
        }
        //cout << "add" <<add<<endl;
        //}
    }

    toNormalSize();
    return true;
}

void MainWindow::WriteData(float featureData[])
{
    int Tracksize = (int)StrokeOpt.size();

    featureData[0] = (float)Tracksize;
    int f_index = 0;

    for(int i=0;i<Tracksize;i++)
    {
        int ListObjSize = (int)StrokeOpt[i].track.size();
        //cout << "ListObjSize" <<ListObjSize;

        assert(ListObjSize>=SAMPLE_COUNT);

        float pcadata[SAMPLE_COUNT_OPT];
        int fData[SAMPLE_COUNT];
        //X DFT
        for(int j=0;j<SAMPLE_COUNT;j++)
        {
            fData[j] = StrokeOpt[i].track[j].center.x;
        }
        ml.ExtractDFT(pcadata,fData,SAMPLE_COUNT,SAMPLE_COUNT_OPT);
        for(int k=0;k<SAMPLE_COUNT_OPT;k++)
        {
            f_index++;
            featureData[f_index] = pcadata[k];


        }
        //Y DFT
        for(int j=0;j<SAMPLE_COUNT;j++)
        {
            fData[j] = StrokeOpt[i].track[j].center.y;
        }
        ml.ExtractDFT(pcadata,fData,SAMPLE_COUNT,SAMPLE_COUNT_OPT);
        for(int k=0;k<SAMPLE_COUNT_OPT;k++)
        {
           // if(!InRecongnize) logfile<<","<<pcadata[k];
            f_index++;
            featureData[f_index] = pcadata[k];
        }


    }
    for(int i=Tracksize;i<3;i++) //fill with 0
    {
        for(int j=0;j<SAMPLE_COUNT_OPT;j++)
        {
            f_index++;
            featureData[f_index] =  0.0f;
            f_index++;
            featureData[f_index] =  0.0f;
        }
    }
}
void MainWindow::mousePressEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton)
    {
        drawing = true;
        lastPoint = event->pos();
        if(!inTrack)
        {
            FingerTrack ft;
            Stroke.push_back(ft);
            inTrack = true;

        }
    }

}

void MainWindow::mouseMoveEvent(QMouseEvent *event)
{
    if((event->buttons() & Qt::LeftButton) && drawing)
    {
        QPainter painter(&image);
        painter.setPen(QPen(brushColour, brushSize, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
        painter.drawLine(lastPoint, event->pos());

        if(inTrack)
        {
            Finger fg;
            fg.center.x  = lastPoint.rx();
            fg.center.y  = lastPoint.ry();
            Stroke.back().track.push_back(fg);
        }
        lastPoint = event->pos();
        this->update();
    }
}

void MainWindow::mouseReleaseEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton)
    {
        drawing = false;
        inTrack = false;
        bool flag = analysis();
        if (!flag)
        {
            QMessageBox::about(this, "error","This line is too short\nPlease write a longer one" );
            image.fill(Qt::white);
            ui->recognitionDisplay->setText("is writing...");
            this->update();
        }
    }
}

void MainWindow::paintEvent(QPaintEvent *event)
{
    QPainter canvasPainter(this);
    canvasPainter.drawImage(this->rect(), image, image.rect());
}

void MainWindow::load_click()
{
    QString filename =  QFileDialog::getOpenFileName(this, tr("Open File"), "", tr("Classifier (*.txt)"));
    if (filename!=NULL){
    QByteArray ba = filename.toLatin1();
    char *mm = ba.data();
    if(!ml.load(mm))
    QMessageBox::about(this, "error","Do not find classifier!" );
    else QMessageBox::about(this, "success","load complete!" );
    }
}

void MainWindow::train_click()
{
    ml.train("./data.txt");
    QMessageBox::about(this, "Train","Train complete" );
}

void MainWindow::recognize_click()
{
    if( Stroke.size()>0 && !inTrack)
    {
        float featureData[31];
        WriteData(featureData);
        Stroke.clear();
        StrokeOpt.clear();

            pre_letter = 0;
            ml.predict(pre_letter,featureData);

           if(pre_letter!=0)
           {
               char str[30];
               sprintf(str,"result=%c",pre_letter);
               QString res=str;
               ui->recognitionDisplay->setText(res);
               //QMessageBox::about(this, "Result", res);
           }

    }
    else QMessageBox::about(this, "error","You do not write anything!" );
}

void MainWindow::clear_click()
{
    Stroke.clear();
    StrokeOpt.clear();
    image.fill(Qt::white);
    ui->recognitionDisplay->setText("is writing...");
    this->update();
}

void MainWindow::on_actionAbout_triggered()
{
    QMessageBox::about(this, "About", "upper letter rule\n1. C J L O S U V W Z        finish in one stroke\n2. B D G K M N P Q T X Y    finish in two stroke\n3. A E F H I R              finish in three stroke\nlower case letter rule\n1. a b c d e g q r u w y    finish in one stroke\n2. f h i j k m p t x        finish in two stroke\nnumber rule\n1. 2 3 6 8 9                finish in one stroke\n2. 1 4 5 7                  finish in two stroke\n");
}

void MainWindow::on_action2px_triggered()
{
    brushSize = 2;
}

void MainWindow::on_action5px_triggered()
{
    brushSize = 5;
}

void MainWindow::on_action10px_triggered()
{
    brushSize = 10;
}

void MainWindow::on_actionBlack_triggered()
{
    brushColour = Qt::black;
}

void MainWindow::on_actionRed_triggered()
{
    brushColour = Qt::red;
}

void MainWindow::on_actionGreen_triggered()
{
    brushColour = Qt::green;
}

void MainWindow::on_actionBlue_triggered()
{
    brushColour = Qt::blue;
}
