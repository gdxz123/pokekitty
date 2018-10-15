#include "DplusMobClickCpp.h"
#import <UMAnalytics/DplusMobClick.h>

namespace umeng {
    
    void DplusMobClickCpp::track(const char * eventName, eventDict* property){
        if(property){
            NSMutableDictionary *dict = [[NSMutableDictionary alloc] init];
            eventDict::iterator it;
            for(it=property->begin();it!=property->end();++it)
            {
                NSString* key = [NSString stringWithUTF8String:it->first.c_str()];
                NSString* obj = [NSString stringWithUTF8String:it->second.c_str()];
                [dict setObject:obj forKey:key];
            }
            NSString* eName = [NSString stringWithUTF8String:eventName];
            [DplusMobClick track:eName property:dict];
            [dict release];
        }else{
            [DplusMobClick track:[NSString stringWithUTF8String:eventName]];
        }
    }
    void DplusMobClickCpp::registerSuperProperty(eventDict* property){
        NSMutableDictionary *dict = [[NSMutableDictionary alloc] init];
        eventDict::iterator it;
        for(it=property->begin();it!=property->end();++it)
        {
            NSString* key = [NSString stringWithUTF8String:it->first.c_str()];
            NSString* obj = [NSString stringWithUTF8String:it->second.c_str()];
            [dict setObject:obj forKey:key];
        }
        [DplusMobClick registerSuperProperty:dict];
        [dict release];
    }
    void DplusMobClickCpp::unregisterSuperProperty(const char* propertyName){
        NSString* eName = [NSString stringWithUTF8String:propertyName];
        [DplusMobClick unregisterSuperProperty:eName];
        
    }
    std::string DplusMobClickCpp::getSuperProperty(const char* propertyName){
        NSString* eName = [NSString stringWithUTF8String:propertyName];
        NSString* value = [DplusMobClick getSuperProperty:eName];
        if(value){
            return std::string([value UTF8String]);
        }
        return NULL;
    }
    std::string DplusMobClickCpp::getSuperProperties(){
        NSDictionary* dict = [DplusMobClick getSuperProperties];
        std::string result;
        result.append("{");
        if(dict){
            for (NSString *key in dict) {
                result.append([key UTF8String]);
                result.append(":");
                result.append([dict[key] UTF8String]);
                result.append(",");
            }
            result.erase(result.end()-1);
        }
        result.append("}");
        return result;
    }
    void DplusMobClickCpp::clearSuperProperties(){
        [DplusMobClick clearSuperProperties];
    }
        
    void DplusMobClickCpp::setFirstLaunchEvent(std::vector<std::string>* eventIdList){
        
        NSMutableArray* arr = [[NSMutableArray alloc] init];
        
        std::vector<std::string>::iterator it =eventIdList->begin();
        
        for(;it!= eventIdList->end();it++){
            [arr addObject:[NSString stringWithUTF8String:it->c_str()]];
        }
        [DplusMobClick setFirstLaunchEvent:arr];
        [arr release];
    }
}
