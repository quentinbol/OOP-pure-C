/**
 * This file is created by quentinbol.
 * 
 * Copyright (C) 2024 quentinbol. All rights reserved.
 * 
 * Free for personal and commercial use.
 **/

#include "../object/qObject.h"

typedef struct __POS__ {
    int x;
    int y;
    float z;
} MyPos;

#define FIELD(type, name) { #name, __OFFSET_OF__(MyPos, name), #type },
FieldOffsetMap my_pose_field_offsets[] = {
    FIELD(int, x)
    FIELD(int, y)
    FIELD(float, z)
};
#undef FIELD

void get_x(void *data, va_list args);
void set_x(void *data, va_list args);
void get_y(void *data, va_list args);
void set_y(void *data, va_list args);
void get_z(void *data, va_list args);
void set_z(void *data, va_list args);

MethodMap __MyPosMethods[] = {
    { "get_x", get_x },
    { "set_x", set_x },
    { "get_y", get_y },
    { "set_y", set_y },
    { "get_z", get_z },
    { "set_z", set_z },
    { NULL, NULL }
};

size_t __MyPosGetFieldOffset(const char* field_name)
{
    return __GetFieldOffset(field_name, my_pose_field_offsets);
}

const char* __MyPosGetFieldType(const char* field_name) 
{
    return __GetFieldType(field_name, my_pose_field_offsets);
}

void __MyPosDtor(void *obj) 
{
    MyPos *pos = (MyPos *)obj;
    pos->x = 0;
    pos->y = 0;
    pos->z = 0.0f;
    printf("Position object deleted successfully\n");
}

void __MyPosCtor(void *obj) 
{
    MyPos *pos = (MyPos *)obj;
    pos->x = 0;
    pos->y = 0;
    pos->z = 0.0f;
    printf("Position object created successfully\n");
}

ObjectClass __MyPosClass = {
    .name = "MyPos",
    .type_name = "MyPos",
    .size = sizeof(MyPos),
    .ctor = &__MyPosCtor,
    .dtor = &__MyPosDtor,
    .get_field_offset = &__MyPosGetFieldOffset,
    .get_field_type = &__MyPosGetFieldType
};

void get_x(void *data, va_list args)
{
    MyPos *pos = (MyPos *)data;
    int *result = va_arg(args, int*);
    *result = pos->x;
}

void set_x(void *data, va_list args)
{
    MyPos *pos = (MyPos *)data;
    int x = va_arg(args, int);
    printf("Setting x to %d\n", x);
    pos->x = x;
}

void get_y(void *data, va_list args)
{
    MyPos *pos = (MyPos *)data;
    int *result = va_arg(args, int*);
    *result = pos->y;
}

void set_y(void *data, va_list args)
{
    MyPos *pos = (MyPos *)data;
    int y = va_arg(args, int);
    printf("Setting y to %d\n", y);
    pos->y = y;
}

void get_z(void *data, va_list args)
{
    MyPos *pos = (MyPos *)data;
    float *result = va_arg(args, float*);
    *result = pos->z;
}

void set_z(void *data, va_list args)
{
    MyPos *pos = (MyPos *)data;
    float z = va_arg(args, double);
    printf("Setting z to %f\n", z);
    pos->z = z;
}
