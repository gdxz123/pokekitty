//
//  HGBellButton.cpp
//  HealthGo2
//
//  Created by GDzqw on 2018/4/21.
//

#include "HGBellButton.h"
#include "HGGiftScene.h"
#include "CCUMSocialSDK.h"
#include "MobClickCpp.h"

void HGBellButton::makeup() {
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    auto visibleSize = Director::getInstance()->getVisibleSize();
    float width = 20;
    
    this->setAnchorPoint(Point(0,0));
    this->setPosition(Vec2(origin.x + 5, origin.y + visibleSize.height - width - 6));
    this->setContentSize(Size(width, width));
    
    this->sprButton = Sprite::create("homepage/homepage_bell.png");
    if (sprButton != nullptr) {
        sprButton->setAnchorPoint(Point(0.5,0.5));
        sprButton->setPosition(Vec2(width/2,width/2));
        sprButton->setContentSize(Size(width,width));
        this->addChild(sprButton, 10);
    }
    
    auto listener = EventListenerTouchOneByOne::create();
    listener->onTouchBegan = CC_CALLBACK_2(HGBellButton::onTouchBegan, this);
    listener->onTouchEnded = CC_CALLBACK_2(HGBellButton::onTouchEnded, this);
    this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
}

void boardDismissCallback() {
    log("share board dismiss");
}

/*
 * 分享回调
 * @param platform 要分享到的目标平台
 * @param stCode 返回码, 200代表分享成功, 100代表开始分享
 * @param errorMsg 分享失败时的错误信息,android平台没有错误信息
 */
void shareCallback(int platform, int stCode, string& errorMsg) {
    log("#### callback!!!!!!");
    string result = "";
    if (stCode == 200) {
        umeng::MobClickCpp::event("ShareSuccess");
        result = "分享成功";
    } else if (stCode == -1) {
        result = "分享取消";
    } else {
        umeng::MobClickCpp::event("ShareFailed");
        result = "分享失败";
    }

    istringstream is;
    is >> platform;
    result.append(is.str());
    log("分享callback %s",result.c_str());
    log("platform num is : %d, %d", platform, stCode);

}

bool HGBellButton::onTouchBegan(Touch* tTouch,Event* eEvent) {
    if (this->getBoundingBox().containsPoint(tTouch->getLocation())) {
        return true;
    } else {
        return false;
    }
}


void HGBellButton::onTouchEnded(Touch* tTouch,Event* eEvent) {
    printf("onTouchEnded\n");
    umeng::MobClickCpp::event("BellButtonClick");
    
    vector<int>* platforms = new vector<int>();
    platforms->push_back(QQ);
    platforms->push_back(QZONE);
    platforms->push_back(WEIXIN);
    platforms->push_back(WEIXIN_CIRCLE);
    platforms->push_back(SINA);
    
    auto *chnStrings = __Dictionary::createWithContentsOfFile("string_en.xml");
    LanguageType currentLanguageType = Application::getInstance()->getCurrentLanguage();
    if (currentLanguageType == LanguageType::CHINESE) {
        chnStrings = __Dictionary::createWithContentsOfFile("string_ch.xml");
    }
    const char *appName = (chnStrings->valueForKey("appName"))->getCString();
    
    const char *shareContent = (chnStrings->valueForKey("shareContent"))->getCString();
    
 umeng::CCUMSocialSDK::setBoardDismissCallback(boarddismiss_selector(boardDismissCallback));
    umeng::CCUMSocialSDK::openShare(platforms, shareContent, appName ,"https://oscimg.oschina.net/oscnet/22b306fe3d4c8a8398b1a8c8969cbfd51a6.jpg","https://itunes.apple.com/cn/app/%E8%90%8C%E5%B8%83%E7%8C%AB%E5%92%AA/id1364404442?mt=8",share_selector(shareCallback));
    
}
