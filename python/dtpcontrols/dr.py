def enable(drNode, en=True):
    """
    Emables the data-reception block
    """

    drNode.getNode('csr.ctrl.en').write(en)
    drNode.getClient().dispatch()