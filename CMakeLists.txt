##---------------------------------------------------------------------------
## Author:      Rasbats aka. Mike Rossiter
## Copyright:
## License:     wxWidgets License
##---------------------------------------------------------------------------

# define minimum cmake version
CMAKE_MINIMUM_REQUIRED(VERSION 2.6.2)

PROJECT(SailawayNMEA_pi)

SET(PACKAGE_NAME SailawayNMEA_pi)
SET(VERBOSE_NAME SailawayNMEA)
SET(TITLE_NAME SailawayNMEA)
SET(CPACK_PACKAGE_CONTACT "Mike Rossiter")

SET(VERSION_MAJOR "0")
SET(VERSION_MINOR "1")

SET(NAME_SUFFIX "ov50")
SET(CMAKE_CXX_STANDARD 11)

#SET(CMAKE_BUILD_TYPE Debug)
SET( wxWidgets_USE_DEBUG OFF)
SET( wxWidgets_USE_UNICODE ON)
SET( wxWidgets_USE_UNIVERSAL OFF)
SET( wxWidgets_USE_STATIC OFF)

OPTION(SailawayNMEA_USE_SVG "Use SVG graphics" ON)

INCLUDE("cmake/PluginConfigure.cmake")


ADD_DEFINITIONS(-DMAKING_PLUGIN)

IF(SailawayNMEA_USE_SVG)
  ADD_DEFINITIONS(-DSailawayNMEA_USE_SVG)
ENDIF(SailawayNMEA_USE_SVG)

INCLUDE("cmake/PluginConfigure.cmake")
INCLUDE("cmake/PluginJSON.cmake")

SET(SRC_SailawayNMEA
        src/SailawayNMEA_pi.h
        src/SailawayNMEA_pi.cpp
        src/icons.h
        src/icons.cpp
	    src/SailawayNMEAgui.h
	    src/SailawayNMEAgui.cpp
	    src/SailawayNMEAgui_impl.cpp
	    src/SailawayNMEAgui_impl.h
	    src/NavFunc.h
	    src/NavFunc.cpp
		src/ocpn_plugin.h
		src/tinyxml.cpp
        src/tinyxmlerror.cpp
        src/tinyxmlparser.cpp
        src/tinyxml.h
		src/InstrumentsData.cpp
		src/InstrumentsData.h
		src/NMEASentenceGenerator.cpp
		src/NMEASentenceGenerator.h
)


ADD_LIBRARY(${PACKAGE_NAME} SHARED ${SRC_SailawayNMEA} ${SRC_JSON})

ADD_DEFINITIONS(-DTIXML_USE_STL)

INCLUDE("cmake/PluginInstall.cmake")
INCLUDE("cmake/PluginLocalization.cmake")
INCLUDE("cmake/PluginPackage.cmake")
