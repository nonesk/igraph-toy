# - Try to find IGRAPH library
# Once done this will define
# 
find_package(PkgConfig)
pkg_check_modules(PC_IGRAPH QUIET igraph)
set(IGRAPH_DEFINITIONS ${PC_IGRAPH_CFLAGS_OTHER})

find_path(IGRAPH_INCLUDE_DIR igraph.h
    HINTS ${PC_IGRAPH_INCLUDEDIR} ${PC_IGRAPH_INCLUDE_DIRS}
    PATH_SUFFIXES igraph)

find_library(IGRAPH_LIBRARY NAMES igraph libigraph libigraph0
    HINTS ${PC_IGRAPH_LIBDIR} ${PC_IGRAPH_LIBRARY_DIRS})

include(FindPackageHandleStandardArgs)
# handle the QUIETLY and REQUIRED arguments and set IGRAPH_FOUND to TRUE
# if all listed variables are TRUE

find_package_handle_standard_args(IGRAPH  DEFAULT_MSG
                                  IGRAPH_LIBRARY IGRAPH_INCLUDE_DIR)

mark_as_advanced(IGRAPH_INCLUDE_DIR IGRAPH_LIBRARY)

set(IGRAPH_LIBRARIES ${IGRAPH_LIBRARY} )
set(IGRAPH_INCLUDE_DIRS ${IGRAPH_INCLUDE_DIR} )

