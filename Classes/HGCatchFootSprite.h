//
//  HGCatchFootSprite.h
//  HealthGo2
//
//  Created by GDzqw on 2018/4/22.
//

#ifndef HGCatchFootSprite_h
#define HGCatchFootSprite_h

#include "cocos2d.h"
using namespace cocos2d;

class HGCatchFootSprite : public Sprite {
public:
    CREATE_FUNC(HGCatchFootSprite);
    virtual bool init();
private:
    Sprite *footSprite;
    Sprite *footBallSprite;
    int hitCount;
    bool isTrickTag;
    bool onTouchBegan(Touch *tTouch,Event *event);
    void onTouchEnded(Touch *tTouch,Event *event);
};
#endif /* HGCatchFootSprite_h */
