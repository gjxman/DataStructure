#include "stdio.h"
#include "single_link_list.h"


typedef struct {
    slink_list_node_t node;
    char name[255];
    int8_t age;
}teacher_t, *teacher_pt;

void teacher_dump(teacher_pt t)
{
    DEBUG_PRF("age : %d", t->age);
}

int main(int argc, char **argv)
{
    err_t ret;
    size_t i = 0;
    slink_list_pt my_list = NULL;
    teacher_pt tmp;
    teacher_t t1, t2, t3;
    t1.age = 31;
    t2.age = 32;
    t3.age = 33;

    
    ret = slink_list_create(&my_list);
    DEBUG_PRF("slink_list_create ret = %d", ret);

    ret = slink_list_push_front(my_list, (slink_list_node_pt)&t1);
    DEBUG_PRF("slink_list_push_front ret = %d", ret);

    ret = slink_list_push_front(my_list, (slink_list_node_pt)&t2);
    DEBUG_PRF("slink_list_push_front ret = %d", ret);
    
    ret = slink_list_push_front(my_list, (slink_list_node_pt)&t3);
    DEBUG_PRF("slink_list_push_front ret = %d", ret);

    ret = slink_list_get_size(my_list);   
    DEBUG_PRF("slink_list_get_size ret = %d", ret);
    
    for(i = 0; i < slink_list_get_size(my_list); i++)
    {
        slink_list_get_node(my_list, i, (slink_list_node_pt *)&tmp);
        teacher_dump(tmp);
    }

    while(slink_list_get_size(my_list))
    {
        slink_list_pop_back(my_list, (slink_list_node_pt *)&tmp);
        teacher_dump(tmp);
    }

    DEBUG_PRF("single link list is %s", slink_list_is_empty(my_list) == true?"empty":"not empty");

    ret = slink_list_destroy(my_list);
    DEBUG_PRF("slink_list_destroy ret = %d", ret);
    
    return 0;
}
