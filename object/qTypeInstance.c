/**
 * This file is created by quentinbol.
 * 
 * Copyright (C) 2024 quentinbol. All rights reserved.
 * 
 * Free for personal and commercial use.
 **/

#include "../qUtils.h"
#include "qObject.h"

/**
 * @brief The type instance map structure.
 * 
 * @param type_name The type name.
 * @param instance The instance.
 * 
 */
typedef struct __TypeInstanceMap__ {
    const char *type_name;
    void *instance;
} TypeInstanceMap;

static int temp_int;
static double temp_double;
static float temp_float;
static float *temp_float_ptr;
static char *temp_char_ptr;
static char **temp_char_ptr_ptr;
static int *temp_int_ptr;
static int **temp_int_ptr_ptr;

/**
 * @brief The type instance map array.
 * 
 */
TypeInstanceMap type_instance_map[] = {
    {"double", &temp_double},
    {"int", &temp_int},
    {"float", &temp_float},
    {"float*", &temp_float_ptr},
    {"char*", &temp_char_ptr},
    {"int*", &temp_int_ptr},
    {"int**", &temp_int_ptr_ptr},
    {"char**", &temp_char_ptr_ptr},
    {NULL, NULL}
};

/**
 * @brief Get the fild type object
 * 
 * @param object 
 * @param field_name 
 * @return const char* 
 */
const char* __get_field_type(Object *object, const char *field_name)
{
    return object->class->get_field_type(field_name);
}


/**
 * @brief Get the field offset object
 * 
 * @param type_name 
 * @return void* 
 */
void *__get_field_type_instance(const char* type_name)
{
    for (int i = 0; type_instance_map[i].type_name != NULL; i++) {
        if (__SAFE_STRCMP__(type_instance_map[i].type_name, type_name) == 0) {
            return type_instance_map[i].instance;
        }
    }
    return NULL;
}
