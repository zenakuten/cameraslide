module shim()
{
	difference()
	{

		cylinder(r=8.2/2,h=6,center=true,$fn=32);
		cylinder(r=6.1/2,h=7,center=true,$fn=32);
	}
}

shim();
