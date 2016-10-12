##### Generates automticly work (Run as daemon as needed)
from Boinc import boinc_project_path
import os
from docker import Client

cli = Client(base_url='unix://var/run/docker.sock')
RawData = os.path.join(boinc_project_path, 'rawData')

if os.listdir(RawData):




def addFiles():
    files = sorted(os.listdir(RawData), key=os.path.getctime)
    oldest = files[0]
    try:
      container = cli.start(image='mtrnord/projectstreet_detection:latest', command='/bin/sleep 300')
      container_ID = container["Id"]
    
    else:
      print "something wrent wrong"
