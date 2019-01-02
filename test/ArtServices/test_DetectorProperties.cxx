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
#include "art/Framework/Core/detail/EngineCreator.h"
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

  ArtServiceHelper::load_services("prodsingle_dune35t.fcl", ArtServiceHelper::FileOnPath);

  cout << myname << line << endl;
  cout << myname << "Get DetectorPropertiesService service." << endl;
  //art::ServiceHandle<detinfo::DetectorPropertiesService> pdetsrv;
  const detinfo::DetectorProperties* pdetsrv =
    art::ServiceHandle<detinfo::DetectorPropertiesService>()->provider();

  cout << myname << line << endl;
  cout << myname << "Use DetectorProperties service." << endl;
  cout << myname << "    SamplingRate: " << pdetsrv->SamplingRate() << endl;
  cout << myname << "  ElectronsToADC: " << pdetsrv->ElectronsToADC() << endl;

  cout << myname << line << endl;
  cout << "Done." << endl;
  return 0;
}

int main() {
  string gname = "dune35t4apa_v6";
  test_DetectorPropertiesService(gname);
  return 0;
}
