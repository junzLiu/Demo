package com.xiyo.doorcard

import android.app.Application
import com.xiyo.doorcard.support.log.LoggerHelper


class App : Application() {

    companion object {
        val TAG = "DoorCard"
        private var instance: App? = null
            get() {
                return instance
            }
    }

    override fun onCreate() {
        super.onCreate()
        instance = this
        LoggerHelper.initLog()
    }
}
