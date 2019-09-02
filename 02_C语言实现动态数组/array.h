#ifndef __ARRAY_H__
#define __ARRAY_H__

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <limits.h>
#include <stdbool.h>
#include <string.h>

#define DEBUG_PRF(fmt, args...)	printf("DEBUG:(%s-%d)" fmt "\n", __func__, __LINE__, ##args)

typedef enum {
    fail = -1,
    success = 0,
    param_err,
    mem_err,
    mem_full,
    non_found,
}err_t;

struct array {
    size_t size;
    int32_t cur_len;
    size_t type_size;
    void   *data;
    void (*copy)(void *des, const void *src);
    void (*free)(void *des);
    bool (*match)(const void *des, const void *src);
};

typedef struct array array_t, *array_pt;

#define array_set_copy_method(array, method) (((array)->copy) = (method))
#define array_set_free_method(array, method) (((array)->free) = (method))
#define array_set_match_method(array, method) (((array)->match) = (method))

#define array_get_copy_method(array)    ((array)->copy)
#define array_get_free_method(array)    ((array)->free)
#define array_get_match_method(array)    ((array)->match)


err_t array_create(struct array **_parray, size_t _size, size_t _type_size);
err_t array_insert(struct array *_array, size_t _pos, const void *_value);
err_t array_insert_head(struct array *_array, const void *_value);
err_t array_insert_tail(struct array *_array, const void *_value);

size_t array_get_pos(struct array *_array, const void *_value);
void *array_get_elem(struct array *_array, size_t _pos);

err_t array_modify(struct array *_array, size_t _pos,const void *_value);
err_t array_modify_adv(struct array *_array, size_t _pos,const void *_value);

size_t array_cur_len_get(struct array *_array);
size_t array_size_get(struct array *_array);

err_t array_clear(struct array *_array);
err_t array_delete_index(struct array *_array, size_t _pos);
err_t array_delete_value(struct array *_array, const void *_value);

err_t array_destroy(struct array *_array);

#endif
