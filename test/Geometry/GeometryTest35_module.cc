////////////////////////////////////////////////////////////////////////
// $Id: GeometryTest35_module.cc,v 1.1 2011/02/17 01:45:48 brebel Exp $
//
//
// geometry unit tests
//
// tylerdalion@gmail.com
//
////////////////////////////////////////////////////////////////////////

#ifndef GEO_GEOMETRYTEST35_H
#define GEO_GEOMETRYTEST35_H
#include <cmath>
#include <vector>
#include <string>
#include <iostream>

// ROOT includes
#include "TH1D.h"
#include "TH2D.h"
#include "TVector3.h"
#include "TNtuple.h"
#include "TGeoManager.h"
#include "TStopwatch.h"
#include "TMath.h"

// LArSoft includes
#include "larcore/Geometry/Geometry.h"
#include "larcorealg/Geometry/CryostatGeo.h"
#include "larcorealg/Geometry/TPCGeo.h"
#include "larcorealg/Geometry/PlaneGeo.h"
#include "larcorealg/Geometry/WireGeo.h"
#include "larcorealg/Geometry/OpDetGeo.h"
#include "larcorealg/Geometry/AuxDetGeo.h"
#include "larcorealg/Geometry/geo.h"
#include "larcoreobj/SimpleTypesAndConstants/geo_types.h"

// Framework includes
#include "art/Framework/Core/ModuleMacros.h"
#include "art/Framework/Principal/Event.h"
#include "fhiclcpp/ParameterSet.h"
#include "art/Framework/Principal/Handle.h"
#include "art/Framework/Services/Registry/ServiceHandle.h"
#include "art/Framework/Services/Optional/TFileService.h"
#include "art/Framework/Services/Optional/TFileDirectory.h"
#include "messagefacility/MessageLogger/MessageLogger.h"

#include "art/Framework/Core/EDAnalyzer.h"

namespace geo { class Geometry; }

namespace geo {
  class GeometryTest35 : public art::EDAnalyzer {
  public:
    explicit GeometryTest35(fhicl::ParameterSet const& pset);
    virtual ~GeometryTest35();

    virtual void analyze(art::Event const&) {}
    virtual void beginJob();

  private:

    void testAuxDet();

  };
}

namespace geo{

  //......................................................................
  GeometryTest35::GeometryTest35(fhicl::ParameterSet const& pset) 
    : EDAnalyzer(pset)
  {
  }

  //......................................................................
  GeometryTest35::~GeometryTest35()
  {
  }

  //......................................................................
  void GeometryTest35::beginJob()
  {

    mf::LogVerbatim("GeometryTest35") << "\n35t specific testing...\n";

    try{

      LOG_DEBUG("GeometryTest35") << "test AuxDets...";
      this->testAuxDet();
      LOG_DEBUG("GeometryTest35") << "complete.";

    }
    catch (cet::exception &e) {
      mf::LogWarning("GeometryTest35") << "exception caught: \n" << e;
    }
    
    return;
  }



  //......................................................................
  void GeometryTest35::testAuxDet()
  {
    art::ServiceHandle<geo::Geometry> geom;
    
    double origin[3] = {0.};
    double AuxDetWorld[3] = {0.};
    mf::LogVerbatim("35tAuxDetTest") << "Number of Aux Dets: " << geom->NAuxDets();
    for(unsigned int a = 0; a < geom->NAuxDets(); ++a) {
      geom->AuxDet(a).LocalToWorld(origin, AuxDetWorld);

      double testPos1[3]   = {AuxDetWorld[0], AuxDetWorld[1], AuxDetWorld[2]};
      double testPos2a[3]  = {AuxDetWorld[0], AuxDetWorld[1], AuxDetWorld[2]};
      double testPos2b[3]  = {AuxDetWorld[0], AuxDetWorld[1], AuxDetWorld[2]};
      std::string CounterType = "";

      if( strncmp( geom->AuxDet(a).TotalVolume()->GetName(), "volAuxDetTrap", 13 ) == 0 ){

	// in 35t gdml, width 2 is the smaller width at +z/2 in local coordinates
	// 
	//        Width 2
	//          ____          Height is the thickness
	//         /    \     T     of the trapezoid
	//        /      \    |
	//       /        \   | Length
	//      /__________\  _ 
	//        Width 1 

	CounterType = "trapezoid";
	testPos1[1]   += geom->AuxDet(a).Length()/2 - 0.1;
        testPos2a[2]  += geom->AuxDet(a).HalfWidth2();
	testPos2b[0]  += geom->AuxDet(a).HalfWidth2();

	double TrapCheckPtA[3] = { AuxDetWorld[0]+geom->AuxDet(a).HalfWidth1(), 
				   AuxDetWorld[1]+geom->AuxDet(a).Length()/2-0.1, 
				   AuxDetWorld[2]};
	double TrapCheckPtB[3] = { AuxDetWorld[0], 
				   AuxDetWorld[1]+geom->AuxDet(a).Length()/2-0.1, 
				   AuxDetWorld[2]+geom->AuxDet(a).HalfWidth1()};


	// these points are close to the small end and should not be found

	bool trpCheckpta(true), trpCheckptb(true);
	try{ trpCheckpta = (geom->FindAuxDetAtPosition(TrapCheckPtA) == a); }
	catch(cet::exception &e){ trpCheckpta = false; }
	try{ trpCheckptb = (geom->FindAuxDetAtPosition(TrapCheckPtB) == a); }
	catch(cet::exception &e){ trpCheckptb = false; }

	if( trpCheckpta || trpCheckptb )
	  throw cet::exception("GeometryTest35_AuxDet")
	    << "\t ...Found unexpected test point outside of trapezoidal AuxDet "
	    << a << "\n";	  


      } else {
	CounterType = "box";
        testPos2a[2] += geom->AuxDet(a).HalfWidth2();
        testPos2b[0] += geom->AuxDet(a).HalfWidth2();
      }

      mf::LogVerbatim("GeometryTest35_AuxDet") << "AuxDet " << a << ": " << CounterType 
				       << ", Center: (" << AuxDetWorld[0] << ", " 
				       << AuxDetWorld[1] << ", " << AuxDetWorld[2] << ")" << std::endl;
      

      // if either test point 1 or test point 2 aren't found, something is wrong
      //    one of 2a or 2b should work
      
      bool tp1(false), tp2a(false), tp2b(false);
      try{ tp1 = (geom->FindAuxDetAtPosition(testPos1) == a); }
      catch(cet::exception &e){ }
      try{ tp2a = (geom->FindAuxDetAtPosition(testPos2a) == a); }
      catch(cet::exception &e){ }
      try{ tp2b = (geom->FindAuxDetAtPosition(testPos2b) == a); }
      catch(cet::exception &e){ }


      if(  !tp1 || !( tp2a || tp2b )  )
	throw cet::exception("GeometryTest35_AuxDet") 
	  << "\t ...Did not find expected test points around AuxDet "
	  << a << "\n";

    }// AuxDet loop

  }




}//end namespace


namespace geo{

  DEFINE_ART_MODULE(GeometryTest35)

}

#endif
