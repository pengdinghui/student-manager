#include <stdio.h>
#include <stdlib.h>

#include "manager.h"


static void add_stu(struct manager_info *info, struct student *stu)
{	
	struct list_head *pos = NULL;

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
				return;
			}else {
				fprintf(stderr, "Error --- student id conflict\n");
				return;
			}
		}
	}

	// the student id is the biggest so far
	list_add_tail(info->head, &stu->list);
}



static void remove_stu(struct manager_info *info, size_t id)
{
	struct list_head *pos = NULL;

	list_for_each(pos, info->head) {
		struct student *cur_stu = container_of(pos, struct student, list);

		if(cur_stu->id == id) {
			list_del_init(pos);
			free(cur_stu);
		}
	}
}

static void print_single_stu(struct student *stu)
{
	print_title();
	print_data(stu);
}

static void print_all_stu(struct manager_info *info)
{
	print_title();

	struct list_head *pos = NULL;
	list_for_each(pos, info->head) {
		struct student *cur_stu = container_of(pos, struct student, list);
		print_data(cur_stu);
	}
}


void manager_info_init(struct manager_info *info)
{
	info->head = (struct list_head *) malloc(sizeof(struct list_head));

	init_list_head(info->head);

	info->add_stu = add_stu;
	info->remove_stu = remove_stu;
	info->print_single_stu = print_single_stu;
	info->print_all_stu = print_all_stu;
}


void manager_info_destroy(struct manager_info *info)
{	
	struct list_head *pos = NULL;	
	struct list_head *tmp = NULL;	
	
	list_for_each_safe(pos, tmp, info->head) {
		list_del_init(pos);		

		struct student *cur_stu = container_of(pos, struct student, list);
		free(cur_stu);
	}
	
	free(info->head);
}









