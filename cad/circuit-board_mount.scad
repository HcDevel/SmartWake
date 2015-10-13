$fn=180;

module screw() {
	translate([0,0,-1.5]) cylinder(d=3.3, h=2, center=true);
	translate([0,0,1]) cylinder(d=8, h=3, center=true);
}

module mount() {
	cube([2,10,8], center=true);
	translate([1,0,5]) cube([4,10,2], center=true);
}

difference() {
	cube([56,100,5], center=true); //Grundplatte
	translate([25,0,0]) cube([30,80,6], center=true);
	translate([-25,0,0]) cube([30,80,6], center=true);
	translate([0,-40]) screw();
	translate([0,40]) screw();
}

translate([-29,45,1.5]) mount();
translate([29,45,1.5]) rotate([0,0,180]) mount();
translate([-29,-45,1.5]) mount();
translate([29,-45,1.5]) rotate([0,0,180]) mount();