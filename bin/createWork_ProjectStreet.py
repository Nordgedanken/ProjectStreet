#!/usr/bin/env python
##### Generates automticly work (Run as daemon as needed)
from Boinc import boinc_project_path
import os
import docker
import argparse

parser = argparse.ArgumentParser()
parser.add_argument('--last_wu_results', type=string,
                    help='Path to the resultds of the last wu')
parser.add_argument('--last_wu_id', type=string,
                    help='last wu_ID')
parser.add_argument('--last_stage', type=string,
                    help='last wu_stage')

args = parser.parse_args()
cli = docker.Client(base_url='unix://var/run/docker.sock')
RawData = os.path.join(boinc_project_path, 'rawData')
boinc2docker = os.path.join(boinc_project_path, 'bin', 'boinc2docker_create_work.py')
def analyse():
    if os.listdir(RawData):
        files = sorted(os.listdir(RawData), key=os.path.getctime)
        oldest = files[0]
        last_wu_results = args.last_wu_results
        last_wu_id = args.last_wu_id
        last_stage = args.last_stage
        if last_stage:
            if last_stage == "1"
                addFiles([last_wu_results], last_wu_id)
                os.system(boinc2docker + '--rsc_fpops_est 90000e15 --delay_bound 1.21e+6 mtrnord/projectstreet_detection:' + last_wu_id + ' sh -c "echo "2" >> /root/shared/results/stage.txt && ./stage2_generateHaarDetector.sh 2>&1 | tee /root/shared/results/logs.txt"')
            if last_stage == "2"
                addFiles([last_wu_results], last_wu_id)
                addFiles(None, last_wu_id, os.path.join(RawData, oldest))
                os.system(boinc2docker + '--rsc_fpops_est 90000e15 --delay_bound 1.21e+6 mtrnord/projectstreet_detection:' + last_wu_id + ' sh -c "echo "3" >> /root/shared/results/stage.txt && ./stage3_analyseVideo.py 2>&1 | tee /root/shared/results/logs.txt"')
                if not os.path.exists(os.path.dirname(os.path.join(RawData, 'old'))):
                try:
                    os.makedirs(os.path.dirname(os.path.join(RawData, 'old')))
                except OSError as exc: # Guard against race condition
                    if exc.errno != errno.EEXIST:
                        raise
                os.rename(os.path.join(RawData, oldest), os.path.join(RawData, "old", oldest))
        else:
            os.system(boinc2docker + '--rsc_fpops_est 90000e15 --delay_bound 1.21e+6 mtrnord/projectstreet_detection:latest sh -c "echo "1" >> /root/shared/results/stage.txt && ./stage1_getNeg.sh 2>&1 | tee /root/shared/results/logs.txt"')
                    
                    
def make_tree(dirs, files):
    #### Function comes from: https://github.com/docker/docker-py/blob/master/tests/helpers.py#L10-L20
    base = tempfile.mkdtemp()

    for path in dirs:
        os.makedirs(os.path.join(base, path))

    for path in files:
        with open(os.path.join(base, path), 'w') as f:
            f.write("content")

    return base

def addFiles(last_wu_results, last_wu_id, files):
    try:
        base = helpers.make_tree(last_wu_results, files)
        container = cli.create_container(image='mtrnord/projectstreet_detection:latest', command='/bin/sleep 300', volumes=['/vol1'])
        with docker.utils.tar(base) as tarFile:
            cli.put_archive(container, '/vol1', tarFile)
        cli.commit(container=container, tag=last_wu_id)    
    else:
        print "something wrent wrong"
