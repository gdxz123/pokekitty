//
//  HGCatLevelView.cpp
//  HealthGo2
//
//  Created by GDzqw on 2018/4/7.
//

#include "HGCatLevelView.h"
#include "HGCatShowItem.h"
#include "HGCatParameter.h"
#include "HGCatGiftParameter.h"

void HGCatLevelView::onEnter() {
    Node::onEnter();
    this->isGotoCatchSceneTag = false;
}


void HGCatLevelView::initLevelView(const char *level, const Rect rect) {
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    this->setAnchorPoint(Point(0, 0));
    this->setPosition(rect.origin);
    this->setContentSize(rect.size);
    
    if (strcmp(level, "1") == 0) {
        this->sprMap = Sprite::create("pet/mapLevel1_small.jpg");
    } else if (strcmp(level, "2") == 0) {
        this->sprMap = Sprite::create("pet/mapLevel2_small.jpg");
    } else {
        this->sprMap = Sprite::create("pet/mapLevel1_small.jpg");
    }
    if (this->sprMap != nullptr) {
        sprMap->setAnchorPoint(Point(0.5, 0.5));
        sprMap->setPosition(Vec2(rect.size.width/2,rect.size.height/2));
        sprMap->setContentSize(rect.size);
        this->addChild(sprMap, 1);
    }
    
    this->catDataUpdateWithLevel(level);
    this->catAddUpdateWithLevel(level, rect);
    
}


void HGCatLevelView::catDataUpdateWithLevel(const char *level) {
    UserDefault *userDefault  = UserDefault::getInstance();
    __Array *catLevelArray;
    if (strcmp(level, "1") == 0) {
        catLevelArray = petDictionaryArrayLevel1();
    } else if (strcmp(level, "2") == 0) {
        catLevelArray = petDictionaryArrayLevel2();
    } else {
        catLevelArray = petDictionaryArrayLevel1();
    }
    for (int i = 0; i < catLevelArray->count(); i++) {
        __Dictionary *catData = (__Dictionary *)catLevelArray->getObjectAtIndex(i);
        if (catData != NULL) {
            const __String *pid = catData->valueForKey("pid");
            bool petIsHereTag = userDefault->getBoolForKey(__String::createWithFormat("L%sC%s_IsHere",level,pid->getCString())->getCString());
            if (petIsHereTag) {
                Data startTimeData = userDefault->getDataForKey(__String::createWithFormat("L%sC%s_StartTime",level,pid->getCString())->getCString());
                if (!startTimeData.isNull()) {
                    time_t startTime = *((time_t *)startTimeData.getBytes());
                    time_t currentTime = time(0);
                    time_t durTime = currentTime - startTime;
                    long durSecond = durTime;///60
                    log("currentTimeStamp->%ld",durSecond);
                    int stayTime = userDefault->getIntegerForKey(__String::createWithFormat("L%sC%s_StayTime",level,pid->getCString())->getCString());
                    if (durSecond >stayTime) {
                        userDefault->setBoolForKey(__String::createWithFormat("L%sC%s_IsHere",level,pid->getCString())->getCString(),false);
                        userDefault->setBoolForKey(__String::createWithFormat("isCatchedTag%s",pid->getCString())->getCString(),false);
                    }
                    
                }
            }
        }
    }
}

void HGCatLevelView::catAddUpdateWithLevel(const char *level, const Rect rect) {
    //  Cat Data
    __Array *showCatArray = __Array::create();
    __Array *catLevelArray;
    if (strcmp(level, "1") == 0) {
        catLevelArray = petDictionaryArrayLevel1();
    } else if (strcmp(level, "2") == 0) {
        catLevelArray = petDictionaryArrayLevel2();
    } else {
        catLevelArray = petDictionaryArrayLevel1();
    }
    
    UserDefault *userDefault  = UserDefault::getInstance();
    //还存在的猫咪要先加入队列
    for (int i = 0; i < catLevelArray->count(); i++) {
        __Dictionary *catData = (__Dictionary *)catLevelArray->getObjectAtIndex(i);
        if (catData != NULL) {
            const __String *pid = catData->valueForKey("pid");
            bool petIsHereTag = userDefault->getBoolForKey(__String::createWithFormat("L%sC%s_IsHere",level,pid->getCString())->getCString());
            if (petIsHereTag) {
                showCatArray->addObject(catData);
            }
        }
    }
    bool isGiftCanUseTag = false;//标记礼物是否起作用
    Data startTimeData = userDefault->getDataForKey(__String::createWithFormat("L%s_GiftStartUseTime",level)->getCString());
    if (!startTimeData.isNull()) {
        time_t startTime = *((time_t *)startTimeData.getBytes());
        time_t currentTime = time(0);
        time_t durTime = currentTime - startTime;
        long durSecond = durTime;///60
        log("GiftStartUseTime_durtime->%ld",durSecond);
        if (durSecond  >= 1200) {
            //20分钟起一次作用
            time_t currentTime = time(0);
            Data currentTimeData ;
            currentTimeData.copy((unsigned char*)&currentTime, sizeof(currentTime));
            userDefault->setDataForKey(__String::createWithFormat("L%s_GiftStartUseTime",level)->getCString(), currentTimeData);
            isGiftCanUseTag = true;
        }
    } else {
        time_t currentTime = time(0);
        Data currentTimeData ;
        currentTimeData.copy((unsigned char*)&currentTime, sizeof(currentTime));
        userDefault->setDataForKey(__String::createWithFormat("L%s_GiftStartUseTime",level)->getCString(), currentTimeData);
        isGiftCanUseTag = true;
    }
    
    if (isGiftCanUseTag) {
        long createPetCount = 0;
        long currentPetCount = showCatArray->count();
        
        int giftShow1 = userDefault->getIntegerForKey("GiftShow1");
        int giftShow2 = userDefault->getIntegerForKey("GiftShow2");
        int giftShow3 = userDefault->getIntegerForKey("GiftShow3");
        
        __Array *catAttractArray;
        if (strcmp(level, "1") == 0) {
            catAttractArray = petArrayGetWithGifLevel1(giftShow1,giftShow2,giftShow3);
        } else if (strcmp(level, "2") == 0) {
            catAttractArray = petArrayGetWithGifLevel2(giftShow1,giftShow2,giftShow3);
        } else {
            catAttractArray = petArrayGetWithGifLevel1(giftShow1,giftShow2,giftShow3);
        }
        
        __Array *atrractArray = __Array::create();
        for (int i = 0; i < catAttractArray->count(); i++) {
            __Dictionary *attractCatData = (__Dictionary *)catAttractArray->getObjectAtIndex(i);
            if (attractCatData != NULL) {
                bool isFindTag = false;
                const __String *attractPid = attractCatData->valueForKey("pid");
                for (int j = 0; j < showCatArray->count(); j++) {
                    __Dictionary *showCatData = (__Dictionary *)showCatArray->getObjectAtIndex(j);
                    if (showCatData != NULL) {
                        const __String *showPid = showCatData->valueForKey("pid");
                        if (strcmp(showPid->getCString(), attractPid->getCString()) == 0) {
                            isFindTag = true;
                            break;
                        }
                    }
                }
                if (!isFindTag) {
                    atrractArray->addObject(attractCatData);
                }
            }
        }
        
        //存在玩具的刷新逻辑
        int giftCurrentCount = 0;
        if (giftShow1 > 0) giftCurrentCount++;
        if (giftShow2 > 0) giftCurrentCount++;
        if (giftShow3 > 0) giftCurrentCount++;
        
        if (giftCurrentCount == 0) {
            // 0个礼物
            if (currentPetCount == 0) {
                createPetCount = 2;
            } else if (currentPetCount == 1) {
                createPetCount = 1;
            } else {
                createPetCount = 0;
            }
        } else if (giftCurrentCount == 1) {
            // 1个礼物
            if (currentPetCount < 2) {
                createPetCount = 2;
            } else if (currentPetCount < 4) {
                createPetCount = 4 - currentPetCount;
            } else {
                createPetCount = 0;
            }
        } else if (giftCurrentCount == 2) {
            // 2个礼物
            if (currentPetCount < 2) {
                createPetCount = 3;
            } else if (currentPetCount < 4) {
                createPetCount = 3;
            } else if (currentPetCount < 6) {
                createPetCount = 6 - currentPetCount;
            } else {
                createPetCount = 0;
            }
        } else if (giftCurrentCount == 3) {
            // 3个礼物
            if (currentPetCount < 2) {
                createPetCount = 4;
            } else if (currentPetCount < 4) {
                createPetCount = 4;
            } else if (currentPetCount < 7) {
                createPetCount = 7 - currentPetCount;
            } else {
                createPetCount = 0;
            }
        } else {
            if (currentPetCount < 2) {
                createPetCount = 2;
            } else {
                createPetCount = 0;
            }
        }
        for (int i = 0; i < createPetCount; i++) {
            float randomWheterCreate = random(0.0,0.9999);
            if (randomWheterCreate < 0.8) {
                //掉落算法
                __String *pidString = __String::create("");
                float totalCount = 0;
                for (ssize_t j = 0; j < atrractArray->count(); j++) {
                    __Dictionary *catCanGetDic = (__Dictionary *)atrractArray->getObjectAtIndex(j);
                    __String *probility = (__String *)catCanGetDic->valueForKey("probility");
                    totalCount += probility->floatValue();
                }
                float randomP = random(0.0, 0.9999)*totalCount;
                ssize_t findIndex = -1;
                for (ssize_t k = 0; k < atrractArray->count(); k++) {
                    __Dictionary *catCanGetDic = (__Dictionary *)atrractArray->getObjectAtIndex(k);
                    __String *probility = (__String *)catCanGetDic->valueForKey("probility");
                    if (randomP < probility->floatValue()) {
                        findIndex = k;
                        pidString = (__String *)catCanGetDic->valueForKey("pid");
                        break;
                    } else {
                        randomP -= probility->floatValue();
                    }
                }
                
                if (findIndex >= 0) {
                    if (findIndex < atrractArray->count()) {
                        atrractArray->removeObjectAtIndex(findIndex);
                    }
                    
                    __Dictionary *catData = petDicDataWithPid(pidString->intValue());
                    time_t currentTime = time(0);
                    Data currentTimeData ;
                    currentTimeData.copy((unsigned char*)&currentTime, sizeof(currentTime));
                    userDefault->setDataForKey(__String::createWithFormat("L%sC%s_StartTime",level,pidString->getCString())->getCString(), currentTimeData);
                    
                    int stayTime = random(0.4,0.9999)*900+1200;  //26分钟- 35分钟
                    userDefault->setIntegerForKey(__String::createWithFormat("L%sC%s_StayTime",level,pidString->getCString())->getCString(), stayTime);
                    userDefault->setBoolForKey(__String::createWithFormat("L%sC%s_IsHere",level,pidString->getCString())->getCString(),true);
                    showCatArray->addObject(catData);
                }
            }
        }
    }
    for (int i = 0; i < showCatArray->count(); i++) {
        __Dictionary *catData = (__Dictionary *)showCatArray->getObjectAtIndex(i);
        if (catData != NULL) {
//            DictElement *pElement;
//            log("------------");
//            log("level->%s",level);
//            CCDICT_FOREACH(catData, pElement) {
//                const char * key = pElement->getStrKey();
//                __String *value = (__String *)pElement->getObject();
//                log("%s:%s",key,value ->getCString());
//            }
//            log("--------------");
//
            const __String *pid = catData->valueForKey("pid");
            
            UserDefault *userDefault  = UserDefault::getInstance();
            userDefault->setBoolForKey(__String::createWithFormat("catIsCollectTag%s",pid->getCString())->getCString(), true);
            
            HGCatShowItem *cat = HGCatShowItem::create();
            cat->initWithDictionary(catData,  rect.size.height);
            this->addChild(cat, 10+pid->intValue(),pid->intValue());
        }
    }
}














