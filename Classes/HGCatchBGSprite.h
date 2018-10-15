//
//  HGCatchBGSprite.h
//  HealthGo2
//
//  Created by GDzqw on 2018/5/21.
//

#ifndef HGCatchBGSprite_h
#define HGCatchBGSprite_h

#include "cocos2d.h"
using namespace cocos2d;

class HGCatchBGSprite : public Sprite {
public:
    CREATE_FUNC(HGCatchBGSprite);
    bool initWithPid(int pid);
private:
    Sprite *bgSprite1;
    Sprite *bgSprite2;
    Sprite *cloudSprite1;
    Sprite *cloudSprite2;
    void update(float t);
};
#endif /* HGCatchBGSprite_h */
