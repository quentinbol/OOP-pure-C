#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "qAlloc.h"
#include "utils/qUtils.h"
#include "object/qObject.h"

typedef struct MyStruct {
    int id;
    char name[50];
} MyStruct;

typedef struct MyInfo {
    int id;
    char *name;
} MyInfo;

typedef struct {
    int x;
    int y;
    float z;
    char *name;
    int *tags;
    Object *info;
} MyPos;

// Field offset maps and offset functions
#define FIELD(type, name) { #name, __OFFSET_OF__(MyPos, name), #type },
FieldOffsetMap my_pose_field_offsets[] = {
    FIELD(int, x)
    FIELD(int, y)
    FIELD(float, z)
    FIELD(char*, name)
    FIELD(int*, tags)
    FIELD(Object*, info)
};
#undef FIELD

size_t __MyPosGetFieldOffset(const char* field_name) {
    for (size_t i = 0; i < sizeof(my_pose_field_offsets) / sizeof(FieldOffsetMap); i++) {
        if (__SAFE_STRCMP__(my_pose_field_offsets[i].field_name, field_name) == 0) {
            return my_pose_field_offsets[i].offset;
        }
    }
    return (size_t)-1;
}

#define FIELD(type, name) { #name, __OFFSET_OF__(MyInfo, name), #type},
FieldOffsetMap my_info_field_offsets[] = {
    FIELD(int, id)
    FIELD(char*, name)
};
#undef FIELD

size_t __MyInfoGetFieldOffset(const char* field_name)
{
    for (size_t i = 0; i < sizeof(my_info_field_offsets) / sizeof(FieldOffsetMap); i++) {
        if (__SAFE_STRCMP__(my_info_field_offsets[i].field_name, field_name) == 0) {
            return my_info_field_offsets[i].offset;
        }
    }
    return (size_t)-1;    
}

const char* __MyPosGetFieldType(const char* field_name) {
    for (size_t i = 0; i < sizeof(my_pose_field_offsets) / sizeof(FieldOffsetMap); i++) {
        if (__SAFE_STRCMP__(my_pose_field_offsets[i].field_name, field_name) == 0) {
            return my_pose_field_offsets[i].type;
        }
    }
    return NULL;
}

const char* __MyInfoGetFieldType(const char* field_name) {
    for (size_t i = 0; i < sizeof(my_info_field_offsets) / sizeof(FieldOffsetMap); i++) {
        if (__SAFE_STRCMP__(my_info_field_offsets[i].field_name, field_name) == 0) {
            return my_info_field_offsets[i].type;
        }
    }
    printf("Field type not found in Info\n");
    return NULL;
}

// Constructor and Destructor functions

void __MyPosDtor(void *obj) {
    MyPos *pos = (MyPos *)obj;
    free(pos->name);
    free(pos->tags);
    printf("Position object deleted successfully\n");
}

void __MyPosCtor(void *obj) {
    MyPos *pos = (MyPos *)obj;
    pos->info = __NEW__(MyInfo);
    printf("%d\n", __GET_FIELD__(pos->info, id));
    pos->x = 0;
    pos->y = 0;
    pos->z = 0.0f;
    pos->name = __SAFE_STRDUP__("Default Name");
    pos->tags = __NEW_ARRAY__(int, 3);
    pos->tags[0] = 1;
    pos->tags[1] = 2;
    pos->tags[2] = 3;
    int idd = 1;
    __SET_FIELD__(pos->info, id, &idd);
    printf("Position object created successfully\n");
}

// Object classes
ObjectClass __MyPosClass = {
    .name = "MyPos",
    .type_name = "MyPos",
    .size = sizeof(MyPos),
    .ctor = &__MyPosCtor,
    .dtor = &__MyPosDtor,
    .get_field_offset = &__MyPosGetFieldOffset,
    .get_field_type = &__MyPosGetFieldType
};

void __MyInfoCtor(void *obj) {
    MyInfo *info = (MyInfo *)obj;
    info->id = 1;
    printf("Info object created successfully\n");
}

ObjectClass __MyInfoClass = {
    .name = "MyInfo",
    .type_name = "MyInfo",
    .size = sizeof(MyInfo),
    .ctor = &__MyInfoCtor,
    .dtor = NULL,
    .get_field_offset = &__MyInfoGetFieldOffset,
    .get_field_type = &__MyInfoGetFieldType
};

// Main function
int main() {
    Object *pos = __NEW__(MyPos);

    if (pos != NULL) {
        printf("Position: (%d, %d), name: %s, z: %f\n", 
            __GET_FIELD__(pos, x), __GET_FIELD__(pos, y), __GET_FIELD__(pos, name), __GET_FIELD__(pos, z));
        /*int new_x = 10;
        int new_y = 20;
        __SET_FIELD__(pos, x, &new_x);
        __SET_FIELD__(pos, y, &new_y);*/
        int new_id = 2;
        __SET_FIELD__(pos, *info->id, &new_id);
        printf("test : %d\n", __GET_FIELD__(pos, *info->id));
        printf("Updated Position: (%d, %d, %f)\n", __GET_FIELD__(pos, x), __GET_FIELD__(pos, y), __GET_FIELD__(pos, z));
        __DELETE__(pos);
    } else {
        printf("Object creation failed\n");
    }

    return 0;
}
