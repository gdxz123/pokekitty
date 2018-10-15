//
//  HGBellButton.h
//  HealthGo2
//
//  Created by GDzqw on 2018/4/21.
//

#ifndef HGBellButton_h
#define HGBellButton_h

#include "cocos2d.h"
#include "CCUMSocialSDK.h"

using namespace cocos2d;

class HGBellButton : public Sprite {
public:
    CREATE_FUNC(HGBellButton);
    void makeup();
private:
    Sprite *sprButton;
    bool onTouchBegan(Touch* tTouch,Event* eEvent);
    void onTouchEnded(Touch* tTouch,Event* eEvent);
};

#endif /* HGBellButton_h */
