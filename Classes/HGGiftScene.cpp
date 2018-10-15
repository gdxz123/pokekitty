//
//  HGGiftScene.cpp
//  HealthGo2
//
//  Created by GDzqw on 2018/4/10.
//

#include "HGGiftScene.h"
#include "HGGiftShowItem.h"
#include "HGGiftParameter.h"
#include "HGHomeGuideView.h"

static void problemLoading(const char *fileName) {
    printf("Error while loading:%s\n",fileName);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HGHomePageScene.cpp\n");
}

HGGiftScene *HGGiftScene::createScene() {
    return HGGiftScene::create();
}

bool HGGiftScene::init() {
    if (!Scene::init()) {
        return false;
    }
    UserDefault *userDefault  = UserDefault::getInstance();
    bool isFirstUseTag = userDefault->getBoolForKey("isFirstUseGiftTag");
    if (!isFirstUseTag) {
        UserDefault *userDefault  = UserDefault::getInstance();
        userDefault->setBoolForKey("isFirstUseGiftTag", true);
        //新手引导页面
        HGHomeGuideView *guideView = HGHomeGuideView::create();
        guideView->initWithText("giftGuideText");
        this->addChild(guideView,1000);
    }
    
    auto *chnStrings = __Dictionary::createWithContentsOfFile("string_en.xml");
    LanguageType currentLanguageType = Application::getInstance()->getCurrentLanguage();
    if (currentLanguageType == LanguageType::CHINESE) {
        chnStrings = __Dictionary::createWithContentsOfFile("string_ch.xml");
    }
    const char *giftSceneName = (chnStrings->valueForKey("giftSceneName"))->getCString();
    
    auto bg = LayerColor::create(Color4B(255,255,255,255));
    this->addChild(bg);
    auto winSize = Director::getInstance()->getWinSize();
    float winW = winSize.width;
    float winH = winSize.height;
    
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    auto visibleSize = Director::getInstance()->getVisibleSize();
    
    
    auto bgmap = Sprite::create("homepage/homepage_bellBG.png");
    if (bgmap == nullptr) {
        problemLoading("'homepage/homepage_bellBG.png'");
    } else {
        float spX = bgmap->getTextureRect().getMaxX();
        float spY = bgmap->getTextureRect().getMaxY();
        
        float scaleX = (float)visibleSize.width/(float)spX;
        float scaleY = (float)visibleSize.height/(float)spY;
        float scale = (scaleX > scaleY?scaleX:scaleY);
        bgmap->setPosition(Vec2(winW/2,winH/2));
        bgmap->setAnchorPoint(Point(0.5,0.5));
        bgmap->setScale(scale, scale);
        this->addChild(bgmap,1);
    }
    
    Label *titleLable = Label::createWithTTF(giftSceneName, "fonts/HYE3GJM_0.TTF", 13);
    if (titleLable == nullptr) {
        problemLoading("'fonts/HYE3GJM_0.TTF'");
    } else {
        titleLable->setPosition(Vec2(origin.x + visibleSize.width/2, origin.y + visibleSize.height - 15));
        titleLable->setColor(Color3B(73, 91, 100));
        this->addChild(titleLable,100);
    }
    
    auto closeItem = MenuItemImage::create("pet/closeButton.png", "pet/closeButton.png", CC_CALLBACK_1(HGGiftScene::onCloseBtnAction, this));
    if (closeItem == nullptr ||
        closeItem->getContentSize().width <= 0 ||
        closeItem->getContentSize().height <= 0) {
        problemLoading("'pet/closeButton.png' and 'pet/closeButton.png'");
    } else {
        float x = origin.x  + closeItem->getContentSize().width/2 + 3;
        float y = origin.y+ visibleSize.height - closeItem->getContentSize().height/2 - 3;
        closeItem->setPosition(Vec2(x,y));
    }
    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 30);
    
    return true;
}

void HGGiftScene::initWithShowGbid(int showGbid) {
    __Array *giftArray = giftDictionaryArray();
    int index = 0;
    for (int i = 0; i <  giftArray->count(); i++) {
        __Dictionary *giftDic = (__Dictionary *)giftArray->getObjectAtIndex(i);
        UserDefault *userDefault  = UserDefault::getInstance();
        __String *gid = (__String *)giftDic->valueForKey("gid");
        int countNumber = userDefault->getIntegerForKey(__String::createWithFormat("GiftHadNumber%s",gid->getCString())->getCString());
        if (countNumber > 0) {
            HGGiftShowItem *giftItem = HGGiftShowItem::create();
            giftItem->initWithDictionary(giftDic, index,HGGiftShowTypeSelect,countNumber);
            giftItem->initGBID(showGbid);
            this->addChild(giftItem,20,gid->intValue());
            index++;
        }
    }
}

void HGGiftScene::onCloseBtnAction(Ref*pSender) {
    Director::getInstance()->popScene();
}













