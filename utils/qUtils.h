/**
 * This file is created by quentinbol.
 * 
 * Copyright (C) 2024 quentinbol. All rights reserved.
 * 
 * Free for personal and commercial use.
 **/

#ifndef qutils_h

    #define qutils_h

    #include <stdio.h>

    #ifndef __SAFE_STRCMP__
        #define __SAFE_STRCMP__(str1, str2) \
            ({ \
                int result = 0; \
                const char *_s1 = (str1); \
                const char *_s2 = (str2); \
                if (_s1 == NULL && _s2 == NULL) { \
                    result = 0; \
                } else if (_s1 == NULL) { \
                    result = -1; \
                } else if (_s2 == NULL) { \
                    result = 1; \
                } else { \
                    while (*_s1 && (*_s1 == *_s2)) { \
                        _s1++; \
                        _s2++; \
                    } \
                    result = *(unsigned char *)_s1 - *(unsigned char *)_s2; \
                } \
                result; \
            })
    #endif

    #ifndef __SAFE_STRDUP__
        #define __SAFE_STRDUP__(src) \
            ({ \
                const char* __src = (src); \
                char* __dest = NULL; \
                if (__src != NULL) { \
                    size_t __len = 0; \
                    while (__src[__len] != '\0') { \
                        __len++; \
                    } \
                    __dest = (char*)malloc(__len + 1); \
                    if (__dest != NULL) { \
                        for (size_t __i = 0; __i <= __len; __i++) { \
                            __dest[__i] = __src[__i]; \
                        } \
                    } else { \
                        perror("Failed to allocate memory"); \
                    } \
                } \
                __dest; \
            })
    #endif

    #ifndef __DUPLICATE_DATA__
        #define __DUPLICATE_DATA__(value, data_type) \
            ({ \
                void* dup; \
                if (__SAFE_STRCMP__(data_type, "String") == 0) { \
                    dup = __SAFE_STRDUP__((char*)value); \
                    CHECK_ALLOC(dup); \
                } else if (__SAFE_STRCMP__(data_type, "int") == 0) { \
                    dup = (int*)malloc(sizeof(int)); \
                    CHECK_ALLOC(dup); \
                    *((int*)dup) = *((int*)value); \
                } else { \
                    dup = NULL; \
                } \
                dup; \
            })
    #endif

    #ifndef __COMPARE_DATA__
        #define __COMPARE_DATA__(data1, data2, data_type) \
            ( \
                (__SAFE_STRCMP__(data_type, "String") == 0) ? __SAFE_STRCMP__((char*)(data1), (char*)(data2)) : \
                (__SAFE_STRCMP__(data_type, "int") == 0) ? (*((int*)(data1)) - *((int*)(data2))) : \
                -1 \
            )
    #endif

#endif