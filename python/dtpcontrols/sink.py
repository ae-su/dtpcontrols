import os

# data sink buffer control and readout


def enable(node, en=True):
    node.getNode("sink0.csr.ctrl.en").write(en)
    node.getNode("sink1.csr.ctrl.en").write(en)
    node.getNode("sink2.csr.ctrl.en").write(en)
    node.getNode("sink3.csr.ctrl.en").write(en)
    node.getClient().dispatch()

kFifoModes = [
    'fifo',
    'capture'
]

kReadyModes = [
    'spy',
    'fifo',
    'force_bsy',
    'force_rdy',
]


def configure(node, fifo_mode, rdy_mode):
    if fifo_mode:
        node.getNode("sink0.csr.ctrl.fifo_mode").write(kFifoModes.index(fifo_mode))
        node.getNode("sink1.csr.ctrl.fifo_mode").write(kFifoModes.index(fifo_mode))
        node.getNode("sink2.csr.ctrl.fifo_mode").write(kFifoModes.index(fifo_mode))
        node.getNode("sink3.csr.ctrl.fifo_mode").write(kFifoModes.index(fifo_mode))
        node.getClient().dispatch()

    if rdy_mode:
        node.getNode("sink0.csr.ctrl.rdy_mode").write(kReadyModes.index(rdy_mode))
        node.getNode("sink1.csr.ctrl.rdy_mode").write(kReadyModes.index(rdy_mode))
        node.getNode("sink2.csr.ctrl.rdy_mode").write(kReadyModes.index(rdy_mode))
        node.getNode("sink3.csr.ctrl.rdy_mode").write(kReadyModes.index(rdy_mode))
        node.getClient().dispatch()

def status(node, sinkNo):
    sCmd = "sink%s.csr.stat" % sinkNo
    print("sCmd = ", sCmd)
    s = node.getNode("sink%s.csr.stat" % sinkNo).read()
    c = node.getNode("sink%s.buf.count" % sinkNo).read()
    node.getClient().dispatch()
    print("Sink status , sink count = ", bin(s), c)
    return sCmd, s, c


def statusAll(node):
    for sinkNo in range(4):
        status(node, sinkNo)


# prints terminal output and adds to a list to be written to a file
def readMessage(line, lines):
    line = str(line)
    print(line)
    lines.append(line)
    return lines


# read data from sinks, outputs in terminal style and saves to file
def readFromSink(node, sinkNo, outtype):
    file = open("output" + str(sinkNo) + "." + outtype, 'w+')
    id = 0
    lines = []
    statArr = status(node, sinkNo)
    sCmd = statArr[0]
    s = statArr[1]
    c = statArr[2]
    lines.append("sCmd = " + sCmd)
    lines.append("Sink status , sink count = " + str(s) + str(c) + os.linesep)
    if s & 0x6 != 0:
        readMessage("Warning - Buffer error", lines)
    if c != 0:
        l = int(c) + 1
        readMessage("l = " + str(l), lines)
        d = node.getNode("sink%s.buf.data" % sinkNo).readBlock(l)
        node.getClient().dispatch()
        readMessage("d = " + str(d), lines)
        di = [int(x) for x in d]
        while l > 6:
            readMessage("Sink %s , Packet:" % sinkNo + str(hex(id)), lines)
            id += 1
            readMessage(
                "\tSink %s , Header:" % sinkNo + str([hex(x) for x in di[:6]]), lines
            )
            del di[:6]
            l -= 6
            p = []
            while True:
                if len(di):
                    r = di.pop(0)
                else:
                    readMessage("Warning - attemping to pop from empty list", lines)
                    l = 0
                    break
                p.append(r)
                if r & 0x10000 != 0:
                    l -= len(p)
                    break
            readMessage(
                "\tSink %s , Payload:" % sinkNo + str([hex(x) for x in p]), lines
            )

    for i in range(0, len(lines)):
        file.write(lines[i] + os.linesep)


# gets raw data from sink ready to convert into 32bit hex
def getFromSink(node, sinkNo, outtype):
    statArr = status(node, sinkNo)
    sCmd = statArr[0]
    s = statArr[1]
    c = statArr[2]
    if s & 0x6 != 0:
        print("Warning - Buffer error")
        # sys.exit()
    # 	elif c != 0:
    if c != 0:
        l = int(c) + 1
        d = node.getNode("sink%s.buf.data" % sinkNo).readBlock(l)
        node.getClient().dispatch()
        di = [int(x) for x in d]
        data = []
        while l > 6:
            h = di[:6]
            del di[:6]
            l -= 6
            p = []
            while True:
                if len(di):
                    r = di.pop(0)
                else:
                    l = 0
                    break
                p.append(r)
                if r & 0x10000 != 0:
                    l -= len(p)
                    break
            compList = [h, p]
            data.append(compList)
        return data
    if c == 0:
        print("ERROR: no data passed to this buffer!")
