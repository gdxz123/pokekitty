//
//  HGGiftDetailView.h
//  HealthGo2
//
//  Created by GDzqw on 2018/4/17.
//

#ifndef HGGiftDetailView_h
#define HGGiftDetailView_h

#include "cocos2d.h"

using namespace cocos2d;

class HGGiftDetailView : public Scene {
public:
    void initDetailViewWithGid(__String *gid);
    CREATE_FUNC(HGGiftDetailView);
private:
    void onCloseBtnAction(Ref*pSender);
};
#endif /* HGGiftDetailView_h */
