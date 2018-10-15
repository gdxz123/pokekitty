//
//  HGHomeBookButton.cpp
//  HealthGo2
//
//  Created by GDzqw on 2018/6/4.
//

#include "HGHomeBookButton.h"
#include "HGBookScene.h"
#include "MobClickCpp.h"

void HGHomeBookButton::makeup() {
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    Size visibleSize = Director::getInstance()->getVisibleSize();
    float width = 20;
    float height = width * 0.833;
    
    this->setAnchorPoint(Point(0,0));
    this->setPosition(Vec2(origin.x + visibleSize.width - width - 5, origin.y + visibleSize.height - height - 9));
    this->setContentSize(Size(width, height));
    
    this->sprButton = Sprite::create("homepage/homepage_book.png");
    if (sprButton != nullptr) {
        sprButton->setAnchorPoint(Point(0.5,0.5));
        sprButton->setPosition(Vec2(width/2,height/2));
        sprButton->setContentSize(Size(width,height));
        this->addChild(sprButton, 10);
    }
    auto listener = EventListenerTouchOneByOne::create();
    listener->onTouchBegan = CC_CALLBACK_2(HGHomeBookButton::onTouchBegan, this);
    listener->onTouchEnded = CC_CALLBACK_2(HGHomeBookButton::onTouchEnded, this);
    this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
}

bool HGHomeBookButton::onTouchBegan(Touch* tTouch,Event* eEvent) {
    if (this->getBoundingBox().containsPoint(tTouch->getLocation())) {
        return true;
    } else {
        return false;
    }
}


void HGHomeBookButton::onTouchEnded(Touch* tTouch,Event* eEvent) {
    umeng::MobClickCpp::event("BookButtonClick");
    log("onTouchEnded");
    HGBookScene *scene = HGBookScene::create();
    Director::getInstance()->pushScene(scene);
}
