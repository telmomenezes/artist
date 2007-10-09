#!/usr/bin/python

from pyc import *

pycasso = Pycasso()

win = pycasso.createWindow(800, 600)
event = pycasso.createEventQ()
root = win.getRootLayer2D()

win.setTitle("Pycasso Demo #4")

root.setBackgroundColor(255, 255, 255)

exit = False

font = win.loadFont("../media/vera/Vera.ttf", 9)
root.setFont(font)
text = "Hello Pycasso World ;)"
textWidth = font.getTextWidth(text)

while not exit:
    root.setColor(150, 0, 0)
    root.drawLine(100, 100, 100 + textWidth, 100)
    root.setColor(0, 150, 0)
    root.drawText(100, 100, text)

    win.update()

    while event.next():
        if event.getType() == EVENT_QUIT:
            exit = True
        elif event.getType() == EVENT_KEY_DOWN:
            if event.getKeyCode() == KEY_ESCAPE:
                exit = True;

