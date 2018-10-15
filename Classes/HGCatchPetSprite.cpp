//
//  HGCatchPetSprite.cpp
//  HealthGo2
//
//  Created by GDzqw on 2018/5/20.
//

#include "HGCatchPetSprite.h"
#include "HGCatParameter.h"
#include "SimpleAudioEngine.h"

bool HGCatchPetSprite::initWithPid(int pid, int hitTotoalScore) {
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    Size visibleSize = Director::getInstance()->getVisibleSize();
    this->spriteSkillStatus = SpriteSkillStatusNormal;
    this->hitTotoalScoreCount = hitTotoalScore;
    this->skillDefenseCount = 0;
    this->skillDefenseAllCount = 0;
    
    double spriteW = visibleSize.width/2;
    double spriteH = spriteW;
    
    this->setContentSize(Size(spriteW, spriteH +40));
    this->setAnchorPoint(Point(0.5, 0.5));
    this->setPosition(Vec2(origin.x + visibleSize.width/2, origin.y + visibleSize.height/2 + 30));
    this->setTag(pid);
    
    __Dictionary *dataDic = petDicDataWithPid(pid);
    if (dataDic == nullptr) return false;
    auto pStr1 = dataDic->valueForKey("petURL");
    this->catchCatSprite = Sprite::create(pStr1->getCString());
    if (this->catchCatSprite != nullptr) {
        catchCatSprite->setAnchorPoint(Point(0.5, 0.5));
        catchCatSprite->setContentSize(Size(spriteW, spriteH));
        catchCatSprite->setPosition(Vec2(spriteW/2, spriteH/2+20));
        this->addChild(catchCatSprite,10);
    }
    
    this->lifeSprite = HGCatchLifeSprite::create();
    if (lifeSprite != nullptr) {
        __String *petName = (__String *)dataDic->valueForKey("petNameEn");
        LanguageType currentLanguageType = Application::getInstance()->getCurrentLanguage();
        if (currentLanguageType == LanguageType::CHINESE) {
            petName = (__String *)dataDic->valueForKey("petName");
        }
        lifeSprite->initWithLifeTotal(hitTotoalScoreCount, petName->getCString());
        lifeSprite->setAnchorPoint(Point(0, 0));
        lifeSprite->setPosition(Vec2(0, catchCatSprite->getPosition().y + catchCatSprite->getContentSize().height/2 + 40));
        this->addChild(lifeSprite,50);
    }
    
    
    return true;
}

//tTouch,点击总次数，这次伤害值，这次是否是重击
void HGCatchPetSprite::hitEffect(Touch *tTouch, int hitCount,int hitDamage,bool isBigHitTag) {
    this->skillDefenseAction();
    this->skillDefenseActionEnd();
    this->damageEffect(tTouch, hitCount,hitDamage,isBigHitTag);
}

void HGCatchPetSprite::damageEffect(Touch *tTouch, int hitCount,int hitDamage,bool isBigHitTag) {
    if (this->spriteSkillStatus == SpriteSkillStatusDefense) {
        CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("catch/catchDefense.mp3");
        skillDefenseCount += hitDamage;
    } else {
        if (hitDamage > 0) {
            Label *damageLabel = Label::createWithSystemFont(__String::createWithFormat("-%d",hitDamage)->getCString(), "Helvetica", 18);
            if (damageLabel != nullptr) {
                damageLabel->enableBold();
                damageLabel->setPosition(Vec2(this->getContentSize().width/4*3,this->getContentSize().height - 10));
                damageLabel->setColor(Color3B(224, 95, 63));
                this->addChild(damageLabel,40);
                FadeOut *fadeOutAction = FadeOut::create(0.3);
                MoveTo *moveToAction = MoveTo::create(0.3, Vec2(damageLabel->getPosition().x, damageLabel->getPosition().y + 10));
                Spawn *spawnAction = Spawn::createWithTwoActions(fadeOutAction, moveToAction);
                damageLabel->runAction(Sequence::create(spawnAction,
                                                       CallFunc::create([=]()
                                                                        {
                                                                            damageLabel->getParent()->removeChild(damageLabel);
                                                                        }),NULL));
            }
        }
        if (isBigHitTag) {
            CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("catch/catchBigHit.mp3");
        } else {
            CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("catch/catchHit.mp3");
        }
        this->catchCatSprite->setRotation(-8);
        this->lifeSprite->changeByHitCount(hitCount - skillDefenseAllCount);
    }
}

void HGCatchPetSprite::recoverEffect() {
    this->catchCatSprite->setRotation(0);
}

int HGCatchPetSprite::currentLifeCount() {
    return this->lifeSprite->currentLifeCount;
}

#pragma mark - 技能
void HGCatchPetSprite::skillCommonAction() {
    ScaleTo *scaleTo2 = ScaleTo::create(0.1, 1.2);
    ScaleTo *scaleTo1 = ScaleTo::create(0.1, 1);
    Sequence *scaleSequence = Sequence::createWithTwoActions(scaleTo2, scaleTo1);
    this->catchCatSprite->runAction(scaleSequence);
}

void HGCatchPetSprite::skillDefenseAction() {
    int skillRandom = random(0.0, 0.9999)*50;
    if (skillRandom > 47) {
        if (spriteSkillStatus == SpriteSkillStatusNormal) {
            this->skillCommonAction();
            spriteSkillStatus = SpriteSkillStatusDefense;
            if (skillDefenseSprite == nullptr) {
                skillDefenseSprite = Sprite::create("catch/catchProtectCover.png");
                skillDefenseSprite->setAnchorPoint(Vec2(0.5, 0.5));
                skillDefenseSprite->setContentSize(Size(117.25, 35));
                skillDefenseSprite->setOpacity(0);
                skillDefenseSprite->setPosition(Vec2(catchCatSprite->getContentSize().width/2, catchCatSprite->getContentSize().height - skillDefenseSprite->getContentSize().height/2 + 35));
            }
            if (this->skillDefenseSprite != nullptr) {
                this->addChild(skillDefenseSprite,20);
                FadeIn* fadein = FadeIn::create(0.2);
                skillDefenseSprite->runAction(fadein);
            }
            
            
            if (skillDefenseStatusSprite == nullptr) {
                skillDefenseStatusSprite = Sprite::create("catch/catchSheild.png");
                skillDefenseStatusSprite->setAnchorPoint(Vec2(0.5, 0.5));
                skillDefenseStatusSprite->setContentSize(Size(10, 10));
                skillDefenseStatusSprite->setOpacity(0);
                skillDefenseStatusSprite->setPosition(Vec2(catchCatSprite->getContentSize().width/2, skillDefenseStatusSprite->getContentSize().height/2 + 10));
            }
            if (this->skillDefenseStatusSprite != nullptr) {
                this->addChild(skillDefenseStatusSprite,20);
                FadeIn* fadein = FadeIn::create(0.2);
                skillDefenseStatusSprite->runAction(fadein);
            }
        }
    }
}

void HGCatchPetSprite::skillDefenseActionEnd() {
    if (this->spriteSkillStatus == SpriteSkillStatusDefense) {
        if (skillDefenseCount > 15) {
            if (skillDefenseSprite != nullptr) {
                this->removeChild(skillDefenseSprite,true);
                skillDefenseSprite = nullptr;
            }
            if (skillDefenseStatusSprite != nullptr) {
                this->removeChild(skillDefenseStatusSprite,true);
                skillDefenseStatusSprite = nullptr;
            }
            skillDefenseAllCount += skillDefenseCount;
            skillDefenseCount = 0;
            spriteSkillStatus = SpriteSkillStatusNormal;
        }
    }
}

int HGCatchPetSprite::hitDamage() {
    return 1;
}












