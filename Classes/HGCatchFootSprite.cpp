//
//  HGCatchFootSprite.cpp
//  HealthGo2
//
//  Created by GDzqw on 2018/4/22.
//

#include "HGCatchFootSprite.h"
#include "SimpleAudioEngine.h"
#include "HGCatchScene.h"
#include "MobClickCpp.h"

#define HGHitKillCount 60
#define HGBallInitWidth Director::getInstance()->getVisibleSize().width*0.20
#define HGBallTargetWidth Director::getInstance()->getVisibleSize().width*0.3648
bool HGCatchFootSprite::init() {
    if (!Sprite::init()) {
        return false;
    }
    this->hitCount = 0;
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    Size visibleSize = Director::getInstance()->getVisibleSize();
//    Texture2D *texture = Director::getInstance()->getTextureCache()->addImage("catchCatfoot.png");
    
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("catch/catFootAll.plist");
    this->footSprite = Sprite::createWithSpriteFrameName("catchCatfoot.png");
    float footWidth = visibleSize.width;
    float footHeight = footWidth*0.57343;
    if (footSprite != nullptr) {
        footSprite->setAnchorPoint(Vec2(0.5, 0.5));
        footSprite->setContentSize(Size(footWidth,footHeight));
        footSprite->setPosition(Vec2(footWidth/2,footHeight/2));
        this->addChild(footSprite, 10);
    }
    
    this->footBallSprite = Sprite::create("catch/catchFootBall.png");
    float ballwidth = HGBallInitWidth;
    float ballheight = ballwidth*0.5203;
    if (footBallSprite != nullptr) {
        footBallSprite->setAnchorPoint(Vec2(0.5, 0));
        footBallSprite->setContentSize(Size(ballwidth,ballheight));
        footBallSprite->setPosition(Vec2(footWidth/2,0));
        this->addChild(footBallSprite, 20);
    }
    
    this->setContentSize(Size(footWidth, footHeight));
    this->setAnchorPoint(Vec2(0.5,0.5));
    this->setPosition(Vec2(origin.x + footWidth/2, origin.y + footHeight/2));
    
    auto listener = EventListenerTouchOneByOne::create();
    listener->onTouchBegan = CC_CALLBACK_2(HGCatchFootSprite::onTouchBegan,this);
    listener->onTouchEnded = CC_CALLBACK_2(HGCatchFootSprite::onTouchEnded,this);
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);

    return true;
}

bool HGCatchFootSprite::onTouchBegan(Touch *tTouch,Event *event) {
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    Rect ballRect = footBallSprite->getBoundingBox();
    ballRect.origin = Vec2(ballRect.origin.x + origin.x, ballRect.origin.y);
    if (ballRect.containsPoint(tTouch->getLocation())) {
        //点击放大招按钮
        if (hitCount >= HGHitKillCount) {
            //放大招
            umeng::MobClickCpp::event("BigSkill");
            CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("catch/catchBigTrickClick.mp3");
            HGCatchScene *parentNode = (HGCatchScene *)this->getParent();
            if (parentNode != nullptr) {
                parentNode->onBigTrickAction();
            }
            footBallSprite->stopAllActions();
            footBallSprite->setContentSize(Size(HGBallInitWidth, HGBallInitWidth*0.5203));
            hitCount = 0;
            isTrickTag = false;
            return false;
        } else {
            return true;
        }
    } else {
        this->footSprite->setSpriteFrame("catchCatfoot2.png");
        Size visibleSize = Director::getInstance()->getVisibleSize();
        float width = visibleSize.width;
        float height = width*0.57343;
        footSprite->setContentSize(Size(width,height));
        footSprite->setPosition(Vec2(width/2,height/2));
        return true;
    }
}

void HGCatchFootSprite::onTouchEnded(Touch *tTouch,Event *event) {
    if (footSprite == nullptr) return;
    footSprite->setSpriteFrame("catchCatfoot.png");
    Size visibleSize = Director::getInstance()->getVisibleSize();
    float width = visibleSize.width;
    float height = width*0.57343;
    footSprite->setContentSize(Size(width,height));
    footSprite->setPosition(Vec2(width/2,height/2));
    if (hitCount < HGHitKillCount) {
        hitCount ++;
        float increadeTem = (HGBallTargetWidth - HGBallInitWidth)/HGHitKillCount;
        float newWidth = footBallSprite->getContentSize().width + increadeTem;
        footBallSprite->setContentSize(Size(newWidth, newWidth*0.5203));
    } else {
        if (!isTrickTag) {
            isTrickTag = true;
            ScaleTo *scaleTo2 = ScaleTo::create(0.4, 1.2);
            ScaleTo *scaleTo1 = ScaleTo::create(0.4, 1);
            Sequence *scaleSequence = Sequence::createWithTwoActions(scaleTo2, scaleTo1);
            RepeatForever *foreverInterval = RepeatForever::create(scaleSequence);
            footBallSprite->runAction(foreverInterval);
        }
    }
}
