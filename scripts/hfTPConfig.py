#!/usr/bin/env python

from pkg_resources import parse_version


import dtpcontrols.setup as setup
import dtpcontrols.sink as sink
from dtpcontrols.toolbox import gen_range_validator

import click

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
@click.argument('pipes', callback=gen_range_validator(0, 4))
@click.option('--mask', callback=gen_range_validator(0, 64), default=None)
@click.option('--sk-on/--sk-off', 'sk_on', help='Enable sinks', default=None)
@click.option('--sk-fifo-mode', 'fifo_mode', type=click.Choice(sink.kFifoModes), help='Select fifo mode', default=None)
@click.option('--sk-ready-mode', 'ready_mode', type=click.Choice(sink.kReadyModes), help='Select ready mode', default=None)
def cli(connection, device, pipes, mask, sk_on, fifo_mode, ready_mode):

    hw = setup.connectionManager(connection).getDevice(str(device))
    hw.setTimeoutPeriod(10000)

    if mask is not None:

        print('Configuring channel masks in pipelines', ', '.join((str(p) for p in pipes)))
        mask_w = 0x0
        for b in mask:
            mask_w |= (1 << b)

        for p in pipes:
            hw.getNode('tpg.sel.chain').write(p)
            hw.getNode('tpg.csr.mask.ch-00-31').write(mask_w & 0xffffffff)
            hw.getNode('tpg.csr.mask.ch-32-63').write((mask_w >> 32) & 0xffffffff)
        hw.dispatch()

        mask_r = []
        for p in pipes:
            hw.getNode('tpg.sel.chain').write(p)
            mask_r += [(
                hw.getNode('tpg.csr.mask.ch-32-63').read(),
                hw.getNode('tpg.csr.mask.ch-00-31').read()
            )]
        hw.dispatch()

        for p, (m_h, m_l) in zip(pipes, mask_r):
            print(p, 'channel mask: 0x%016x' % ((m_h.value() << 32) | m_l.value()))

    if sk_on is not None:
        sink.enable(hw, sk_on)

    if any((fifo_mode, ready_mode)):
        sink.configure(hw, fifo_mode, ready_mode)


if __name__ == '__main__':
    cli(complete_var='_HFDRIVER_COMPLETE')
