package jetpark.test.com.mvvmdemo.model

import androidx.lifecycle.MutableLiveData

/**
 * @author:markLiu
 * @create:2019/2/15
 * @title:
 * @description:
 **/

data class People internal constructor(var nameStr: String, var heightI: Int) {
    var name: MutableLiveData<String> = MutableLiveData()
    var height: MutableLiveData<Int> = MutableLiveData()

    init {
        name.postValue(nameStr)
        height.postValue(heightI)
    }
}
