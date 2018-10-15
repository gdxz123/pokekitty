//
//  HGCatchSuccessSprite.cpp
//  HealthGo2
//
//  Created by GDzqw on 2018/5/7.
//

#include "HGCatchFailSprite.h"
#include "HGGiftParameter.h"
#include "MobClickCpp.h"


bool HGCatchFailSprite::initWithHitCount(int hitCount) {
    if (!Sprite::init()) {
        return false;
    }
    
    umeng::eventDict catchFailedMap;
    catchFailedMap.insert(std::make_pair("hitCount", __String::createWithFormat("%d",hitCount)->getCString()));
    umeng::MobClickCpp::event("catchFailed", &catchFailedMap);
    
    
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    Size visibleSize = Director::getInstance()->getVisibleSize();
    float width = 150;
    float height = 170;
    
    this->bgSprite = Sprite::create("catch/catchFail.png");
    if (bgSprite != nullptr) {
        bgSprite->setContentSize(Size(width,height));
        bgSprite->setPosition(Vec2(width/2, height/2));
        bgSprite->setOpacity(0);
        this->addChild(bgSprite,10);
        FadeIn* fadeIn = FadeIn::create(0.5);
        bgSprite->runAction(fadeIn);
    }
    
    this->setContentSize(Size(width,height));
    this->setAnchorPoint(Vec2(0.5,0.5));
    this->setPosition(Vec2(origin.x + visibleSize.width/2, origin.y + visibleSize.height/2));

    this->nextButton = Sprite::create("catch/catchNextButton.png");
    if (nextButton != nullptr) {
        nextButton->setAnchorPoint(Vec2(0.5, 0.5));
        nextButton->setContentSize(Size(50, 25));
        nextButton->setPosition(Vec2(width/2, 25/2+3));
        nextButton->setOpacity(0);
        this->addChild(nextButton,20);
        FadeIn* fadeIn = FadeIn::create(1.5);
        nextButton->runAction(Sequence::create(fadeIn,
                                               CallFunc::create([=]()
                                                                {
        auto listener = EventListenerTouchOneByOne::create();
        listener->onTouchBegan = CC_CALLBACK_2(HGCatchFailSprite::onTouchBegan,this);
        listener->onTouchEnded = CC_CALLBACK_2(HGCatchFailSprite::onTouchEnded,this);
        Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
                                                                    
                                                                }),NULL));
    }
    return true;
}

bool HGCatchFailSprite::onTouchBegan(Touch *tTouch,Event *event) {
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    Rect nextButtonRect = nextButton->getBoundingBox();
    nextButtonRect.origin = Vec2(nextButtonRect.origin.x + origin.x, nextButtonRect.origin.y+this->getPosition().y - this->getContentSize().height/2);
    if (nextButtonRect.containsPoint(tTouch->getLocation())) {
        return true;
    } else {
        return false;
    }
}

void HGCatchFailSprite::onTouchEnded(Touch *tTouch,Event *event) {
    Director::getInstance()->popScene();
}










