#include "circle_link_list.h"

typedef struct {

    clink_list_node_t head;
    size_t size;
    clink_list_node_pt slider;
}clink_list_head_t, *clink_list_head_pt;

/*
 * @brief: 
 * @name:
 * @param:
 * @retval:
*/
err_t clink_list_create(clink_list_pt *_list)
{
    if(NULL == _list)
        return param_err;
    
    clink_list_head_pt list;
    list = (clink_list_head_pt)malloc(sizeof(clink_list_head_t));
    if(NULL == list)
        return mem_err;

    list->head.next = NULL;
    list->size = 0;
    list->slider = NULL;
    *_list = list;
    
    return success;
}

/*
 * @brief: 
 * @name:
 * @param:
 * @retval:
*/
err_t clink_list_destroy(clink_list_pt _list)
{
    if(NULL == _list)
        return param_err;
    clink_list_head_pt list = (clink_list_head_pt)_list;
   
    free(list);
    list = NULL;
    
    return success;
}

/*
 * @brief: 
 * @name:
 * @param:
 * @retval:
*/
err_t clink_list_insert(clink_list_pt _list, size_t _pos, clink_list_node_pt _node)
{
    size_t i = 0;
    clink_list_head_pt list = (clink_list_head_pt)_list;
    clink_list_node_pt current = &(list->head); //first
    clink_list_node_pt last_node = NULL;
    
    if(NULL == _list || NULL == _node)
        return param_err;

    /* Detect pos if is legal */
    if(_pos > list->size)
        _pos = list->size;

    
    for(i = 0; i < _pos; i++)
        current = current->next; //second

    /* Insert node */
    _node->next = current->next;
    current->next = _node;
    
    /* Init slider if first insert */
    if(list->size == 0)
        list->slider = _node;
    
    /* Circle link list inc first */
    list->size++;
    
    /* Reset head node next pointer if insert in pos zero */
    if(current == &list->head) {
        clink_list_get_node(_list, list->size - 1, &last_node);
        last_node->next = current->next;
    }    
    
    return success;

}

/*
 * @brief: between head and first node
 * @name:
 * @param:
 * @retval:
*/
err_t clink_list_push_front(clink_list_pt _list, clink_list_node_pt _node)
{
    return clink_list_insert(_list, 0, _node);
}

/*
 * @brief: between last node and first node
 * @name:
 * @param:
 * @retval:
*/
err_t clink_list_push_back(clink_list_pt _list, clink_list_node_pt _node)
{
    return clink_list_insert(_list, ((clink_list_head_pt)_list)->size, _node);
}

/*
 * @brief:  Delete one node, notice the pos can not equal to size, but inert is ok
 * @name:
 * @param:
 * @retval:
*/
err_t clink_list_delete(clink_list_pt _list, size_t _pos, clink_list_node_pt *_node)
{
    size_t i = 0;
    clink_list_head_pt list = (clink_list_head_pt)_list;
    clink_list_node_pt current = &(list->head);
    clink_list_node_pt del_node = NULL;
    clink_list_node_pt last_node = NULL;
    
    if(NULL == list || NULL == _node || list->size == 0)
        return param_err;
    
    /* Detect pos if is legal */
    if(_pos >= list->size)
        _pos = list->size - 1;
    
    for(i = 0; i < _pos; i++)
        current = current->next;
    
    if(current == &list->head) {
        clink_list_get_node(_list, list->size - 1, &last_node);
    }
    
    /* Delete node */
    del_node = current->next;
    current->next = del_node->next;
    
    list->size--;
    
    /* Reset head node next pointer if insert in pos zero */
    if(NULL != last_node) {
        last_node->next = current->next;
    }
    
    if(list->slider == del_node)
        list->slider = del_node->next;

    if(list->size == 0) {
        list->head.next = NULL;
        list->slider = NULL;
    }
    
    *_node = del_node;

    return success;
    
}

/*
 * @brief: 
 * @name:
 * @param:
 * @retval:
*/
err_t clink_list_pop_front(clink_list_pt _list, clink_list_node_pt *_node)
{
    return clink_list_delete(_list, 0, _node);
}

/*
 * @brief: 
 * @name:
 * @param:
 * @retval:
*/
err_t clink_list_pop_back(clink_list_pt _list, clink_list_node_pt *_node)
{
    return clink_list_delete(_list, ((clink_list_head_pt)_list)->size - 1, _node); 
}

/*
 * @brief: 
 * @name:
 * @param:
 * @retval:
*/
bool clink_list_is_empty(clink_list_pt _list)
{
    if(NULL == _list)
        return true;
    
    return (((clink_list_head_pt)_list)->size == 0 ? true : false);
}

/*
 * @brief: 
 * @name:
 * @param:
 * @retval:
*/
size_t clink_list_get_size(clink_list_pt _list)
{
    if(NULL == _list)
        return 0;
    
    return ((clink_list_head_pt)_list)->size;
}

/*
 * @brief: 
 * @name:
 * @param:
 * @retval:
*/
err_t clink_list_get_node(clink_list_pt _list, size_t _pos, clink_list_node_pt *_node)
{
    size_t i = 0;
    clink_list_head_pt list = (clink_list_head_pt)_list;
    clink_list_node_pt current = &(list->head);
    
    if(NULL == _list || NULL == _node)
        return param_err;

    if(_pos > list->size)
        return false;
    
    for(i = 0; i < _pos; i++)
        current = current->next;

    *_node = current->next;
    
    return success;
}

/*
 * @brief: 
 * @name:
 * @param:
 * @retval:
*/
err_t clink_list_get_pos(clink_list_pt _list, size_t *_pos, clink_list_node_pt _node)
{
    size_t i = 0;
    clink_list_head_pt list = (clink_list_head_pt)_list;
    clink_list_node_pt current = &(list->head);
    clink_list_node_pt del_node = NULL;
    
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

err_t clink_list_slider_reset(clink_list_pt _list)
{
    clink_list_head_pt list = (clink_list_head_pt)_list;
    
    if(NULL == _list)
        return param_err;

    list->slider = list->head.next;

    return success;
}

err_t clink_list_slider_move(clink_list_pt _list)
{
    clink_list_head_pt list = (clink_list_head_pt)_list;
    
    if(NULL == _list)
        return param_err;

    if(list->slider != NULL)
        list->slider = list->slider->next;

    return success;
}


err_t clink_list_get_current_slider_node(clink_list_pt _list, clink_list_node_pt *_node)
{
    clink_list_head_pt list = (clink_list_head_pt)_list;
    
    if(NULL == _list || NULL == _node)
        return param_err;

    *_node = list->slider;

    return success;
}



