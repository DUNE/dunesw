// test_LArSeedService.cxx

// David Adams
// September 2015
//
// This test demonstrates how to configure and use the LArSoft SeedService
// service outside the art framework.

#include "larsim/RandomUtils/LArSeedService.h"

#include <string>
#include <iostream>
#include "dune/ArtSupport/ArtServiceHelper.h"
#include "art/Framework/Services/Registry/ServiceHandle.h"
#include "art/Framework/Core/EngineCreator.h"
#include "CLHEP/Random/RandomEngine.h"

using std::string;
using std::cout;
using std::endl;

int test_LArSeedService(string gname) {
  const string myname = "test_LArSeedService: ";
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
  cout << myname << "Add the LArSeedService service." << endl;
  scfg = "endOfJobSummary: \"true\" policy: \"random\"";
  cout << myname << "Configuration: " << scfg << endl;
  assert( ash.addService("LArSeedService", scfg) == 0 );

  cout << myname << line << endl;
  cout << myname << "Load the services." << endl;
  assert( ash.loadServices() == 1 );
  ash.print();

  cout << myname << line << endl;
  cout << myname << "Get LArSeedService service." << endl;
  art::ServiceHandle<sim::LArSeedService> psrv;

  cout << myname << line << endl;
  cout << myname << "Use LArSeedService service." << endl;
  try {
    cout << "  Seed: " << psrv->getSeed() << endl;
  } catch(...) {
    cout << "  Service use raised an exception." << endl;
    cout << "  Allow this for now." << endl;
  }

  // Close services.
  cout << myname << line << endl;
  cout << myname << "Close services." << endl;
  ArtServiceHelper::close();

  cout << myname << line << endl;
  cout << "Done." << endl;
  return 0;
}

int main() {
  string gname = "dune35t4apa_v5";
  test_LArSeedService(gname);
  return 0;
}
