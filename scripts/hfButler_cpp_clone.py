#!/usr/bin/env python

from __future__ import print_function, absolute_import
from pkg_resources import parse_version

import click
import time
import os
import pprint
from colorama import Fore

import uhal

from dtpcontrols import core as controls

import optionValidators
#INITIALSE---------------------------------------------------------------------

class HFObject(object):
    def __init__(self):
        super(HFObject, self).__init__()

CONTEXT_SETTINGS = dict(help_option_names=['-h', '--help'])

def get_devices(ctx, args, incomplete):
    connection_file = controls.find_connection_file()
    print ("Connection file is : " + connection_file)
    devs = uhal.ConnectionManager(connection_file).getDevices()
    #devs = setup.connectionManager(ctx.params['connection']).getDevices()
    return [k for k in devs if incomplete in k]

extra_autocompl = {'autocompletion': get_devices} if parse_version(click.__version__) >= parse_version('7.0') else {}
pprint.pprint(extra_autocompl)
@click.group(context_settings=CONTEXT_SETTINGS, invoke_without_command=True)
@click.option('-e', '--exception-stack', 'aExcStack', is_flag=True, help="Display full exception stack")
@click.option('-c', '--connection', type=click.Path(exists=True), default=controls.find_connection_file()[6:])
@click.argument('device', **extra_autocompl)
@click.pass_context
@click.version_option(version='ultimate')
def cli(ctx, aExcStack, connection, device):
    obj = ctx.obj
    obj.mPrintExceptionStack = aExcStack
    hw = uhal.ConnectionManager("file://"+connection).getDevice(str(device))
    hw.setTimeoutPeriod(10000)
    obj.mHW = hw
    obj.podNode = hw.getNode()
    # Extract info from InfoNode
    infoNode = obj.podNode.get_info_node()
    config_info = infoNode.get_firmware_config_info()
    id_info = infoNode.get_firmware_id_info()

    pprint.pprint(config_info)
    pprint.pprint(id_info)
    
    obj.mIdInfo = config_info
    obj.mConfigInfo = id_info

# -----------------------------------------------------------------------------
@cli.command('init')
@click.pass_obj
def init(obj):
    obj.podNode.reset()
    print(Fore.YELLOW + "\n RESET DONE!!")
    print(Fore.GREEN + "\n Initilisation complete.")
    print(Fore.RESET) #reset to normal colour

# Command group link------------------------------------------------------------
@cli.group('link', invoke_without_command=True)
@click.option('-i', '--ids', default='all', callback=optionValidators.validate_link_ids)
@click.pass_obj
def link(obj, ids):
    """
    Partition specific commands

    ID: Id of the selected partition
    """
    obj.mLinkIds = ids
    try:
        obj.mLinkNodes = [obj.podNode.getNode('linkproc{}'.format(i)) for i in ids]
    except Exception as lExc:
        click.Abort('Wibulator {} not found in address table'.format(id))

dpr_mux_choices = {
    'reset': (0, 0),
    'playback': (0, 1),
    'sink': (1, 0),
    'passthrough': (1, 1)
}

# ------------------------------------------------------------------------------
    

#MAIN-------------------------------------------------------------------------

if __name__ == '__main__':
    cli(obj=HFObject(), complete_var='_HFBUTLER_COMPLETE')
