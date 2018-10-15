//
//  HGCatShowItem.h
//  HealthGo2
//
//  Created by GDzqw on 2018/4/7.
//

#ifndef HGCatShowItem_h
#define HGCatShowItem_h

#include "cocos2d.h"
using namespace cocos2d;

class HGCatShowItem : public Sprite {
public:
    void initWithDictionary(__Dictionary *dataDic, double sceneHeight);
    CREATE_FUNC(HGCatShowItem);
    Sprite *getCatSprite();
private:
    __Dictionary *petDataDic;
    Sprite *catSprite;
    bool onTouchBegan(Touch* tTouch,Event* eEvent);
    void onTouchEnded(Touch* tTouch,Event* eEvent);
};
#endif /* HGCatShowItem_h */
