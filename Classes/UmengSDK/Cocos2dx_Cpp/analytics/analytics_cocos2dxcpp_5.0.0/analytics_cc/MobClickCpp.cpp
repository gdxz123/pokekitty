//
//  MobClickCpp.m
//  MobClickCpp
//
//  Created by 周厚振 on 16-5-24.
//  Copyright (c) 2016年 zhouhouzhen. All rights reserved.
//

#include "MobClickCpp.h"
#include <jni.h>
#include <jni/JniHelper.h>


#define JAVA_CLASS_MOBCLICKAGENT                "com/umeng/analytics/MobclickAgent"
#define JAVA_CLASS_UMGAMEANALYTICS              "com/umeng/analytics/UMGameAnalytics"
#define JAVA_CLASS_UMGAMEAGENT                  "com/umeng/analytics/game/UMGameAgent"

using namespace std;
USING_NS_CC;
namespace umeng {

    extern "C"
    {
        jobject createJavaMapObject(JNIEnv *env, std::map<std::string, std::string>* map) {
            jclass class_Hashtable = env->FindClass("java/util/HashMap");
            jmethodID construct_method = env->GetMethodID( class_Hashtable, "<init>","()V");
            jobject obj_Map = env->NewObject( class_Hashtable, construct_method, "");
            if (map != NULL) {
                jmethodID add_method= env->GetMethodID( class_Hashtable,"put","(Ljava/lang/Object;Ljava/lang/Object;)Ljava/lang/Object;");
                for (std::map<std::string, std::string>::const_iterator it = map->begin(); it != map->end(); ++it) {
                    env->CallObjectMethod(obj_Map, add_method, env->NewStringUTF(it->first.c_str()), env->NewStringUTF(it->second.c_str()));
                }
            }
            env->DeleteLocalRef(class_Hashtable);
            return obj_Map;
        }
    }
    void MobClickCpp::setLogEnabled(bool value){
        JniMethodInfo t;
        if (JniHelper::getStaticMethodInfo(t,JAVA_CLASS_MOBCLICKAGENT,"setDebugMode", "(Z)V")){
            t.env->CallStaticVoidMethod(t.classID, t.methodID,value);
        }
    }
    void MobClickCpp::setCheckDevice(bool value){
        JniMethodInfo t;
        if (JniHelper::getStaticMethodInfo(t, JAVA_CLASS_MOBCLICKAGENT,"setCheckDevice", "(Z)V")){
            t.env->CallStaticVoidMethod(t.classID, t.methodID,value);
        }
    }
    void MobClickCpp::setSessionIdleLimit(int seconds){
        JniMethodInfo t;
        if (JniHelper::getStaticMethodInfo(t, JAVA_CLASS_MOBCLICKAGENT,"setSessionContinueMillis", "(J)V")){
            t.env->CallStaticVoidMethod(t.classID, t.methodID,seconds);
        }
    }
    
    void MobClickCpp::event(const char * eventId, const char * label){
        JniMethodInfo t;
        if (JniHelper::getStaticMethodInfo(t, JAVA_CLASS_UMGAMEANALYTICS,"event", "(Ljava/lang/String;Ljava/lang/String;)V")){
            jstring eId = t.env->NewStringUTF(eventId);
            jstring la = t.env->NewStringUTF(label);
            t.env->CallStaticVoidMethod(t.classID, t.methodID,eId,la);
            t.env->DeleteLocalRef(eId);
            t.env->DeleteLocalRef(la);
        }
    }
    void MobClickCpp::event(const char * eventId, eventDict * attributes, int counter){
        JniMethodInfo t;
        if (JniHelper::getStaticMethodInfo(t, JAVA_CLASS_UMGAMEANALYTICS,"event", "(Ljava/lang/String;Ljava/util/Map;I)V")){
            jstring eId = t.env->NewStringUTF(eventId);
            jobject jparamMap = createJavaMapObject(t.env, attributes);
            t.env->CallStaticVoidMethod(t.classID, t.methodID,eId,jparamMap,counter);
            t.env->DeleteLocalRef(eId);
            t.env->DeleteLocalRef(jparamMap);
        }
    }
    void MobClickCpp::event(const char * eventId, eventDict * attributes){
        JniMethodInfo t;
        if (JniHelper::getStaticMethodInfo(t, JAVA_CLASS_UMGAMEANALYTICS,"event", "(Ljava/lang/String;Ljava/util/Map;)V")){
            jstring eId = t.env->NewStringUTF(eventId);
            jobject jparamMap = createJavaMapObject(t.env, attributes);
            t.env->CallStaticVoidMethod(t.classID, t.methodID,eId,jparamMap);
            t.env->DeleteLocalRef(eId);
            t.env->DeleteLocalRef(jparamMap);
        }
    }
   
    void MobClickCpp::setUserLevel(int level) {
        JniMethodInfo t;
        if (JniHelper::getStaticMethodInfo(t,JAVA_CLASS_UMGAMEAGENT,"setPlayerLevel", "(I)V")){
            t.env->CallStaticVoidMethod(t.classID, t.methodID,level);
        }
    }
   
    
    void MobClickCpp::startLevel(const char *level){
        JniMethodInfo t;
        if (JniHelper::getStaticMethodInfo(t, JAVA_CLASS_UMGAMEAGENT,"startLevel", "(Ljava/lang/String;)V")){
            jstring le = t.env->NewStringUTF(level);
            t.env->CallStaticVoidMethod(t.classID, t.methodID,le);
            t.env->DeleteLocalRef(le);
        }
    }
    
    void MobClickCpp::finishLevel(const char *level){
        JniMethodInfo t;
        if (JniHelper::getStaticMethodInfo(t, JAVA_CLASS_UMGAMEAGENT,"finishLevel", "(Ljava/lang/String;)V")){
            jstring le = t.env->NewStringUTF(level);
            t.env->CallStaticVoidMethod(t.classID, t.methodID,le);
            t.env->DeleteLocalRef(le);
        }
    }
    
    void MobClickCpp::failLevel(const char *level){
        JniMethodInfo t;
        if (JniHelper::getStaticMethodInfo(t, JAVA_CLASS_UMGAMEAGENT,"failLevel", "(Ljava/lang/String;)V")){
            jstring le = t.env->NewStringUTF(level);
            t.env->CallStaticVoidMethod(t.classID, t.methodID,le);
            t.env->DeleteLocalRef(le);
        }
    }
    
    void MobClickCpp::pay(double cash, int source, double coin){
        JniMethodInfo t;
        if (JniHelper::getStaticMethodInfo(t, JAVA_CLASS_UMGAMEAGENT,"pay", "(DDI)V")){
            t.env->CallStaticVoidMethod(t.classID, t.methodID,cash,coin,source);
        }
    }
    
    void MobClickCpp::pay(double cash, int source, const char *item, int amount, double price){
        JniMethodInfo t;
        if (JniHelper::getStaticMethodInfo(t, JAVA_CLASS_UMGAMEAGENT,"pay", "(DLjava/lang/String;IDI)V")){
            jstring it = t.env->NewStringUTF(item);
            t.env->CallStaticVoidMethod(t.classID, t.methodID,cash,it,amount,price,source);
            t.env->DeleteLocalRef(it);
        }
    }
    
    void MobClickCpp::buy(const char *item, int amount, double price){
        JniMethodInfo t;
        if (JniHelper::getStaticMethodInfo(t, JAVA_CLASS_UMGAMEAGENT,"buy", "(Ljava/lang/String;ID)V")){
            jstring it = t.env->NewStringUTF(item);
            t.env->CallStaticVoidMethod(t.classID, t.methodID,it,amount,price);
            t.env->DeleteLocalRef(it);
        }
    }
    
    void MobClickCpp::use(const char *item, int amount, double price){
        JniMethodInfo t;
        if (JniHelper::getStaticMethodInfo(t, JAVA_CLASS_UMGAMEAGENT,"use", "(Ljava/lang/String;ID)V")){
            jstring it = t.env->NewStringUTF(item);
            t.env->CallStaticVoidMethod(t.classID, t.methodID,it,amount,price);
            t.env->DeleteLocalRef(it);
        }
    }
    
    void MobClickCpp::bonus(double coin, int source){
        JniMethodInfo t;
        if (JniHelper::getStaticMethodInfo(t, JAVA_CLASS_UMGAMEAGENT,"bonus", "(DI)V")){
            t.env->CallStaticVoidMethod(t.classID, t.methodID,coin,source);
        }
    }
    
    void MobClickCpp::bonus(const char *item, int amount, double price, int source){
        JniMethodInfo t;
        if (JniHelper::getStaticMethodInfo(t, JAVA_CLASS_UMGAMEAGENT,"bonus", "(Ljava/lang/String;IDI)V")){
            jstring it = t.env->NewStringUTF(item);
            t.env->CallStaticVoidMethod(t.classID, t.methodID,it,amount,price,source);
            t.env->DeleteLocalRef(it);
        }
    }
    
    void MobClickCpp::beginLogPageView(const char *pageName){
        JniMethodInfo t;
        if (JniHelper::getStaticMethodInfo(t, JAVA_CLASS_MOBCLICKAGENT,"onPageStart", "(Ljava/lang/String;)V")){
            jstring page = t.env->NewStringUTF(pageName);
            t.env->CallStaticVoidMethod(t.classID, t.methodID,page);
            t.env->DeleteLocalRef(page);
        }
    }
    
    void MobClickCpp::endLogPageView(const char *pageName){
        JniMethodInfo t;
        if (JniHelper::getStaticMethodInfo(t, JAVA_CLASS_MOBCLICKAGENT,"onPageEnd", "(Ljava/lang/String;)V")){
            jstring page = t.env->NewStringUTF(pageName);
            t.env->CallStaticVoidMethod(t.classID, t.methodID,page);
            t.env->DeleteLocalRef(page);
        }
    }
    
    void MobClickCpp::setEncryptEnabled(bool value) {
       JniMethodInfo t;
        if (JniHelper::getStaticMethodInfo(t, JAVA_CLASS_MOBCLICKAGENT,"enableEncrypt", "(Z)V")){
            t.env->CallStaticVoidMethod(t.classID, t.methodID,value);
        }
    }
    
    void MobClickCpp::profileSignIn(const char *puid, const char *provider) {
        JniMethodInfo t;
        if(provider == NULL){
            if (JniHelper::getStaticMethodInfo(t, JAVA_CLASS_MOBCLICKAGENT,"onProfileSignIn", "(Ljava/lang/String;)V")){
                jstring uid = t.env->NewStringUTF(puid);
                t.env->CallStaticVoidMethod(t.classID, t.methodID,uid);
                t.env->DeleteLocalRef(uid);
            }
        }else{
            if (JniHelper::getStaticMethodInfo(t, JAVA_CLASS_MOBCLICKAGENT,"onProfileSignIn", "(Ljava/lang/String;Ljava/lang/String;)V")){
                jstring uid = t.env->NewStringUTF(puid);
                jstring pro = t.env->NewStringUTF(provider);
                t.env->CallStaticVoidMethod(t.classID, t.methodID,uid,pro);
                t.env->DeleteLocalRef(uid);
                t.env->DeleteLocalRef(pro);
            }
        }
    }
    
    void MobClickCpp::profileSignOff() {
        JniMethodInfo t;
        if (JniHelper::getStaticMethodInfo(t, JAVA_CLASS_MOBCLICKAGENT,"onProfileSignOff", "()V")){
            t.env->CallStaticVoidMethod(t.classID, t.methodID);
        }
    }
    void MobClickCpp::exchange(const char *orderId, double currencyAmount, const char *currencyType,double virtualAmount,int channel) {
        JniMethodInfo t;
        if (JniHelper::getStaticMethodInfo(t, JAVA_CLASS_UMGAMEAGENT,"exchange", "(DLjava/lang/String;DILjava/lang/String;)V")){
            jstring oId = t.env->NewStringUTF(orderId);
            jstring cTp = t.env->NewStringUTF(currencyType);
            t.env->CallStaticVoidMethod(t.classID, t.methodID,currencyAmount,cTp,virtualAmount,channel,oId);
            t.env->DeleteLocalRef(oId);
            t.env->DeleteLocalRef(cTp);
        }
    }
    void MobClickCpp::setLatency(unsigned int latency) {
        JniMethodInfo t;
        if (JniHelper::getStaticMethodInfo(t,JAVA_CLASS_MOBCLICKAGENT,"setLatencyWindow", "(J)V")){
            t.env->CallStaticVoidMethod(t.classID,t.methodID,latency);
        }
    }
    void MobClickCpp::init() {
        //for iOS
    }
}
