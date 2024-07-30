/**
 * This file is created by quentinbol.
 * 
 * Copyright (C) 2024 quentinbol. All rights reserved.
 * 
 * Free for personal and commercial use.
 **/

#include "qObject.h"

void callMethod(Object *obj, const char *method_name, ...)
{
    if (obj == NULL) {
        return;
    }

    va_list args;
    va_start(args, method_name);
    for (int i = 0; obj->methods[i].method_name != NULL; i++) {
        if (__SAFE_STRCMP__(obj->methods[i].method_name, method_name) == 0) {
            obj->methods[i].method(obj->data, args);
            break;
        }
    }
    va_end(args);
}

size_t __GetFieldOffset(const char* field_name, FieldOffsetMap *offsetMap)
{
    for (size_t i = 0; i < sizeof(offsetMap) / sizeof(FieldOffsetMap); i++) {
        if (__SAFE_STRCMP__(offsetMap[i].field_name, field_name) == 0) {
            return offsetMap[i].offset;
        }
    }
    return (size_t)-1;
}

const char* __GetFieldType(const char* field_name, FieldOffsetMap *offsetMap) 
{
    for (size_t i = 0; i < sizeof(offsetMap) / sizeof(FieldOffsetMap); i++) {
        if (__SAFE_STRCMP__(offsetMap[i].field_name, field_name) == 0) {
            return offsetMap[i].type;
        }
    }
    return NULL;
}