#include <stdio.h>
#include "array.h"


struct student {
    uint8_t age;
    char *name;
};

void free_student(void* s)
{
    struct student *p = s;
    free(p->name);
    p->name = NULL;
}

void student_info_dump(struct student *s)
{
    printf("name : ");
    printf("%s",s->name);
    printf(" age : %d\r\n", s->age);
}

int main(int argc, char **argv)
{
    err_t ret;
    size_t i = 0;
    struct student s1, s2, s3, s4;
    struct student *s;
    struct array *my_array = NULL;
    
    /* Create node */
    s1.age = 13,
    s1.name = (char *)malloc(sizeof("xiazi"));
    memcpy(s1.name, "xiazi", sizeof("xiazi"));
    
    s2.age = 18,
    s2.name = (char *)malloc(sizeof("delaiwen"));
    memcpy(s2.name, "deleiwen", sizeof("delaiwen"));

    s3.age = 83,
    s3.name = (char *)malloc(sizeof("vn"));
    memcpy(s3.name, "vn", sizeof("vn"));
    
    s4.age = 66,
    s4.name = (char *)malloc(sizeof("ruiwen"));
    memcpy(s4.name, "ruiwen", sizeof("ruiwen"));
    
    /* Create array */
    DEBUG_PRF("create array......");
    ret = array_create(&my_array, 9, sizeof(struct student));    
    DEBUG_PRF("array_create ret = %d", ret);
    array_set_free_method(my_array,free_student);
    printf("\r\n");
    
    /* Insert */
    DEBUG_PRF("inseart array......");
    ret = array_insert_tail(my_array, &s1);
    DEBUG_PRF("array_insert_tail ret = %d", ret);
    
    ret = array_insert_tail(my_array, &s2);
    DEBUG_PRF("array_insert_tail ret = %d", ret);
    
    ret = array_insert_tail(my_array, &s3);
    DEBUG_PRF("array_insert_tail ret = %d", ret);

    DEBUG_PRF("present array length is : %ld", array_cur_len_get(my_array));
    
    for(i = 0; i < array_cur_len_get(my_array); i++) {
        if(array_get_elem(my_array, i) != NULL)
            student_info_dump(array_get_elem(my_array, i));
        else
            DEBUG_PRF("array_get_elem ret null");
    }
    printf("\r\n");

    /* Delete */
    DEBUG_PRF("delete array......");
    ret = array_delete_value(my_array, &s2);
    DEBUG_PRF("array_delete_value ret = %d", ret);

    for(i = 0; i < array_cur_len_get(my_array); i++) {
        if(array_get_elem(my_array, i) != NULL)
            student_info_dump(array_get_elem(my_array, i));
        else
            DEBUG_PRF("array_get_elem ret null");
    }
    printf("\r\n");


    /* Modfily */
    DEBUG_PRF("nmodifily array......");
    array_modify_adv(my_array, array_cur_len_get(my_array) - 1, &s4);
    for(i = 0; i < array_cur_len_get(my_array); i++) {
        if(array_get_elem(my_array, i) != NULL)
            student_info_dump(array_get_elem(my_array, i));
        else
            DEBUG_PRF("array_get_elem ret null");
    }
    printf("\r\n");


    /* Clear array */
    DEBUG_PRF("clear array......");
    array_clear(my_array);
    for(i = 0; i < array_cur_len_get(my_array); i++) {
        if(array_get_elem(my_array, i) != NULL)
            student_info_dump(array_get_elem(my_array, i));
        else
            DEBUG_PRF("array_get_elem ret null");
    }
    printf("\r\n");

    /* Destroy array */
    DEBUG_PRF("destroy array......");
    array_destroy(my_array);
    for(i = 0; i < array_cur_len_get(my_array); i++) {
        if(array_get_elem(my_array, i) != NULL)
            student_info_dump(array_get_elem(my_array, i));
        else
            DEBUG_PRF("array_get_elem ret null");
    }
    printf("\r\n");

    DEBUG_PRF("end array......");
    
    return 0;
    
}

