#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/module.h>
#include <linux/kthread.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Jeremy");
MODULE_DESCRIPTION("A module that implements kernel threading");

static struct task_struct *thread_one;

int thread_fn(void) {
  printk("Creating thread one\n");
  return 0;
}

static int __init initFunc(void) {
  char our_thread[11]="thread one";
  printk("Initialising threads module\n");
  thread_one = kthread_create(thread_fn(), NULL, our_thread);
}
 
static void __exit exitFunc(void) {
  int ret = kthread_stop(thread_one);
  if(ret) {
    printk("Thread stopped\n");
  }
  printk("Cleaning threads module\n");
}

module_init(initFunc);
module_exit(exitFunc);
