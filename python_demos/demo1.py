#!/usr/bin/python

from pyc import *

pycasso = Pycasso()

win = pycasso.createWindow(800, 600)
event = pycasso.createEventQ()
root = win.getRootLayer2D()

win.setTitle("Pycasso Demo #1")

root.setBackgroundColor(255, 255, 255)

exit = False
x = 400.0
y = 300.0
deltaX = 3.0
deltaY = 3.0

while not exit:
    print pycasso.getTime()
    root.setColor(255, 0, 0)
    root.fillCircle(x, y, 50.0)

    win.update()

    x += deltaX
    y += deltaY

    if x >= 750:
        deltaX = -deltaX
    if x <= 50:
        deltaX = -deltaX
    if y >= 550:
        deltaY = -deltaY
    if y <= 50:
        deltaY = -deltaY

    while event.next():
        if event.getType() == EVENT_QUIT:
            exit = True
        elif event.getType() == EVENT_KEY_DOWN:
            if event.getKeyCode() == KEY_ESCAPE:
                exit = True;

