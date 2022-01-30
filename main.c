#include "header.h"

#define DESCRIPTON "simple kernel module"
#define AUTHOR "John Reich"

static int testVar__initdata = 3;
static char *mystring;

module_param(mystring, charp, 0000);
MODULE_PARM_DESC(mystring, "A test string");

static int enterInt_init (void) {
    printk(KERN_INFO "TEST INER %d \n", testVar__initdata);
    printk(KERN_INFO "TEST STRING ARG:: %s", mystring);
    return 0;
}



module_init(enterInt_init);


MODULE_LICENSE("GPL");

MODULE_DESCRIPTION(DESCRIPTON);
MODULE_AUTHOR(AUTHOR);
//MODULE_SUPPORTED_DEVICE('linux 5.13.0-27-generic');