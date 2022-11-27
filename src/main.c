#include <linux/init.h>
#include <linux/module.h>
#include <linux/proc_fs.h>
#include <linux/slab.h>
#include <linux/string.h>
#include <linux/uaccess.h>
#include <linux/kernel.h>
#include <linux/kmod.h>
#include <linux/seq_file.h>

#include "monitor.h"

MODULE_LICENSE("GPL");

#define ENTRY_NAME "monitor"
#define PERMS 0777
#define PARENT NULL

static long PID = 0;
static int state = STOP;

static char *env[] = {"/home/ubuntu", "/usr/local/sbin", NULL};

static struct Path path = {
    .output = "/tmp/output_monitor.txt",
    .strace = "/usr/bin/strace",
    .killall = "/usr/bin/killall"
};


static int monitor_show(struct seq_file *s, void *v) {
    char *buffer = kmalloc(sizeof(char) * 1, __GFP_WRITE | __GFP_IO | __GFP_FS);
    loff_t f_pos = 0;
    struct file *fp = filp_open(path.output, O_RDWR | O_CREAT, 0666);

    if (IS_ERR(fp)) {
        printk(KERN_ERR "output file open error");
        return 0;
    }

    while (kernel_read(fp, buffer, 1, &f_pos)) {
        seq_printf(s, "%s", buffer);
    }
	
    seq_printf(s, "\n");

    kfree(buffer);
    filp_close(fp, NULL);
    
    return 0;
}

static int monitor_proc_open(struct inode *inode, struct file *file) {
    return single_open(file, monitor_show, NULL);
}

static void monitor_start(void) {
    char *buffer = kmalloc(sizeof(char) * 10, __GFP_WRITE | __GFP_IO | __GFP_FS);

    sprintf(buffer, "%ld", PID);
    char *arv[] = {path.strace, "-c", "-p", buffer, "-o", path.output, NULL};

    call_usermodehelper(path.strace, arv, env, UMH_WAIT_EXEC);
    kfree(buffer);
}
	
static void monitor_stop(void) {
    char *arv[] = {path.killall, path.strace, NULL};

    call_usermodehelper(path.killall, arv, env, UMH_WAIT_EXEC);
}

static ssize_t monitor_proc_write(struct file *sp_file, const char __user *buf, size_t
size, loff_t *offset) {
    char *str = kmalloc(sizeof(char) * 10, __GFP_WRITE | __GFP_IO | __GFP_FS);

    if (!str) return -ENOMEM;	
    if (copy_from_user(str, buf, size)) return -EFAULT;	

    if (!PID) {
	kstrtol(str, 10, &PID);
	state = STOP;
    } else {
	if (sysfs_streq(str, "start") && state == STOP) {
	    monitor_start();
	    state = START;
	} else if (sysfs_streq(str, "stop")) {
	    monitor_stop();
	    PID = 0;
	    state = STOP;
	} else if (sysfs_streq(str, "pause") && state == START) {
	    monitor_stop();
	    state = PAUSE;
    	} else if (sysfs_streq(str, "recover") && state == PAUSE) {
	    monitor_start();
	    state = START;
        } 
    }

    kfree(str);

    return size;
}

static struct file_operations fops = {
    .owner = THIS_MODULE,
    .open = monitor_proc_open,
    .release = single_release,
    .read = seq_read,
    .llseek  = seq_lseek,
    .write = monitor_proc_write
};

static int monitor_init(void) {
    if (!proc_create(ENTRY_NAME, PERMS, NULL, &fops)) {
	printk(KERN_ERR "ERROR! proc_create");
	remove_proc_entry(ENTRY_NAME, NULL);
	return -ENOMEM;
    }
    return 0;
}

static void monitor_exit(void) {
    remove_proc_entry(ENTRY_NAME, NULL);
}

module_init(monitor_init);
module_exit(monitor_exit);
