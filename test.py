# -*- coding: utf-8 -*-
from numba import jit, cuda, vectorize
from random import random

@cuda.jit
def main():
    v = 0.0
    w = 1.0
    for i in range(10000000):
        v += w
        if v > 30:
            v = 0.0
            w += 0.01
            w -= 0.01
    print(v, w)

#@cuda.jit
@vectorize('float32(float32, float32)', target='cuda')
def test(a, b):
    return a + b


if __name__ == '__main__':
    main()
    #print(test(1, 2))
