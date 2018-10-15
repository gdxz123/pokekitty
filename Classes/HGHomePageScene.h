//
//  HGHomePageScene.h
//  HealthGo2
//
//  Created by GDzqw on 2018/4/2.
//

#ifndef HGHomePageScene_h
#define HGHomePageScene_h

#include "cocos2d.h"
#include "HGGiftButton.h"
using namespace cocos2d;

class HGHomePageScene : public cocos2d::Scene {
public:
    static cocos2d::Scene *createScene();
    virtual bool init() override;
    CREATE_FUNC(HGHomePageScene);
private:
    void onEnter() override;
    virtual void onEnterTransitionDidFinish() override;
    HGGiftButton *giftBtn1;
    HGGiftButton *giftBtn2;
    HGGiftButton *giftBtn3;
    void makeupGiftBtnUI();
};

#endif /* HGHomePageScene_h */
