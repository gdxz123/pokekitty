//
//  UmSocialControllerIOS.cpp
//  UmengGame
//
//  Created by 张梓琦 on 14-3-16.
//
//

#include "CCUMSocialSDK.h"
#import <UIKit/UIKit.h>
#import <UShareUI/UShareUI.h>

//#import "UMSocialTencentWeiboHandler.h"

#define UMSYSTEM_VERSION_GREATER_THAN_OR_EQUAL_TO(v)  ([[[UIDevice currentDevice] systemVersion] compare:v options:NSNumericSearch] != NSOrderedAscending)
int const platformlength = 34;
@interface UMSocialBriage :NSObject<UMSocialShareMenuViewDelegate>
{
@public BoardDismissEventHandler callback;
}

+ (UMSocialBriage *)defaultManage;

@end
@implementation UMSocialBriage
+ (UMSocialBriage *)defaultManager
{
    static UMSocialBriage *instance = nil;
    static dispatch_once_t onceToken;
    dispatch_once(&onceToken, ^{
        if (!instance) {
            instance = [[self alloc] init];
        }
    });
    return instance;
}
- (void)UMSocialShareMenuViewDidDisappear
{
    callback();
}
@end
//UMSocialUIDelegateObject * UmSocialControllerIOS::m_socialDelegate = nil;
UMSocialPlatformType const platforms[platformlength] = {
    UMSocialPlatformType_QQ
    , UMSocialPlatformType_Sina
    , UMSocialPlatformType_WechatSession
    , UMSocialPlatformType_WechatTimeLine
    , UMSocialPlatformType_Qzone
    , UMSocialPlatformType_Email
    , UMSocialPlatformType_Sms
    , UMSocialPlatformType_Facebook
    , UMSocialPlatformType_Twitter
    , UMSocialPlatformType_WechatFavorite
    , UMSocialPlatformType_GooglePlus
    , UMSocialPlatformType_Renren
    , UMSocialPlatformType_TencentWb
    , UMSocialPlatformType_Douban
    , UMSocialPlatformType_FaceBookMessenger
    , UMSocialPlatformType_YixinSession
    , UMSocialPlatformType_YixinTimeLine
    , UMSocialPlatformType_Instagram
    , UMSocialPlatformType_Pinterest
    , UMSocialPlatformType_EverNote
    , UMSocialPlatformType_Pocket
    , UMSocialPlatformType_Linkedin
    , UMSocialPlatformType_UnKnown
    , UMSocialPlatformType_YouDaoNote
    , UMSocialPlatformType_Whatsapp
    , UMSocialPlatformType_Linkedin
    , UMSocialPlatformType_Flickr
    , UMSocialPlatformType_Tumblr
    , UMSocialPlatformType_AlipaySession
    , UMSocialPlatformType_KakaoTalk
    , UMSocialPlatformType_DropBox
    , UMSocialPlatformType_VKontakte
    , UMSocialPlatformType_DingDing
    , UMSocialPlatformType_UnKnown
   
};

UMSocialPlatformType getPlatformString(int platform){
    
    return platforms[platform];
}
int getPlatformself(int platform){
    for (int i = 0 ; i<platformlength; i++) {
        if (platform == platforms[i]) {
            return i;
        }
    }
    return -1;
}
NSString* getNSStringFromCString(const char* cstr){
    if (cstr) {
        return [NSString stringWithUTF8String:cstr];
    }
    return nil;
}

UIViewController* getViewController(){
    UIViewController* ctrol = nil;
    if ( [[UIDevice currentDevice].systemVersion floatValue] < 6.0)
    {
        // warning: addSubView doesn't work on iOS6
        NSArray* array=[[UIApplication sharedApplication]windows];
        UIWindow* win=[array objectAtIndex:0];
        
        UIView* ui=[[win subviews] objectAtIndex:0];
        ctrol=(UIViewController*)[ui nextResponder];
    }
    else
    {
        // use this method on ios6
        ctrol=[UIApplication sharedApplication].keyWindow.rootViewController;
    }
    return ctrol;
}









string asserstring(NSString* str){
    if (str == nil || str.length == 0) {
        return "nil";
    }else{
        return  string([str UTF8String]);
    }
}

UIImage * formatImage(id image) {
    UIImage *retImage = image;
    if ([image isKindOfClass:[UIImage class]]) {
        retImage = [UIImage imageWithData:UIImagePNGRepresentation(image)];
    } else if ([image isKindOfClass:[NSData class]]) {
        retImage = [UIImage imageWithData:image];
    }
    return retImage;
}




namespace umeng {
void CCUMSocialSDK::getPlatformInfo(int platform, AuthEventHandler callback){
    [[UMSocialManager defaultManager]  getUserInfoWithPlatform:getPlatformString(platform) currentViewController:getViewController() completion:^(id result, NSError *error) {
        NSString *message = nil;
        int code = 200;
        map<string,string> loginData;
        if (error) {
            NSLog(@"get fail with error %@", error);
            message = @"Auth fail";
            code = error.code;
            loginData.insert(pair<string, string>("message",  asserstring(message)));
        }else{
            if ([result isKindOfClass:[UMSocialUserInfoResponse class]]) {
                UMSocialUserInfoResponse *resp = result;
                // 授权信息
                if (resp.uid) {
                    loginData.insert(pair<string, string>("uid", asserstring(resp.uid)));
                }
                
                if (resp.accessToken) {
                    loginData.insert(pair<string, string>("accessToken",asserstring(resp.accessToken)));
                }
                
                if (resp.refreshToken) {
                    loginData.insert(pair<string, string>("refreshToken", asserstring(resp.refreshToken)));
                }
                
                if (resp.name) {
                    loginData.insert(pair<string, string>("name", asserstring(resp.name)));
                }
                
                if (resp.iconurl) {
                    loginData.insert(pair<string, string>("iconurl", asserstring(resp.iconurl)));
                }
                
                if (resp.gender) {
                    loginData.insert(pair<string, string>("gender",asserstring(resp.gender)));
                }
                
            }
            else{
                NSLog(@"Auth fail with unknow error");
                loginData.insert(pair<string, string>("message",  "get fail with unknow error"));
            }
        }
        callback(platform, code,loginData);
    }];

}




void CCUMSocialSDK::authorize(int platform, AuthEventHandler callback){
    [[UMSocialManager defaultManager]  authWithPlatform:getPlatformString(platform) currentViewController:getViewController() completion:^(id result, NSError *error) {
        NSString *message = nil;
        NSInteger code = 200;
        map<string,string> loginData;
        if (error) {
            NSLog(@"Auth fail with error %@", error);
            message = @"Auth fail";
            if (error.code == 2009) {
                code = -1;
            } else {
                code = error.code;
            }
            loginData.insert(pair<string, string>("message", asserstring(message)));
        }else{
            if ([result isKindOfClass:[UMSocialAuthResponse class]]) {
                UMSocialAuthResponse *resp = result;
                // 授权信息
                if (resp.uid) {
                    loginData.insert(pair<string, string>("uid",asserstring(resp.uid)));
                }
                
                if (resp.accessToken) {
                    loginData.insert(pair<string, string>("accessToken",asserstring(resp.accessToken) ));
                }

                if (resp.refreshToken) {
                    loginData.insert(pair<string, string>("refreshToken",asserstring(resp.refreshToken)));
                }
            }
            else{
                NSLog(@"Auth fail with unknow error");
                loginData.insert(pair<string, string>("message",  "Auth fail with unknow error"));
            }
        }
        callback(platform, code,loginData);
    }];
  
}

void CCUMSocialSDK::deleteAuthorization(int platform, AuthEventHandler callback){
    [[UMSocialManager defaultManager] cancelAuthWithPlatform:getPlatformString(platform) completion:^(id result, NSError *error) {
          map<string,string> loginData;
        if (!error) {
            loginData.insert(pair<string, string>("message",  "success"));
 
            callback(platform, 200,loginData);
        }else {
            loginData.insert(pair<string, string>("message",  "fail"));
            
            callback(platform, -1,loginData);
        }
        
    }];
}
void CCUMSocialSDK::setBoardDismissCallback(BoardDismissEventHandler callback){
    
    [UMSocialUIManager setShareMenuViewDelegate:[UMSocialBriage defaultManager]];
    [UMSocialBriage defaultManager]->callback = callback;
}

id getUIImageFromFilePath(const char* imagePath){
    id returnImage = nil;
    if (imagePath) {
        NSString *imageString = getNSStringFromCString(imagePath);
        
        if ([imageString hasPrefix:@"http"]) {
            returnImage = imageString;
        }else{
            returnImage = [UIImage imageNamed:imageString];
        }
        
    }
    return returnImage;
}
 void CCUMSocialSDK::openCustomShare(vector<int>* platform, BoardEventHandler callback){
     NSMutableArray *arr = [NSMutableArray arrayWithCapacity:platform->size()];
     for (int i:*platform) {
         
         int d = i;
         UMSocialPlatformType type = getPlatformString(d);
         [arr addObject:@(type)];
         
     }
     [UMSocialUIManager showShareMenuViewInWindowWithPlatformSelectionBlock:^(UMSocialPlatformType platformType, NSDictionary *userInfo) {
         callback(getPlatformself(platformType));
     }];
}
void CCUMSocialSDK::openShare(vector<int>* platform, const char* text, const char* title,const char* imagePath,const char* targeturl,ShareEventHandler callback){
    NSMutableArray *arr = [NSMutableArray arrayWithCapacity:platform->size()];
    for (int i:*platform) {
        
        int d = i;
         UMSocialPlatformType type = getPlatformString(d);
          [arr addObject:@(type)];
        
    }
    
    [UMSocialUIManager setPreDefinePlatforms:[arr copy]];
    
    
    
       id image = nil;
    image = getUIImageFromFilePath(imagePath);
    UMSocialMessageObject *messageObject = [UMSocialMessageObject messageObject];
    if (targeturl==NULL) {
        if (image==nil) {
            
            messageObject.text =  [NSString stringWithUTF8String:text];
        }else{
            UMShareImageObject *shareObject = [[UMShareImageObject alloc] init];
            [shareObject setShareImage:image];
            messageObject.shareObject = shareObject;
        }
    }else{
        messageObject.text = [NSString stringWithUTF8String:text];
        UMShareWebpageObject *shareObject = [UMShareWebpageObject shareObjectWithTitle:[NSString stringWithUTF8String:title] descr:[NSString stringWithUTF8String:text] thumImage:image];
        //设置网页地址
        shareObject.webpageUrl =[NSString stringWithUTF8String:targeturl];
        
        //分享消息对象设置分享内容对象
        messageObject.shareObject = shareObject;
        
        
    }

   
    [UMSocialUIManager showShareMenuViewInWindowWithPlatformSelectionBlock:^(UMSocialPlatformType platformType, NSDictionary *userInfo) {
        
        [[UMSocialManager defaultManager] shareToPlatform:platformType messageObject:messageObject currentViewController:getViewController() completion:^(id data, NSError *error) {
            int code;
            NSString* message;
            if (error) {
                code = (int)error.code;
                if (error.code == 2009) {
                    code = -1;
                }
                NSLog(@"************Share fail with error %@*********",error);
                message =@"************Share fail with error %@*********";
            }else{
                code = 200;
                if ([data isKindOfClass:[UMSocialShareResponse class]]) {
                    UMSocialShareResponse *resp = data;
                    //分享结果消息
                    NSLog(@"response message is %@",resp.message);
                    //第三方原始返回的数据
                    NSLog(@"response originalResponse data is %@",resp.originalResponse);
                    code = 200;
                    message =@"success";
                }else{
                    NSLog(@"response data is %@",data);
                    message =@"unkonw fail";
                }
            }
            callback(getPlatformself(platformType), code,string([message UTF8String]));
            
        }];
        
    }];
    
  }





void CCUMSocialSDK::directShare( int platform,const char* text, const char* title, const char* targeturl,const char* imagePath, ShareEventHandler callback){
    id image = nil;
    NSString* nstargeturl = [NSString stringWithUTF8String:targeturl];
    NSString* nstext = [NSString stringWithUTF8String:text];
    NSString* nstitle = [NSString stringWithUTF8String:title];
    
    image = getUIImageFromFilePath(imagePath);
    UMSocialMessageObject *messageObject = [UMSocialMessageObject messageObject];
    if (nstargeturl==nil||nstargeturl.length==0) {
        if (image==nil) {
            
            messageObject.text =  nstext;
        }else{
            UMShareImageObject *shareObject = [[UMShareImageObject alloc] init];
            [shareObject setShareImage:image];
            messageObject.shareObject = shareObject;
        }
    }else{
        messageObject.text = [NSString stringWithUTF8String:text];
        UMShareWebpageObject *shareObject = [UMShareWebpageObject shareObjectWithTitle:nstitle descr:[NSString stringWithUTF8String:text] thumImage:image];
        //设置网页地址
        shareObject.webpageUrl =nstargeturl;
        
        //分享消息对象设置分享内容对象
        messageObject.shareObject = shareObject;
        
        
    }
    [[UMSocialManager defaultManager] shareToPlatform:getPlatformString(platform) messageObject:messageObject currentViewController:getViewController() completion:^(id data, NSError *error) {
        int code;
        NSString* message;
        if (error) {
            code = error.code;
            if (error.code == 2009) {
                code = -1;
            }
            NSLog(@"************Share fail with error %@*********",error);
            message =@"************Share fail with error %@*********";
        }else{
            code = 200;
            if ([data isKindOfClass:[UMSocialShareResponse class]]) {
                UMSocialShareResponse *resp = data;
                //分享结果消息
                NSLog(@"response message is %@",resp.message);
                //第三方原始返回的数据
                NSLog(@"response originalResponse data is %@",resp.originalResponse);
                code = 200;
                message =@"success";
            }else{
                NSLog(@"response data is %@",data);
                message =@"unkonw fail";
            }
        }
        callback(platform, code,asserstring(message));
        
    }];
}
}
