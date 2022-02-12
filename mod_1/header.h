#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/moduleparam.h>
#include <linux/kallsyms.h>
#include <linux/unistd.h> //contains syscall names/numbers
#include <linux/version.h>
#include <linux/fs.h>

static int modInit(void);

static void modExit(void);

