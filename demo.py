# -*- coding: utf-8 -*-
"""
Created on Mon Apr 23 13:26:05 2018

@author: zx013
"""

import os
import struct
import pickle
import numpy as np
import matplotlib.pyplot as plt
from brian2 import *

MNIST_data_path  = 'data/'

def get_labeled_data(test):
    if test:
        picklename = 'test.pickle'
    else:
        picklename = 'train.pickle'

    if os.path.isfile(picklename):
        data = pickle.load(open(picklename, 'rb'))
    else:
        if test:
            images = open(MNIST_data_path + 't10k-images.idx3-ubyte', 'rb')
            labels = open(MNIST_data_path + 't10k-labels.idx1-ubyte', 'rb')
        else:
            images = open(MNIST_data_path + 'train-images.idx3-ubyte', 'rb')
            labels = open(MNIST_data_path + 'train-labels.idx1-ubyte', 'rb')

        images.read(4)
        num = struct.unpack('>I', images.read(4))[0]
        rows = struct.unpack('>I', images.read(4))[0]
        cols = struct.unpack('>I', images.read(4))[0]

        labels.read(4)
        N = struct.unpack('>I', labels.read(4))[0]

        if num != N:
            raise Exception('Error')

        x = np.zeros((N, rows, cols), dtype=np.uint8)
        y = np.zeros((N, 1), dtype=np.uint8)

        for i in range(N):
            x[i] = [[struct.unpack('>B', images.read(1))[0] for col in range(cols)] for row in range(rows)]
            y[i] = struct.unpack('>B', labels.read(1))[0]
        data = {'x': x, 'y': y, 'rows': rows, 'cols': cols}

        pickle.dump(data, open(picklename, 'wb'))

if __name__ == '__main__':
    get_labeled_data(True)