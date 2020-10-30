//Carter Mooring
//OS Project 2
//10/14/2020

#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/list.h>
#include <linux/slab.h>

struct person{
	int month;
	int day;
	int year;
	struct person *next;
};

struct person *mainList = NULL;

struct person* newNode(struct person* val, int month, int day, int year){
	if(val == NULL){
		val = (struct person*)kmalloc(sizeof(struct person), GFP_KERNEL);
		val -> month = month;
		val -> day = day;
		val -> year = year;
	}else{
		val -> next = newNode(val->next, month, day, year);
	}
	return val;
}

void printList(struct person *list){
	printk(KERN_INFO "Printing List");

	while(list != NULL){
		printk(KERN_INFO "%d, %d, %d\n", list -> month, list -> day, list -> year);
		if(list -> next != NULL){
			list = list -> next;
		}
	}
}

struct person *deleteList(struct person *list){
	if(list != NULL){
		list = deleteList(list->next);
		return NULL;
	}
	kfree(mainList);
	return NULL;
}

void populateList(struct person *mainList){
	mainList = newNode(mainList, 10, 14, 2020);
	mainList = newNode(mainList, 10, 15, 2019);
	mainList = newNode(mainList, 1, 20, 1432);
	mainList = newNode(mainList, 4, 3, 12);
	mainList = newNode(mainList, 8, 3, 1999);
	mainList = newNode(mainList, 5, 27, 2005);

	printList(mainList);
}

/* This function is called when the module is loaded. */
int simple_init(void)
{
       printk(KERN_INFO "Loading Module\n");
	   populateList(mainList);

       return 0;
}

/* This function is called when the module is removed. */
void simple_exit(void) {
	printk(KERN_INFO "Removing Module\n");
	printk(KERN_INFO "Deleting List\n");
	deleteList(mainList);
	printk(KERN_INFO "List Deleted\n");
}

/* Macros for registering module entry and exit points. */
module_init( simple_init );
module_exit( simple_exit );

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Simple Module");
MODULE_AUTHOR("SGG");
