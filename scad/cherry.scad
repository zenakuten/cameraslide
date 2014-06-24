module cherry()
{
	difference()
	{
		cube([28,16,10], center=true);
		translate([11,5,0]) cylinder(h=12,r=3.3/2, center=true, $fn=32);
		translate([-11,-5,0]) cylinder(h=12,r=3.3/2, center=true, $fn=32);
	}
}

