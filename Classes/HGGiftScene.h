//
//  HGGiftScene.h
//  HealthGo2
//
//  Created by GDzqw on 2018/4/10.
//

#ifndef HGGiftScene_h
#define HGGiftScene_h

#include "cocos2d.h"

using namespace cocos2d;
class HGGiftScene : public Scene {
public:
    static HGGiftScene *createScene();
    virtual bool init();
    void initWithShowGbid(int showGbid);
    CREATE_FUNC(HGGiftScene);
private:
    void onCloseBtnAction(Ref*pSender);
};


#endif /* HGGiftScene_h */
