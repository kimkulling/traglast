CMAKE_MINIMUM_REQUIRED( VERSION 2.8 )
PROJECT( traglast )
SET ( TRAGLAST_VERSION_MAJOR 0 )
SET ( TRAGLAST_VERSION_MINOR 1 )
SET ( TRAGLAST_VERSION_PATCH 0 )
SET ( TRAGLAST_VERSION ${TRAGLAST_VERSION_MAJOR}.${TRAGLAST_VERSION_MINOR}.${TRAGLAST_VERSION_PATCH} )
SET ( PROJECT_VERSION "${TRAGLAST_VERSION}" )


# Cache these to allow the user to override them manually.
SET( LIB_INSTALL_DIR "lib" CACHE PATH
    "Path the built library files are installed to." )
SET( INCLUDE_INSTALL_DIR "traglast" CACHE PATH
    "Path the header files are installed to." )
SET( BIN_INSTALL_DIR "bin" CACHE PATH
    "Path the tool executables are installed to." )

INCLUDE_DIRECTORIES(
    code/
)

link_directories(
    ${CMAKE_HOME_DIRECTORY}/lib
    ${CMAKE_HOME_DIRECTORY}/bin
)

SET( CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_HOME_DIRECTORY}/lib )
SET( CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_HOME_DIRECTORY}/lib )
SET( CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_HOME_DIRECTORY}/bin )

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

IF ( BUILD_SHARED_LIBS AND CMAKE_SIZEOF_VOID_P EQUAL 8 ) # -fPIC is only required for shared libs on 64 bit
  SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fPIC" )
  SET(CMAKE_C_FLAGS   "${CMAKE_C_FLAGS}   -fPIC" )
ENDIF()

if( WIN32 )
else()
  if(CMAKE_BUILD_TYPE STREQUAL "Debug")
      set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib-debug)
      set(LIB_INSTALL_DIR ${CMAKE_SOURCE_DIR}/lib-debug)
      set(EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/bin-dbg)
  else()
      set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib)
      set(LIB_INSTALL_DIR ${CMAKE_SOURCE_DIR}/lib)
      set(EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/bin)
  endif()
endif()

# we want to have all wanings
if( WIN32 AND NOT CYGWIN )
  set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /EHsc" )  # Force to always compile with W4
  if( CMAKE_CXX_FLAGS MATCHES "/W[0-4]" )
    string( REGEX REPLACE "/W[0-4]" "/W4" CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}" )
  else()
    set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4" )
  endif()
elseif( CMAKE_COMPILER_IS_GNUCC OR CMAKE_COMPILER_IS_GNUCXX )
  # Update if necessary
  execute_process(COMMAND ${CMAKE_C_COMPILER} -dumpversion
                OUTPUT_VARIABLE GCC_VERSION)
    if (GCC_VERSION VERSION_EQUAL 4.6 )
      set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wno-long-long -pedantic -std=c++0x")
    else()
      set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wno-long-long -pedantic -std=gnu++11")
    endif()
elseif ( "${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang" )
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fvisibility=hidden -Wall -Wno-long-long -pedantic -std=c++11" )
endif()

SET( BUILD_SHARED_LIBS OFF )
# Include all sub directories of the engine code component
ADD_SUBDIRECTORY( 3dparty/cppcore/build )
ADD_SUBDIRECTORY( code )

# Include the doc component.
#ADD_SUBDIRECTORY( Doc )
#FIND_PACKAGE( doxygen )
#IF ( DOXYGEN_FOUND )
#    CONFIGURE_FILE( Doc/Doxygen/OSRE_dox_config.in Doc/Doxygen/Doxyfile @ONLY )
#    ADD_CUSTOM_TARGET( doc ALL ${DOXYGEN_EXECUTABLE} Doc/Doxygen/Doxyfile
#        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
#        COMMENT "Generating API documentation with Doxygen" VERBATIM
#    )
#ENDIF ( DOXYGEN_FOUND )

set_target_properties(  cppcore PROPERTIES FOLDER ThirdParty )
set_target_properties(  cppcore_unittest PROPERTIES FOLDER ThirdParty )
set_target_properties(  traglast PROPERTIES FOLDER Lib )

