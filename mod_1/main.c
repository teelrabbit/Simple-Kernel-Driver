#include "header.h"

MODULE_LICENSE("GPL");

#define DRIVER_AUTHOR "johnreich"
#define DRIVER_DESC "simple kernel driver"
MODULE_AUTHOR(DRIVER_AUTHOR);
MODULE_DESCRIPTION(DRIVER_DESC);
MODULE_VERSION("0.0.5");

static char *mystring; module_param(mystring, charp, 0);
static unsigned long *__sys_call_table = NULL; //null=0

// creating buffer for proc file
struct proc_dir_entery *Our_Proc_File;
#define procfs_name "helloworld"


int procfile_read(char *buffer, char **buffer_location, off_t offset, int buffer_length, int *eof, void *data)
{
	int ret;
	
	printk(KERN_INFO "procfile_read (/proc/%s) called\n", procfs_name);
	
	/* 
	 * We give all of our information in one go, so if the
	 * user asks us if we have more information the
	 * answer should always be no.
	 *
	 * This is important because the standard read
	 * function from the library would continue to issue
	 * the read system call until the kernel replies
	 * that it has no more information, or until its
	 * buffer is filled.
	 */
	if (offset > 0) {
		/* we have finished to read, return 0 */
		ret  = 0;
	} else {
		/* fill the buffer, return the buffer size */
		ret = sprintf(buffer, "HelloWorld!\n");
	}

	return ret;
}

static int modInit(void) {

    __sys_call_table = (unsigned long*)kallsyms_lookup_name("sys_call_table");
    printk(KERN_INFO "DEBUG: Syscall Table located at: %s %lu\n", mystring, __sys_call_table);
    //printk(KERN_INFO "DEBUG: %ld", __sys_call_table);

    	Our_Proc_File = create_proc_entry(procfs_name, 0644, NULL);
	
	if (Our_Proc_File == NULL) {
		remove_proc_entry(procfs_name, &proc_root);
		printk(KERN_ALERT "Error: Could not initialize /proc/%s\n",
		       procfs_name);
		return -ENOMEM;
	}

	Our_Proc_File->read_proc = procfile_read;
	Our_Proc_File->owner 	 = THIS_MODULE;
	Our_Proc_File->mode 	 = S_IFREG | S_IRUGO;
	Our_Proc_File->uid 	 = 0;
	Our_Proc_File->gid 	 = 0;
	Our_Proc_File->size 	 = 37;

	printk(KERN_INFO "/proc/%s created\n", procfs_name);		
    return 0;
}

static void modExit(void) {

    printk(KERN_INFO "DEBUG: The short life of km\n");
    printk(KERN_INFO "/proc/%s created\n", procfs_name);
}

module_init(modInit);
module_exit(modExit);
