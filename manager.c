#include <stdio.h>
#include <stdlib.h>

#include "manager.h"


static void add_stu(struct manager_info *info, struct student *stu)
{	
	struct list_head *pos;

	list_for_each(pos, info->head) {
		struct student *cur_stu = container_of(pos, struct student, list);

		if(cur_stu->id > stu->id) {
			if(pos->prev == info->head) {
				list_add(info->head, &stu->list);
				return;
			}
			
			struct student *prev_stu =
				container_of(pos->prev, struct student, list);
			if(prev_stu->id < stu->id) {

				__list_add(pos->prev, pos, &stu->list);		
			}else {
				fprintf(stderr, "Error --- student id conflict\n");
			}
		}
	}

	// the student id is the biggest so far
	list_add_tail(info->head, &stu->list);
}



static void remove_stu(struct manager_info *info, struct student *stu)
{
	
}

static void print_stu(struct student *stu)
{


}


void manager_info_init(struct manager_info *info)
{
	info->head = (struct list_head *) malloc(sizeof(struct list_head));

	init_list_head(info->head);

	info->add_stu = add_stu;
	info->remove_stu = remove_stu;
	info->print_stu = print_stu;
}


void manager_info_destroy(struct manager_info *info)
{	
}
