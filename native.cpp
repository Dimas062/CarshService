#include "native.h"

#ifdef Q_OS_ANDROID
#include <jni.h>
#endif
#include <QMetaObject>
#include <QDebug>





// //create a vector with all our JNINativeMethod(s)
// static JNINativeMethod methods[] = {
//  //   { "onArchiveTimeChanged", "(I)V",reinterpret_cast<void *>(onNativeArchiveTimeChanged)},
//  //   { "onPlayStopped", "()V",reinterpret_cast<void *>(onNativePlayStopped)},
//     { "onPicUriGeted", "()V",reinterpret_cast<void *>(onNativeEncounteredError)}
// };

// // this method is called automatically by Java after the .so file is loaded
// JNIEXPORT jint JNI_OnLoad(JavaVM* vm, void* /*reserved*/)
// {
//     JNIEnv* env;
//     // get the JNIEnv pointer.
//     if (vm->GetEnv(reinterpret_cast<void**>(&env), JNI_VERSION_1_6) != JNI_OK)
//       return JNI_ERR;

//     // search for Java class which declares the native methods
//    jclass javaClass = env->FindClass("org/nlb/VideoSapiens/QtAdMobActivity");
//     if (!javaClass)
//       return JNI_ERR;

//     // register our native methods
//     if (env->RegisterNatives(javaClass, methods,
//                           sizeof(methods) / sizeof(methods[0])) < 0) {

//       return JNI_ERR;
//     }

//     return JNI_VERSION_1_6;
// }
