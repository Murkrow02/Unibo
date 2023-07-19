import os
import sys

for file in os.scandir("dir"):
    stats = file.stat()