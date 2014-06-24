include <centermountscrew.scad>
include <screwnut.scad>
module centermount()
{
	difference() 
	{
		union()
		{
			translate([0,0,0]) cube([30,68,20], center=true);
			translate([0,0,14]) cube([30,30,8], center=true);
		}
		rotate([0,90,0]) rotate([0,0,30]) screwnut(16);
		rotate([0,90,0]) cylinder(r=9/2,h=32, center=true,$fn=32);
		rotate([0,0,30]) translate([0,0,16.1]) screwnut(4);
		rotate([0,0,30]) translate([0,0,6]) cylinder(r=15/2,h=13,center=true,$fn=32);
		translate([0,0,14]) cylinder(r=6/2,h=10,center=true, $fn=32);
		translate([0,0,0]) cube([32,70,1], center=true);

		translate([-9,-28,0]) centermountscrew(20);
		translate([9,-28,0]) centermountscrew(20);
		translate([-9,28,0]) centermountscrew(20);
		translate([9,28,0]) centermountscrew(20);

		translate([-9,-10,4]) centermountscrew(28);
		translate([9,-10,4]) centermountscrew(28);
		translate([-9,10,4]) centermountscrew(28);
		translate([9,10,4]) centermountscrew(28);
		rotate([0,90,0]) 
		{
			translate([ 0 ,20,0]) cylinder(h=32,r=6.35/2,center=true, $fn=32);
			translate([ 0 ,0,0]) cylinder(h=32,r=6.35/2,center=true, $fn=32);
			translate([ 0 ,-20,0]) cylinder(h=32,r=6.35/2,center=true, $fn=32);
		}
	}
}

