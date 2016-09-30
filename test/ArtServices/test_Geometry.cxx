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
#include <fstream>
#include "dune/ArtSupport/ArtServiceHelper.h"
#include "art/Framework/Services/Registry/ServiceHandle.h"

using std::string;
using std::cout;
using std::endl;
using std::ofstream;

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
  cout << myname << "Create configuration." << endl;
  const char* ofname = "test_Geometry.fcl";
  {
    ofstream fout(ofname);
    fout << "#include \"geometry_dune.fcl\"" << endl;;
    fout << "services.Geometry:                   @local::" + gname << endl;;
    fout << "services.ExptGeoHelperInterface:     @local::dune_geometry_helper" << endl;;
  }

  cout << myname << "Configuration:\n" << scfg << endl;
  assert( ash.addServices(ofname, true) == 0 );

  cout << myname << line << endl;
  cout << myname << "Load the services." << endl;
  assert( ash.loadServices() == 1 );
  ash.print();

  cout << myname << line << endl;
  cout << myname << "Get Geometry service." << endl;
  art::ServiceHandle<geo::Geometry> pgeo;
  cout << myname << line << endl;
  cout << myname << "Geometry name: " << pgeo->DetectorName() << endl;

  cout << myname << line << endl;
  return 0;
}

int main(int argc, const char* argv[]) {
  string gname = "dune35t_geo";
  if ( argc > 1 ) {
    string sarg = argv[1];
    if ( sarg == "-h" ) {
      cout << argv[0] << ": GEOFCLNAME [dune35t_geo]";
      return 0;
    }
    gname = sarg;
  }
  test_Geometry(gname);
  return 0;
}
