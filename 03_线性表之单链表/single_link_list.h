#ifndef __SINGLE_LINK_LIST_H__
#define __SINGLE_LINK_LIST_H__

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

struct slink_list_node {

    struct slink_list_node *next;
};

typedef void slink_list_t;
typedef void *slink_list_pt;
typedef struct slink_list_node slink_list_node_t, *slink_list_node_pt;


err_t slink_list_create(slink_list_pt *_list);
err_t slink_list_destroy(slink_list_pt _list);
err_t slink_list_clear(slink_list_pt _list);

/* add */
err_t slink_list_insert(slink_list_pt _list, size_t _pos, slink_list_node_pt _node);
err_t slink_list_push_front(slink_list_pt _list, slink_list_node_pt _node);
err_t slink_list_push_back(slink_list_pt _list, slink_list_node_pt _node);

/* delete */
err_t slink_list_delete(slink_list_pt _list, size_t _pos, slink_list_node_pt *_node);
err_t slink_list_pop_front(slink_list_pt _list, slink_list_node_pt *_node);
err_t slink_list_pop_back(slink_list_pt _list, slink_list_node_pt *_node);

/*query*/
bool slink_list_is_empty(slink_list_pt _list);
size_t slink_list_get_size(slink_list_pt _list);
err_t slink_list_get_node(slink_list_pt _list, size_t _pos, slink_list_node_pt *_node);
err_t slink_list_get_pos(slink_list_pt _list, size_t *_pos, slink_list_node_pt _node);


#endif


