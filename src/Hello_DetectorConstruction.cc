
#include "Hello_DetectorConstruction.hh"

#include "G4Material.hh"
#include "G4Box.hh"
#include "G4Tubs.hh"
#include "G4LogicalVolume.hh" 
#include "G4ThreeVector.hh"  
#include "G4PVPlacement.hh"
#include "globals.hh"

#include "G4Colour.hh"
#include "G4VisAttributes.hh"



Hello_DetectorConstruction::Hello_DetectorConstruction()
{
  makeVariables();
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

  makePMTLogical();
  makePMTPhysical();

  return experimentalHall_phys;
}

void 
Hello_DetectorConstruction::makeVariables()
{
  expHall_x = 1.0 * m;
  expHall_y = 1.0 * m;
  expHall_z = 1.0 * m;

  pmttube_r = 50.8*cm / 2;
  pmttube_h = 68.5*cm;
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
  Al = new G4Material("Aluminium",
                      13.,
                      26.98*g/mole,
                      2.700*g/cm3);

}

G4LogicalVolume* 
Hello_DetectorConstruction::makeWorldLogical()
{
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
  return experimentalHall_phys;

}

G4LogicalVolume* 
Hello_DetectorConstruction::makePMTLogical()
{
  G4Tubs* pmttube_solid = new G4Tubs(
                                    "PMTTube",
                                    0*cm,  /* inner */ 
                                    pmttube_r, //21*cm/2, /* pmt_r */ 
                                    pmttube_h/2, //30*cm/2, /* pmt_h */ 
                                    0*deg, 
                                    360*deg);
  pmttube_log = new G4LogicalVolume(
                                    pmttube_solid, 
                                    Al/*Material*/, 
                                    "PMTTube_Logic");

  G4VisAttributes* pmttube_visatt = new G4VisAttributes(G4Colour(0.5, 0.5, 0.5));
  //pmttube_visatt -> SetForceWireframe(true);  
  //pmttube_visatt -> SetForceAuxEdgeVisible(true);
  pmttube_visatt -> SetForceSolid(true);
  pmttube_visatt -> SetForceLineSegmentsPerCircle(4);

  pmttube_log -> SetVisAttributes(pmttube_visatt);

  return pmttube_log;

}

G4VPhysicalVolume* 
Hello_DetectorConstruction::makePMTPhysical()
{
  pmttube_phys = new G4PVPlacement(
                                    0,
                                    G4ThreeVector(),
                                    pmttube_log,
                                    "PMTTube",
                                    experimentalHall_log, 
                                    false, 
                                    0); 

}
