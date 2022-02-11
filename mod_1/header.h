#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/moduleparam.h>
#include <linux/kallsyms.h>
#include <linux/unistd.h> //contains syscall names/numbers

static int modInit(void);

static void modExit(void);

