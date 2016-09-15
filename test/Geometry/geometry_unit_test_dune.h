/**
 * @file   geometry_unit_test_dune.h
 * @brief  Class for objects initializing DUNE geometries
 * @date   May 11th, 2015
 * @author petrillo@fnal.gov
 * 
 * Provides an environment for easy set up of DUNE-aware tests.
 * Keep in mind that the channel mapping algorithm must be hard-coded
 * (no software switch between 35t optimized and non-optimized version) and, if
 * using Boost unit test, the configuration file location must be hard coded too
 * (or you can use the provided configuration).
 * 
 * For an example of usage, see larcore/test/Geometry/geometry_iterator_test.cxx
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
    
    /** ************************************************************************
     * @brief Class holding the configuration for a DUNE 35t fixture
     * @tparam CHANNELMAP the class used for channel mapping
     * @see BasicGeometryEnvironmentConfiguration, GeometryTesterEnvironment
     *
     * This class needs to be fully constructed by the default constructor
     * in order to be useful as Boost unit test fixture.
     * It is supposed to be passed as a template parameter to another class
     * that can store an instance of it and extract configuration information
     * from it.
     * 
     * This class should be used with ChannelMap35tOptAlg, since by default it
     * sets a geometry v3.
     * 
     * We reuse BasicGeometryEnvironmentConfiguration as base class and we override its
     * setup.
     */
    template <typename CHANNELMAP>
    struct DUNE35tGeometryEnvironmentConfiguration:
      public ::testing::BasicGeometryEnvironmentConfiguration<CHANNELMAP>
    {
      // remember that BasicGeometryEnvironmentConfiguration is not polymorphic
      using base_t
         = ::testing::BasicGeometryEnvironmentConfiguration<CHANNELMAP>;
      
      /// Default constructor; this is what is used in Boost unit test
      DUNE35tGeometryEnvironmentConfiguration() { DUNEdefaultInit(); }
      
      /// Constructor; accepts the name as parameter
      DUNE35tGeometryEnvironmentConfiguration(std::string name):
        DUNE35tGeometryEnvironmentConfiguration()
        { base_t::SetApplicationName(name); }
      
        private:
      void DUNEdefaultInit()
        {
          // overwrite the configuration that happened in the base class:
          base_t::SetApplicationName("DUNE35tGeometryTest");
          base_t::SetDefaultGeometryConfiguration(R"(
              Name:     "dune35t"
              GDML:     "dune35t4apa_v5.gdml"
              ROOT:     "dune35t4apa_v5.gdml"
              SortingParameters: {
                DetectorVersion: "dune35t4apa_v5" 
                ChannelsPerOpDet: 12
              } 
              SurfaceY:  0.0e2 # in cm, vertical distance to the surface
            )");
        } // DUNE35tGeometryEnvironmentConfiguration()
      
    }; // class DUNE35tGeometryEnvironmentConfiguration<>
    
    
    /** ************************************************************************
     * @brief Class holding the configuration for a DUNE FD fixture
     * @tparam CHANNELMAP the class used for channel mapping
     * @see BasicGeometryEnvironmentConfiguration, GeometryTesterEnvironment
     *
     * This class needs to be fully constructed by the default constructor
     * in order to be useful as Boost unit test fixture.
     * It is supposed to be passed as a template parameter to another class
     * that can store an instance of it and extract configuration information
     * from it.
     * 
     * This class should be used with ChannelMapAPAAlg.
     * 
     * We reuse BasicGeometryEnvironmentConfiguration as base class and we
     * override its setup.
     */
    template <typename CHANNELMAP>
    struct DUNEFDGeometryEnvironmentConfiguration:
      public ::testing::BasicGeometryEnvironmentConfiguration<CHANNELMAP>
    {
      // remember that BasicGeometryEnvironmentConfiguration is not polymorphic
      using base_t
        = ::testing::BasicGeometryEnvironmentConfiguration<CHANNELMAP>;
      
      /// Default constructor; this is what is used in Boost unit test
      DUNEFDGeometryEnvironmentConfiguration()
        {
          // overwrite the configuration that happened in the base class:
          base_t::SetApplicationName("DUNEFDGeometryTest");
          base_t::SetDefaultGeometryConfiguration(R"(
              Name:     "dune10kt"
              GDML:     "dune10kt_v1_workspace.gdml"
              ROOT:     "dune10kt_v1_workspace.gdml"
              SurfaceY:  0.0e2  # in cm, vertical distance to the surface
             # SurfaceY: 147828 # Underground option. 4850 feet to cm. from DocDb-3833
              SortingParameters: {ChannelsPerOpDet:	12}
            )");
        } // DUNEFDGeometryEnvironmentConfiguration()
      
      /// Constructor; accepts the name as parameter
      DUNEFDGeometryEnvironmentConfiguration(std::string name):
        DUNEFDGeometryEnvironmentConfiguration()
        { base_t::SetApplicationName(name); }
      
    }; // class DUNEFDGeometryEnvironmentConfiguration<>
    
    
  } // namespace testing
} // namespace dune

#endif // TEST_GEOMETRY_UNIT_TEST_DUNE_H
