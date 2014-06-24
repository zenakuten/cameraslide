module motorcoupling()
{
	difference()
	{
		union()
		{
			translate([0,0,-5]) cylinder(r=12/2,h=10,center=true,$fn=32);
			translate([0,0,12]) cylinder(r=8.2/2,h=28,center=true,$fn=32);
		}
		translate([0,0,-8 - 0.1]) cylinder(r=6.2/2,h=12,center=true,$fn=32);
		intersection()
		{
			translate([0,0,20 + 0.1]) cylinder(r=5.6/2,h=28,center=true,$fn=32);
			translate([2.9,0,20 + 0.1]) cube([10,10,28],center=true);
		}
	}
}

motorcoupling();
