module knob()
{
	union()
	{
		translate([0,0,1.1]) 
		difference()
		{
			minkowski()
			{
				cylinder(r=60/2,h=3,center=true,$fn=32);
				rotate([0,90,0]) cylinder(r=4/2,h=3.1,center=true,$fn=32);
			}
			cylinder(r=52/2,h=10.1,center=true,$fn=32);
		}

		difference()
		{
			cylinder(r=60/2,h=5,center=true,$fn=32);
			cylinder(r=6.2/2,h=5.1,center=true,$fn=32);
		}
	}
}

knob();
