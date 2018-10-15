//
//  HGShootingStar.h
//  HealthGo2
//
//  Created by GDzqw on 2018/5/19.
//

#ifndef HGShootingStar_h
#define HGShootingStar_h

#include "cocos2d.h"
#include "2d/CCParticleSystemQuad.h"
using namespace cocos2d;
class HGShootingStar : public ParticleSystemQuad
{
public:
    static HGShootingStar * create();
    static HGShootingStar* createWithTotalParticles(int numberOfParticles);
    
CC_CONSTRUCTOR_ACCESS:
    HGShootingStar(){}
    virtual ~HGShootingStar(){}
    
    bool init(){ return initWithTotalParticles(100); }
    virtual bool initWithTotalParticles(int numberOfParticles);
    
private:
    CC_DISALLOW_COPY_AND_ASSIGN(HGShootingStar);
};

#endif /* HGShootingStar_h */
