def enable(crNode, en=True):
    """
    Enables the cr_interface block
    """

    crNode.getNode('csr.ctrl.en').write(en)
    crNode.getNode('csr.ctrl.drop_empty').write(en)
    crNode.getClient().dispatch()

def drop(crNode, en=True):
    """
    drop empty packets block
    """

    crNode.getNode('csr.ctrl.drop_empty').write(en)
    crNode.getClient().dispatch()

def sink(crNode, en=True):
    """
    sink mode control
    """

    crNode.getNode('csr.ctrl.sink').write(en)
    crNode.getClient().dispatch()
