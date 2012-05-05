#include <stdio.h>
#include <stdlib.h>

#include "manager.h"


int main()
{
	struct manager_info *info = (struct manager_info *)
			malloc(sizeof(struct manager_info));
	
	manager_info_init(info);


}
