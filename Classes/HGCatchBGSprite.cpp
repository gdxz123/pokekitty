//
//  HGCatchBGSprite.cpp
//  HealthGo2
//
//  Created by GDzqw on 2018/5/21.
//

#include "HGCatchBGSprite.h"
bool HGCatchBGSprite::initWithPid(int pid) {
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    Size visibleSize = Director::getInstance()->getVisibleSize();
    
    float width = visibleSize.width;
    float height = visibleSize.height;

    this->setAnchorPoint(Point(0, 0));
    this->setPosition(Vec2(origin.x, origin.y));
    this->setContentSize(Size(width, height));
    
    this->bgSprite1 = Sprite::create("catch/catchBG1.png");
    if (bgSprite1 != nullptr) {
        bgSprite1->setAnchorPoint(Point(0, 0));
        bgSprite1->setPosition(Vec2(0, 0));
        bgSprite1->setContentSize(Size(width, height));
        this->addChild(bgSprite1,10);
    }
    
    this->bgSprite2 = Sprite::create("catch/catchBG2.png");
    if (bgSprite2 != nullptr) {
        bgSprite2->setAnchorPoint(Point(0, 0));
        bgSprite2->setPosition(Vec2(0, 0));
        bgSprite2->setContentSize(Size(width, height));
        this->addChild(bgSprite2,10);
    }
    
    this->cloudSprite1 = Sprite::create("catch/catchBGCloud.png");
    if (cloudSprite1 != nullptr) {
        cloudSprite1->setAnchorPoint(Point(0, 0));
        cloudSprite1->setContentSize(Size(20, 11.3));
        cloudSprite1->setPosition(Vec2(cloudSprite1->getContentSize().width, height - 60));
        this->addChild(cloudSprite1,10);
    }
    this->cloudSprite2 = Sprite::create("catch/catchBGCloud2.png");
    if (cloudSprite2 != nullptr) {
        cloudSprite2->setAnchorPoint(Point(0, 0));
        cloudSprite2->setContentSize(Size(35, 21));
        cloudSprite2->setPosition(Vec2(30 + cloudSprite2->getContentSize().width, height - 30));
        this->addChild(cloudSprite2,10);
    }
    if (cloudSprite1 != nullptr && cloudSprite2 != nullptr) {
        schedule(schedule_selector(HGCatchBGSprite::update));
    }
    return true;
}

void HGCatchBGSprite::update(float t) {
    cloudSprite1->setPosition(Vec2(cloudSprite1->getPosition().x + 0.05, cloudSprite1->getPosition().y));
    cloudSprite2->setPosition(Vec2(cloudSprite2->getPosition().x + 0.1, cloudSprite2->getPosition().y));
    Size visibleSize = Director::getInstance()->getVisibleSize();
    if (cloudSprite1->getPosition().x > visibleSize.width + cloudSprite1->getContentSize().width + 5) {
        cloudSprite1->setPosition(Vec2(0 - cloudSprite1->getContentSize().width, cloudSprite1->getPosition().y));
    }
    
    if (cloudSprite2->getPosition().x > visibleSize.width + cloudSprite2->getContentSize().width + 5) {
        cloudSprite2->setPosition(Vec2(0 - cloudSprite2->getContentSize().width, cloudSprite2->getPosition().y));
    }
}
