# Simple-Kernel-Driver
### INTRODUCTION 
- A kernel module is a loadable kernel object that is executed directly onto the kernel.
- Kernel modules exist on ring zero [Operating systems typically have 4 rings including '0' ]
###### Understanding the different rings
- Ring 0 is the kernel
- Ring 1 is device drivers
- ring 2 is also used for device drivers
- ring 3 is for applications
-- The ring level has a direct correlation between the application/modules privileges 
## Building module
- use the following commands 
```bash
make 
```
## To install module
```bash
sudo insmod main.ko
```
## To remove module
```bash
sudo rmmod main
```
## Kernel module libary
-- Before starting first it is important to locate some specific locations on your current operating systems 
		- These include your linux kernel module libraries
					-	| These can be typically found in your '/usr/include/linux' directory 
					- 	| Documentation that will be referenced in this section can be found at 
					- 	| https://tldp.org/LDP/lkmpg/2.6/html/lkmpg.html
					
## Tail Script [For syslog/kernel input tracking]
- Simply uses the subprocess lib/module in python to simulate constant user input to track and [use the tail command to follow things loaded onto the kernel] 
```python
#!/usr/bin/env python3.8

import subprocess as sub
import time
import os
import sys

BLUE, RED, WHITE, YELLOW, MAGENTA, GREEN, END = '\33[94m', '\033[91m', '\33[97m', '\33[93m', '\033[1;35m', '\033[1;32m', '\033[0m'

if not os.geteuid() == 0:
    sys.exit(RED + '[-] must be run as root')

runing = 1

def run():
    print(GREEN + "[+] EV LOG >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>" + END)
    sub.run(["tail", "/var/log/syslog"])
    
    

while runing == 1:
    run()
    time.sleep(6)
```
### Using the correct libs 
- When creating your first kennel mod, it is important to use the correct libraries.
###### Header File
- All kernel modules must have a kernel.h lib and a module.h
```c
#include <linux/module.h> //needed by all modules
#include <linux/kernel.h> //needed for KERN_INFO
#include <linux/init.h>   //Needed for macros

```
###### Makefile 
- Makefiles are used as a way of automating the compilation process, they define a set of tasks for your compiler to interpret, and use to compile 
- In our example This makefile takes the object 'main.o'
- What are .o files? '.o' files are known as object files. They contain machine code output from the assembler or compiler. 
```bash
obj-m += main.o

all:

make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules

clean:

make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean
```
###### Main.c
- The "#include" tells the compiler to include the contents of the header file to main when it is being compiled
- The "header.h" file is used to store different library locations using "#include" instead of having them inside of our main file

###### breakdown
- What is a function header? A function header is the first line of a function that establishes the type of function it is (return type), the name, and what type of things it can take in (i.e parameters) ex: "int example(void)"

- "int" is the the return type. Int stand for integer, so we know this function will return a number when it is completed. "example" is the functions name, this will be used later when calling the function. Void is the parameter, the parameters is what the function is capable of taking in. This can be any data type (int, float, double, void etc). In this example the void data type is used.

- What is a Void data type? When void is declared it is actually the representation of no data type. It is often used to show that no parameter of data type is being passed in the function.

- The first function header can be broken down into 3 parts [rerun type, funct name, Parameter]

```c
#include "header.h"

static int exampleInit (void) {
	printk(KERN_INFO "EXAMPLE ENTER\n");
	return 0;
}

static void exampleExit (void) {
	printk(KERN_INFO "Module EXIT");
}

module_init(exampleInit);
module_exit(exampleExit);

MODULE_LICENSE("GPL");
}
```
- The Printk Function 
		- printk is a function used to log information for the kernel or give warnings
		- printk statements come with different levels of priority (there are 8 levels of priority)
		- The priority used in our printk statement is 'KERN_INFO' or '1'. The meanings for these levels are defined in "linux/kernel.h"
		- if a priority level is not specified the default one assigned will be "DEFUALT_ MESSAGE_LOGLEVEL"
		- [NOTE] 
				- The linux/kernel module is responsible for kernel alert function (i.e printk)
				- before typing our example message the priority level is specified using "KERN_INFO"
- The "module_init(exampleInit)" and "module_exit(exampleExit)" are used to signal for the program to use the two functions made above.
*****************************************************
#### Making variables 
- when making variables in a kernel module the macro "__initdata" is used 
```c
static int exampleVar__initdata = 3;
```
- The __initdata is added to the end of the variable (i.e the macro) which will be replaced by the the comelier later with code from the init.h library which defines our macros.
- when added to our code it will look like this:
```c
#include <linux/module.h>	/* Needed by all modules */
#include <linux/kernel.h>	/* Needed for KERN_INFO */
#include <linux/init.h>		/* Needed for the macros */

static int testVar __initdata = 3;

static int __init enterInit(void)
{
	printk(KERN_INFO "Hello, world %d\n", testVar __initdata);
	return 0;
}

static void __exit exitMessage(void)
{
	printk(KERN_INFO "Goodbye, world 3\n");
}

module_init(hello_3_init);
module_exit(hello_3_exit);
```
#### Licensing 
- When making a kernel module licensing is very important. because the device will pickup on the licensing when your km is being ran on the kernel 
- This can be done in our code by using the following macros 
		- MODULE_DESCRIPTION()
		- MODULE_AUTHOR()
		-  MODULE_SUPPORTED_DEVICE()
- First it is important to start with defining the information needed for those macros, this will look like the code bellow 
```c
#define DRIVER_AUTHOR "Peter Jay Salzman <p@dirac.org>"
#define DRIVER_DESC   "A sample driver"

MODULE_AUTHOR(DRIVER_AUTHOR);	/* Who wrote this module? */
MODULE_DESCRIPTION(DRIVER_DESC);	/* What does this module do */

```

### Passing Command Line Arguments | Module Param
- To start using command line input, first you need to use the correct library
- the library you will be using is linux/moduleparam.h 
- the structure when using this library will look similar to whats bellow 
```c 
int myint 3;
module_param(myint, int, 0);
```
- module param uses three different arguments, the first is the variables name, then its corresponding data type, and finally its permission which in this example is 0;
- for arrays it will look like 
```c 
int myintarray[2];
module_param_array(myintarray, int, NULL, 0); /* not interested in count */
```
- The format is name, type, number, and privilege (note that in our example the number is NULL) 
- -This is mainly used to set the permission for the module param, but with out running the command "module_param(examplestr, charp, 0)" the km wil still take userinput when it is being insmod'ed example="insmod main.ko examplestr="example"

### Information on splitting files 
**Example 2-8. start.c**
``` c
/*
 *  start.c - Illustration of multi filed modules
 */

#include <linux/kernel.h>	/* We're doing kernel work */
#include <linux/module.h>	/* Specifically, a module */

int init_module(void)
{
	printk(KERN_INFO "Hello, world - this is the kernel speaking\n");
	return 0;
}

The next file:
```
**Example 2-9. stop.c**
```c
/*
 *  stop.c - Illustration of multi filed modules
 */

#include <linux/kernel.h>	/* We're doing kernel work */
#include <linux/module.h>	/* Specifically, a module  */

void cleanup_module()
{
	printk(KERN_INFO "Short is the life of a kernel module\n");
}

And finally, the makefile:

**Example 2-10. Makefile**

obj-m += hello-1.o
obj-m += hello-2.o
obj-m += hello-3.o
obj-m += hello-4.o
obj-m += hello-5.o
obj-m += startstop.o
startstop-objs := start.o stop.o

all:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules

clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean
```
- This is the complete makefile for all the examples we've seen so far. The first five lines are nothing special, but for the last example we'll need two lines. First we invent an object name for our combined module, second we tell **make** what object files are part of that module.

				
### Modules Vs Programs
- Some things that are universal to all kernel module, normal programs typicaly start with a main() function
- Kernel modules are different in the aspect that they will always start an  end with a module_init and ends with a module_exit or cleanup_module

### checking symbols that have been exported by your kernel
- they can be found in /proc/ kallsyms 
- an example of a symbol exported by the kernel is printk
- these symbols are defined by the kernel and do not come from an external library 
- they are initialized when your km is insmoded, this because kms are object files 
### The difrence between syscalls and  regular functions
- regular functions such s printf exist purely in the user space (ring 3), while system calls exist on the kernel level directly on the behalf of the kernel itself
- all functions like printf do is format data into strings and output them from a lower level syscall like write().

### Things related to the CPU
- Your CPU can run in different modes each mode gives you a different level of freedom, 
- the intell 80386 architecture has 4 modes 
- those 4 modes are called rings 
- unix only uses two rings (ring 0 being the highest 'supervisor mode')
### Name space notes
- When making global varies they become apart of everyone elses list of global variables and cause name space pollution (which i when global  variables of the same name begin causing problems) 
- Ways to combat this is to declare your variables as static and use well define prefix symbols 
- if you would like too avoid declaring everything as static, another option is to create/declare a symbol table

## Checking Module info 
- to check a kernel modules information simply use the command "modinfo example.ko"

### Code space 
- When a process i created, the kernel sets aside a portion of real physical mempory, and it gives it to a process to use for executing code 
- this memory begins with 0x00000000 and extends to whatever it needs 

## Major and Minor numbers
### [IMPOERTANT] If you want to see which major numbers have been assigned, you can look at /usr/src/linux/Documentation/devices.txt. or in /proc/devices
- THESE SCRENSHOTS WERE TAKEN FROM THE DIRECTORY /dev/
![[Pasted image 20220201005729.png]]
***************************************************************
- Major number tell you with drivers are beg used to access the hardware 
- all device files with the same major number are being controlled by the same driver 
- minor numbers is the second number 
- minor numbers distinguishes the between the different hardware it  uses 
So devices files can have the same major number butt may have different minor numbers for the hardware they control 
![[Pasted image 20220201010255.png]]
## Different types of devices
- Devices come in two types, character devices and block devices 
- This can be seen by the first character in the permissions area, it will be a "b" for block and a "c" for character
************************************************
![[Pasted image 20220201010701.png]]
*************************************************
- The major differences between block devices and character devices is the character devices can use s many bits as they need
- block devices can only can buffer or function with fixed block sizes 
- modes devices are character devices 
- - note that when a device file is used the file is acesse by the kernel useing the majhor number, which also means the kernel does not really need to know the minor number

## Making device files
- creating device files can be done with the command 
```bbash
mknod example c 12 2 
```
	- to breakdown the command, mknod is called to create a new device file
	- next is the name of the device file
	- then the device file type which is either a charcter or a block, in this example it is a charcter 
	- lastly the major and minor numbers are established, major being to destinguish the driver and the minor for what peice of hardware the device file is using 
