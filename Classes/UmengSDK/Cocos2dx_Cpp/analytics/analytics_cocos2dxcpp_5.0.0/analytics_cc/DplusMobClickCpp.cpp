#include "DplusMobClickCpp.h"
#include <jni/JniHelper.h>
#include <jni.h>
using namespace std;


#ifndef JAVA_CLASS_UMGAMEANALYTICS
#define JAVA_CLASS_UMGAMEANALYTICS              "com/umeng/analytics/UMGameAnalytics"
#endif

USING_NS_CC;

extern "C" jobject createJavaMapObject(JNIEnv *env, std::map<std::string, std::string>* map);

static string jstring2str(JNIEnv* env, jstring jstr)
{   
    char*   rtn   =   NULL;   
    jclass   clsstring   =   env->FindClass("java/lang/String");   
    jstring   strencode   =   env->NewStringUTF("GB2312");   
    jmethodID   mid   =   env->GetMethodID(clsstring,   "getBytes",   "(Ljava/lang/String;)[B");   
    jbyteArray   barr=   (jbyteArray)env->CallObjectMethod(jstr,mid,strencode);   
    jsize   alen   =   env->GetArrayLength(barr);   
    jbyte*   ba   =   env->GetByteArrayElements(barr,JNI_FALSE);   
    if(alen   >   0)   
    {   
        rtn   =   (char*)malloc(alen+1);         
        memcpy(rtn,ba,alen);   
        rtn[alen]=0;   
    }   
    env->ReleaseByteArrayElements(barr,ba,0);   
    std::string stemp(rtn);
    free(rtn);
    return   stemp;   
}   

static jobjectArray createJavaArrayObject(JNIEnv* env, std::vector<std::string>* cStrVector){
    
    jclass objClass = env->FindClass("java/lang/String");
    jobjectArray aStr= env->NewObjectArray((jsize)cStrVector->size(), objClass, 0);
    jstring jstr;
     int i=0;
     for(;i<cStrVector->size();i++)
      {
        jstr = env->NewStringUTF(cStrVector->at(i).c_str());
        env->SetObjectArrayElement(aStr, i, jstr);//必须放入jstring
     }
     return aStr;
}

namespace umeng {
    void DplusMobClickCpp::track(const char * eventName, eventDict* property){
        JniMethodInfo t;
        if(property){
            if (JniHelper::getStaticMethodInfo(t, JAVA_CLASS_UMGAMEANALYTICS, "track", "(Ljava/lang/String;Ljava/util/Map;)V")){
                jstring eName = t.env->NewStringUTF(eventName);
                jobject jparamMap = createJavaMapObject(t.env, property);
                t.env->CallStaticVoidMethod(t.classID, t.methodID,eName,jparamMap);
                t.env->DeleteLocalRef(eName);
                t.env->DeleteLocalRef(jparamMap);
            }
        }else{
            if (JniHelper::getStaticMethodInfo(t, JAVA_CLASS_UMGAMEANALYTICS, "track", "(Ljava/lang/String;)V")){
                jstring eName = t.env->NewStringUTF(eventName);
                t.env->CallStaticVoidMethod(t.classID, t.methodID,eName);
                t.env->DeleteLocalRef(eName);
            }
        }
    }
    void DplusMobClickCpp::registerSuperProperty(eventDict* property){
        JniMethodInfo t;
        if (JniHelper::getStaticMethodInfo(t, JAVA_CLASS_UMGAMEANALYTICS, "registerSuperProperty", "(Ljava/util/Map;)V")){
            jobject jparamMap = createJavaMapObject(t.env, property);
            t.env->CallStaticVoidMethod(t.classID, t.methodID,jparamMap);
            t.env->DeleteLocalRef(jparamMap);
        }
    }
    void DplusMobClickCpp::unregisterSuperProperty(const char* propertyName){
        JniMethodInfo t;
        if (JniHelper::getStaticMethodInfo(t, JAVA_CLASS_UMGAMEANALYTICS, "unregisterSuperProperty", "(Ljava/lang/String;)V")){
            jstring eName = t.env->NewStringUTF(propertyName);
            t.env->CallStaticVoidMethod(t.classID, t.methodID,eName);
            t.env->DeleteLocalRef(eName);
        }
        
    }
    string DplusMobClickCpp::getSuperProperty(const char* propertyName){
        JniMethodInfo t;
        if (JniHelper::getStaticMethodInfo(t, JAVA_CLASS_UMGAMEANALYTICS, "getSuperProperty", "(Ljava/lang/String;)Ljava/lang/String;")){
            jstring eName = t.env->NewStringUTF(propertyName);
            jstring jstr = (jstring)t.env->CallStaticObjectMethod(t.classID, t.methodID,eName);
            t.env->DeleteLocalRef(eName);
            return jstring2str(t.env,jstr);
        }
        return NULL;
    }
    string DplusMobClickCpp::getSuperProperties(){
        JniMethodInfo t;
        if (JniHelper::getStaticMethodInfo(t, JAVA_CLASS_UMGAMEANALYTICS, "getSuperProperties", "()Ljava/lang/String;")){
            jstring jstr = (jstring)t.env->CallStaticObjectMethod(t.classID, t.methodID);
            return jstring2str(t.env,jstr);
        }
        return NULL;
    }
    void DplusMobClickCpp::clearSuperProperties(){
        JniMethodInfo t;
        if (JniHelper::getStaticMethodInfo(t, JAVA_CLASS_UMGAMEANALYTICS, "clearSuperProperties", "()V")){
            t.env->CallStaticVoidMethod(t.classID, t.methodID);
        }
    }
        
    void DplusMobClickCpp::setFirstLaunchEvent(std::vector<std::string>* eventIdList){
         if(eventIdList->size()>0){
            JniMethodInfo t;
            
            if (JniHelper::getStaticMethodInfo(t, JAVA_CLASS_UMGAMEANALYTICS, "setFirstLaunchEvent", "([Ljava/lang/String;)V")){
                jobjectArray aStr = createJavaArrayObject(t.env,eventIdList);
                t.env->CallStaticVoidMethod(t.classID, t.methodID,aStr);
            }
        }
    }
}
