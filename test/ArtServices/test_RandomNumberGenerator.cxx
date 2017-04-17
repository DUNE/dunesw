// test_RandomNumberGenerator.cxx

// David Adams
// September 2015
//
// This test demonstrates how to configure and use the LArSoft RandomNumberGenerator
// service outside the art framework.

#include "art/Framework/Services/Optional/RandomNumberGenerator.h"

#include <string>
#include <iostream>
#include "dune/ArtSupport/ArtServiceHelper.h"
#include "art/Framework/Services/Registry/ServiceHandle.h"
#include "art/Framework/Core/EngineCreator.h"
#include "CLHEP/Random/RandomEngine.h"

using std::string;
using std::cout;
using std::endl;

int test_RandomNumberGenerator(string gname) {
  const string myname = "test_RandomNumberGenerator: ";
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
  cout << myname << "Add the RandomNumberGenerator service." << endl;
  scfg = "";
  cout << myname << "Configuration: " << scfg << endl;
  assert( ash.addService("RandomNumberGenerator", scfg) == 0 );

  cout << myname << line << endl;
  cout << myname << "Load the services." << endl;
  assert( ash.loadServices() == 1 );
  ash.print();

  cout << myname << line << endl;
  cout << myname << "Get RandomNumberGenerator service." << endl;
  art::ServiceHandle<art::RandomNumberGenerator> pransrv;

  cout << myname << line << endl;
  cout << myname << "Create the random engine." << endl;
  art::EngineCreator ecr;
  CLHEP::HepRandomEngine& ran0 = ecr.createEngine(317729);

  cout << myname << line << endl;
  cout << myname << "Fetch random engine from service." << endl;
  CLHEP::HepRandomEngine& ran = pransrv->getEngine();
  assert( &ran0 == &ran );

  cout << myname << "Generate randoms." << endl;
  std::vector<double> vals;
  for ( unsigned int ival=0; ival<20; ++ival ) {
    double val = ran.flat();
    cout << myname << "  " << val << endl;
    assert( val > 0.0 );
    assert( val < 1.0 );
    assert( vals.size() == ival );
    assert( std::find(vals.begin(), vals.end(), val) == vals.end() );
    vals.push_back(val);
  }

  cout << myname << line << endl;
  return 0;
}

int main() {
  string gname = "dune35t4apa_v6";
  test_RandomNumberGenerator(gname);
  return 0;
}
