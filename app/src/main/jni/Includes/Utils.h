#ifndef UTILS
#define UTILS

#include <jni.h>
#include <unistd.h>
#include <cstdio>
#include <cstring>
#include <string>
#include <cstdlib>
#include "Logger.h"

typedef unsigned long DWORD;
static uintptr_t libBase;

bool isGameLibLoaded = false;

DWORD findLibrary(const char *library) {
    char filename[0xFF] = {0},
            buffer[1024] = {0};
    FILE *fp = NULL;
    DWORD address = 0;

    sprintf(filename, OBFUSCATE("/proc/self/maps"));

    fp = fopen(filename, OBFUSCATE("rt"));
    if (fp == NULL) {
        perror(OBFUSCATE("fopen"));
        goto done;
    }

    while (fgets(buffer, sizeof(buffer), fp)) {
        if (strstr(buffer, library)) {
            address = (DWORD) strtoul(buffer, NULL, 16);
            goto done;
        }
    }

    done:

    if (fp) {
        fclose(fp);
    }

    return address;
}

DWORD getAbsoluteAddress(const char *libraryName, DWORD relativeAddr) {
    libBase = findLibrary(libraryName);
    if (libBase == 0)
        return 0;
    return (reinterpret_cast<DWORD>(libBase + relativeAddr));
}

extern "C" {
JNIEXPORT jboolean JNICALL
Java_uk_lgl_modmenu_FloatingModMenuService_isGameLibLoaded(JNIEnv *env, jobject thiz) {
    return isGameLibLoaded;
}
}

bool isLibraryLoaded(const char *libraryName) {
    //isGameLibLoaded = true;
    char line[512] = {0};
    FILE *fp = fopen(OBFUSCATE("/proc/self/maps"), OBFUSCATE("rt"));
    if (fp != NULL) {
        while (fgets(line, sizeof(line), fp)) {
            std::string a = line;
            if (strstr(line, libraryName)) {
                isGameLibLoaded = true;
                return true;
            }
        }
        fclose(fp);
    }
    return false;
}

//Credit: Octowolve
void MakeToast(JNIEnv *env, jobject thiz, const char *text, int length) {
    //Add our toast in here so it wont be easy to change by simply editing the smali and cant
    //be cut out because this method is needed to start the hack (Octowolve is smart)
    jstring jstr = env->NewStringUTF(text); //Edit this text to your desired toast message!
    jclass toast = env->FindClass(OBFUSCATE("android/widget/Toast"));
    jmethodID methodMakeText =
            env->GetStaticMethodID(
                    toast,
                    OBFUSCATE("makeText"),
                    OBFUSCATE(
                            "(Landroid/content/Context;Ljava/lang/CharSequence;I)Landroid/widget/Toast;"));
    if (methodMakeText == NULL) {
        LOGE(OBFUSCATE("toast.makeText not Found"));
        return;
    }
    //The last int is the length on how long the toast should be displayed
    //0 = Short, 1 = Long
    jobject toastobj = env->CallStaticObjectMethod(toast, methodMakeText,
                                                   thiz, jstr, length);

    jmethodID methodShow = env->GetMethodID(toast, OBFUSCATE("show"), OBFUSCATE("()V"));
    if (methodShow == NULL) {
        LOGE(OBFUSCATE("toast.show not Found"));
        return;
    }
    env->CallVoidMethod(toastobj, methodShow);
}

uintptr_t string2Offset(const char *c) {
    int base = 16;
    // See if this function catches all possibilities.
    // If it doesn't, the function would have to be amended
    // whenever you add a combination of architecture and
    // compiler that is not yet addressed.
    static_assert(sizeof(uintptr_t) == sizeof(unsigned long)
                  || sizeof(uintptr_t) == sizeof(unsigned long long),
                  "Please add string to handle conversion for this architecture.");

    // Now choose the correct function ...
    if (sizeof(uintptr_t) == sizeof(unsigned long)) {
        return strtoul(c, nullptr, base);
    }

    // All other options exhausted, sizeof(uintptr_t) == sizeof(unsigned long long))
    return strtoull(c, nullptr, base);
}

int ConvertIntToDp(JNIEnv *env, jobject context, int i) {
    jclass tvClass = env->FindClass("android/util/TypedValue");
    jmethodID applyDimensionMethod = env->GetStaticMethodID(tvClass, "applyDimension", "(IFLandroid/util/DisplayMetrics;)F");
    jfieldID complexUnitDipField = env->GetStaticFieldID(tvClass, "COMPLEX_UNIT_DIP", "I");
	jint complexUnitDip = env->GetStaticIntField(tvClass, complexUnitDipField);
	jclass contextClass = env->GetObjectClass(context);
	jmethodID getResourcesMethod = env->GetMethodID(contextClass, "getResources", "()Landroid/content/res/Resources;");
    jobject getResourcesObj = env->CallObjectMethod(context, getResourcesMethod);
	jclass getDisplayMetricsClass = env->GetObjectClass(getResourcesObj);
	jmethodID getDisplayMetricsMethod = env->GetMethodID(getDisplayMetricsClass, "getDisplayMetrics", "()Landroid/util/DisplayMetrics;");
    jobject getDisplayMetricsObj = env->CallObjectMethod(getResourcesObj, getDisplayMetricsMethod);
    jfloat pixelValue = env->CallStaticFloatMethod(tvClass, applyDimensionMethod, complexUnitDip, (jfloat)i, getDisplayMetricsObj);
	
	env->DeleteLocalRef(tvClass);
    env->DeleteLocalRef(contextClass);
	env->DeleteLocalRef(getResourcesObj);
    env->DeleteLocalRef(getDisplayMetricsClass);
    env->DeleteLocalRef(getDisplayMetricsObj);
	return (int) pixelValue;
}

void AantikToast(JNIEnv *env, jobject context, const char *text, int lenght) {
	jclass toastClass = env->FindClass("android/widget/Toast");
    jmethodID toastConstructor = env->GetMethodID(toastClass, "<init>", "(Landroid/content/Context;)V");
    jobject toastObj = env->NewObject(toastClass, toastConstructor, context);
    
	
    jstring messageStr = env->NewStringUTF(text);
	jclass colorClass = env->FindClass("android/graphics/Color");
    jmethodID parseColorMethod = env->GetStaticMethodID(colorClass, "parseColor", "(Ljava/lang/String;)I");
    jstring colorStr = env->NewStringUTF("#FF00FFFF");
    jstring colorStr2 = env->NewStringUTF("#FF0A0A0A");
	int textColorCode = env->CallStaticIntMethod(colorClass, parseColorMethod, colorStr);
	int backgroundColorCode = env->CallStaticIntMethod(colorClass, parseColorMethod, colorStr2);
	jclass porterDuffModeClass = env->FindClass("android/graphics/PorterDuff$Mode");
    jfieldID srcInField = env->GetStaticFieldID(porterDuffModeClass, "SRC_IN", "Landroid/graphics/PorterDuff$Mode;");
	jobject srcInObj = env->GetStaticObjectField(porterDuffModeClass, srcInField);
    jclass cls = env->FindClass("android/graphics/drawable/GradientDrawable");
    jmethodID constructor = env->GetMethodID(cls, "<init>", "()V");
    jobject body = env->NewObject(cls, constructor);
    
    // Set corner radius
    jmethodID setCornerRadil = env->GetMethodID(cls, "setCornerRadii", "([F)V");
    jfloatArray cornerRadii = env->NewFloatArray(8);
    jfloat radii[] = { ConvertIntToDp(env, context, 0), ConvertIntToDp(env, context, 0), ConvertIntToDp(env, context, 15), ConvertIntToDp(env, context, 15), ConvertIntToDp(env, context, 0), ConvertIntToDp(env, context, 0), ConvertIntToDp(env, context, 15), ConvertIntToDp(env, context, 15) }; // adjust radii as needed
    env->SetFloatArrayRegion(cornerRadii, 0, 8, radii);
    env->CallVoidMethod(body, setCornerRadil, cornerRadii);
    
    // Set stroke
    jmethodID setStrokeMethod = env->GetMethodID(cls, "setStroke", "(II)V");
    env->CallVoidMethod(body, setStrokeMethod, ConvertIntToDp(env, context, 1), textColorCode); // 2 is stroke width, adjust as needed
    
    // Set background color
    jmethodID setColorMethod = env->GetMethodID(cls, "setColor", "(I)V");
    env->CallVoidMethod(body, setColorMethod, backgroundColorCode);

    
    jclass linearLayoutClass = env->FindClass("android/widget/LinearLayout");
    jmethodID linearLayoutConstructor = env->GetMethodID(linearLayoutClass, "<init>", "(Landroid/content/Context;)V");
    jobject linearLayoutObj = env->NewObject(linearLayoutClass, linearLayoutConstructor, context);
    jmethodID setBackground = env->GetMethodID(linearLayoutClass, "setBackground", "(Landroid/graphics/drawable/Drawable;)V");
    env->CallVoidMethod(linearLayoutObj, setBackground, body);
    jmethodID setPadding = env->GetMethodID(linearLayoutClass, "setPadding", "(IIII)V");
    env->CallVoidMethod(linearLayoutObj, setPadding, ConvertIntToDp(env, context, 2), ConvertIntToDp(env, context, 2), ConvertIntToDp(env, context, 2), ConvertIntToDp(env, context, 2));
    jmethodID setDuration = env->GetMethodID(toastClass, "setDuration", "(I)V");
    env->CallVoidMethod(toastObj, setDuration, lenght);
    jclass textViewClass = env->FindClass("android/widget/TextView");
    jmethodID textViewConstructor = env->GetMethodID(textViewClass, "<init>", "(Landroid/content/Context;)V");
    jobject textViewObj = env->NewObject(textViewClass, textViewConstructor, context);
    jmethodID setTextMethod = env->GetMethodID(textViewClass, "setText", "(Ljava/lang/CharSequence;)V");
    env->CallVoidMethod(textViewObj, setTextMethod, messageStr);
    jmethodID setTextColorMethod = env->GetMethodID(textViewClass, "setTextColor", "(I)V");
    env->CallVoidMethod(textViewObj, setTextColorMethod, textColorCode);
    jmethodID setPadding2 = env->GetMethodID(textViewClass, "setPadding", "(IIII)V");
    env->CallVoidMethod(textViewObj, setPadding2, ConvertIntToDp(env, context, 3), ConvertIntToDp(env, context, 3), ConvertIntToDp(env, context, 3), ConvertIntToDp(env, context, 3));
	jmethodID addViewMethod = env->GetMethodID(linearLayoutClass, "addView", "(Landroid/view/View;)V");
    env->CallVoidMethod(linearLayoutObj, addViewMethod, textViewObj);
    jmethodID setViewMethod = env->GetMethodID(toastClass, "setView", "(Landroid/view/View;)V");
    env->CallVoidMethod(toastObj, setViewMethod, linearLayoutObj);
	jmethodID showMethod = env->GetMethodID(toastClass, "show", "()V");
    env->CallVoidMethod(toastObj, showMethod);
	
    env->DeleteLocalRef(messageStr);
    env->DeleteLocalRef(colorStr);
    env->DeleteLocalRef(colorStr2);
	env->DeleteLocalRef(colorClass);
    env->DeleteLocalRef(porterDuffModeClass);
	env->DeleteLocalRef(srcInObj);
    env->DeleteLocalRef(cls);
    env->DeleteLocalRef(body);
    env->DeleteLocalRef(linearLayoutClass);
	env->DeleteLocalRef(linearLayoutObj);
    env->DeleteLocalRef(toastClass);
	env->DeleteLocalRef(toastObj);
    env->DeleteLocalRef(textViewClass);
    env->DeleteLocalRef(textViewObj);
}

namespace Toast {
    inline const int LENGTH_LONG = 1;
    inline const int LENGTH_SHORT = 0;
}

#endif