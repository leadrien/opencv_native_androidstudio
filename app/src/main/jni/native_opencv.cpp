//
// Created by adrien on 11/19/15.
//

#include "native_opencv.h"

using namespace std;
using namespace cv;

extern "C" {
JNIEXPORT void JNICALL Java_ch_hepia_lsn_opencv_1native_1androidstudio_MainActivity_salt(JNIEnv *env, jobject instance,
                                                                                         jlong matAddrGray,
                                                                                         jint nbrElem) {

    Mat& mGr  = *(Mat*)matAddrGray;
    //TODO
}
}
