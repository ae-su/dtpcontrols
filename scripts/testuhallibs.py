import os
import uhal
from ctypes import cdll

def connectionManager(conn_file=os.environ['CONNECTION_FILE']):
    uhal.setLogLevelTo(uhal.LogLevel.WARNING)
    conn_file = "file://"+conn_file
    
    cdll.LoadLibrary("libuhallibs.so")
    manager = uhal.ConnectionManager(conn_file, ['ipbusflx-2.0'])

    return manager

cm = connectionManager("/users/phjjb/dune/daq/workDir/sourcecode/dtpcontrols/config/etc/connections.xml")
