#ifndef OPENCV_NATIVE_ANDROIDSTUDIO_NATIVE_OPENCV_H
#define OPENCV_NATIVE_ANDROIDSTUDIO_NATIVE_OPENCV_H

#include <jni.h>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/features2d/features2d.hpp>
#include <vector>

extern "C" {
JNIEXPORT void JNICALL Java_ch_hepia_lsn_opencv_1native_1androidstudio_MainActivity_salt(JNIEnv *env, jobject instance,
                                                                                         jlong matAddrGray,
                                                                                         jint nbrElem);

}
#endif //OPENCV_NATIVE_ANDROIDSTUDIO_NATIVE_OPENCV_H
