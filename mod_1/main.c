#include "header.h"

MODULE_LICENSE("GPL");

#define DRIVER_AUTHOR "johnreich"
#define DRIVER_DESC "simple kernel driver"
MODULE_AUTHOR(DRIVER_AUTHOR);
MODULE_DESCRIPTION(DRIVER_DESC);

static char *mystring; module_param(mystring, charp, 0);
static long *__sys_call_table;

static int HelloInit(void) {

    __sys_call_table = kallsyms_lookup_name("sys_call_table");
    printk(KERN_INFO "Hello freind%s\n", mystring);
    return 0;
}

static void HelloExit(void) {

    printk(KERN_INFO "The short life of km\n");
}

module_init(HelloInit);
module_exit(HelloExit);
