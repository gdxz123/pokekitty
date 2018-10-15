//
//  HGCatchScene.cpp
//  HealthGo2
//
//  Created by GDzqw on 2018/4/21.
//

#include "HGCatchScene.h"
#include "HGGiftParameter.h"
#include "HGCatParameter.h"
#include "HGCatchFootSprite.h"
#include "HGCatchClockSprite.h"
#include "HGHomeGuideView.h"
#include "SimpleAudioEngine.h"

HGCatchScene *HGCatchScene::createScene() {
    return HGCatchScene::create();
}

bool HGCatchScene::init() {
    if (!Scene::init()) {
        return false;
    }
    
    UserDefault *userDefault  = UserDefault::getInstance();
    bool isFirstUseTag = userDefault->getBoolForKey("isFirstUseCatchSceneTag");
    if (!isFirstUseTag) {
        UserDefault *userDefault  = UserDefault::getInstance();
                userDefault->setBoolForKey("isFirstUseCatchSceneTag", true);
        //新手引导页面
        HGHomeGuideView *guideView = HGHomeGuideView::create();
        guideView->initWithText("catchGuideText");
        this->addChild(guideView,1000);
    }
    
    
    gameStatus = GameStatusPlaying;
    hitCount = 0;
    hitTotoalScore = 0;
    timeCount = 30;
    isBigHitStatus = false;
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    Size visibleSize = Director::getInstance()->getVisibleSize();
    auto *chnStrings = __Dictionary::createWithContentsOfFile("string_en.xml");
    LanguageType currentLanguageType = Application::getInstance()->getCurrentLanguage();
    if (currentLanguageType == LanguageType::CHINESE) {
        chnStrings = __Dictionary::createWithContentsOfFile("string_ch.xml");
    }
    auto closeItem = MenuItemImage::create("pet/closeButton.png", "pet/closeButton.png", CC_CALLBACK_1(HGCatchScene::onCloseBtnAction, this));
    if (closeItem == nullptr ||
        closeItem->getContentSize().width <= 0 ||
        closeItem->getContentSize().height <= 0) {
        log("'pet/closeButton.png' and 'pet/closeButton.png'");
    } else {
        float x = origin.x  + closeItem->getContentSize().width/2 + 3;
        float y = origin.y+ visibleSize.height - closeItem->getContentSize().height/2 - 3;
        closeItem->setPosition(Vec2(x,y));
    }
    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 60);
    
    HGCatchFootSprite *footSprite = HGCatchFootSprite::create();
    this->addChild(footSprite, 20);
    
    HGCatchClockSprite *clockSprite = HGCatchClockSprite::create();
    if (clockSprite != nullptr) {
        float width = 20;
        clockSprite->initWithFrame(Rect(Vec2(origin.x+visibleSize.width - width - 25, visibleSize.height-width -5), Size(width, width)));
        this->addChild(clockSprite,40);
    }
    this->timeLabel = Label::createWithTTF(__String::createWithFormat("%d",timeCount)->getCString(), "fonts/HYE3GJM_0.TTF", 15);
    if (timeLabel != nullptr) {
        timeLabel->setPosition(Vec2(origin.x + visibleSize.width - 16, visibleSize.height - 15));
        timeLabel->setColor(Color3B(73, 91, 100));
        this->addChild(timeLabel,40);
    }
    schedule(schedule_selector(HGCatchScene::onUpdateCustom), 1.0f, kRepeatForever, 0);
    return true;
}

void HGCatchScene::initWithPid(int pid) {
    this->spritePid = pid;
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    this->catchBG = HGCatchBGSprite::create();
    catchBG->initWithPid(pid);
    this->addChild (catchBG,10);
    
    __Dictionary *dataDic = petDicDataWithPid(pid);
    if (dataDic == nullptr) return;
    //初始化hitTotalScore
    const __String *petLevel = dataDic->valueForKey("petLevel");
    if (petLevel != nullptr) {
        if (strcmp(petLevel->getCString(), "1") == 0) {
            hitTotoalScore = 70;
        } else if (strcmp(petLevel->getCString(), "2") == 0) {
            hitTotoalScore = 100;
        } else if (strcmp(petLevel->getCString(), "3") == 0) {
            hitTotoalScore = 130;
        } else if (strcmp(petLevel->getCString(), "4") == 0) {
            hitTotoalScore = 160;
        } else if (strcmp(petLevel->getCString(), "5") == 0) {
            hitTotoalScore = 190;
        } else {
            hitTotoalScore = 70;
        }
        int hitScoreRandom = random(0.0,0.9999)*30;
        hitTotoalScore += hitScoreRandom;
    }
    this->catchCatSprite = HGCatchPetSprite::create();
    catchCatSprite->initWithPid(pid,hitTotoalScore);
    this->addChild(catchCatSprite,40);
    
    auto listener = EventListenerTouchOneByOne::create();
    listener->onTouchBegan = CC_CALLBACK_2(HGCatchScene::onTouchBegan,this);
    listener->onTouchMoved = CC_CALLBACK_2(HGCatchScene::onTouchMoved,this);
    listener->onTouchEnded = CC_CALLBACK_2(HGCatchScene::onTouchEnded,this);
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
}

#pragma mark - scheduler
void HGCatchScene::onUpdateCustom(float dt) {
    if (gameStatus != GameStatusSuccess) {
        if (timeCount > 0) {
            timeCount-- ;
            this->timeLabel->setString(__String::createWithFormat("%d",timeCount)->getCString());
            if (this->catchCatSprite->currentLifeCount() <= 0) {
                unschedule(schedule_selector(HGCatchScene::onUpdateCustom));
                gameStatus = GameStatusSuccess;
                successSprite = HGCatchSuccessSprite::create();
                if (successSprite != nullptr) {
                    successSprite->initWithHitCount(hitCount,spritePid);
                    this->addChild(successSprite,60);
                }
                CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("catch/catchWin.mp3");
            }
        } else {
            if (this->catchCatSprite->currentLifeCount() > 0) {
                unschedule(schedule_selector(HGCatchScene::onUpdateCustom));
                gameStatus = GameStatusFailture;
                Vec2 origin = Director::getInstance()->getVisibleOrigin();
                failtureSprite = HGCatchFailSprite::create();
                if (failtureSprite != nullptr) {
                    failtureSprite->initWithHitCount(hitCount);
                    this->addChild (failtureSprite,60);
                }
                CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("catch/catchFail.wav");
            }
        }
    }
}

#pragma mark - action
void HGCatchScene::onBigTrickAction() {
    if (gameStatus == GameStatusSuccess || gameStatus == GameStatusFailture) return;
    isBigHitStatus = true;
    schedule(schedule_selector(HGCatchScene::onRecoverBigTrickAction), 5.0f, kRepeatForever, 0);
}

void HGCatchScene::onRecoverBigTrickAction(float dt) {
    isBigHitStatus = false;
}

void HGCatchScene::onCloseBtnAction(Ref*pSender) {
    Director::getInstance()->popScene();
}

bool HGCatchScene::onTouchBegan(Touch *tTouch,Event *event) {
    if (gameStatus == GameStatusPlaying) {
        int hitDamage = 1;
        if (catchCatSprite != nullptr) {
            hitDamage = catchCatSprite->hitDamage();
        }
        if (isBigHitStatus) {
            hitDamage += 1;
        }
        hitCount += hitDamage;
        
        catchCatSprite->hitEffect(tTouch,hitCount,hitDamage,isBigHitStatus);
        
        ParticleSystemQuad *chooseHitEmiter;
        int choose = hitCount % 3;
        if (choose == 0) {
            chooseHitEmiter = hitEmiter1;
        } else if (choose == 1) {
            chooseHitEmiter = hitEmiter2;
        } else if (choose == 2) {
            chooseHitEmiter = hitEmiter3;
        }  else {
            chooseHitEmiter = hitEmiter4;
        }
        if (chooseHitEmiter != nullptr) {
            chooseHitEmiter->removeFromParentAndCleanup(true);
        }
        Point pos2 = tTouch->getLocation();
        if (isBigHitStatus) {
            chooseHitEmiter = ParticleSystemQuad::create("catch/catchBigHitCircle.plist");
        } else {
            chooseHitEmiter = ParticleSystemQuad::create("catch/catchHitCircle.plist");}
        chooseHitEmiter->setPosition(Vec2(pos2.x, pos2.y));
        this->addChild(chooseHitEmiter, 60);
    } else if (gameStatus == GameStatusFailture) {
        if (failtureSprite->getBoundingBox().containsPoint(tTouch->getLocation())) {
            return true;
        } else {
            return false;
        }
    } else if (gameStatus == GameStatusSuccess) {
        if (successSprite->getBoundingBox().containsPoint(tTouch->getLocation())) {
            return true;
        } else {
            return false;
        }
    } else {
        return false;
    }
    return true;
}

void HGCatchScene::onTouchMoved(Touch *tTouch,Event *event) {
}

void HGCatchScene::onTouchEnded(Touch *tTouch,Event *event) {
    if (gameStatus == GameStatusPlaying) {
        catchCatSprite->recoverEffect();
    } else if (gameStatus == GameStatusFailture) {
//        Director::getInstance()->popScene();
    } else if (gameStatus == GameStatusSuccess) {
//        Director::getInstance()->popScene();
    }
}

void HGCatchScene::onEnterTransitionDidFinish() {
    CocosDenshion::SimpleAudioEngine::getInstance()->stopBackgroundMusic();
    CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("catch/catchBGmusic.wav", true);
}

void HGCatchScene::onExitTransitionDidStart() {
    CocosDenshion::SimpleAudioEngine::getInstance()->stopBackgroundMusic();
    CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("homepage/homepage_BGmusic.mp3", true);
}
