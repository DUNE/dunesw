include_guard()

cmake_minimum_required(VERSION 3.20...3.21 FATAL_ERROR)

include(toolPlugin)

# Define functions to deal with known DUNE tool types (BASEs) via
# tool_plugin(), and either the art_plugin_types::${BASE} target (if
# defined) or the generic art_plugin_types::tool target as appropriate.
foreach (_dune_tool_stem IN ITEMS AdcChannelTool TpcDataTool)
  cmake_language(EVAL CODE "function(${_dune_tool_stem} NAME)
  if (TARGET art_plugin_types::${_dune_tool_stem})
    set(_dune_${_dune_tool_stem}_BASE ${_dune_tool_stem})
  else()
    set(_dune_${_dune_tool_stem}_BASE)
  endif()
  tool_plugin(\${NAME} \"\${_dune_${_dune_tool_stem}_BASE}\" \${ARGN}
     LIBRARIES
     PUBLIC dune::DuneInterface_Data
     PRIVATE dune::ArtSupport
)
endfunction()\
")
endforeach()
