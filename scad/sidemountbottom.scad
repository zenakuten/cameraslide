include <sidemount.scad>

module sidemountbottom()
{
	translate([0,0,4]) rotate([0,90,0])difference()
	{
		sidemount();
		translate([0,0,16]) cube([50,70,32], center=true);
	}
}

sidemountbottom();
