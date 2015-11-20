#include "native_opencv.h"

using namespace std;
using namespace cv;

extern "C" {
JNIEXPORT void JNICALL Java_ch_hepia_lsn_opencv_1native_1androidstudio_MainActivity_salt(JNIEnv *env, jobject instance,
                                                                                         jlong matAddrGray,
                                                                                         jint nbrElem) {

    Mat& mGr  = *(Mat*)matAddrGray;
    for(int k=0; k<nbrElem; k++)
    {
        int i = rand()%mGr.cols;
        int j = rand()%mGr.rows;
        mGr.at<uchar>(j,i)=255;
    }
}
}
