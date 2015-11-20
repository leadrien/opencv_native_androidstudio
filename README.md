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


## How to create the native OpenCV project from scratch
Here is how I made this project. If you simply want to run openCV with NDK support, use the previous **Usage** chapter. If you want to build the full project from scratch, you can follow the steps in this chapter.

I used mostly [this](http://stackoverflow.com/questions/27406303/opencv-in-android-studio), [this](http://stackoverflow.com/questions/32171259/opencv-with-android-studio-1-3-using-new-gradle-undefined-reference) and [that](https://github.com/jlhonora/opencv-android-sample)


* Download latest OpenCV sdk for Android from OpenCV.org and decompress the zip file.
* Import OpenCV to Android Studio, From File -> New -> Import Module, choose sdk/java folder in the unzipped opencv archive.
* Add module dependency by Application -> Module Settings, and select the Dependencies tab. Click + icon at bottom, choose Module Dependency and select the imported OpenCV module.

* Make a symlink named `jniLibs` in `app/src/main` that points to `OPENCV_SDK/sdk/native/libs`

* In application build.gradle use `gradle-experimental:0.3.alpha7`
* 
 replace

     `classpath 'com.android.tools.build:gradle:1.3.0'`
     
 with
 
     `classpath 'com.android.tools.build:gradle-experimental:0.3.0-alpha7'`


* In gradle-wrapper.properties, use grade 2.6
```
    distributionBase=GRADLE_USER_HOME
    distributionPath=wrapper/dists
    zipStoreBase=GRADLE_USER_HOME
    zipStorePath=wrapper/dists
    distributionUrl=https\://services.gradle.org/distributions/gradle-2.6-all.zip
```

* In openCVLibrary module, use the `model` plugin and make sure you use java 7
```
    apply plugin: 'com.android.model.library'

    model {

        compileOptions.with {
            sourceCompatibility=JavaVersion.VERSION_1_7
            targetCompatibility=JavaVersion.VERSION_1_7
        }

        android {
            compileSdkVersion = 19
            buildToolsVersion = "19.1"

            defaultConfig.with {
                minSdkVersion.apiLevel = 19
                targetSdkVersion.apiLevel = 19
            }
        }
    }
```

* In app `build.gradle`: use the `model` plugin, add opencv native stuff, remove unused
  dependencies

 Remove the following lines:
 
```
    testCompile 'junit:junit:4.12'
    compile 'com.android.support:appcompat-v7:23.1.1'
    compile 'com.android.support:design:23.1.1'
```

And add OpenCV stuff:
```
def openCVAndroidSdkDir = "/opt/opencv-android-sdk-v3.0/sdk/native"
    android.ndk {
        moduleName = "native"
        cppFlags += "-I${file(openCVAndroidSdkDir + "/jni/include")}".toString()
        cppFlags += "-frtti"
        cppFlags += "-fexceptions"
        ldLibs += ["log", "opencv_java3"]
        stl    = "gnustl_static"
    }

    android.productFlavors {
        // for detailed abiFilter descriptions, refer to "Supported ABIs" @
        // https://developer.android.com/ndk/guides/abis.html#sa
        create("arm") {
            ndk.abiFilters += "armeabi"
            ndk.ldFlags += "-L${file('src/main/jniLibs/armeabi')}".toString()
        }
        create("arm7") {
            ndk.abiFilters += "armeabi-v7a"
            ndk.ldFlags += "-L${file('src/main/jniLibs/armeabi-v7a')}".toString()
        }
        create("arm8") {
            ndk.abiFilters += "arm64-v8a"
            ndk.ldFlags += "-L${file('src/main/jniLibs/arm64-v8a')}".toString()
        }
    }
 ```

* In the app module, delete the following files and folders:
```
  src/main/res/values-21
  src/main/res/values-w820dp
  src/main/res/values/stypes.xml
```

* In `src/main/res/menu/menu_main.xml` remove `app:showAsAction="never"`

* In `AndreoidManifest.xml` remove the following lines:
```
    android:theme="@style/AppTheme"
    android:theme="@style/AppTheme.NoActionBar" >
```

  And add the camera permissions:
  
```
    <uses-permission android:name="android.permission.CAMERA"/>

    <uses-feature android:name="android.hardware.camera"/>
    <uses-feature android:name="android.hardware.camera.autofocus"/>
    <uses-feature android:name="android.hardware.camera.front"/>
    <uses-feature android:name="android.hardware.camera.front.autofocus"/>
```

* [Here](https://github.com/leadrien/opencv_native_androidstudio/blob/master/app/src/main/java/ch/hepia/lsn/opencv_native_androidstudio/MainActivity.java) is an example of the Activity.


* In `app/src/main` add a new directory named `jni`
* 
  Create a new cpp class, named `native_opencv.h` `native_opencv.cpp`

* [Here](https://github.com/leadrien/opencv_native_androidstudio/blob/master/app/src/main/jni/native_opencv.cpp) is an example of C++ code that add random noise to a frame
