//
//  HGCatchFailSprite.h
//  HealthGo2
//
//  Created by GDzqw on 2018/5/7.
//

#ifndef HGCatchFailSprite_h
#define HGCatchFailSprite_h
#include "cocos2d.h"
using namespace cocos2d;

class HGCatchFailSprite : public Sprite {
public:
    CREATE_FUNC(HGCatchFailSprite);
    bool initWithHitCount(int hitCount);
private:
    Sprite *bgSprite;
    Sprite *nextButton;
    
    bool onTouchBegan(Touch *tTouch,Event *event);
    void onTouchMoved(Touch *tTouch,Event *event);
    void onTouchEnded(Touch *tTouch,Event *event);
};
#endif /* HGCatchFailSprite_h */
