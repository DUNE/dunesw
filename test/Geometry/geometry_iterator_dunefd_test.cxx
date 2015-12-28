/**
 * @file   geometry_iterator_dunefd_test.cxx
 * @brief  Unit test for geometry iterators on DUNE Far Detector
 * @date   May 11th, 2015
 * @author petrillo@fnal.gov
 * 
 * Usage: just run the executable.
 * Boost unit testing environment keeps the arguments secret anyway.
 */

// Boost test libraries; defining this symbol tells boost somehow to generate
// a main() function; Boost is pulled in by geometry_boost_unit_test_base.h
#define BOOST_TEST_MODULE GeometryIteratorTestDUNEFD

// LArSoft libraries
#include "test/Geometry/geometry_unit_test_dune.h"
#include "test/Geometry/boost_unit_test_base.h"
#include "test/Geometry/GeometryIteratorTestAlg.h"
#include "Geometry/GeometryCore.h"
#include "dune/Geometry/ChannelMapAPAAlg.h"

// utility libraries
#include "messagefacility/MessageLogger/MessageLogger.h"

// C/C++ standard libraries
#include <string>
#include <iostream>


//------------------------------------------------------------------------------
//---  The test environment
//---

// we define here all the configuration that is needed;
// in the specific, the type of the channel mapping and a proper test name,
// used for output only; we use DUNEFDGeometryEnvironmentConfiguration
// as base class, that is already configured to use DUNE FD geometry.
// We wrap it in testing::BoostCommandLineConfiguration<> so that it can learn
// the configuration file name from the command line.
struct DUNEFDGeometryConfiguration:
  public testing::BoostCommandLineConfiguration<
    dune::testing::DUNEFDGeometryEnvironmentConfiguration
      <geo::ChannelMapAPAAlg>
    >
{
  /// Constructor: overrides the application name; ignores command line
  DUNEFDGeometryConfiguration()
    { SetApplicationName("GeometryIteratorUnitTest"); }
}; // class DUNEFDGeometryConfiguration


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
  private testing::GeometryTesterEnvironment<DUNEFDGeometryConfiguration>
{
  using Tester_t = geo::GeometryIteratorTestAlg;
  
  using TesterRegistry_t = testing::TestSharedGlobalResource<Tester_t>;
  
    public:
  
  /// Constructor: initialize the tester with the Geometry from base class
  DUNEFDGeometryIteratorTestFixture()
    {
      // propose a new global tester
      // (constructed with the specified argumrents);
      // if there is already one, never mind: we stick to that one
      TesterRegistry_t::ProposeDefaultSharedResource(TesterParameters());
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


BOOST_AUTO_TEST_CASE( CryostatIDIteratorsTest )
{
  GlobalTester().CryostatIDIteratorsTest();
} // BOOST_AUTO_TEST_CASE( CryostatIDIteratorsTest )



BOOST_AUTO_TEST_CASE( CryostatIteratorsTest )
{
  GlobalTester().CryostatIteratorsTest();
} // BOOST_AUTO_TEST_CASE( CryostatIteratorsTest )



BOOST_AUTO_TEST_CASE( TPCIDIteratorsTest )
{
  GlobalTester().TPCIDIteratorsTest();
} // BOOST_AUTO_TEST_CASE( TPCIDIteratorsTest )



BOOST_AUTO_TEST_CASE( TPCIteratorsTest )
{
  GlobalTester().TPCIteratorsTest();
} // BOOST_AUTO_TEST_CASE( TPCIteratorsTest )



BOOST_AUTO_TEST_CASE( PlaneIDIteratorsTest )
{
  GlobalTester().PlaneIDIteratorsTest();
} // BOOST_AUTO_TEST_CASE( PlaneIDIteratorsTest )



BOOST_AUTO_TEST_CASE( PlaneIteratorsTest )
{
  GlobalTester().PlaneIteratorsTest();
} // BOOST_AUTO_TEST_CASE( PlaneIteratorsTest )



BOOST_AUTO_TEST_CASE( WireIDIteratorsTest )
{
  GlobalTester().WireIDIteratorsTest();
} // BOOST_AUTO_TEST_CASE( WireIDIteratorsTest )



BOOST_AUTO_TEST_CASE( WireIteratorsTest )
{
  GlobalTester().WireIteratorsTest();
} // BOOST_AUTO_TEST_CASE( WireIteratorsTest )


BOOST_AUTO_TEST_SUITE_END()
