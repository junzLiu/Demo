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

public class MainActivity extends AppCompatActivity {
  TextView tv;

  @Override protected void onCreate(Bundle savedInstanceState) {
    super.onCreate(savedInstanceState);
    setContentView(R.layout.activity_main);
    tv = findViewById(R.id.tv);
    LocationHelper.getInstance().setLocationListener(new BDAbstractLocationListener() {
      @Override public void onReceiveLocation(BDLocation bdLocation) {
        LocationInfo info = new LocationInfo(bdLocation.getLongitude(), bdLocation.getLatitude(),
            bdLocation.getAddress(), bdLocation.getTime());
        Log.d("tag", new Gson().toJson(info));
        tv.setText(tv.getText() + "\n" + new Gson().toJson(info));
      }
    });
    LocationHelper.getInstance().genLocationOption(1, true);
    LocationHelper.getInstance().start();
  }

  @Override protected void onDestroy() {
    super.onDestroy();
    LocationHelper.getInstance().removeLocationListener();
    LocationHelper.getInstance().stop();
  }
}
