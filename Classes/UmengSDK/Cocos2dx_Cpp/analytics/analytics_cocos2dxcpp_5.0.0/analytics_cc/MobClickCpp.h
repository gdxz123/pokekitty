//
//  MobClickCpp.m
//  MobClickCpp
//
//  Created by zhangziqi on 14-2-24.
//  Copyright (c) 2014年 Umeng Inc. All rights reserved.
//

#ifndef __MobClickGameAnalytics__MobClickCpp__
#define __MobClickGameAnalytics__MobClickCpp__

#include "cocos2d.h"
#include <string>
#include <map>
using namespace std;
USING_NS_CC;
#if defined(__GNUC__) && ((__GNUC__ >= 4) || ((__GNUC__ == 3) && (__GNUC_MINOR__ >= 1)))
#define UMENG_DEPRECATED __attribute__((deprecated))
#elif _MSC_VER >= 1400 //vs 2005 or higher
#define UMENG_DEPRECATED __declspec(deprecated)
#else
#define UMENG_DEPRECATED
#endif

namespace umeng {
    
    typedef map<string, string> eventDict;
    
    
    class MobClickCpp {
        
    public:
        /** 初始化sdk
         @param void.
         @return .
         @exception .
         */
        
        static void init();
        /** 设置是否打印sdk的log信息,默认不开启
         @param value 设置为true,umeng SDK 会输出log信息,记得release产品时要设置回false.
         @return .
         @exception .
         */
        
        static void setLogEnabled(bool value);
        
        /** 设置是否在android 6.0下获取mac信息,默认不开启
         @param value 设置为true,umeng SDK 采集mac信息.
         @return .
         @exception .
         */
        
        static void setCheckDevice(bool value);
        
        
        /** 设置app切到后台经过多少秒之后，切到前台会启动新session,默认30
         @param seconds 秒数
         @return .
         @exception .
         */
        static void setSessionIdleLimit(int seconds);
        
        /** 设置是否对日志信息进行加密, 默认false(不加密).
         @param value 设置为true, umeng SDK 会将日志信息做加密处理
         @return void.
         */
        static void setEncryptEnabled(bool value);
        
        /** 设置app版本号。由于历史原因需要和xcode3工程兼容,友盟提取的是Build号(CFBundleVersion)，
         如果需要和App Store上的版本一致,请调用此方法。
         @param appVersion 版本号，例如设置成`XcodeAppVersion`.
         @return void.
         */
        ///---------------------------------------------------------------------------------------
        /// @name  事件统计
        ///---------------------------------------------------------------------------------------
        
        
        /** 自定义事件,数量统计.
         使用前，请先到友盟App管理后台的设置->编辑自定义事件 中添加相应的事件ID，然后在工程中传入相应的事件ID
         
         @param  eventId 网站上注册的事件Id.
         @param  label 分类标签。不同的标签会分别进行统计，方便同一事件的不同标签的对比,为NULL或空字符串时后台会生成和eventId同名的标签.
         @return void.
         */
        static void event(const char * eventId, const char * label = NULL);
        /** 自定义事件,数量统计.
         请注意：key不能含有“,”字符，value不能含有"|"字符
         这是因为不同shared library之间传递std对象可能引发兼容性问题，所以需要先将std对象转换成c语言的基本类型，
         在这里我会把eventDict转换成“k1,v1|k2,v2”形式的字符串
         
         使用前，请先到友盟App管理后台的设置->编辑自定义事件 中添加相应的事件ID，然后在工程中传入相应的事件ID
         */
        
        static void event(const char * eventId, eventDict * attributes, int counter);

        
        static void event(const char * eventId, eventDict * attributes);
        ///---------------------------------------------------------------------------------------
        /// @name  页面计时
        ///---------------------------------------------------------------------------------------
        
        
        /** 页面时长统计,记录某个view被打开多长时间,可以自己计时也可以调用beginLogPageView,endLogPageView自动计时
         
         @param pageName 需要记录时长的view名称.
         @return void.
         */
        
        static void beginLogPageView(const char *pageName);
        static void endLogPageView(const char *pageName);
        
        
        //游戏统计开始
        
        ///---------------------------------------------------------------------------------------
        /// @name  账号
        ///---------------------------------------------------------------------------------------
        
        /** active user sign-in.
         使用sign-In函数后，如果结束该PUID的统计，需要调用sign-Off函数
         @param puid : user's ID
         @param provider : 不能以下划线"_"开头，使用大写字母和数字标识; 如果是上市公司，建议使用股票代码。
         @return void.
         */
        static void profileSignIn(const char * puid, const char * provider = NULL);
        
        /** active user sign-off.
         停止sign-in PUID的统计
         @return void.
         */
        static void profileSignOff();
        
        ///---------------------------------------------------------------------------------------
        /// @name  玩家属性设置
        ///---------------------------------------------------------------------------------------
        
        /** 设置玩家的等级、游戏中的唯一Id、性别、年龄和来源.
         */
        
        /** 设置玩家等级属性.
         @param level 玩家等级
         @return void
         */
        static void setUserLevel(int level);
        
        
        ///---------------------------------------------------------------------------------------
        /// @name  关卡统计
        ///---------------------------------------------------------------------------------------
        
        /** 记录玩家进入关卡，通过关卡及失败的情况.
         */
        
        
        /** 进入关卡.
         @param level 关卡
         @return void
         */
        static void startLevel(const char * level);
        
        /** 通过关卡.
         @param level 关卡,如果level == NULL 则为当前关卡
         @return void
         */
        static void finishLevel(const char * level);
        
        /** 未通过关卡.
         @param level 关卡,如果level == NULL 则为当前关卡
         @return void
         */
        
        static void failLevel(const char * level);
        
        ///---------------------------------------------------------------------------------------
        /// @name  支付统计
        ///---------------------------------------------------------------------------------------
        
        /** 记录玩家使用真实货币的消费情况
         */
        
        
        /** 玩家支付货币兑换虚拟币.
         @param cash 真实货币数量
         @param source 支付渠道
         @param coin 虚拟币数量
         @return void
         */
        
        static void pay(double cash, int source, double coin);
        
        /** 玩家支付货币购买道具.
         @param cash 真实货币数量
         @param source 支付渠道
         @param item 道具id
         @param amount 道具数量
         @param price 道具单价
         @return void
         */
        static void pay(double cash, int source, const char * item, int amount, double price);
        
        ///---------------------------------------------------------------------------------------
        /// @name  虚拟币购买统计
        ///---------------------------------------------------------------------------------------
        
        /** 记录玩家使用虚拟币的消费情况
         */
        
        
        /** 玩家使用虚拟币购买道具
         @param item 道具id
         @param amount 道具数量
         @param price 道具单价
         @return void
         */
        static void buy(const char *item, int amount, double price);
        
        
        ///---------------------------------------------------------------------------------------
        /// @name  道具消耗统计
        ///---------------------------------------------------------------------------------------
        
        /** 记录玩家道具消费情况
         */
        
        
        /** 玩家使用虚拟币购买道具
         @param item 道具id
         @param amount 道具数量
         @param price 道具单价
         @return void
         */
        
        static void use(const char * item, int amount, double price);
        
        
        ///---------------------------------------------------------------------------------------
        /// @name  虚拟币及道具奖励统计
        ///---------------------------------------------------------------------------------------
        
        /** 记录玩家获赠虚拟币及道具的情况
         */
        
        
        /** 玩家获虚拟币奖励
         @param coin 虚拟币数量
         @param source 奖励方式
         @return void
         */
        
        static void bonus(double coin, int source);
        
        /** 玩家获道具奖励
         @param item 道具id
         @param amount 道具数量
         @param price 道具单价
         @param source 奖励方式
         @return void
         */
        
        static void bonus(const char * item, int amount, double price, int source);
        
        /** 记录玩家交易兑换货币的情况
         @param currencyAmount 现金或等价物总额
         @param currencyType 为ISO4217定义的3位字母代码，如CNY,USD等（如使用其它自定义等价物作为现金，可使￼用ISO4217中未定义的3位字母组合传入货币类型）￼
         @param virtualAmount 虚拟币数量
         @param channel 支付渠道
         @param orderId 交易订单ID
         @return void
         */
        
        static void exchange(const char *orderId, double currencyAmount, const char *currencyType,double virtualAmount,int channel);
        //游戏统计结束
        
        /*如果使用,在启动sdk之前调用*/
        static void setLatency(unsigned int latency);
        
    };
}
#endif
