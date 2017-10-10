CMAKE_MINIMUM_REQUIRED( VERSION 3.0 )
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

add_definitions( -D_AFXDLL )

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
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wno-long-long -pedantic -std=c++0x")
elseif ( "${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang" )
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wno-long-long -pedantic -std=c++11")
endif()

SET ( tinyxml_src
	contrib/tinyxml/tinystr.cpp  
	contrib/tinyxml/tinystr.h  
	contrib/tinyxml/tinyxml.cpp  
	contrib/tinyxml/tinyxml.h  
	contrib/tinyxml/tinyxmlerror.cpp  
	contrib/tinyxml/tinyxmlparser.cpp  
)

SET ( traglast_src
	#code/Ansicht.cpp
	#code/Ansicht.h
	code/Band.cpp
	code/Band.h
	code/BandOp.cpp
	code/BandOp.h
	code/CalcOption.cpp
	code/CalcOption.h
	code/Calculate.cpp
	code/Calculate.h
	code/ChildView.cpp
	code/ChildView.h
	code/DebugLogStream.cpp
	code/DebugLogStream.h
	code/Delmat.cpp
	code/Delmat.h
	code/Eigenschaften.cpp
	code/Eigenschaften.h
	code/Einzeleinwirkung.cpp
	code/Einzeleinwirkung.h
	code/Element.cpp
	code/ElementStack.h
	code/ElementWork.cpp
	code/ElementWork.h
	code/element_berechnen.cpp
	code/element_berechnen.h
	code/EnviromentServer.cpp
	code/EnviromentServer.h
	code/fem2d.h
	code/GUITextUtils.cpp
	code/GUITextUtils.h
	code/ILogStream.h
	code/Inzidenz.cpp
	code/inzidenz.h
	code/IOperation.h
	code/ISolveStep.h
	code/IUpdate.cpp
	code/Koord.cpp
	code/Koord.h
	code/KoordWork.cpp
	code/KoordWork.h
	code/Lager.cpp
	code/Last.cpp
	code/Last.h
	code/LinAlg.cpp
	code/LinALg.h
	code/LocalizationObserver.cpp
	code/LocalizationObserver.h
	code/LocalizationObserverSubject.h
	code/LocalizationServer.cpp
	code/LocalizationServer.h
	code/Logger.cpp
	code/Logger.h
	code/MainFrm.cpp
	code/MainFrm.h
	code/Material.cpp
	code/MaterialWork.cpp
	code/MaterialWork.h
	code/MyMathDef.cpp
	code/mymathdef.h
	code/Node.h
	code/NodeStack.cpp
	code/NodeStack.h
	code/Observer.cpp
	code/Observer.h
	code/ObserverSubject.cpp
	code/ObserverSubject.h
	code/OSUtils.cpp
	code/OSUtils.h
	code/PlastCalcCtrl.cpp
	code/PlastCalcCtrl.h
	code/Plot.cpp
	code/ReadMe.txt
	code/resource.h
	code/StdAfx.cpp
	code/StdAfx.h
	code/Streckeneinwirkung.cpp
	code/Streckeneinwirkung.h
	code/Structure.cpp
	code/Structure.h
	code/SystemStiffnessBuilder.cpp
	code/SystemStiffnessBuilder.h
	code/Tragwerk.cpp
	code/TragwerkInfo.cpp
	code/TragwerkInfo.h
	code/TScale.h
	code/types.h
	code/vector.h
	code/Vektor.cpp
	code/Win_Traglast.cpp
	code/Win_Traglast.h
	code/Win_Traglast.rc
	code/Win_Traglast_eng.rc
	code/wtErrorHandler.h
	code/wtlErrorHandler.cpp
)

SOURCE_GROUP( code\\Traglast    FILES ${traglast_src} )
SOURCE_GROUP( code\\contrib\\tinyxml FILES ${tinyxml_src} )

ADD_EXECUTABLE( traglast
    ${traglast_src}
	${tinyxml_src}
)
