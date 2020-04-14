package com.mark.kaptlib

import com.squareup.kotlinpoet.*
import java.lang.Exception
import java.util.*
import javax.annotation.processing.*
import javax.lang.model.SourceVersion
import javax.lang.model.element.Element
import javax.lang.model.element.TypeElement
import javax.lang.model.element.VariableElement
import javax.lang.model.util.Elements
import javax.tools.Diagnostic

/*
 * @title
 * @author MarkLiu
 * @description
 * @create 2020/4/13-14:33
 */
@SupportedSourceVersion(SourceVersion.RELEASE_8)
class MarkGetProcessor : AbstractProcessor() {
    private var elementUtils: Elements? = null
    private var mFiler: Filer? = null
    private var mMessager: Messager? = null
    @Synchronized
    override fun init(processingEnv: ProcessingEnvironment) {
        super.init(processingEnv)
        elementUtils = processingEnv.elementUtils
        mFiler = processingEnv.filer
        mMessager = processingEnv.messager
        info("----- init -----")
    }

    override fun getSupportedAnnotationTypes(): Set<String> {
        val sets: MutableSet<String> =
            LinkedHashSet()
        sets.add(MarkGet::class.java.canonicalName)
        return sets
    }

    override fun process(
        annotations: Set<TypeElement?>,
        roundEnv: RoundEnvironment
    ): Boolean {
        info("p0:" + annotations.size)
        for (se in roundEnv.getElementsAnnotatedWith(MarkGet::class.java)) {
            generateClass(se)
            info(se.toString())
        }
        return true
    }

    fun generateClass(se: Element?) {
        if (se is VariableElement) {
            info("run generate" + se.enclosingElement.toString())
            val packageName =
                elementUtils!!.getPackageOf(se.enclosingElement).qualifiedName.toString()
            val tag = se.getAnnotation(MarkGet::class.java)
            val builder: TypeSpec.Builder =
                TypeSpec.classBuilder(se.enclosingElement.simpleName.toString() + "Print")
            builder.addProperty(
                PropertySpec.builder(
                    "str",
                    String::class
                ).initializer("\"mark\"").build()
            )
            val printFun: FunSpec.Builder =
                FunSpec.builder("print" + captureName(se.toString()))
                    .addStatement(
                        java.lang.String.format(
                            "System.out.println(\"%s is %s\")",
                            tag.value,
                            se.enclosingElement
                        )
                    ).addModifiers(KModifier.OPEN)
            builder.addFunction(printFun.build())
            builder.addModifiers(KModifier.OPEN)
            val fileSpec =
                FileSpec.builder(packageName, se.enclosingElement.simpleName.toString() + "Print")
                    .addType(builder.build()).build()
            try {
                fileSpec.writeTo(mFiler!!)
            } catch (e: Exception) {
                e.printStackTrace()
            }
        }
    }

    fun info(str: String?) {
        mMessager!!.printMessage(Diagnostic.Kind.NOTE, str)
    }

    companion object {
        fun captureName(name: String): String {
            val cs = name.toCharArray()
            cs[0] = cs[0] - 32
            return String(cs)
        }
    }
}