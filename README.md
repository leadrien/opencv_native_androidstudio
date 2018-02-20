Native OpenCV with Android Studio
=================================

This application is a sample Android Studio project (tested on version 3.0) with native OpenCV.

It gets the camera frames, make JNI calls with its gray matrices references as parameters, add some random noise to the images from a C++ method, and render the generated frames.


(Old stuff with experimental gradle and AndroidStudio 1.4 under the branch android_studio_v1.4).

Usage
-----

Here is how to use this project to run native OpenCV code.

* Make sure you have Android SDK up to date, with NDK installed and CMake
* Download latest OpenCV SDK for Android from OpenCV.org and decompress the zip file.
* Clone this project
* Create a symlink named `jniLibs` in `app/src/main` that points to `YOUR_OPENCV_SDK/sdk/native/libs`
* In `app/CMakeLists.txt` change line 9 to points to `YOUR_OPENCV_SDK/sdk/native/jni/include`
* Sync gradle
* Run the application


How to create the native OpenCV project from scratch
----------------------------------------------------

Here is how I made this project. If you simply want to run openCV with NDK support, use the previous **Usage** chapter. If you want to build the full project from scratch, you can follow the steps in this chapter.

* Make sure you have Android SDK up to date, with NDK installed
* Download latest OpenCV SDK for Android from OpenCV.org and decompress the zip file.

* Create a new Android Studio project
  * Check Include C++ Support
  * Choose empty Activity
  * In C++ Support, you can check -fexceptions and -frtti

* Import OpenCV library module
  * New -> Import Module
  * Choose the `YOUR_OPENCV_SDK/sdk/java` folder
  * Unckeck replace jar, unckeck replace lib, unckeck create gradle-style

* Set the OpenCV library module up to fit your SDK

  Edit `openCVLibrary300/build.gradle` to fit your SDK:

  ```
    compileSdkVersion 26
    defaultConfig {
        minSdkVersion 19
        targetSdkVersion 26
    }
  ```

* Add OpenCV module dependency in your app module

  File -> Project structure -> Module app -> Dependencies tab -> New module dependency -> choose OpenCV library module


* Make a symlink named `jniLibs` in `app/src/main` that points to `YOUR_OPENCV_SDK/sdk/native/libs`

* Set the app build.gradle
  * Add abiFilters
    ```
        externalNativeBuild {
            cmake {
                cppFlags "-frtti -fexceptions"
                abiFilters 'x86', 'x86_64', 'armeabi', 'armeabi-v7a', 'arm64-v8a', 'mips', 'mips64'
            }
        }
    ```

  * Add openCV jniLibs directory to point to the symlink
    ```
    sourceSets {
        main {
            jniLibs.srcDirs = ['src/main/jniLibs']
        }
    }
    ```
  See [build.gradle](app/build.gradle)

* Configure the `CMakeLists.txt` file
  * After the `cmake_minimum_required`, add

    ```
    include_directories(YOUR_OPENCV_SDK/sdk/native/jni/include)
    add_library( lib_opencv SHARED IMPORTED )
    set_target_properties(lib_opencv PROPERTIES IMPORTED_LOCATION ${CMAKE_CURRENT_SOURCE_DIR}/src/main/jniLibs/${ANDROID_ABI}/libopencv_java3.so)
    ```

  * At the end of the file add `lib_opencv` to the `target_link_libraries` list


* Grant camera permission
  * Add the following lines in the `AndroidManifest.xml` file

    ```
    <uses-permission android:name="android.permission.CAMERA"/>
    <uses-feature android:name="android.hardware.camera"/>
    <uses-feature android:name="android.hardware.camera.autofocus"/>
    <uses-feature android:name="android.hardware.camera.front"/>
    <uses-feature android:name="android.hardware.camera.front.autofocus"/>
    ```

* Add OpenCV code
  * [MainActivity.java](app/src/main/java/ch/hepia/iti/opencvnativeandroidstudio/MainActivity.java)
  * [activity_main.xml](app/src/main/res/layout/activity_main.xml)
  * [native-lib.cpp](app/src/main/cpp/native-lib.cpp)

