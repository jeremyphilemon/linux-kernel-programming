	#include <linux/module.h>
	#include <linux/kernel.h>
	#include <linux/init.h>
	#include <linux/gfp.h> //(get free pages) interface to allocate/free memory within kernel.
	#include <linux/mm_types.h>

	MODULE_LICENSE("GNU");
	MODULE_AUTHOR("Jeremy");
	MODULE_DESCRIPTION("A module that implements memory management");

	/*  
		struct page {
			unsigned long flags; //Stores the status of the page (dirty, locked)
			atomic_t_count; //Stores the usage count of the page (-1: none using)
			atomic_t_mapcount;
			unsigned long private;
			struct address_space *mapping;
			pgoff_t index;
			struct list_head lru;
			void *virtual;
		}

		Kernel also uses zones to group pages of similar properties because some pages,
		because of their physical address in memory, they cannot be used for certain
		tasks. The kernel cannot treat all pages as identical due to hardware 
		limitations.

		Two limitations of hardware wrt memory addressing:
		- Some hardware devices can perfoem DMA to only certain memory addresses.
		- Some architectures can physically address larger amounts of memory than they 
		  can virtually address.
	*/

	void calculation(void) {
		signed short count=0;
		unsigned long page;
		while(count<1500) {
			page= __get_free_pages(GFP_KERNEL, 1);
			if(!page) {
				break;
			}
			count++;
		}
		printk("The no. of pages allocated are: %hi", count);
	}

	static int __init memory_init(void)
	{
		calculation();
		return 0;
	}

	static void __exit memory_cleanup(void)
	{
	    printk(KERN_INFO "Cleaning up module.\n");
	}

	module_init(memory_init);
	module_exit(memory_cleanup);