//
//  HGHomeGuideView.hpp
//  HealthGo2
//
//  Created by GDzqw on 2018/6/15.
//

#ifndef HGHomeGuideView_h
#define HGHomeGuideView_h

#include "cocos2d.h"
using namespace cocos2d;

class HGHomeGuideView : public Sprite {
public:
    CREATE_FUNC(HGHomeGuideView);
    bool initWithText(const char *text);
private:
    bool onTouchBegan(Touch* tTouch,Event* eEvent);
    void onTouchEnded(Touch* tTouch,Event* eEvent);
};

#endif /* HGHomeGuideView_h */
