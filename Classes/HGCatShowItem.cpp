//
//  HGCatShowItem.cpp
//  HealthGo2
//
//  Created by GDzqw on 2018/4/7.
//

#include "HGCatShowItem.h"
#include "HGCatchScene.h"
#include "HGCatLevelView.h"
#include "MobClickCpp.h"

void HGCatShowItem::initWithDictionary(__Dictionary *dataDic, double sceneHeight){
    petDataDic = dataDic;
    
    __String *pStr1 = (__String *)dataDic->valueForKey("petURL");
    this->catSprite = Sprite::create(pStr1->getCString());
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    double scale = sceneHeight*2/1136.0;
    double spriteW = dataDic->valueForKey("petWidth")->doubleValue()*scale;
    double spriteH = spriteW;
    double spriteX = dataDic->valueForKey("petX")->doubleValue()*scale;
    double spriteY = sceneHeight - dataDic->valueForKey("petY")->doubleValue()*scale;
    
    catSprite->setAnchorPoint(Point(0.5, 0.5));
    catSprite->setPosition(Vec2(spriteW/2, spriteH/2));
    catSprite->setContentSize(Size(spriteW, spriteH));
    
    
    this->setAnchorPoint(Point(0, 1));
    this->setPosition(Vec2(spriteX, spriteY));
    this->setContentSize(Size(spriteW, spriteH));
    this->addChild(catSprite, 10);
    
//    DictElement *pElement;
//    log("------------");
//    CCDICT_FOREACH(dataDic, pElement) {
//        const char * key = pElement->getStrKey();
//        __String *value = (__String *)pElement->getObject();
//        log("%s:%s",key,value ->getCString());
//    }
//    log("--------------");

    
    //动画效果
    __String *petSportUrl = (__String *)dataDic->valueForKey("petSportURL");
    if (petSportUrl->length() > 0) {
        __String *pid = (__String *)dataDic->valueForKey("pid");
        
        SpriteFrameCache *cache = SpriteFrameCache::getInstance();
        cache->addSpriteFramesWithFile(petSportUrl->getCString());
        Vector<SpriteFrame*> frameArray;
        __String *petSportCount = (__String *)dataDic->valueForKey("petSportCount");
        for (int i = 1; i <= petSportCount->intValue(); i++) {
            SpriteFrame* frame = cache->getSpriteFrameByName(StringUtils::format("cat%sF%d.png",pid->getCString(), i));
            Size size = frame->getOriginalSize();
            catSprite->setScale(catSprite->getContentSize().width/size.width);
            frameArray.pushBack(frame);
        }
        Animation *animation = Animation::createWithSpriteFrames(frameArray);
        animation->setLoops(-1);
        animation->setDelayPerUnit(0.17f);
        Animate *animate = Animate::create(animation);
        this->catSprite->runAction(animate);
    }
    
    
    EventListenerTouchOneByOne *listener = EventListenerTouchOneByOne::create();
    listener->onTouchBegan = CC_CALLBACK_2(HGCatShowItem::onTouchBegan, this);
    listener->onTouchEnded = CC_CALLBACK_2(HGCatShowItem::onTouchEnded, this);
    this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
}

bool HGCatShowItem::onTouchBegan(Touch* tTouch,Event* eEvent) {
    Rect boundingBox = this->getBoundingBox();
    float width = boundingBox.getMaxX() - boundingBox.getMinX();
    float height = boundingBox.getMaxY() - boundingBox.getMinY();
    Vec2 point = this->getParent()->convertToWorldSpaceAR(this->getPosition());
    Rect rect = Rect(point.x, point.y-height, width, height);
    log("tTouch->%f %f",tTouch->getLocation().x,tTouch->getLocation().y);
    log("rect->%f %f %f %f",rect.origin.x,rect.origin.y,rect.size.width,rect.size.height);
    
    if (rect.containsPoint(tTouch->getLocation())) {
        return true;
    } else {
        return false;
    }
}

void HGCatShowItem::onTouchEnded(Touch* tTouch,Event* eEvent) {
    log("onTouchEnded");
    umeng::MobClickCpp::event("CatShowItemClick");
    HGCatLevelView *parentView = (HGCatLevelView *)this->getParent();
    if (parentView != nullptr && !parentView->isGotoCatchSceneTag) {
        int pid = this->getTag();
        UserDefault *userDefault  = UserDefault::getInstance();
        bool isCatchedTag = userDefault->getBoolForKey(__String::createWithFormat("isCatchedTag%d",pid)->getCString());
        if (!isCatchedTag) {
            userDefault->setBoolForKey(__String::createWithFormat("isCatchedTag%d",pid)->getCString(), true);
            HGCatchScene *scene = HGCatchScene::createScene();
            scene->initWithPid(pid);
            Director::getInstance()->pushScene(scene);
            parentView->isGotoCatchSceneTag = true;
        }
        
    }
}


Sprite *HGCatShowItem::getCatSprite() {
    return catSprite;
}

