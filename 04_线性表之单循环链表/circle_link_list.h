#ifndef __CIRCLE_LINK_LIST_H__
#define __CIRCLE_LINK_LIST_H__

#include "stdio.h"
#include "stdbool.h"
#include "stdint.h"
#include "stddef.h"
#include "stdlib.h"
#include "string.h"
#include "assert.h"

#define DEBUG_PRF(fmt, args...)	printf("DEBUG:(%s-%d)" fmt "\n", __func__, __LINE__, ##args)


typedef enum
{
    fail = -1,
    success = 0,
    param_err,
    mem_err,
    key_conflict,
    non_exist,
    unknew,
}err_t;

struct clink_list_node {

    struct clink_list_node *next;
};

typedef void clink_list_t;
typedef void *clink_list_pt;
typedef struct clink_list_node clink_list_node_t, *clink_list_node_pt;


err_t clink_list_create(clink_list_pt *_list);
err_t clink_list_destroy(clink_list_pt _list);
err_t clink_list_clear(clink_list_pt _list);

/* add */
err_t clink_list_insert(clink_list_pt _list, size_t _pos, clink_list_node_pt _node);
err_t clink_list_push_front(clink_list_pt _list, clink_list_node_pt _node);
err_t clink_list_push_back(clink_list_pt _list, clink_list_node_pt _node);

/* delete */
err_t clink_list_delete(clink_list_pt _list, size_t _pos, clink_list_node_pt *_node);
err_t clink_list_pop_front(clink_list_pt _list, clink_list_node_pt *_node);
err_t clink_list_pop_back(clink_list_pt _list, clink_list_node_pt *_node);

/*query*/
bool clink_list_is_empty(clink_list_pt _list);
size_t clink_list_get_size(clink_list_pt _list);
err_t clink_list_get_node(clink_list_pt _list, size_t _pos, clink_list_node_pt *_node);
err_t clink_list_get_pos(clink_list_pt _list, size_t *_pos, clink_list_node_pt _node);

err_t clink_list_slider_move(clink_list_pt _list);
err_t clink_list_get_current_slider_node(clink_list_pt _list, clink_list_node_pt *_node);
err_t clink_list_slider_reset(clink_list_pt _list);

#endif


