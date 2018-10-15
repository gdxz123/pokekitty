//
//  HGHomeGuideView.cpp
//  HealthGo2
//
//  Created by GDzqw on 2018/6/15.
//

#include "HGHomeGuideView.h"

bool HGHomeGuideView::initWithText(const char *text) {
    if (!Sprite::init()) {
        return false;
    }
    
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    Size visibleSize = Director::getInstance()->getVisibleSize();
    
    this->setPosition(Vec2(origin.x+visibleSize.width/2, origin.y+visibleSize.height/2));
    this->setContentSize(Size(visibleSize.width, visibleSize.height));
    
    auto *chnStrings = __Dictionary::createWithContentsOfFile("string_en.xml");
    LanguageType currentLanguageType = Application::getInstance()->getCurrentLanguage();
    if (currentLanguageType == LanguageType::CHINESE) {
        chnStrings = __Dictionary::createWithContentsOfFile("string_ch.xml");
    }
    const char *appName = (chnStrings->valueForKey(text))->getCString();
    Label *contentLabel = Label::createWithTTF(appName, "fonts/HYE3GJM_0.TTF", 10);
    if (contentLabel != nullptr) {
        contentLabel->setPosition(Vec2(this->getContentSize().width/2, this->getContentSize().height/2));
        contentLabel->setMaxLineWidth(visibleSize.width/1.3);
        contentLabel->setColor(Color3B(255, 255, 255));
        this->addChild(contentLabel,100);
    }
    
    DrawNode* drawNode = DrawNode::create();
    this->addChild(drawNode,1);
    Vec2 point1[4];
    point1[0] = Vec2(0, 0);
    point1[1] = Vec2(0, this->getContentSize().height);
    point1[2] = Vec2(this->getContentSize().width, this->getContentSize().height);
    point1[3] = Vec2(this->getContentSize().width, 0);
    drawNode->drawPolygon(point1, 4, Color4F(0, 0, 0, 0.85), 0, Color4F(0, 0, 0, 0));
    
    
    EventListenerTouchOneByOne *listener = EventListenerTouchOneByOne::create();
    listener->onTouchBegan = CC_CALLBACK_2(HGHomeGuideView::onTouchBegan, this);
    listener->onTouchEnded = CC_CALLBACK_2(HGHomeGuideView::onTouchEnded, this);
    this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
    
    return true;
}

bool HGHomeGuideView::onTouchBegan(Touch* tTouch,Event* eEvent) {
    return true;
}

void HGHomeGuideView::onTouchEnded(Touch* tTouch,Event* eEvent) {
    log("onTouchEnded");
    this->getParent()->removeChild(this);
}
