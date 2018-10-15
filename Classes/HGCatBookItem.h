//
//  HGCatBookItem.h
//  HealthGo2
//
//  Created by GDzqw on 2018/6/6.
//

#ifndef HGCatBookItem_h
#define HGCatBookItem_h

#include "cocos2d.h"
using namespace cocos2d;

class HGCatBookItem : public Sprite {
public:
    void initWithDictionary(__Dictionary *dataDic);
    CREATE_FUNC(HGCatBookItem);
private:
    Sprite *catSprite;
    void onTouchCatItemAction(Ref* pSender);
};

#endif /* HGCatBookItem_h */
