#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <limits.h>
#include <math.h>

#define DEBUG_PRF(fmt, args...)	printf("DEBUG:(%s-%d)" fmt "\n", __func__, __LINE__, ##args)
#define HASH_SHIFT  4
#define HASH_SIZE   (1 << HASH_SHIFT)
#define HASH_MASK   (HASH_SIZE - 1)

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

struct elem_type{

    int32_t key;
    int32_t value;
};
typedef struct elem_type *elem_type_pt;


struct hash_node{
    
    struct elem_type elem;
    struct hash_node *next;
};
typedef struct hash_node *hash_node_pt;


struct hash_table{

    size_t size;
    struct hash_node *table;
};
typedef struct hash_table *hash_table_pt;

/*
 * @name:  hash_function
 * @brief:
 * @param:
 * @retval:
*/
size_t hash_function(int32_t key)
{
    return abs(key & HASH_MASK);
}

/*
 * @name:  hash_table_create
 * @brief:
 * @param:
 * @retval:
*/
err_t hash_table_create(struct hash_table **_hash_table, size_t _size)
{
    hash_table_pt handle =  NULL;
    size_t i = 0;
    
    if(NULL == _hash_table || 0 == _size)
        return param_err;

    handle = (hash_table_pt)malloc(sizeof(struct hash_table));
    if(NULL == handle)
        return mem_err;

    handle->size = 2 * _size;
    handle->table = (hash_node_pt)malloc(sizeof(struct hash_node) * _size);
    if(NULL == handle->table)
        return mem_err;
    
    for(i = 0; i < _size; i++) {
        handle->table[i].elem.key = INT_MIN;
        handle->table[i].next = NULL;
    }
    
    *_hash_table = handle;
    
    return success;
}

/*
 * @name:  hash_table_put
 * @brief: 
 * @param:
 * @retval:
*/
err_t hash_table_put(struct hash_table *_hash_table, int32_t _key, int32_t _value)
{
    size_t pos = 0;
    hash_node_pt node_new, node_tmp;
    if(NULL == _hash_table)
        return param_err;

    pos = hash_function(_key);

    /* Conflict check */
    node_tmp = &(_hash_table->table[pos]);
    if(node_tmp->elem.key == INT_MIN) {
        node_tmp->elem.key = _key;
        node_tmp->elem.value = _value;
        return success;
    }
    else if(node_tmp->elem.key == _key)
    {
        /* maybe overwrite */
        return key_conflict;
    }
    else
    {
        /* move to tail and check key if is conflict */
        while(node_tmp->next != NULL) {
            node_tmp = node_tmp->next;
            if(node_tmp->elem.key == _key){
                return key_conflict;
            }
        }

        node_new = (hash_node_pt)malloc(sizeof(struct hash_node));
        if(NULL == node_new)
           return mem_err;

        node_new->elem.key = _key;
        node_new->elem.value = _value;
        node_new->next = NULL;

        node_tmp->next = node_new;
        
        return success;

        
    }

    /* should not run here */
    return unknew;
}

err_t hash_table_delete(struct hash_table *_hash_table, int32_t _key)
{
    size_t pos;
    hash_node_pt node_delete, node_tmp;
    if(NULL == _hash_table)
        return param_err;

    pos = abs(hash_function(_key));
    node_tmp = &(_hash_table->table[pos]); 
    
    if(node_tmp->elem.key == _key) {
       node_tmp->elem.key = INT_MIN;
       return success;
    }
    else {
        
        while(node_tmp->next != NULL) {
            
            if(node_tmp->next->elem.key == _key) {
                /* detele */
                node_delete = node_tmp->next;
                node_tmp->next = node_delete->next;
                free(node_delete);
                node_delete = NULL;
                return success;
            }
            else {
                node_tmp = node_tmp->next;
            }
            
        }
    }

    /* Not found */
    return non_exist;
        
}

int32_t hash_table_get(struct hash_table *_hash_table, int32_t _key)
{
    size_t pos;
    hash_node_pt node_tmp;
    if(NULL == _hash_table)
        return param_err;

    pos = abs(hash_function(_key));
    node_tmp = &(_hash_table->table[pos]); 
    
    do
    {
        if(node_tmp->elem.key == _key)
        {
            return node_tmp->elem.value;
        }

        node_tmp = node_tmp->next;
        
    }while(NULL != node_tmp);
    

    /* Not found */
    return INT_MIN;
        
}

err_t hash_table_destroy(struct hash_table *_hash_table)
{
    size_t i = 0;
    hash_node_pt node_tmp, node_delete;
    if(NULL == _hash_table)
        return param_err;

    for(i = 0; i < _hash_table->size / 2; i++) {
        node_delete = &(_hash_table->table[i]); 
        node_delete->elem.key = INT_MIN;

        node_tmp = node_delete->next;
        while(node_tmp != NULL) {
            node_delete = node_tmp;
            free(node_delete);
            node_delete = NULL;
            node_tmp = node_tmp->next;  
        }  
    }

    return success;
}


err_t hash_table_dump(struct hash_table *_hash_table)
{    
    size_t i;
    hash_node_pt node_delete, node_tmp;
    if(NULL == _hash_table)
        return param_err;
    
    for(i = 0; i < _hash_table->size / 2; i++) {
        node_tmp = &(_hash_table->table[i]);

        while(node_tmp != NULL)
        {
            if(node_tmp->elem.key != INT_MIN)
                printf("[%d]-->[%d]\r\n",node_tmp->elem.key, node_tmp->elem.value);
            node_tmp = node_tmp->next;            
        }
    }
    
    return success;
}


err_t hash_table_test(void)
{
    err_t ret;
    hash_table_pt my_hash_table = NULL;
    int32_t array_test[4] = {
        2, 7, 11, 15
    };
        
    ret = hash_table_create(&my_hash_table, HASH_SIZE);
    if(success != ret) {
        DEBUG_PRF("ret = %d",ret);
        return fail;
    }
    
    ret = hash_table_put(my_hash_table, 2, 0);
    DEBUG_PRF("ret = %d",ret);
    ret = hash_table_put(my_hash_table, 7, 1);
    DEBUG_PRF("ret = %d",ret);
    ret = hash_table_put(my_hash_table, 11, 2);
    DEBUG_PRF("ret = %d",ret);
    ret = hash_table_put(my_hash_table, 15, 3);
    DEBUG_PRF("ret = %d",ret);
    hash_table_dump(my_hash_table);


    ret = hash_table_delete(my_hash_table, 11);
    DEBUG_PRF("ret = %d",ret);
    hash_table_dump(my_hash_table);

    ret = hash_table_destroy(my_hash_table);
    DEBUG_PRF("ret = %d",ret);
    hash_table_dump(my_hash_table);

    
    return success;

}


err_t sum_two_num(void)
{
    err_t ret;
    int32_t target = 9;
    int32_t num;
    int32_t i = 0;
    int32_t index;
    hash_table_pt my_hash_table = NULL;
    int32_t array_test[4] = {
        2, 7, 11, 15
    };
        
    ret = hash_table_create(&my_hash_table, HASH_SIZE);
    if(success != ret) {
        DEBUG_PRF("ret = %d",ret);
        return fail;
    }

    for(i = 0; i < sizeof(array_test)/sizeof(array_test[0]); i++) {
        num = target - array_test[i];
        if((index = hash_table_get(my_hash_table, num)) != INT_MIN) {
            printf("******%d,%d******\r\n", i, index);
        }
        
        ret = hash_table_put(my_hash_table, array_test[i], i);
        DEBUG_PRF("ret = %d",ret);
        
    }

    return success;
    
}

int main(int argc, char **argv)
{
    //hash_table_test();
    sum_two_num();
}

