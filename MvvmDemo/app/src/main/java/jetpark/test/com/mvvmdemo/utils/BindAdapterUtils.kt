package jetpark.test.com.mvvmdemo.utils

import android.text.Editable
import android.text.TextWatcher
import android.view.View
import android.widget.EditText
import androidx.databinding.BindingAdapter
import androidx.databinding.InverseBindingAdapter
import androidx.databinding.InverseBindingListener

/**
 * @author:markLiu
 * @create:2019/2/18
 * @title:
 * @description:
 **/

object BindAdapterUtils {
    @JvmStatic
    @BindingAdapter("android:textInt")
    fun setText(view: EditText, text: Int) {
        view.setText("$text")
    }

    @JvmStatic
    @InverseBindingAdapter(attribute = "android:textInt", event = "textIntAttrChange")
    fun getText(view: EditText): Int {
        val text: String = view.text.toString()
        return try {
            Integer.parseInt(text)
        } catch (ex: NumberFormatException) {
            ex.printStackTrace()
            0
        }

    }

    @JvmStatic
    @BindingAdapter("textIntAttrChange")
    fun textIntAttrChange(view: EditText, listener: InverseBindingListener) {
        view.addTextChangedListener(object : TextWatcher {
            override fun beforeTextChanged(s: CharSequence, start: Int, count: Int, after: Int) {

            }

            override fun onTextChanged(s: CharSequence, start: Int, before: Int, count: Int) {
                listener.onChange()
            }

            override fun afterTextChanged(s: Editable) {

            }
        })
    }

    @BindingAdapter("android:killAble")
    @JvmStatic
    fun View.setKillAble(killAble: Boolean) {
        this.isEnabled = killAble
    }
}

