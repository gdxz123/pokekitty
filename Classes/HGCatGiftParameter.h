//
//  HGCatGiftParameter.h
//  HealthGo2
//
//  Created by GDzqw on 2018/6/13.
//

#ifndef HGCatGiftParameter_h
#define HGCatGiftParameter_h

#include "cocos2d.h"
using namespace cocos2d;
extern __Array *giftArrayGetWithPid(int pid);

extern __Array *petArrayGetWithGifLevel1(int gidA, int gidB, int gidC);

extern __Array *petArrayGetWithGifLevel2(int gidA, int gidB, int gidC);
#endif /* HGCatGiftParameter_h */
