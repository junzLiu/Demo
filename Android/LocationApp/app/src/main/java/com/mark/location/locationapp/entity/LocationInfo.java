package com.mark.location.locationapp.entity;

import com.baidu.location.Address;
import java.io.Serializable;

/**
 * @author:markLiu
 * @create:2019/1/22
 * @title:
 * @description:
 **/
public class LocationInfo implements Serializable {
  public double longitude;
  public double latitude;
  public float radius;
  public Address address;
  public String time;

  public LocationInfo(double longitude, double latitude, float radius, Address address, String time) {
    this.longitude = longitude;
    this.latitude = latitude;
    this.radius = radius;
    this.address = address;
    this.time = time;
  }

  public LocationInfo() {
  }
}
