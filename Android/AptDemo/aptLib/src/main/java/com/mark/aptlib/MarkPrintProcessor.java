package com.mark.aptlib;

import com.google.auto.service.AutoService;
import com.squareup.javapoet.JavaFile;
import com.squareup.javapoet.MethodSpec;
import com.squareup.javapoet.TypeName;
import com.squareup.javapoet.TypeSpec;

import java.io.IOException;
import java.util.LinkedHashSet;
import java.util.Set;

import javax.annotation.processing.AbstractProcessor;
import javax.annotation.processing.Filer;
import javax.annotation.processing.Messager;
import javax.annotation.processing.ProcessingEnvironment;
import javax.annotation.processing.Processor;
import javax.annotation.processing.RoundEnvironment;
import javax.annotation.processing.SupportedSourceVersion;
import javax.lang.model.SourceVersion;
import javax.lang.model.element.Element;
import javax.lang.model.element.Modifier;
import javax.lang.model.element.TypeElement;
import javax.lang.model.element.VariableElement;
import javax.lang.model.util.Elements;
import javax.tools.Diagnostic;

/*
 * @title
 * @author MarkLiu
 * @description
 * @create 2020/4/13-14:33
 */

@SupportedSourceVersion(SourceVersion.RELEASE_8)
public class MarkPrintProcessor extends AbstractProcessor {
    private Elements elementUtils;
    private Filer mFiler;
    private Messager mMessager;

    @Override
    public synchronized void init(ProcessingEnvironment processingEnv) {
        super.init(processingEnv);
        elementUtils = processingEnv.getElementUtils();
        mFiler = processingEnv.getFiler();
        mMessager = processingEnv.getMessager();
        info("----- init -----");
    }

    @Override
    public Set<String> getSupportedAnnotationTypes() {
        Set<String> sets = new LinkedHashSet<>();
        sets.add(MarkPrint.class.getCanonicalName());
        return sets;
    }

    @Override
    public boolean process(Set<? extends TypeElement> annotations, RoundEnvironment roundEnv) {
        info("p0:" + annotations.size());

        for (Element se : roundEnv.getElementsAnnotatedWith(MarkPrint.class)) {
            generateClass(se);
            info(se.toString());
        }
        return true;
    }

    void generateClass(Element se) {
        if (se instanceof VariableElement) {
            VariableElement vse = (VariableElement) se;

            info("run generate" + vse.getEnclosingElement().toString());
            String packageName = elementUtils.getPackageOf(vse.getEnclosingElement()).getQualifiedName().toString();
            MarkPrint tag = vse.getAnnotation(MarkPrint.class);

            TypeSpec.Builder builder = TypeSpec.classBuilder(vse.getEnclosingElement().getSimpleName() + "Print");
            builder.addField(TypeName.CHAR, "print", Modifier.PUBLIC);
            MethodSpec.Builder printFun = MethodSpec.methodBuilder("print" + captureName(vse.toString()))
                    .addStatement(String.format("System.out.println(\"%s is %s\")", tag.value(), vse.getEnclosingElement().toString()))
                    .addModifiers(Modifier.PUBLIC);
            builder.addMethod(printFun.build());
            builder.addModifiers(Modifier.PUBLIC);

            JavaFile javaFile = JavaFile.builder(packageName, builder.build()).build();
            try {
                javaFile.writeTo(mFiler);
            } catch (Exception e) {
                e.printStackTrace();
            }
        }
    }

    public void info(String str) {
        mMessager.printMessage(Diagnostic.Kind.NOTE, str);
    }

    public static String captureName(String name) {
        char[] cs = name.toCharArray();
        cs[0] -= 32;
        return String.valueOf(cs);
    }
}
