#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#include "manager.h"
#include "test_data.h"

#define INSERT_DATA	1 
#define PRINT_ALL	2 
#define ADD_ONE		3	
#define REMOVE_ONE	4 
#define EXIT		5 

struct manager_info *info;
char buf[100];	

static void insert_test_data(struct manager_info *info);
static void print_menu();
static void read_command();
static void choice_handle(int choice);
static void add_one_stu();
static void remove_one_stu();


static void insert_test_data(struct manager_info *info)
{
	int i = 0;
	for(; i < sizeof(STU_ARR)/sizeof(struct student); ++i) {
		struct student *stu = (struct student *)
			malloc(sizeof(struct student));
		stu->id = STU_ARR[i].id;
		stu->name = (char *)malloc(strlen(STU_ARR[i].name) + 1);
		strcpy(stu->name, STU_ARR[i].name);
		
		stu->gender = STU_ARR[i].gender;
		stu->math_score = STU_ARR[i].math_score;
		stu->english_score = STU_ARR[i].english_score;
		stu->computer_score = STU_ARR[i].computer_score;

		info->add_stu(info, stu);
	}
	printf("insert test data complete!\n");
}

static void print_menu()
{
	printf("---------------------------------------\n");
	printf("1.Insert the test data\n");
	printf("2.Print all the student information\n");
	printf("3.Add a student information\n");
	printf("4.Remove a student information\n");
	printf("5.Exit\n");
	printf("Plz enter your choice number!\n");
}


static void read_command()
{
	int choice = 0;


	while (1) {
		print_menu();

		fgets(buf, 100, stdin);		
		
		if(strlen(buf) != 2) {
			goto error;
		}

		
		
		if (buf[0] > '0' && buf[0] < '6') {
			choice = buf[0] - '0';	
			choice_handle(choice);

			printf("\n");
			continue;

		}else {
			goto error;
		}

error :      	printf("input not correct\n");
		continue;
	}
}


static void choice_handle(int choice)
{
	switch (choice) {
	case INSERT_DATA:
		insert_test_data(info);
		break;

	case PRINT_ALL:
		info->print_all_stu(info);
		break;

	case ADD_ONE:
		add_one_stu();
		break;

	case REMOVE_ONE:
		remove_one_stu();
		break;

	case EXIT:
		manager_info_destroy(info);
		printf("Bye\n");
		exit(0);
		break;

	default:
		printf("input not correct\n");
		break;
	}
}

static void add_one_stu()
{
	char *stop;
	struct student *stu = (struct student *)
			malloc(sizeof(struct student));
	//id
	while (1) {

		printf("id:");
		fgets(buf, 100, stdin);	
		stu->id = strtol(buf, &stop, 10);
		if(stu->id > 0) {
			break;
		}

		printf("input error\n");
	}

	//name
	printf("name:");
	fgets(buf, 100, stdin);	
	int len = strlen(buf);
	buf[len - 1] = '\0';//remove the \n char
	char *name = (char *)malloc(len);
	strcpy(name, buf);
	stu->name = name;
	
	//gender
	while (1) {
		printf("gender[m/f]:");
		fgets(buf, 100, stdin);	
		if (buf[0] == 'm') {
			stu->gender = 0;
			break;
		}else if(buf[0] == 'f'){
			stu->gender = 1;
			break;
		}
		printf("input error\n");

	}

	//math score
	printf("math_score:");
	fgets(buf, 100, stdin);	
	stu->math_score = strtol(buf, &stop, 10);

	//english score
	printf("english_score:");
	fgets(buf, 100, stdin);	
	stu->english_score = strtol(buf, &stop, 10);

	//computer score
	printf("computer_score:");
	fgets(buf, 100, stdin);	
	stu->computer_score = strtol(buf, &stop, 10);

	info->add_stu(info, stu);
}

void remove_one_stu()
{
	char *stop;
	printf("student id:");
	fgets(buf, 100, stdin);	
	size_t id = strtol(buf, &stop, 10);

	info->remove_stu(info, id);
}

int main()
{
	info = (struct manager_info *)
			malloc(sizeof(struct manager_info));

	printf("\nWelcome to the student manager system!\n");

	manager_info_init(info);

	read_command();
}
