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

    ret = slink_list_push_back(my_list, (slink_list_node_pt)&t1);
    DEBUG_PRF("slink_list_push_back ret = %d", ret);

    ret = slink_list_push_front(my_list, (slink_list_node_pt)&t2);
    DEBUG_PRF("slink_list_push_back ret = %d", ret);
    
    ret = slink_list_push_back(my_list, (slink_list_node_pt)&t3);
    DEBUG_PRF("slink_list_push_back ret = %d", ret);

    for(i = 0; i < slink_list_get_size(my_list); i++)
    {
        slink_list_get_node(my_list, i, &tmp);
        teacher_dump(tmp);
    }
    
    return 0;
}