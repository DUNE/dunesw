// test_Geometry.cxx

// David Adams
// September 2015
//
// This test demonstrates how to configure and use the LArSoft Geometry
// service outside the art framework. DUNE geometry and geometry helper
// service are used.
//
// Note the geometry service requires the experiment-specific geometry
// helper with the channel map also be loaded. 
//
// See DXGeo/GeoHelper ctor from geometry name for an alternative to
// loading the geometry service outside the art framework.

#include "larcore/Geometry/Geometry.h"

#include <string>
#include <iostream>
#include "dune/ArtSupport/ArtServiceHelper.h"
#include "art/Framework/Services/Registry/ServiceHandle.h"

using std::string;
using std::cout;
using std::endl;

int test_Geometry(string gname) {
  const string myname = "test_Geometry: ";
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
  cout << myname << "Add the Geometry service." << endl;
  scfg = "DisableWiresInG4: true GDML: \"dune35t4apa_v5.gdml\" Name: \"" + gname +
         "\" ROOT: \"" + gname + "\" SortingParameters: { DetectorVersion: \"" + gname +
         "\" } SurfaceY: 0";
  cout << myname << "Configuration: " << scfg << endl;
  assert( ash.addService("Geometry", scfg) == 0 );

  cout << myname << line << endl;
  cout << myname << "Add the DUNE geometry helper service (required to load DUNE geometry)." << endl;
  scfg = "service_provider: \"DUNEGeometryHelper\"";
  cout << myname << "Configuration: " << scfg << endl;
  assert( ash.addService("ExptGeoHelperInterface", scfg) == 0 );

  cout << myname << line << endl;
  cout << myname << "Load the services." << endl;
  assert( ash.loadServices() == 1 );
  ash.print();

  cout << myname << line << endl;
  cout << myname << "Get Geometry service." << endl;
  art::ServiceHandle<geo::Geometry> pgeo;
  cout << myname << "Geometry name: " << pgeo->DetectorName() << endl;

  cout << myname << line << endl;
  return 0;
}

int main() {
  string gname = "dune35t4apa_v5";
  test_Geometry(gname);
  return 0;
}
