include <sidemount.scad>

module sidemounttop()
{
	translate([0,0,4]) rotate([0,90,0])difference()
	{
		sidemount();
		translate([0,0,-16]) cube([80,80,32], center=true);
	}
}

sidemounttop();
