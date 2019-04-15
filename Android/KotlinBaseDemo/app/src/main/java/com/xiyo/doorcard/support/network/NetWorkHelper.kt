package com.xiyo.doorcard.support.network

import io.reactivex.Observable
import io.reactivex.Observer
import io.reactivex.android.schedulers.AndroidSchedulers
import io.reactivex.schedulers.Schedulers

object NetWorkHelper {

    /**
     * 处理请求线程转换
     *  <h5>observable<h5> from RetrofitHelper.get().getRetrofit().create(Api.class).fun
     *  observer
     */
    fun <T : Any> rxRequest(observable: Observable<T>, observer: Observer<T>) {
        observable
            .subscribeOn(Schedulers.io())
            .observeOn(AndroidSchedulers.mainThread())
            .subscribe(observer)
    }


}