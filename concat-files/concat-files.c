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
MODULE_DESCRIPTION("A module that concatenates two files");
 
static int __init init(void) {
// Initial configuration
  struct file *filp;

// Kernel memory access setting
  mm_segment_t old_fs = get_fs();
  set_fs(KERNEL_DS);

  filp = filp_open("file-1.txt", O_RDWR, S_IRUSR|S_IWUSR);
  char file1[100]; file1[35] = '\0';
  vfs_read(filp, file1, 35, &filp->f_pos);
  filp_close(filp, NULL);
  filp = filp_open("file-2.txt", O_RDWR, S_IRUSR|S_IWUSR);
  char file2[100];
  vfs_read(filp, file2, 35, &filp->f_pos);
  filp_close(filp, NULL);
  filp = filp_open("file.txt", O_RDWR, S_IRUSR|S_IWUSR);
  strcat(file1, file2);
  vfs_write(filp, file1, 70, &filp->f_pos);
  filp_close(filp, NULL);

// Restore kernel memory setting
  set_fs(old_fs);
  return 0;
}
 
static void __exit exitFunc(void) {
  printk("Cleaning concat-files.c\n");
}

module_init(init);
module_exit(exitFunc);
