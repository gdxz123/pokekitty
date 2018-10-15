#include "MobClickCpp.h"
#include <UMCommon/UMConfigure.h>
#include <UMAnalytics/MobClick.h>
#include <UMAnalytics/DplusMobClick.h>

#include <UMAnalytics/MobClickGameAnalytics.h>

#define UMENG_SDK_WRAPPER_TYPE                      @"Cocos2d-x"
#define UMENG_SDK_WRAPPER_VERSION                   @"4.7.1"

namespace umeng {
    
    void MobClickCpp::setCheckDevice(bool value){
       
    }
    void MobClickCpp::setSessionIdleLimit(int seconds){
       
    }
    void MobClickCpp::setLogEnabled(bool value){
        BOOL valTmp = value?YES:NO;
        [UMConfigure setLogEnabled:valTmp];
    }
    void MobClickCpp::setEncryptEnabled(bool value){
        BOOL valTmp = value?YES:NO;
        [UMConfigure setEncryptEnabled:valTmp];
    }
    void MobClickCpp::init(void){
        [MobClick setScenarioType:(eScenarioType)(E_UM_GAME|E_UM_DPLUS)]; // 仅适用于游戏场景
    }
    void MobClickCpp::event(const char * eventId, const char * label){
        if(label){
            [MobClick event:[NSString stringWithUTF8String:eventId] label:[NSString stringWithUTF8String:label]];
        }else{
            [MobClick event:[NSString stringWithUTF8String:eventId]];
        }
    }
    void MobClickCpp::event(const char * eventId, eventDict * attributes, int counter){
        NSMutableDictionary *dict = [[NSMutableDictionary alloc] init];
        eventDict::iterator it;
        for(it=attributes->begin();it!=attributes->end();++it)
        {
            NSString* key = [NSString stringWithUTF8String:it->first.c_str()];
            NSString* obj = [NSString stringWithUTF8String:it->second.c_str()];
            [dict setObject:obj forKey:key];
        }
        NSString* eId = [NSString stringWithUTF8String:eventId];
        [MobClick event:eId attributes:dict counter:counter];
        [dict release];
    }
        
    void MobClickCpp::event(const char * eventId, eventDict * attributes){
        NSMutableDictionary *dict = [[NSMutableDictionary alloc] init];
        eventDict::iterator it;
        for(it=attributes->begin();it!=attributes->end();++it)
        {
            NSString* key = [NSString stringWithUTF8String:it->first.c_str()];
            NSString* obj = [NSString stringWithUTF8String:it->second.c_str()];
            [dict setObject:obj forKey:key];
        }
        NSString* eId = [NSString stringWithUTF8String:eventId];
        [MobClick event:eId attributes:dict];
        [dict release];
    }
    void MobClickCpp::beginLogPageView(const char *pageName){
        NSString* name = [NSString stringWithUTF8String:pageName];
        [MobClick beginLogPageView:name];
    }
    void MobClickCpp::endLogPageView(const char *pageName){
        NSString* name = [NSString stringWithUTF8String:pageName];
        [MobClick endLogPageView:name];
    }
    void MobClickCpp::profileSignIn(const char * puid, const char * provider){
        NSString* uid = [NSString stringWithUTF8String:puid];
        if(provider){
            NSString* pro = [NSString stringWithUTF8String:provider];
            [MobClick profileSignInWithPUID:uid provider:pro];
        }else{
            [MobClick profileSignInWithPUID:uid];
        }
    }
    
    void MobClickCpp::profileSignOff(){
        [MobClick profileSignOff];
    }
    void MobClickCpp::setUserLevel(int level){
        [MobClickGameAnalytics setUserLevelId:level];
    }
    void MobClickCpp::startLevel(const char * level){
        [MobClickGameAnalytics startLevel:[NSString stringWithUTF8String:level]];
    }
    void MobClickCpp::finishLevel(const char * level){
        [MobClickGameAnalytics finishLevel:[NSString stringWithUTF8String:level]];
    }
    
    void MobClickCpp::failLevel(const char * level){
        [MobClickGameAnalytics failLevel:[NSString stringWithUTF8String:level]];
    }
    
    void MobClickCpp::pay(double cash, int src, double co){
        [MobClickGameAnalytics pay:cash source:src coin:co];
    }
    
    void MobClickCpp::pay(double cash, int src, const char * item, int am, double pr){
        NSString* it = [NSString stringWithUTF8String:item];
        [MobClickGameAnalytics pay:cash source:src item:it amount:am price:pr];
    }
    
    void MobClickCpp::buy(const char *item, int am, double pr){
        NSString* it = [NSString stringWithUTF8String:item];
        [MobClickGameAnalytics buy:it amount:am price:pr];
    }
    
    void MobClickCpp::use(const char * item, int am, double pr){
        NSString* it = [NSString stringWithUTF8String:item];
        [MobClickGameAnalytics use:it amount:am price:pr];
    }
    void MobClickCpp::bonus(double coin, int src){
        [MobClickGameAnalytics bonus:coin source:src];
    }
    void MobClickCpp::bonus(const char * item, int am, double pr, int src){
        NSString* it = [NSString stringWithUTF8String:item];
        [MobClickGameAnalytics bonus:it amount:am price:pr source:src];
    }
    void MobClickCpp::exchange(const char *orderId, double currencyAmount, const char *currencyType,double virtualAmount,int channel){
        NSString* oId = [NSString stringWithUTF8String:orderId];
        NSString* cTy = [NSString stringWithUTF8String:currencyType];
        [MobClickGameAnalytics exchange:oId currencyAmount:currencyAmount currencyType:cTy virtualCurrencyAmount:virtualAmount paychannel:channel];
    }
    void MobClickCpp::setLatency(unsigned int latency){
    }
}
