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

struct file *file_open(const char *path, int flags, int rights) 
{
  struct file *filp = NULL ;
  mm_segment_t oldfs;
  int err = 0;

  oldfs = get_fs();
  set_fs(get_ds());
  filp = filp_open(path, flags, rights);
  set_fs(oldfs);
  if (IS_ERR(filp)) {
    err = PTR_ERR(filp);
    return NULL;
    printk("Error opening file :/\n");
  }
  printk("File opened!\n");
  return filp;
}

void file_close(struct file *file) 
{
  filp_close(file, NULL);
}

int file_read(struct file *file, unsigned long long offset, unsigned char *data, unsigned int size) 
{
  mm_segment_t oldfs;
  int ret;

  oldfs = get_fs();
  set_fs(get_ds());

  ret = vfs_read(file, data, size, offset);

  printk("read: %llu\n", offset);

  set_fs(oldfs);
  return ret;
} 

int file_write(struct file *file, unsigned long long offset, unsigned char *data, unsigned int size) 
{
  mm_segment_t oldfs;
  int ret;

  oldfs = get_fs();
  set_fs(get_ds());

  printk("write: %s\n", data);

  ret = vfs_write(file, data, size, offset);

  set_fs(oldfs);
  return ret;
}
 
static int __init init(void) {
  struct file *filp;
  filp = file_open("file-1.txt", O_RDWR, S_IRUSR|S_IWUSR);
  char file1[100];
  file_read(filp, &filp->f_pos, file1, 100);
  file_close(filp);
  filp = file_open("file-2.txt", O_RDWR, S_IRUSR|S_IWUSR);
  char file2[100];
  file_read(filp, &filp->f_pos, file2, 100);
  file_close(filp);
  filp = file_open("file.txt", O_RDWR, S_IRUSR|S_IWUSR);
  file_write(filp, &filp->f_pos, file1, 100);
  file_close(filp);
  return 0;
}
 
static void __exit exitFunc(void) {
  printk("Cleaning concat-files.c\n");
}

module_init(init);
module_exit(exitFunc);
