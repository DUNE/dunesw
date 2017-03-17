/**
 * @file   geometry_unit_test_dune.h
 * @brief  Class for objects initializing DUNE geometries
 * @date   May 11th, 2015
 * @author petrillo@fnal.gov
 * 
 * Provides an environment for easy set up of DUNE-aware tests.
 * Keep in mind that the channel mapping algorithm must be hard-coded and, if
 * using Boost unit test, the configuration file location must be hard coded too
 * (or you can use the provided configuration).
 * 
 */

#ifndef TEST_GEOMETRY_UNIT_TEST_DUNE_H
#define TEST_GEOMETRY_UNIT_TEST_DUNE_H

// LArSoft libraries
#include "test/Geometry/geometry_unit_test_base.h"

// C/C++ standard libraries
#include <string>


namespace dune {
  
  /// Namespace including DUNE-specific testing
  namespace testing {
    
    // The old geometry objects foor 35t and FD have been removed because the new
    // initialisation scheme of their mapping is not compatible with the geometry
    // support infrastructure in LArSoft unit tests.
    // The reason is that that system does not use ExptGeoInterfaceHelper but
    // instead replicates it, which was possible as long as the code would be
    // common between experiments, that is not any more.
    
    // This file is left here as placeholder, waiting for Dual Phase support
    // to be ready. That one still uses the old scheme.
    
    /** ************************************************************************
     * @brief Class holding the configuration for a DUNE FD Dual Phase fixture
     * @tparam CHANNELMAP the class used for channel mapping
     * @see BasicGeometryEnvironmentConfiguration, GeometryTesterEnvironment
     *
     * This class needs to be fully constructed by the default constructor
     * in order to be useful as Boost unit test fixture.
     * It is supposed to be passed as a template parameter to another class
     * that can store an instance of it and extract configuration information
     * from it.
     * 
     * This class should be used with ChannelMapCRMAlg.
     * 
     * We reuse BasicGeometryEnvironmentConfiguration as base class and we
     * override its setup.
     */
    template <typename CHANNELMAP>
    struct DUNEFDDPGeometryEnvironmentConfiguration:
      public ::testing::BasicGeometryEnvironmentConfiguration<CHANNELMAP>
    {
      // remember that BasicGeometryEnvironmentConfiguration is not polymorphic
      using base_t
        = ::testing::BasicGeometryEnvironmentConfiguration<CHANNELMAP>;
      
      /// Default constructor; this is what is used in Boost unit test
      DUNEFDDPGeometryEnvironmentConfiguration()
        {
          // overwrite the configuration that happened in the base class:
          base_t::SetApplicationName("DUNEFDDPGeometryTest");
          base_t::SetDefaultGeometryConfiguration(R"(
              Name:      "dunedphase10kt_v2"
              GDML:      "dunedphase10kt_v2.gdml"
              ROOT:      "dunedphase10kt_v2.gdml"
              SortingParameters: { ChannelsPerOpDet: 1 }
              SurfaceY: 147828 # Underground option. 4850 feet to cm. from DocDb-3833
            )");
        } // DUNEFDDPGeometryEnvironmentConfiguration()
      
      /// Constructor; accepts the name as parameter
      DUNEFDDPGeometryEnvironmentConfiguration(std::string name):
        DUNEFDDPGeometryEnvironmentConfiguration()
        { base_t::SetApplicationName(name); }
      
    }; // class DUNEFDDPGeometryEnvironmentConfiguration<>
    
    
  } // namespace testing
} // namespace dune

#endif // TEST_GEOMETRY_UNIT_TEST_DUNE_H
