/*
 * FileName : CCUMScoialSDK.h
 * Author   : hehonghui
 * Company  : umeng.com
 *
 */

#ifndef __CCUMSOCIALSDK__
#define __CCUMSOCIALSDK__

#include "cocos2d.h"

#include <vector>


using namespace std;

enum Platform {
    QQ = 0,
    SINA = 1,
    WEIXIN = 2,
    WEIXIN_CIRCLE = 3,
    QZONE = 4,
    EMAIL = 5,
    SMS = 6,
    FACEBOOK = 7,
    TWITTER = 8,
    WEIXIN_FAVORITE = 9,
    GOOGLEPLUS = 10,
    RENREN = 11,
    TENCENT = 12,
    DOUBAN = 13,
    FACEBOOK_MESSAGER = 14,
    YIXIN = 15,
    YIXIN_CIRCLE = 16,
    INSTAGRAM = 17,
    PINTEREST = 18,
    EVERNOTE = 19,
    POCKET = 20,
    LINKEDIN = 21,
    FOURSQUARE = 22,
    YNOTE = 23,
    WHATSAPP = 24,
    LINE = 25,
    FLICKR = 26,
    TUMBLR = 27,
    ALIPAY = 28,
    KAKAO = 29,
    DROPBOX = 30,
    VKONTAKTE = 31,
    DINGTALK = 32,
    MORE = 33
	
};


typedef void (*AuthEventHandler)(int platform, int stCode,
		const map<string, string>& data);

    typedef void (*ShareEventHandler)(int platform, int stCode,
    const string& errorMsg);

typedef void (*BoardEventHandler)(int platform);
typedef void (*BoardDismissEventHandler)();
#define auth_selector(_SELECTOR) (AuthEventHandler)(&_SELECTOR)
#define share_selector(_SELECTOR) (ShareEventHandler)(&_SELECTOR)
#define board_selector(_SELECTOR) (BoardEventHandler)(&_SELECTOR)
#define boarddismiss_selector(_SELECTOR) (BoardDismissEventHandler)(&_SELECTOR)

namespace umeng {
    class CCUMSocialSDK {

    public:
        static void authorize(int platform, AuthEventHandler callback);
        static void deleteAuthorization(int platform, AuthEventHandler callback);
        static void openShare(vector<int>* platforms,const char* text, const char* title,const char* imgName,const char* targeturl,ShareEventHandler callback);
        static void openCustomShare(vector<int>* platforms,BoardEventHandler callback);
        static void setBoardDismissCallback(BoardDismissEventHandler callback);
        static void getPlatformInfo(int platforms,AuthEventHandler callback);
	
        static void directShare(int platform, const char* text,const char* title,const char* targeturl,
			const char* imgName, ShareEventHandler callback);

	

    };
}
#endif
