#!/usr/bin/env python
import dtpcontrols.setup as setup
import dtpcontrols.sink as sink
import click
from pkg_resources import parse_version

from dtpcontrols.toolbox import readSinkStatus

CONTEXT_SETTINGS = dict(help_option_names=['-h', '--help'])

def dump_regs(node):
    regs = {}
    for i in sorted(node.getNodes()):
        regs[i] = node.getNode(i).read()
    # pkt_ctr = hw.getNode("dpr.csr.stat.wib_frame_ptr_r").read()
    node.getClient().dispatch()

    return {k: v.value() for k, v in regs.items()}


def get_devices(ctx, args, incomplete):
    devs = setup.connectionManager(ctx.params['connection']).getDevices()
    return [k for k in devs if incomplete in k]


extra_autocompl = {'autocompletion': get_devices} if parse_version(click.__version__) >= parse_version('7.0') else {}


@click.command(context_settings=CONTEXT_SETTINGS)
@click.option('-c', '--connection', type=click.Path(exists=True), envvar='CONNECTION_FILE')
@click.argument('device', **extra_autocompl)
@click.argument('step', type=click.Choice(['reset', 'config', 'flush']))
def cli(connection, device, step):

    hw = setup.connectionManager(connection).getDevice(str(device))
    hw.setTimeoutPeriod(10000)

    if step == 'reset':
        sink.enable(hw, False)
        sink.enable(hw, True)

    elif step == 'config':
        # Fifo mode: 0 = sink
        #            1 = capture

        hw.getNode("sink0.csr.ctrl.fifo_mode").write(1)
        # hw.getNode("sink1.csr.ctrl.fifo_mode").write(0)
        # hw.getNode("sink2.csr.ctrl.fifo_mode").write(0)
        # hw.getNode("sink3.csr.ctrl.fifo_mode").write(0)

        # rdy mode: 0 = upstream
        #           1 = fifo
        #           2 = force low
        #           3 = force high
        #
        hw.getNode("sink0.csr.ctrl.rdy_mode").write(1)
        # hw.getNode("sink1.csr.ctrl.rdy_mode").write(1)
        # hw.getNode("sink2.csr.ctrl.rdy_mode").write(1)
        # hw.getNode("sink3.csr.ctrl.rdy_mode").write(1)
        hw.dispatch()

    elif step == 'flush':
        s0 = hw.getNode("sink0.buf.data").readBlock(1024)
        # s1 = hw.getNode("sink1.buf.data").readBlock(10)
        # s2 = hw.getNode("sink2.buf.data").readBlock(10)
        # s3 = hw.getNode("sink3.buf.data").readBlock(10)
        hw.dispatch()

        print(s0)
        # print s1
        # print s2
        # print s3

    print('--- sinks ---')
    print((readSinkStatus(hw.getNode())))


if __name__ == '__main__':
    cli()
