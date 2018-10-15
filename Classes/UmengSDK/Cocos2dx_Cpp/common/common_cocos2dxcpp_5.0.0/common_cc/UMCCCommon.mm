#include "UMCCCommon.h"
#include <UMCommon/UMConfigure.h>
#include "MobClickCpp.h"




static  NSString* getNSStringFromCString(const char* cstr){
    if (cstr) {
        return [NSString stringWithUTF8String:cstr];
    }
    return nil;
}
void UMCCCommon::setLogEnabled(bool value){
    BOOL valTmp = value?YES:NO;
    [UMConfigure setLogEnabled:valTmp];
}
void UMCCCommon::init(const char *appkey, const char *channel){
    SEL sel = NSSelectorFromString(@"setWraperType:wrapperVersion:");
    if ([UMConfigure respondsToSelector:sel]) {
        [UMConfigure performSelector:sel withObject:@WRAP_TYPE withObject:@VERSION];
    }
    [UMConfigure initWithAppkey:getNSStringFromCString(appkey) channel:getNSStringFromCString(channel)];
}
    

