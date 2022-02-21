# all the DPR control stuff goes here.....

# Set up input and output Mux ( 1 = IPBus control )
# def setupDPRMux(dprNode,input_ctl , output_ctl):
def setup(dprNode, mux_in, mux_out):
    status = 0
    dprNode.getNode("csr.ctrl.config.mux_in").write(mux_in)
    dprNode.getNode("csr.ctrl.config.mux_out").write(mux_out)
    # dprNode.getNode("config").write(mux_ctl^0b11)
    # dprNode.getNode("config.input_ctl").write(input_ctl & 0x00000001)
    # dprNode.getNode("config.output_ctl").write( (output_ctl<<1) & 0x00000002)
    dprNode.getClient().dispatch()

    return status


# Writes a 64-bit word to DPR
# N.B. Make sure that Mux is set to access write port from IPBus
def writeDprLongLongWord(dprNode, address, data):
    status = 0

    dprNode.getNode("csr.ctrl.write_data_low").write(data & 0xFFFFFFFF)
    dprNode.getNode("csr.ctrl.write_data_high").write((data >> 32) & 0xFFFFFFFF)
    dprNode.getNode("csr.ctrl.write_addr").write(address)
    dprNode.getClient().dispatch()

    return status


# Read a 64-bit word to DPR
# N.B. Make sure that Mux is set to access write port from IPBus
def readDprLongLongWord(dprNode, address):
    status = 0

    dprNode.getNode("csr.ctrl.read_addr").write(address)
    dprNode.getClient().dispatch()  # set up read address. Put as separate dispatch to allow for read latency

    data_low = dprNode.getNode("csr.stat.read_data_low").read()
    data_high = dprNode.getNode("csr.stat.read_data_high").read()
    dprNode.getClient().dispatch()

    # print "low = " , hex(data_low)
    # print "high = ", hex(data_high)
    return data_low + (data_high << 32)


def writeWibPtr(hw, ptr_to_write):
    print("Writing %x to WIB frame pointer" % ptr_to_write)
    hw.getNode("csr.ctrl.wib_frame_ptr_w").write(ptr_to_write)
    hw.dispatch()


def write(hw, data):
    print("Writing data to DPR")
    nwordsInFrame = 75
    previousWIBFrame = -1

    for addr in range(len(data)):
        wibFrame = addr / nwordsInFrame
        word = data[addr]
        if wibFrame != previousWIBFrame:
            print("New Frame")
            writeWibPtr(hw, wibFrame)

        # print hex(addr), hex(word), hex(wibFrame)
        writeDprLongLongWord(hw, addr, word)
        previousWIBFrame = wibFrame
