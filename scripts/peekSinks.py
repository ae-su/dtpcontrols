#!/usr/bin/env python
import dtpcontrols.setup as setup
import dtpcontrols.dpr as dpr
import dtpcontrols.sink as sink


device = 'flx-1-hf'

hw = setup.connectionManager().getDevice(device)

# setup.softReset(hw)
# dpr.setup(hw, 0, 0)

print("Enable source and sink")

for i in range(4):
    sink.status(hw, i)
sink.enable(hw)

for i in range(4):
    sink.status(hw, i)

