/**
 * This file is created by quentinbol.
 * 
 * Copyright (C) 2024 quentinbol. All rights reserved.
 * 
 * Free for personal and commercial use.
 **/

#ifndef qalloc_h
    
    #define qalloc_h

    #include <stdlib.h>

    #ifndef CHECK_ALLOC
    /**
     * @brief Check if the memory allocation was successful.
     * 
     * @param _ptr_ The pointer that you want to check.
     * 
     */
        #define CHECK_ALLOC(_ptr_) \
            do { \
                if (!(_ptr_)) { \
                    fprintf(stderr, "Memory allocation failed in %s at line %d\n", __FILE__, __LINE__); \
                    exit(EXIT_FAILURE); \
                } \
            } while (0)
    #endif

    #ifndef __NEW_ARRAY__
    /**
     * @brief Macro to create a new array based on the type and size.
     * 
     * @param type The type of the array.
     * @param size The size of the array.
     * 
     */
        #define __NEW_ARRAY__(type, size) \
            ({ \
                type* _ptr_ = (type*)malloc(sizeof(type) * (size)); \
                CHECK_ALLOC(_ptr_); \
                _ptr_; \
            })
    #endif

    #ifndef __NEW_ZEROED__
    /**
     * @brief Macro to create a new object based on the type and zeroed.
     * 
     * @param _instance The class that you want to create an object from.
     * 
     */
        #define __NEW_ZEROED__(_instance) \
            ({ \
                _instance* _ptr_ = (_instance*)calloc(1, sizeof(_instance)); \
                CHECK_ALLOC(_ptr_); \
                _ptr_; \
            })
    #endif

    #ifndef __NEW_ZEROED_ARRAY__
    /**
     * @brief Macro to create a new array based on the type and size and zeroed.
     * 
     * @param type The type of the array.
     * @param size The size of the array.
     * 
     */
        #define __NEW_ZEROED_ARRAY__(type, size) \
            ({ \
                type* _ptr_ = (type*)calloc((size), sizeof(type)); \
                CHECK_ALLOC(_ptr_); \
                _ptr_; \
            })
    #endif

    #ifndef __FREE__
    /**
     * @brief Macro to free the memory of the pointer.
     * 
     * @param _ptr_ The pointer that you want to free.
     * 
     */
        #define __FREE__(_ptr_) \
            do { \
                free(_ptr_); \
                _ptr_ = NULL; \
            } while (0)
    #endif

    #ifndef __FREE_ARRAY__
    /**
     * @brief Macro to free the memory of the array.
     * 
     * @param _ptr_ The array that you want to free.
     * 
     */
        #define __FREE_ARRAY__(_ptr_) \
            do { \
                for (int i = 0; i < sizeof(_ptr_) / sizeof(_ptr_[0]); i++) { \
                    free(_ptr_[i]); \
                } \
            } while (0)
    #endif
#endif // qalloc_h