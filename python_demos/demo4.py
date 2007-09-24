#!/usr/bin/python

from pyc import *

pycasso = Pycasso()

win = pycasso.createWindow(800, 600)
event = pycasso.createEventQ()
root = win.getRootLayer2D()

win.setTitle("Pycasso Demo #4")

root.setBackgroundColor(255, 255, 255)

exit = False

root.setColor(0, 150, 0)
font = win.loadFont("../media/vera/Vera.ttf", 9)
root.setFont(font)

while not exit:
    root.drawText(100, 100, "Hello Pycasso World!")
    win.update()

    while event.next():
        if event.getType() == EVENT_QUIT:
            exit = True
        elif event.getType() == EVENT_KEY_DOWN:
            if event.getKeyCode() == KEY_ESCAPE:
                exit = True;

