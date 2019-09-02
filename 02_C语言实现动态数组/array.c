#include "array.h"

static void hang(void)
{
    printf("program hang at :%s-%d",__func__, __LINE__);
    while(1);
}

/*
 * @brief: create an array
 * @name:
 * @param:
 * @retval:
*/
err_t array_create(struct array **_parray, size_t _size, size_t _type_size)
{
    struct array *array_new = NULL;
    void *pdata = NULL;
    
    if(NULL == _parray || 0 == _size || 0 == _type_size )
        return param_err;
    
    /* Create struct array and data eara*/
    array_new = (struct array *)malloc(sizeof(struct array) + _size * _type_size);
    if(NULL == array_new)
        return mem_err;

    /* member init */
    array_new->size = _size;
    array_new->cur_len = 0;
    array_new->type_size = _type_size;
    array_new->data = array_new + 1;
    array_new->copy = NULL;
    array_new->free = NULL;
    array_new->match = NULL;

    *_parray = array_new;
    return success;    
}

/*
 * @brief: 
 * @name:
 * @param:
 * @retval:
*/
err_t array_insert(struct array *_array, size_t _pos, const void *_value)
{
    size_t i = 0;
    void *pnew = NULL;
    void *pold = NULL;
    if(NULL == _array)
        return param_err;

    /* Detect if there is valid space for new node */
    if(_array->cur_len == _array->size)
        return mem_full;
	
	/* Detect pos if is legal */
	if(_pos >= _array->size || _pos > _array->size)
		_pos = _array->cur_len;
	
    /* Move node if need */
    for(i = _array->cur_len; i < _pos; i--) {
        pnew = _array->data + i * _array->type_size;
        pold = _array->data + (i - 1) * _array->type_size;

        if(NULL != _array->copy) {
            _array->copy(pnew, pold);
        }else {
            memcpy(pnew, pold, _array->type_size);
        }
    }

    /* Insert new node */
    if(NULL != _array->copy) {
        _array->copy(_array->data + _pos * _array->type_size, _value);
    }else {
        memcpy(_array->data + _pos * _array->type_size, _value, _array->type_size);
    }

    _array->cur_len++;

    return success;
}


/*
 * @brief: 
 * @name:
 * @param:
 * @retval:
*/
err_t array_insert_head(struct array *_array, const void *_value)
{
    return array_insert(_array, 0, _value);
}

/*
 * @brief: 
 * @name:
 * @param:
 * @retval:
*/
err_t array_insert_tail(struct array *_array, const void *_value)
{
    return array_insert(_array, _array->cur_len, _value);
}


size_t array_get_pos(struct array *_array, const void *_value)
{
    size_t i = 0;
    
    if(_array == NULL || _value == NULL)
        hang();

    for(i = 0; i < _array->cur_len; i++) {
        if(NULL != _array->match){
            if(true == _array->match(_array->data + i * _array->type_size, _value))
                return i;
        }else {
            if(0 == memcmp(_array->data + i * _array->type_size, _value, _array->type_size))
                return i;
        }        
    }

    return INT_MAX;
}
void* array_get_elem(struct array *_array, size_t _pos)
{
    if(NULL == _array || _pos >= _array->cur_len)
        return NULL;
    
    return _array->data + _pos * _array->type_size;
}


err_t array_modify(struct array *_array, size_t _pos,const void *_value)
{
    if(NULL == _array || _pos > _array->size - 1)
        return param_err;

    if(NULL != _array->copy) {
        _array->copy(_array->data + _pos * _array->type_size, _value);
    }else {
        memcpy(_array->data + _pos * _array->type_size, _value, _array->type_size);
    }
    return success;
}

err_t array_modify_adv(struct array *_array, size_t _pos,const void *_value)
{
    if(NULL == _array || _pos > _array->size - 1)
        return param_err;

    if(NULL != _array->copy) {
        if(NULL != _array->free)
            _array->free(_array->data + _pos * _array->type_size);
        _array->copy(_array->data + _pos * _array->type_size, _value);
    }else {
        memcpy(_array->data + _pos * _array->type_size, _value, _array->type_size);
    }
    return success;
}

size_t array_cur_len_get(struct array *_array)
{
    if(NULL == _array)
        hang();
    return _array->cur_len;
}

size_t array_size_get(struct array *_array)
{
    if(NULL == _array)
        hang();
    return _array->size;
}

err_t array_clear(struct array *_array)
{
    size_t i;
    if(NULL == _array)
        return param_err;
    
    for(i = 0; i <_array->cur_len; i++)
    {
        if(NULL == _array->free)
            _array->free(_array->data + i * _array->type_size);
    }

    _array->cur_len = 0;
}

err_t array_delete_index(struct array *_array, size_t _pos)
{
    size_t i = 0;
    void *pold = NULL;
    void *pnew = NULL;
    
    if(NULL == _array || _pos > _array->cur_len - 1)
        return param_err;

    if(NULL != _array->free){
        _array->free(_array->data + _pos * _array->type_size);
    }

    for(i = _pos; i < _array->cur_len - 1; i++) {
        pold = _array->data + i * _array->type_size;
        pnew = _array->data + (i + 1) * _array->type_size;

        if(NULL != _array->copy) {
            _array->copy(pold, pnew);
        }else {
            memcpy(pold, pnew, _array->type_size);
        }
    }

    _array->cur_len--;
    return success;
    
}
err_t array_delete_value(struct array *_array, const void *_value)
{
    size_t pos = 0;
    if(NULL == _array)
        return param_err;

    pos = array_get_pos(_array, _value);
    if(pos == INT_MAX)
        return non_found;

    return array_delete_index(_array, pos);
}

err_t array_destroy(struct array *_array)
{
    size_t i;
    if(NULL == _array)
        return param_err;
    
    for(i = 0; i <_array->cur_len; i++) {
        if(NULL == _array->free)
            _array->free(_array->data + i * _array->type_size);
    }
    
    free(_array);
    _array = NULL;
    
    return success;
}



