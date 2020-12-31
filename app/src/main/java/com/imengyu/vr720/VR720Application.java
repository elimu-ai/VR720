package com.imengyu.vr720;

import android.app.Application;
import android.util.Log;

import com.imengyu.vr720.core.NativeVR720;
import com.hjq.toast.ToastUtils;
import com.imengyu.vr720.service.CacheServices;
import com.imengyu.vr720.service.ListDataService;
import com.imengyu.vr720.service.ListImageCacheService;

/**
 * 应用全局初始化操作
 */
public class VR720Application extends Application {

    public static final String TAG = VR720Application.class.getSimpleName();

    private ListDataService listDataService = null;
    private ListImageCacheService listImageCacheService = null;
    private CacheServices cacheServices = null;

    public ListDataService getListDataService() {
        return listDataService;
    }
    public ListImageCacheService getListImageCacheService() {
        return listImageCacheService;
    }
    public CacheServices getCacheServices() {
        return cacheServices;
    }

    private boolean nativeDestroyed = true;

    public void checkAndInit() {
        if(nativeDestroyed) {
            NativeVR720.initNative(getAssets(), getApplicationContext());
            nativeDestroyed = false;
        }
    }

    @Override
    public void onCreate() {
        super.onCreate();
        Log.i(TAG, "onCreate");

        //设置错误回调


        //初始化数据服务
        listDataService = new ListDataService(getApplicationContext());
        listImageCacheService = new ListImageCacheService(getApplicationContext());
        cacheServices = new CacheServices(getApplicationContext());

        //ToastUtils
        ToastUtils.init(this);
        //初始化内核
        checkAndInit();


    }

    @Override
    public void onTerminate() {
        Log.i(TAG, "onTerminate");
        if(listImageCacheService != null) {
            listImageCacheService.releaseImageCache();
            listImageCacheService = null;
        }
        if(!nativeDestroyed) {
            NativeVR720.releaseNative();
            nativeDestroyed = true;
        }
        super.onTerminate();
    }

    public void onQuit() {
        Log.i(TAG, "onQuit");
        if(!nativeDestroyed) {
            NativeVR720.releaseNative();
            nativeDestroyed = true;
        }
    }

    @Override
    public void onLowMemory() {
        Log.i(TAG, "onLowMemory");
        if(listImageCacheService != null)
            listImageCacheService.releaseAllMemoryCache();
        if(!nativeDestroyed)
            NativeVR720.lowMemory();
        super.onLowMemory();
    }
}
