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
#include "dunecore/ArtSupport/ArtServiceHelper.h"
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

  std::ostringstream oss;
  oss << "#include \"geometry_dune.fcl\"" << endl;
  oss << "services.Geometry:                   @local::" << gname << endl;
  if (gname.find("dune35t") != std::string::npos) {
    oss << "services.WireReadout:     @local::dune35t_wire_readout" << endl;
  } else {
    oss << "services.WireReadout:     @local::dune_wire_readout" << endl;
  }
  ArtServiceHelper::load_services(oss.str());

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
