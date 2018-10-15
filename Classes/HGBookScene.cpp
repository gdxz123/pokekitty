//
//  HGBookScene.cpp
//  HealthGo2
//
//  Created by GDzqw on 2018/6/5.
//

#include "HGBookScene.h"
#include "HGCatBookItem.h"
#include "HGCatParameter.h"
#include "HGGiftDetailView.h"
#include <ui/CocosGUI.h>

bool HGBookScene::init() {
    if (!Scene::init()) {
        return false;
    }
    
    auto *chnStrings = __Dictionary::createWithContentsOfFile("string_en.xml");
    LanguageType currentLanguageType = Application::getInstance()->getCurrentLanguage();
    if (currentLanguageType == LanguageType::CHINESE) {
        chnStrings = __Dictionary::createWithContentsOfFile("string_ch.xml");
    }
    const char *giftSceneName = (chnStrings->valueForKey("bookSceneName"))->getCString();
    
    auto bg = LayerColor::create(Color4B(255,255,255,255));
    this->addChild(bg);
    auto winSize = Director::getInstance()->getWinSize();
    float winW = winSize.width;
    float winH = winSize.height;
    
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    auto visibleSize = Director::getInstance()->getVisibleSize();
    
    
    auto bgmap = Sprite::create("homepage/homepage_bellBG.png");
    if (bgmap != nullptr) {
        float spX = bgmap->getTextureRect().getMaxX();
        float spY = bgmap->getTextureRect().getMaxY();
        
        float scaleX = (float)visibleSize.width/(float)spX;
        float scaleY = (float)visibleSize.height/(float)spY;
        float scale = (scaleX > scaleY?scaleX:scaleY);
        bgmap->setPosition(Vec2(winW/2,winH/2));
        bgmap->setAnchorPoint(Point(0.5,0.5));
        bgmap->setScale(scale, scale);
        this->addChild(bgmap,10);
    }
    
    Label *titleLable = Label::createWithTTF(giftSceneName, "fonts/HYE3GJM_0.TTF", 13);
    if (titleLable != nullptr) {
        titleLable->setPosition(Vec2(origin.x + visibleSize.width/2, origin.y + visibleSize.height - 15));
        titleLable->setColor(Color3B(73, 91, 100));
        this->addChild(titleLable,100);
    }
    
    auto closeItem = MenuItemImage::create("pet/closeButton.png", "pet/closeButton.png", CC_CALLBACK_1(HGBookScene::onCloseBtnAction, this));
    if (closeItem != nullptr) {
        float x = origin.x  + closeItem->getContentSize().width/2 + 3;
        float y = origin.y+ visibleSize.height - closeItem->getContentSize().height/2 - 3;
        closeItem->setPosition(Vec2(x,y));
    }
    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 30);
    
    float padding = 3;
    float width = (visibleSize.width - 4*padding)/3;
    __Array *catArray = petDictionaryArrayLevel1();
    __Array *catArray2 = petDictionaryArrayLevel2();
    
    ui::ScrollView *scrollView = ui::ScrollView::create();
    scrollView->setDirection(ui::ScrollView::Direction::VERTICAL);
    scrollView->setAnchorPoint(Vec2(0.5, 0.5));
    scrollView->setPosition(Vec2(origin.x+visibleSize.width/2, origin.y+visibleSize.height/2 - 30));
    scrollView->setContentSize(visibleSize);
    scrollView->setBounceEnabled(true);
    scrollView->setInnerContainerSize(Size(visibleSize.width, 2 + (width + padding)* ((catArray->count() + catArray2->count())/3 + 1.5)));
    this->addChild(scrollView,10);
    
    for (int i = 0; i <  catArray->count(); i++) {
        __Dictionary *catDic = (__Dictionary *)catArray->getObjectAtIndex(i);
        HGCatBookItem *catItem = HGCatBookItem::create();
        catItem->initWithDictionary(catDic);

        int px = i % 3;
        int py = i / 3;
        catItem->setPosition(Vec2(px * width+ (px+1)*padding + width/2, scrollView->getInnerContainerSize().height - width/2 - py*width - (py + 1)*padding));
        const __String *pid = catDic->valueForKey("pid");
        scrollView->addChild(catItem,20,pid->intValue());
    }
    
    for (int i = 0; i <  catArray2->count(); i++) {
        __Dictionary *catDic2 = (__Dictionary *)catArray2->getObjectAtIndex(i);
        HGCatBookItem *catItem2 = HGCatBookItem::create();
        int index = (int)(i+catArray->count());
        catItem2->initWithDictionary(catDic2);
        int px = index % 3;
        int py = index / 3;
        catItem2->setPosition(Vec2(px * width+ (px+1)*padding + width/2, scrollView->getInnerContainerSize().height - width/2 - py*width - (py + 1)*padding));
        const __String *pid = catDic2->valueForKey("pid");
        scrollView->addChild(catItem2,20,pid->intValue());
    }
    return true;
}

void HGBookScene::onCloseBtnAction(Ref*pSender) {
    Director::getInstance()->popScene();
}
