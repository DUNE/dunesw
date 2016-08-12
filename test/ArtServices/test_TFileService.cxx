// test_TFileService.cxx

// David Adams
// September 2015
//
// This test demonstrates how to configure and use the art TFileService
// outside the art framework.

#include "art/Framework/Services/Optional/TFileService.h"

#include <string>
#include <iostream>
#include "TFile.h"
#include "TH1F.h"
#include "art/Framework/Services/Registry/ServiceHandle.h"
#include "dune/ArtSupport/ArtServiceHelper.h"

using std::string;
using std::cout;
using std::endl;
using std::vector;
using std::unique_ptr;
using art::TFileService;
using art::TFileDirectory;

int test_TFileService(string ofilename) {
  const string myname = "test_TFileService: ";
  cout << myname << "Starting test" << endl;
#ifdef NDEBUG
  cout << myname << "NDEBUG must be off." << endl;
  abort();
#endif
  string line = "-----------------------------";

  cout << line << endl;
  cout << "Fetch art service helper." << endl;
  ArtServiceHelper& ash = ArtServiceHelper::instance();

  cout << line << endl;
  cout << myname << "Add and fetch TFileService." << endl;
  string scfg = "fileName: \"test.root\" service_type: \"TFileService\"";
  assert( ash.addService("TFileService", scfg) == 0 );

  cout << line << endl;
  cout << myname << "Load the services." << endl;
  assert( ash.loadServices() == 1 );

  cout << line << endl;
  cout << "Get TFile service." << endl;
  art::ServiceHandle<art::TFileService> pfs;
  cout << "Check if TFile is open." << endl;
  assert(pfs->file().IsOpen());
  cout << "Retrieve TFile name." << endl;
  cout << "File name: " << pfs->file().GetName() << endl;

  cout << line << endl;
  cout << "Add a histogram." << endl;
  TH1* ph1 = pfs->make<TH1F>("hist1", "Histogram 1", 100, 0, 100);

  cout << line << endl;
  cout << "Add a histogram in a subdirectory." << endl;
  TFileDirectory fd2 = pfs->mkdir("mydir", "My directory");
  TH1* ph2 = fd2.make<TH1F>("hist2", "Histogram 2", 100, 0, 100);

  cout << line << endl;
  cout << "Fill histograms." << endl;
  int nent = 10000;
  for ( int ent=0; ent<nent; ++ent ) {
    double val = 10.0/double(nent)*ent;
    val *= val;
    if ( val < 10.0 ) ph1->Fill(val);
    else ph2->Fill(val);
  }
  return 0;
}

int main() {
  string line = "-----------------------------";
  string ofilename = "test.root";
  system("rm -f test.root");
  system("ls -ls");
  TFile* pf1 = TFile::Open(ofilename.c_str(), "READ");
  assert( pf1 == nullptr );
  int rstat = test_TFileService("test.root");
  assert( rstat == 0 );
  system("ls -ls");
  cout << line << endl;
  cout << "Close services." << endl;
  ArtServiceHelper::close();
  system("ls -ls");
  cout << line << endl;
  cout << "Checking output root file" << endl;
  TFile* pf2 = TFile::Open("test.root", "READ");
  assert( pf2 != nullptr && pf2->IsOpen() );
  pf2->ls();
  TObject* po1 = pf2->Get("hist1");
  TObject* po2 = pf2->Get("hist2");
  TH1F* ph1 = dynamic_cast<TH1F*>(po1);
  assert( po1 != nullptr );
  assert( ph1 != nullptr );
  assert( po2 == nullptr );
  cout << line << endl;
  cout << "Changing to bad directory" << endl;
  TDirectory* pd2 = pf2->GetDirectory("nodir");
  assert( pd2 == nullptr );
  cout << line << endl;
  cout << "Changing file directory" << endl;
  pd2 = pf2->GetDirectory("mydir");
  assert( pd2 != nullptr );
  pd2->ls();
  po1 = pd2->Get("hist1");
  po2 = pd2->Get("hist2");
  TH1F* ph2 = dynamic_cast<TH1F*>(po2);
  assert( po2 != nullptr );
  assert( ph2 != nullptr );
  assert( po1 == nullptr );
  cout << line << endl;
  cout << "Output file: " << ofilename << endl;
  cout << "Done." << endl;
  return rstat;
}

