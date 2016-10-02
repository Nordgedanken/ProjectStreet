#!/usr/bin/env python

import argparse
from os import environ, makedirs as _makedirs
from os.path import join, exists, basename, dirname, abspath
import yaml
from functools import partial
from subprocess import check_output
from shutil import copy as _copy

#some convenience stuff
rootdir=dirname(abspath(__file__))
sh = lambda cmd: check_output(['sh','-c',cmd])
fmt = partial(lambda s,l: s.format(**l),l=locals())
def download(f):
    tgt=join(args.tmpdir,basename(f))
    sh('wget --progress=bar:force --content-disposition %s -O %s'%(f,tgt))
    return tgt
def makedirs(d):
    if not exists(d): _makedirs(d)
class attrdict(dict):
    def __init__(self,*args,**kwargs):
        super(attrdict, self).__init__(*args, **kwargs)
        self.__dict__ = self
def copy(src,dst,clobber=True):
    if clobber or not exists(dst): _copy(src,dst)

# load and parse options

defaults = yaml.load(open(join(rootdir,'boinc2docker.yml')))
defaults.update({
    'tmpdir':join(rootdir,'build'),
    'projhome':environ.get('PROJHOME')
})

args = [
    ['iso',             'boinc2docker ISO version to use'],
    ['vboxwrapper',     'vboxwrapper version to use'],
    ['projhome',        'project home'],
    ['appname',         'name to give the app'],
    ['appver',          'version to give the app'],
    ['resultsdir',      'where to assimilate results to (default: /results/APPNAME)'],
    ['tmpdir',          "where to store downloaded ISO and vboxwrapper exe's"],
    ['dont_install',    'one or more of ["template_in","template_out","assimilator"'],
]

parser = argparse.ArgumentParser(prog='boinc2docker_create_app')
for a,h in args: 
    if a == 'dont_install':
        parser.add_argument('--'+a, default=[], nargs='+', help=h)
    elif a in defaults:
        parser.add_argument('--'+a, default=defaults[a], help=h+' (default: %s)'%defaults[a])
    else:
        parser.add_argument('--'+a, help=h)
parser.add_argument('boinc2docker.yml', nargs='?', help="boinc2docker.yml file containing confirugation options")
args = attrdict(defaults,**vars(parser.parse_args()))
if args['boinc2docker.yml'] is not None:
    args.update(yaml.load(open(args['boinc2docker.yml'])))
if args.resultsdir is None:
    args.resultsdir = join('/results',args.appname)
if not args.projhome: raise ValueError("Please specify either --projhome option or $PROJHOME variable")
for x in args.dont_install:
    if x not in ['template_in','template_out','assimilator']:
        raise ValueError("Unrecognized argument '%s' given to --dont_install"%x)
approot=join(args.projhome,'apps',args.appname,args.appver)



# create app versions

makedirs(args.tmpdir)
platforms = ["x86_64-pc-linux-gnu","windows_x86_64",  "x86_64-apple-darwin"]
if isinstance(args.vboxwrapper,str):
    args.vboxwrapper = {platform:args.vboxwrapper for platform in platforms}


for platform in platforms:
    appfolder = join(approot,platform+'__cuda')
    makedirs(appfolder)
    vboxwrapper_file = get_vboxwrapper(platform)
    iso_file = get_iso()

    #version.xml
    open(join(appfolder,'version.xml'),'w').write(
        open(join(rootdir,'version.xml')).read().format(vboxwrapper=basename(vboxwrapper_file),iso=basename(iso_file))
    )

    #vboxwrapper and ISO
    copy(vboxwrapper_file,appfolder)
    copy(iso_file,appfolder)
