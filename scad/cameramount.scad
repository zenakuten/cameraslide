include <nema.scad>
include <screwnut.scad>
include <sidemount.scad>
include <centermount.scad>
include <motor.scad>
include <motormount.scad>

module extrusion(h)
{
	difference()
	{
	   translate([-50,-50,0]) linear_extrude(height=h, center = true) import(file="hfs8-4040.dxf");
	   translate([85,0,0]) cube([52,42,h+2], center=true);
	}
}


module hardware()
{
	rotate([0,90,0])
	union()
	{
		translate([  0,0,150-24]) motor();
		translate([41,0,0]) extrusion(300);
		translate([0,0,-30]) 
		{
			translate([0,0,100 -7/2]) cylinder(h=11,r=22/2,center=true,$fn=32);
			translate([ 0 ,20,0]) cylinder(h=205,r=6.35/2,center=true, $fn=32);
			translate([ 0 ,0,0]) cylinder(h=205,r=6.35/2,center=true, $fn=32);
			translate([ 0 ,-20,0]) cylinder(h=205,r=6.35/2,center=true, $fn=32);
			translate([0,0,-100 +7/2]) cylinder(h=11,r=22/2,center=true,$fn=32);
		}
	}
}



module cameramount()
{
	union()
	{
		translate([100,0,0])
		{
			motormount();
		}

		translate([66,0,0])
		{
			sidemount();
		}

		centermount();

		translate([-126,0,0]) rotate([0,0,180])
		{
			sidemount();
		}


		hardware();

	}
}

cameramount();
