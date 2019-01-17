package com.test.jetpark.ui.ui.testviewmode

import android.arch.lifecycle.ViewModelProviders
import android.os.Bundle
import android.support.v4.app.Fragment
import android.view.LayoutInflater
import android.view.View
import android.view.ViewGroup
import com.test.jetpark.R

class TestViewModeFragment : Fragment() {

    companion object {
        fun newInstance() = TestViewModeFragment()
    }

    private lateinit var viewModel: TestViewModeViewModel

    override fun onCreateView(
        inflater: LayoutInflater, container: ViewGroup?,
        savedInstanceState: Bundle?
    ): View {
        return inflater.inflate(R.layout.test_view_mode_fragment, container, false)
    }

    override fun onActivityCreated(savedInstanceState: Bundle?) {
        super.onActivityCreated(savedInstanceState)
        viewModel = ViewModelProviders.of(this).get(TestViewModeViewModel::class.java)
        // TODO: Use the ViewModel
    }

}
