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
    
  } // namespace testing
} // namespace dune

#endif // TEST_GEOMETRY_UNIT_TEST_DUNE_H
