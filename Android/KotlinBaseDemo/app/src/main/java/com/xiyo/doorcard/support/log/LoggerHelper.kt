package com.xiyo.doorcard.support.log

import com.orhanobut.logger.AndroidLogAdapter
import com.orhanobut.logger.FormatStrategy
import com.orhanobut.logger.Logger
import com.orhanobut.logger.PrettyFormatStrategy
import com.xiyo.doorcard.App
import com.xiyo.doorcard.BuildConfig

/**
 * @author:markLiu
 * @create:2018/11/27
 * @title:
 * @description:
 **/
class LoggerHelper {

    companion object {
        fun initLog() {
            val formatStrategy = PrettyFormatStrategy.newBuilder()
                .showThreadInfo(false)
                .methodCount(2)
                .methodOffset(6)
                .tag(App.TAG)
                .build()
            Logger.addLogAdapter(MyAndroidLogAdapter(formatStrategy))
        }
    }

    internal class MyAndroidLogAdapter : AndroidLogAdapter {

        constructor(formatStrategy: FormatStrategy) : super(formatStrategy)
        constructor() : super()


        override fun isLoggable(priority: Int, tag: String?): Boolean {
            return BuildConfig.DEBUG
        }
    }
}