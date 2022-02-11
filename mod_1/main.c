#include "header.h"

MODULE_LICENSE("GPL");

#define DRIVER_AUTHOR "johnreich"
#define DRIVER_DESC "simple kernel driver"
MODULE_AUTHOR(DRIVER_AUTHOR);
MODULE_DESCRIPTION(DRIVER_DESC);

static char *mystring; module_param(mystring, charp, 0);
static unsigned long *__sys_call_table = NULL; //null=0

static int modInit(void) {

    __sys_call_table = kallsyms_lookup_name("sys_call_table");
    printk(KERN_INFO "DEBUG: Syscall Table located at: %s %lu\n", mystring, __sys_call_table);
    //printk(KERN_INFO "DEBUG: %ld", __sys_call_table);
    return 0;
}

static void modExit(void) {

    printk(KERN_INFO "DEBUG: The short life of km\n");
}

module_init(modInit);
module_exit(modExit);
