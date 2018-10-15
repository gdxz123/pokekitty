//
//  HGGiftParameter.cpp
//  HealthGo2
//
//  Created by GDzqw on 2018/4/21.
//
#include "HGGiftParameter.h"
#include <stdio.h>

__Array* giftDictionaryArray() {
    __Dictionary *giftDic1 = __Dictionary::create();
    giftDic1->setObject(__String::create("1"), "gid");
    giftDic1->setObject(__String::create("哑铃"), "gName");
    giftDic1->setObject(__String::create("Dumbbell"), "gNameEn");
    giftDic1->setObject(__String::create("gift/gift1.png"), "gPicture");
    giftDic1->setObject(__String::create("1"), "gLevel");
    giftDic1->setObject(__String::create("温暖"), "gDecription");
    giftDic1->setObject(__String::create("0"), "gCount");
    
    __Dictionary *giftDic2 = __Dictionary::create();
    giftDic2->setObject(__String::create("2"), "gid");
    giftDic2->setObject(__String::create("麝香豆"), "gName");
    giftDic2->setObject(__String::create("Love pea"), "gNameEn");
    giftDic2->setObject(__String::create("gift/gift2.png"), "gPicture");
    giftDic2->setObject(__String::create("1"), "gLevel");
    giftDic2->setObject(__String::create("麝香豆"), "gDecription");
    giftDic2->setObject(__String::create("0"), "gCount");
    
    __Dictionary *giftDic3 = __Dictionary::create();
    giftDic3->setObject(__String::create("3"), "gid");
    giftDic3->setObject(__String::create("自拍杆"), "gName");
    giftDic3->setObject(__String::create("Selfie stick"), "gNameEn");
    giftDic3->setObject(__String::create("gift/gift3.png"), "gPicture");
    giftDic3->setObject(__String::create("1"), "gLevel");
    giftDic3->setObject(__String::create("自拍杆"), "gDecription");
    giftDic3->setObject(__String::create("0"), "gCount");
    
    __Dictionary *giftDic4 = __Dictionary::create();
    giftDic4->setObject(__String::create("4"), "gid");
    giftDic4->setObject(__String::create("小咸鱼"), "gName");
    giftDic4->setObject(__String::create("Fish"), "gNameEn");
    giftDic4->setObject(__String::create("gift/gift4.png"), "gPicture");
    giftDic4->setObject(__String::create("1"), "gLevel");
    giftDic4->setObject(__String::create("自拍杆"), "gDecription");
    giftDic4->setObject(__String::create("0"), "gCount");
    
    __Dictionary *giftDic5 = __Dictionary::create();
    giftDic5->setObject(__String::create("5"), "gid");
    giftDic5->setObject(__String::create("麝香猫的手帕"), "gName");
    giftDic5->setObject(__String::create("Handkerchief"), "gNameEn");
    giftDic5->setObject(__String::create("gift/gift5.png"), "gPicture");
    giftDic5->setObject(__String::create("2"), "gLevel");
    giftDic5->setObject(__String::create("总觉得哪里不对"), "gDecription");
    giftDic5->setObject(__String::create("0"), "gCount");
    
    __Dictionary *giftDic6 = __Dictionary::create();
    giftDic6->setObject(__String::create("6"), "gid");
    giftDic6->setObject(__String::create("田园猫的围巾"), "gName");
    giftDic6->setObject(__String::create("Scarf"), "gNameEn");
    giftDic6->setObject(__String::create("gift/gift6.png"), "gPicture");
    giftDic6->setObject(__String::create("2"), "gLevel");
    giftDic6->setObject(__String::create("有围巾就会很温暖吗？"), "gDecription");
    giftDic6->setObject(__String::create("0"), "gCount");
    
    __Array* giftArray = __Array::create(giftDic1,giftDic2,giftDic3,giftDic4,giftDic5,giftDic6, NULL);

    return giftArray;
}


extern __Dictionary *giftDicDataWithGid(int gid) {
    __Dictionary *dataDic = __Dictionary::create();
    __Array* giftArray = giftDictionaryArray();
    for (int i = 0; i < giftArray->count(); i++) {
        __Dictionary *temDic = (__Dictionary *)giftArray->getObjectAtIndex(i);
        int tempid = temDic->valueForKey("gid")->intValue();
        if (tempid == gid) {
            dataDic = temDic;
        }
    }
    
    return dataDic;
}
