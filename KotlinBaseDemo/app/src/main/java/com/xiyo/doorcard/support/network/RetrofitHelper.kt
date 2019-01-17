package com.xiyo.doorcard.support.network

import retrofit2.Retrofit
import retrofit2.adapter.rxjava2.RxJava2CallAdapterFactory
import retrofit2.converter.gson.GsonConverterFactory


class RetrofitHelper private constructor() {
    private var retrofit: Retrofit? = null

    companion object {
        private var instance: RetrofitHelper? = null
            get() {
                field = field ?: RetrofitHelper()
                return field
            }

        fun get() = instance!!
    }

    fun getRetrofit(): Retrofit {
        retrofit = retrofit ?: Retrofit.Builder()
            .client(OkHttpHelper.get().getOkHttpClient())
            .addConverterFactory(GsonConverterFactory.create())
            .addCallAdapterFactory(RxJava2CallAdapterFactory.create())
            .baseUrl("http://gc.ditu.aliyun.com")
            .build()
        return retrofit!!
    }

}
