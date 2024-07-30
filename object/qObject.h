/**
 * This file is created by quentinbol.
 * 
 * Copyright (C) 2024 quentinbol. All rights reserved.
 * 
 * Free for personal and commercial use.
 **/

#include <stdlib.h>
#include <stdio.h>

#ifndef qObject_h
    #define qObject_h

    #include <stdio.h>
    #include <stdarg.h>
    #include "../utils/qUtils.h"

    #ifndef __PTR_F0__
        typedef void (*ctor_t)(void *null__ptr); //-> ctor_t function pointer use as a constructor
        typedef void (*dtor_t)(void *null__ptr); // -> dtor_t function pointer use as a destructor
        typedef size_t (*field_offset_t)(const char* field_name); // -> field_offset_t function pointer use to get the offset of a field
        typedef const char* (*field_type_t)(const char* field_name); // -> field_type_t function pointer use to get the type of a field
    #endif

    #ifndef __OBJECT_CLASS__
        /**
         * @brief The object class structure.
         * 
         * @param name The name of the class.
         * @param type_name The type name of the class.
         * @param size The size of the class.
         * @param ctor The constructor of the class.
         * @param dtor The destructor of the class.
         * @param get_field_offset The function to get the field offset.
         * @param get_field_type The function to get the field type.
         * 
         */
        typedef struct __OBJECT_CLASS__ {
            const char *name;
            const char *type_name;
            size_t size;
            ctor_t ctor;
            dtor_t dtor;
            field_offset_t get_field_offset;
            field_type_t get_field_type;
        } ObjectClass;
    #endif

    #ifndef __METHOD__
        typedef void (*method_func_t)(void *data, va_list args);
    #endif

    #ifndef __METHOD_MAP__
        typedef struct {
            const char *method_name;
            method_func_t method;
        } MethodMap;
    #endif

    #ifndef __OBJECT__
        /**
         * @brief The object structure.
         * 
         * @param class The class of the object.
         * @param data The data of the object -> cast to a structure (instance of the class).
         * 
         */
        typedef struct __OBJECT__ {
            ObjectClass *class;
            void *data;
            MethodMap *methods;
            /**
             * @brief function pointer to call method of the object.
             * 
             * @param obj The object that you want to call the method.
             * @param method_name The name of the method that you want to call.
             * @param ... The arguments that you want to pass to the method.
             * 
             */
            void (*callMethod)(struct __OBJECT__ *obj, const char *method_name, ...);
        } Object;
    #endif

    void callMethod(Object *obj, const char *method_name, ...);

    #ifndef __FIELD_OFFSET_MAP__
        /**
         * @brief The field offset map structure.
         * 
         * @param field_name The name of the field.
         * @param offset The offset of the field.
         * @param type The type of the field.
         * 
         */
        typedef struct FieldOffsetMap {
            const char *field_name;
            size_t offset;
            const char *type;
        } FieldOffsetMap;
    #endif

    #ifndef __NEW__
    /**
     * @brief Macro to create a new object.
     * 
     * @param type The type of the object.
     * 
     */
        
#define __NEW__(type) ({ \
            extern ObjectClass __##type##Class; \
            Object *(obj) = (Object *)malloc(sizeof(Object)); \
            if (obj != NULL) { \
                obj->class = &(__##type##Class); \
                obj->data = malloc(__##type##Class.size); \
                obj->methods = __##type##Methods; \
                obj->callMethod = &callMethod; \
                if (obj->data != NULL) { \
                    __##type##Class.ctor(obj->data); \
                } else { \
                    free(obj); \
                    obj = NULL; \
                } \
            } \
            obj; \
        })
    #endif

    #ifndef __DELETE__
        #define __DELETE__(instance) do { \
                if ((instance) != NULL) { \
                    (instance)->class->dtor((instance)->data); \
                    free((instance)->data); \
                    free(instance); \
                    instance = NULL; \
                } \
            } while (0)
    #endif

    #ifndef __FIELD_TYPE__
        /**
         * @brief Macro to get the field type of the object.
         * 
         * @param object The object that you want to get the field type.
         * @param field The field that you want to get the type.
         * 
         */
        #define FIELD_TYPE(object, field) __get_field_type(object, #field)
    #endif

    #ifndef __OFFSET_OF__
    /**
     * @brief Macro to get the byte offset of a field within a structure.
     * 
     * This macro calculates the offset (in bytes) of a specific field within a given structure. 
     * The offset is calculated from the beginning of the structure to the start of the specified field.
     * 
     * @param type The structure type containing the field.
     * @param field The field within the structure whose offset is to be determined.
     * 
     * @return The byte offset of the field within the structure.
     * 
     * @note This macro uses pointer arithmetic to determine the offset and casts it to a `size_t`.
     *       It is typically used for low-level operations such as memory management, serialization, or 
     *       interfacing with hardware where precise knowledge of field positions is required.
     *       In this context here are the different use cases:
     *       1 : Memory access
     *       2 : Manipulating field
     *       3 : Macro implementation
     * 
     */
        #define __OFFSET_OF__(type, field) \
            ((size_t) (&(((type *)0)->field)))
    #endif

    #ifndef FieldValue
    /**
     * @brief Union to store the field value of the object.
     * 
     */
        typedef union {
            int int_val;
            float float_val;
            double double_val;
            char *str_val;
            void *ptr_val;
            char **str_array;
            int **int_array;
            float **float_array;
            double **double_array;
            void **ptr_array;
        } FieldValue;
    #endif

    #ifndef __GET_FIELD_TYPE_OF__
    /**
     * @brief Macro to get the field type of the object.
     * 
     * @param object The object that you want to get the field type.
     * @param field The field that you want to get the type.
     * 
     */
        #define __GET_FIELD_TYPE__(object, field) _Generic(&(((typeof(object->data))0)->field), \
            int*: int, \
            float*: float, \
            double*: double, \
            char**: char*, \
            void**: void*, \
            char***: char**, \
            int***: int**, \
            default: void*)
    #endif

    #ifndef __GET_FIELD__
        /**
         * @brief Macro to get the field value of the object.
         * 
         * @param object The object that you want to get the field value.
         * @param field The field that you want to get the value.
         * 
         */
        #define __GET_FIELD__(object, field) \
            ({ \
                size_t offset = (object)->class->get_field_offset(#field); \
                void *field_ptr = (offset != (size_t)-1) ? (char *)(object)->data + offset : NULL; \
                const char *field_type = FIELD_TYPE(object, field); \
                typeof(__get_field_type_instance(field_type)) field_value; \
                if (field_ptr) { \
                    field_value = (*(typeof(field_value) *)field_ptr); \
                } else { \
                    field_value = (typeof(field_value)){0}; \
                } \
                field_value; \
            })
    #endif

    #ifndef __SET_FIELD__
        /**
         * @brief Macro to set the field value of the object.
         * 
         * @param object The object that you want to set the field value.
         * @param field The field that you want to set the value.
         * @param value The value that you want to set.
         * 
         */
        #define __SET_FIELD__(object, field, value) \
            ({ \
                size_t offset = (object)->class->get_field_offset(#field); \
                if (offset != (size_t)-1) { \
                    __assign_field_value((char *)(object)->data + offset, FIELD_TYPE(object, field), value); \
                } \
            })
    #endif

    #define GET_MACRO(_1,_2,_3,NAME,...) NAME
    #ifndef __NEW__
        #define __NEW__(...) \
            GET_MACRO(__VA_ARGS__, __NEW_WITH_ARGS, __NEW_NO_ARGS) \
                (__VA_ARGS__)
    #endif


    #ifndef __NEW_WITH_ARGS__
        /**
         * @brief Macro to create a new object based on the type with arguments.
         * 
         * @param _instance The class that you want to create an object from.
         * @param ... The arguments that you want to pass to the constructor.
         * 
         */
        #define __NEW_WITH_ARGS(_instance, ...) \
            ({ \
                _instance* obj = (_instance*)malloc(sizeof(_instance)); \
                if (obj != NULL) { \
                    init_##_instance(obj, __VA_ARGS__); \
                } \
                obj; \
            })
    #endif

    #ifndef __NEW__
        /**
         * @brief Macro to create a new object based on the type without arguments.
         * 
         * @param _instance The class that you want to create an object from.
         * 
         */
        #define __NEW_NO_ARGS(_instance) \
            ({ \
                _instance* obj = (_instance*)malloc(sizeof(_instance)); \
                if (obj != NULL) { \
                    init_##_instance##_default(obj); \
                } \
                obj; \
            })
    #endif

    void __assign_field_value(void *field_ptr, const char *type_name, void *value_ptr);
    void *__get_field_type_instance(const char* type_name);
    const char* __get_field_type(Object *object, const char *field_name);
    const char* __GetFieldType(const char* field_name, FieldOffsetMap *offsetMap);
    size_t __GetFieldOffset(const char* field_name, FieldOffsetMap *offsetMap);

#endif // qObject_h
    