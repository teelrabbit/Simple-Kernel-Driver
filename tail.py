#!/usr/bin/env python

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
