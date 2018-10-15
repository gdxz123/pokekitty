//
//  HGCatchLifeSprite.cpp
//  HealthGo2
//
//  Created by GDzqw on 2018/5/19.
//

#include "HGCatchLifeSprite.h"
bool HGCatchLifeSprite::initWithLifeTotal(int lifeCount,const char *petName) {
    if (!Sprite::init()) {
        return false;
    }
    
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    Size visibleSize = Director::getInstance()->getVisibleSize();
    
    this->height = 13;
    this->width = visibleSize.width/2;
    this->totoalLifeCount = lifeCount;
    this->currentLifeCount = lifeCount;
    this->setContentSize(Size(width, height));
    
    this->lifeBGSprite = Sprite::create("catch/catchLife.png");
    if (lifeBGSprite != nullptr) {
        lifeBGSprite->setAnchorPoint(Point(0, 0));
        lifeBGSprite->setPosition(Vec2(0, 0));
        lifeBGSprite->setContentSize(Size(width, height));
        this->addChild(lifeBGSprite,10);
    }
    
    this->lifeSprite = Sprite::create("catch/catchLifeChange.png");
    if (lifeSprite != nullptr) {
        lifeSprite->setAnchorPoint(Point(0, 0));
        lifeSprite->setPosition(Vec2(3, 3.4));
        lifeSprite->setContentSize(Size(width-4, height-5));
        this->addChild(lifeSprite,10);
    }
    
    this->nameLabel = Label::createWithTTF(__String::createWithFormat("%s",petName)->getCString(), "fonts/HYE3GJM_0.TTF", 7);
    if (nameLabel != nullptr) {
        nameLabel->setAnchorPoint(Point(0, 0));
        nameLabel->setPosition(Vec2(5, 4));
        nameLabel->setColor(Color3B(255, 255, 255));
        this->addChild(nameLabel,20);
    }

    
    return true;
}

void HGCatchLifeSprite::changeByHitCount(int hitCount) {
    this->currentLifeCount = totoalLifeCount - hitCount;
    if (lifeSprite != nullptr) {
        float lifeWidth = (float)(width-4) *(1 - 1/(float)totoalLifeCount*(float)hitCount);
        if (lifeWidth < 0) lifeWidth = 0;
        lifeSprite->setContentSize(Size(lifeWidth, height-5));
    }
}
