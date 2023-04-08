# TO D0:
#   Display voltage and temp on display
#   External Reference Voltage
#   ADC External
#   Resistance Graph while inputing temp

#   USE AREF - use that voltage machine see if makes accuracy difference
#

from pyfirmata import Arduino, util
import numpy as np
import matplotlib
matplotlib.use('TkAgg')
from matplotlib import pyplot

def LED():
    if blue1 <= tempRT <= blue2:
        bluePin.write(1)
        greenPin.write(0)
        redPin.write(0)
    elif red1 <= tempRT <= red2:
        bluePin.write(0)
        greenPin.write(0)
        redPin.write(1)
    elif green1 <= tempRT <= green2:
        bluePin.write(0)
        greenPin.write(1)
        redPin.write(0)


def resistancePrecision():
    total = 0
    for i in range(trials):
        total += thermistorPin.read()
    return resistor * total / (trials - total)


def ToReducedRowEchelonForm(M):
    if not M: return
    lead = 0
    rowCount = len(M)
    columnCount = len(M[0])
    for r in range(rowCount):
        if lead >= columnCount:
            return
        i = r
        while M[i][lead] == 0:
            i += 1
            if i == rowCount:
                i = r
                lead += 1
                if columnCount == lead:
                    return
        M[i],M[r] = M[r],M[i]
        lv = M[r][lead]
        M[r] = [ mrx / float(lv) for mrx in M[r]]
        for i in range(rowCount):
            if i != r:
                lv = M[i][lead]
                M[i] = [ iv - lv*rv for rv,iv in zip(M[r],M[i])]
        lead += 1

def matrixMaker(temps, rs, n):
  matrix = [[0 for x in range(n-1)] for y in range(n)]
  for x in range(n):
    i = 1
    for y in range(n-1):
      matrix[x][y] = np.log(rs[x])**i
      i+=2

  matrix = list(map(list, zip(*matrix)))
  matrix.insert(0, [1 for x in range(n)])
  matrix.append([1/(temps[x]) for x in range(n)])
  matrix = list(map(list, zip(*matrix)))
  return matrix

def displayGraph(title, realTimeValue, range, figure):
    pyplot.title(title)
    figure.append(realTimeValue)
    pyplot.ylim([realTimeValue - range, realTimeValue + range])
    del figure[0]
    ax.set_xdata([i for i in xrange(25)])
    pyplot.pause(0.0000001)
    ax.set_ydata(figure)
    pyplot.pause(0.0000001)
    pyplot.legend()
    pyplot.draw()

try:
    board = Arduino("/dev/cu.usbmodem14101")  # Port Name
except:
    board = Arduino("/dev/cu.usbmodem14201")  # Port Name

it = util.Iterator(board)
it.start()

# Pins
bluePin = board.get_pin("d:7:o")
greenPin = board.get_pin("d:10:o")
redPin = board.get_pin("d:13:o")
thermistorPin = board.get_pin("a:0:i")

# Lists
resis = []
temps = []

allResis = []

# Variables
vin = 5
resistor = 10000    # Fixed resistor resistance
delayTime = .05     # Delay time in s
trials = 10         # Amount of trials for mean resistance
tempRT = 0          # Temp Real Time
resisRT = 0         # Resistance Real Time

# LED Ranges
blue1 = 0
blue2 = 20
green1 = 20
green2 = 45
red1 = 45
red2 = 75

# Boolean
dataCollection = True
temperature = True

# Create figure for plotting TEMPERATURE
tempFig = [0] * 25
fig = pyplot.figure()
pyplot.title("Temperatrue")
ax1 = pyplot.axes()
ax, = pyplot.plot(tempFig)
pyplot.ylim([0,75])
pyplot.ion()
pyplot.show()

# Create figure for plotting RESISTANCE
resisFig = [0] * 25
fig = pyplot.figure()
pyplot.title("Resistance")
ax1 = pyplot.axes()
ax, = pyplot.plot(resisFig)
pyplot.ylim([1000,30000])
pyplot.ion()
pyplot.show()

while dataCollection:

    resisRT = resistancePrecision()
    allResis.append(resisRT)
    displayGraph("Resistance: "+str(round(resisRT,3)), round(resisRT,3), 200, resisFig)

    temp = raw_input("Temperature (C): ")
    if temp != "stop":
        temps.append(float(temp)+273.15)
        resis.append(resistancePrecision())
    else:
        break

    print(resis[-1:])

A = matrixMaker(temps, resis, len(temps))
coffs = ToReducedRowEchelonForm(A)
coffs = list(map(list, zip(*A)))[len(A)]

print(resis)
print(temps)
print(coffs)

while temperature:

    resisRT = resistancePrecision()
    i, sum1 = 1, coffs[0]
    for x in coffs[1:]:
        sum1 += x * (np.log(resisRT) ** i)
        i += 2
    tempRT = (sum1 ** -1) - 273.15

    LED()
    print("Temperature: " + str(round(tempRT, 3)))
    print("Volts: " + str(round(thermistorPin.read() * 5, 3)))
    print("Resistance: " + str(round(resisRT, 3)))
    print("--------------------")

    displayGraph("Temperature: "+str(round(tempRT, 1))+"\n Volts: "+str(round(thermistorPin.read() * 5, 3)), tempRT, 2, tempFig)

    '''
    pyplot.ylim([tempRT-2, tempRT+2])
    del tempFig[0]
    ax.set_xdata([i for i in xrange(25)])
    pyplot.pause(0.0000001)
    ax.set_ydata(tempFig)
    pyplot.pause(0.0000001)
    pyplot.legend()
    pyplot.draw()
    '''


