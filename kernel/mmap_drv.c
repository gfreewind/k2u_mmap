/*
 * =====================================================================================
 *
 *       Filename:  mmap_drv.c
 *
 *    Description:  mmap driver
 *                  The driver is used to mmap kernel memory to user space
 *
 *        Version:  1.0
 *        Created:  03/20/2013 09:39:14 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  gfree.wind@gmail.com
 *        Company:  
 *
 * =====================================================================================
 */
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/uaccess.h>


static struct cdev mmap_drv;
static dev_t ndev;


static int mmap_drv_open(struct inode *nd, struct file *filp)
{
    int major = MAJOR(nd->i_rdev);
    int minor = MINOR(nd->i_rdev);

    printk(KERN_INFO "mmap_drv: major=%d minor=%d\n", major, minor);

    return 0;
}


static int mmap_drv_read(struct file *f, char __user *u, size_t sz, loff_t *off)
{
#define MMAP_TEST_STR       "hello from mmap_drv"
    printk(KERN_INFO "mmap_drv: enter read func\n");

    copy_to_user(u, MMAP_TEST_STR, sizeof(MMAP_TEST_STR));

    return 0;
}

struct file_operations mmap_drv_ops = {
    .owner = THIS_MODULE,
    .open = mmap_drv_open,
    .read = mmap_drv_read,
};


static int mmap_drv_init(void)
{
    int ret;

    cdev_init(&mmap_drv, &mmap_drv_ops);
    ret = alloc_chrdev_region(&ndev, 0, 1, "mmap_drv");
    if (ret < 0) {
        return ret;
    }
    printk(KERN_INFO "mmap_drv_init: major=%d minor=%d\n", MAJOR(ndev), MINOR(ndev));
    ret = cdev_add(&mmap_drv, ndev, 1);
    if (ret < 0) {
        return ret;
    }
    
    return 0;
}

static void mmap_drv_exit(void)
{
    printk(KERN_INFO "mmap_drv_exit...\n");
    cdev_del(&mmap_drv);
    unregister_chrdev_region(ndev, 1);
}

module_init(mmap_drv_init);
module_exit(mmap_drv_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("gfree.wind@gmail.com");
MODULE_DESCRIPTION("The kernel part used to mmap kernel memory to userspace");





