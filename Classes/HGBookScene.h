//
//  HGBookScene.hpp
//  HealthGo2
//
//  Created by GDzqw on 2018/6/5.
//

#ifndef HGBookScene_h
#define HGBookScene_h

#include "cocos2d.h"
#include <ui/CocosGUI.h>
using namespace cocos2d;

class HGBookScene : public Scene {
public:
    CREATE_FUNC(HGBookScene);
    virtual bool init();
private:
    void onCloseBtnAction(Ref*pSender);
};

#endif /* HGBookScene_h */
