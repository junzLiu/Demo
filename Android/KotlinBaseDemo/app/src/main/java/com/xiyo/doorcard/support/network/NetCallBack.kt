package com.xiyo.doorcard.support.network

interface NetCallBack<T> {
     fun onNext(t: T)

     fun onError(message:String,e: Throwable){

     }

}