#!/usr/bin/env python

from pkg_resources import parse_version


import dtpcontrols.setup as setup
import dtpcontrols.dpr as dpr
import dtpcontrols.dr as dr
import dtpcontrols.cr as cr
import dtpcontrols.sink as sink
import click
from dtpcontrols.toolbox import dumpSubRegs, printRegTable

CONTEXT_SETTINGS = dict(help_option_names=['-h', '--help'])

dpr_mux_choices = {
    'reset': (0, 0),
    'playback': (0, 1),
    'sink': (1, 0),
    'passthrough': (1, 1)
}


def get_devices(ctx, args, incomplete):
    devs = setup.connectionManager(ctx.params['connection']).getDevices()
    return [k for k in devs if incomplete in k]


extra_autocompl = {'autocompletion': get_devices} if parse_version(click.__version__) >= parse_version('7.0') else {}


@click.command(context_settings=CONTEXT_SETTINGS)
@click.option('-c', '--connection', type=click.Path(exists=True), default=setup.find_conn_file())
@click.argument('device', **extra_autocompl)
@click.option('--init/--no-init', 'init', help='Setup', default=False)
@click.option('--dr-on/--dr-off', 'dr_on', help='Enable data-reception block', default=None)
@click.option('--dpr-mux', 'dpr_mux', type=click.Choice(list(dpr_mux_choices.keys()),), help='Configure DPR mux', default=None)
@click.option('--cr-on/--cr-off', 'cr_on', help='Enable central-router interface block', default=None)
@click.option('--drop-empty/--keep-empty', 'drop_empty', help='Drop empty hit packets', default=None)
@click.option('--sk-on/--sk-off', 'sk_on', help='Enable sinks', default=None)
def cli(connection, device, init, dr_on, dpr_mux, cr_on, drop_empty, sk_on):

    hw = setup.connectionManager(connection).getDevice(str(device))
    hw.setTimeoutPeriod(10000)


    ctrlNode = hw.getNode('ctrl')
    tpgPipeNode = hw.getNode('tpg_pipe')
    drNode = hw.getNode('tpg_pipe.drtr.dr')
    dprNode = hw.getNode('tpg_pipe.drtr.dpr')
    crNode = hw.getNode('tpg_pipe.cr_if')

    magic = ctrlNode.getNode('id.magic').read()
    rev = ctrlNode.getNode('id.revision').read()
    ctrlNode.getClient().dispatch()

    print('magic', hex(magic))
    print('rev  ', hex(rev))


    if init:
        setup.softReset(ctrlNode)

    if cr_on is not None:
        cr.enable(crNode, cr_on)

    if dpr_mux:
        print("Configuring DPR's mux :", dpr_mux)
        dpr.setup(dprNode, *dpr_mux_choices[dpr_mux])

    if drop_empty is not None:
    	cr.drop(crNode, drop_empty)

    if sk_on:
        sink.enable(tpgPipeNode, sk_on)

    if dr_on is not None:
        dr.enable(drNode, dr_on)

    print('--- dr ---')
    regs = dumpSubRegs(drNode)
    printRegTable(regs, False)

    print('--- dpr.csr ---')
    regs = dumpSubRegs(dprNode.getNode("csr"))
    printRegTable(regs, False)

    print('--- cr_if.csr ---')
    regs = dumpSubRegs(crNode.getNode("csr"))
    printRegTable(regs, False)


if __name__ == '__main__':
    cli(complete_var='_HFDRIVER_COMPLETE')
