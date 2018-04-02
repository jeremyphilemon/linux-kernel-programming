#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/module.h>
#include <linux/kthread.h>
#include <linux/time.h>
#include <linux/timer.h>
#include <linux/sched.h>
#include <linux/jiffies.h>
#include <linux/gfp.h>
#include <linux/mm_types.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Jeremy");
MODULE_DESCRIPTION("A module that implements kernel threading");

/*
    struct task_struct {
      volatile long state;
      void *stack;
      unsigned int flags;
      int prio, static_prio;
      struct list_head tasks;
      struct mm_struct *mm, *active_mm;
      pid_t pid;
      pid_t tgid;
      struct task_struct *real_parent;
      char comm[TASK_COMM_LEN];
      struct thread_struct thread;
      struct files_struct *files;
      ...
    };
*/

int no_of_pages;

static struct task_struct *thread_one;
static struct task_struct *thread_two;

unsigned long j_start_addition, j_end_addition, j_count_addition;
unsigned long j_start_multiplication, j_end_multiplication, j_count_multiplication;

static int thread_fn_addition(void *unused) {
  int a, b, sum;
  printk("Inside addition thread\n");
  a = 100;
  b = 200;
  sum = a+b;
  printk("Result of addition is %d\n",sum);
  while(!kthread_should_stop())
    schedule();
  return 0;
}

static int thread_fn_multiplication(void *unused) {
  int a, b, product;
  printk("Inside multiplication thread\n");
  a = 100;
  b = 200;
  product = a*b;
  printk("Result of multiplication is %d\n",product);
  while(!kthread_should_stop())
    schedule();
  return 0;
}

static int __init initFunc(void) {
  char thread_one_name[11] = "thread one";
  char thread_two_name[11] = "thread two";
  printk("Initialising threads module\n");
  thread_one = kthread_create(thread_fn_addition, NULL, thread_one_name);
  if(thread_one) {
    printk("Thread one created successfully\n");
    wake_up_process(thread_one);
  }
  thread_two = kthread_create(thread_fn_multiplication, NULL, thread_two_name);
  if(thread_two) {
    printk("Thread two created successfully\n");
    wake_up_process(thread_two);
  }
  return 0;
}

void create_pages(void) {
  unsigned long page;
  no_of_pages = 100;
  page = __get_free_page(GFP_KERNEL);
  if(page) {
    printk("%d pages have been allocated\n", no_of_pages);
  }
}

static void __exit exitFunc(void) {
  int ret = kthread_stop(thread_one);
  if(!ret) {
    printk("Addition thread stopped\n");
  }
  ret = kthread_stop(thread_two);
  if(!ret) {
    printk("Multiplication thread stopped\n");
  }
  create_pages();
  printk("Cleaning up module\n");
}

module_init(initFunc);
module_exit(exitFunc);
