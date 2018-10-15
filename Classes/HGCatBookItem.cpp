//
//  HGCatBookItem.cpp
//  HealthGo2
//
//  Created by GDzqw on 2018/6/6.
//

#include "HGCatBookItem.h"
#include "HGGiftDetailView.h"
void HGCatBookItem::initWithDictionary(__Dictionary *dataDic) {
    auto gPicUrl = dataDic->valueForKey("petURL");
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    Size size = Director::getInstance()->getVisibleSize();
    float padding = 3;
    float width = (size.width - 4*padding)/3;
    float titleHeight = 15;
    UserDefault *userDefault  = UserDefault::getInstance();
    const __String *pid = dataDic->valueForKey("pid");
    bool petIsCollectTag = userDefault->getBoolForKey(__String::createWithFormat("catIsCollectTag%s",pid->getCString())->getCString());

    if (petIsCollectTag) {
        this->catSprite = Sprite::create(gPicUrl->getCString());
    } else {
        this->catSprite = Sprite::create("catbook/catbookQout.png");
    }
    if (catSprite != nullptr) {
        catSprite->setAnchorPoint(Point(0,0));
        catSprite->setPosition(Vec2(10, 0));
        catSprite->setContentSize(Size(width - titleHeight, width - titleHeight));
        this->addChild(catSprite, 10);
    }
    this->setAnchorPoint(Point(0.5, 0.5));
    this->setContentSize(Size(width, width));
    
    __String *petName = (__String *)dataDic->valueForKey("petNameEn");
    LanguageType currentLanguageType = Application::getInstance()->getCurrentLanguage();
    if (currentLanguageType == LanguageType::CHINESE) {
        petName = (__String *)dataDic->valueForKey("petName");
    }
    Label *titleLable = Label::createWithTTF(petName->getCString(), "fonts/HYE3GJM_0.TTF", 8,Size(width,titleHeight),TextHAlignment::CENTER,TextVAlignment::CENTER);
    if (titleLable != nullptr) {
        titleLable->setAnchorPoint(Point(0,1));
        titleLable->setPosition(Vec2(0, width));
        titleLable->setColor(Color3B(73, 91, 100));
        this->addChild(titleLable,20);
    }
    
    DrawNode* drawBGNode = DrawNode::create();
    this->addChild(drawBGNode,5);
    Vec2 point1[4];
    point1[0] = Vec2(0, 0);
    point1[1] = Vec2(0, width);
    point1[2] = Vec2(width, width);
    point1[3] = Vec2(width, 0);
    drawBGNode->drawPolygon(point1, 4, Color4F(0.96, 0.8745, 0.7215, 1), 0.5, Color4F(0, 0, 0, 1));
    
    DrawNode* drawGiftNode = DrawNode::create();
    this->addChild(drawGiftNode,5);
    Vec2 point2[4];
    point2[0] = Vec2(2, 4);
    point2[1] = Vec2(2, width - titleHeight);
    point2[2] = Vec2(width - 2, width - titleHeight);
    point2[3] = Vec2(width - 2, 4);
    drawGiftNode->drawPolygon(point2, 4, Color4F(1, 1, 1, 1), 0, Color4F(0, 0, 0, 0));
    
    if (petIsCollectTag) {
        if (strcmp(pid->getCString(), "0") == 0
            || strcmp(pid->getCString(), "2") == 0
            || strcmp(pid->getCString(), "3") == 0
            || strcmp(pid->getCString(), "6") == 0
            || strcmp(pid->getCString(), "7") == 0) {
            MenuItemImage *clickItem = MenuItemImage::create(
                                                   "catbook/catbookBook.png",
                                                   "catbook/catbookBook.png",
                                                   CC_CALLBACK_1(HGCatBookItem::onTouchCatItemAction, this));
            if (clickItem != nullptr) {
                clickItem->setAnchorPoint(Vec2(0.5,0.5));
                clickItem->setContentSize(Size(titleHeight, titleHeight));
                clickItem->setPosition(Vec2(width - titleHeight/2 + 3, width - titleHeight/2 + 2));
                
                Menu *clickMenu = Menu::create(clickItem, NULL);
                clickMenu->setPosition(Vec2::ZERO);
                this->addChild(clickMenu, 100);
            }
        }
    }
}



void HGCatBookItem::onTouchCatItemAction(Ref* pSender) {
    int tag = this->getTag();
    log("tag->%d",tag);
    __String* gidString = __String::createWithFormat("%i",tag);
    HGGiftDetailView *giftDetailView = HGGiftDetailView::create();
    if (giftDetailView != nullptr) {
        giftDetailView->initDetailViewWithGid(gidString);
        Director::getInstance()->pushScene(giftDetailView);
    }
}



