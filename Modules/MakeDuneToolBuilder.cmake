include_guard()

cmake_minimum_required(VERSION 3.20...3.21 FATAL_ERROR)

include(BasicPlugin)

set(dest_subdir Modules)

# Used downstream for simple tool builders.
function(make_dune_tool_builder NAME)
  list(POP_FRONT ARGN kw)
  if (kw STREQUAL "BASE")
    list(POP_FRONT ARGN BASE)
    unset(kw)
  else()
    set(BASE art::tool)
  endif()
  cet_make_plugin_builder(${NAME} ${BASE} ${dest_subdir} ${kw} ${ARGN}
    LIBRARIES
    CONDITIONAL "$<$<TARGET_EXISTS:${NAME}>:${NAME}>"
    REG dune::ArtSupport)
endfunction()
