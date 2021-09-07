// test_SignalShapingServiceDUNE.cxx

// David Adams
// September 2015
//
// This test demonstrates how to configure and use the LArSoft signal
// service service outside the art framework.

#include "dune/Utilities/SignalShapingServiceDUNE.h"
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <iomanip>
#include "dune/ArtSupport/ArtServiceHelper.h"
#include "art/Framework/Services/Registry/ServiceHandle.h"
#include "lardata/Utilities/LArFFT.h"
#include "lardata/DetectorInfoServices/DetectorClocksService.h"
#include "larcore/Geometry/Geometry.h"
#include "TH1.h"

using std::string;
using std::cout;
using std::endl;
using std::vector;
using std::setw;
using std::ofstream;

int test_SignalShapingServiceDUNE() {
  const string myname = "test_SignalShapingServiceDUNE: ";
  cout << myname << "Starting test" << endl;
#ifdef NDEBUG
  cout << myname << "NDEBUG must be off." << endl;
  abort();
#endif
  string line = "-----------------------------";
  string scfg;

  cout << myname << line << endl;
  cout << "Prevent Root from managing histograms." << endl;
  TH1::AddDirectory(kFALSE);

  string const config{"#include \"services_dune.fcl\"\n"
                      "services: { @table::dune35t_services_legacy }"};
  ArtServiceHelper::load_services(config);

  cout << myname << line << endl;
  cout << myname << "Get the geometry service." << endl;
  // Now because it takes time and makes noise.
  art::ServiceHandle<geo::Geometry> pgeo;

  cout << myname << line << endl;
  cout << myname << "Get the signal shaping service." << endl;
  art::ServiceHandle<util::SignalShapingServiceDUNE> psss;

  cout << myname << line << endl;
  cout << myname << "Retrieve shaping parameters." << endl;
  art::ServiceHandle<util::LArFFT> pfft;
  unsigned int xformSize = pfft->FFTSize();
  cout << "Transform size: " << xformSize << endl;
  cout << "Decon norm: " << psss->GetDeconNorm() << endl;
  cout << "UseFunctionFieldShape: " << psss->GetDeconNorm() << endl;
  cout << "Decon norm: " << psss->GetDeconNorm() << endl;

  cout << myname << line << endl;
  cout << myname << "Create raw data." << endl;
  unsigned int chan = 450;   // Must be a collection plane.
  vector<float> raw;
  for ( int i=0; i<20; ++i ) raw.push_back(0.0);
  raw.push_back(1.0);
  raw.push_back(1.0);
  raw.push_back(2.0);
  raw.push_back(2.0);
  raw.push_back(3.0);
  raw.push_back(4.0);
  raw.push_back(5.0);
  raw.push_back(6.0);
  raw.push_back(8.0);
  raw.push_back(10.0);
  raw.push_back(10.0);
  raw.push_back(13.0);
  raw.push_back(16.0);
  raw.push_back(20.0);
  raw.push_back(25.0);
  raw.push_back(30.0);
  raw.push_back(34.0);
  raw.push_back(33.0);
  raw.push_back(27.0);
  raw.push_back(21.0);
  raw.push_back(14.0);
  raw.push_back( 8.0);
  raw.push_back( 3.0);
  raw.push_back( 2.0);
  for ( int i=0; i<20; ++i ) raw.push_back(0.0);
  assert( xformSize > raw.size() );

  cout << endl;
  cout << myname << "Deconvolute." << endl;
  vector<float> decon(xformSize);;
  for ( unsigned int i=0; i<raw.size(); ++i ) decon[i] = raw[i];
  auto const clockData = art::ServiceHandle<detinfo::DetectorClocksService const>()->DataForJob();
  psss->Deconvolute(clockData, chan, decon);
  cout << "      Raw     Decon" << endl;
  for ( int unsigned i=0; i<raw.size(); ++i ) {
    cout << setw(10) << raw[i] << setw(10) << decon[i] << endl;
  }

  cout << myname << line << endl;
  cout << "Done." << endl;
  return 0;
}

int main() {
  test_SignalShapingServiceDUNE();
  return 0;
}
