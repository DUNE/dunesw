/**
 * @file   geometry_iterator_dunefd_test.cxx
 * @brief  Unit test for geometry iterators on DUNE Far Detector
 * @date   May 11th, 2015
 * @author petrillo@fnal.gov
 * 
 * Usage: just run the executable.
 * Boost unit testing environment keeps the arguments secret anyway.
 */

// LArSoft libraries
#include "test/Geometry/geometry_unit_test_dune.h"
#include "test/Geometry/GeometryIteratorTestAlg.h"
#include "Geometry/GeometryCore.h"
#include "lbne/Geometry/ChannelMapAPAAlg.h"

// utility libraries
#include "messagefacility/MessageLogger/MessageLogger.h"

// Boost libraries
#define BOOST_TEST_MODULE GeometryIteratorTestDUNEFD
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
using DUNEFDGeometryConfiguration
  = lbne::testing::DUNEFDGeometryFixtureConfigurer<geo::ChannelMapAPAAlg>;

/*
 * Our fixture is based on GeometryTesterFixture, configured with the object
 * above.
 * It provides:
 * - `GlobalTester()`, (static) returning a global configured instance of the
 *   test algorithm.
 * 
 * The testing::TestSharedGlobalResource<> facility provides a singleton
 * instance of the tester algorithm, shared through the whole program.
 * This is better suited to be used as global fixture, as no per-object
 * interface is provided.
 */
class DUNEFDGeometryIteratorTestFixture:
  private testing::SharedGeometryTesterFixture<DUNEFDGeometryConfiguration>
{
  using Tester_t = geo::GeometryIteratorTestAlg;
  
  using TesterRegistry_t = testing::TestSharedGlobalResource<Tester_t>;
  
    public:
  
  /// Constructor: initialize the tester with the Geometry from base class
  DUNEFDGeometryIteratorTestFixture()
    {
      // create a new global tester
      TesterRegistry_t::ProposeDefaultSharedResource(TesterConfiguration());
      // configure it
      GlobalTester().Setup(*Geometry());
    }
  
  /// Retrieves the global tester
  static Tester_t& GlobalTester() { return TesterRegistry_t::Resource(); }
  
}; // class DUNEFDGeometryIteratorTestFixture


//------------------------------------------------------------------------------
//---  The tests
//---

//------------------------------------------------------------------------------
//---  The tests
//---
BOOST_FIXTURE_TEST_SUITE
  (GeometryIterators, DUNEFDGeometryIteratorTestFixture)
// BOOST_GLOBAL_FIXTURE(DUNEFDGeometryIteratorTestFixture)


BOOST_AUTO_TEST_CASE( CryostatIteratorsTest )
{
  GlobalTester().CryostatIteratorsTest();
} // BOOST_AUTO_TEST_CASE( CryostatIteratorsTest )



BOOST_AUTO_TEST_CASE( TPCIteratorsTest )
{
  GlobalTester().TPCIteratorsTest();
} // BOOST_AUTO_TEST_CASE( TPCIteratorsTest )



BOOST_AUTO_TEST_CASE( PlaneIteratorsTest )
{
  GlobalTester().PlaneIteratorsTest();
} // BOOST_AUTO_TEST_CASE( PlaneIteratorsTest )



BOOST_AUTO_TEST_CASE( WireIteratorsTest )
{
  GlobalTester().WireIteratorsTest();
} // BOOST_AUTO_TEST_CASE( WireIteratorsTest )


BOOST_AUTO_TEST_SUITE_END()
