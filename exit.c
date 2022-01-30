#include "header.h"

static void exitMessage_exit (void) {
    printk(KERN_INFO "Short is the life of a kernel module\n");

}

module_exit(exitMessage_exit);