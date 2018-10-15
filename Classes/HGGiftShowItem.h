//
//  HGGiftShowItem_h
//  HealthGo2
//
//  Created by GDzqw on 2018/4/11.
//

#ifndef HGGiftShowItem_h
#define HGGiftShowItem_h
#include "cocos2d.h"

using namespace cocos2d;

typedef enum {
    HGGiftShowTypeStory = 0,
    HGGiftShowTypeSelect = 1
} HGGiftShowType;


class HGGiftShowItem : public Sprite {
public:
    void initWithDictionary(__Dictionary *dataDic, int index,HGGiftShowType type, int countNumber);
    void initGBID(int gbid);
    CREATE_FUNC(HGGiftShowItem);
    Sprite *getGiftSprite();
private:
    Sprite *giftSprite;
    Label *giftNumberLabel;
    HGGiftShowType showType;
    int gid;
    int showGBid;
    bool onTouchBegan(Touch *tTouch,Event *event);
    void onTouchEnded(Touch *tTouch,Event *event);
};
#endif /* HGGiftShowItem_h */
