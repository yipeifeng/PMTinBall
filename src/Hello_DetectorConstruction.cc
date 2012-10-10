
#include "Hello_DetectorConstruction.hh"

#include "G4Material.hh"
#include "G4Box.hh"
#include "G4LogicalVolume.hh" 
#include "G4ThreeVector.hh"  
#include "G4PVPlacement.hh"
#include "globals.hh"


Hello_DetectorConstruction::Hello_DetectorConstruction()
{
  makeMaterial();
}


Hello_DetectorConstruction::~Hello_DetectorConstruction()
{

}

G4VPhysicalVolume*
Hello_DetectorConstruction::Construct()
{
  makeWorldLogical();
  makeWorldPhysical();

  return experimentalHall_phys;
}

void
Hello_DetectorConstruction::makeMaterial()
{
  Vacuum = new G4Material("Galatic",
                          1.,
                          1.01 * g/mole,
                          universe_mean_density,
                          kStateGas,
                          2.73 * kelvin,
                          3.e-18 * pascal);

}

G4LogicalVolume* 
Hello_DetectorConstruction::makeWorldLogical()
{
  G4double expHall_x = 1.0 * m;
  G4double expHall_y = 1.0 * m;
  G4double expHall_z = 1.0 * m;
  G4Box* experimentalHall_box = new G4Box("expHall_box",
                                          expHall_x,
                                          expHall_y,
                                          expHall_z);
  experimentalHall_log = new G4LogicalVolume(
                                experimentalHall_box,
                                Vacuum,
                                "expHall_log",
                                0,
                                0,
                                0);
  return experimentalHall_log;
}

G4VPhysicalVolume* 
Hello_DetectorConstruction::makeWorldPhysical()
{
  experimentalHall_phys = new G4PVPlacement(0, 
                                            G4ThreeVector(),
                                            experimentalHall_log,
                                            "expHall",
                                            0, 
                                            false, 
                                            0); 

}
