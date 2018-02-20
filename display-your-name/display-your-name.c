#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>

MODULE_LICENSE("MIT");
MODULE_AUTHOR("Jeremy");
MODULE_DESCRIPTION("A module that prints your name");

static int __init name_init(void)
{
    printk(KERN_INFO "Jeremy Philemon\n");
    return 0;
}

static void __exit name_cleanup(void)
{
    printk(KERN_INFO "Cleaning up module.\n");
}

module_init(name_init);
module_exit(name_cleanup);