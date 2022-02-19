#!/usr/bin/env python

from future.utils import raise_from
from future.utils import iterkeys, itervalues, iteritems
from pkg_resources import parse_version

import click
import dtpcontrols.setup as setup
import dtpcontrols..dpr as dpr
from dtpcontrols.toolbox import dumpSubRegs, readTpgStatus, readSinkStatus, printRegTable
CONTEXT_SETTINGS = dict(help_option_names=['-h', '--help'])


def get_devices(ctx, args, incomplete):
    devs = setup.connectionManager(ctx.params['connection']).getDevices()
    return [k for k in devs if incomplete in k]

extra_autocompl = {'autocompletion': get_devices} if parse_version(click.__version__) >= parse_version('7.0') else {}


# -----------------------------------------------------------------------------
@click.command(context_settings=CONTEXT_SETTINGS)
@click.option('-c', '--connection', type=click.Path(exists=True), envvar='CONNECTION_FILE')
@click.argument('device', **extra_autocompl)
@click.option('-r/-R', '--show-dr/--hide-dr', 'dr', default=True)
@click.option('-b/-B', '--show-dpr/--hide-dpr', 'dpr', default=True)
@click.option('-t/-T', '--show-tpg/--hide-tpg', 'tpg', default=True)
@click.option('-s/-S', '--show-spies/--hide-spies', 'sp', default=True)
@click.option('-c/-C', '--show-cr/--hide-cr', 'cr', default=True)
def cli(connection, device, dr, dpr, tpg, cr, sp):

    hw = setup.connectionManager(connection).getDevice(str(device))
    hw.setTimeoutPeriod(10000)


    ctrlNode = hw.getNode('ctrl')
    drNode = hw.getNode('tpg_pipe.drtr.dr')
    dprNode = hw.getNode('tpg_pipe.drtr.dpr')
    tpgNode = hw.getNode('tpg_pipe.tpg')
    crNode = hw.getNode('tpg_pipe.cr_if')

    if dr:
        print('--- dr ---')
        regs = dumpSubRegs(drNode)
        printRegTable(regs, False)

    if dpr:
        print('--- dpr.csr ---')
        regs = dumpSubRegs(dprNode.getNode("csr"))
        printRegTable(regs, False)

    if tpg:
        print(readTpgStatus(tpgNode))
    
        for i in range(4):
            tpgNode.getNode('sel.chain').write(i)
            ch0031 = tpgNode.getNode('csr.mask.ch-00-31').read()
            ch3263 = tpgNode.getNode('csr.mask.ch-32-63').read()
            tpgNode.getClient().dispatch()

            print(i, hex((ch3263 << 32)+ch0031))

    if sp:
        print('--- spies ---')
        print(readSinkStatus(hw.getNode('tpg_pipe')))
    
    if cr:
        print('--- cr_if ---')
        regs = dumpSubRegs(crNode)
        printRegTable(regs, False)




if __name__ == '__main__':
    cli(complete_var='_HFWATCHER_COMPLETE')
