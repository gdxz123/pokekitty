//
//  HGGiftShowItem.cpp
//  HealthGo2
//
//  Created by GDzqw on 2018/4/11.
//

#include "HGGiftShowItem.h"
#include "HGGiftDetailView.h"
void HGGiftShowItem::initWithDictionary(__Dictionary *dataDic, int index,HGGiftShowType type, int countNumber) {
    this->showType = type;
    __String *gidString = (__String *)dataDic->valueForKey("gid");
    this->gid = gidString->intValue();
    auto gPicUrl = dataDic->valueForKey("gPicture");
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    Size size = Director::getInstance()->getVisibleSize();
    float padding = 3;
    float width = (size.width - 4*padding)/3;
    float titleHeight = 20;
    this->giftSprite = Sprite::create(gPicUrl->getCString());
    if (giftSprite != nullptr) {
        giftSprite->setAnchorPoint(Point(0,0));
        giftSprite->setPosition(Vec2(10, 2));
        giftSprite->setContentSize(Size(width - titleHeight, width - titleHeight));
        this->addChild(giftSprite, 10);
    }
    this->setAnchorPoint(Point(0, 1));
    this->setPosition(Vec2(origin.x + padding+(index-1)*width, origin.y + (index - 1)*width));
    int px = index % 3;
    int py = index / 3;
    this->setPosition(Vec2(origin.x +px * width+ (px+1)*padding, size.height+origin.y - 30 - py*width - (py + 1)*padding));
    this->setContentSize(Size(width, width));
    
    __String *giftName = (__String *)dataDic->valueForKey("gNameEn");
    LanguageType currentLanguageType = Application::getInstance()->getCurrentLanguage();
    if (currentLanguageType == LanguageType::CHINESE) {
        giftName = (__String *)dataDic->valueForKey("gName");
    }
    
    Label *titleLable = Label::createWithTTF(giftName->getCString(), "fonts/HYE3GJM_0.TTF", 8,Size(width,titleHeight),TextHAlignment::CENTER,TextVAlignment::CENTER);
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
    
    
    this->giftNumberLabel = Label::createWithTTF(__String::createWithFormat("%d",countNumber)->getCString(), "fonts/HYE3GJM_0.TTF", 13);
    if (giftNumberLabel != nullptr) {
        giftNumberLabel->setAnchorPoint(Point(1,0.5));
        giftNumberLabel->setPosition(Vec2(width-3, 9));
        giftNumberLabel->setColor(Color3B(73, 91, 100));
        this->addChild(giftNumberLabel, 50);
    }
    
    auto listener = EventListenerTouchOneByOne::create();
    listener->onTouchBegan = CC_CALLBACK_2(HGGiftShowItem::onTouchBegan,this);
    listener->onTouchEnded = CC_CALLBACK_2(HGGiftShowItem::onTouchEnded,this);
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
}

void HGGiftShowItem::initGBID(int gbid) {
    this->showGBid = gbid;
}


bool HGGiftShowItem::onTouchBegan(Touch *tTouch,Event *event) {
    if (this->getBoundingBox().containsPoint(tTouch->getLocation())) {
        return true;
    } else {
        return false;
    }
}

void HGGiftShowItem::onTouchEnded(Touch *tTouch,Event *event) {
    int tag = this->getTag();
    if (showType == HGGiftShowTypeStory) {
        log("HGGiftShowTypeStory");
        __String* gidString = __String::createWithFormat("%i",tag);
        HGGiftDetailView *giftDetailView = HGGiftDetailView::create();
        giftDetailView->initDetailViewWithGid(gidString);
        Director::getInstance()->pushScene(giftDetailView);
    } else if (showType == HGGiftShowTypeSelect) {
        log("HGGiftShowTypeSelect");
        UserDefault *userDefault  = UserDefault::getInstance();
        const char *key = __String::createWithFormat("GiftHadNumber%d",gid)->getCString();
        int countNumber = userDefault->getIntegerForKey(key);
        userDefault->setIntegerForKey(key, --countNumber);
        
        userDefault->setIntegerForKey(__String::createWithFormat("GiftShow%i",this->showGBid)->getCString(), tag);
        Director::getInstance()->popScene();
    }
}

Sprite *HGGiftShowItem::getGiftSprite() {
    return giftSprite;
}























