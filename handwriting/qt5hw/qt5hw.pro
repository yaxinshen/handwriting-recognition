#-------------------------------------------------
#
# Project created by QtCreator 2016-12-22T21:13:09
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = qt5hw
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    MachineLearning.cpp \
    stdafx.cpp

HEADERS  += mainwindow.h \
    Finger.h \
    MachineLearning.h \
    stdafx.h

FORMS    += mainwindow.ui

INCLUDEPATH+=D:\opencv\build\include\opencv\
                    D:\opencv\build\include\opencv2\
                    D:\opencv\build\include

CONFIG(debug,debug|release) {
LIBS += -Ld:\opencv\build\x86\vc10\lib \
-lopencv_ml2411d  \
-lopencv_calib3d2411d  \
-lopencv_contrib2411d  \
-lopencv_core2411d  \
-lopencv_features2d2411d  \
-lopencv_flann2411d  \
-lopencv_gpu2411d  \
-lopencv_highgui2411d  \
-lopencv_imgproc2411d  \
-lopencv_legacy2411d  \
-lopencv_objdetect2411d  \
-lopencv_ts2411d  \
-lopencv_video2411d  \
-lopencv_nonfree2411d  \
-lopencv_ocl2411d  \
-lopencv_photo2411d  \
-lopencv_stitching2411d  \
-lopencv_superres2411d  \
-lopencv_videostab2411d  \
} else {
LIBS += -Ld:\opencv\build\x86\vc10\lib \
-lopencv_objdetect2411  \
-lopencv_ts2411  \
-lopencv_video2411  \
-lopencv_nonfree2411  \
-lopencv_ocl2411  \
-lopencv_photo2411  \
-lopencv_stitching2411  \
-lopencv_superres2411  \
-lopencv_videostab2411  \
-lopencv_calib3d2411  \
-lopencv_contrib2411  \
-lopencv_core2411  \
-lopencv_features2d2411  \
-lopencv_flann2411  \
-lopencv_gpu2411  \
-lopencv_highgui2411  \
-lopencv_imgproc2411  \
-lopencv_legacy2411  \
-lopencv_ml2411  \
}


