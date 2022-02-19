# eveyrthing to do with ipbus connection to the device goes here...

import os
import uhal
from ctypes import cdll

def connectionManager(conn_file=os.environ['CONNECTION_FILE']):
    uhal.setLogLevelTo(uhal.LogLevel.WARNING)
    conn_file = "file://"+conn_file
    
    try:
        cdll.LoadLibrary("libuhallibs.so")
        manager = uhal.ConnectionManager(conn_file, ['ipbusflx-2.0'])
    except OSError:
        manager = uhal.ConnectionManager(conn_file)

    return manager


def init(conn_file, device):

    manager = connectionManager(conn_file)

    hw = manager.getDevice(str(device))
    return hw


def softReset(ctrlNode):

    print("Soft reset")
    ctrlNode.getNode("csr.ctrl.soft_rst").write(1)
    ctrlNode.getClient().dispatch()
    csrVal = ctrlNode.getNode("csr.ctrl.soft_rst").read()
    ctrlNode.getClient().dispatch()
    print("CSR value after reset = ", csrVal)

    print("Master reset")
    ctrlNode.getNode("csr.ctrl.mst_rst").write(1)
    ctrlNode.getClient().dispatch()
    ctrlNode.getNode("csr.ctrl.mst_rst").write(0)
    ctrlNode.getClient().dispatch()

