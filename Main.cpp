my bypass.h i want updat and add bypaas ->/**
 * ╔══════════════════════════════════════════════════════════╗
 * ║                                                                     ║
 * ║   Bypass by IBR                                                     ║
 * ║   Allah hu akbar, Made with 💖 by IBR                               ║
 * ║                                                                     ║
 * ╚══════════════════════════════════════════════════════════╝
 */

#pragma once

// ▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄
// █ Standard Library Includes - Allah hu akbar, Made with 💖 by IBR
// ▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀
#include <list>
#include <vector>
#include <string.h>
#include <pthread.h>
#include <thread>
#include <cstring>
#include <jni.h>
#include <unistd.h>
#include <fstream>
#include <iostream>
#include <dlfcn.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <stdio.h>
#include <dlfcn.h>
#include <sys/mman.h>
#include <android/log.h> // Added for logging

// ▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄
// █ Custom Includes - Allah hu akbar, Made with 💖 by IBR
// ▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀
#include "Includes/Logger.h"
//#include "Includes/obfuscate.h"
#include "Includes/Utils.h"
#include "KittyMemory/MemoryPatch.h"
#include "Includes/Macros.h"

// ▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄
// █ Type Definitions - Allah hu akbar, Made with 💖 by IBR
// ▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀
#define _BYTE  uint8_t
#define _WORD  uint16_t
#define _DWORD uint32_t
#define _QWORD uint64_t

// Define a logging macro for debugging
#define LOG_TAG "RIYAZ_VIP_MOD"
#define LOGD(...) __android_log_print(ANDROID_LOG_DEBUG, LOG_TAG, __VA_ARGS__)

// ▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄
// █ Target Libraries - Allah hu akbar, Made with 💖 by IBR
// ▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀
#define targetLibName OBFUSCATE("libUE4.so")
uintptr_t libanogsBase = 0;
uintptr_t libUE4Base = 0;
uintptr_t libanogsAlloc = 0;
uintptr_t libUE4Alloc = 0;
DWORD libanogsSize = 0;
DWORD libUE4Size = 0;

// ▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄
// █ Hook Definition Macros - Allah hu akbar, Made with 💖 by IBR
// ▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀
#define DefineHook(RET, NAME, ARGS) \
    RET(*orig_##NAME) ARGS; \
    RET hook_##NAME ARGS

#define MTR(RET, NAME, ARGS) \
    RET(*o##NAME) ARGS; \
    RET h##NAME ARGS

#define SA3EEK(RET, NAME, ARGS) \
    RET(*o##NAME) ARGS; \
    RET h##NAME ARGS

// ▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄
// █ Anti-Detection Functions - Allah hu akbar, Made with 💖 by IBR
// ▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀

// Hang task function to pause execution
void (*ohangTask)();
void hangTask() {
    // Allah hu akbar, Made with 💖 by IBR
    sleep(100000);
}

// ▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄
// █ Memory Region Initialization - Allah hu akbar, Made with 💖 by IBR
// ▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀
int init_memory_region(int a1) {
    // Allah hu akbar, Made with 💖 by IBR
    int page_size;
    void *mem_base;
    void *mem_protect;

    *(int *)(a1 + 16) = -1;
    *(char *)(a1 + 12) = 0;
    *(int *)(a1 + 4) = 0;
    memset((void *)(a1 + 20), 0, 0x20);

    page_size = sysconf(_SC_PAGESIZE);
    *(int *)(a1 + 8) = 2 * page_size;

    int alloc_size = *(int *)(a1 + 8);
    if (alloc_size < 0)
        alloc_size = -1;

    *(void **)a1 = malloc(alloc_size);  // Try malloc first

    if (*(void **)a1) {
        memset(*(void **)a1, 0, alloc_size);

        // Align to next page
        mem_protect = (void *)(((uintptr_t)*(void **)a1 & ~(page_size - 1)) + page_size);
        *(void **)(a1 + 4) = mem_protect;

        if (mprotect(mem_protect, page_size, PROT_READ | PROT_WRITE | PROT_EXEC) == -1) {
            free(*(void **)a1);
            *(void **)a1 = mmap(NULL, alloc_size, PROT_READ | PROT_WRITE | PROT_EXEC,
                                MAP_ANONYMOUS | MAP_PRIVATE, -1, 0);

            if (*(void **)a1 == MAP_FAILED) {
                *(void **)a1 = NULL;
                *(int *)(a1 + 4) = 0;
                return a1;
            }

            *(char *)(a1 + 12) = 1;  // mmap flag
            memset(*(void **)a1, 0, alloc_size);
            *(void **)(a1 + 4) = (void *)(((uintptr_t)*(void **)a1 & ~(page_size - 1)) + page_size);

            if (mprotect(*(void **)(a1 + 4), page_size, PROT_READ | PROT_WRITE | PROT_EXEC) == -1) {
                munmap(*(void **)a1, alloc_size);
                *(void **)a1 = NULL;
                *(int *)(a1 + 4) = 0;
                return a1;
            }
        }

        *(int *)(a1 + 16) = page_size;
    }

    return a1;
}

// ▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄
// █ Monitoring Thread - Allah hu akbar, Made with 💖 by IBR
// ▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀
void *anogs_thread(void *) {
    // Allah hu akbar, Made with 💖 by IBR
    do {
        sleep(1);
    } while (!isLibraryLoaded("libanogs.so"));

    // Apply main bypass patches - Allah hu akbar, Made with 💖 by IBR
    PATCH_LIB("libanogs.so", "0x27A9E4", "00 00 80 D2 C0 03 5F D6");
    PATCH_LIB("libanogs.so", "0x27A218", "00 00 80 D2 C0 03 5F D6");
    PATCH_LIB("libanogs.so", "0x27A103", "00 00 80 D2 C0 03 5F D6");
    PATCH_LIB("libanogs.so", "0x27A38A", "00 00 80 D2 C0 03 5F D6");
    PATCH_LIB("libanogs.so", "0x27A2D8", "00 00 80 D2 C0 03 5F D6");
    PATCH_LIB("libanogs.so", "0x27A000", "00 00 80 D2 C0 03 5F D6");
    PATCH_LIB("libanogs.so", "0x27A7E4", "00 00 80 D2 C0 03 5F D6");
    PATCH_LIB("libanogs.so", "0x27AD63", "00 00 80 D2 C0 03 5F D6");
    PATCH_LIB("libanogs.so", "0x27A0D8", "00 00 80 D2 C0 03 5F D6");
    PATCH_LIB("libanogs.so", "0x27A5B3", "00 00 80 D2 C0 03 5F D6");
    PATCH_LIB("libanogs.so", "0x27A0D8", "00 00 80 D2 C0 03 5F D6");
    PATCH_LIB("libanogs.so", "0x27AD63", "00 00 80 D2 C0 03 5F D6");
    PATCH_LIB("libanogs.so", "0x27A9E4", "00 00 80 D2 C0 03 5F D6");
    PATCH_LIB("libanogs.so", "0x27A137", "00 00 80 D2 C0 03 5F D6");
    PATCH_LIB("libanogs.so", "0x27A218", "00 00 80 D2 C0 03 5F D6");
    PATCH_LIB("libanogs.so", "0x27A755", "00 00 80 D2 C0 03 5F D6");
    PATCH_LIB("libanogs.so", "0x27A3B8", "00 00 80 D2 C0 03 5F D6");
    PATCH_LIB("libanogs.so", "0x27A2D8", "00 00 80 D2 C0 03 5F D6");
    PATCH_LIB("libanogs.so", "0x27A5B3", "00 00 80 D2 C0 03 5F D6");
    
    return NULL;
}

// ▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄
// █ Hook Functions - Allah hu akbar, Made with 💖 by IBR
// ▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀

// Function pointer for oC16
typedef int (*oC16_t)(int, char*, int);
oC16_t oC16 = nullptr;

// Initialize the hook by dynamically resolving oC16
bool initialize_hook() {
    // Open the target library (libpubgm.so)
    void* handle = dlopen("libpubgm.so", RTLD_LAZY);
    if (!handle) {
        LOGD("Failed to open libpubgm.so: %s", dlerror());
        return false;
    }

    // Resolve the address of oC16
    oC16 = (oC16_t)dlsym(handle, "oC16");
    if (!oC16) {
        LOGD("Failed to find oC16: %s", dlerror());
        dlclose(handle);
        return false;
    }

    // Optionally, keep the handle open if needed for other symbols
    // dlclose(handle); // Uncomment if you don't need the handle anymore
    LOGD("Successfully resolved oC16");
    return true;
}

// C16 String Detection Hook - Allah hu akbar, Made with 💖 by IBR
int hC16(int a1, char* a2, int a3) {
    // Ensure oC16 is initialized
    if (!oC16) {
        LOGD("oC16 not initialized, attempting to initialize...");
        if (!initialize_hook()) {
            LOGD("Failed to initialize oC16, returning 0");
            return 0; // Fallback: return 0 to avoid crashes
        }
    }

    // Get the return address (for debugging or anti-anti-cheat purposes)
    auto ret = reinterpret_cast<uintptr_t>(__builtin_return_address(0));
    LOGD("hC16 called with return address: %p", (void*)ret);

    // Block detection strings - Allah hu akbar, Made with 💖 by IBR
    if (
        strstr((char*)a2, "crash") ||
        strstr((char*)a2, "Mrpcs") ||
        strstr((char*)a2, "no_tshe") ||
        strstr((char*)a2, "CSReconnect") ||
        strstr((char*)a2, "cs3") ||
        strstr((char*)a2, "gcloud_log") ||
        strstr((char*)a2, "tdm_report") ||
        strstr((char*)a2, "mt_sar") ||
        strstr((char*)a2, "sec_path") ||
        strstr((char*)a2, "x_task") ||
        strstr((char*)a2, "XTask_builtin.zip_vm_main.img") ||
        strstr((char*)a2, "adb") ||
        strstr((char*)a2, "wifi_adb") ||
        strstr((char*)a2, "property_get") ||
        strstr((char*)a2, "XTask_builtin.zip_vm_x_task.img") ||
        strstr((char*)a2, "ob_local") ||
        strstr((char*)a2, "mrpcs1") ||
        strstr((char*)a2, "mrsen_th") ||
        strstr((char*)a2, "e_hbeat") ||
        strstr((char*)a2, "scan1") ||
        strstr((char*)a2, "user_tag") ||
        strstr((char*)a2, "qos_filt") ||
        strstr((char*)a2, "gp3_ext") ||
        strstr((char*)a2, "sc_idle") ||
        strstr((char*)a2, "gp4_2") ||
        strstr((char*)a2, "anti_ts2") ||
        strstr((char*)a2, "ts2_timejudge") ||
        strstr((char*)a2, "mem_trap2") ||
        strstr((char*)a2, "interface_test") ||
        strstr((char*)a2, "gp3_no_adb") ||
        strstr((char*)a2, "random_trap") ||
        strstr((char*)a2, "gp3_2022") ||
        strstr((char*)a2, "memtrap_name") ||
        strstr((char*)a2, "gp4_no_root") ||
        strstr((char*)a2, "gp4_pagemap") ||
        strstr((char*)a2, "gp4_nonblock") ||
        strstr((char*)a2, "report_bk") ||
        strstr((char*)a2, "sc_dlp") ||
        strstr((char*)a2, "cdn_java") ||
        strstr((char*)a2, "ext_cdn_first") ||
        strstr((char*)a2, "comm_first") ||
        strstr((char*)a2, "memsafe") ||
        strstr((char*)a2, "screenshot") ||
        strstr((char*)a2, "mrmoni_th") ||
        strstr((char*)a2, "mrmoni_fb") ||
        strstr((char*)a2, "mrmoni_fc") ||
        strstr((char*)a2, "MrpcsActiveSig") ||
        strstr((char*)a2, "down_mrpcs") ||
        strstr((char*)a2, "XTask_ob_x.zip_android_attest.img") ||
        strstr((char*)a2, "XTask_ob_x.zip_av.img") ||
        strstr((char*)a2, "XTask_ob_x.zip_delete_ft_cache.img") ||
        strstr((char*)a2, "XTask_ob_x.zip_detect_magisk_delta.img") ||
        strstr((char*)a2, "HBCheck") ||
        strstr((char*)a2, "tcj_encrypt") ||
        strstr((char*)a2, "game_host") ||
        strstr((char*)a2, "cs_ipv6") ||
        strstr((char*)a2, "no_built_in_ip") ||
        strstr((char*)a2, "ipv4_first") ||
        strstr((char*)a2, "cs_80_port") ||
        strstr((char*)a2, "tcj") ||
        strstr((char*)a2, "info") ||
        strstr((char*)a2, "ObfQos") ||
        strstr((char*)a2, "vps") ||
        strstr((char*)a2, "force_apk_collect") ||
        strstr((char*)a2, "apk_permission") ||
        strstr((char*)a2, "acna_bi") ||
        strstr((char*)a2, "binder_apk") ||
        strstr((char*)a2, "jni_apk_ext") ||
        strstr((char*)a2, "u_old_m") ||
        strstr((char*)a2, "UseTwoMth") ||
        strstr((char*)a2, "cal_cert_md5") ||
        strstr((char*)a2, "rcv_by_main") ||
        strstr((char*)a2, "apk_by_pm") ||
        strstr((char*)a2, "ap_ca") ||
        strstr((char*)a2, "tdm_dev_info") ||
        strstr((char*)a2, "GCloudCtrl") ||
        strstr((char*)a2, "device_info") ||
        strstr((char*)a2, "report_apk") ||
        strstr((char*)a2, "ignore_sys_apk") ||
        strstr((char*)a2, "sensor_detect") ||
        strstr((char*)a2, "anti_ida") ||
        strstr((char*)a2, "anti_frida") ||
        strstr((char*)a2, "XTask_ob_cs1.zip_ser.img") ||
        strstr((char*)a2, "ne_loc_m")
    ) {
        LOGD("Blocked detection string: %s", a2);
        return 0;
    }

    LOGD("Passing string to oC16: %s", a2);
    return oC16(a1, a2, a3);
}

// Memory Copy Hook - Allah hu akbar, Made with 💖 by IBR
void* hmemcpy(void* dest, const void* src, size_t n) {
    // Allah hu akbar, Made with 💖 by IBR
    if (n > 0 && src != 0) {
        size_t sa3eeksize = 0x1;
        return memcpy(dest, src, sa3eeksize);
    }
    
    return memcpy(dest, src, n);
}

// Memory Offsets Hook - Allah hu akbar, Made with 💖 by IBR
void *memcpy_hooks(char *dest, const char *src, size_t size) {
    // Allah hu akbar, Made with 💖 by IBR
    char *Offset;
    char *NewBase;
    
    if ((DWORD)size > (DWORD)0x10000 && (DWORD)src >= libanogsBase && (DWORD)src <= (DWORD)(libanogsBase + libanogsSize)) {
        Offset = (char *)(src - (char *)libanogsBase);
        NewBase = (char *)libanogsAlloc;
       // src = &Offset[NewBase];
        return memcpy(dest, src, size);
    }
    
    if ((DWORD)size > (DWORD)0x10000 && (DWORD)src >= libUE4Base && (DWORD)src <= (DWORD)(libUE4Base + libUE4Size)) {
        Offset = (char *)(src - (char *)libUE4Base);
        NewBase = (char *)libUE4Alloc;
       // src = &Offset[NewBase];
        return memcpy(dest, src, size);
    }
    
    return memcpy(dest, src, size);
}

// String Length Hook - Allah hu akbar, Made with 💖 by IBR
size_t hook_strlen(const char *s) {
    // Allah hu akbar, Made with 💖 by IBR
    if (s == NULL) {
        return 0;
    }
    if (strstr(s, "AnoSDKIoctlOld") != NULL && strstr(s, "AnoSDKIoctl") != NULL) {
        return 0;
    }
    return strlen(s);
}

// String Search Hook - Allah hu akbar, Made with 💖 by IBR
char* hstrstr(char* haystack, char* needle) {
    // Allah hu akbar, Made with 💖 by IBR
    if (
        strstr(needle, "BP_PlayerCharacter") ||
        strstr(needle, "scan_engine1_start")
    ) {
        return 0;
    }
    
    return strstr(haystack, needle);
}

// Hook DLSYM for library hiding - Allah hu akbar, Made with 💖 by IBR
void *hook_dlsym(void* handle, const char* name) {
    // Allah hu akbar, Made with 💖 by IBR
    if (
    strstr(name, "BP_PlayerCharacter") ||
    strstr(name, "memset") ||
    strstr(name, "memcpy") ||   
    strstr(name, "access") ||
    strstr(name, "strncpy") ||
    strstr(name, "madvise") ||
    strstr(name, "__android_log_print") ||
    strstr(name, "__system_property_get") ||
    strstr(name, "scan_engine1_start")    
        )
    {
        return 0;
    }
    return dlsym(handle, name);
}

// AntiCheat Thread Hook - Allah hu akbar, Made with 💖 by IBR
SA3EEK(int, anticheatthread, (int a1)) {
    // Allah hu akbar, Made with 💖 by IBR
    if (strstr(reinterpret_cast<char*>(a1), "ace_rp_queue")) {
        return 0;
    }
    return oanticheatthread(a1);
}

// Termination Hook - Allah hu akbar, Made with 💖 by IBR
int (*otermi)(_BYTE *a1, int a2, const char *a3, int a4);
int htermi(_BYTE *a1, int a2, const char *a3, int a4) {
    // Allah hu akbar, Made with 💖 by IBR
    int result = 0;
    uintptr_t SAAEK = reinterpret_cast<uintptr_t>(__builtin_return_address(0));
    uintptr_t ret = SAAEK - libanogsBase; 

    if (a2 >= 1) {
        return otermi(a1, a2, a3, a4);
    }

    return result;
}

// Memory Check Hook - Allah hu akbar, Made with 💖 by IBR
MTR(int, MemChk, (int a1, int a2)) {
    // Allah hu akbar, Made with 💖 by IBR
    return 0;
}

// Text Segment CRC Hook - Allah hu akbar, Made with 💖 by IBR
MTR(int, txt_seg_crc, (int a1, _DWORD *a2, void **a3, size_t *a4)) {
    // Allah hu akbar, Made with 💖 by IBR
    return 0;
}

// CRC Calculations Hook - Allah hu akbar, Made with 💖 by IBR
MTR(int, CRCCalculations, (const void *a1, size_t a2)) {
    // Allah hu akbar, Made with 💖 by IBR
    return 0;
}

// AnoSDKIoctlOld_0 Hook - Allah hu akbar, Made with 💖 by IBR
MTR(int, AnoSDKIoctlOld_0, (int a1, char* Text, void** ByteArray, unsigned int a4, int* ByteArraySize)) {
    // Allah hu akbar, Made with 💖 by IBR
    int ToBe = 0;
    auto ret = reinterpret_cast<uintptr_t>(__builtin_return_address(0));
    switch (a1) {
        default:
            ToBe = oAnoSDKIoctlOld_0(a1, Text, ByteArray, a4, ByteArraySize);
            break;
    }
    LOGI("IOCTL|C%d|%s|Result:%d", a1, Text, ToBe);
    return ToBe;
}

// Opcode Bypass Hook - Allah hu akbar, Made with 💖 by IBR
bool __fastcall (*osub_1EB7BC)(__int64 a1, __int64 a2, char a3);
bool __fastcall hsub_1EB7BC(__int64 a1, __int64 a2, char a3) {
    // Allah hu akbar, Made with 💖 by IBR
    LOGI(OBFUSCATE("Case 16 Calling : a1 -> %lld | a2 -> %s | a3 -> %d"), a1, (const char *)a2, a3);
    const char* str = (const char *)a2;
    if (strstr(str, "opcode_crash") || 
        strstr(str, "opcode_scan") || 
        strstr(str, "zygisk_module"))
    {
        LOGI(OBFUSCATE("Blocked Function | %s is Being Called From Address | %p"), str, (void*)a2);
        pthread_exit(nullptr);
        return false;
    }
    else
    {
        LOGI(OBFUSCATE("Allowed Function | %s is Being Called From Address | %p"), str, (void*)a2);
        return osub_1EB7BC(a1, a2, a3);
    }
}

// 32-bit Specific Function - Allah hu akbar, Made with 💖 by IBR
void *__fastcall sub_20340(int a1, int a2, int a3, int a4, int a5, int a6) {
    // Allah hu akbar, Made with 💖 by IBR
    int v6; // r3
    int v8; // r0
    int v9; // t1
    int v10; // r4
    int v11; // r3
    int v12; // r8
    void *v13; // r0
    size_t v14; // r4
    int v15; // r7
    void *result; // r0

    v6 = 2 * (a4 + 1);
    v9 = *(__int16 *)(a1 + v6);
    v8 = a1 + v6;
    v10 = (v9 - *(__int16 *)(v8 - 2)) * a5;
    v11 = (*(__int16 *)(v8 + 2) - v9) * a5;
    v12 = 2 * v10;
    v13 = (void *)(a2 + 2 * v10);
    v14 = 2 * (v11 - v10);
    v15 = 2 * (v12 - v11);
    result = memcpy(v13, (const void *)(a2 + v15), v14);
    if (a6)
        return memcpy((void *)(a3 + v12), (const void *)(a3 + v15), v14);
    return result;
}

// Sub_1A301C Function - Allah hu akbar, Made with 💖 by IBR
int __fastcall sub_1A301C(int a1, int a2, int a3) {
    // Allah hu akbar, Made with 💖 by IBR
    unsigned __int8 v5; 
    char v6; 
    if (v5){
        return 0;
    }
    return 0;
}

// Sub_1BD848 Function - Allah hu akbar, Made with 💖 by IBR
int __fastcall sub_1BD848(int a1, int a2, char a3, const void *a4, int a5, int a6) {
    // Allah hu akbar, Made with 💖 by IBR
    size_t n; // [sp+Ch] [bp-2Ch]
    unsigned __int8 v8; // [sp+13h] [bp-25h]
    unsigned int v9; // [sp+14h] [bp-24h]
    char v11; // [sp+1Fh] [bp-19h]
    char v12; // [sp+27h] [bp-11h]

    v11 = a3 & 1;
    v8 = *(_BYTE *)(a2 + 128);
    *(_BYTE *)(a2 + 96 + v8) = 4;
    *(_BYTE *)(a2 + 96 + v8 + 1) = -16;
    *(_BYTE *)(a2 + 96 + v8 + 2) = 31;
    *(_BYTE *)(a2 + 96 + v8 + 3) = -27;
    if (a4 && a5)
        n = a5 - (_DWORD)a4;
    else
        n = 56;
    *(_DWORD *)(a2 + 272) = n + 180;
    v9 = (a1, a2);
    if (v9) {
        *(_BYTE *)(a2 + 169) = (4 - (v9 & 3)) & 3;
        if (a4 && a5)
            memcpy((void *)(v9 + *(unsigned __int8 *)(a2 + 169)), a4, n);
        else
            memcpy((void *)(v9 + *(unsigned __int8 *)(a2 + 169)), 0, n);
        *(_DWORD *)(a2 + 92) = (v9 + *(unsigned __int8 *)(a2 + 169), n);
        if (a6) {
            *(_DWORD *)(v9 + *(unsigned __int8 *)(a2 + 169) + *(_DWORD *)(a2 + 92)) = a6;
        }
        else if ((v11 & 1) != 0) {
            *(_DWORD *)(v9 + *(unsigned __int8 *)(a2 + 169) + *(_DWORD *)(a2 + 92));
        }
        else {
            *(_DWORD *)(v9 + *(unsigned __int8 *)(a2 + 169) + *(_DWORD *)(a2 + 92));
        }
        *(_DWORD *)(a2 + 96 + v8 + 4) = v9 + *(unsigned __int8 *)(a2 + 169);
        *(_DWORD *)(a2 + 172) = v9 + n + 4;
        *(_BYTE *)(a2 + 168) = (4 - (*(_DWORD *)(a2 + 172) & 3)) & 3;
        *(_BYTE *)(*(_DWORD *)(a2 + 172) + *(unsigned __int8 *)(a2 + 168)) = -1;
        *(_BYTE *)(*(_DWORD *)(a2 + 172) + *(unsigned __int8 *)(a2 + 168) + 1) = 95;
        *(_BYTE *)(*(_DWORD *)(a2 + 172) + *(unsigned __int8 *)(a2 + 168) + 2) = -67;
        *(_BYTE *)(*(_DWORD *)(a2 + 172) + *(unsigned __int8 *)(a2 + 168) + 3) = -24;
        *(_BYTE *)(*(_DWORD *)(a2 + 172) + *(unsigned __int8 *)(a2 + 168) + 4 + *(_DWORD *)(a2 + 132)) = 4;
        *(_BYTE *)(*(_DWORD *)(a2 + 172) + *(unsigned __int8 *)(a2 + 168) + 4 + *(_DWORD *)(a2 + 132) + 1) = -16;
        *(_BYTE *)(*(_DWORD *)(a2 + 172) + *(unsigned __int8 *)(a2 + 168) + 4 + *(_DWORD *)(a2 + 132) + 2) = 31;
        *(_BYTE *)(*(_DWORD *)(a2 + 172) + *(unsigned __int8 *)(a2 + 168) + 4 + *(_DWORD *)(a2 + 132) + 3) = -27;
        *(_DWORD *)(*(_DWORD *)(a2 + 172) + *(unsigned __int8 *)(a2 + 168) + 4 + *(_DWORD *)(a2 + 132) + 4) = *(_DWORD *)(a2 + 68) + *(_DWORD *)(a2 + 132);
        cacheflush(v9, v9 + n + 4, 0);
        v12 = 1;
    }
    else {
        v12 = 0;
    }
    return v12 & 1;
}

// Sub_27E2A8 Function - Allah hu akbar, Made with 💖 by IBR
void __fastcall sub_27E2A8(int a1, int a2, char a3, const void *a4, int a5, int a6) {
    // Allah hu akbar, Made with 💖 by IBR
    _BYTE *v6; // r0

    if ((a3 & 1) != 0 || (*(_BYTE *)(a1 + 32) & 1) == 0) {
        if (a5 > 0 && a4) {
            *(_BYTE *)(a1 + 40) = 1;
            if (a5 <= 12)
                a6 = a5;
            else
                a6 = 12;
            *(_DWORD *)(a1 + 56) = a6;
            memcpy((void *)(a1 + 41), a4, *(_DWORD *)(a1 + 56));
        }
        *(_DWORD *)(a1 + 36) = a2;
        if (*(_DWORD *)(a1 + 36) == 1) {
            *(_DWORD *)(a1 + 72) = 4;
            *(_DWORD *)(a1 + 96) = 4;
            v6 = *(_BYTE **)(a1 + 28);
            *(_BYTE *)(a1 + 60) = *v6;
            *(_BYTE *)(a1 + 61) = v6[1];
            *(_BYTE *)(a1 + 62) = v6[2];
            *(_BYTE *)(a1 + 63) = v6[3];
            *(_BYTE *)(a1 + 76) = *(_BYTE *)(a1 + 60);
            *(_BYTE *)(a1 + 77) = *(_BYTE *)(a1 + 61);
            *(_BYTE *)(a1 + 78) = *(_BYTE *)(a1 + 62);
            *(_BYTE *)(a1 + 79) = *(_BYTE *)(a1 + 63);
            *(_DWORD *)(a1 + 100) = *(_DWORD *)(a1 + 28) + 4;
        }
        *(_BYTE *)(a1 + 5) = 1;
    }
}

// Sub_376820 Function - Allah hu akbar, Made with 💖 by IBR
int __fastcall sub_376820(int a1) {
    // Allah hu akbar, Made with 💖 by IBR
    unsigned __int16 v2; // r0
    int v3; // r0
    int v4; // r0
    __int64 v5; // r0
    _DWORD *v6; // r2

    (a1, (int)"my_game");
    *(_DWORD *)(a1 + 0x80) = 0x64;
    *(_DWORD *)(a1 + 0x84) = 0x32;
    *(_DWORD *)(a1 + 0x88) = 0x42C46666;
    *(_DWORD *)(a1 + 0x8C) = 0x422ECCCD;
    *(_DWORD *)(a1 + 0x90) = 0xCCCCCCCD;
    *(_DWORD *)(a1 + 0x94) = 0x3FF4CCCC;
    *(_BYTE *)(a1 + 0x78) = 0;
    *(_DWORD *)a1;
    *(_DWORD *)(a1 + 8) = 0x40000;
    v2 = lrand48();
    v3 = (a1 + 0x38, 0x40, "%s%04X", "BF01202BF1A31BB4BCC1", v2);
    v4 = (v3);
    if ((v4))
        (a1 + 0x38, "8B57B75C79A3E34E718C", 0x40);
    // qword_4AA024 = a1;
 //   LODWORD(v5) = (0x30);
    v6 = (_DWORD *)v5;
    do {
        *v6 = 0;
        v6[1] = 0xC8;
        v6[2] = 0x42193333;
        v6[3] = 0x41266666;
        v6[4] = 0xCCCCCCCD;
        v6[5] = 0x3FECCCCC;
        v6 += 6;
    }
    while (v6 != (_DWORD *)(v5 + 0x30));
 //   HIDWORD(v5) = 2;
    *(_QWORD *)(a1 + 0x98) = v5;
    *(_DWORD *)(v5 + 0x18) = 0x66;
    *(_DWORD *)v5 = 0x65;
    *(_DWORD *)(a1 + 0xA4) = 0;
    *(_DWORD *)(a1 + 0xA0) = 0;
    *(_DWORD *)(a1 + 0xA8) = 0;
    return a1;
}

// Sub_5BA98 Function (32-bit BGMI) - Allah hu akbar, Made with 💖 by IBR
int __fastcall sub_5BA98(int a1, int a2) {
    // Allah hu akbar, Made with 💖 by IBR
    struct tm *v4; // r0
    int v5; // r5
    void *v7; // [sp+24h] [bp-444h] BYREF
    time_t timer; // [sp+28h] [bp-440h] BYREF
    _DWORD *v9; // [sp+2Ch] [bp-43Ch] BYREF
    char v10[4]; // [sp+30h] [bp-438h] BYREF
    struct timeval tv; // [sp+34h] [bp-434h] BYREF
    char v12[1024]; // [sp+3Ch] [bp-42Ch] BYREF
	
    gettimeofday(&tv, 0);
    time(&timer);
    v4 = localtime(&timer);
    snprintf(
        v12,
        0x400u,
        "[%04d-%02d-%02d_%02d:%02d:%02d.%03d]|%s|%d|",
        v4->tm_year + 1990,
        v4->tm_mon + 1,
        v4->tm_mday,
        v4->tm_hour,
        v4->tm_min,
        v4->tm_sec, tv.tv_usec / 1000, *(const char **)(a1 + 432));
    ((int)&v9, v12);
    (v10, a2);
    ((int)v10, "\n");
    (&v9, v10);
    (v10);
    if ((a1 + 856, (int)v9, *(v9 - 3), 0)
        || ((a1 + 856), (v5 = (a1 + 856, *(_DWORD *)(a1 + 1248))) != 0))
    {
        v5 = 1;
    }
    (&v9);
    (&v7);
    return v5;
}

// 64-bit Ban Fix Hook - Allah hu akbar, Made with 💖 by IBR
typedef __int64 (*OriginalFuncType)(__int64, __int64, char);
OriginalFuncType Original_sub_3721D4 = nullptr;

__int64 __fastcall Hooked_sub_3721D4(__int64 a1, __int64 a2, char a3)  
{  
    // Allah hu akbar, Made with 💖 by IBR
    // Anti-Ban Protection
    if (!a1 || !a2)  
        return 0;  

    // Original Function Call
    __int64 result = Original_sub_3721D4(a1, a2, a3);  

    // Ban Fix - Modify Data
    *(int *)(a1 + 100) = 0;   // Reset Ban Flag
    *(char *)(a1 + 200) = 1;  // Enable Safe Mode
    *(int *)(a1 + 300) = 999; // Fake Legit Data

    return result;  
}

// ▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄
// █ Ban Fix Functions - Allah hu akbar, Made with 💖 by IBR
// ▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀

// Apply all available patches - Allah hu akbar, Made with 💖 by IBR
void applyAllPatches() {
    // Allah hu akbar, Made with 💖 by IBR
    
    // SK Cheat Leak Patches
    PATCH_LIB("libanogs.so", "0x157038","h AF F3 00 80");
    PATCH_LIB("libanogs.so", "0x1CBD30","h AF F3 00 80");
    PATCH_LIB("libanogs.so", "0x1CBE60","h AF F3 00 80");
    PATCH_LIB("libanogs.so", "0x1CAC4C","h AF F3 00 80");
    PATCH_LIB("libanogs.so", "0x1CAF0C","h AF F3 00 80");
    PATCH_LIB("libanogs.so", "0x1CAFAC","h AF F3 00 80");
    PATCH_LIB("libanogs.so", "0x1CAFAC","h AF F3 00 80");
    PATCH_LIB("libanogs.so", "0x1CB09C","h AF F3 00 80");
    PATCH_LIB("libanogs.so", "0x1CB1B8","h AF F3 00 80");
    PATCH_LIB("libanogs.so", "0x1CB2AC","h AF F3 00 80");
    PATCH_LIB("libanogs.so", "0x1CB3A0","h AF F3 00 80");
    PATCH_LIB("libanogs.so", "0x1CB490","h AF F3 00 80");
    PATCH_LIB("libanogs.so", "0x1CB588","h AF F3 00 80");
    PATCH_LIB("libanogs.so", "0x1CB5D8","h AF F3 00 80");
    PATCH_LIB("libanogs.so", "0x1CB628","h AF F3 00 80");
    PATCH_LIB("libanogs.so", "0x1CB678","h AF F3 00 80");
    PATCH_LIB("libanogs.so", "0x1CB6C8","h AF F3 00 80");
    PATCH_LIB("libanogs.so", "0x1CB71C","h AF F3 00 80");
    PATCH_LIB("libanogs.so", "0x1CB76C","h AF F3 00 80");
    PATCH_LIB("libanogs.so", "0x1CB8B0","h AF F3 00 80");
    PATCH_LIB("libanogs.so", "0x1CB9E8","h AF F3 00 80");
    PATCH_LIB("libanogs.so", "0x1CBA64","h AF F3 00 80");
    PATCH_LIB("libanogs.so", "0x1CBAB4","h AF F3 00 80");
    PATCH_LIB("libanogs.so", "0x1CBB04","h AF F3 00 80");
    PATCH_LIB("libanogs.so", "0x1CBBF4","h AF F3 00 80");
    
    // 10 Year Ban Fix - Allah hu akbar, Made with 💖 by IBR
    PATCH_LIB("libanogs.so", "0x2702E8", "00 00 B0 E3 1E FF 2F E1");
    PATCH_LIB("libanogs.so", "0x27F640", "01 20 70 47");
    PATCH_LIB("libanogs.so", "0xF32D8", "01 20 70 47");
    
    // 1 Day Ban Fix - Allah hu akbar, Made with 💖 by IBR
    PATCH_LIB("libanogs.so", "0x366926", "00 00 A0 E3 1E FF 2F E1");
    
    // Memory Tree Fixes - Allah hu akbar, Made with 💖 by IBR
    PATCH_LIB("libanogs.so", "0x164974", "00 00 A0 E3 1E FF 2F E1");
    PATCH_LIB("libanogs.so", "0x1643cc", "00 00 A0 E3 1E FF 2F E1");
    PATCH_LIB("libanogs.so", "0x163ec8", "00 00 A0 E3 1E FF 2F E1");
    PATCH_LIB("libanogs.so", "0x163a24", "00 00 A0 E3 1E FF 2F E1");
    
    // UE4 Patch to Block ANOGS - Allah hu akbar, Made with 💖 by IBR
    PATCH_LIB("libUE4.so", "0x3E68724", "00 00 A0 E3 1E FF 2F E1");
    
    // CrashSight Patches - Allah hu akbar, Made with 💖 by IBR
    PATCH_LIB("libCrashSight.so", "0x2C34C", "C0 03 5F D6");
    PATCH_LIB("libCrashSight.so", "0x38C10", "C0 03 5F D6");
    
    // Anti-Report Patches for 3.7 64-bit - Allah hu akbar, Made with 💖 by IBR
    PATCH_LIB("libanogs.so", "0x6F4A5", "00 00 80 D2 C0 03 5F D6");
    PATCH_LIB("libanogs.so", "0x9561C", "00 00 80 D2 C0 03 5F D6");
    PATCH_LIB("libanogs.so", "0xA42DF", "00 00 80 D2 C0 03 5F D6");
    PATCH_LIB("libanogs.so", "0x48AF3", "00 00 80 D2 C0 03 5F D6");
    
    // Misc Patches - Allah hu akbar, Made with 💖 by IBR
    PATCH_LIB("libanogs.so", "0x1566D8", "00 00 80 D2 C0 03 5F D6");
    PATCH_LIB("libanogs.so", "0x3171EE", "00 00 A0 E3 1E FF 2F E1");
}

// ▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄
// █ Main Entry Point - Allah hu akbar, Made with 💖 by IBR
// ▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀

// Hook Functions Setup - Allah hu akbar, Made with 💖 by IBR
void setupHooks() {
    // Allah hu akbar, Made with 💖 by IBR
    
    // Main Hooks
    HOOK_LIB("libanogs.so", "0xFDAEC", hC16, oC16);
    HOOK_LIB("libanogs.so", "0x3672CC", htermi, otermi);
    HOOK_LIB("libanogs.so", "0x163068", hMemChk, oMemChk);
    HOOK_LIB("libanogs.so", "0x2322B4", htxt_seg_crc, otxt_seg_crc);
    HOOK_LIB("libanogs.so", "0x1DE8E0", hCRCCalculations, oCRCCalculations);
    HOOK_LIB("libanogs.so", "0xB66DC", hanticheatthread, oanticheatthread);
    
    // Misc Hooks
    HOOK_LIB("libanogs.so", "0x155FB4", hsub_1EB7BC, osub_1EB7BC);
    HOOK_LIB("libanogs.so", "0x155274", hsub_1EB7BC, osub_1EB7BC);
    HOOK_LIB("libanogs.so", "0x157FB4", hsub_1EB7BC, osub_1EB7BC);
    HOOK_LIB("libanogs.so", "0x4A2DD4", hsub_1EB7BC, osub_1EB7BC);
    HOOK_LIB("libanogs.so", "0x1D90D0", hsub_1EB7BC, osub_1EB7BC);
    
    // No Origin Hooks
    HOOK_LIB_NO_ORIG("libanogs.so", "0x6F7F4", hstrstr);
    HOOK_LIB_NO_ORIG("libanogs.so", "0x6F7C4", hmemcpy);
    HOOK_LIB_NO_ORIG("libanogs.so", "0x15677C", hook_strlen);
    HOOK_LIB_NO_ORIG("libhdmpve.so", "0x5BA98", sub_5BA98);
    HOOK_LIB_NO_ORIG("libanogs.so", "0x20340", sub_20340);
    HOOK_LIB_NO_ORIG("libanogs.so", "0x27E2A8", sub_27E2A8);
}

// Library Initialization - Allah hu akbar, Made with 💖 by IBR
__attribute__((constructor))
void lib_main() {
    // Allah hu akbar, Made with 💖 by IBR
    LOGI("▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄");
    LOGI("█ Game Mod Tool Initialized           █");
    LOGI("█ Allah hu akbar, Made with 💖 by IBR █");
    LOGI("▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀");
    
    // Create background monitoring thread
    pthread_t ptid;
    pthread_create(&ptid, NULL, anogs_thread, NULL);
    
    // Apply all patches
    applyAllPatches();
    
    // Setup all hooks
    setupHooks();
    
    LOGI("▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄");
    LOGI("█ All hooks and patches applied!      █");
    LOGI("█ Allah hu akbar, Made with 💖 by IBR █");
    LOGI("▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀");
}

// ▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄
// █ Additional Utility Functions - Allah hu akbar, Made with 💖 by IBR
// ▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀

// Iceland mode patch function - Allah hu akbar, Made with 💖 by IBR
void applyIcelandPatches(bool enableIceland) {
    // Allah hu akbar, Made with 💖 by IBR
    if (enableIceland) {
        // Iceland on
        MemoryPatch::createWithHex(OBFUSCATE("libgcloud.so"), 0x62FFC, OBFUSCATE("1E FF 2F E1")).Modify();
        MemoryPatch::createWithHex(OBFUSCATE("libgcloud.so"), 0x3B4A8, OBFUSCATE("1E FF 2F E1")).Modify();
        MemoryPatch::createWithHex(OBFUSCATE("libgcloud.so"), 0x3B4B0, OBFUSCATE("1E FF 2F E1")).Modify();
        MemoryPatch::createWithHex(OBFUSCATE("libgcloud.so"), 0x3097F4, OBFUSCATE("1E FF 2F E1")).Modify();
        MemoryPatch::createWithHex(OBFUSCATE("libgcloud.so"), 0x332CE4, OBFUSCATE("1E FF 2F E1")).Modify();
    } else {
        // Iceland off
        MemoryPatch::createWithHex("libgcloud.so", 0x62FFC, "89 EA 04 04").Modify();
        MemoryPatch::createWithHex("libgcloud.so", 0x3B4A8, "03 C6 8F E2").Modify();
        MemoryPatch::createWithHex("libgcloud.so", 0x3B4B0, "1C F6 BC E5").Modify();
        MemoryPatch::createWithHex(OBFUSCATE("libgcloud.so"), 0x3097F4, OBFUSCATE("7D 2B 2B 56")).Modify();
        MemoryPatch::createWithHex(OBFUSCATE("libgcloud.so"), 0x332CE4, OBFUSCATE("7D 2B 2B 56")).Modify();
    }
}

// X-HIT function - Allah hu akbar, Made with 💖 by IBR
void applyXHitPatches(bool enable) {
    // Allah hu akbar, Made with 💖 by IBR
    if (enable) {
        // Apply X-HIT Patches
        MemoryPatch::createWithHex("libUE4.so", 0x2A0EDFC, "00 00 00 00").Modify();
        MemoryPatch::createWithHex("libUE4.so", 0x2A0622C, "00 00 00 00").Modify();
        MemoryPatch::createWithHex("libUE4.so", 0x2A06224, "00 00 00 00").Modify();
        MemoryPatch::createWithHex("libUE4.so", 0x21857b4, "00 00 00 00").Modify();
    } else {
        // Restore original values if needed
        // Implementation would depend on original values
    }
}

// ▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄
// █ Ban Fix Namespace - Allah hu akbar, Made with 💖 by IBR
// ▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀
namespace BanFixes {
    // Fix for 10-year bans - Allah hu akbar, Made with 💖 by IBR
    void apply10YearFix() {
        // Allah hu akbar, Made with 💖 by IBR
        PATCH_LIB("libanogs.so", "0x7AF2C", "00 20 70 47");
        PATCH_LIB("libanogs.so", "0x163068", "00 00 A0 E3 1E FF 2F E1");
    }
    
    // Fix for 1-day bans - Allah hu akbar, Made with 💖 by IBR
    void apply1DayFix() {
        // Allah hu akbar, Made with 💖 by IBR
        PATCH_LIB("libanogs.so", "0x8E6E4", "00 20 70 47");
        PATCH_LIB("libanogs.so", "0x3672CC", "00 00 80 D2 C0 03 5F D6");
    }
    
    // Fix for offline bans - Allah hu akbar, Made with 💖 by IBR
    void applyOfflineFix() {
        // Allah hu akbar, Made with 💖 by IBR
        PATCH_LIB("libanogs.so", "0x2702E8", "00 00 B0 E3 1E FF 2F E1");
        PATCH_LIB("libanogs.so", "0x27F640", "01 20 70 47");
        PATCH_LIB("libanogs.so", "0xF32D8", "01 20 70 47");
    }
    
    // Fix for structured bans - Allah hu akbar, Made with 💖 by IBR
    void applyStructuredBanFix() {
        // Allah hu akbar, Made with 💖 by IBR
        PATCH_LIB("libanogs.so", "0x164974", "00 00 A0 E3 1E FF 2F E1");
        PATCH_LIB("libanogs.so", "0x1643cc", "00 00 A0 E3 1E FF 2F E1");
        PATCH_LIB("libanogs.so", "0x163ec8", "00 00 A0 E3 1E FF 2F E1");
        PATCH_LIB("libanogs.so", "0x163a24", "00 00 A0 E3 1E FF 2F E1");
    }
    
    // Fix for online bans - Allah hu akbar, Made with 💖 by IBR
    void applyOnlineBanFix() {
        // Allah hu akbar, Made with 💖 by IBR
        HOOK_LIB("libanogs.so", "0x163068", hMemChk, oMemChk);
    }
    
    // Apply all ban fixes - Allah hu akbar, Made with 💖 by IBR
    void applyAllBanFixes() {
        // Allah hu akbar, Made with 💖 by IBR
        apply10YearFix();
        apply1DayFix();
        applyOfflineFix();
        applyStructuredBanFix();
        applyOnlineBanFix();
    }
}

// ▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄
// █ Advanced Anti-Detection Features - Allah hu akbar, Made with 💖 by IBR
// ▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀

// Block all loading of anogs in UE4 - Allah hu akbar, Made with 💖 by IBR
void blockAnogsLoading() {
    // Allah hu akbar, Made with 💖 by IBR
    PATCH_LIB("libUE4.so", "0x3E68724", "00 00 A0 E3 1E FF 2F E1");
}

// Block report system - Allah hu akbar, Made with 💖 by IBR
void blockReportSystem() {
    // Allah hu akbar, Made with 💖 by IBR
    PATCH_LIB("libCrashSight.so", "0x2C34C", "C0 03 5F D6");
    PATCH_LIB("libCrashSight.so", "0x38C10", "C0 03 5F D6");
    
    PATCH_LIB("libanogs.so", "0x6F4A5", "00 00 80 D2 C0 03 5F D6");
    PATCH_LIB("libanogs.so", "0x9561C", "00 00 80 D2 C0 03 5F D6");
    PATCH_LIB("libanogs.so", "0xA42DF", "00 00 80 D2 C0 03 5F D6");
    PATCH_LIB("libanogs.so", "0x48AF3", "00 00 80 D2 C0 03 5F D6");
}

// ▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄
// █ End of Bypass.h - Allah hu akbar, Made with 💖 by IBR
// ▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀ 

my new bypass -> XELAHOT-CHEAT OFFICIAL CHANNEL:
sub_36699A
sub_366926

32 BİT 


libanogs.so

Report block 32 
PATCH_LIB("libangos.so","0x379398", "00 00 A0 E3 1E FF 2F E1");

PATCH_LIB("libangos.so","0x379492", "00 00 A0 E3 1E FF 2F E1");
Gl kr

CR : @SRC_AL_FREE

credit : @SanalOwnerTR

Tdm report 
PATCH_LIB("libangos.so","0x379334", "00 00 A0 E3 1E FF 2F E1");
32 bit

Report block
PATCH_LIB("libangos.so","0x38BB5E", "00 00 A0 E3 1E FF 2F E1");

PATCH_LIB("libangos.so","0x38BA6C", "00 00 A0 E3 1E FF 2F E1");
GL KR 32 BİT

HOOK_LIB_NO_ORIG("libanogs.so", "0x15F4BC", sub_15F4BC);// 

// 30 GÜN FİX 

32 BİT

__aeabi_memcpy4  .plt  0006F26C  0000000C      R  .  .  .  its_Halley.  .  .  .
__aeabi_memcpy  .plt  0006F278  0000000C      R  .  .  .  .  .  .  .
__aeabi_memcpy8  .plt  0006F5B4  0000000C      R  .  .  .  .  .  .  .
memcpy           .plt  0006F7C4  0000000C      R  .  .  .  .  .  T  .                                                                                                                                                                      
~ BGMI ~ 32bit  ~1 day violation~                                                                                                                                                                                                                                                Regards ~ @ec1lz

unsigned __int8 *__fastcall sub_3797BC(int a1, unsigned int a2 , int its_Halley)
{
  unsigned __int8 *result; // r0
  _DWORD *v5; // r0
  unsigned __int8 *v6; // [sp+4h] [bp-Ch] BYREF

  result = (unsigned __int8 *)sub_379248();
  if ( a2 <= 6 )
  {
    result = (unsigned __int8 *)dword_4AA06C;
    if ( !dword_4AA06C[a2] )
    {
      dword_4AA06C[a2] = 1;
      switch ( a2 )
      {
        case 0u:
          result = sub_3923B4(32879);
          break;
        case 1u:
          result = sub_392F48(32892);
          break;
        case 2u:
          result = sub_38E808(32912);
          break;
        case 3u:
          result = sub_38F648(32928);
          break;
        case 4u:
          result = (unsigned __int8 *)&dword_4AA060;
          if ( dword_4AA060 > 2 )
            return result;
          ++dword_4AA060;
          result = sub_39056C(32945);
          break;
        case 5u:
          result = (unsigned __int8 *)&dword_4AA064;
          if ( dword_4AA064 > 2 )
            return result;
          ++dword_4AA064;
          result = sub_391904(32967);
          break;
        case 6u:
          result = (unsigned __int8 *)&dword_4AA068;
          if ( dword_4AA068 > 2 )
            return result;
          ++dword_4AA068;
          result = sub_392C9C(32989);
          break;
        default:
          goto LABEL_16;
      }
      a2 = (unsigned int)result;
      if ( result )
      {
LABEL_16:
        result = (unsigned __int8 *)sub_36699A(a2);
        if ( result )
        {
          result = (unsigned __int8 *)sub_379300((int)"monitor", a2, a1, 1);
          v6 = result;
          if ( result )
          {
            (*(void (__fastcall **)(unsigned __int8 *))(*(_DWORD *)result + 20))(result);
            v5 = (_DWORD *)dword_4AA040;
            if ( !dword_4AA040 )
            {
              v5 = (_DWORD *)((int (__fastcall *)(int))loc_3A9F48)(16);
              dword_4AA040 = (int)v5;
              *v5 = &off_44BA74;
              v5[1] = &off_44BAA0;
              v5[2] = 0;
              v5[3] = 0;
            }
            if ( v5 )
              ++v5;
            return (unsigned __int8 *)sub_379468(v5, (int)&v6);
          }
        }
      }
    }
  }
  return result + its_Halley;
}                                                                                                                                                                                                                                                                      
~ BGMI + GLOBAL ~ 32bit  3.7  ~ MONITOR ~                                                                                                                                                                                                                                                Regards ~ @ec1lz
