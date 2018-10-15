//
//  HGCatchPetSprite.h
//  HealthGo2
//
//  Created by GDzqw on 2018/5/20.
//

#ifndef HGCatchPetSprite_h
#define HGCatchPetSprite_h

#include "cocos2d.h"
#include "HGCatchLifeSprite.h"
using namespace cocos2d;
typedef enum {
    SpriteSkillStatusNormal = 1,
    SpriteSkillStatusDefense = 2,
    SpriteSkillStatusRecoveryBlood = 4
} SpriteSkillStatus;

class HGCatchPetSprite : public Sprite {
public:
    CREATE_FUNC(HGCatchPetSprite);
    bool initWithPid(int pid,int hitTotoalScore);
    void hitEffect(Touch *tTouch,int hitCount,int hitDamage,bool isBigHitTag);
    void recoverEffect();
    int hitDamage();//用户每次点击能造成的伤害
    int currentLifeCount();//当前血量
private:
    SpriteSkillStatus spriteSkillStatus;// 使用技能状态
    HGCatchLifeSprite * lifeSprite;
    Sprite *catchCatSprite;
    int hitTotoalScoreCount;
    
    void damageEffect(Touch *tTouch, int hitCount,int hitDamage,bool isBigHitTag);
    // 技能
    Sprite *skillDefenseSprite;
    Sprite *skillDefenseStatusSprite;
    int skillDefenseCount;// 阻挡的伤害
    int skillDefenseAllCount;// 阻挡的所有伤害
    
    void skillCommonAction();
    void skillDefenseAction();
    void skillDefenseActionEnd();
};


#endif /* HGCatchPetSprite_h */
