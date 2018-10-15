//
//  DplusMobClick.h
//  wrap
//
//  Created by 周厚振 on 2016/10/19.
//
//

#ifndef DplusMobClick_h
#define DplusMobClick_h
#include <vector>
#include "MobClickCpp.h"


namespace umeng{
    class DplusMobClickCpp {
    public:
        /** Dplus增加事件
         @param eventName 事件名
         @param property 自定义属性
         */
        static void track(const char * eventName, eventDict* property = NULL);
        
        /**
         * 设置属性 键值对 会覆盖同名的key
         * 将该函数指定的key-value写入dplus专用文件；APP启动时会自动读取该文件的所有key-value，并将key-value自动作为后续所有track事件的属性。
         */
        static void registerSuperProperty(eventDict* property);
        
        /**
         *
         * 从dplus专用文件中删除指定key-value
         @param propertyName
         */
        static void unregisterSuperProperty(const char* propertyName);
        
        /**
         *
         * 返回dplus专用文件中key对应的value；如果不存在，则返回空。
         @param propertyName
         @return char*
         */
        static std::string getSuperProperty(const char* propertyName);
        
        /**
         * 返回Dplus专用文件中的所有key-value；如果不存在，则返回空。
         */
        static std::string getSuperProperties();
        
        /**
         *清空Dplus专用文件中的所有key-value。
         */
        static void clearSuperProperties();
        
        /**
         * 设置关注事件是否首次触发,只关注eventList前五个合法eventID.只要已经保存五个,此接口无效
         */
        static void setFirstLaunchEvent(std::vector<std::string>* eventIdList);
    };
}

#endif /* DplusMobClick_h */
