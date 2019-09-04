#include "stdio.h"
#include "circle_link_list.h"


typedef struct {
    clink_list_node_t node;
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
    clink_list_pt my_list = NULL;
    teacher_pt tmp;
    teacher_t t1, t2, t3;
    t1.age = 31;
    t2.age = 32;
    t3.age = 33;

    
    ret = clink_list_create(&my_list);
    DEBUG_PRF("clink_list_push_front ret = %d", ret);

    ret = clink_list_push_front(my_list, (clink_list_node_pt)&t1);
    DEBUG_PRF("clink_list_push_front ret = %d", ret);

    ret = clink_list_push_front(my_list, (clink_list_node_pt)&t2);
    DEBUG_PRF("clink_list_push_front ret = %d", ret);
    
    ret = clink_list_push_front(my_list, (clink_list_node_pt)&t3);
    DEBUG_PRF("clink_list_push_front ret = %d", ret);

    ret = clink_list_get_size(my_list);   
    DEBUG_PRF("clink_list_get_size ret = %d", ret);
    
    for(i = 0; i < clink_list_get_size(my_list); i++)
    {
        clink_list_get_node(my_list, i, (clink_list_node_pt *)&tmp);
        teacher_dump(tmp);
    }

    for(i = 0; i < 20; i++)
    {
        clink_list_get_current_slider_node(my_list, (clink_list_node_pt *)&tmp);
        teacher_dump(tmp);
        clink_list_slider_move(my_list);
    }
    
    while(clink_list_get_size(my_list))
    {
        clink_list_pop_back(my_list, (clink_list_node_pt *)&tmp);
        teacher_dump(tmp);
    }

    DEBUG_PRF("circle link list is %s", clink_list_is_empty(my_list) == true?"empty":"not empty");

    ret = clink_list_destroy(my_list);
    DEBUG_PRF("clink_list_destroy ret = %d", ret);
    
    return 0;
}
