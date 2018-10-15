//
//  HGGiftDetailView.cpp
//  HealthGo2
//
//  Created by GDzqw on 2018/4/17.
//

#include "HGGiftDetailView.h"
#include <ui/CocosGUI.h>


void HGGiftDetailView::initDetailViewWithGid(__String *gid) {
    auto bg = LayerColor::create(Color4B(255,255,255,255));
    this->addChild(bg);
    if (gid == nullptr) return;
    auto winSize = Director::getInstance()->getWinSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    auto visibleSize = Director::getInstance()->getVisibleSize();
    
    auto closeItem = MenuItemImage::create("pet/closeButton.png", "pet/closeButton.png", CC_CALLBACK_1(HGGiftDetailView::onCloseBtnAction, this));
    if (closeItem != nullptr ) {
        float x = origin.x  + closeItem->getContentSize().width/2 + 3;
        float y = origin.y+ visibleSize.height - closeItem->getContentSize().height/2 - 3;
        closeItem->setPosition(Vec2(x,y));
    }
    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 30);
    
    __String *storyName = __String::createWithFormat("story/story%s.jpg",gid->getCString());
    ui::ScrollView *scrollView = ui::ScrollView::create();
    scrollView->setDirection(ui::ScrollView::Direction::VERTICAL);
    scrollView->setAnchorPoint(Vec2(0.5, 0.5));
    scrollView->setPosition(Vec2(origin.x+visibleSize.width/2, origin.y+visibleSize.height/2));
    scrollView->setContentSize(visibleSize);
    scrollView->setBounceEnabled(true);
    
    auto content = Sprite::create(storyName->getCString());
    if (content != nullptr) {
        content->setScale(visibleSize.width / content->getContentSize().width, visibleSize.width / content->getContentSize().width);
        scrollView->addChild(content);
        float height = visibleSize.width*content->getContentSize().height/content->getContentSize().width;
        scrollView->setInnerContainerSize(Size(visibleSize.width, height));
        content->setPosition(Vec2(0, origin.y));
        content->setAnchorPoint(Vec2(0 , 0));
        this->addChild(scrollView, 20);
    } else {
        Label *label = Label::createWithTTF("期待更新...", "fonts/HYE3GJM_0.TTF", 13);
        if (label != nullptr) {
            label->setColor(Color3B(73, 91, 100));
            label->setAnchorPoint(Vec2(0.5, 0.5));
            label->setPosition(Vec2(origin.x + visibleSize.width/2,
                                    origin.y + visibleSize.height/2));
            this->addChild(label, 20);
        }
    }
    
}

void HGGiftDetailView::onCloseBtnAction(Ref*pSender) {
    Director::getInstance()->popScene();
}

