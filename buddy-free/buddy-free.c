#include<linux/gfp.h> 
#include<linux/module.h> 
#include<linux/init.h> 
#include<linux/mm.h> 

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Jeremy");
MODULE_DESCRIPTION("A module that implements the buddy free algorithm");

void buddy(void) { 
	unsigned long page = __get_free_pages(GFP_KERNEL,10);
	signed short n; 
	signed short m=100; 
	signed short k; 
	n = 4;
	memset((void *)page,'0',sizeof(page)); 
	if(!page) 
		printk("Return error\n"); 
	else 
		printk("Success %p\n",(void *) page); 
	while(m<=n) 
	{ 
		m = m/2; 
	} 
	if(m<n) 
		m = m*2; 
	k = 100-m; 
	__free_pages((void*) page, k);				 
	printk("The no. of pages freed are %hi\n", k); 
} 

static int memory_init(void) { 
	printk("Initialising module\n"); 
	buddy(); 
	return 0; 
} 
static void memory_cleanup(void) { 
	printk("Cleaning up module\n"); 
} 

module_init(memory_init);
module_exit(memory_cleanup);