package com.mark.location.locationapp;

import android.os.Bundle;
import android.support.v7.app.AppCompatActivity;
import android.util.Log;
import android.widget.TextView;

import com.baidu.location.BDAbstractLocationListener;
import com.baidu.location.BDLocation;
import com.google.gson.Gson;
import com.mark.location.locationapp.entity.LocationInfo;
import com.mark.location.locationapp.utils.LocationHelper;
import com.tencent.bugly.crashreport.CrashReport;

public class MainActivity extends AppCompatActivity {
  TextView tv;

  @Override protected void onCreate(Bundle savedInstanceState) {
    super.onCreate(savedInstanceState);
    setContentView(R.layout.activity_main);
    tv = findViewById(R.id.tv);
    LocationHelper.getInstance().setLocationListener(new BDAbstractLocationListener() {
      @Override public void onReceiveLocation(BDLocation bdLocation) {
        LocationInfo info = new LocationInfo(bdLocation.getLongitude(), bdLocation.getLatitude(),bdLocation.getRadius(),
            bdLocation.getAddress(), bdLocation.getTime());
        final String locationStr = new Gson().toJson(info);
        Log.d("tag", locationStr);
        runOnUiThread(new Runnable() {
          @Override
          public void run() {
            CrashReport.postCatchedException(new RuntimeException(locationStr));
            tv.setText(tv.getText() + ".");
          }
        });


      }
    });

    LocationHelper.getInstance().genLocationOption(600, true);
    LocationHelper.getInstance().start();
  }


  @Override protected void onDestroy() {
    super.onDestroy();
    LocationHelper.getInstance().removeLocationListener();
    LocationHelper.getInstance().stop();
  }

  @Override
  public void onBackPressed() {

  }

  @Override
  public void finish() {
  }
}
