# configure processing blocks

from . import dpr


def payloadArray(data, addr):

    payload = []
    for configData in data:
        chanPayload = [addr & 0xFFFF]
        chanPayload.append(((addr << 16) & 0x7FFF) + 0x8000)  # set bit 15
        chanPayload.append(len(configData))
        chanPayload = chanPayload + configData
        payload.append(chanPayload)

    print("config payload = ", payload)
    return payload


def configHeader(rw, blockAddr):
    data = []
    data.append(0x0)  # crate, fibre slot number. Don't care about these.
    data.append(blockAddr & 0xFFFF)  # block address
    data.append(0x1 << 48)  # Write to flags bit-0: this is a config packet
    return data


## write a config packet to four processing blocks ( one on each of
## the four chains fed by a fibre )
## All 64 wires handled by the processing block are written
# blockAddr = which block in chain to address ( normally only one block = 0)
# configAddr = address in configuration memory
# data = array of 256 arrays. ( one array per channel ). Each array is the data
# to write
def writeConfig(hw, blockAddr, configAddr, data):

    assert len(data) == 256, "configuration data must be an array of 256 arrays"

    payload = payloadArray(data, configAddr)
    nConfigWords = len(payload[0])
    print("Number of configuration words = ", nConfigWords)

    block = []
    # Assemble a block of 64 WIB frames.
    for wibFrame in range(0, 65):  # 64 WIB frames for config data. 65th to provoke unpacker to activate.

        # First make the header.
        packet = configHeader(1, blockAddr)

        for hdrWord in range(0, 7):
            packet.append(0x0)  # COLDATA - don't care here

        # Now write the payload
        if (
            wibFrame < nConfigWords
        ):  # For the first wibFrames less than nConfigWords pack the 64 bit DPR words with four config words ( one for each pipeline)
            for nChan in range(0, 64):  # loop over the channels in a pipeline
                dprData = 0
                for nPipeline in range(0, 4):  # loop over the 4 pipelines
                    channelNumber = 4 * nChan + nPipeline
                    dprData = dprData + (
                        payload[channelNumber][wibFrame] << (16 * nPipeline)
                    )
                print("Appending wib frame = ", wibFrame, " dpr data = ", hex(dprData))
                packet.append(dprData)

        else:
            packet = packet + (64 * [0x0])  # Pad with zeros

        block = block + packet

    dpr.setup(hw, 0, 1)  # DPR input under IPBus control (bit0 = 0 . DPR output under unpacker control bit1 = 1 )

    print("len(block) , block = ", len(block), block)
    # Write block of 64 WIB packets to DPR
    dpr.write(hw, block)


# This needs fixing....
def readConfig(hw, pipe, chan, addr, data):

    for i in range(0, 63):

        block = configHeader(1, addr)

        while len(block) < 75:
            block.append(0x0)

        dpr.write(hw, block)
