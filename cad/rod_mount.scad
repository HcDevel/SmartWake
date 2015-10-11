$fn = 90;
$preview=false;

module bett() {
    translate([0,-452.5,0]) cube([180,30,130], center=true); //Seitenteil
    translate([0,452.5,0]) cube([180,30,130], center=true); //Seitenteil
    translate([-59.5,0,0]) cube([54,905,5], center=true); //Latte
    translate([59.5,0,0]) cube([54,905,5], center=true); //Latte
}

module schraubenloch() {
    rotate([90,0,0]) cylinder(r=5, h=30, center=true);
    translate([0,-5,0]) rotate([90,0,0]) cylinder(r=10, h=10, center=true);
}

module halter() {
    difference() {
        minkowski() {
            cube([30,1,70], center=true);
            sphere(r=5);
        }
        cube([25,20,25], center=true);
        
        translate([0,0,25]) schraubenloch();
        translate([0,0,-25]) schraubenloch();
    }
}

if ($preview) {
    bett();

    color ("green")translate([0,0,-20]) cube([23,905,23], center=true); //Messlatte

    translate([0,-432.5,-20]) rotate([0,0,180]) color("red") halter();
    translate([0,432.5,-20]) color("red") halter();
} else {
   rotate([90,180,0]) halter();
}