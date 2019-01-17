package com.xiyo.doorcard.support.network

import okhttp3.OkHttpClient
import java.util.concurrent.TimeUnit
import android.text.TextUtils
import com.orhanobut.logger.Logger
import com.xiyo.doorcard.BuildConfig


class OkHttpHelper private constructor() {

    companion object {
        private var instance: OkHttpHelper? = null
            get() {
                field = field ?: OkHttpHelper()
                return field
            }

        fun get() = instance!!
    }

    fun getOkHttpClient(): OkHttpClient {

        val builder = OkHttpClient.Builder()
        builder.addInterceptor(
            LoggingInterceptor(MyLogger())
                .setLevel(if (BuildConfig.DEBUG) LoggingInterceptor.Level.BODY else LoggingInterceptor.Level.NONE)
        )
            .connectTimeout(30, TimeUnit.SECONDS)
            .writeTimeout(10, TimeUnit.SECONDS)
            .readTimeout(10, TimeUnit.SECONDS)
            .followRedirects(true)
        return builder.build()
    }

    internal inner class MyLogger : LoggingInterceptor.Logger {

        override fun log(message: String) {
            if (!TextUtils.isEmpty(message)) {
                Logger.e("netdata $message")
            }
        }

    }
}