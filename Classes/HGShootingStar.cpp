//
//  HGShootingStar.cpp
//  HealthGo2
//
//  Created by GDzqw on 2018/5/19.
//

#include "HGShootingStar.h"
#include "base/CCDirector.h"
#include "base/firePngData.h"
#include "renderer/CCTextureCache.h"

HGShootingStar * HGShootingStar::create()
{
    HGShootingStar *ret = new (std::nothrow) HGShootingStar();
    if (ret && ret->init())
    {
        ret->autorelease();
    }
    else
    {
        CC_SAFE_DELETE(ret);
    }
    return ret;
}

HGShootingStar* HGShootingStar::createWithTotalParticles(int numberOfParticles)
{
    HGShootingStar* ret = new (std::nothrow) HGShootingStar();
    if (ret && ret->initWithTotalParticles(numberOfParticles))
    {
        ret->autorelease();
    }
    else
    {
        CC_SAFE_DELETE(ret);
    }
    return ret;
}

bool HGShootingStar::initWithTotalParticles(int numberOfParticles)
{
    if( ParticleSystemQuad::initWithTotalParticles(numberOfParticles) )
    {
        // duration
        _duration = DURATION_INFINITY;
        
        // Gravity Mode
        setEmitterMode(Mode::GRAVITY);
        
        // Gravity Mode: gravity
        setGravity(Vec2(-200,200));
        
        // Gravity Mode: speed of particles
        setSpeed(5);
        setSpeedVar(5);
        
        // Gravity Mode: radial
        setRadialAccel(0);
        setRadialAccelVar(0);
        
        // Gravity Mode: tangential
        setTangentialAccel(0);
        setTangentialAccelVar(0);
        
        // angle
        _angle = 90;
        _angleVar = 360;
        
        // emitter position
        Size winSize = Director::getInstance()->getWinSize();
        this->setPosition(winSize.width/2, winSize.height/2);
        setPosVar(Vec2::ZERO);
        
        // life of particles
        _life = 1;
        _lifeVar = 0.2;
        
        // size, in pixels
        _startSize = 5.0f;
        _startSizeVar = 2.0f;
        _endSize = START_SIZE_EQUAL_TO_END_SIZE;
        
        // emits per second
        _emissionRate = _totalParticles/_life;
        
        // color of particles
        _startColor.r = 0.7f;
        _startColor.g = 0.87f;
        _startColor.b = 0.3f;
        _startColor.a = 1.0f;
        _startColorVar.r = 0.0f;
        _startColorVar.g = 0.0f;
        _startColorVar.b = 0.15f;
        _startColorVar.a = 0.1f;
        _endColor.r = 0.0f;
        _endColor.g = 0.0f;
        _endColor.b = 0.0f;
        _endColor.a = 0.0f;
        _endColorVar.r = 0.0f;
        _endColorVar.g = 0.0f;
        _endColorVar.b = 0.0f;
        _endColorVar.a = 0.0f;
        
        // additive
        this->setBlendAdditive(true);
        return true;
    }
    return false;
}
