//
//  HGHomePageScene.cpp
//  HealthGo2
//
//  Created by GDzqw on 2018/4/2.
//

#include "HGHomePageScene.h"
#include "SimpleAudioEngine.h"
#include "HGCatLevelView.h"
#include "HGBellButton.h"
#include "HGHomeBookButton.h"
#include "HGGiftParameter.h"
#include "HGHomeGuideView.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;

Scene *HGHomePageScene::createScene() {
    return HGHomePageScene::create();
}

void HGHomePageScene::onEnter() {
    Scene::onEnter();
    log("HGHomePageScene->onEnter");
    this->makeupGiftBtnUI();
}

static void problemLoading(const char *fileName) {
    printf("Error while loading:%s\n",fileName);
}

bool HGHomePageScene::init() {
    if (!Scene::init()) {
        return false;
    }

    UserDefault *userDefault  = UserDefault::getInstance();
    bool isFirstUseTag = userDefault->getBoolForKey("isFirstUseHomePageTag");
    if (!isFirstUseTag) {
        UserDefault *userDefault  = UserDefault::getInstance();
        userDefault->setBoolForKey("isFirstUseHomePageTag", true);
        
        //开局一把刀
        const char *key = "GiftHadNumber1";
        int countNumber = userDefault->getIntegerForKey(key);
        userDefault->setIntegerForKey(key, ++countNumber);
        
        //新手引导页面
        HGHomeGuideView *guideView = HGHomeGuideView::create();
        guideView->initWithText("homepageGuideText");
        this->addChild(guideView,1000);
    }
    
    auto bg = LayerColor::create(Color4B(255,255,255,255));
    this->addChild(bg);
    auto winSize = Director::getInstance()->getWinSize();
    float winW = winSize.width;
    float winH = winSize.height;
    
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    auto visibleSize = Director::getInstance()->getVisibleSize();
    
    
    auto bgmap = Sprite::create("homepage/BellBG.png");
    if (bgmap == nullptr) {
        problemLoading("'homepage/BellBG.png'");
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
    
    auto *chnStrings = __Dictionary::createWithContentsOfFile("string_en.xml");
    LanguageType currentLanguageType = Application::getInstance()->getCurrentLanguage();
    if (currentLanguageType == LanguageType::CHINESE) {
        chnStrings = __Dictionary::createWithContentsOfFile("string_ch.xml");
    }
    const char *appName = (chnStrings->valueForKey("appName"))->getCString();
    auto titleLable = Label::createWithTTF(appName, "fonts/HYE3GJM_0.TTF", 13);
    if (titleLable == nullptr) {
        problemLoading("'fonts/HYE3GJM_0.TTF'");
    } else {
        titleLable->setPosition(Vec2(origin.x + visibleSize.width/2, origin.y + visibleSize.height - 15));
        titleLable->setColor(Color3B(73, 91, 100));
        this->addChild(titleLable,100);
    }

    float catLevel1SpriteWidth = visibleSize.width;
    float catLevel1SpriteHeight = catLevel1SpriteWidth*0.64056;
    auto catLevelView1 = HGCatLevelView::create();
    if (catLevelView1 == nullptr) {
        problemLoading("catLevelView1");
    } else {
        catLevelView1->initLevelView("1", Rect(Vec2(origin.x, titleLable->getPosition().y - 13 - catLevel1SpriteHeight), Size(catLevel1SpriteWidth, catLevel1SpriteHeight)));
        this->addChild(catLevelView1,10);
    }
    
    float catLevel2SpriteWidth = visibleSize.width;
    float catLevel2SpriteHeight = catLevel2SpriteWidth*0.559375;
    auto catLevelView2 = HGCatLevelView::create();
    if (catLevelView2 == nullptr) {
        problemLoading("catLevelView2");
    } else {
        catLevelView2->initLevelView("2", Rect(origin.x, catLevelView1->getPosition().y - 3 - catLevel2SpriteHeight, catLevel2SpriteWidth, catLevel2SpriteHeight));
        this->addChild(catLevelView2,10);
    }
    HGBellButton *bellBtn = HGBellButton::create();
    bellBtn->makeup();
    this->addChild(bellBtn, 30);
    
    HGHomeBookButton *bookBtn = HGHomeBookButton::create();
    bookBtn->makeup();
    this->addChild(bookBtn, 30);
    
    return true;
}

void HGHomePageScene::makeupGiftBtnUI() {
    if (giftBtn1 != nullptr) this->removeChild(giftBtn1);
    __Dictionary *giftBtn1Dic = __Dictionary::create();
    giftBtn1Dic->setObject(__String::create("1"), "gbid");
    this->giftBtn1 = HGGiftButton::create();
    giftBtn1->initWithDictionary(giftBtn1Dic);
    if (giftBtn1 != nullptr) {
        this->addChild(giftBtn1,20);
    }
    
    if (giftBtn2 != nullptr) this->removeChild(giftBtn2);
    __Dictionary *giftBtn2Dic = __Dictionary::create();
    giftBtn2Dic->setObject(__String::create("2"), "gbid");
    this->giftBtn2 = HGGiftButton::create();
    giftBtn2->initWithDictionary(giftBtn2Dic);
    if (giftBtn2 != nullptr) {
        this->addChild(giftBtn2,20);
    }
    
    if (giftBtn3 != nullptr) this->removeChild(giftBtn3);
    __Dictionary *giftBtn3Dic = __Dictionary::create();
    giftBtn3Dic->setObject(__String::create("3"), "gbid");
    this->giftBtn3 = HGGiftButton::create();
    giftBtn3->initWithDictionary(giftBtn3Dic);
    if (giftBtn3 != nullptr) {
        this->addChild(giftBtn3,20);
    }
}


void HGHomePageScene::onEnterTransitionDidFinish() {
    if (!CocosDenshion::SimpleAudioEngine::getInstance()->isBackgroundMusicPlaying()) {
        CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("homepage/homepage_BGmusic.mp3", true);
    }
}
































