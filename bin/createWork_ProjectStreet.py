#### Wait for file code from: http://stackoverflow.com/a/21746775/4929236

import os.path
import time
from subprocess import call
import tarfile
import zstandard
### Need to add  way to find job

dctx = zstd.ZstdDecompressor()

while not os.path.exists(file_path):
    time.sleep(1)

if os.path.isfile(file_path):
    # read file
    call(["ls", "-l", file_path])
    decompressed = dctx.decompress(data)
else:
    raise ValueError("%s isn't a file!" % file_path)
