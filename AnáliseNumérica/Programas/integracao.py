import numpy as numpy

def function(Y,R,S0,B):
    return Y * (1 - R - S0 * numpy.exp(R * - B / Y))
#################################################################IMPLEMENTAÇÃO DE HEUN
def Heun(h):
    Y, B, r0, x0 = 0.4, 0.8, 0, 0.1
    X = x0
    R = r0
    Fxy = function(Y, R + (h / 2) * function(Y, R, 0.8, B), 0.8 + (h / 2), B)
    i = 1;
    for j in range(0, 3):
        while X < 40 * (j + 1):
            X = x0 + h * i
            R += h * Fxy
            Fxy = function(Y, R + (h / 2) * function(Y, R, 0.8, B), 0.8 + (h / 2), B)
            i += 1
        print(40 * (j + 1))
        print(R)
        S = 0.8 * numpy.exp(R * - B / Y)
        print(S)
        X = 1 - R - S
        print(X)
    print("\n")

################################################################IMPLEMENTAÇÃO DE EULER
def Euler(h):
    Y, B, r0, x0 = 0.4, 0.8, 0, 0.1
    X = x0
    R = r0
    Fxy = function(Y, R, 0.8, B)
    i = 1;
    for j in range(0,3):
        while X < 40 * (j + 1):
            X = x0 + h * i
            R += h * Fxy
            Fxy = function(Y, R, 0.8, B)
            i += 1
        print(40 * (j + 1))
        print(R)
        S = 0.8 * numpy.exp(R * - B / Y)
        print(S)
        X = 1 - R - S
        print(X)
    print("\n")

Euler(0.1)
Heun(0.1)
Euler(0.05)
Heun(0.05)
