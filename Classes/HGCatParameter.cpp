//
//  HGCatParameter.cpp
//  HealthGo2
//
//  Created by GDzqw on 2018/4/21.
//

#include "HGCatParameter.h"
extern __Array* petDictionaryArrayLevel1() {
    __Dictionary *catDic0 = __Dictionary::create();
    catDic0->setObject(__String::create("0"), "pid");
    catDic0->setObject(__String::create("pet/catA.png"), "petURL");
    catDic0->setObject(__String::create("catsport/sportCatA.plist"), "petSportURL");
    catDic0->setObject(__String::create("15"), "petSportCount");
    catDic0->setObject(__String::create("180"), "petWidth");
    catDic0->setObject(__String::create("黑糖"), "petName");
    catDic0->setObject(__String::create("Brown Sugar"), "petNameEn");
    catDic0->setObject(__String::create("100"), "petX");
    catDic0->setObject(__String::create("125"), "petY");
    catDic0->setObject(__String::create("1"), "petLevel");
    
    __Dictionary *catDic1 = __Dictionary::create();
    catDic1->setObject(__String::create("1"), "pid");
    catDic1->setObject(__String::create("pet/catB.png"), "petURL");
    catDic1->setObject(__String::create("150"), "petWidth");
    catDic1->setObject(__String::create("豆子"), "petName");
    catDic1->setObject(__String::create("Soya"), "petNameEn");
    catDic1->setObject(__String::create("280"), "petX");
    catDic1->setObject(__String::create("175"), "petY");
    catDic1->setObject(__String::create("1"), "petLevel");
    
    __Dictionary *catDic2 = __Dictionary::create();
    catDic2->setObject(__String::create("2"), "pid");
    catDic2->setObject(__String::create("pet/catC.png"), "petURL");
    catDic2->setObject(__String::create("200"), "petWidth");
    catDic2->setObject(__String::create("包子"), "petName");
    catDic2->setObject(__String::create("Bun"), "petNameEn");
    catDic2->setObject(__String::create("90"), "petX");
    catDic2->setObject(__String::create("260"), "petY");
    catDic2->setObject(__String::create("3"), "petLevel");
    
    __Dictionary *catDic3 = __Dictionary::create();
    catDic3->setObject(__String::create("3"), "pid");
    catDic3->setObject(__String::create("pet/catD.png"), "petURL");
    catDic3->setObject(__String::create("150"), "petWidth");
    catDic3->setObject(__String::create("咸鱼"), "petName");
    catDic3->setObject(__String::create("Salted Fish"), "petNameEn");
    catDic3->setObject(__String::create("430"), "petX");
    catDic3->setObject(__String::create("23"), "petY");
    catDic3->setObject(__String::create("3"), "petLevel");
    
    __Dictionary *catDic4 = __Dictionary::create();
    catDic4->setObject(__String::create("4"), "pid");
    catDic4->setObject(__String::create("pet/catE.png"), "petURL");
    catDic4->setObject(__String::create("150"), "petWidth");
    catDic4->setObject(__String::create("布丁"), "petName");
    catDic4->setObject(__String::create("Pudding"), "petNameEn");
    catDic4->setObject(__String::create("430"), "petX");
    catDic4->setObject(__String::create("205"), "petY");
    catDic4->setObject(__String::create("2"), "petLevel");
    
    __Dictionary *catDic5 = __Dictionary::create();
    catDic5->setObject(__String::create("5"), "pid");
    catDic5->setObject(__String::create("pet/catF.png"), "petURL");
    catDic5->setObject(__String::create("160"), "petWidth");
    catDic5->setObject(__String::create("茉莉"), "petName");
    catDic5->setObject(__String::create("Jasmine"), "petNameEn");
    catDic5->setObject(__String::create("595"), "petX");
    catDic5->setObject(__String::create("225"), "petY");
    catDic5->setObject(__String::create("2"), "petLevel");
    
    __Dictionary *catDic6 = __Dictionary::create();
    catDic6->setObject(__String::create("6"), "pid");
    catDic6->setObject(__String::create("pet/catG.png"), "petURL");
    catDic6->setObject(__String::create("150"), "petWidth");
    catDic6->setObject(__String::create("泡芙"), "petName");
    catDic6->setObject(__String::create("Puff"), "petNameEn");
    catDic6->setObject(__String::create("395"), "petX");
    catDic6->setObject(__String::create("413"), "petY");
    catDic6->setObject(__String::create("1"), "petLevel");
    
    __Dictionary *catDic7 = __Dictionary::create();
    catDic7->setObject(__String::create("7"), "pid");
    catDic7->setObject(__String::create("pet/catH.png"), "petURL");
    catDic7->setObject(__String::create("180"), "petWidth");
    catDic7->setObject(__String::create("catsport/sportCatH.plist"), "petSportURL");
    catDic7->setObject(__String::create("28"), "petSportCount");
    catDic7->setObject(__String::create("西瓜大喵"), "petName");
    catDic7->setObject(__String::create("DAV"), "petNameEn");
    catDic7->setObject(__String::create("610"), "petX");
    catDic7->setObject(__String::create("74"), "petY");
    catDic7->setObject(__String::create("3"), "petLevel");
    
    __Dictionary *catDic8 = __Dictionary::create();
    catDic8->setObject(__String::create("8"), "pid");
    catDic8->setObject(__String::create("pet/catI.png"), "petURL");
    catDic8->setObject(__String::create("150"), "petWidth");
    catDic8->setObject(__String::create("泡泡"), "petName");
    catDic8->setObject(__String::create("Bubble"), "petNameEn");
    catDic8->setObject(__String::create("735"), "petX");
    catDic8->setObject(__String::create("135"), "petY");
    catDic8->setObject(__String::create("1"), "petLevel");
    
    __Array* petLevel1Array = __Array::create(catDic0,catDic1,catDic2,catDic3,catDic4,catDic5,catDic6,catDic7,catDic8,NULL);
    return petLevel1Array;
}

extern __Array* petDictionaryArrayLevel2() {
    __Dictionary *cat2Dic0 = __Dictionary::create();
    cat2Dic0->setObject(__String::create("9"), "pid");
    cat2Dic0->setObject(__String::create("pet/catL2A.png"), "petURL");
    cat2Dic0->setObject(__String::create("200"), "petWidth");
    cat2Dic0->setObject(__String::create("泡泡"), "petName");
    cat2Dic0->setObject(__String::create("Bubble"), "petNameEn");
    cat2Dic0->setObject(__String::create("170"), "petX");
    cat2Dic0->setObject(__String::create("5"), "petY");
    cat2Dic0->setObject(__String::create("3"), "petLevel");
    
    __Dictionary *cat2Dic1 = __Dictionary::create();
    cat2Dic1->setObject(__String::create("10"), "pid");
    cat2Dic1->setObject(__String::create("pet/catL2B.png"), "petURL");
    cat2Dic1->setObject(__String::create("200"), "petWidth");
    cat2Dic1->setObject(__String::create("咸鱼"), "petName");
    cat2Dic1->setObject(__String::create("Salted Fish"), "petNameEn");
    cat2Dic1->setObject(__String::create("650"), "petX");
    cat2Dic1->setObject(__String::create("5"), "petY");
    cat2Dic1->setObject(__String::create("3"), "petLevel");
    
    __Dictionary *cat2Dic2 = __Dictionary::create();
    cat2Dic2->setObject(__String::create("11"), "pid");
    cat2Dic2->setObject(__String::create("pet/catL2C.png"), "petURL");
    cat2Dic2->setObject(__String::create("200"), "petWidth");
    cat2Dic2->setObject(__String::create("大王喵"), "petName");
    cat2Dic2->setObject(__String::create("King Miao"), "petNameEn");
    cat2Dic2->setObject(__String::create("445"), "petX");
    cat2Dic2->setObject(__String::create("5"), "petY");
    cat2Dic2->setObject(__String::create("5"), "petLevel");
    
    __Dictionary *cat2Dic3 = __Dictionary::create();
    cat2Dic3->setObject(__String::create("12"), "pid");
    cat2Dic3->setObject(__String::create("pet/catL2D.png"), "petURL");
    cat2Dic3->setObject(__String::create("200"), "petWidth");
    cat2Dic3->setObject(__String::create("泡芙"), "petName");
    cat2Dic3->setObject(__String::create("Puff"), "petNameEn");
    cat2Dic3->setObject(__String::create("135"), "petX");
    cat2Dic3->setObject(__String::create("220"), "petY");
    cat2Dic3->setObject(__String::create("1"), "petLevel");
    
    __Dictionary *cat2Dic4 = __Dictionary::create();
    cat2Dic4->setObject(__String::create("13"), "pid");
    cat2Dic4->setObject(__String::create("pet/catL2E.png"), "petURL");
    cat2Dic4->setObject(__String::create("200"), "petWidth");
    cat2Dic4->setObject(__String::create("豆子"), "petName");
    cat2Dic4->setObject(__String::create("Soya"), "petNameEn");
    cat2Dic4->setObject(__String::create("685"), "petX");
    cat2Dic4->setObject(__String::create("215"), "petY");
    cat2Dic4->setObject(__String::create("1"), "petLevel");
    
    __Dictionary *cat2Dic5 = __Dictionary::create();
    cat2Dic5->setObject(__String::create("14"), "pid");
    cat2Dic5->setObject(__String::create("pet/catL2F.png"), "petURL");
    cat2Dic5->setObject(__String::create("220"), "petWidth");
    cat2Dic5->setObject(__String::create("布丁"), "petName");
    cat2Dic5->setObject(__String::create("Pudding"), "petNameEn");
    cat2Dic5->setObject(__String::create("40"), "petX");
    cat2Dic5->setObject(__String::create("310"), "petY");
    cat2Dic5->setObject(__String::create("1"), "petLevel");
    
    __Dictionary *cat2Dic6 = __Dictionary::create();
    cat2Dic6->setObject(__String::create("15"), "pid");
    cat2Dic6->setObject(__String::create("pet/catL2G.png"), "petURL");
    cat2Dic6->setObject(__String::create("200"), "petWidth");
    cat2Dic6->setObject(__String::create("黑糖"), "petName");
    cat2Dic6->setObject(__String::create("Brown Sugar"), "petNameEn");
    cat2Dic6->setObject(__String::create("765"), "petX");
    cat2Dic6->setObject(__String::create("325"), "petY");
    cat2Dic6->setObject(__String::create("1"), "petLevel");
    
    __Dictionary *cat2Dic7 = __Dictionary::create();
    cat2Dic7->setObject(__String::create("16"), "pid");
    cat2Dic7->setObject(__String::create("pet/catL2H.png"), "petURL");
    cat2Dic7->setObject(__String::create("240"), "petWidth");
    cat2Dic7->setObject(__String::create("美人喵"), "petName");
    cat2Dic7->setObject(__String::create("Beauty Miao"), "petNameEn");
    cat2Dic7->setObject(__String::create("390"), "petX");
    cat2Dic7->setObject(__String::create("290"), "petY");
    cat2Dic7->setObject(__String::create("4"), "petLevel");

    __Array* petLevel2Array = __Array::create(cat2Dic0,cat2Dic1,cat2Dic2,cat2Dic3,cat2Dic4,cat2Dic5,cat2Dic6,cat2Dic7,NULL);
    return petLevel2Array;
}

extern __Dictionary *petDicDataWithPid(int pid) {
    __Dictionary *dataDic = __Dictionary::create();
    __Array* petlevel1Array = petDictionaryArrayLevel1();
    if (pid >= petlevel1Array->count()) {
        __Array* petlevel2Array = petDictionaryArrayLevel2();
        for (int i = 0; i < petlevel2Array->count(); i++) {
            __Dictionary *temDic = (__Dictionary *)petlevel2Array->getObjectAtIndex(i);
            int tempid = temDic->valueForKey("pid")->intValue();
            if (tempid == pid) {
                dataDic = temDic;
            }
        }
    } else {
        for (int i = 0; i < petlevel1Array->count(); i++) {
            __Dictionary *temDic = (__Dictionary *)petlevel1Array->getObjectAtIndex(i);
            int tempid = temDic->valueForKey("pid")->intValue();
            if (tempid == pid) {
                dataDic = temDic;
            }
        }
    }
    return dataDic;
}
