# Native OpenCV with Android Studio

This application is a sample Android Studio project (tested on 1.4.1) with native OpenCV.

It gets the camera frames, make JNI calls with its gray matrices references as parameters, add some random noise to the images from a C++ method, and render the generated frames.

## Usage
Here is how to use this project to run native OpenCV code.

* Make sure you have Android SDK up to date, with NDK installed
* Download latest OpenCV SDK for Android from OpenCV.org and decompress the zip file.
* Clone this project
* Create a symlink named `jniLibs` in `app/src/main` that points to `$OPENCV_SDK/sdk/native/libs`
* In `app/build.gradle` change line 25 to points to `$OPENCV_SDK/sdk/native`
* Sync gradle
* Run the application

