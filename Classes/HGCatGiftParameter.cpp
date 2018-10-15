//
//  HGCatGiftParameter.cpp
//  HealthGo2
//
//  Created by GDzqw on 2018/6/13.
//

#include "HGCatGiftParameter.h"
#include <stdio.h>

__Array *giftArrayGetWithPid(int pid) {
    __Array* giftArray = __Array::create();
    
    if (pid == 0) {
        __Dictionary *giftDic1 = __Dictionary::create();
        giftDic1->setObject(__String::create("1"), "gid");
        giftDic1->setObject(__String::create("0.5"), "probility");
        
        __Dictionary *giftDic2 = __Dictionary::create();
        giftDic2->setObject(__String::create("5"), "gid");
        giftDic2->setObject(__String::create("0.3"), "probility");
        
        __Dictionary *giftDic3 = __Dictionary::create();
        giftDic3->setObject(__String::create("4"), "gid");
        giftDic3->setObject(__String::create("0.2"), "probility");
        
        giftArray->addObject(giftDic1);
        giftArray->addObject(giftDic2);
        giftArray->addObject(giftDic3);
    } else if (pid == 1) {
        __Dictionary *giftDic1 = __Dictionary::create();
        giftDic1->setObject(__String::create("4"), "gid");
        giftDic1->setObject(__String::create("0.6"), "probility");
        
        __Dictionary *giftDic2 = __Dictionary::create();
        giftDic2->setObject(__String::create("5"), "gid");
        giftDic2->setObject(__String::create("0.2"), "probility");
        
        __Dictionary *giftDic3 = __Dictionary::create();
        giftDic3->setObject(__String::create("6"), "gid");
        giftDic3->setObject(__String::create("0.2"), "probility");
        
        giftArray->addObject(giftDic1);
        giftArray->addObject(giftDic2);
        giftArray->addObject(giftDic3);
    } else if (pid == 2) {
        __Dictionary *giftDic1 = __Dictionary::create();
        giftDic1->setObject(__String::create("2"), "gid");
        giftDic1->setObject(__String::create("0.6"), "probility");
        
        __Dictionary *giftDic2 = __Dictionary::create();
        giftDic2->setObject(__String::create("6"), "gid");
        giftDic2->setObject(__String::create("0.4"), "probility");
        
        giftArray->addObject(giftDic1);
        giftArray->addObject(giftDic2);
    } else if (pid == 3) {
        __Dictionary *giftDic1 = __Dictionary::create();
        giftDic1->setObject(__String::create("4"), "gid");
        giftDic1->setObject(__String::create("0.5"), "probility");
        
        __Dictionary *giftDic2 = __Dictionary::create();
        giftDic2->setObject(__String::create("5"), "gid");
        giftDic2->setObject(__String::create("0.5"), "probility");
        
        giftArray->addObject(giftDic1);
        giftArray->addObject(giftDic2);
    } else if (pid == 4) {
        __Dictionary *giftDic1 = __Dictionary::create();
        giftDic1->setObject(__String::create("3"), "gid");
        giftDic1->setObject(__String::create("0.7"), "probility");
        
        __Dictionary *giftDic2 = __Dictionary::create();
        giftDic2->setObject(__String::create("4"), "gid");
        giftDic2->setObject(__String::create("0.3"), "probility");
        
        giftArray->addObject(giftDic1);
        giftArray->addObject(giftDic2);
    } else if (pid == 5) {
        __Dictionary *giftDic1 = __Dictionary::create();
        giftDic1->setObject(__String::create("3"), "gid");
        giftDic1->setObject(__String::create("0.6"), "probility");
        
        __Dictionary *giftDic2 = __Dictionary::create();
        giftDic2->setObject(__String::create("4"), "gid");
        giftDic2->setObject(__String::create("0.4"), "probility");
        
        giftArray->addObject(giftDic1);
        giftArray->addObject(giftDic2);
    } else if (pid == 6) {
        __Dictionary *giftDic1 = __Dictionary::create();
        giftDic1->setObject(__String::create("4"), "gid");
        giftDic1->setObject(__String::create("0.6"), "probility");
        
        __Dictionary *giftDic2 = __Dictionary::create();
        giftDic2->setObject(__String::create("2"), "gid");
        giftDic2->setObject(__String::create("0.4"), "probility");
        
        giftArray->addObject(giftDic1);
        giftArray->addObject(giftDic2);
    } else if (pid == 7) {
        __Dictionary *giftDic1 = __Dictionary::create();
        giftDic1->setObject(__String::create("2"), "gid");
        giftDic1->setObject(__String::create("0.4"), "probility");
        
        
        __Dictionary *giftDic2 = __Dictionary::create();
        giftDic2->setObject(__String::create("6"), "gid");
        giftDic2->setObject(__String::create("0.6"), "probility");
        
        giftArray->addObject(giftDic1);
        giftArray->addObject(giftDic2);
    } else if (pid == 8) {
        __Dictionary *giftDic1 = __Dictionary::create();
        giftDic1->setObject(__String::create("2"), "gid");
        giftDic1->setObject(__String::create("0.6"), "probility");
        
        __Dictionary *giftDic2 = __Dictionary::create();
        giftDic2->setObject(__String::create("6"), "gid");
        giftDic2->setObject(__String::create("0.4"), "probility");
        
        giftArray->addObject(giftDic1);
        giftArray->addObject(giftDic2);
    } else if (pid == 9) {
        __Dictionary *giftDic1 = __Dictionary::create();
        giftDic1->setObject(__String::create("2"), "gid");
        giftDic1->setObject(__String::create("0.6"), "probility");
        
        __Dictionary *giftDic2 = __Dictionary::create();
        giftDic2->setObject(__String::create("4"), "gid");
        giftDic2->setObject(__String::create("0.4"), "probility");
        
        giftArray->addObject(giftDic1);
        giftArray->addObject(giftDic2);
    } else if (pid == 10) {
        __Dictionary *giftDic1 = __Dictionary::create();
        giftDic1->setObject(__String::create("4"), "gid");
        giftDic1->setObject(__String::create("0.6"), "probility");
        
        __Dictionary *giftDic2 = __Dictionary::create();
        giftDic2->setObject(__String::create("5"), "gid");
        giftDic2->setObject(__String::create("0.4"), "probility");
        
        giftArray->addObject(giftDic1);
        giftArray->addObject(giftDic2);
    } else if (pid == 11) {
        __Dictionary *giftDic1 = __Dictionary::create();
        giftDic1->setObject(__String::create("1"), "gid");
        giftDic1->setObject(__String::create("0.5"), "probility");
        
        __Dictionary *giftDic2 = __Dictionary::create();
        giftDic2->setObject(__String::create("2"), "gid");
        giftDic2->setObject(__String::create("0.1"), "probility");
        
        __Dictionary *giftDic3 = __Dictionary::create();
        giftDic3->setObject(__String::create("3"), "gid");
        giftDic3->setObject(__String::create("0.1"), "probility");
        
        __Dictionary *giftDic4 = __Dictionary::create();
        giftDic4->setObject(__String::create("4"), "gid");
        giftDic4->setObject(__String::create("0.1"), "probility");
        
        __Dictionary *giftDic5 = __Dictionary::create();
        giftDic5->setObject(__String::create("5"), "gid");
        giftDic5->setObject(__String::create("0.1"), "probility");
        
        __Dictionary *giftDic6 = __Dictionary::create();
        giftDic6->setObject(__String::create("6"), "gid");
        giftDic6->setObject(__String::create("0.1"), "probility");
        
        giftArray->addObject(giftDic1);
        giftArray->addObject(giftDic2);
        giftArray->addObject(giftDic3);
        giftArray->addObject(giftDic4);
        giftArray->addObject(giftDic5);
        giftArray->addObject(giftDic6);
    } else if (pid == 12) {
        __Dictionary *giftDic1 = __Dictionary::create();
        giftDic1->setObject(__String::create("5"), "gid");
        giftDic1->setObject(__String::create("0.5"), "probility");
        
        __Dictionary *giftDic2 = __Dictionary::create();
        giftDic2->setObject(__String::create("6"), "gid");
        giftDic2->setObject(__String::create("0.5"), "probility");
        
        giftArray->addObject(giftDic1);
        giftArray->addObject(giftDic2);
    } else if (pid == 13) {
        __Dictionary *giftDic1 = __Dictionary::create();
        giftDic1->setObject(__String::create("2"), "gid");
        giftDic1->setObject(__String::create("0.5"), "probility");
        
        __Dictionary *giftDic2 = __Dictionary::create();
        giftDic2->setObject(__String::create("4"), "gid");
        giftDic2->setObject(__String::create("0.5"), "probility");
        
        giftArray->addObject(giftDic1);
        giftArray->addObject(giftDic2);
    } else if (pid == 14) {
        __Dictionary *giftDic1 = __Dictionary::create();
        giftDic1->setObject(__String::create("3"), "gid");
        giftDic1->setObject(__String::create("0.6"), "probility");
        
        __Dictionary *giftDic2 = __Dictionary::create();
        giftDic2->setObject(__String::create("4"), "gid");
        giftDic2->setObject(__String::create("0.4"), "probility");
        
        giftArray->addObject(giftDic1);
        giftArray->addObject(giftDic2);
    } else if (pid == 15) {
        __Dictionary *giftDic1 = __Dictionary::create();
        giftDic1->setObject(__String::create("1"), "gid");
        giftDic1->setObject(__String::create("0.6"), "probility");
        
        __Dictionary *giftDic2 = __Dictionary::create();
        giftDic2->setObject(__String::create("3"), "gid");
        giftDic2->setObject(__String::create("0.4"), "probility");
        
        giftArray->addObject(giftDic1);
        giftArray->addObject(giftDic2);
    } else if (pid == 16) {
        __Dictionary *giftDic1 = __Dictionary::create();
        giftDic1->setObject(__String::create("1"), "gid");
        giftDic1->setObject(__String::create("0.2"), "probility");
        
        __Dictionary *giftDic2 = __Dictionary::create();
        giftDic2->setObject(__String::create("2"), "gid");
        giftDic2->setObject(__String::create("0.2"), "probility");
        
        __Dictionary *giftDic3 = __Dictionary::create();
        giftDic3->setObject(__String::create("3"), "gid");
        giftDic3->setObject(__String::create("0.2"), "probility");
        
        __Dictionary *giftDic4 = __Dictionary::create();
        giftDic4->setObject(__String::create("4"), "gid");
        giftDic4->setObject(__String::create("0.2"), "probility");
        
        __Dictionary *giftDic5 = __Dictionary::create();
        giftDic5->setObject(__String::create("5"), "gid");
        giftDic5->setObject(__String::create("0.2"), "probility");
        
        giftArray->addObject(giftDic1);
        giftArray->addObject(giftDic2);
        giftArray->addObject(giftDic3);
        giftArray->addObject(giftDic4);
        giftArray->addObject(giftDic5);
    } else {
        __Dictionary *giftDic1 = __Dictionary::create();
        giftDic1->setObject(__String::create("1"), "gid");
        giftDic1->setObject(__String::create("0.5"), "probility");
        
        __Dictionary *giftDic2 = __Dictionary::create();
        giftDic2->setObject(__String::create("2"), "gid");
        giftDic2->setObject(__String::create("0.5"), "probility");
        
        giftArray->addObject(giftDic1);
        giftArray->addObject(giftDic2);
    }
    
    return giftArray;
}

__Array *petArrayGetWithGifLevel1(int gidA, int gidB, int gidC) {
    __Array *petArray = __Array::create();
    __Dictionary *petHeiTangDic = __Dictionary::create();
    petHeiTangDic->setObject(__String::create("0"), "pid");
    petHeiTangDic->setObject(__String::create("0.2"), "probility");
    petArray->addObject(petHeiTangDic);
    
    __Dictionary *petDouziDic = __Dictionary::create();
    petDouziDic->setObject(__String::create("1"), "pid");
    petDouziDic->setObject(__String::create("0.2"), "probility");
    petArray->addObject(petDouziDic);
    
    __Dictionary *petBuDingDic = __Dictionary::create();
    petBuDingDic->setObject(__String::create("4"), "pid");
    petBuDingDic->setObject(__String::create("0.2"), "probility");
    petArray->addObject(petBuDingDic);
    
    __Dictionary *petPaoFuDic = __Dictionary::create();
    petPaoFuDic->setObject(__String::create("6"), "pid");
    petPaoFuDic->setObject(__String::create("0.2"), "probility");
    petArray->addObject(petPaoFuDic);
    
    
    if (gidA == 0 && gidB == 0 && gidC == 0) {
        
    } else {
        if (gidA == 2 || gidB == 2 || gidC == 2) {
            __Dictionary *petBaoZiDic = __Dictionary::create();
            petBaoZiDic->setObject(__String::create("2"), "pid");
            petBaoZiDic->setObject(__String::create("0.3"), "probility");
            petArray->addObject(petBaoZiDic);
        }
        
        if (gidA == 5 || gidB == 5 || gidC == 5) {
            __Dictionary *petXianYuDic = __Dictionary::create();
            petXianYuDic->setObject(__String::create("3"), "pid");
            petXianYuDic->setObject(__String::create("0.3"), "probility");
            petArray->addObject(petXianYuDic);
        }
        
        if (gidA == 6 || gidB == 6 || gidC == 6 || gidA == 1 || gidB == 1 || gidC == 1) {
            __Dictionary *petChaMiDic = __Dictionary::create();
            petChaMiDic->setObject(__String::create("7"), "pid");
            petChaMiDic->setObject(__String::create("0.5"), "probility");
            petArray->addObject(petChaMiDic);
        }
        
        if ((gidA == 2 && gidB == 4)||(gidA == 4 && gidB == 2)||(gidB == 2 && gidC == 4)||(gidC == 4 && gidB == 2)) {
            __Dictionary *petPaoPaoDic = __Dictionary::create();
            petPaoPaoDic->setObject(__String::create("8"), "pid");
            petPaoPaoDic->setObject(__String::create("0.5"), "probility");
            petArray->addObject(petPaoPaoDic);
        }
        
        if ((gidA == 5 && gidB == 6)||(gidA == 6 && gidB == 5)||(gidB == 5 && gidC == 6)||(gidC == 6 && gidB == 5)) {
            __Dictionary *petMolioDic = __Dictionary::create();
            petMolioDic->setObject(__String::create("5"), "pid");
            petMolioDic->setObject(__String::create("0.5"), "probility");
            petArray->addObject(petMolioDic);
        }
    }
    
    return petArray;
}

__Array *petArrayGetWithGifLevel2(int gidA, int gidB, int gidC) {
    __Array *petArray = __Array::create();
    __Dictionary *petPaofuDic = __Dictionary::create();
    petPaofuDic->setObject(__String::create("12"), "pid");
    petPaofuDic->setObject(__String::create("0.2"), "probility");
    petArray->addObject(petPaofuDic);
    
    __Dictionary *petDouziDic = __Dictionary::create();
    petDouziDic->setObject(__String::create("13"), "pid");
    petDouziDic->setObject(__String::create("0.2"), "probility");
    petArray->addObject(petDouziDic);
    
    __Dictionary *petBuDingDic = __Dictionary::create();
    petBuDingDic->setObject(__String::create("14"), "pid");
    petBuDingDic->setObject(__String::create("0.2"), "probility");
    petArray->addObject(petBuDingDic);
    
    __Dictionary *petHeiTangDic = __Dictionary::create();
    petHeiTangDic->setObject(__String::create("15"), "pid");
    petHeiTangDic->setObject(__String::create("0.2"), "probility");
    petArray->addObject(petHeiTangDic);
    
    if (gidA == 4 || gidB == 4 || gidC == 4) {
        __Dictionary *petDouZiDic = __Dictionary::create();
        petDouZiDic->setObject(__String::create("9"), "pid");
        petDouZiDic->setObject(__String::create("0.3"), "probility");
        petArray->addObject(petDouZiDic);
    }
    
    if (gidA == 1 || gidB == 1 || gidC == 1) {
        __Dictionary *petXianYuDic = __Dictionary::create();
        petXianYuDic->setObject(__String::create("10"), "pid");
        petXianYuDic->setObject(__String::create("0.3"), "probility");
        petArray->addObject(petXianYuDic);
    }
    
    if ((gidA == 2 && gidB == 3 && gidC == 4) || (gidA == 2 && gidB == 4  && gidC == 3) || (gidA == 4 && gidB == 2  && gidC == 3) || (gidA == 4 && gidB == 3  && gidC == 2)) {
        __Dictionary *petDaWangDic = __Dictionary::create();
        petDaWangDic->setObject(__String::create("11"), "pid");
        petDaWangDic->setObject(__String::create("0.6"), "probility");
        petArray->addObject(petDaWangDic);
    }
    
    if ((gidA == 1 && gidB == 3)||(gidA == 3 && gidB == 1)||(gidB == 1 && gidC == 3)||(gidC == 3 && gidB == 1)) {
        __Dictionary *petDaWangDic = __Dictionary::create();
        petDaWangDic->setObject(__String::create("16"), "pid");
        petDaWangDic->setObject(__String::create("0.4"), "probility");
        petArray->addObject(petDaWangDic);
    }
    
    return petArray;
}
