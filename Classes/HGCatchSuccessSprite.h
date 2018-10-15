//
//  HGCatchSuccessSprite.h
//  HealthGo2
//
//  Created by GDzqw on 2018/5/7.
//

#ifndef HGCatchSuccessSprite_h
#define HGCatchSuccessSprite_h
#include "cocos2d.h"
using namespace cocos2d;

class HGCatchSuccessSprite : public Sprite {
public:
    CREATE_FUNC(HGCatchSuccessSprite);
    bool initWithHitCount(int hitCount,int pid);
private:
    Sprite *starSprite1;
    Sprite *starSprite2;
    Sprite *starSprite3;
    Sprite *bgSprite;
    Sprite *giftSprite;
    Sprite *nextButton;
    
    bool onTouchBegan(Touch *tTouch,Event *event);
    void onTouchMoved(Touch *tTouch,Event *event);
    void onTouchEnded(Touch *tTouch,Event *event);
};
#endif /* HGCatchSuccessSprite_h */
