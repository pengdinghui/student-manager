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

	
};
