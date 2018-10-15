package com.umeng.common;

import java.lang.reflect.InvocationTargetException;
import java.lang.reflect.Method;

import android.content.Context;
import android.graphics.YuvImage;
import android.util.Log;
import com.umeng.commonsdk.UMConfigure;

/**
 * Created by wangfei on 17/9/14.
 */

public class UMCocosConfigure {

    public native static void InitCC();
    public static void init(Context context, String appkey, String channel, int type, String secret){
        InitCC();
        UMConfigure.init(context,appkey,channel,type,secret);
    }
    public static void initCocos(String v,String t){

        Method method = null;
        try {
            Log.e("xxxxxx","v="+v+"  t="+t);
            Class<?> config = Class.forName("com.umeng.commonsdk.UMConfigure");
            method = config.getDeclaredMethod("setWraperType", String.class, String.class);
            method.setAccessible(true);
            method.invoke(null, v,t);
        } catch (NoSuchMethodException | InvocationTargetException | IllegalAccessException | ClassNotFoundException e) {
            e.printStackTrace();
        }
    }
    public static void setLog(boolean able){
        Log.e("cocos2d-x","success");
       UMConfigure.setLogEnabled(able);
    }
}
