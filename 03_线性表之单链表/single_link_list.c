#include "single_link_list.h"

typedef struct {

    slink_list_node_t head;
    size_t size;

}slink_list_head_t, *slink_list_head_pt;

err_t slink_list_create(slink_list_pt *_list)
{
    if(NULL == _list)
        return param_err;
    
    slink_list_head_pt list;
    list = (slink_list_head_pt)malloc(sizeof(slink_list_head_t));
    if(NULL == list)
        return mem_err;

    list->head.next = NULL;
    list->size = 0;
    
    *_list = list;
    
    return success;
}

err_t slink_list_destroy(slink_list_pt _list)
{
    if(NULL == _list)
        return param_err;
    slink_list_head_pt list = (slink_list_head_pt)_list;
   
    free(list);
    list = NULL;
    
    return success;
}

err_t slink_list_insert(slink_list_pt _list, size_t _pos, slink_list_node_pt _node)
{
    size_t i = 0;
    slink_list_head_pt list = (slink_list_head_pt)_list;
    slink_list_node_pt current = &(list->head);
    
    if(NULL == _list || NULL == _node)
        return param_err;
    
    if(_pos > list->size)
        _pos = list->size;

    for(i = 0; i < _pos; i++)
        current = current->next;

    _node->next = current->next;
    current->next = _node;
    
    list->size++;
    
    return success;

}

err_t slink_list_push_front(slink_list_pt _list, slink_list_node_pt _node)
{
    return slink_list_insert(_list, 0, _node);
}

err_t slink_list_push_back(slink_list_pt _list, slink_list_node_pt _node)
{
    return slink_list_insert(_list, ((slink_list_head_pt)_list)->size, _node);
}

err_t slink_list_delete(slink_list_pt _list, size_t _pos, slink_list_node_pt *_node)
{
    size_t i = 0;
    slink_list_head_pt list = (slink_list_head_pt)_list;
    slink_list_node_pt current = &(list->head);
    slink_list_node_pt del_node = NULL;
    
    if(NULL == _list || NULL == _node)
        return param_err;

    if(_pos > list->size)
        _pos = list->size;
    
    for(i = 0; i < _pos; i++)
        current = current->next;

    del_node = current->next;
    current->next = del_node->next;
    
    list->size--;
    
    *_node = del_node;

    return success;
    
}


err_t slink_list_pop_front(slink_list_pt _list, slink_list_node_pt *_node)
{
    return slink_list_delete(_list, 0, _node);
}

err_t slink_list_pop_back(slink_list_pt _list, slink_list_node_pt *_node)
{
    return slink_list_delete(_list, ((slink_list_head_pt)_list)->size - 1, _node);
}


bool slink_list_is_empty(slink_list_pt _list)
{
    if(NULL == _list)
        return true;
    
    return (((slink_list_head_pt)_list)->size == 0 ? true : false);
}

size_t slink_list_get_size(slink_list_pt _list)
{
    if(NULL == _list)
        return 0;
    
    return ((slink_list_head_pt)_list)->size;
}

err_t slink_list_get_node(slink_list_pt _list, size_t _pos, slink_list_node_pt *_node)
{
    size_t i = 0;
    slink_list_head_pt list = (slink_list_head_pt)_list;
    slink_list_node_pt current = &(list->head);
    
    if(NULL == _list || NULL == _node)
        return param_err;

    if(_pos > list->size)
        return false;
    
    for(i = 0; i < _pos; i++)
        current = current->next;

    *_node = current->next;
    
    return success;
}


err_t slink_list_get_pos(slink_list_pt _list, size_t *_pos, slink_list_node_pt _node)
{
    size_t i = 0;
    slink_list_head_pt list = (slink_list_head_pt)_list;
    slink_list_node_pt current = &(list->head);
    slink_list_node_pt del_node = NULL;
    
    if(NULL == _list || NULL == _node || NULL == _pos)
        return param_err;

    for(i = 0; i < list->size; i++) {
        if(current->next == _node) {
            *_pos = i;
            break;
        }
    }

    return success;
}

