#### Wait for file code from: http://stackoverflow.com/a/21746775/4929236

import os.path
import time
from subprocess import call
import tarfile
### Need to add  way to find job

while not os.path.exists(file_path):
    time.sleep(1)

if os.path.isfile(file_path):
    # read file
    call(["ls", "-l"])
else:
    raise ValueError("%s isn't a file!" % file_path)
