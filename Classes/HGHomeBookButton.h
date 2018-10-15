//
//  HGHomeBookButton.h
//  HealthGo2
//
//  Created by GDzqw on 2018/6/4.
//

#ifndef HGHomeBookButton_h
#define HGHomeBookButton_h

#include "cocos2d.h"
using namespace cocos2d;

class HGHomeBookButton : public Sprite {
public:
    CREATE_FUNC(HGHomeBookButton);
    void makeup();
private:
    Sprite *sprButton;
    bool onTouchBegan(Touch* tTouch,Event* eEvent);//手指按下事件
    void onTouchEnded(Touch* tTouch,Event* eEvent);//手指离开事件
};



#endif /* HGHomeBookButton_h */
