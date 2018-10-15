//
//  HGGiftButton.h
//  HealthGo2
//
//  Created by GDzqw on 2018/4/9.
//

#ifndef HGGiftButton_h
#define HGGiftButton_h

#include "cocos2d.h"
using namespace cocos2d;

class HGGiftButton : public Sprite {
public:
    void initWithDictionary(__Dictionary *giftDic);
    CREATE_FUNC(HGGiftButton);
private:
    Sprite *sprGift;
    Sprite *sprBGGift;
    int showGBid;//标记第几个按钮
    bool onTouchBegan(Touch* tTouch,Event* eEvent);//手指按下事件
    void onTouchEnded(Touch* tTouch,Event* eEvent);//手指离开事件
};

#endif /* HGGiftButton_h */
