/**
 * FileName : CCUMScoialSDK.cpp
 * Author   : hehonghui
 * Company  : umeng.com
 * 该类为友盟社会化组件的Cocos2d-x版本，在友盟社会化组件Android、iOS原生SDK上进行适配，支持打开分享面板分享、直接分享、授权某平台、删除某平台授权、判断某平台是否授权这几个核心功能。
 *
 * Android 平台实现的代码参考UmengSocial/Android目录下的实现, IOS平台的参考UmengSocial/IOS目录下的实现。
 *
 */

#include "CCUMSocialSDK.h"
#include <platform/CCCommon.h>
//#include <platform/CCPlatformConfig.h>
//#include <platform/CCPlatformMacros.h>
#include <stddef.h>
//#include <vector>



USING_NS_CC;
using namespace std;

AuthEventHandler authCallback = NULL;
ShareEventHandler shareCallback = NULL;
BoardEventHandler boardCallback = NULL;
BoardDismissEventHandler boardDismissCallback = NULL;


 extern "C"{
 	static bool getMethod(JniMethodInfo &mi, const char *methodName,
		const char *signature) {
	return JniHelper::getStaticMethodInfo(mi,
			"com/umeng/social/CCUMSocialController", methodName, signature);
}

static void getData(JNIEnv *env, jobjectArray data,jobjectArray key, map<string, string>& outputMap) {
	jsize count = env->GetArrayLength(data);

	for(int i=0;i<env->GetArrayLength(data);i++){
		jsize temp = i;
		jstring jkey = (jstring) env->GetObjectArrayElement(key, temp);
		jstring value = (jstring) env->GetObjectArrayElement(data,temp);
		if(jkey == NULL ||value == NULL){
			continue;
		}

		const char* pkey = env->GetStringUTFChars(jkey, NULL);
		const char* pvalue = env->GetStringUTFChars(value, NULL);
		outputMap.insert(make_pair( pkey, pvalue));
	}

}
static void releaseMethod(JniMethodInfo &mi) {
	mi.env->DeleteLocalRef(mi.classID);
}

JNIEXPORT void JNICALL Java_com_umeng_social_CCUMSocialController_OnAuthorizeComplete(
		JNIEnv *env, jclass clz, jint platform, jint stCode,
		jobjectArray data,jobjectArray key) {
	if (authCallback != NULL) {
		map<string, string> dataMap;
		// 获取数据
		getData(env, data, key,dataMap);
		authCallback(platform, stCode, dataMap);
	}

}


JNIEXPORT void JNICALL Java_com_umeng_social_CCUMSocialController_OnBoard(
		JNIEnv *env, jclass clz, jint platform) {
	if (boardCallback != NULL) {
		// 参数1代表平台, 参数2代表状态, 比如start, cancel, complete, 参数3代表状态码, 200为成功.
		boardCallback(platform);

	}
}

JNIEXPORT void JNICALL Java_com_umeng_social_CCUMSocialController_OnBoardDismiss(
		JNIEnv *env, jclass clz) {
	if (boardDismissCallback != NULL) {

		boardDismissCallback();

	}
}

JNIEXPORT void JNICALL Java_com_umeng_social_CCUMSocialController_OnShareComplete(
		JNIEnv *env, jclass clz, jint platform, jint stCode,
		jstring descriptor) {
	if (shareCallback != NULL) {
		shareCallback(platform, stCode, "");
	}
}
}

namespace umeng{
void CCUMSocialSDK::authorize(int platform, AuthEventHandler callback){
	 	authCallback = callback;
	if (authCallback != NULL) {
		CCLog("#### 授权回调不为NULL");

	}
	JniMethodInfo mi;
	bool isHave = getMethod(mi, "doAuthorize", "(I)V");
	if (isHave) {
		mi.env->CallStaticVoidMethod(mi.classID, mi.methodID, platform);
		releaseMethod(mi);
	}
}

void CCUMSocialSDK::deleteAuthorization(int platform, AuthEventHandler callback){
	authCallback = callback;
	JniMethodInfo mi;
	bool isHave = getMethod(mi, "deleteAuthorization", "(I)V");
	if (isHave) {
		mi.env->CallStaticVoidMethod(mi.classID, mi.methodID, platform);
		releaseMethod(mi);
	}
}

void CCUMSocialSDK::openShare(vector<int>* platforms,const char* text, const char* title,const char* imgName,const char* targeturl,ShareEventHandler callback){
	shareCallback = callback;
	if (shareCallback != NULL) {
		CCLog("#### 分享回调不为NULL");

	}
	JniMethodInfo mi;
	bool isHave = getMethod(mi, "openShare", "([ILjava/lang/String;Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;)V");
	int* platformArr = platforms->data();
	int length = platforms->size();

	// 创建数组对象,且不能在函数末尾删除引用
	jintArray iArr = mi.env->NewIntArray(length);
	// 将nums数组中的内容设置到jintArray对象中,
	mi.env->SetIntArrayRegion(iArr, 0, length, platformArr);
	if (isHave) {
		jstring text_content = mi.env->NewStringUTF(text);
						jstring image = mi.env->NewStringUTF(imgName);
						jstring share_title = mi.env->NewStringUTF(title);
						jstring share_target_url = mi.env->NewStringUTF(targeturl);
		mi.env->CallStaticVoidMethod(mi.classID, mi.methodID,iArr,text_content,share_title,share_target_url,image);
		releaseMethod(mi);
	}
}

void CCUMSocialSDK:: openCustomShare(vector<int>* platforms,BoardEventHandler callback){
	boardCallback = callback;
	if (boardCallback != NULL) {
		CCLog("#### 分享回调不为NULL");

	}
	JniMethodInfo mi;
	bool isHave = getMethod(mi, "openCustomShare", "([I)V");
	int* platformArr = platforms->data();
	int length = platforms->size();

	// 创建数组对象,且不能在函数末尾删除引用
	jintArray iArr = mi.env->NewIntArray(length);
	// 将nums数组中的内容设置到jintArray对象中,
	mi.env->SetIntArrayRegion(iArr, 0, length, platformArr);
	if (isHave) {

		mi.env->CallStaticVoidMethod(mi.classID, mi.methodID,iArr);
		releaseMethod(mi);
	}
}
void CCUMSocialSDK:: setBoardDismissCallback(BoardDismissEventHandler callback){
	boardDismissCallback = callback;
	JniMethodInfo mi;
	bool isHave = getMethod(mi, "setDismissCallback", "()V");
	if (isHave) {

			mi.env->CallStaticVoidMethod(mi.classID, mi.methodID);
			releaseMethod(mi);
		}
}
void CCUMSocialSDK:: getPlatformInfo(int platforms,AuthEventHandler callback){
	JniMethodInfo mi;
	authCallback = callback;
	bool isHave = getMethod(mi, "getplatformInfo", "(I)V");
	jboolean isAuthorized = false;
	if (isHave) {
		 mi.env->CallStaticVoidMethod(mi.classID, mi.methodID,
				platforms);
		releaseMethod(mi);
	}
}
void CCUMSocialSDK:: directShare(int platform, const char* text,const char* title,const char* targeturl,
			const char* imgName, ShareEventHandler callback){
	shareCallback = callback;
	if (shareCallback != NULL) {
		CCLog("#### 授权回调不为NULL");

	}
	JniMethodInfo mi;
	bool isHave = getMethod(mi, "directShare", "(ILjava/lang/String;Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;)V");
	if (isHave) {
		jstring text_content = mi.env->NewStringUTF(text);
				jstring image = mi.env->NewStringUTF(imgName);
				jstring share_title = mi.env->NewStringUTF(title);
				jstring share_target_url = mi.env->NewStringUTF(targeturl);
				mi.env->CallStaticVoidMethod(mi.classID, mi.methodID, platform,
								text_content,share_title,share_target_url,image);
//		mi.env->CallStaticVoidMethod(mi.classID, mi.methodID, platform);
				mi.env->DeleteLocalRef(text_content);
				mi.env->DeleteLocalRef(image);
				mi.env->DeleteLocalRef(share_title);
				mi.env->DeleteLocalRef(share_target_url);
		releaseMethod(mi);
	}
}
}
