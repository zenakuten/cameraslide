include <centermount.scad>

module centermountbottom()
{
	difference()
	{
		centermount();
		translate([0,0,15]) cube([32,70,30], center=true);
	}
}

centermountbottom();
