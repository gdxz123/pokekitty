//
//  HGCatLevelView.h
//  HealthGo2
//
//  Created by GDzqw on 2018/4/7.
//

#ifndef HGCatLevelView_h
#define HGCatLevelView_h

#include "cocos2d.h"
using namespace cocos2d;

class HGCatLevelView : public Sprite {
public:
    void initLevelView(const char *level, const Rect rect);
    CREATE_FUNC(HGCatLevelView);
    bool isGotoCatchSceneTag;
    void onEnter();
private:
    void catDataUpdateWithLevel(const char *level);//cat数组更新
    void catAddUpdateWithLevel(const char *level, const Rect rect);
    Sprite *sprMap;
};




#endif /* HGCatLevelView_h */
