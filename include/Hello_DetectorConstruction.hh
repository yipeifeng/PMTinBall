
#ifndef Hello_Detector_Construction
#define Hello_Detector_Construction

class G4LogicalVolume;
class G4VPhysicalVolume;
class G4Material;

#include "G4VUserDetectorConstruction.hh"

class Hello_DetectorConstruction : public G4VUserDetectorConstruction
{
    public:
        Hello_DetectorConstruction();
        ~Hello_DetectorConstruction();

        G4VPhysicalVolume* Construct();

        void makeMaterial();
        G4LogicalVolume*   makeWorldLogical();
        G4VPhysicalVolume* makeWorldPhysical();

    private:
        // Volume
        G4LogicalVolume* experimentalHall_log;
        G4VPhysicalVolume* experimentalHall_phys;

        // Material
        G4Material* Vacuum;

};

#endif
