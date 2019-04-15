package jetpark.test.com.mvvmdemo.viewMode

import android.util.Log
import androidx.lifecycle.MutableLiveData
import androidx.lifecycle.ViewModel
import jetpark.test.com.mvvmdemo.model.People

/**
 * @author:markLiu
 * @create:2019/2/14
 * @title:
 * @description:
 **/

open class HomeViewModel : ViewModel() {
    val TAG = HomeViewModel::class.java.simpleName
    val numPre: MutableLiveData<Int> by lazy {
        MutableLiveData<Int>()
    }
    val peopleData: MutableLiveData<People> by lazy {
        MutableLiveData<People>()
    }
    val summaryData = MutableLiveData<String>()
    val ckAble = true

    init {
        numPre.postValue(0)
        peopleData.postValue(People("Mark", 170))
    }

    fun getPeople(): People? {
        return peopleData.value
    }

    fun clickNum() {
        numPre.value = numPre.value?.plus(1)
        peopleData.value?.height?.postValue(peopleData.value?.height?.value?.plus(1))
        summaryData.postValue("name:${getPeople()?.name?.value}\nheight:${getPeople()?.height?.value}\nClickTimes:${numPre.value}")
        Log.d(TAG, "Action:clickNum,num is ${numPre.value}")
    }


}