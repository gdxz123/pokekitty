//
//  HGCatchClockSprite.h
//  HealthGo2
//
//  Created by GDzqw on 2018/5/2.
//

#ifndef HGCatchClockSprite_h
#define HGCatchClockSprite_h

#include "cocos2d.h"
using namespace cocos2d;

class HGCatchClockSprite : public Sprite {
public:
    CREATE_FUNC(HGCatchClockSprite);
    bool initWithFrame(Rect rect);
private:
    Sprite *clockSprite;
};




#endif /* HGCatchClockSprite_h */
