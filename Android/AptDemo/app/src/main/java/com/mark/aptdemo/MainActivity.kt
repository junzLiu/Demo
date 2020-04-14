package com.mark.aptdemo

import androidx.appcompat.app.AppCompatActivity
import android.os.Bundle

class MainActivity : AppCompatActivity() {

//    @MarkPrint("MainActivity.ts")
    val ts = "Test Ann"

//    @MarkPrint("iMain")
    val index = 0

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_main)
    }
}
