### MvvmDemo

#### 自定义属性双向绑定

##### 数据模型
```
val num: MutableLiveData<Int> by lazy {
        MutableLiveData<Int>()
    }
```

- UI绑定数据
```
//添加自定义属性
 @JvmStatic
    @BindingAdapter("android:textInt")
    fun setText(view: EditText, text: Int) {
        view.setText("$text")
    }
```
```
//xml 
<EditText
    android:textInt="@{viewModel.num}"
```
- 数据绑定UI
```
//添加反向绑定
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
//添加属性变化方法
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
```
```
//xml 
<EditText
    android:textInt="@={viewModel.num}"
```

#### issue
- BindingAdapter 设置的自定义属性，在xml文件里面的值必须是“@{}”内容

给EditText创建textInt属性,否则无法生成对应的属性关联方法，导致无法找到对应的属性
```
    
    @JvmStatic
    @BindingAdapter("android:textInt")
    fun setText(view: EditText, text: Int) {
        view.setText("$text")
    }
```
对应的xml中的设值
```
<layout ...>
<data>
<variable
        name="viewModel"
        type="jetpark.test.com.mvvmdemo.viewMode.HomeViewModel"
        />
        </data>
<EditText
  ...
  ...
  android:textInt="@{viewModel.num}"
>
</layout>
```