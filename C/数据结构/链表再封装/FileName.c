#include"LinkList.h"
#include<stdio.h>

int main(){ 
	LinkList* list = CreatLinkList();

	//linkList_push_front(list, 11);
	//linkList_push_front(list, 22);
	//linkList_push_front(list, 33);

	linkList_push_back(list, 444);
	linkList_push_back(list, 555);
	linkList_push_back(list, 666);

	//linkList_push(list,666,123);

	//linkList_pop_front(list);
	//linkList_pop_front(list);
	//linkList_pop_front(list);
	//linkList_pop_front(list);

	//linkList_pop_back(list);
	//linkList_pop_back(list);
	//linkList_pop_back(list);
	//linkList_pop_back(list);

	destoryLinkList(list);
	return 0;
}
