#include <list>
#include <vector>
#include <string>
#include <string.h>
#include <pthread.h>
#include <cstring>
#include <jni.h>
#include <unistd.h>
#include <dlfcn.h>
#include <sstream>
#include <fstream>
#include <iostream>
#include "Includes/Logger.h"
#include "Includes/obfuscate.h"
#include "Includes/Utils.h"
#include "Includes/MonoString.h"
#include "Includes/Strings.h"
#include "KittyMemory/MemoryPatch.h"
#include "And64InlineHook/And64InlineHook.hpp"
#include "Menu.h"
#include "AutoHook/AutoHook.h"

//Target lib here
#define targetLibName OBFUSCATE("libil2cpp.so")

DWORD 
GetMaxModifiedSpeed,
GetCoinMultiplierBoost,
GetScoreMultiplier,
GetTripleCoinStartDistance,
CalcPickupDistance,
GetMagnetDurationBoost,
GetCurrentRank,
CanAffordCharacter,
IsPowerPurchased,
CanAffordRegion,
updatePotionsCountOfType,
ProcessGemProbability,
IsAdRemovalPurchased,
IsInvincible,
OnTriggerEnter,
CanAffordResurrect,
HasCompletedTutorial;

uintptr_t getBaseAddress;

void *hack_thread(void *) {
    LOGI(OBFUSCATE("Test ... Load"));
    
    do {
        sleep(1);
    } while (!isLibraryLoaded(targetLibName));
    
    LOGI(OBFUSCATE("Test ... Loaded"), (const char *) targetLibName);
    
    // Dumping Offsets
    getBaseAddress = getAbsoluteAddress(targetLibName, 0);
    auto TRRunnerPawn_S1 = new LoadClass("", OBFUSCATE("TRRunnerPawn"));
    auto GameProfile_S1 = new LoadClass("", OBFUSCATE("GameProfile"));
    auto RegionManager_S1 = new LoadClass("", OBFUSCATE("RegionManager")); 
    auto PlayerStats_S1 = new LoadClass("", OBFUSCATE("PlayerStats"));
    auto PotionsManager_S1 = new LoadClass("", OBFUSCATE("PotionsManager")); 
    auto PickupManager_S1 = new LoadClass("", OBFUSCATE("PickupManager")); 
    auto RunnerPowers_S1 = new LoadClass("", OBFUSCATE("RunnerPowers"));
    auto TRGameRunner_S1 = new LoadClass("", OBFUSCATE("TRGameRunner"));
    auto TutorialCompletionData_S1 = new LoadClass("", OBFUSCATE("TutorialCompletionData"));
    auto TRImangiStoreManager_S1 = new LoadClass("", OBFUSCATE("TRImangiStoreManager"));
	
	
	GetMaxModifiedSpeed = TRRunnerPawn_S1->GetMethodOffsetByName(OBFUSCATE("GetMaxModifiedSpeed"), 0);
	
	
	GetCoinMultiplierBoost = GameProfile_S1->GetMethodOffsetByName(OBFUSCATE("GetCoinMultiplierBoost"), 0);
	
	
	GetScoreMultiplier = GameProfile_S1->GetMethodOffsetByName(OBFUSCATE("GetScoreMultiplier"), 0);
	
	
	GetTripleCoinStartDistance = GameProfile_S1->GetMethodOffsetByName(OBFUSCATE("GetTripleCoinStartDistance"), 0);
	
	
	CalcPickupDistance = TRRunnerPawn_S1->GetMethodOffsetByName(OBFUSCATE("CalcPickupDistance"), 1);
	
	
	GetMagnetDurationBoost = GameProfile_S1->GetMethodOffsetByName(OBFUSCATE("GetMagnetDurationBoost"), 0);
	
	
	GetCurrentRank = PlayerStats_S1->GetMethodOffsetByName(OBFUSCATE("GetCurrentRank"), 0);
	
	
// HEX
	
	
	CanAffordCharacter = PlayerStats_S1->GetMethodOffsetByName(OBFUSCATE("CanAffordCharacter"), 1);
	
	
	IsPowerPurchased = PlayerStats_S1->GetMethodOffsetByName(OBFUSCATE("IsPowerPurchased"), 1);
	
	
	CanAffordRegion = RegionManager_S1->GetMethodOffsetByName(OBFUSCATE("CanAffordRegion"), 1);
	
	
	updatePotionsCountOfType = PotionsManager_S1->GetMethodOffsetByName(OBFUSCATE("updatePotionsCountOfType"), 3);
	
	
	ProcessGemProbability = PickupManager_S1->GetMethodOffsetByName(OBFUSCATE("ProcessGemProbability"), 1);
	
	
	IsAdRemovalPurchased = TRImangiStoreManager_S1->GetMethodOffsetByName(OBFUSCATE("IsAdRemovalPurchased"), 0);
	
	
	IsInvincible = RunnerPowers_S1->GetMethodOffsetByName(OBFUSCATE("IsInvincible"), 0);
	
	
	OnTriggerEnter = TRRunnerPawn_S1->GetMethodOffsetByName(OBFUSCATE("OnTriggerEnter"), 1);
	
	
	CanAffordResurrect = TRGameRunner_S1->GetMethodOffsetByName(OBFUSCATE("CanAffordResurrect"), 0);
	
	
	HasCompletedTutorial = TutorialCompletionData_S1->GetMethodOffsetByName(OBFUSCATE("HasCompletedTutorial"), 0);
	
	
    do {
        sleep(1);
    } while (!isLibraryLoaded (OBFUSCATE("libMyLibName.so")));
   
   
   return NULL;
}
 
extern "C" {

JNIEXPORT jstring JNICALL
Java_antik_modz_modmenu_FloatingModMenuService_Offset1(JNIEnv *env, jobject thiz) {
 std::stringstream stream1;
 stream1 << "0x" << std::uppercase << std::hex << (GetMaxModifiedSpeed - getBaseAddress);
   return env->NewStringUTF(stream1.str().c_str());
}
JNIEXPORT jstring JNICALL
Java_antik_modz_modmenu_FloatingModMenuService_Offset2(JNIEnv *env, jobject thiz) {
 std::stringstream stream2;
 stream2 << "0x" << std::uppercase << std::hex << (GetCoinMultiplierBoost - getBaseAddress);
   return env->NewStringUTF(stream2.str().c_str());
}
JNIEXPORT jstring JNICALL
Java_antik_modz_modmenu_FloatingModMenuService_Offset3(JNIEnv *env, jobject thiz) {
 std::stringstream stream3;
 stream3 << "0x" << std::uppercase << std::hex << (GetScoreMultiplier - getBaseAddress);
   return env->NewStringUTF(stream3.str().c_str());
}
JNIEXPORT jstring JNICALL
Java_antik_modz_modmenu_FloatingModMenuService_Offset4(JNIEnv *env, jobject thiz) {
 std::stringstream stream4;
 stream4 << "0x" << std::uppercase << std::hex << (GetTripleCoinStartDistance - getBaseAddress);
   return env->NewStringUTF(stream4.str().c_str());
}
JNIEXPORT jstring JNICALL
Java_antik_modz_modmenu_FloatingModMenuService_Offset5(JNIEnv *env, jobject thiz) {
 std::stringstream stream5;
 stream5 << "0x" << std::uppercase << std::hex << (CalcPickupDistance - getBaseAddress);
   return env->NewStringUTF(stream5.str().c_str());
}

JNIEXPORT jstring JNICALL
Java_antik_modz_modmenu_FloatingModMenuService_Offset6(JNIEnv *env, jobject thiz) {
 std::stringstream stream6;
 stream6 << "0x" << std::uppercase << std::hex << (GetMagnetDurationBoost - getBaseAddress);
   return env->NewStringUTF(stream6.str().c_str());
}

JNIEXPORT jstring JNICALL
Java_antik_modz_modmenu_FloatingModMenuService_Offset7(JNIEnv *env, jobject thiz) {
 std::stringstream stream7;
 stream7 << "0x" << std::uppercase << std::hex << (GetCurrentRank - getBaseAddress);
   return env->NewStringUTF(stream7.str().c_str());
}

JNIEXPORT jstring JNICALL
Java_antik_modz_modmenu_FloatingModMenuService_Offset8(JNIEnv *env, jobject thiz) {
 std::stringstream stream8;
 stream8 << "0x" << std::uppercase << std::hex << (CanAffordCharacter - getBaseAddress);
   return env->NewStringUTF(stream8.str().c_str());
}

JNIEXPORT jstring JNICALL
Java_antik_modz_modmenu_FloatingModMenuService_Offset9(JNIEnv *env, jobject thiz) {
 std::stringstream stream9;
 stream9 << "0x" << std::uppercase << std::hex << (IsPowerPurchased - getBaseAddress);
   return env->NewStringUTF(stream9.str().c_str());
}

JNIEXPORT jstring JNICALL
Java_antik_modz_modmenu_FloatingModMenuService_Offset10(JNIEnv *env, jobject thiz) {
 std::stringstream stream10;
 stream10 << "0x" << std::uppercase << std::hex << (CanAffordRegion - getBaseAddress);
   return env->NewStringUTF(stream10.str().c_str());
}

JNIEXPORT jstring JNICALL
Java_antik_modz_modmenu_FloatingModMenuService_Offset11(JNIEnv *env, jobject thiz) {
 std::stringstream stream11;
 stream11 << "0x" << std::uppercase << std::hex << (updatePotionsCountOfType - getBaseAddress);
   return env->NewStringUTF(stream11.str().c_str());
}

JNIEXPORT jstring JNICALL
Java_antik_modz_modmenu_FloatingModMenuService_Offset12(JNIEnv *env, jobject thiz) {
 std::stringstream stream12;
 stream12 << "0x" << std::uppercase << std::hex << (ProcessGemProbability - getBaseAddress);
   return env->NewStringUTF(stream12.str().c_str());
}

JNIEXPORT jstring JNICALL
Java_antik_modz_modmenu_FloatingModMenuService_Offset13(JNIEnv *env, jobject thiz) {
 std::stringstream stream13;
 stream13 << "0x" << std::uppercase << std::hex << (IsAdRemovalPurchased - getBaseAddress);
   return env->NewStringUTF(stream13.str().c_str());
}

JNIEXPORT jstring JNICALL
Java_antik_modz_modmenu_FloatingModMenuService_Offset14(JNIEnv *env, jobject thiz) {
 std::stringstream stream14;
 stream14 << "0x" << std::uppercase << std::hex << (IsInvincible - getBaseAddress);
   return env->NewStringUTF(stream14.str().c_str());
}

JNIEXPORT jstring JNICALL
Java_antik_modz_modmenu_FloatingModMenuService_Offset15(JNIEnv *env, jobject thiz) {
 std::stringstream stream15;
 stream15 << "0x" << std::uppercase << std::hex << (OnTriggerEnter - getBaseAddress);
   return env->NewStringUTF(stream15.str().c_str());
}

JNIEXPORT jstring JNICALL
Java_antik_modz_modmenu_FloatingModMenuService_Offset16(JNIEnv *env, jobject thiz) {
 std::stringstream stream16;
 stream16 << "0x" << std::uppercase << std::hex << (CanAffordResurrect - getBaseAddress);
   return env->NewStringUTF(stream16.str().c_str());
}

JNIEXPORT jstring JNICALL
Java_antik_modz_modmenu_FloatingModMenuService_Offset17(JNIEnv *env, jobject thiz) {
 std::stringstream stream17;
 stream17 << "0x" << std::uppercase << std::hex << (HasCompletedTutorial - getBaseAddress);
   return env->NewStringUTF(stream17.str().c_str());
}

JNIEXPORT jobjectArray
JNICALL
Java_antik_modz_modmenu_FloatingModMenuService_getFeatureList(JNIEnv *env, jobject context) {
    jobjectArray ret;

    //Toasts added here so it's harder to remove it
    AantikToast(env, context, OBFUSCATE("WELCOME TO OFFSET DUMPER"), 1);


    const char *features[] = {
            OBFUSCATE("Category_The Category"), //Not counted
            OBFUSCATE("mom_PREVIEW DUMP"),
            OBFUSCATE("ButtonLink_DUMP OFFSET_https://t.me/antik_modx"),
    };

    //Now you dont have to manually update the number everytime;
    int Total_Feature = (sizeof features / sizeof features[0]);
    ret = (jobjectArray)
            env->NewObjectArray(Total_Feature, env->FindClass(OBFUSCATE("java/lang/String")),
                                env->NewStringUTF(""));

    for (int i = 0; i < Total_Feature; i++)
        env->SetObjectArrayElement(ret, i, env->NewStringUTF(features[i]));

    pthread_t ptid;
    pthread_create(&ptid, NULL, antiLeech, NULL);

    return (ret);
}

JNIEXPORT void JNICALL
Java_antik_modz_modmenu_Preferences_Changes(JNIEnv *env, jclass clazz, jobject obj,
                                        jint featNum, jstring featName, jint value,
                                        jboolean boolean, jstring str) {

    LOGD(OBFUSCATE("Feature name: %d - %s | Value: = %d | Bool: = %d | Text: = %s"), featNum,
         env->GetStringUTFChars(featName, 0), value,
         boolean, str != NULL ? env->GetStringUTFChars(str, 0) : "");

    //BE CAREFUL NOT TO ACCIDENTLY REMOVE break;

    switch (featNum) {
    }
	
}
}

__attribute__((constructor))
void lib_main() {

    pthread_t ptid;
    pthread_create(&ptid, NULL, hack_thread, NULL);
}


