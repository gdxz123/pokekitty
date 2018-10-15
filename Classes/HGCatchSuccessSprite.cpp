//
//  HGCatchSuccessSprite.cpp
//  HealthGo2
//
//  Created by GDzqw on 2018/5/7.
//

#include "HGCatchSuccessSprite.h"
#include "HGCatGiftParameter.h"
#include "HGGiftParameter.h"
#include "MobClickCpp.h"


bool HGCatchSuccessSprite::initWithHitCount(int hitCount,int pid) {
    if (!Sprite::init()) {
        return false;
    }
    
    umeng::eventDict catchSuccessMap;
    catchSuccessMap.insert(std::make_pair("hitCount", __String::createWithFormat("%d",hitCount)->getCString()));
    umeng::MobClickCpp::event("catchSuccess", &catchSuccessMap);
    
    
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    Size visibleSize = Director::getInstance()->getVisibleSize();
    float width = 150;
    float height = 147;
    
    this->bgSprite = Sprite::create("catch/catchSuccess.png");
    if (bgSprite != nullptr) {
        bgSprite->setContentSize(Size(width,height));
        bgSprite->setPosition(Vec2(width/2, height/2));
        bgSprite->setOpacity(0);
        this->addChild(bgSprite,10);
        FadeIn* fadeIn = FadeIn::create(0.5);
        bgSprite->runAction(fadeIn);
    }
    
    this->starSprite1 = Sprite::create("catch/catchSuccessStar.png");
    if (starSprite1 != nullptr) {
        starSprite1->setAnchorPoint(Vec2(0.5, 0.5));
        starSprite1->setContentSize(Size(20, 20));
        starSprite1->setPosition(Vec2(width/4, height - 20));
        starSprite1->setOpacity(0);
        this->addChild(starSprite1,20);
        FadeIn* fadeIn = FadeIn::create(0.5);
        starSprite1->runAction(fadeIn);
    }
    
    if (hitCount >= 100) {
        this->starSprite2 = Sprite::create("catch/catchSuccessStar.png");
        if (starSprite2 != nullptr) {
            starSprite2->setAnchorPoint(Vec2(0.5, 0.5));
            starSprite2->setContentSize(Size(20, 20));
            starSprite2->setPosition(Vec2(width/2, height - 20));
            starSprite2->setOpacity(0);
            this->addChild(starSprite2,20);
            FadeIn* fadeIn = FadeIn::create(0.5);
            starSprite2->runAction(fadeIn);
        }
    }
    if (hitCount >= 200) {
        this->starSprite3 = Sprite::create("catch/catchSuccessStar.png");
        if (starSprite3 != nullptr) {
            starSprite3->setAnchorPoint(Vec2(0.5, 0.5));
            starSprite3->setContentSize(Size(20, 20));
            starSprite3->setPosition(Vec2(width*3/4, height - 20));
            starSprite3->setOpacity(0);
            this->addChild(starSprite3,20);
            FadeIn* fadeIn = FadeIn::create(0.5);
            starSprite3->runAction(fadeIn);
        }
    }
    
    int gid = 1;
    __Array *giftArray = giftArrayGetWithPid(pid);
    
    float totalCount = 0;
    for (ssize_t i = 0; i < giftArray->count(); i++) {
        __Dictionary *giftCanGetDic = (__Dictionary *)giftArray->getObjectAtIndex(i);
        __String *probility = (__String *)giftCanGetDic->valueForKey("probility");
        totalCount += probility->floatValue();
    }
    float randomP = random(0.0, 0.9999)*totalCount;
    for (ssize_t i = 0; i < giftArray->count(); i++) {
        __Dictionary *giftCanGetDic = (__Dictionary *)giftArray->getObjectAtIndex(i);
        __String *probility = (__String *)giftCanGetDic->valueForKey("probility");
        if (randomP < probility->floatValue()) {
            __String *gidString = (__String *)giftCanGetDic->valueForKey("gid");
            gid = gidString->intValue();
            break;
        } else {
            randomP -= probility->floatValue();
        }
    }
    
    __Dictionary *giftDictionary = giftDicDataWithGid(gid);
    
    UserDefault *userDefault  = UserDefault::getInstance();
    const char *key = __String::createWithFormat("GiftHadNumber%d",gid)->getCString();
    int countNumber = userDefault->getIntegerForKey(key);
    userDefault->setIntegerForKey(key, ++countNumber);
    
    
    auto gPicUrl = giftDictionary->valueForKey("gPicture");
    this->giftSprite = Sprite::create(gPicUrl->getCString());
    if (giftSprite != nullptr) {
        float giftwidth = 50;
        giftSprite->setContentSize(Size(giftwidth,giftwidth));
        giftSprite->setPosition(Vec2(width/2, height/2 - 10));
        giftSprite->setAnchorPoint(Vec2(0.5, 0.5));
        giftSprite->setOpacity(0);
        this->addChild(giftSprite,50);
        FadeIn* fadeIn = FadeIn::create(0.5);
        giftSprite->runAction(fadeIn);
    }
    
    auto *chnStrings = __Dictionary::createWithContentsOfFile("string_en.xml");
    LanguageType currentLanguageType = Application::getInstance()->getCurrentLanguage();
    if (currentLanguageType == LanguageType::CHINESE) {
        chnStrings = __Dictionary::createWithContentsOfFile("string_ch.xml");
    }
    const char *congratulationString = (chnStrings->valueForKey("congratulation"))->getCString();
    
    Label *contentLabel = Label::createWithTTF(congratulationString, "fonts/HYE3GJM_0.TTF", 10);
    if (contentLabel != nullptr) {
        contentLabel->setPosition(Vec2(width/2, height/2+22));
        contentLabel->setColor(Color3B(246, 171, 53));
        contentLabel->setOpacity(0);
        this->addChild(contentLabel,50);
        FadeIn* fadeIn = FadeIn::create(0.5);
        contentLabel->runAction(fadeIn);
    }
    
    this->setContentSize(Size(width,height));
    this->setAnchorPoint(Vec2(0.5,0.5));
    this->setPosition(Vec2(origin.x + visibleSize.width/2, origin.y + visibleSize.height/2));

    this->nextButton = Sprite::create("catch/catchNextButton.png");
    if (nextButton != nullptr) {
        nextButton->setAnchorPoint(Vec2(0.5, 0.5));
        nextButton->setContentSize(Size(50, 25));
        nextButton->setPosition(Vec2(width/2, 25/2+10));
        nextButton->setOpacity(0);
        this->addChild(nextButton,20);
        FadeIn* fadeIn = FadeIn::create(1.5);
        nextButton->runAction(Sequence::create(fadeIn,
                                               CallFunc::create([=]()
                                                                {
        auto listener = EventListenerTouchOneByOne::create();
        listener->onTouchBegan = CC_CALLBACK_2(HGCatchSuccessSprite::onTouchBegan,this);
        listener->onTouchEnded = CC_CALLBACK_2(HGCatchSuccessSprite::onTouchEnded,this);
        Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
                                                                    
                                                                }),NULL));
    }
    return true;
}

bool HGCatchSuccessSprite::onTouchBegan(Touch *tTouch,Event *event) {
    if (this->getBoundingBox().containsPoint(tTouch->getLocation())) {
        return true;
    } else {
        return false;
    }
}

void HGCatchSuccessSprite::onTouchEnded(Touch *tTouch,Event *event) {
    Director::getInstance()->popScene();
}










