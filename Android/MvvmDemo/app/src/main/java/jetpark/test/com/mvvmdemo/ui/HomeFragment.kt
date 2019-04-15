package jetpark.test.com.mvvmdemo.ui

import android.os.Bundle
import android.view.LayoutInflater
import android.view.View
import android.view.ViewGroup
import androidx.databinding.DataBindingUtil
import androidx.fragment.app.Fragment
import androidx.lifecycle.ViewModelProviders
import jetpark.test.com.mvvmdemo.R
import jetpark.test.com.mvvmdemo.databinding.FragmentHomeBinding
import jetpark.test.com.mvvmdemo.viewMode.HomeViewModel

/**
 * @author:markLiu
 * @create:2019/2/14
 * @title:
 * @description:
 **/
class HomeFragment : Fragment() {

    override fun onCreateView(inflater: LayoutInflater, container: ViewGroup?, savedInstanceState: Bundle?): View? {

        val binding: FragmentHomeBinding = DataBindingUtil.inflate(inflater, R.layout.fragment_home, container, false)
        val rootView = binding.root
        val viewmodel = ViewModelProviders.of(this).get(HomeViewModel::class.java)
        binding.lifecycleOwner = this
        binding.viewModel = viewmodel
        return rootView
    }
}