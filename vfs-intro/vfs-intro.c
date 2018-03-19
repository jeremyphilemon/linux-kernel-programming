#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/module.h>
#include <linux/syscalls.h>
#include <linux/file.h>
#include <linux/fs.h>
#include <linux/fcntl.h>
#include <asm/uaccess.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Jeremy");
MODULE_DESCRIPTION("A module that supports file I/O");

static void read_file(char *filename) {
  char buf[1];
  struct file *filp;
  char bufs[100];
  int ret;
 
  strcpy(bufs, "Hello, world!");

// Kernel memory access setting
  mm_segment_t old_fs = get_fs();
  set_fs(KERNEL_DS);

// Opening a file
  filp = filp_open(filename, O_RDWR, S_IRUSR|S_IWUSR);
  if (IS_ERR(filp)) {
      printk("Open error :/\n");
      return;
  }
  else {
      printk("Open success!\n");
  }
 
// Writing
  vfs_write(filp, bufs, strlen(bufs), &filp->f_pos);

// Reading 
  filp->f_pos = 0;
  ret = vfs_read(filp, bufs, 13, &filp->f_pos);
  printk("%s\n", bufs);

// Closing said file
  filp_close(filp, NULL);  

// Restore kernel memory setting
  set_fs(old_fs);
}
 
static int __init init(void) {
  read_file("./file-1.txt");
  return 0;
}
 
static void __exit exitFunc(void) {
  printk("Cleaning vfs-intro.c\n");
}

module_init(init);
module_exit(exitFunc);
