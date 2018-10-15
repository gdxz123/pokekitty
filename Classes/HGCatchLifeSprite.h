//
//  HGCatchLifeSprite.h
//  HealthGo2
//
//  Created by GDzqw on 2018/5/19.
//

#ifndef HGCatchLifeSprite_h
#define HGCatchLifeSprite_h

#include "cocos2d.h"
using namespace cocos2d;

class HGCatchLifeSprite : public Sprite {
public:
    CREATE_FUNC(HGCatchLifeSprite);
    bool initWithLifeTotal(int lifeCount,const char *petName);
    void changeByHitCount(int hitCount);
    int currentLifeCount;//当前血量
private:
    int totoalLifeCount;//总血量
    float width;
    float height;
    Sprite *lifeBGSprite;
    Sprite *lifeSprite;
    Label *nameLabel;
};




#endif /* HGCatchLifeSprite_h */
