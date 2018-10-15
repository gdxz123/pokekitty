package com.umeng.social;

import java.io.File;
import java.io.IOException;
import java.io.InputStream;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

import android.app.Activity;
import android.content.Intent;
import android.content.res.AssetManager;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.os.Bundle;
import android.os.Handler;
import android.os.Looper;
import android.text.TextUtils;
import android.widget.PopupWindow.OnDismissListener;
import com.umeng.socialize.ShareAction;
import com.umeng.socialize.UMAuthListener;
import com.umeng.socialize.UMShareAPI;
import com.umeng.socialize.UMShareListener;
import com.umeng.socialize.bean.SHARE_MEDIA;
import com.umeng.socialize.bean.StatusCode;
import com.umeng.socialize.common.ResContainer;
import com.umeng.socialize.common.SocializeConstants;
import com.umeng.socialize.media.UMImage;
import com.umeng.socialize.media.UMWeb;
import com.umeng.socialize.net.utils.SocializeNetUtils;
import com.umeng.socialize.shareboard.ShareBoardConfig;
import com.umeng.socialize.shareboard.SnsPlatform;
import com.umeng.socialize.utils.Log;
import com.umeng.socialize.utils.ShareBoardlistener;
import org.cocos2dx.lib.Cocos2dxActivity;
import org.cocos2dx.lib.Cocos2dxGLSurfaceView;

/**
 * 友盟Social Android SDK的控制器, cocos2d-x sdk 通过jni代码调用相关的静态函数实现对应的功能.
 * 该sdk目前提供的功能有授权、分享(打开分享面板来分享、底层api分享)、删除授权、判断某个平台是否授权、设置文字分享内容、设置图片分享内容的功能,
 * 并且将结果回调给cocos2d-x sdk.
 *
 * @author mrsimple
 *
 */
public class CCUMSocialController {

	//	/**
//	 * 友盟社会化组件控制器
//	 */
//	private static UMSocialService mController;
//	/**
//	 * Social SDK 配置类, 单例
//	 */
//	private static SocializeConfig mSocializeConfig = SocializeConfig
//			.getSocializeConfig();
	// Cocos2dxActivity对象
	private static Cocos2dxActivity mActivity;
	/**
	 * log tag
	 */
	private static final String TAG = CCUMSocialController.class
			.getSimpleName();

	/**
	 * 主线程的消息Handler
	 */
	private static Handler mSDKHandler = new Handler(Looper.getMainLooper());
	private static final int DELAY_MS = 50;
	private static String DESCRIPTOR;
	private static ShareBoardConfig config = new ShareBoardConfig();
	// ******* 以下字段的调用都在supportPlatfrom函数中 *********
	/**
	 * QQ和QQ空间app id
	 */
	private static String QQ_QZONE_APP_ID = "";
	/**
	 * QQ和QQ空间app key
	 */
	private static String QQ_QZONE_APP_KEY = "";

	/**
	 * 微信或者微信朋友圈 app id
	 */
	private static String WEIXIN_APP_ID = "";

	/**
	 * facebook app id
	 */
	private static String FACEBOOK_APP_ID = "";
	/**
	 * 易信或者易信朋友圈app id, 需要添加易信或者易信朋友圈平台的支持, 请参考线上文档
	 */
	private static String YIXIN_APPKEY = "";
	/**
	 * 来往和来往动态的app id, 需要添加来往或者来往动态平台的支持, 请参考线上文档
	 */
	private static String LAIWANG_APPID = "";
	/**
	 * 来往和来往动态的app key, 需要添加来往或者来往动态平台的支持, 请参考线上文档
	 */
	private static String LAIWANG_APPKEY = "";
	/**
	 * 当前应用名称,用于显示在来往分享来源上
	 */
	private static String LAIWANG_APP_NAME = "";
	/**
	 * 在某些平台的分享中， 希望用户点击该分享内容跳转到的目标平台, 一般为app的官网或者下载地址
	 */
	private static String TARGET_URL = "http://www.umeng.com/social";

	/**
	 * 初始化SDK
	 *
	 * @param activity
	 *            游戏的Cocos2dxActivity类型
	 * @param descriptor
	 *            SDK的字符串描述符
	 */
	private static UMShareAPI mShareAPI = null;
	private static 	HashMap<String , platformShareCotent> map = new HashMap<String , platformShareCotent>();
	private static ShareAction openBoardAction;
	private static ShareAction shareAction;
	private static ArrayList<Integer> platforms = new ArrayList<Integer>();
	public static void initSocialSDK(final Activity activity) {

		runOnMainThread(new Runnable() {

			@Override
			public void run() {
//				OnAuthorizeStart(platform);
				mShareAPI = UMShareAPI.get( activity );

			}
		});

		if (activity instanceof Cocos2dxActivity) {
			mActivity = (Cocos2dxActivity) activity;
		} else {
			throw new IllegalArgumentException(
					"initSocialSDK函数的activity参数必须设置为Cocos2dxActivity类型, 且不为null. ");
		}

		openBoardAction = new ShareAction(activity);
		shareAction = new ShareAction(activity);
		// mController.getConfig().closeToast();
	}

	/**
	 * 授权回调
	 *
	 * @param requestCode
	 * @param resultCode
	 * @param data
	 */
	public static void onActivityResult(int requestCode, int resultCode,
										Intent data) {
		mShareAPI.onActivityResult(requestCode, resultCode, data);
	}

	/**
	 * 授权某个平台
	 *
	 * @param platform
	 *            授权平台的字符串表示
	 */
	public static void doAuthorize(final int platform) {
		// 检测平台的有效性

		checkActivity();

		// 在UI线程执行授权操作
		runOnMainThread(new Runnable() {

			@Override
			public void run() {
//				OnAuthorizeStart(platform);
				Log.e("xxxx run");
				mShareAPI.doOauthVerify(mActivity, getPlatform(platform), mAuthListener);

			}
		});

	}

	/**
	 * 删除平台授权
	 *
	 * @param platform
	 *            授权平台的字符串表示
	 */
	public static void deleteAuthorization(final int platform) {

		// 检测平台的有效性
		if (!isPlatformValid(platform)) {
			return;
		}

		checkActivity();

		// 在UI线程执行授权操作
		runOnMainThread(new Runnable() {

			@Override
			public void run() {
				// 删除授权
				mShareAPI.deleteOauth(mActivity, getPlatform(platform), new UMAuthListener() {
					@Override
					public void onComplete(SHARE_MEDIA share_media, int i, Map<String, String> map) {
						runOnOpenGLThread(new Runnable() {

							@Override
							public void run() {
								// 删除授权的回调, 开发者可以通过字符串来判断
								OnAuthorizeComplete(platform, StatusCode.ST_CODE_SUCCESSED,
										new String[]{"deleteOauth"},new String[]{"deleteOauth"});
							}
						});
					}

					@Override
					public void onError(SHARE_MEDIA share_media, int i, final Throwable throwable) {
						runOnOpenGLThread(new Runnable() {

							@Override
							public void run() {
								// 删除授权的回调, 开发者可以通过字符串来判断
								OnAuthorizeComplete(platform, 0,
										new String[]{throwable.getMessage()},new String[]{"deleteOauth"});
							}
						});
					}

					@Override
					public void onCancel(SHARE_MEDIA share_media, int i) {

					}

					@Override
					public void onStart(SHARE_MEDIA arg0) {
						// TODO Auto-generated method stub

					}
				});

			}
		});

		Log.d(TAG, "@@@@ deleteAuthorization");

	}
	public static void setDismissCallback(){
		config.setOnDismissListener(new OnDismissListener() {

			@Override
			public void onDismiss() {
				OnBoardDismiss();

			}
		});
	}

	public static void openShare(final int[] platforms,final String text,final String title,final String targeturl,final String image) {
		// 注册回调接口, 默认将分享回调注册要sdk

//		openBoardAction.setShareboardclickCallback(mSocialShareListener);
		checkActivity();
		SHARE_MEDIA[] dis = new SHARE_MEDIA[platforms.length];
		if (platforms != null && platforms.length > 0) {
			for (int i = 0;i<platforms.length;i++){
				dis[i] = getPlatform(platforms[i]);
			}
		}
		final SHARE_MEDIA[] disfinal = dis;
		// 在UI线程执行打开分享面板操作
		runOnMainThread(new Runnable() {
			@Override
			public void run() {
				//自定义分享面板

				config.setShareboardPostion(ShareBoardConfig.SHAREBOARD_POSITION_CENTER);
				config.setMenuItemBackgroundShape(ShareBoardConfig.BG_SHAPE_CIRCULAR); // 圆角背景
				config.setTitleVisibility(false); // 隐藏title
				config.setCancelButtonVisibility(false); // 隐藏取消按钮
				// 打开分享面板
				ShareAction shareAction = new ShareAction(mActivity);
				if (TextUtils.isEmpty(targeturl)) {
					shareAction.setDisplayList(disfinal).withText(text).setCallback(umShareListener)
							.withMedia(getUmImage(image)).open(config);
				}else {
					UMWeb web = new UMWeb(targeturl);
					web.setThumb(getUmImage(image));
					web.setTitle(title);
					web.setDescription(text);
					shareAction.setDisplayList(disfinal).withText(text).setCallback(umShareListener)
							.withMedia(web).open(config);
				}

			}
		});

		Log.d(TAG, "@@@@ openShare");

	}
	public static void openCustomShare(final int[] platforms) {
		// 注册回调接口, 默认将分享回调注册要sdk

//		openBoardAction.setShareboardclickCallback(mSocialShareListener);
		checkActivity();
		SHARE_MEDIA[] dis = new SHARE_MEDIA[platforms.length];
		if (platforms != null && platforms.length > 0) {
			for (int i = 0;i<platforms.length;i++){
				dis[i] = getPlatform(platforms[i]);
			}
		}
		final SHARE_MEDIA[] disfinal = dis;
		// 在UI线程执行打开分享面板操作
		runOnMainThread(new Runnable() {
			@Override
			public void run() {
				// 打开分享面板
				new ShareAction(mActivity).setDisplayList(disfinal).setShareboardclickCallback(shareBoardlistener)
						.open(config);
			}
		});

		Log.d(TAG, "@@@@ openShare");

	}
	private static ShareBoardlistener shareBoardlistener = new ShareBoardlistener() {

		@Override
		public void onclick(SnsPlatform snsPlatform, final SHARE_MEDIA share_media) {
			Log.e("xxxxxx  share_media="+share_media+"    "+getPlatformInt(share_media));
			OnBoard(getPlatformInt(share_media));

		}
	};
	/**˙
	 * 直接分享到某个平台, 不打开分享面板, 直接底层分享
	 *
	 * @param platform
	 *            平台对应的字符串
	 */
	public static void directShare(final int platform,final String text,final String title,final String targeturl,final String image) {
		Log.e("xxxxxx 44444");
		// 检测平台的有效性
		if (!isPlatformValid(platform)) {
			return;
		}

		checkActivity();

		// 在UI线程执行底层分享操作
		runOnMainThread(new Runnable() {

			@Override
			public void run() {
//				platformShareCotent temp = map.get(getPlatform(platform).toString());

//				if(TextUtils.isEmpty(text)){
//					text = null;
//				}
//				if(TextUtils.isEmpty(image)){
//					image = null;
//				}
//				if(TextUtils.isEmpty(title)){
//					title = null;
//
//				}
//				if(TextUtils.isEmpty(targeturl)){
//					targeturl = null;
//
//				}
				Log.e("xxxxxx 33333");
				ShareAction shareAction = new ShareAction(mActivity);
				if (TextUtils.isEmpty(targeturl)) {
					Log.e("xxxxxx 1111");
					shareAction.setPlatform(getPlatform(platform)).withText(text).setCallback(umShareListener)
							.withMedia(getUmImage(image)).share();
				}else {
					Log.e("xxxxxx 2222");
					UMWeb web = new UMWeb(targeturl);
					web.setThumb(getUmImage(image));
					web.setTitle(title);
					web.setDescription(text);
					shareAction.setPlatform(getPlatform(platform)).withText(text).setCallback(umShareListener)
							.withMedia(web).share();
				}

			}
		});

		Log.d(TAG, "@@@@ directShare");
	}
	private static UMImage getUmImage(String url){
		if (TextUtils.isEmpty(url)) {
			return null;
		}
		if(url.startsWith("http")){
			return new UMImage(mActivity, url);
		}else if(url.startsWith("assets")){
			return new UMImage(mActivity, getImageFromAssetsFile(url));
		}else if(url.startsWith("res")){
			Log.e("xxxxxx url="+url.replace("res/", ""));
			int pic = mActivity. getResources().getIdentifier(url.replace("res/", ""), "drawable",mActivity.getPackageName());
			return new UMImage(mActivity, pic);
		}else if(url.startsWith("/sdcard")){
			return new UMImage(mActivity, new File(url));
		}
		return null;

	}

	private static Bitmap getImageFromAssetsFile(String fileName)
	{
		Bitmap image = null;
		AssetManager am = mActivity.getResources().getAssets();
		try
		{
			InputStream is = am.open(fileName.replace("assets/", ""));
			image = BitmapFactory.decodeStream(is);
			is.close();
		}
		catch (IOException e)
		{
			e.printStackTrace();
		}

		return image;

	}
	/**
	 * 判断某个平台是否授权
	 *
	 * @param platform
	 *            平台的字符串表示
	 * @return 返回true则表示该平台已经授权, 否则为未授权.
	 */
	public static boolean isAuthorized(int platform) {
		SHARE_MEDIA target = getPlatform(platform);
		if (target != null && target != SHARE_MEDIA.GENERIC) {
			Log.d(TAG, "xxxxxx isAuthorized="+mShareAPI.isAuthorize(mActivity,getPlatform(platform)));
			return mShareAPI.isAuthorize(mActivity,getPlatform(platform));
		}

		Log.d(TAG, "xxxxxx isAuthorized="+false);
		return false;

	}


	public static void setUmengAppkey(String appkey) {
		Log.d(TAG, "#### 设置umeng appkey :" + appkey);
		if (!TextUtils.isEmpty(appkey)) {
			SocializeConstants.APPKEY = appkey;
		}
	}

	/**
	 * 设置要分享的文字内容
	 *
	 * @param text
	 */
	public static void setShareContent(String text) {
		Log.d(TAG, "#### 设置分享文字内容 :" + text);
		shareAction.withText(text);
		openBoardAction.withText(text);
	}
	/**
	 * 获取用户信息
	 *
	 * @param text
	 */
	public static void getplatformInfo(final int platform) {
		Log.e("xxxx run");
		checkActivity();

		// 在UI线程执行授权操作
		runOnMainThread(new Runnable() {

			@Override
			public void run() {


				mShareAPI.getPlatformInfo(mActivity, getPlatform(platform), mAuthListener);

			}
		});
	}
	/**
	 * 设置要分享的图片路径或者url,或者资源名
	 *
	 * @param imgName
	 *            图片的本地路径或者url,
	 *            如果是url则必须以http://或者https://开头.assets下的图片资源需要传递assets
	 *            /图片名，资源图片则需要传递res/图片名
	 */
	public static void setShareImageName(String imgName) {
		Log.d(TAG, "#### 设置图片路径 :" + imgName);

		UMImage shareImage = null;

		// 网络图片
		if (imgName.startsWith("http://") || imgName.startsWith("https://")) {
			shareImage = new UMImage(mActivity, imgName);
		} else if (imgName.startsWith("assets/")) {
			AssetManager am = mActivity.getResources().getAssets();
			String imageName = getFileName(imgName);
			InputStream is = null;
			if (!TextUtils.isEmpty(imageName)) {
				try {
					is = am.open(imageName);
					shareImage = new UMImage(mActivity,
							BitmapFactory.decodeStream(is));
					is.close();
				} catch (IOException e) {
					e.printStackTrace();
				} finally {
					if (is != null) {
						try {
							is.close();
						} catch (IOException e) {
							e.printStackTrace();
						}
					}
				}
			}

		} else if (imgName.startsWith("res/")) {
			String imgNameWithFormat = getFileName(imgName);
			if (!TextUtils.isEmpty(imgNameWithFormat)) {
				int index = imgNameWithFormat.indexOf(".");
				if (index > 0) {
					String imgNameString = imgNameWithFormat
							.substring(0, index);
					int imgId = ResContainer.getResourceId(mActivity,
							"drawable", imgNameString);
					shareImage = new UMImage(mActivity, imgId);
				} else {
					Log.e(TAG, "### 请检查你传递的图片路径 : " + imgName);
				}
			}

		} else {
			// 本地图片
			File imgFile = new File(imgName);
			if (!imgFile.exists()) {
				Log.e(TAG, "### 要分享的本地图片不存在");
			} else {
				shareImage = new UMImage(mActivity, imgFile);
			}
		}
		shareAction.withMedia(shareImage);
		openBoardAction.withMedia(shareImage);
	}

	/**
	 *
	 * @param fullname
	 * @return
	 */
	private static String getFileName(String fullname) {
		if (fullname.startsWith("assets/") || fullname.startsWith("res/")) {
			return fullname.split("/")[1];
		}
		return "";
	}

	/**
	 * 设置是否开启log
	 *
	 * @param flag
	 */
	protected static void setAndroidLogEnable(boolean flag) {
		Log.LOG = flag;
		Log.e(TAG, "### 是否开启log : " + Log.LOG);
	}

	/**
	 * 初始化Cocos2d-x SDK版本信息
	 */
	protected static void initCocos2dxSDKInfo(String type, String sdkVersion) {
		Log.d(TAG, "### initCocos2dxSDKInfo, type = " + type + ", version = "
				+ sdkVersion);
		// 设置cocos2dx sdk版本号
//		Config.setAdapterSDKInfo(type, sdkVersion);
	}

	/**
	 * 设置用户点击某条分享时跳转到的目标页面
	 *
	 * @param targetUrl
	 */
	public static void setTargetUrl(String targetUrl) {
		if (!TextUtils.isEmpty(targetUrl)
				&& SocializeNetUtils.startWithHttp(targetUrl)) {
			//	shareAction.withTargetUrl(targetUrl);
		}
		Log.d(TAG, "### target url : " + TARGET_URL);
	}
	public static void setShareImagePath(String targetUrl) {
		shareAction.withMedia(new UMImage(mActivity, targetUrl));
	}
	public static void setPlatformShareContent(int platform, String text,
											   String imagePath, String title, String targetUrl) {
		//if (map.containsKey(getPlatform(platform).toString())) {
		platformShareCotent temp = new platformShareCotent();
		temp.text = text;
		temp.imagepath = imagePath;
		temp.title = title;
		temp.targeturl = targetUrl;
		map.put(getPlatform(platform).toString(), temp);
		//}

	}
	public static void setPlatformShareContent(String targetUrl) {
		if (!TextUtils.isEmpty(targetUrl)
				&& SocializeNetUtils.startWithHttp(targetUrl)) {
			//shareAction.withTargetUrl(targetUrl);
		}
		Log.d(TAG, "### target url : " + TARGET_URL);
	}
	public static class platformShareCotent{
		public String text ="";
		public String imagepath = "";
		public String title = "";
		public String targeturl = "";
	}

	public static void supportPlatfrom(int platform) {
		final SHARE_MEDIA target = getPlatform(platform);
		// 判断target
		if (target == null || target == SHARE_MEDIA.GENERIC) {
			return;
		}
		checkActivity();


	}

	/**
	 * 设置平台顺序, 没有的平台则添加, 内置的但是没有给出的则移除.
	 *
	 * @param platforms
	 *            平台的顺序数组
	 */
	public static void setPlatforms(final int[] platforms) {

		// 运行在主线程
		runOnMainThread(new Runnable() {

			@Override
			public void run() {
				if (platforms != null && platforms.length > 0) {
					SHARE_MEDIA[] dis = new SHARE_MEDIA[platforms.length];
					for (int i = 0;i<platforms.length;i++){
						dis[i] = getPlatform(platforms[i]);
					}
					openBoardAction.setDisplayList(dis);
				}
			}
		});

	}





	private static void runOnOpenGLThread(Runnable runnable) {
		if (mActivity != null) {
			// Cocos2dxGLSurfaceView.getInstance().queueEvent(runnable);
			mActivity.runOnGLThread(runnable);
		}
	}

	/**
	 * 将操作封装在Runnable中, 使之运行在Android主线程
	 *
	 * @param runnable
	 */
	private static void runOnMainThread(Runnable runnable) {
		mSDKHandler.postDelayed(runnable, DELAY_MS);
	}
	public static void runNativeCallback(Runnable runnable)
	{
		Cocos2dxGLSurfaceView.getInstance().queueEvent(runnable);
	}
	/**
	 *
	 * @param platform
	 *            要检测的平台
	 * @return
	 */
	private static boolean isPlatformValid(int platform) {
		final SHARE_MEDIA target = getPlatform(platform);
		if (target == null || target == SHARE_MEDIA.GENERIC) {
			Log.e(TAG, "### 设置的目标平台无效.   platform = " + target);
			return false;
		}
		return true;
	}




	/**
	 * 检查mActivity的合法性
	 */
	private static void checkActivity() {
		assert mActivity != null : "在CCUMSocialController类中, mActivity为null.";
	}

	/**
	 * 清空SDK
	 */
	public static void cleanup() {
		mShareAPI = null;
		mSDKHandler = null;
		mActivity = null;
		Log.d(TAG, "@@@@ cleanup");
	}

	/*******************************************************************************
	 * 授权回调接口, 会调用native层对应的回调方法, 开发者可以在Java或者native层进行相应的处理
	 ******************************************************************************/
	private static UMAuthListener mAuthListener = new UMAuthListener() {



		@Override
		public void onComplete(final SHARE_MEDIA share_media, int i, final Map<String, String> map) {
			// 运行在gl线程

			runOnOpenGLThread(new Runnable() {

				@Override
				public void run() {
					Log.e("xxxxxxauthcallback ff");
					OnAuthorizeComplete(getPlatformInt(share_media),
							StatusCode.ST_CODE_SUCCESSED, getAuthMap(map),getAuthKey(map));
				}
			});
		}

		@Override
		public void onError(final SHARE_MEDIA share_media, int i, final Throwable throwable) {

			runOnOpenGLThread(new Runnable() {

				@Override
				public void run() {
					OnAuthorizeComplete(getPlatformInt(share_media), 0,
							new String[] { throwable.getMessage() },new String[] { "error" });
				}
			});
		}

		@Override
		public void onCancel(final SHARE_MEDIA share_media, int i) {

			runOnOpenGLThread(new Runnable() {

				@Override
				public void run() {
					OnAuthorizeComplete(getPlatformInt(share_media), -1,
							new String[] { "cancel" },new String[] { "cancel" });
				}
			});
		}

		/**
		 *
		 * @param data
		 *            授权的数据
		 * @return 如果含有access_token则获取access_token和过期时间, 传递到native层
		 */
		private String[] getAuthData(Bundle data) {
			if (data != null
					&& (data.containsKey("access_token") || data
					.containsKey("access_secret"))) {
				String[] authData = new String[3];
				// 有的字段为secret
				if (data.containsKey("access_secret")) {
					authData[0] = data.getString("access_secret");
				} else {
					authData[0] = data.getString("access_token");
				}
				if (data.containsKey("uid")) {
					authData[1] = data.getString("uid");
				} else {
					authData[1] = "";
				}

				return authData;
			} else {
				return new String[] {};
			}
		}
		private String[] getAuthMap(Map<String, String> data) {

			String[] authData = new String[data.size()];
			int i = 0;
			for (String key : data.keySet()) {
				Log.e("xxxxxx stringvalue="+ data.get(key));
				authData[i] = data.get(key);
				i++;
			}
			return authData;

		}
		private String[] getAuthKey(Map<String, String> data) {
//			if (data != null
//					&& (data.containsKey("access_token") || data
//					.containsKey("access_secret"))) {
//				String[] authData = new String[3];
//				// 有的字段为secret
//				if (data.containsKey("access_secret")) {
//					authData[0] = data.get("access_secret");
//				} else {
//					authData[0] = data.get("access_token");
//				}
//				if (data.containsKey("uid")) {
//					authData[1] = data.get("uid");
//				} else {
//					authData[1] = "";
//				}
//
//				return authData;
//			} else {
			String[] authData = new String[data.size()];
			int i = 0;
			for (String key : data.keySet()) {
				Log.e("xxxxxx stringkey="+key);
				authData[i] = key;
				i++;
			}
			return authData;
//			}
		}

		@Override
		public void onStart(SHARE_MEDIA arg0) {
			// TODO Auto-generated method stub

		}
	};

	/**
	 * 回调授权的OnStart方法到native层
	 */
	private native static void OnAuthorizeStart(int platform);

	/**
	 * 回调授权的onComplete方法到native层
	 *
	 * @param value
	 *            授权信息, 包含token等, 包含access_token, 过期时间expires_in
	 * @param platform
	 *            平台
	 */
	private native static void OnAuthorizeComplete(int platform, int stCode,
												   String[] value,String[] key);

	/******************************************************************************
	 * 分享回调接口,会调用native层对应的回调方法, 开发者可以在Java或者native层进行相应的处理
	 *****************************************************************************/
	private static UMShareListener umShareListener = new UMShareListener() {

		@Override
		public void onResult(final SHARE_MEDIA share_media) {
			runNativeCallback(new Runnable() {

				@Override
				public void run() {
					OnShareComplete(getPlatformInt(share_media), StatusCode.ST_CODE_SUCCESSED,
							share_media.toString()+"share success");
				}
			});
		}

		@Override
		public void onError(final SHARE_MEDIA share_media, final Throwable throwable) {
			runNativeCallback(new Runnable() {

				@Override
				public void run() {
					OnShareComplete(getPlatformInt(share_media), 0,
							share_media.toString()+throwable.getMessage());
				}
			});
		}

		@Override
		public void onCancel(final SHARE_MEDIA share_media) {
			runNativeCallback(new Runnable() {

				@Override
				public void run() {
//					if (share_media == SHARE_MEDIA.QZONE) {
//						OnShareComplete(getPlatformInt(share_media), StatusCode.ST_CODE_SUCCESSED,
//								share_media.toString()+"share cancle");
//
//					}
//					else {

					OnShareComplete(getPlatformInt(share_media), -1,
							share_media.toString()+"share cancle");
//					}
				}
			});
		}

		@Override
		public void onStart(SHARE_MEDIA arg0) {
			// TODO Auto-generated method stub

		}
	};
//	private static SnsPostListener mSocialShareListener = new SnsPostListener() {
//
//		/*
//		 * 分享开始 (non-Javadoc)
//		 *
//		 * @see com.umeng.socialize.controller.listener.SocializeListeners.
//		 * SnsPostListener#onStart()
//		 */
//		@Override
//		public void onStart() {
//			runOnOpenGLThread(new Runnable() {
//
//				@Override
//				public void run() {
//					OnShareStart();
//				}
//			});
//
//		}
//
//		/*
//		 * 分享完成 (non-Javadoc)
//		 *
//		 * @see com.umeng.socialize.controller.listener.SocializeListeners.
//		 * SnsPostListener#onComplete(com.umeng.socialize.bean.SHARE_MEDIA, int,
//		 * com.umeng.socialize.bean.SocializeEntity)
//		 */
//		@Override
//		public void onComplete(final SHARE_MEDIA platform, final int eCode,
//				final SocializeEntity entity) {
//			runOnOpenGLThread(new Runnable() {
//
//				@Override
//				public void run() {
//					OnShareComplete(getPlatformInt(platform), eCode,
//							entity.mDescriptor);
//				}
//			});
//
//		}
//	};

	/**
	 * 回调分享的OnStart方法到native层
	 */
	private native static void OnShareStart();

	/**
	 * 回调分享的onComplete方法到native层
	 *
	 * @param platform
	 *            平台
	 * @param eCode
	 *            错误码, 200为授权成功
	 * @param entity
	 *            UMSocialService的属性容器
	 */
	private native static void OnShareComplete(int platform, int eCode,
											   String descriptor);
	/**
	 * 回调分享的board方法到native层
	 *
	 * @param platform
	 *            平台
	 */
	private native static void OnBoard(int platform);
	private native static void OnBoardDismiss();

	/**
	 * 通过整型获取对应的平台, C++中使用enum常量来代表平台
	 *
	 * @param location
	 * @return
	 */
	private static SHARE_MEDIA getPlatform(int location) {
		int length = mPlatformsList.size();
		if (location < 0 || location >= length) {
			return null;
		}
		return mPlatformsList.get(location);
	}

	/**
	 * 获取平台对应的整型号码
	 *
	 * @param platform
	 *            对应的平台
	 * @return the index of the first occurrence of the object or -1 if the
	 *         object was not found.
	 */
	private static int getPlatformInt(SHARE_MEDIA platform) {
		Log.e("xxxxxx platform="+platform);
		return mPlatformsList.indexOf(platform);
	}

	/*
	 * 
	 */
	private static List<SHARE_MEDIA> mPlatformsList = new ArrayList<SHARE_MEDIA>();
	/*
	 * 
	 */
	static {
		mPlatformsList.add(0, SHARE_MEDIA.QQ);
		mPlatformsList.add(1, SHARE_MEDIA.SINA);
		mPlatformsList.add(2, SHARE_MEDIA.WEIXIN);
		mPlatformsList.add(3, SHARE_MEDIA.WEIXIN_CIRCLE);
		mPlatformsList.add(4, SHARE_MEDIA.QZONE);
		mPlatformsList.add(5, SHARE_MEDIA.EMAIL);
		mPlatformsList.add(6, SHARE_MEDIA.SMS);
		mPlatformsList.add(7, SHARE_MEDIA.FACEBOOK);
		mPlatformsList.add(8, SHARE_MEDIA.TWITTER);
		mPlatformsList.add(9, SHARE_MEDIA.WEIXIN_FAVORITE);
		mPlatformsList.add(10, SHARE_MEDIA.GOOGLEPLUS);
		mPlatformsList.add(11, SHARE_MEDIA.RENREN);
		mPlatformsList.add(12, SHARE_MEDIA.TENCENT);
		mPlatformsList.add(13, SHARE_MEDIA.DOUBAN);
		mPlatformsList.add(14, SHARE_MEDIA.FACEBOOK_MESSAGER);
		mPlatformsList.add(15, SHARE_MEDIA.YIXIN);
		mPlatformsList.add(16, SHARE_MEDIA.YIXIN_CIRCLE);
		mPlatformsList.add(17, SHARE_MEDIA.INSTAGRAM);
		mPlatformsList.add(18, SHARE_MEDIA.PINTEREST);
		mPlatformsList.add(19, SHARE_MEDIA.EVERNOTE);
		mPlatformsList.add(20, SHARE_MEDIA.POCKET);
		mPlatformsList.add(21, SHARE_MEDIA.LINKEDIN);
		mPlatformsList.add(22, SHARE_MEDIA.FOURSQUARE);
		mPlatformsList.add(23, SHARE_MEDIA.YNOTE);
		mPlatformsList.add(24, SHARE_MEDIA.WHATSAPP);
		mPlatformsList.add(25, SHARE_MEDIA.LINE);
		mPlatformsList.add(26, SHARE_MEDIA.FLICKR);
		mPlatformsList.add(27, SHARE_MEDIA.TUMBLR);
		mPlatformsList.add(28, SHARE_MEDIA.ALIPAY);
		mPlatformsList.add(29, SHARE_MEDIA.KAKAO);
		mPlatformsList.add(30, SHARE_MEDIA.DROPBOX);
		mPlatformsList.add(31, SHARE_MEDIA.VKONTAKTE);
		mPlatformsList.add(32, SHARE_MEDIA.DINGTALK);
		mPlatformsList.add(33, SHARE_MEDIA.MORE);
	}

}
