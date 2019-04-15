package com.mark.location.locationapp;

import android.app.Application;

import com.tencent.bugly.crashreport.CrashReport;

/**
 * @author:markLiu
 * @create:2019/1/22
 * @title:
 * @description:
 **/
public class App extends Application {

  private static App instance;

  public static App getInstance() {
    return instance;
  }

  @Override public void onCreate() {
    super.onCreate();
    instance = this;
    CrashReport.initCrashReport(this,"f08596c384",false);
  }
}
