package com.xiyo.doorcard

import com.xiyo.doorcard.config.api.TestApi
import com.xiyo.doorcard.entity.TestEntity
import com.xiyo.doorcard.support.network.RetrofitHelper
import io.reactivex.Observer
import io.reactivex.disposables.Disposable
import org.junit.Assert.assertEquals
import org.junit.Test

/**
 * Example local unit test, which will execute on the development machine (host).
 *
 * See [testing documentation](http://d.android.com/tools/testing).
 */
class ExampleUnitTest {
    @Test
    fun addition_isCorrect() {
        assertEquals(4, 2 + 2)
    }

    @Test
    fun testNet() {
        RetrofitHelper.get().getRetrofit().create(TestApi::class.java).getTestData("杭州市")
            .subscribe(object : Observer<TestEntity> {
                override fun onComplete() {
//                TODO("not implemented") //To change body of created functions use File | Settings | File Templates.
                    print("com")
                }

                override fun onSubscribe(d: Disposable) {
//                TODO("not implemented") //To change body of created functions use File | Settings | File Templates.
                    print("sub")
                }

                override fun onNext(t: TestEntity) {
                    print(t)
                    print("next")
//                TODO("not implemented") //To change body of created functions use File | Settings | File Templates.
                }

                override fun onError(e: Throwable) {
                    print("err")
//                TODO("not implemented") //To change body of created functions use File | Settings | File Templates.
                }
            })
    }
}
