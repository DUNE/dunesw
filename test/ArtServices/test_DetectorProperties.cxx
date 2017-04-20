// test_DetectorProperties.cxx

// David Adams
// September 2015
//
// This test demonstrates how to configure and use the LArSoft DetectorProperties
// service outside the art framework.

#include "lardata/DetectorInfoServices/DetectorPropertiesService.h"

#include <string>
#include <iostream>
#include "dune/ArtSupport/ArtServiceHelper.h"
#include "art/Framework/Services/Registry/ServiceHandle.h"
#include "art/Framework/Core/EngineCreator.h"
#include "CLHEP/Random/RandomEngine.h"

using std::string;
using std::cout;
using std::endl;

int test_DetectorPropertiesService(string gname) {
  const string myname = "test_DetectorPropertiesService: ";
  cout << myname << "Starting test" << endl;
#ifdef NDEBUG
  cout << myname << "NDEBUG must be off." << endl;
  abort();
#endif
  string line = "-----------------------------";
  string scfg;

  cout << myname << line << endl;
  cout << myname << "Fetch art service helper." << endl;
  ArtServiceHelper& ash = ArtServiceHelper::instance();

  cout << myname << line << endl;
  cout << myname << "Add the DetectorPropertiesService service." << endl;
  scfg = "prodsingle_dune35t.fcl";
  bool isFile = true;
  cout << myname << "Configuration: " << scfg << endl;
  assert( ash.addService("DetectorPropertiesService", scfg, isFile) == 0 );

  cout << myname << line << endl;
  cout << myname << "Add other services." << endl;
  assert( ash.addService("Geometry", scfg, isFile) == 0 );
  assert( ash.addService("ExptGeoHelperInterface", scfg, isFile) == 0 );
  assert( ash.addService("LArPropertiesService", scfg, isFile) == 0 );
  assert( ash.addService("DetectorClocksService", scfg, isFile) == 0 );

  cout << myname << line << endl;
  cout << myname << "Load the services." << endl;
  assert( ash.loadServices() == 1 );
  ash.print();

  cout << myname << line << endl;
  cout << myname << "Get DetectorPropertiesService service." << endl;
  //art::ServiceHandle<detinfo::DetectorPropertiesService> pdetsrv;
  const detinfo::DetectorProperties* pdetsrv =
    art::ServiceHandle<detinfo::DetectorPropertiesService>()->provider();

  cout << myname << line << endl;
  cout << myname << "Use DetectorProperties service." << endl;
  cout << myname << "    SamplingRate: " << pdetsrv->SamplingRate() << endl;
  cout << myname << "  ElectronsToADC: " << pdetsrv->ElectronsToADC() << endl;

  // Close services.
  cout << myname << line << endl;
  cout << myname << "Close services." << endl;
  ArtServiceHelper::close();

  cout << myname << line << endl;
  cout << "Done." << endl;
  return 0;
}

int main() {
  string gname = "dune35t4apa_v6";
  test_DetectorPropertiesService(gname);
  return 0;
}
