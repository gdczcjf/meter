cmake_minimum_required(VERSION 3.5)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE "Debug")
endif()
message("CMAKE_BUILD_TYPE: ${CMAKE_BUILD_TYPE}")

if(NOT DEFINED WELCOME_EN)
  set(WELCOME_EN 1)
endif()
add_compile_definitions(WELCOME_EN=${WELCOME_EN})
message("WELCOME_EN: ${WELCOME_EN}")


if(CMAKE_BUILD_TYPE STREQUAL "Debug")
  add_compile_definitions(DEBUG=1)
elseif()
  add_compile_definitions(ADC_EN=1)
  add_compile_definitions(IO_EN=1)
endif()

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

project(meter LANGUAGES CXX)
find_package(Qt5 COMPONENTS Widgets SerialPort REQUIRED)

include_directories(.)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -no-pie")
if(CMAKE_HOST_WIN32)
  add_compile_definitions(_TTY_WIN_)
	if(MSVC)
		set_target_properties(${PROJECT_NAME} PROPERTIES
			WIN32_EXECUTABLE YES
			LINK_FLAGS "/ENTRY:mainCRTStartup"
		)
	elseif(CMAKE_COMPILER_IS_GNUCXX)
			SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -mwindows")
	endif(MSVC)
endif()

set(HEADERS_FILES 
  adjustwin.h
  button.h
  calculator.h
  calucwin.h
  choptwin.h
  datacollection.h
  datadealwin.h
  dataoperate.h
  delreclect.h
  figure.h
  graphicsitem.h
  hardware.h
  helpwin.h
  home.h
  i_optionwin.h
  importdatawin.h
  keyboard.h
  meter.h
  meteroption.h
  meterscale.h
  metertype.h
  needle.h
  progress.h
  settingwin.h
  tablewidgetitem.h
  u_optionwin.h
  ui_setting.h
  welcome.h
)

set(FORMS_FILES 
  adjustwin.ui
  calucwin.ui
  choptwin.ui
  datacollection.ui
  datadealwin.ui
  dataoperate.ui
  delreclect.ui
  helpwin.ui
  home.ui
  i_optionwin.ui
  importdatawin.ui
  keyboard.ui
  meteroption.ui
  progress.ui
  settingwin.ui
  u_optionwin.ui
)

set(SOURCES_FILES 
  adjustwin.cpp
  button.cpp
  calculator.cpp
  calucwin.cpp
  choptwin.cpp
  datacollection.cpp
  datadealwin.cpp
  dataoperate.cpp
  delreclect.cpp
  figure.cpp
  graphicsitem.cpp
  hardware.cpp
  helpwin.cpp
  home.cpp
  i_optionwin.cpp
  importdatawin.cpp
  keyboard.cpp
  main.cpp
  meter.cpp
  meteroption.cpp
  meterscale.cpp
  needle.cpp
  progress.cpp
  settingwin.cpp
  tablewidgetitem.cpp
  u_optionwin.cpp
  welcome.cpp
)

set (RESOURCES_FILES
  res.qrc
)

add_executable(meter
  ${HEADERS_FILES}
  ${FORMS_FILES}
  ${SOURCES_FILES}
  ${RESOURCES_FILES}
)

target_link_libraries(meter PRIVATE Qt5::Widgets)