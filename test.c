#include <stdio.h>
#include <stdlib.h>


#include "manager.h"
#include "test_data.h"

static void insert_test_data(struct manager_info *info)
{
	int i = 0;
	for(; i < sizeof(STU_ARR)/sizeof(struct student); ++i) {
		struct student *stu = (struct student *)
			malloc(sizeof(struct student));
		stu->id = STU_ARR[i].id;
		stu->name = STU_ARR[i].name;
		stu->gender = STU_ARR[i].gender;
		stu->math_score = STU_ARR[i].math_score;
		stu->english_score = STU_ARR[i].english_score;
		stu->computer_score = STU_ARR[i].computer_score;

		info->add_stu(info, stu);
	}
	printf("insert test data complete!\n");

}

int main()
{
	struct manager_info *info = (struct manager_info *)
			malloc(sizeof(struct manager_info));
	//init	
	manager_info_init(info);

	insert_test_data(info);	
	
	info->print_all_stu(info);

	//destroy 
	manager_info_destroy(info);
}
