package com.umeng.analytics;

/**
 * Created by zhz on 2017/9/13.
 */
import java.util.Map;
import java.util.List;
import java.util.HashMap;
import java.util.Iterator;
import java.util.ArrayList;
import android.content.Context;
import android.util.Log;

import com.umeng.analytics.MobclickAgent;
import com.umeng.analytics.game.UMGameAgent;
import com.umeng.commonsdk.UMConfigure;
import com.umeng.analytics.MobclickAgent.EScenarioType;
import com.umeng.analytics.dplus.UMADplus;

public class UMGameAnalytics {
    private static String wrapperType = "Cocos2d-x";
    private static String wrapperVersion = "4.7.1";

    private static Context mCtx = null;

    public static void init(Context context){
        if(context == null){
            Log.e("umcocos2dx","context is null");
            return;
        }
        mCtx = context.getApplicationContext();
        MobclickAgent.setScenarioType(context,EScenarioType.E_DUM_GAME);
        UMGameAgent.init(context);
    }

    public static void event(String event_id, String label){
        if(mCtx != null){
            if(label == null){
                MobclickAgent.onEvent(mCtx,event_id);
            }else{
                MobclickAgent.onEvent(mCtx,event_id,label);
            }
        }
    }

    public static void event(String event_id,Map<String, String> map){
        if(mCtx != null){
            MobclickAgent.onEvent(mCtx,event_id,map);
        }
    }

    public static void event(String event_id,Map<String, String> map,int value){
        if(mCtx != null){
            MobclickAgent.onEventValue(mCtx,event_id,map,value);
        }
    }
    public static void track(String eventName,Map<String, String> map){

        Map<String , Object> pMap = new HashMap<String,Object>();
        Iterator entries = map.entrySet().iterator();
        while (entries.hasNext()) {

            Map.Entry entry = (Map.Entry) entries.next();

            String key = (String)entry.getKey();


            String value = (String)entry.getValue();
            pMap.put(key, (Object)value);
        }
        UMADplus.track(mCtx,eventName,pMap);
    }
    public static void track(String eventName){
        UMADplus.track(mCtx,eventName);
    }
    public static void registerSuperProperty(Map<String, String> map){
        Iterator entries = map.entrySet().iterator();
        while (entries.hasNext()) {
            Map.Entry entry = (Map.Entry) entries.next();

            String key = (String)entry.getKey();

            String value = (String)entry.getValue();
            UMADplus.registerSuperProperty(mCtx,key,(Object)value);
        }
    }
    public static void unregisterSuperProperty(String propertyName){
        UMADplus.unregisterSuperProperty(mCtx, propertyName);
    }
    public static String getSuperProperty(String propertyName){
        return (String)UMADplus.getSuperProperty(mCtx, propertyName);
    }
    public static String getSuperProperties(){
        return UMADplus.getSuperProperties(mCtx);
    }

    public static void clearSuperProperties(){
        UMADplus.clearSuperProperties(mCtx);
    }

    public static void setFirstLaunchEvent(String[] events){
        List list = new ArrayList();
        for(int i=0;i<events.length;i++){
            list.add(events[i]);
        }
        UMADplus.setFirstLaunchEvent(mCtx, list);
    }
}
