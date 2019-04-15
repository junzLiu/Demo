package com.xiyo.doorcard.ui

import android.os.Bundle
import com.xiyo.doorcard.R
import com.xiyo.doorcard.ui.base.BaseActivity
import com.xiyo.doorcard.ui.base.needPermissWithPermissionCheck
import kotlinx.android.synthetic.main.activity_main.*

class MainActivity : BaseActivity() {

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_main)
       needPermissWithPermissionCheck()
    // Example of a call to a native method
    sample_text.text = stringFromJNI()
    }

    /**
     * A native method that is implemented by the 'native-lib' native library,
     * which is packaged with this application.
     */
    external fun stringFromJNI(): String

    companion object {

        // Used to load the 'native-lib' library on application startup.
        init {
            System.loadLibrary("native-lib")
        }
    }
}
