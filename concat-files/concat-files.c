#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>

#include <linux/fs.h>
#include <asm/segment.h>
#include <asm/uaccess.h>
#include <linux/buffer_head.h>

MODULE_LICENSE("MIT");
MODULE_AUTHOR("Jeremy");
MODULE_DESCRIPTION("A module that concatenates two input files' contents");

static int __init hello_init(void)
{
	struct file *file;
	*file = openfile_open("file-1.txt", 0, 0);
    return 0;
}

static void __exit hello_cleanup(void)
{
    printk(KERN_INFO "Cleaning up module.\n");
}

module_init(hello_init);
module_exit(hello_cleanup);