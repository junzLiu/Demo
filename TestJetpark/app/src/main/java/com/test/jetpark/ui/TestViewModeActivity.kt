package com.test.jetpark.ui

import android.support.v7.app.AppCompatActivity
import android.os.Bundle
import com.test.jetpark.R
import com.test.jetpark.ui.ui.testviewmode.TestViewModeFragment

class TestViewModeActivity : AppCompatActivity() {

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.test_view_mode_activity)
        if (savedInstanceState == null) {
            supportFragmentManager.beginTransaction()
                .replace(R.id.container, TestViewModeFragment.newInstance())
                .commitNow()
        }
    }

}
