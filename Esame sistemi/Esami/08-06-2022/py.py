import os
import sys
uid = os.getuid()
user_procs = []

def printMemory(file, name):
    for line in f:
        if line.startswith("VmSize"):
            print(name + line.removeprefix("VmSize"))


for file in os.scandir("/proc"):

    #This process is not owned by uid
    if file.stat().st_uid != uid:
        continue

    #This process is owned by uid
    status_path = file.path + "/status"
    if os.path.exists(status_path):
        f = open(status_path,'r')
        printMemory(f, file.name);
    #print(file.name + "\t" + file.path)


