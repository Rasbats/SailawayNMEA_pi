# ~~~
# Summary:      Local, non-generic plugin setup
# Copyright (c) 2020-2021 Mike Rossiter
# License:      GPLv3+
# ~~~

# This program is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation; either version 3 of the License, or
# (at your option) any later version.


# -------- Options ----------

set(OCPN_TEST_REPO
    "mike-rossiter/sailawaynmea-alpha"
    CACHE STRING "Default repository for untagged builds"
)
set(OCPN_BETA_REPO
    "mike-rossiter/sailawaynmea-beta"
    CACHE STRING
    "Default repository for tagged builds matching 'beta'"
)
set(OCPN_RELEASE_REPO
    "mike-rossiter/sailawaynmea-prod"
    CACHE STRING
    "Default repository for tagged builds not matching 'beta'"
)

option(SailawayNMEA_USE_SVG "Use SVG graphics" ON)

#
#
# -------  Plugin setup --------
#
set(PKG_NAME SailawayNMEA_pi)
set(PKG_VERSION  0.4.0)
set(PKG_PRERELEASE "")  # Empty, or a tag like 'beta'

set(DISPLAY_NAME SailawayNMEA)    # Dialogs, installer artifacts, ...
set(PLUGIN_API_NAME SailawayNMEA) # As of GetCommonName() in plugin API
set(PKG_SUMMARY "Connect SailAway simgame")
set(PKG_DESCRIPTION [=[
Provides NMEA feed from the Sailaway simgame.
]=])

set(PKG_AUTHOR "Mike Rossiter")
set(PKG_IS_OPEN_SOURCE "yes")
set(PKG_HOMEPAGE https://github.com/Rasbats/SailawayNMEA_pi)
set(PKG_INFO_URL https://opencpn.org/OpenCPN/plugins/SailawayNMEA.html)

SET(SRC
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
		src/InstrumentsData.cpp
		src/InstrumentsData.h
		src/NMEASentenceGenerator.cpp
		src/NMEASentenceGenerator.h
)

set(PKG_API_LIB api-17)  #  A directory in libs/ e. g., api-17 or api-16


macro(late_init)
  # Perform initialization after the PACKAGE_NAME library, compilers
  # and ocpn::api is available.
  
  if (SailawayNMEA_USE_SVG)
    target_compile_definitions(${PACKAGE_NAME} PUBLIC SailawayNMEA_USE_SVG)
  endif ()

  add_definitions(-DMAKING_PLUGIN)  

endmacro ()

macro(add_plugin_libraries)
  # Add libraries required by this plugin
  add_subdirectory("libs/tinyxml")
  target_link_libraries(${PACKAGE_NAME} ocpn::tinyxml)

  add_subdirectory("libs/wxJSON")
  target_link_libraries(${PACKAGE_NAME} ocpn::wxjson)

  add_subdirectory("libs/plugingl")
  target_link_libraries(${PACKAGE_NAME} ocpn::plugingl)

  add_subdirectory("libs/jsoncpp")
  target_link_libraries(${PACKAGE_NAME} ocpn::jsoncpp)
endmacro ()
