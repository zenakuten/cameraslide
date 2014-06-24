include <motor.scad>

module motormount()
{
	difference()
	{
		union()
		{
			rotate([0,90,0])
			{
				cube([42,42,4], center=true);
				difference()
				{
					translate([19,0,-13]) cube([4,42,30], center=true);
					translate([15.5,15.5,0]) rotate([0,30,0]) cylinder(h=26,r=9/2,center=true);
					translate([15.5,-15.5,0]) rotate([0,30,0]) cylinder(h=26,r=9/2,center=true);
				}
			}

			intersection()
			{
				translate([-19,0,-13]) cube([42,42,16],center=true);
				translate([4,0,-13]) rotate([0,-45,0]) cube([42,20,16],center=true);
			}
		}

		rotate([0,90,0])
		{	
			cylinder(h=11,r=22/2 + 1,center=true,$fn=32);
			translate([15.5,15.5,0]) cylinder(h=5,r=4/2,center=true);
			translate([15.5,-15.5,0]) cylinder(h=5,r=4/2,center=true);
			translate([-15.5,15.5,0]) cylinder(h=5,r=4/2,center=true);
			translate([-15.5,-15.5,0]) cylinder(h=5,r=4/2,center=true);
		}
		translate([-19,0,-19]) cylinder(h=6,r=9/2 + 0.5,center=true,$fn=32);
	}
}
