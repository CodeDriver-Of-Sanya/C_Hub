#include<stdio.h>
#include<malloc.h>
#include"ForwardList.h"

int main() {
	List list;
	flist_init(&list);

	flist_push(&list, 1);
	flist_push(&list, 2);
	flist_push(&list, 3);
	
	flist_pop(&list, 7);
	flist_pop(&list, 6);
	flist_pop(&list, 5);

	flist_insert(&list, 6, 888);

	//flist_print(&list);

	//flist_tailDel(&list);
	//flist_print(&list);

	//flist_popDel(&list);
	//flist_print(&list);

	//flist_distDel(&list, 1);
	//flist_distDel(&list, 2);
	//flist_distDel(&list,3);
	flist_print(&list);

	//printf("%d\n", flist_size(&list));
	//printf("%d", list.data);

	flist_sort(&list);
	flist_print(&list);

	flist_reverse(&list);
	flist_print(&list);

	flist_clean(&list);
	return 0;
}