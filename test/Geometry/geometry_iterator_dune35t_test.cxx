/**
 * @file   geometry_iterator_dune35t_test.cxx
 * @brief  Unit test for geometry iterators on "optimized" DUNE 35t detector
 * @date   May 11th, 2015
 * @author petrillo@fnal.gov
 * 
 * Usage: just run the executable.
 * Boost unit testing environment keeps the arguments secret anyway.
 */

// LArSoft libraries
#include "test/Geometry/geometry_unit_test_dune.h"
#include "Geometry/GeometryCore.h"
#include "lbne/Geometry/ChannelMap35OptAlg.h"

// utility libraries
#include "messagefacility/MessageLogger/MessageLogger.h"

// Boost libraries
#define BOOST_TEST_MODULE GeometryIteratorTestDUNE35t
#include <boost/test/included/unit_test.hpp>

// C/C++ standard libraries
#include <string>
#include <iostream>


//------------------------------------------------------------------------------
//---  The test environment
//---

// we define here all the configuration that is needed;
// we use an existing class provided for this purpose, since our test
// environment allows us to tailor it at run time.
using DUNE35tGeometryConfiguration
  = lbne::testing::DUNE35tGeometryFixtureConfigurer<geo::ChannelMap35OptAlg>;

/*
 * GeometryTesterFixture, configured with the object above, is used in a
 * non-Boost-unit-test context.
 * It provides:
 * - `geo::GeometryCore const* Geometry()`
 * - `geo::GeometryCore const* GlobalGeometry()` (static member)
 */
using DUNE35tGeometryTestFixture
  = testing::GeometryTesterFixture<DUNE35tGeometryConfiguration>;


//------------------------------------------------------------------------------
//---  The tests
//---

// BOOST_FIXTURE_TEST_SUITE(GeometryIterators, DUNE35tGeometryTestFixture)
BOOST_GLOBAL_FIXTURE(DUNE35tGeometryTestFixture)


BOOST_AUTO_TEST_CASE( CryostatIteratorsTest )
{
  using ID_t = geo::CryostatID::ID_t;
  const ID_t InvalidID = geo::CryostatID::InvalidID;
  
  geo::GeometryCore const* geom = DUNE35tGeometryTestFixture::GlobalGeometry();
  
  /*
   * public interface (cryostat_iterator_base):
   *
   *     /// Default constructor; effect not defined: assign to it before using!
   *     cryostat_iterator_base();
   *     
   *     /// Constructor: points to begin
   *     cryostat_iterator_base(geo::GeometryCore const* geom);
   *     
   *     /// Constructor: points to the specified cryostat
   *     cryostat_iterator_base
   *       (geo::GeometryCore const* geom, GEOID const& start_from);
   *     
   *     /// Constructor: points to begin
   *     cryostat_iterator_base(geo::GeometryCore const* geom, BeginPos_t);
   *     
   *     /// Constructor: points to end
   *     cryostat_iterator_base(geo::GeometryCore const* geom, EndPos_t);
   *     
   *     /// Returns true if the two iterators point to the same cryostat
   *     template <typename OTHERID>
   *     bool operator== (cryostat_iterator_base<OTHERID> const& as) const;
   *     
   *     /// Returns true if the two iterators point to different cryostats
   *     template <typename OTHERID>
   *     bool operator!= (cryostat_iterator_base<OTHERID> const& as) const;
   *     
   *     /// Returns the ID the iterator points to
   *     LocalID_t const& operator* () const;
   *     
   *     /// Returns a pointer to the ID the iterator points to
   *     LocalID_t const* operator-> () const;
   *     
   *     /// Prefix increment: returns this iterator pointing to next cryostat
   *     iterator& operator++ ();
   *     
   *     /// Postfix increment: returns the current iterator, then increments it
   *     iterator operator++ (int);
   *     
   *     /// Returns whether the iterator is pointing to a valid cryostat
   *     operator bool() const;
   *     
   *     /// Returns a pointer to cryostat, or nullptr if invalid
   *     ElementPtr_t get() const;
   *
   */
  
  //
  // default constructed
  //
  {
    geo::GeometryCore::cryostat_iterator iCryo;
    std::cout << "Default created cryostat iterator: " << (*iCryo) << std::endl;
    
    BOOST_CHECK_EQUAL(iCryo->Cryostat, InvalidID);
    
    // check that the iterator tests false
    BOOST_CHECK(!iCryo);
    BOOST_CHECK(!(bool(iCryo)));
  
  /*
    // this is more of a curiosity, since this behaviour is undefined
    ++iCryo;
    std::cout << "  (incremented: " << (*iCryo) << ")" << std::endl;
  */
  }
  
  //
  // begin-constructed
  //
  {
    geo::GeometryCore::cryostat_iterator iCryo(geom);
    std::cout << "Begin-created cryostat iterator: " << (*iCryo) << std::endl;
    
    BOOST_CHECK_EQUAL(iCryo->Cryostat, ID_t(0));
    
    // check that the iterator tests true
    BOOST_CHECK(bool(iCryo));
    BOOST_CHECK(!!iCryo);
    
    // initialize to the beginning directly; this has probably ID's isValid true
    geo::CryostatID BeginID;
    geom->GetBeginID(BeginID);
    geo::GeometryCore::cryostat_iterator iCryoD(geom, BeginID);
    BOOST_CHECK_EQUAL(iCryoD->Cryostat, ID_t(0));
    BOOST_CHECK_EQUAL(iCryoD, iCryo);
    
    // construct from explicit begin position
    geo::GeometryCore::cryostat_iterator iCryoBC
      (geom, geo::GeometryCore::cryostat_iterator::begin_pos);
    BOOST_CHECK_EQUAL(iCryoBC, iCryo);
    
    // construct at begin position by geometry
    geo::GeometryCore::cryostat_iterator iCryoGB = geom->begin_cryostat();
    BOOST_CHECK_EQUAL(iCryoGB, iCryo);
    
    // check access to ID
    BOOST_CHECK_EQUAL(*iCryo, BeginID);
    BOOST_CHECK_EQUAL(iCryo->Cryostat, BeginID.Cryostat);
    
    // check access to geometry element
    geo::CryostatGeo const* pCryo = geom->CryostatPtr(BeginID);
    BOOST_CHECK_EQUAL(iCryo.get(), pCryo);
    
    // test copy and postfix increment
    geo::GeometryCore::cryostat_iterator iCryoI(iCryo++);
    
    BOOST_CHECK_EQUAL(iCryo->Cryostat, ID_t(1));
    BOOST_CHECK_EQUAL(iCryoI->Cryostat, ID_t(0));
    BOOST_CHECK_NE(iCryoI, iCryo);
    
    // test copy and prefix increment
    ++iCryoI;
    BOOST_CHECK_EQUAL(iCryoI->Cryostat, ID_t(1));
    BOOST_CHECK_EQUAL(iCryoI, iCryo);
    
    if (geom->Ncryostats() > 1) {
      ++iCryoI;
      BOOST_CHECK_EQUAL(iCryoI->Cryostat, ID_t(2));
      BOOST_CHECK_NE(iCryoI, iCryo);
    }
    
  }
  
  //
  // constructed from starting point
  //
  {
    // test iterator to last TPC
    geo::CryostatID LastID(geom->Ncryostats() - 1); // last cryostat
    
    geo::GeometryCore::cryostat_iterator iLastCryo(geom, LastID);
    std::cout << "Position-created iterator to last cryostat: "
      << (*iLastCryo) << std::endl;
    
    // check that the iterator tests true
    BOOST_CHECK(bool(iLastCryo));
    BOOST_CHECK(!!iLastCryo);
    
    // check that the pointed ID is as expected
    BOOST_CHECK_EQUAL(*iLastCryo, LastID);
    BOOST_CHECK_EQUAL(iLastCryo->Cryostat, LastID.Cryostat);
    BOOST_CHECK_EQUAL(iLastCryo.get(), geom->CryostatPtr(LastID));
    
    // test increment to past-the-end
    geo::GeometryCore::cryostat_iterator iEndCryo = iLastCryo;
    ++iEndCryo;
    
    // check that the iterator tests false
    BOOST_CHECK(!bool(iEndCryo));
    BOOST_CHECK(!iEndCryo);
    
    BOOST_CHECK_EQUAL(iEndCryo->Cryostat, geom->Ncryostats());
    BOOST_CHECK_EQUAL(iEndCryo, geom->end_cryostat());
    BOOST_CHECK(!iEndCryo.get());
    
  }
  
  //
  // end-constructed
  //
  {
    // construct from end position
    geo::GeometryCore::cryostat_iterator iCryo
      (geom, geo::GeometryCore::cryostat_iterator::end_pos);
    std::cout << "End-created cryostat iterator: " << (*iCryo) << std::endl;
    
    BOOST_CHECK_EQUAL(iCryo->Cryostat, geom->Ncryostats());
    
    // check that the iterator tests false
    BOOST_CHECK(!bool(iCryo));
    BOOST_CHECK(!iCryo);
    
    // check access to geometry element (result of operator* is not defined)
    BOOST_CHECK(!(iCryo.get())); // should get nullptr
    
    // construct at end position by geometry
    geo::GeometryCore::cryostat_iterator iCryoGE = geom->end_cryostat();
    BOOST_CHECK_EQUAL(iCryoGE, iCryo);
    
    // initialize to the end directly; this has probably ID's isValid true
    geo::GeometryCore::cryostat_iterator iCryo2
      (geom, geo::CryostatID(geom->Ncryostats()));
    BOOST_CHECK_EQUAL(iCryo2->Cryostat, geom->Ncryostats());
    BOOST_CHECK_EQUAL(iCryo2, iCryo);
  /*
    // this is more of a curiosity, since this behaviour is undefined
    ++iCryo;
    std::cout << "  (incremented: " << (*iCryo) << ")" << std::endl;
  */
    
  }
  
} // BOOST_AUTO_TEST_CASE( CryostatIteratorsTest )



BOOST_AUTO_TEST_CASE( TPCIteratorsTest )
{
  using ID_t = geo::CryostatID::ID_t;
  const ID_t InvalidID = geo::CryostatID::InvalidID;
  
  geo::GeometryCore const* geom = DUNE35tGeometryTestFixture::GlobalGeometry();
  
  /*
   * public interface (TPC_iterator_base):
   *
   *     /// Default constructor; effect not defined: assign to it before using!
   *     TPC_iterator_base()
   *     
   *     /// Constructor: points to begin
   *     TPC_iterator_base(geo::GeometryCore const* geom)
   *     
   *     /// Constructor: points to the specified cryostat
   *     TPC_iterator_base
   *       (geo::GeometryCore const* geom, GEOID const& start_from)
   *     
   *     /// Constructor: points to begin
   *     TPC_iterator_base(geo::GeometryCore const* geom, BeginPos_t)
   *     
   *     /// Constructor: points to end
   *     TPC_iterator_base(geo::GeometryCore const* geom, EndPos_t)
   *     
   *     /// Returns true if the two iterators point to the same TPC
   *     template <typename OTHERID>
   *     bool operator== (TPC_iterator_base<OTHERID> const& as) const
   *     
   *     /// Returns true if the two iterators point to different TPCs
   *     template <typename OTHERID>
   *     bool operator!= (TPC_iterator_base<OTHERID> const& as) const
   *     
   *     /// Returns the TPCID the iterator points to
   *     LocalID_t const& operator* () const
   *     
   *     /// Returns the TPCID the iterator points to
   *     LocalID_t const* operator-> () const
   *     
   *     /// Prefix increment: returns this iterator pointing to the next TPC
   *     iterator& operator++ ()
   *     
   *     /// Postfix increment: returns the current iterator, then increments it
   *     iterator operator++ (int)
   *     
   *     /// Returns whether the iterator is pointing to a valid TPC
   *     operator bool() const
   *     
   *     /// Returns a pointer to TPC, or nullptr if invalid
   *     ElementPtr_t get() const
   *     
   */
  
  //
  // default constructed
  //
  {
    geo::GeometryCore::TPC_iterator iTPC;
    std::cout << "Default created TPC iterator: " << (*iTPC) << std::endl;
    
    BOOST_CHECK_EQUAL(iTPC->Cryostat, InvalidID);
    BOOST_CHECK_EQUAL(iTPC->TPC, InvalidID);
    
    // check that the iterator tests false
    BOOST_CHECK(!iTPC);
    BOOST_CHECK(!(bool(iTPC)));
  
  }
  
  //
  // begin-constructed
  //
  {
    geo::GeometryCore::TPC_iterator iTPC(geom);
    std::cout << "Begin-created TPC iterator: " << (*iTPC) << std::endl;
    
    BOOST_CHECK_EQUAL(iTPC->Cryostat, ID_t(0));
    BOOST_CHECK_EQUAL(iTPC->TPC, ID_t(0));
    
    // check that the iterator tests true
    BOOST_CHECK(bool(iTPC));
    BOOST_CHECK(!!iTPC);
    
    // initialize to the beginning directly; this has probably ID's isValid true
    geo::TPCID BeginID;
    geom->GetBeginID(BeginID);
    geo::GeometryCore::TPC_iterator iTPCD(geom, BeginID);
    BOOST_CHECK_EQUAL(iTPCD->Cryostat, ID_t(0));
    BOOST_CHECK_EQUAL(iTPCD->TPC, ID_t(0));
    BOOST_CHECK_EQUAL(iTPCD, iTPC);
    
    // construct from explicit begin position
    geo::GeometryCore::TPC_iterator iTPCBC
      (geom, geo::GeometryCore::TPC_iterator::begin_pos);
    BOOST_CHECK_EQUAL(iTPCBC, iTPC);
    
    // construct at begin position by geometry
    geo::GeometryCore::TPC_iterator iTPCGB = geom->begin_TPC();
    BOOST_CHECK_EQUAL(iTPCGB, iTPC);
    
    // check access to ID
    BOOST_CHECK_EQUAL(*iTPC, BeginID);
    BOOST_CHECK_EQUAL(iTPC->Cryostat, BeginID.Cryostat);
    BOOST_CHECK_EQUAL(iTPC->TPC, BeginID.TPC);
    
    // check access to geometry element
    geo::TPCGeo const* pTPC = geom->TPCPtr(BeginID);
    BOOST_CHECK_EQUAL(iTPC.get(), pTPC);
    
    // test copy and postfix increment
    geo::GeometryCore::TPC_iterator iTPCI(iTPC++);
    
    const unsigned int nTPCsInC0 = geom->NTPC(geo::CryostatID(0));
    if (nTPCsInC0 > 1) {
      BOOST_CHECK_EQUAL(iTPCI->Cryostat, ID_t(0));
      BOOST_CHECK_EQUAL(iTPCI->TPC, ID_t(0));
      BOOST_CHECK_EQUAL(iTPC->Cryostat, ID_t(0));
      BOOST_CHECK_EQUAL(iTPC->TPC, ID_t(1));
    }
    BOOST_CHECK_NE(iTPCI, iTPC);
    
    // test copy and prefix increment
    ++iTPCI;
    BOOST_CHECK_EQUAL(iTPCI, iTPC); // arguable if both are end-iterators by now
    
  }
  
  //
  // constructed from starting point
  //
  {
    // test increment flipping cryostat
    geo::TPCID ID(0, 0);
    ID.TPC = geom->NTPC(ID) - 1; // last TPC of first cryostat
    
    geo::GeometryCore::TPC_iterator iTPC(geom, ID);
    
    // check that the iterator tests true
    BOOST_CHECK(bool(iTPC));
    BOOST_CHECK(!!iTPC);
    
    // check that the pointed ID is as expected
    BOOST_CHECK_EQUAL(*iTPC, ID);
    BOOST_CHECK_EQUAL(iTPC->Cryostat, ID.Cryostat);
    BOOST_CHECK_EQUAL(iTPC->TPC, ID.TPC);
    BOOST_CHECK_EQUAL(iTPC.get(), geom->TPCPtr(ID));
    
    ++iTPC;
    // check that the pointed ID is as expected
    BOOST_CHECK_EQUAL(iTPC->Cryostat, ID.Cryostat + 1);
    BOOST_CHECK_EQUAL(iTPC->TPC, ID_t(0));
    
    
    // test iterator to last TPC
    geo::TPCID LastID(geom->Ncryostats() - 1, 0);
    LastID.TPC = geom->NTPC(LastID) - 1; // last TPC of last cryostat
    geo::GeometryCore::TPC_iterator iLastTPC(geom, LastID);
    std::cout << "Position-created iterator to last TPC: "
      << (*iLastTPC) << std::endl;
    
    // check that the iterator tests true
    BOOST_CHECK(bool(iLastTPC));
    BOOST_CHECK(!!iLastTPC);
    
    // check that the pointed ID is as expected
    BOOST_CHECK_EQUAL(*iLastTPC, LastID);
    BOOST_CHECK_EQUAL(iLastTPC->Cryostat, LastID.Cryostat);
    BOOST_CHECK_EQUAL(iLastTPC->TPC, LastID.TPC);
    BOOST_CHECK_EQUAL(iLastTPC.get(), geom->TPCPtr(LastID));
    
    // test increment to past-the-end
    geo::GeometryCore::TPC_iterator iEndTPC = iLastTPC;
    ++iEndTPC;
    
    // check that the iterator tests false
    BOOST_CHECK(!bool(iEndTPC));
    BOOST_CHECK(!iEndTPC);
    
    BOOST_CHECK_EQUAL(iEndTPC->Cryostat, geom->Ncryostats());
    BOOST_CHECK_EQUAL(iEndTPC->TPC, ID_t(0));
    BOOST_CHECK_EQUAL(iEndTPC, geom->end_TPC());
    BOOST_CHECK(!iEndTPC.get());
    
  }
  
  //
  // end-constructed
  //
  {
    // construct from end position
    geo::GeometryCore::TPC_iterator iTPC
      (geom, geo::GeometryCore::TPC_iterator::end_pos);
    std::cout << "End-created TPC iterator: " << (*iTPC) << std::endl;
    
    BOOST_CHECK_EQUAL(iTPC->Cryostat, geom->Ncryostats());
    BOOST_CHECK_EQUAL(iTPC->TPC, ID_t(0));
    
    // check that the iterator tests false
    BOOST_CHECK(!bool(iTPC));
    BOOST_CHECK(!iTPC);
    
    // check access to geometry element (result of operator* is not defined)
    BOOST_CHECK(!(iTPC.get())); // should get nullptr
    
    // construct at end position by geometry
    geo::GeometryCore::TPC_iterator iTPCGE = geom->end_TPC();
    BOOST_CHECK_EQUAL(iTPCGE, iTPC);
    
    // initialize to the end directly; this has probably ID's isValid true
    geo::GeometryCore::TPC_iterator iTPC2
      (geom, geo::TPCID(geom->Ncryostats(), 0));
    BOOST_CHECK_EQUAL(iTPC2->Cryostat, geom->Ncryostats());
    BOOST_CHECK_EQUAL(iTPC2->TPC, ID_t(0));
    BOOST_CHECK_EQUAL(iTPC2, iTPC);
    
  }
  
} // BOOST_AUTO_TEST_CASE( TPCIteratorsTest )



BOOST_AUTO_TEST_CASE( PlaneIteratorsTest )
{
  using ID_t = geo::CryostatID::ID_t;
  const ID_t InvalidID = geo::CryostatID::InvalidID;
  
  geo::GeometryCore const* geom = DUNE35tGeometryTestFixture::GlobalGeometry();
  
  /*
   * public interface (plane_iterator_base):
   *
   *     /// Default constructor; effect not defined: assign to it before using!
   *     plane_iterator_base()
   *     
   *     /// Constructor: points to begin
   *     plane_iterator_base(geo::GeometryCore const* geom)
   *     
   *     /// Constructor: points to the specified cryostat
   *     plane_iterator_base
   *       (geo::GeometryCore const* geom, GEOID const& start_from)
   *     
   *     /// Constructor: points to begin
   *     plane_iterator_base(geo::GeometryCore const* geom, BeginPos_t)
   *     
   *     /// Constructor: points to end
   *     plane_iterator_base(geo::GeometryCore const* geom, EndPos_t)
   *     
   *     // TODO reconsider if the additional template is indeed needed
   *     /// Returns true if the two iterators point to the same plane
   *     template <typename OTHERID>
   *     bool operator== (plane_iterator_base<OTHERID> const& as) const
   *     
   *     /// Returns true if the two iterators point to different planes
   *     template <typename OTHERID>
   *     bool operator!= (plane_iterator_base<OTHERID> const& as) const
   *     
   *     /// Returns the PlaneID the iterator points to
   *     LocalID_t const& operator* () const
   *     
   *     /// Returns the PlaneID the iterator points to
   *     LocalID_t const* operator-> () const
   *     
   *     /// Prefix increment: returns this iterator pointing to the next plane
   *     iterator& operator++ ()
   *     
   *     /// Postfix increment: returns the current iterator, then increments it
   *     iterator operator++ (int)
   *     
   *     /// Returns whether the iterator is pointing to a valid plane
   *     operator bool() const
   *     
   *     /// Returns a pointer to plane, or nullptr if invalid
   *     ElementPtr_t get() const
   *     
   */
  
  //
  // default constructed
  //
  {
    geo::GeometryCore::plane_iterator iPlane;
    std::cout << "Default created plane iterator: " << (*iPlane) << std::endl;
    
    BOOST_CHECK_EQUAL(iPlane->Cryostat, InvalidID);
    BOOST_CHECK_EQUAL(iPlane->TPC, InvalidID);
    BOOST_CHECK_EQUAL(iPlane->Plane, InvalidID);
    
    // check that the iterator tests false
    BOOST_CHECK(!iPlane);
    BOOST_CHECK(!(bool(iPlane)));
  
  }
  
  //
  // begin-constructed
  //
  {
    geo::GeometryCore::plane_iterator iPlane(geom);
    std::cout << "Begin-created plane iterator: " << (*iPlane) << std::endl;
    
    BOOST_CHECK_EQUAL(iPlane->Cryostat, ID_t(0));
    BOOST_CHECK_EQUAL(iPlane->TPC, ID_t(0));
    BOOST_CHECK_EQUAL(iPlane->Plane, ID_t(0));
    
    // check that the iterator tests true
    BOOST_CHECK(bool(iPlane));
    BOOST_CHECK(!!iPlane);
    
    // initialize to the beginning directly; this has probably ID's isValid true
    geo::PlaneID BeginID;
    geom->GetBeginID(BeginID);
    geo::GeometryCore::plane_iterator iPlaneD(geom, BeginID);
    BOOST_CHECK_EQUAL(iPlaneD->Cryostat, ID_t(0));
    BOOST_CHECK_EQUAL(iPlaneD->TPC, ID_t(0));
    BOOST_CHECK_EQUAL(iPlaneD->Plane, ID_t(0));
    BOOST_CHECK_EQUAL(iPlaneD, iPlane);
    
    // construct from explicit begin position
    geo::GeometryCore::plane_iterator iPlaneBC
      (geom, geo::GeometryCore::plane_iterator::begin_pos);
    BOOST_CHECK_EQUAL(iPlaneBC, iPlane);
    
    // construct at begin position by geometry
    geo::GeometryCore::plane_iterator iPlaneGB = geom->begin_plane();
    BOOST_CHECK_EQUAL(iPlaneGB, iPlane);
    
    // check access to ID
    BOOST_CHECK_EQUAL(*iPlane, BeginID);
    BOOST_CHECK_EQUAL(iPlane->Cryostat, BeginID.Cryostat);
    BOOST_CHECK_EQUAL(iPlane->TPC, BeginID.TPC);
    BOOST_CHECK_EQUAL(iPlane->Plane, BeginID.Plane);
    
    // check access to geometry element
    geo::PlaneGeo const* pPlane = geom->PlanePtr(BeginID);
    BOOST_CHECK_EQUAL(iPlane.get(), pPlane);
    
    // test copy and postfix increment
    geo::GeometryCore::plane_iterator iPlaneI(iPlane++);
    
    const unsigned int nPlanesInC0T0 = geom->Nplanes(geo::TPCID(0, 0));
    if (nPlanesInC0T0 > 1) {
      BOOST_CHECK_EQUAL(iPlaneI->Cryostat, ID_t(0));
      BOOST_CHECK_EQUAL(iPlaneI->TPC, ID_t(0));
      BOOST_CHECK_EQUAL(iPlaneI->Plane, ID_t(0));
      BOOST_CHECK_EQUAL(iPlane->Cryostat, ID_t(0));
      BOOST_CHECK_EQUAL(iPlane->TPC, ID_t(0));
      BOOST_CHECK_EQUAL(iPlane->Plane, ID_t(1));
    }
    BOOST_CHECK_NE(iPlaneI, iPlane);
    
    // test copy and prefix increment
    ++iPlaneI;
    BOOST_CHECK_EQUAL(iPlaneI, iPlane); // arguable if both are end-iterators by now
    
  }
  
  //
  // constructed from starting point
  //
  {
    // test increment flipping TPC
    geo::PlaneID ID(0, 0, 0);
    ID.Plane = geom->Nplanes(ID) - 1; // last plane of first TPC
    
    geo::GeometryCore::plane_iterator iPlane(geom, ID);
    
    // check that the iterator tests true
    BOOST_CHECK(bool(iPlane));
    BOOST_CHECK(!!iPlane);
    
    // check that the pointed ID is as expected
    BOOST_CHECK_EQUAL(*iPlane, ID);
    BOOST_CHECK_EQUAL(iPlane->Cryostat, ID.Cryostat);
    BOOST_CHECK_EQUAL(iPlane->TPC, ID.TPC);
    BOOST_CHECK_EQUAL(iPlane->Plane, ID.Plane);
    BOOST_CHECK_EQUAL(iPlane.get(), geom->PlanePtr(ID));
    
    // check that the pointed ID is as expected
    ++iPlane;
    if (ID.TPC + 1 < geom->NTPC(ID)) {
      BOOST_CHECK_EQUAL(iPlane->Cryostat, ID.Cryostat);
      BOOST_CHECK_EQUAL(iPlane->TPC, ID.TPC + 1);
      BOOST_CHECK_EQUAL(iPlane->Plane, ID_t(0));
    }
    else {
      BOOST_CHECK_EQUAL(iPlane->Cryostat, ID.Cryostat + 1);
      BOOST_CHECK_EQUAL(iPlane->TPC, ID_t(0));
      BOOST_CHECK_EQUAL(iPlane->Plane, ID_t(0));
    }
    
    // test iterator to last plane
    geo::PlaneID LastID(geom->Ncryostats() - 1, 0, 0);
    LastID.TPC = geom->NTPC(LastID) - 1; // last TPC of last cryostat
    LastID.Plane = geom->Nplanes(LastID) - 1; // last plane of last TPC
    geo::GeometryCore::plane_iterator iLastPlane(geom, LastID);
    std::cout << "Position-created iterator to last plane: "
      << (*iLastPlane) << std::endl;
    
    // check that the iterator tests true
    BOOST_CHECK(bool(iLastPlane));
    BOOST_CHECK(!!iLastPlane);
    
    // check that the pointed ID is as expected
    BOOST_CHECK_EQUAL(*iLastPlane, LastID);
    BOOST_CHECK_EQUAL(iLastPlane->Cryostat, LastID.Cryostat);
    BOOST_CHECK_EQUAL(iLastPlane->TPC, LastID.TPC);
    BOOST_CHECK_EQUAL(iLastPlane->Plane, LastID.Plane);
    BOOST_CHECK_EQUAL(iLastPlane.get(), geom->PlanePtr(LastID));
    
    // test increment to past-the-end
    geo::GeometryCore::plane_iterator iEndPlane = iLastPlane;
    ++iEndPlane;
    
    // check that the iterator tests false
    BOOST_CHECK(!bool(iEndPlane));
    BOOST_CHECK(!iEndPlane);
    
    BOOST_CHECK_EQUAL(iEndPlane->Cryostat, geom->Ncryostats());
    BOOST_CHECK_EQUAL(iEndPlane->TPC, ID_t(0));
    BOOST_CHECK_EQUAL(iEndPlane->Plane, ID_t(0));
    BOOST_CHECK_EQUAL(iEndPlane, geom->end_plane());
    BOOST_CHECK(!iEndPlane.get());
    
  }
  
  //
  // end-constructed
  //
  {
    // construct from end position
    geo::GeometryCore::plane_iterator iPlane
      (geom, geo::GeometryCore::plane_iterator::end_pos);
    std::cout << "End-created plane iterator: " << (*iPlane) << std::endl;
    
    BOOST_CHECK_EQUAL(iPlane->Cryostat, geom->Ncryostats());
    BOOST_CHECK_EQUAL(iPlane->TPC, ID_t(0));
    BOOST_CHECK_EQUAL(iPlane->Plane, ID_t(0));
    
    // check that the iterator tests false
    BOOST_CHECK(!bool(iPlane));
    BOOST_CHECK(!iPlane);
    
    // check access to geometry element (result of operator* is not defined)
    BOOST_CHECK(!(iPlane.get())); // should get nullptr
    
    // construct at end position by geometry
    geo::GeometryCore::plane_iterator iPlaneGE = geom->end_plane();
    BOOST_CHECK_EQUAL(iPlaneGE, iPlane);
    
    // initialize to the end directly; this has probably ID's isValid true
    geo::GeometryCore::plane_iterator iPlane2
      (geom, geo::PlaneID(geom->Ncryostats(), 0, 0));
    BOOST_CHECK_EQUAL(iPlane2->Cryostat, geom->Ncryostats());
    BOOST_CHECK_EQUAL(iPlane2->TPC, ID_t(0));
    BOOST_CHECK_EQUAL(iPlane2->Plane, ID_t(0));
    BOOST_CHECK_EQUAL(iPlane2, iPlane);
    
  }
} // BOOST_AUTO_TEST_CASE( PlaneIteratorsTest )



BOOST_AUTO_TEST_CASE( WireIteratorsTest )
{
  using ID_t = geo::CryostatID::ID_t;
  const ID_t InvalidID = geo::CryostatID::InvalidID;
  
  geo::GeometryCore const* geom = DUNE35tGeometryTestFixture::GlobalGeometry();
  
  /*
   * public interface (wire_iterator_base):
   *
   *     /// Default constructor; effect not defined: assign to it before using!
   *     wire_iterator_base()
   *     
   *     /// Constructor: points to begin
   *     wire_iterator_base(geo::GeometryCore const* geom)
   *     
   *     /// Constructor: points to the specified cryostat
   *     wire_iterator_base
   *       (geo::GeometryCore const* geom, GEOID const& start_from)
   *     
   *     /// Constructor: points to begin
   *     wire_iterator_base(geo::GeometryCore const* geom, BeginPos_t)
   *     
   *     /// Constructor: points to end
   *     wire_iterator_base(geo::GeometryCore const* geom, EndPos_t)
   *     
   *     // TODO reconsider if the additional template is indeed needed
   *     /// Returns true if the two iterators point to the same wire
   *     template <typename OTHERID>
   *     bool operator== (wire_iterator_base<OTHERID> const& as) const
   *     
   *     /// Returns true if the two iterators point to different wires
   *     template <typename OTHERID>
   *     bool operator!= (wire_iterator_base<OTHERID> const& as) const
   *     
   *     /// Returns the WireID the iterator points to
   *     LocalID_t const& operator* () const
   *     
   *     /// Returns the WireID the iterator points to
   *     LocalID_t const* operator-> () const
   *     
   *     /// Prefix increment: returns this iterator pointing to the next wire
   *     iterator& operator++ ()
   *     
   *     /// Postfix increment: returns the current iterator, then increments it
   *     iterator operator++ (int)
   *     
   *     /// Returns whether the iterator is pointing to a valid wire
   *     operator bool() const
   *     
   *     /// Returns a pointer to wire, or nullptr if invalid
   *     ElementPtr_t get() const
   *     
   */
  
  //
  // default constructed
  //
  {
    geo::GeometryCore::wire_iterator iWire;
    std::cout << "Default created wire iterator: " << (*iWire) << std::endl;
    
    BOOST_CHECK_EQUAL(iWire->Cryostat, InvalidID);
    BOOST_CHECK_EQUAL(iWire->TPC, InvalidID);
    BOOST_CHECK_EQUAL(iWire->Plane, InvalidID);
    BOOST_CHECK_EQUAL(iWire->Wire, InvalidID);
    
    // check that the iterator tests false
    BOOST_CHECK(!iWire);
    BOOST_CHECK(!(bool(iWire)));
  
  }
  
  //
  // begin-constructed
  //
  {
    geo::GeometryCore::wire_iterator iWire(geom);
    std::cout << "Begin-created wire iterator: " << (*iWire) << std::endl;
    
    BOOST_CHECK_EQUAL(iWire->Cryostat, ID_t(0));
    BOOST_CHECK_EQUAL(iWire->TPC, ID_t(0));
    BOOST_CHECK_EQUAL(iWire->Plane, ID_t(0));
    BOOST_CHECK_EQUAL(iWire->Wire, ID_t(0));
    
    // check that the iterator tests true
    BOOST_CHECK(bool(iWire));
    BOOST_CHECK(!!iWire);
    
    // initialize to the beginning directly; this has probably ID's isValid true
    geo::WireID BeginID;
    geom->GetBeginID(BeginID);
    geo::GeometryCore::wire_iterator iWireD(geom, BeginID);
    BOOST_CHECK_EQUAL(iWireD->Cryostat, ID_t(0));
    BOOST_CHECK_EQUAL(iWireD->TPC, ID_t(0));
    BOOST_CHECK_EQUAL(iWireD->Plane, ID_t(0));
    BOOST_CHECK_EQUAL(iWireD->Wire, ID_t(0));
    BOOST_CHECK_EQUAL(iWireD, iWire);
    
    // construct from explicit begin position
    geo::GeometryCore::wire_iterator iWireBC
      (geom, geo::GeometryCore::wire_iterator::begin_pos);
    BOOST_CHECK_EQUAL(iWireBC, iWire);
    
    // construct at begin position by geometry
    geo::GeometryCore::wire_iterator iWireGB = geom->begin_wire();
    BOOST_CHECK_EQUAL(iWireGB, iWire);
    
    // check access to ID
    BOOST_CHECK_EQUAL(*iWire, BeginID);
    BOOST_CHECK_EQUAL(iWire->Cryostat, BeginID.Cryostat);
    BOOST_CHECK_EQUAL(iWire->TPC, BeginID.TPC);
    BOOST_CHECK_EQUAL(iWire->Plane, BeginID.Plane);
    BOOST_CHECK_EQUAL(iWire->Wire, BeginID.Wire);
    
    // check access to geometry element
    geo::WireGeo const* pWire = geom->WirePtr(BeginID);
    BOOST_CHECK_EQUAL(iWire.get(), pWire);
    
    // test copy and postfix increment
    geo::GeometryCore::wire_iterator iWireI(iWire++);
    
    const unsigned int nWiresInC0T0P0 = geom->Nwires(geo::PlaneID(0, 0, 0));
    if (nWiresInC0T0P0 > 1) {
      BOOST_CHECK_EQUAL(iWireI->Cryostat, ID_t(0));
      BOOST_CHECK_EQUAL(iWireI->TPC, ID_t(0));
      BOOST_CHECK_EQUAL(iWireI->Plane, ID_t(0));
      BOOST_CHECK_EQUAL(iWireI->Wire, ID_t(0));
      BOOST_CHECK_EQUAL(iWire->Cryostat, ID_t(0));
      BOOST_CHECK_EQUAL(iWire->TPC, ID_t(0));
      BOOST_CHECK_EQUAL(iWire->Plane, ID_t(0));
      BOOST_CHECK_EQUAL(iWire->Wire, ID_t(1));
    }
    BOOST_CHECK_NE(iWireI, iWire);
    
    // test copy and prefix increment
    ++iWireI;
    BOOST_CHECK_EQUAL(iWireI, iWire); // arguable if both are end-iterators by now
    
  }
  
  //
  // constructed from starting point
  //
  {
    // test increment flipping plane
    geo::WireID ID(0, 0, 0, 0);
    ID.Wire = geom->Nwires(ID) - 1; // last wire of first plane
    
    geo::GeometryCore::wire_iterator iWire(geom, ID);
    
    // check that the iterator tests true
    BOOST_CHECK(bool(iWire));
    BOOST_CHECK(!!iWire);
    
    // check that the pointed ID is as expected
    BOOST_CHECK_EQUAL(*iWire, ID);
    BOOST_CHECK_EQUAL(iWire->Cryostat, ID.Cryostat);
    BOOST_CHECK_EQUAL(iWire->TPC, ID.TPC);
    BOOST_CHECK_EQUAL(iWire->Plane, ID.Plane);
    BOOST_CHECK_EQUAL(iWire->Wire, ID.Wire);
    BOOST_CHECK_EQUAL(iWire.get(), geom->WirePtr(ID));
    
    ++iWire;
    // check that the pointed ID is as expected
    if (ID.Plane + 1 < geom->Nplanes(ID)) {
      BOOST_CHECK_EQUAL(iWire->Cryostat, ID_t(0));
      BOOST_CHECK_EQUAL(iWire->TPC, ID_t(0));
      BOOST_CHECK_EQUAL(iWire->Plane, ID.Plane + 1);
      BOOST_CHECK_EQUAL(iWire->Wire, ID_t(0));
    } else if (ID.TPC + 1 < geom->NTPC(ID)) {
      BOOST_CHECK_EQUAL(iWire->Cryostat, ID_t(0));
      BOOST_CHECK_EQUAL(iWire->TPC, ID.TPC + 1);
      BOOST_CHECK_EQUAL(iWire->Plane, ID_t(0));
      BOOST_CHECK_EQUAL(iWire->Wire, ID_t(0));
    } else {
      BOOST_CHECK_EQUAL(iWire->Cryostat, ID.Cryostat + 1);
      BOOST_CHECK_EQUAL(iWire->TPC, ID_t(0));
      BOOST_CHECK_EQUAL(iWire->Plane, ID_t(0));
      BOOST_CHECK_EQUAL(iWire->Wire, ID_t(0));
	 }
    
    // test iterator to last wire
    geo::WireID LastID(geom->Ncryostats() - 1, 0, 0, 0);
    LastID.TPC = geom->NTPC(LastID) - 1; // last TPC of last cryostat
    LastID.Plane = geom->Nplanes(LastID) - 1; // last plane of last TPC
    LastID.Wire = geom->Nwires(LastID) - 1; // last wire of last plane
    geo::GeometryCore::wire_iterator iLastWire(geom, LastID);
    std::cout << "Position-created iterator to last wire: "
      << (*iLastWire) << std::endl;
    
    // check that the iterator tests true
    BOOST_CHECK(bool(iLastWire));
    BOOST_CHECK(!!iLastWire);
    
    // check that the pointed ID is as expected
    BOOST_CHECK_EQUAL(*iLastWire, LastID);
    BOOST_CHECK_EQUAL(iLastWire->Cryostat, LastID.Cryostat);
    BOOST_CHECK_EQUAL(iLastWire->TPC, LastID.TPC);
    BOOST_CHECK_EQUAL(iLastWire->Plane, LastID.Plane);
    BOOST_CHECK_EQUAL(iLastWire->Wire, LastID.Wire);
    BOOST_CHECK_EQUAL(iLastWire.get(), geom->WirePtr(LastID));
    
    // test increment to past-the-end
    geo::GeometryCore::wire_iterator iEndWire = iLastWire;
    ++iEndWire;
    
    // check that the iterator tests false
    BOOST_CHECK(!bool(iEndWire));
    BOOST_CHECK(!iEndWire);
    
    BOOST_CHECK_EQUAL(iEndWire->Cryostat, geom->Ncryostats());
    BOOST_CHECK_EQUAL(iEndWire->TPC, ID_t(0));
    BOOST_CHECK_EQUAL(iEndWire->Plane, ID_t(0));
    BOOST_CHECK_EQUAL(iEndWire->Wire, ID_t(0));
    BOOST_CHECK_EQUAL(iEndWire, geom->end_wire());
    BOOST_CHECK(!iEndWire.get());
    
  }
  
  //
  // end-constructed
  //
  {
    // construct from end position
    geo::GeometryCore::wire_iterator iWire
      (geom, geo::GeometryCore::wire_iterator::end_pos);
    std::cout << "End-created end iterator: " << (*iWire) << std::endl;
    
    BOOST_CHECK_EQUAL(iWire->Cryostat, geom->Ncryostats());
    BOOST_CHECK_EQUAL(iWire->TPC, ID_t(0));
    BOOST_CHECK_EQUAL(iWire->Plane, ID_t(0));
    BOOST_CHECK_EQUAL(iWire->Wire, ID_t(0));
    
    // check that the iterator tests false
    BOOST_CHECK(!bool(iWire));
    BOOST_CHECK(!iWire);
    
    // check access to geometry element (result of operator* is not defined)
    BOOST_CHECK(!(iWire.get())); // should get nullptr
    
    // construct at end position by geometry
    geo::GeometryCore::wire_iterator iWireGE = geom->end_wire();
    BOOST_CHECK_EQUAL(iWireGE, iWire);
    
    // initialize to the end directly; this has probably ID's isValid true
    geo::GeometryCore::wire_iterator iWire2
      (geom, geo::WireID(geom->Ncryostats(), 0, 0, 0));
    BOOST_CHECK_EQUAL(iWire2->Cryostat, geom->Ncryostats());
    BOOST_CHECK_EQUAL(iWire2->TPC, ID_t(0));
    BOOST_CHECK_EQUAL(iWire2->Plane, ID_t(0));
    BOOST_CHECK_EQUAL(iWire2->Wire, ID_t(0));
    BOOST_CHECK_EQUAL(iWire2, iWire);
    
  }
  
} // BOOST_AUTO_TEST_CASE( WireIteratorsTest )


// BOOST_AUTO_TEST_SUITE_END()

