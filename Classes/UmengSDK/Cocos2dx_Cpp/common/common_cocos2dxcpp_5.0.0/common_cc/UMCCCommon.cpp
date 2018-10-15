//
//  MobClickCpp.m
//  MobClickCpp
//
//  Created by 周厚振 on 16-5-24.
//  Copyright (c) 2016年 zhouhouzhen. All rights reserved.
//

#include "UMCCCommon.h"
#include <platform/CCCommon.h>
#include <jni/JniHelper.h>
#include "platform/android/jni/JniHelper.h"
#include <jni.h>
//#include <stdio.h>
//#include "cocos2d.h"

#include <map>
#include <string>
#include <utility>
#include <vector>
#include <stddef.h>





USING_NS_CC;
using namespace std;


extern "C"
    {
         static bool getCCommonMethod(JniMethodInfo &mi, const char *methodName,const char *signature) {
             CCLog("111%s", methodName);
             CCLog("222%s", signature);

            return JniHelper::getStaticMethodInfo(mi,
            "com/umeng/common/UMCocosConfigure", methodName, signature);
        }

        static void releaseCommonMethod(JniMethodInfo &mi) {
        mi.env->DeleteLocalRef(mi.classID);
        }
       
JNIEXPORT void JNICALL Java_com_umeng_common_UMCocosConfigure_InitCC (
        JNIEnv *env, jclass clz) {
    // initwrap();
      // jclass dpclazz = (*env)->FindClass(env,"com/umeng/common/UMCocosConfigure");
       jclass strClass = env->FindClass("com/umeng/common/UMCocosConfigure");
    if(strClass==0){
        CCLog("0000");
        return;
    }
     jmethodID mid = env->GetStaticMethodID(strClass, "initCocos", "(Ljava/lang/String;Ljava/lang/String;)V");
  
     if(mid==0){
        CCLog("find method1 error");
        return;
    }
     CCLog("2222");
     jstring version = env->NewStringUTF("Cocos2d-x");
    jstring type = env->NewStringUTF("5.0");
    
    // jstring version = env->NewStringUTF("1111");
    // jstring type = env->NewStringUTF("2222");
    //  CCLog("1vvvv%s", version);
    env->CallStaticVoidMethod(strClass, mid,version, type);
}

    }
     static void initwrap() {
      
     CCLog("111eee");
        JniMethodInfo mi;
        bool isHave = getCCommonMethod(mi, "initCocos", "(Ljava/lang/String;Ljava/lang/String;)V");

        if (isHave) {
        jstring version = mi.env->NewStringUTF(VERSION);
        jstring type = mi.env->NewStringUTF(WRAP_TYPE);
        mi.env->CallStaticVoidMethod(mi.classID, mi.methodID, type,version);
        mi.env->DeleteLocalRef(version);
        mi.env->DeleteLocalRef(type);

        releaseCommonMethod(mi);
            }
    }

  
    void UMCCCommon::setLogEnabled(bool value){
         JniMethodInfo mi;
        bool isHave = getCCommonMethod(mi, "setLog",  "(Z)V");
        if (isHave) {
        mi.env->CallStaticVoidMethod(mi.classID, mi.methodID, value);
        releaseCommonMethod(mi);
        } 
    }
    void UMCCCommon::init(const char *appkey, const char *channel){
       
    }
   

