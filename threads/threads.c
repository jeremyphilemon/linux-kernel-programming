#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/module.h>
#include <linux/kthread.h>
#include <linux/time.h>
#include <linux/timer.h>
#include <linux/sched.h>
#include <linux/jiffies.h>

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

static struct task_struct *thread_one;
static struct task_struct *thread_two;

unsigned long j_start_addition, j_end_addition, j_count_addition;
unsigned long j_start_multiplication, j_end_multiplication, j_count_multiplication;

static int thread_fn_addition(void *unused) {
  int a, b, sum;
  printk("Inside thread creation's function\n");  
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
  printk("Inside thread creation's function\n");  
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
  j_start_addition = jiffies;
  thread_one = kthread_create(thread_fn_addition, NULL, thread_one_name);
  if(thread_one) {
    printk("Thread one created successfully\n");
    wake_up_process(thread_one);
  }
  j_start_multiplication = jiffies;
  thread_two = kthread_create(thread_fn_multiplication, NULL, thread_two_name);
  if(thread_two) {
    printk("Thread one created successfully\n");
    wake_up_process(thread_two);
  }
  return 0;
}
 
static void __exit exitFunc(void) {
  int ret = kthread_stop(thread_one);
  if(!ret) {
    printk("Addition thread stopped\n");
    j_end_addition = jiffies;
  }
  j_count_addition = j_end_addition - j_start_addition;
  printk("Time elapsed in milliseconds: %lu\n", (j_count_addition*1000)/HZ);
  ret = kthread_stop(thread_two);
  if(!ret) {
    printk("Mulitpliction thread stopped\n");
    j_end_multiplication = jiffies;
  }
  j_count_multiplication = j_end_multiplication - j_start_multiplication;
  printk("Time elapsed in milliseconds: %lu\n", (j_count_multiplication*1000)/HZ);
  printk("Cleaning threads module\n");
}

module_init(initFunc);
module_exit(exitFunc);
