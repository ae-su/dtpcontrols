from os.path import exists
import time


# kch_idle = 0x1000000BC

# -----------------------------------------------------------------------------
def loadWIBPatternFromFile(path):

    data = []
    with open(path, 'r') as f:
        for l in f:
            tokens = l.split()
            val, ctrl0, ctrl1, ctrl2, ctrl3 = int(tokens[0], 0), int(tokens[1]), int(tokens[2]), int(tokens[3]), int(tokens[4])
            data.append(val + (ctrl0 << 32) + (ctrl1 << 33) + (ctrl2 << 34) + (ctrl3 << 35))
    return data

# -----------------------------------------------------------------------------
def format36bto32b(data):
    pdata = []
    for v in data:
        pdata += [ (v & 0x3ffff) , ((v>>18) & 0x3ffff) ]
   
    return pdata


# -----------------------------------------------------------------------------
def format32bto36b(pdata):

    data = []
    for i in range(0, len(pdata), 2):
        data += [ ((pdata[i+1] & 0x3ffff) << 18) + (pdata[i] & 0x3ffff) ]

    return data


# -----------------------------------------------------------------------------
def getSize(wibNode):
    aw = wibNode.getNode('csr.addr_width').read()
    wibNode.getClient().dispatch()

    return (1<<aw)

# -----------------------------------------------------------------------------
def writePattern(wibNode, pattern):

    # Read buffer address width
    aw = wibNode.getNode('csr.addr_width').read()
    wibNode.getClient().dispatch()

    # Calculate the buffer size in number of 36b-words
    bufSize = 1<<aw
    patt = pattern[:bufSize]
    lp = len(patt)



    print('Writing wibulator pattern (size ', lp, ')')
    
    portedPattern = format36bto32b(patt)
    wibNode.getNode('buf.addr').write(0x0)
    wibNode.getNode('buf.data').writeBlock(portedPattern)
    wibNode.getNode('csr.ctrl.max_word').write(lp-1 if (lp-1 > 0) else 0)
    wibNode.getClient().dispatch()

# -----------------------------------------------------------------------------
def readPattern(wibNode):

    # Read buffer address width
    aw = wibNode.getNode('csr.addr_width').read()
    mw = wibNode.getNode('csr.max_word').read()
    wibNode.getClient().dispatch()

    # Calculate the size in number of 32b-words
    l = 1<<(aw+1)
    # l = wibNode.getNode('buf.data').getSize()
    wibNode.getNode('buf.addr').write(0x0)
    p = wibNode.getNode('buf.data').readBlock(l)
    wibNode.getClient().dispatch()

    return format32bto36b(p)

# -----------------------------------------------------------------------------
def fire(wibNode, n=1, interval=None):

    for i in range(n):

        if i != 0:
            time.sleep(interval)

        wibNode.getNode('csr.ctrl.fire').write(0x1)
        wibNode.getNode('csr.ctrl.fire').write(0x0)
        wibNode.getClient().dispatch()

# -----------------------------------------------------------------------------
def loop(wibNode, loop):
    wibNode.getNode('csr.ctrl.chain').write(loop)
    wibNode.getClient().dispatch()
