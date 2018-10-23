// test_LArProperties.cxx

// David Adams
// September 2015
//
// This test demonstrates how to configure and use the LArSoft LArProperties
// service outside the art framework.

#include "lardata/DetectorInfoServices/LArPropertiesServiceStandard.h"

#include <string>
#include <iostream>
#include "dune/ArtSupport/ArtServiceHelper.h"
#include "art/Framework/Services/Registry/ServiceHandle.h"
#include "art/Framework/Core/detail/EngineCreator.h"
#include "CLHEP/Random/RandomEngine.h"

using std::string;
using std::cout;
using std::endl;
using detinfo::LArProperties;
using detinfo::LArPropertiesService;

int test_LArPropertiesStandard(string gname) {
  const string myname = "test_LArPropertiesStandardServiceStandard: ";
  cout << myname << "Starting test" << endl;
#ifdef NDEBUG
  cout << myname << "NDEBUG must be off." << endl;
  abort();
#endif
  string line = "-----------------------------";

  ArtServiceHelper::load_services("prodsingle_dune35t.fcl", ArtServiceHelper::FileOnPath);

  cout << myname << line << endl;
  cout << myname << "Get LArPropertiesServiceStandard service." << endl;
  const LArProperties* plarsrv = art::ServiceHandle<LArPropertiesService>()->provider();

  cout << myname << line << endl;
  cout << myname << "Use LArPropertiesStandard." << endl;
  cout << myname << "     Atomic number: " << plarsrv->AtomicNumber() << endl;
  cout << myname << "  Radiation length: " << plarsrv->RadiationLength() << endl;

  cout << myname << line << endl;
  cout << "Done." << endl;
  return 0;
}

int main() {
  string gname = "dune35t4apa_v6";
  test_LArPropertiesStandard(gname);
  return 0;
}
