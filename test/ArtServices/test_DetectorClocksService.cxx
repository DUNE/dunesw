// test_DetectorClocksService.cxx

// David Adams
// September 2015
//
// This test demonstrates how to configure and use the LArSoft DetectorClocksService
// service outside the art framework.

#include "lardata/DetectorInfoServices/DetectorClocksService.h"

#include <string>
#include <iostream>
#include "art/Framework/Services/Registry/ServiceHandle.h"
#include "art/Framework/Core/EngineCreator.h"
#include "CLHEP/Random/RandomEngine.h"
#include "dune/ArtSupport/ArtServiceHelper.h"

using std::string;
using std::cout;
using std::endl;

int test_DetectorClocksService(string gname) {
  const string myname = "test_DetectorClocksService: ";
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
  scfg = "prodsingle_dune35t.fcl";
  bool isFile = true;

  cout << myname << line << endl;
  cout << myname << "Add the DetectorClocksService service." << endl;
  cout << myname << "Configuration: " << scfg << endl;
  assert( ash.addService("DetectorClocksService", scfg, isFile) == 0 );

  cout << myname << line << endl;
  cout << myname << "Load the services." << endl;
  assert( ash.loadServices() == 1 );
  ash.print();

  cout << myname << line << endl;
  cout << myname << "Get DetectorClocksService service." << endl;
  const detinfo::DetectorClocks* pclksrv =
    art::ServiceHandle<detinfo::DetectorClocksService>()->provider();

  cout << myname << line << endl;
  cout << myname << "Use DetectorClocksService service." << endl;
  cout << "   TriggerTime: " << pclksrv->TriggerTime() << endl;
  cout << "  BeamGateTime: " << pclksrv->BeamGateTime() << endl;

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
  test_DetectorClocksService(gname);
  return 0;
}
