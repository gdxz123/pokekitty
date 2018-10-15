//
//  MobClickCpp.m
//  MobClickCpp
//
//  Created by zhangziqi on 14-2-24.
//  Copyright (c) 2014年 Umeng Inc. All rights reserved.
//

#ifndef __UMCCCommon_H__
#define __UMCCCommon_H__

#include "cocos2d.h"

#include <vector>

USING_NS_CC;
using namespace std;
// #if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
// #include "cocos2d.h"
// #include <jni.h>
// #include "platform/android/jni/JniHelper.h"
// #include <android/log.h>
// #endif
#define VERSION "5.0"
#define WRAP_TYPE "Cocos2d-x"


// JNIEXPORT void JNICALL Java_com_umeng_common_UMCocosConfuture_Init(
//         JNIEnv*, jclass  ) ;

class UMCCCommon{
        
public:
    static void setLogEnabled(bool value);
    
        
    static void init(const char *appkey, const char *channel);
};
#endif
