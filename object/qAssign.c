/**
 * This file is created by quentinbol.
 * 
 * Copyright (C) 2024 quentinbol. All rights reserved.
 * 
 * Free for personal and commercial use.
 **/

#include "../utils/qUtils.h"

/**
 * @brief The type instance map structure.
 * 
 */
typedef void (*assign_func_t)(void *field_ptr, void *value_ptr);


/**
 * @brief Assign an integer value to a field.
 * 
 * @param field_ptr 
 * @param value_ptr 
 */
void assign_int(void *field_ptr, void *value_ptr) {
    *(int *)field_ptr = *(int *)value_ptr;
}

/**
 * @brief Assign a float value to a field.
 * 
 * @param field_ptr 
 * @param value_ptr 
 */
void assign_float(void *field_ptr, void *value_ptr) {
    *(float *)field_ptr = *(float *)value_ptr;
}

/**
 * @brief Assign a char pointer value to a field.
 * 
 * @param field_ptr 
 * @param value_ptr 
 */
void assign_char_ptr(void *field_ptr, void *value_ptr) {
    *(char **)field_ptr = *(char **)value_ptr;
}

/**
 * @brief Assign an integer pointer value to a field.
 * 
 * @param field_ptr 
 * @param value_ptr 
 */
void assign_int_ptr(void *field_ptr, void *value_ptr) {
    *(int **)field_ptr = *(int **)value_ptr;
}

/**
 * @brief The type assign map structure.
 * 
 */
typedef struct __TypeAssignMap__ {
    const char *type_name;
    assign_func_t assign_func;
} TypeAssignMap;

/**
 * @brief The type assign map array.
 * 
 */
TypeAssignMap type_assign_map[] = {
    {"int", assign_int},
    {"float", assign_float},
    {"char*", assign_char_ptr},
    {"int*", assign_int_ptr},
    {NULL, NULL}
};

/**
 * @brief Assign a value to a field.
 * 
 * @param field_ptr 
 * @param type_name 
 * @param value_ptr 
 */
void __assign_field_value(void *field_ptr, const char *type_name, void *value_ptr) {
    for (int i = 0; type_assign_map[i].type_name != NULL; i++) {
        if (__SAFE_STRCMP__(type_assign_map[i].type_name, type_name) == 0) {
            type_assign_map[i].assign_func(field_ptr, value_ptr);
            return;
        }
    }
    printf("Invalid type\n");
}