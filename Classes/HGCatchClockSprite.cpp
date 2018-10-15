//
//  HGCatchClockSprite.cpp
//  HealthGo2
//
//  Created by GDzqw on 2018/5/2.
//

#include "HGCatchClockSprite.h"

bool HGCatchClockSprite::initWithFrame(Rect rect) {
    if (!Sprite::init()) {
        return false;
    }
    this->setAnchorPoint(Point(0, 0));
    this->setPosition(rect.origin);
    this->setContentSize(rect.size);
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    this->clockSprite = Sprite::create("catch/catchClock.png");
    if (clockSprite != nullptr) {
        clockSprite->setAnchorPoint(Point(0.5, 0.5));
        clockSprite->setPosition(Vec2(rect.size.width/2,rect.size.height/2));
        clockSprite->setContentSize(rect.size);
        this->addChild(clockSprite,10);
    }
    return true;
}
