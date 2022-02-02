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
				
