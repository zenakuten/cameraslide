#Camera slider

<img src="pics/IMG_1391.JPG" style="width:100%;" title="camera slider"/>

Camera slider used for focus stacking and time lapse photography.  It interprets g-code and
accepts an M240 command to take a photograph remotely using an infrared LED.  The remote control 
is compatible with most Cannon cameras.


#Usage

Once constructed, use a terminal program with XON/XOFF flow control 
such as [putty](http://www.chiark.greenend.org.uk/~sgtatham/putty/download.html), 
and then upload or cut/paste the g-code commands to it. 

Arrange the infrared LED so that it has line-of-sight to the front of 
the camera where the sensor is located. In the camera controls, you'll need to enable
the timed/remote mode, and once enabled make sure it is in remote mode instead of timed mode.  

An example script might look like:


      g28
      g0 x10
      m240
      g4 p1
      g0 x10.5
      m240
      g4 p1
      g0 x11
      m240
      g4 p1
      g0 x11.5
      m240
      g4 p1
      g0 x12
      ...
      g28


This translates to:

      Home
      move to position 10mm
      take a picture
      pause 1 second 
      move to position 10.5mm
      take a picture
      pause 1 second 
      move to position 11mm
      take a picture
      ...etc.



#Source

Source is available [here](cameraslide.ino).  It is a modified version of 
Dan Royer's [GcodeCNCDemo](https://github.com/MarginallyClever/GcodeCNCDemo) (2 axis, V1). It was
modified to work with a polulu 8825 stepper driver, and added support for the camera IR signal,
endstop trigger support, and flow control support.

STL files are available [here](stl), and OpenSCAD files are [here](scad)

