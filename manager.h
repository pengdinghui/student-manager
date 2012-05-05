#pragma once

#include <stdio.h>
#include <stdlib.h>

#include "klist.h"

struct student {
	size_t id;
	char *name;
	int gender;
	size_t math_score;
	size_t english_score;
	size_t computer_score;

	struct list_head list;
};


struct manager_info {
	struct list_head *head;	
	
	void (*add_stu)(struct manager_info *info, struct student *stu);

	void (*remove_stu)(struct manager_info *info, struct student *stu);

	void (*print_stu)(struct student *stu);
		
};

void manager_info_init(struct manager_info *info);
void manager_info_destroy(struct manager_info *info);
