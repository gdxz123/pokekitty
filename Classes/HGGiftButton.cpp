//
//  HGGiftButton.cpp
//  HealthGo2
//
//  Created by GDzqw on 2018/4/9.
//

#include "HGGiftButton.h"
#include "HGGiftScene.h"
#include "HGGiftParameter.h"
#include "MobClickCpp.h"

void HGGiftButton::initWithDictionary(__Dictionary *giftDic) {
    int gbid = giftDic->valueForKey("gbid")->intValue();
    this->showGBid = gbid;
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    auto visibleSize = Director::getInstance()->getVisibleSize();
    float width = 50;
    float padding = (visibleSize.width - width*3)/4;
    this->setAnchorPoint(Point(0,0));
    this->setPosition(Vec2(origin.x+padding*gbid+width*(gbid - 1), origin.y+5));
    this->setContentSize(Size(width, width));
    
    DrawNode* drawNode = DrawNode::create();
    this->addChild(drawNode,1);
    Vec2 point1[4];
    point1[0] = Vec2(0, 0);
    point1[1] = Vec2(0, width);
    point1[2] = Vec2(width, width);
    point1[3] = Vec2(width, 0);
    drawNode->drawPolygon(point1, 4, Color4F(1, 0.9647, 0.9568, 1), 0.5, Color4F(0.8274, 0.8274, 0.8274, 1));

    UserDefault *userDefault  = UserDefault::getInstance();
    int giftShow = userDefault->getIntegerForKey(__String::createWithFormat("GiftShow%i",this->showGBid)->getCString());
    if (giftShow) {
        __Dictionary *dataDic = giftDicDataWithGid(giftShow);
        auto gPicUrl = dataDic->valueForKey("gPicture");
        this->sprGift = Sprite::create(gPicUrl->getCString());
        if (this->sprGift != nullptr) {
            sprGift->setAnchorPoint(Point(0.5,0.5));
            sprGift->setPosition(Vec2(width/2, width/2));
            sprGift->setContentSize(Size(width, width));
            this->addChild(sprGift,10);
        }
    } else {
        this->sprBGGift = Sprite::create("homepage/homepage_placehold.png");
        if (this->sprBGGift != nullptr) {
            sprBGGift->setAnchorPoint(Point(0.5,0.5));
            sprBGGift->setPosition(Vec2(width/2, width/2));
            sprBGGift->setContentSize(Size(width, width));
            this->addChild(sprBGGift,10);
        }
    }
    
    
    auto listener = EventListenerTouchOneByOne::create();
    listener->onTouchBegan = CC_CALLBACK_2(HGGiftButton::onTouchBegan, this);
    listener->onTouchEnded = CC_CALLBACK_2(HGGiftButton::onTouchEnded, this);
    this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
}

bool HGGiftButton::onTouchBegan(Touch* tTouch,Event* eEvent) {
    if (this->getBoundingBox().containsPoint(tTouch->getLocation())) {
        return true;
    } else {
        return false;
    }
}

void HGGiftButton::onTouchEnded(Touch* tTouch,Event* eEvent) {
    printf("onTouchEnded\n");
    umeng::MobClickCpp::event("GiftButtonClick");
    HGGiftScene *giftScene = HGGiftScene::createScene();
    giftScene->initWithShowGbid(this->showGBid);
    Director::getInstance()->pushScene(giftScene);
}
