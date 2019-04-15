package com.xiyo.doorcard.config.api

import com.xiyo.doorcard.entity.TestEntity
import io.reactivex.Observable
import retrofit2.http.GET
import retrofit2.http.Query

 interface TestApi {
    @GET("/geocoding")
    fun getTestData(@Query("a") cityName: String): Observable<TestEntity>
}