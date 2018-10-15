//
//  HGCatchScene.h
//  HealthGo2
//
//  Created by GDzqw on 2018/4/21.
//

#ifndef HGCatchScene_h
#define HGCatchScene_h

#include "cocos2d.h"
#include "HGCatchSuccessSprite.h"
#include "HGCatchFailSprite.h"
#include "HGCatchPetSprite.h"
#include "HGCatchBGSprite.h"
using namespace cocos2d;
typedef enum {
    GameStatusPlaying = 0,
    GameStatusSuccess = 1,
    GameStatusFailture = 2
} GameStatus;

class HGCatchScene : public Scene {
public:
    static HGCatchScene *createScene();
    virtual bool init();
    void initWithPid(int pid);
    CREATE_FUNC(HGCatchScene);
    
    void onBigTrickAction();//放大招
private:
    virtual void onEnterTransitionDidFinish() override;
    virtual void onExitTransitionDidStart() override;
    int spritePid;
    GameStatus gameStatus;
    HGCatchPetSprite *catchCatSprite;
    HGCatchBGSprite *catchBG;
    
    int hitCount;
    int hitTotoalScore;
    bool isBigHitStatus;
    Label *timeLabel;
    int timeCount;
    
    HGCatchSuccessSprite *successSprite;
    HGCatchFailSprite *failtureSprite;
    
    ParticleSystemQuad *hitEmiter1;
    ParticleSystemQuad *hitEmiter2;
    ParticleSystemQuad *hitEmiter3;
    ParticleSystemQuad *hitEmiter4;
    
    void onCloseBtnAction(Ref*pSender);
    bool onTouchBegan(Touch *tTouch,Event *event);
    void onTouchMoved(Touch *tTouch,Event *event);
    void onTouchEnded(Touch *tTouch,Event *event);
    void onUpdateCustom(float dt);
    void onRecoverBigTrickAction(float dt);
    void onChangeGameStatus(float dt);
};





#endif /* HGCatchScene_h */
