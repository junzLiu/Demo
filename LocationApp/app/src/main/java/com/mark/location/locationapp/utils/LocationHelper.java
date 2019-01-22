package com.mark.location.locationapp.utils;

import android.app.Notification;
import com.baidu.location.BDAbstractLocationListener;
import com.baidu.location.LocationClient;
import com.baidu.location.LocationClientOption;
import com.mark.location.locationapp.App;
import com.mark.location.locationapp.R;

/**
 * @author:markLiu
 * @create:2019/1/22
 * @title:
 * @description:
 **/
public class LocationHelper {
  public static int DEF_TIME_INTERVAL = 10;
  private static LocationHelper instance;
  LocationClient client;
  LocationClientOption clientOption;
  BDAbstractLocationListener locationListener;

  public LocationHelper() {
    client = new LocationClient(App.getInstance());
  }

  public static LocationHelper getInstance() {
    if (instance == null) instance = new LocationHelper();
    return instance;
  }

  public void start() {
    if (clientOption == null) genLocationOption(DEF_TIME_INTERVAL, true);
    client.setLocOption(clientOption);
    if (locationListener != null) client.registerLocationListener(locationListener);
    client.start();
  }

  public void setLocationListener(BDAbstractLocationListener locationListener) {
    this.locationListener = locationListener;
  }

  public void genLocationOption(int timeInterval, boolean isNeedNotification) {
    clientOption = new LocationClientOption();
    clientOption.setIgnoreKillProcess(true);
    clientOption.setIsNeedAddress(true);
    clientOption.setOpenGps(true);
    clientOption.setCoorType("gcj02");
    clientOption.setScanSpan(timeInterval * 1000);
    clientOption.setIsNeedLocationDescribe(true);
    clientOption.setLocationMode(LocationClientOption.LocationMode.Device_Sensors);
    if (isNeedNotification) {
      Notification notification = genNotification();
      client.enableLocInForeground(1001, notification);
    }
  }

  private Notification genNotification() {
    //开启前台定位服务：
    Notification.Builder builder = new Notification.Builder(App.getInstance());
    //获取一个Notification构造器

    //Intent nfIntent = new Intent(App.getInstance(), MainActivity.class);
    //    setContentIntent(PendingIntent.getActivity(, 0, nfIntent, 0))
    builder// 设置PendingIntent
        .setContentTitle("loc") // 设置下拉列表里的标题
        .setSmallIcon(R.mipmap.ic_launcher) // 设置状态栏内的小图标
        .setContentText("loc ing...") // 设置上下文内容
        .setAutoCancel(false).setWhen(System.currentTimeMillis()); // 设置该通知发生的时间
    return builder.build();
  }

  public void removeLocationListener() {
    if (locationListener != null) client.unRegisterLocationListener(locationListener);
  }

  public void stop() {
    client.stop();
  }
}
