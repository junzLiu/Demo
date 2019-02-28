package jetpark.test.com.mvvmdemo.utils

import android.text.Editable
import android.text.TextWatcher
import android.widget.EditText

/**
 * @author:markLiu
 * @create:2019/2/27
 * @title:
 * @description:
 */
class TestUtils {
    internal fun testText(editText: EditText) {
        editText.addTextChangedListener(object : TextWatcher {
            override fun beforeTextChanged(s: CharSequence, start: Int, count: Int, after: Int) {

            }

            override fun onTextChanged(s: CharSequence, start: Int, before: Int, count: Int) {

            }

            override fun afterTextChanged(s: Editable) {

            }
        })
    }
}
