# Volume Knob

## Overview
I followed [this guide](https://blog.prusaprinters.org/3d-print-an-oversized-media-control-volume-knob-arduino-basics_30184/) by Mikolas Zuza. 
One of the changes I made was that I wanted the knob to do horizontal scroll which isn't a method included in the library in the guide. So I found a forked library that has the fuctionality of horizontal scroll. 
The libraries used in this project are all included here. 


## Functionality 
* The knob has 2 modes. 
    * Mode 1: rotation of the knob will increase or decrease volume. A single click will play or pause the media. 
    * Mode 2: rotation of the knob will scroll left or right horizontally. A single click will skip current media. 
* Modes are changed with a double click. 