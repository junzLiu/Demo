package com.mark.location.locationapp;

import android.app.Application;

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
  }
}
