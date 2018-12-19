// test_LArSeedService.cxx

// David Adams
// September 2015
//
// This test demonstrates how to configure and use the LArSoft SeedService
// service outside the art framework.

#include "nutools/RandomUtils/NuRandomService.h"

#include <string>
#include <iostream>
#include "dune/ArtSupport/ArtServiceHelper.h"
#include "art/Framework/Services/Registry/ServiceHandle.h"
#include "art/Framework/Core/detail/EngineCreator.h"
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

  std::string const config{"NuRandomService: { endOfJobSummary: true  policy: random}"};
  ArtServiceHelper::load_services(config);

  cout << myname << line << endl;
  cout << myname << "Get NuRandomService service." << endl;
  art::ServiceHandle<rndm::NuRandomService> psrv;

  cout << myname << line << endl;
  cout << myname << "Use NuRandomService service." << endl;
  try {
    cout << "  Seed: " << psrv->getSeed() << endl;
  } catch(...) {
    cout << "  Service use raised an exception." << endl;
    cout << "  Allow this for now." << endl;
  }

  cout << myname << line << endl;
  cout << "Done." << endl;
  return 0;
}

int main() {
  string gname = "dune35t4apa_v6";
  test_LArSeedService(gname);
  return 0;
}
