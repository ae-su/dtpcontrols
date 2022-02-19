#!/usr/bin/env python

from pkg_resources import parse_version


import click
import dtpcontrols.setup as setup
import dtpcontrols.wibulator as wibulator
import time
import uhal

from dtpcontrols.toolbox import dumpReg, dumpSubRegs, printRegTable


CONTEXT_SETTINGS = dict(help_option_names=['-h', '--help'])

def get_devices(ctx, args, incomplete):
    devs = setup.connectionManager(ctx.params['connection']).getDevices()
    return [k for k in devs if incomplete in k]

extra_autocompl = {'autocompletion': get_devices} if parse_version(click.__version__) >= parse_version('7.0') else {}

@click.command(context_settings=CONTEXT_SETTINGS)
@click.option('-c', '--connection', type=click.Path(exists=True), envvar='CONNECTION_FILE')
@click.argument('device', **extra_autocompl)
# Flowswitch
@click.option('--src-sel', type=click.Choice(['gbt', 'wibtor']), help='Input source selection', default=None)
@click.option('--sink-sel', type=click.Choice(['tpg', 'gbt']), help='Sink input selection', default=None)
# Wibulator
@click.option('-p', '--pattern', type=click.Path(exists=True), help='Pattern file path', default=None)
@click.option('-t', '--trim-length', type=int, help='Trim pattern length', default=None)
@click.option('-i', '--pad-idles', is_flag=True, help='Pad pattern with idles', default=None)
@click.option('-f', '--fire', is_flag=True, help='Start playback', default=None)
@click.option('-l/-s', '--loop/--single', help='Configure loop mode', default=None)
# b33 sink
@click.option('-c','--capture', is_flag=True, help='Capture from b33sink', default=None)
@click.option('--cap-path', type=click.Path(exists=False), help='Capture file path', default='b33_dump.txt')
@click.option('--cap-timeout', type=float, help='Capture timeout', default=10)
@click.option('--drop-idles', is_flag=True, help='Drop idle words', default=None)


def cli(connection, device, src_sel, sink_sel, pattern, trim_length, pad_idles, fire, loop, capture, cap_path, cap_timeout, drop_idles):

    hw = setup.connectionManager(connection).getDevice(str(device))
    hw.setTimeoutPeriod(100000)


    wibtorNode = hw.getNode('wibtor')

    try:
        b33sinkNode = hw.getNode('b33sink')
    except:
        b33sinkNode = None

    try:
        flowmasterNode = hw.getNode('flowmaster')
    except:
        flowmasterNode = None

    # Flowswitch
    if any((x is not None) for x in (src_sel, sink_sel)):
        if flowmasterNode is None:
            print('ERROR: no flowmaster in this desing')
        else:
            src_map = {'gbt': 0, 'wibtor': 1}
            sink_map = {'tpg': 0, 'gbt':1 }

            if src_sel:
                flowmasterNode.getNode('csr.ctrl.gbt_src').write(src_map[src_sel])
            if sink_sel is not None:
                flowmasterNode.getNode('csr.ctrl.sink_src').write(sink_map[sink_sel])
            flowmasterNode.getClient().dispatch()



    # Wibulator bit
    if not pattern is None:
        
        p = wibulator.loadWIBPatternFromFile(pattern)

        print('Pattern file:', pattern)
        print('      length:', len(p))

        if trim_length is not None:
            print('Trimming pattern to length', trim_length)
            p = p[:trim_length]
        if pad_idles:
            print('Padding pattern with idles')

            kch_idle = 0x1000000BC

            wSize = wibulator.getSize(wibtorNode)

            if len(p) < wSize:
                p += [kch_idle]*(wSize-len(p))
    # 
        wibulator.writePattern(wibtorNode, p)

    if not loop is None:
        wibulator.loop(wibtorNode, loop)
        
    if not fire is None:
        wibulator.fire(wibtorNode)


    # b33Sink bit
    if capture:
        if b33sinkNode is None:
            print('ERROR: capture skipped. B33 sink not found')
        else:
            print('Capturing b33sink data')
            b33sinkNode.getNode('csr.ctrl.en').write(0)
            b33sinkNode.getNode('csr.ctrl.clear').write(1)
            b33sinkNode.getNode('csr.ctrl.clear').write(0)
            if drop_idles:
                b33sinkNode.getNode('csr.pattern_kchar').write(0x1)
                b33sinkNode.getNode('csr.pattern_data').write(0xbc)
                b33sinkNode.getNode('csr.ctrl.filter').write(0x1)
            else:
                b33sinkNode.getNode('csr.pattern_kchar').write(0x0)
                b33sinkNode.getNode('csr.pattern_data').write(0x0)
                b33sinkNode.getNode('csr.ctrl.filter').write(0x0)
            b33sinkNode.getClient().dispatch()
            b33sinkNode.getNode('csr.ctrl.en').write(1)
            b33sinkNode.getClient().dispatch()

            sleep = 0.1
            max_iter = int(cap_timeout//sleep)
            for i in range(max_iter):
                full = b33sinkNode.getNode('csr.stat.full').read()
                count = b33sinkNode.getNode('buf.count').read()
                b33sinkNode.getClient().dispatch()
                if full.value():
                    break
                print("FIFO counts",int(count))
                if i == (max_iter - 1):
                    print('Capture Timeout!!!')
                time.sleep(sleep)

            b33sinkNode.getNode('csr.ctrl.en').write(0)
            count = b33sinkNode.getNode('buf.count').read()
            b33sinkNode.getClient().dispatch()


            print('Reading out %s frames' % count)
            d = b33sinkNode.getNode('buf.data').readBlock(2*int(count))
            b33sinkNode.getClient().dispatch()
            data = [((w >> 32) & 0x1, w & 0xffffffff) for w in wibulator.format32bto36b(d)]
            with open(cap_path, 'w') as lFile:
                for i, (k, d) in enumerate(data):
                    lFile.write('0x{1:08x} {0}\n'.format(k, d)) 
                    print ('%04d' % i, k, '0x%08x' % d)


    time.sleep(1)

    print('WIBulator registers')
    regs = dumpSubRegs(wibtorNode)
    printRegTable(regs, False)

    if b33sinkNode:
        print('b33 sink regs')
        # regs = dumpSubRegs(b33sinkNode)
        regs = dumpSubRegs(b33sinkNode.getNode('csr'))
        # This contraption is to avoid reading the fifo
        regs.update(dumpReg(b33sinkNode.getNode('buf.count')))
        printRegTable(regs, False)

    if flowmasterNode:
        print('flowmaster regs')
        regs = dumpSubRegs(flowmasterNode)
        printRegTable(regs, False)

if __name__ == '__main__':
    cli(complete_var='_HFWIBULATOR_COMPLETE')
