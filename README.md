#Camera slider

<img src="pics/IMG_1391.JPG" style="width:100%;" title="camera slider"/>

Camera slider used for focus stacking and time lapse photography.  It interprets g-code and
accepts an M240 command to take a photograph remotely using an infrared LED.  The remote control 
is compatible with most Canon cameras.


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


[More images on imgur](http://imgur.com/a/SMLx9#0)


[Video](http://www.youtube.com/watch?v=6ovWjnzBGUw)

TODO - Need to get images of the output! soon...

#Hardware


[1/4 in.-20 x 7/8 in coupling nut](http://www.homedepot.com/p/Everbilt-1-4-in-20-x-7-8-in-Zinc-Plated-Rod-Coupling-Nut-15-Pieces-19117/202249719 )

They have packs of 3 in the store.



[1/4 in x 72  in. Plain Steel Round Rod](http://www.homedepot.com/p/Everbilt-1-4-in-x-72-in-Plain-Steel-Round-Rod-49060/202183538)

I cut two pieces to length and then polished them by putting each in my drill and using [polishing compound.](http://www.homedepot.com/p/Ryobi-Hard-Metal-Cleaning-Compound-Set-A04HM01/202886264)



[1/4 in 12 in Stainless Steel Threaded Rod](http://www.homedepot.com/p/Crown-Bolt-1-4-in-x-12-in-Stainless-Steel-Threaded-Rod-43540/203122557)

Don't get the zinc plated stuff, search around for the stainless.



[608 skate bearings](http://www.amazon.com/VXB-Skateboard-Bearings-Double-Shielded/dp/B002BBGTK6)

I had left overs, but you only need two.  I believe Ace Hardware sells them as well, as will any skate shop.




This stuff is optional, but it's what I used as a base (also left overs)

[Aluminum angle](http://www.homedepot.com/p/Unbranded-1-in-x-96-in-Aluminum-Angle-Bar-with-1-20-in-Thick-802587/204273981)


[Aluminum extrusion](http://us.misumi-ec.com/vona2/mech/M1500000000/M1501000000/M1501010000/M1501010300/)

Since the extrusion is a little harder to come by I'd recommend simply building the base out of wood.  



The rest of the screws are either M3 in various sizes (m3x30,m3x20,m3x16?I do not remember all of them sorry), or the bigger M8 used 
to connect everything to the extrusion.


#Electronics

[Arduino Nano](http://arduino.cc/en/Main/ArduinoBoardNano)

[8825 stepper driver](http://www.pololu.com/product/2133)

[Infrared LED](http://www.radioshack.com/product/index.jsp?productId=2062565) (I bought this in a brick and mortar store)

[Cherry switch](http://na.suzohapp.com/all_catalogs/electrical_supplies/95-0733-90) (not exact, I had an old cherry video game switch)

[Power connector](http://www.digikey.com/product-detail/en/PJ-037A/CP-037A-ND/1644545)


You'll also want header pins and connectors to connect everything, all stuff I bought off digikey.  
I used a 12V, 1.5A wall wart power supply that I bought at Goodwill.  Anything 12V 1A+ will be good enough.


I do not have a schematic but the wiring is very straight forward.  Everything was soldered together using [perfboard prototyping](http://www.youtube.com/watch?v=3N3ApzmyjzE)

Arduino Pins (configurable in the software):

- 4 -> DRV8825 step
- 5 -> DRV8825 dir
- 8 -> Cherry switch (other end of switch goes to ground)
- 6 -> 180 ohm resistor in series with the LED.  The LED should be connected with long wires so 
       it can be placed in front of the camera where the remote control sensor is.
