package com.xiyo.doorcard.ui.base

import android.Manifest
import android.os.Bundle
import androidx.appcompat.app.AppCompatActivity
import com.xiyo.doorcard.support.network.NetCallBack
import com.xiyo.doorcard.support.network.NetWorkHelper
import io.reactivex.Observable
import io.reactivex.Observer
import io.reactivex.disposables.Disposable
import permissions.dispatcher.*

@RuntimePermissions
open class BaseActivity : AppCompatActivity() {
    private var mDisposeables: ArrayList<Disposable> = ArrayList()

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
    }

    override fun onDestroy() {
        super.onDestroy()
        for (d in mDisposeables)
            if (!d.isDisposed)
                d.dispose()
    }

     fun <T : Any> rxRequest(observable: Observable<T>, netCallBack: NetCallBack<T>) {
        NetWorkHelper.rxRequest(observable, object : Observer<T> {
            override fun onComplete() {

            }

            override fun onSubscribe(d: Disposable) {
                mDisposeables.add(d)
            }

            override fun onNext(t: T) {
                netCallBack.onNext(t)
            }

            override fun onError(e: Throwable) {
                netCallBack.onError("", e)
            }
        })
    }

    @NeedsPermission(
        Manifest.permission.CAMERA,
        Manifest.permission.BLUETOOTH,
        Manifest.permission.BLUETOOTH_ADMIN,
        Manifest.permission.READ_EXTERNAL_STORAGE,
        Manifest.permission.WRITE_EXTERNAL_STORAGE
    )
    fun needPermiss() {

    }

    override fun onRequestPermissionsResult(requestCode: Int, permissions: Array<out String>, grantResults: IntArray) {
        super.onRequestPermissionsResult(requestCode, permissions, grantResults)
        onRequestPermissionsResult(requestCode,permissions, grantResults)
    }

    @OnShowRationale(
        Manifest.permission.CAMERA,
        Manifest.permission.BLUETOOTH,
        Manifest.permission.BLUETOOTH_ADMIN,
        Manifest.permission.READ_EXTERNAL_STORAGE,
        Manifest.permission.WRITE_EXTERNAL_STORAGE
    )
    fun showPermiss(request: PermissionRequest) {
        request.proceed()
    }

    @OnPermissionDenied(
        Manifest.permission.CAMERA,
        Manifest.permission.READ_EXTERNAL_STORAGE,
        Manifest.permission.WRITE_EXTERNAL_STORAGE
    )
    fun deniedpermiss() {
    }

    @OnNeverAskAgain(
        Manifest.permission.CAMERA,
        Manifest.permission.READ_EXTERNAL_STORAGE,
        Manifest.permission.WRITE_EXTERNAL_STORAGE
    )
    fun NeverAskAgain() {
    }
}