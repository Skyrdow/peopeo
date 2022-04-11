import time
import matplotlib as mpl
import matplotlib.pyplot as plt
import numpy as np

def recursiva(numero):
    if numero == 1:
        return 1
    if numero == 0:
        return 1
    return (recursiva(numero-1) + recursiva(numero-2))

def iterativa(numero):
    i = 0
    fib1 = 0
    fib2 = 1
    fib = 1
    while i < numero:
        fib = fib1 + fib2
        fib1 = fib2
        fib2 = fib
        i+=1
    return fib

ises_iter = []
tiemposes_iter = []

ises_rec = []
tiemposes_rec = []

iteraciones = 40
for i in range(0,iteraciones):
    inicio = time.time()
    print(iterativa(i))
    fin = time.time()
    ises_iter.append(i)
    tiemposes_iter.append((fin-inicio))

for i in range(0,iteraciones):
    inicio = time.time()
    print(recursiva(i))
    fin = time.time()
    ises_rec.append(i)
    tiemposes_rec.append((fin-inicio))

fig, x = mpl.subplots()
x.plot(ises_iter, tiemposes_iter)