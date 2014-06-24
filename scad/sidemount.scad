include <cherry.scad>

module sidemount()
{
	difference()
	{
		union()
		{
			difference() 
			{
				translate([0,0,-8]) cube([12,66,25],center=true);
				translate([0,28,-13.5]) cube([13,16,20],center=true);
				translate([0,-28,-13.5]) cube([13,16,20],center=true);
			}

			translate([0,-20,0]) rotate([0,90,0]) cylinder(h=12,r=12/2,center=true,$fn=32);
			translate([0,20,0]) rotate([0,90,0]) cylinder(h=12,r=12/2,center=true,$fn=32);
			translate([0,0,0]) rotate([0,90,0]) cylinder(h=12,r=28/2,center=true,$fn=32);
			translate([0,0,4]) cube([12,40,4],center=true);

			difference() 
			{
				translate([-12,0,-17.5]) cube([36,40,7], center=true);
				rotate([0,0,90]) 
				{
					translate([11,26,-16.5]) cylinder(h=10,r=2.7/2, center=true, $fn=32);
					translate([-11,16,-16.5]) cylinder(h=10,r=2.7/2, center=true, $fn=32);
				}
			
				translate([-18,0,-17.5]) cylinder(h=10,r=8.5/2,center=true);
				translate([-18,0,-15.5]) cylinder(h=6,r=14.5/2,center=true);
			}

			rotate([0,0,90]) translate([0,21,-9.0]) cherry();

		}

		translate([0,-29,-2.5]) cylinder(r=3.3, h=2.3, center=true, $fn=6);
		translate([0,-29,0]) cylinder(r=4/2, h=10, center=true, $fn=32);
		
		translate([0,29,-2.5]) cylinder(r=3.3, h=2.3, center=true, $fn=6);
		translate([0,29,0]) cylinder(r=4/2, h=10, center=true, $fn=32);

		translate([0,-14.5,-3]) cylinder(r=2.7/2, h=20, center=true, $fn=32);
		translate([0,14.5,-3]) cylinder(r=2.7/2, h=20, center=true, $fn=32);

		translate([0,-14.5,11]) cylinder(r=8/2, h=10, center=true, $fn=32);
		translate([0,14.5,11]) cylinder(r=8/2, h=10, center=true, $fn=32);

		translate([0,0,0.25]) cube([13,68,1],center=true);
		rotate([0,90,0]) 
		{
			cylinder(h=14,r=22/2,center=true,$fn=32);
			translate([ 0 ,20,0]) cylinder(h=20,r=6.35/2,center=true, $fn=32);
			translate([ 0 ,0,0]) cylinder(h=20,r=6.35/2,center=true, $fn=32);
			translate([ 0 ,-20,0]) cylinder(h=20,r=6.35/2,center=true, $fn=32);
		}
	}
}

