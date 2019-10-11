#!/usr/bin/python
# -*- coding: utf-8 -*-
import numpy as np
import sys

# Global variable base, indicates the basis of PL
base = {} # Coordinates of the base matrix
solution = {} # If it is unlimited, feasible
epsilon = np.finfo(float).eps * 1000000
canonical = False # Global variable that holds if the fpi is canonical

def equalZero(num): # Identifies whether the number is small enough to be considered zero
    return num < epsilon and num > -epsilon

def ReadArq(filename): # Reads the input
    arq = open(filename, 'r')
    text = arq.readlines() # Split the file by lines
    finalText = []
    for line in text: # Split the lines by numbers and symbols
        finalText.append(line.split(" "))

    arq.close()
    return finalText # Return a variable with the file splitted

def FPI(text):
    varNum = int(text[0][0]) # Integer number of variables
    maxi = 4 + int(text[1][0]) # Integer number os lines in the file
    equali = 0 # Non-equality restrictions number
    tam = int(text[1][0]) +2 # Column number
    tableau = np.zeros((int(text[1][0]),(varNum + 2))) # Create a matrix to receive the PL restrictions filled with zeros
    i = 0
    while i < maxi: # Runs the file lines
        j = 0 # Find the file positions with the restrictions
        k= i - 4
        while j < (varNum + 2): # Fill the restriction column with 0's
            if k >= 0:
                if text[i][j] in [">=", "<="]:
                    tableau[k][j] = 0
                    equali += 1
                elif text[i][j] in ["=="]:
                    tableau[k][j] = 0
                else:
                    tableau[k][j] = float(text[i][j]) # Store the numbers

            j +=1
        i += 1
    sol = np.zeros((1,(varNum + 2))) # Creates a matrix[1][varNum+2] filled with zeros
    sol[0][varNum+1] # CHANGE
    i = 0
    while i < (varNum + 2):
        if i < varNum:
            sol[0][i] = -(float(text[3][i])) # Put the values in the sol matrix
        i += 1

    sol = np.array(sol)
    tableau = np.concatenate((sol, tableau), axis=0) # Concatenate sol with matrix
    tableau1 = tableau[:, 0:varNum] # Divide the PL in two parts
    tableau2 = tableau[:, varNum+1:varNum+2]
    iden = np.zeros((int(text[1][0]),equali))
    b = np.zeros((1,equali))
    i = 0
    j = 0
    basis = 0
    while i < int(text[1][0]):
        if text[i+4][varNum] in [">=", "<="]:
                if text[i+4][varNum] == ">=": # If it is >= put -1
                    iden[i][j] = -1
                    j += 1
                else: # If it is <= put 1
                    iden[i][j] = 1
                    basis += 1 # Hold the number of <= , to identify canonical fpi
                    j += 1
        i += 1

    if basis == int(text[1][0]):
        canonical = True

    iden = np.concatenate((b, iden), axis=0)
    tableau = np.concatenate((tableau1, iden,tableau2), axis=1)

    # Non-equality restrictions FPI problem resolved
    tam+=(equali-1) # Number of column after equality restrictions FPI problem be solved
    i = 0
    offset = 0
    while i < varNum:
        if int(text[2][i]) == 0:
            tableau = np.insert(tableau, offset+1, tableau[:,offset]*-1, axis=1)
            offset += 1

        offset += 1
        i += 1

    # Non-negative restrictions FPI problem solved

    # Matrix shape
    lin = tableau.shape[0]
    col = tableau.shape[1]

    # Multiply by -1 if b is negative
    i = 1
    while i < lin:
        if tableau[i][col-1] < 0:
            tableau[i] = tableau[i,:] * -1
        i += 1

    return tableau

def PLAux(PL): # Creates the auxiliar PL
    lin = PL.shape[0]
    col = PL.shape[1]
    iden = np.concatenate((np.full((1,(lin -1)), -1),np.eye((lin-1))), axis = 0)
    PL = np.concatenate( (np.zeros((1,col))  , PL[1:lin,:]), axis = 0)
    PL = np.concatenate((PL[:,0:(col-1)] , iden ,PL[:,(col-1):col]), axis = 1)

    return PL

def PLA(PL): # Sum all the lines in the first lines and multiply by -1
    lin = PL.shape[0]
    col = PL.shape[1]

    i = 0
    while i < col:
        PL[0][i] = np.sum((PL[:,i] * -1), axis = 0)
        i += 1

    # Define the new base matrix in the global variable
    i = 1
    while i < lin:
        base[i]= (col - (lin - 1) - 2 + i)
        i += 1

    return PL

def pivot(PL, pivoi , pivoj): # Pivots matrix
    i = 0
    lin = PL.shape[0]
    col = PL.shape[1]
    mult =np.zeros((1,lin))
    while i < lin: # Calculates de each line multipliers
        mult[0][i]= (-( PL[i][pivoj]/ PL[pivoi][pivoj]) )
        i += 1
    i = 0
    j = 0
    while i < lin: # Runs the loop through the lines
        j = 0
        while j < col: # Runs the loop through the columns
            if i != pivoi: # If it is not the pivot line, operate
                PL[i][j] += mult[0][i] * PL[pivoi][j]
            j += 1

        i += 1

    i= pivoi
    j = 0
    div = PL[pivoi][pivoj] # Calculates the pivot multiplier
    while j < col: # Runs the loop through teh column of the pivot line, operate
        PL[i][j] /= div
        j += 1
    base[pivoi] = pivoj # Store the new base matrix
    return PL

def simplex(PL): # Run one time through the columns
    i = 0
    lin = PL.shape[0]
    col = PL.shape[1]


    while i < (col-1):
        if PL[0][i] < 0:
            menorRazao = -1
            pivoi = -1
            pivoj = -1
            j = 1

            while j < lin:
                if PL[j][i] <= epsilon:
                    j += 1
                    continue
                else:
                    razao = PL[j][col-1]/PL[j][i]

                if menorRazao == -1 or menorRazao - razao > 0 and razao >= 0:
                    menorRazao = razao
                    pivoi = j
                    pivoj = i

                j += 1

            if menorRazao >= 0:
                PL = pivot(PL, pivoi , pivoj)
                solution["unlimited"] = False
            elif menorRazao < 0:
                solution["unlimited"] = True

        i += 1
    return PL

def recSimplex(PL): # Calls simplex until there's no negative number in the first line, or it is unlimited
    lin = PL.shape[0]
    col = PL.shape[1]
    neg = 1 # Assume that theres is an negative number in the first line
    while neg:
        i = 0
        numNeg = 0
        while  i < col-1:
            if PL[0][i] < 0:
                numNeg += 1
            i += 1

        if numNeg == 0:
            neg = 0
        else:
            simplex(PL)

        if neg == 0 or solution["unlimited"]:
            break

    return PL

def isFeasible(PL):
    lin = PL.shape[0]
    col = PL.shape[1]
    return not equalZero(PL[0][col-1])

def adjustCanonical(PL):
    i = 1
    lin = PL.shape[0]
    col = PL.shape[1]

    while i < lin:
        mult= (-( PL[0][base[i]]/ PL[i][base[i]]) )
        j = 0
        while j < col:
            PL[0][j] += mult * PL[i][j]
            j += 1
        i += 1

    return PL

def createBase(PL):
    lin = PL.shape[0]
    col = PL.shape[1]
    i = 1
    while  i < lin:
        base[i] = col - lin + i -1
        i += 1

def fullSimplex(outfile, fpi):
    if not canonical:
        PLaux = PLAux(fpi)
        PLaux = PLA(PLaux)

        PL = recSimplex(PLaux)
        lin = PL.shape[0]
        col = PL.shape[1]
        solution["infeasible"] = isFeasible(PLaux)

        if not solution["infeasible"]:
            PL1 = fpi[0:1,:]

            PL = np.concatenate(
                (
                    PL[1:lin, 0:col-lin],
                    PL[1:lin, col-1:col]
                ), axis = 1
            )

            PL = np.concatenate((PL1, PL), axis = 0)
            PL = adjustCanonical(PL)
            recSimplex(PL)
    else:
        createBase(fpi)
        PL = recSimplex(fpi)
        solution["infeasible"] = False

    out = output(PL)

    saida = open(outfile, 'w')
    saida.write(out + "\n")
    print(out)

def output(PL):
    lin = PL.shape[0]
    col = PL.shape[1]

    res = ''
    if solution["unlimited"]:
        res += "Status: ilimitado\n"
    elif solution["infeasible"]:
        res += "Status: inviavel\n"
    else:
        res += "Status: otimo\n"
        res += "Objetivo: " + str(PL[0][col-1]) + "\n"
        res += getSol(PL) + "\n"
    res += "Certificado:\n"

    return res

def getSol(PL):
    lin = PL.shape[0]
    col = PL.shape[1]
    sol = np.zeros((1, (col-1)))

    i = 1
    while i < lin:
        sol[0][base[i]] = PL[i][col-1]
        i += 1

    res = ''
    for elem in sol[0]:
        res += '%.4f ' % elem
    return res

def main():
    if len(sys.argv) < 3:
        print('Uso: python2 simplex.py <entrada> <saída>')
        sys.exit(1)

    infile = sys.argv[1]
    outfile = sys.argv[2]

    finalText = ReadArq(infile)
    fpi = FPI(finalText)
    PL = fullSimplex(outfile, fpi)

if __name__ == "__main__":
    main()
