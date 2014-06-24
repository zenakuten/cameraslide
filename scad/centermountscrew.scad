module centermountscrew(height)
{
	union()
	{
		translate([0,0,-height/2+2.3/2-0.1]) cylinder(r=3.3,h=2.3,center=true,$fn=6);
		cylinder(r=4/2,h=height,center=true,$fn=32);
		translate([0,0,height/2-2.3/2+0.1]) cylinder(r=3.3,h=2.3,center=true,$fn=32);

	}
}

