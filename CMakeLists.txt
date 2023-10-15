cmake_minimum_required(VERSION 3.14)

include(cmake/prelude.cmake)

project(
    CheapAteDebugger
    VERSION 0.1.0
    DESCRIPTION "A Qt/QML application for running and debugging Chip8 applications."
    HOMEPAGE_URL "https://b1te.my/CheapAteDebugger/"
    LANGUAGES CXX
)


set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_INCLUDE_CURRENT_DIRS ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


include(cmake/project-is-top-level.cmake)
include(cmake/variables.cmake)

# Fetch Library
find_package(Qt5 COMPONENTS Core)
include(FetchContent)
FetchContent_Declare(
  kddockwidgets
  GIT_REPOSITORY https://github.com/KDAB/KDDockWidgets.git
  GIT_TAG        db43dbdc9d8f47022ed1e57e53948eb84ccee2b6 # 2.0
)
FetchContent_MakeAvailable(kddockwidgets)

# ---- Declare library ----

add_library(
    CheapAteDebugger_lib OBJECT
    source/lib.cpp
)

target_include_directories(
    CheapAteDebugger_lib ${warning_guard}
    PUBLIC
    "$<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/source>"
)

target_compile_features(CheapAteDebugger_lib PUBLIC cxx_std_17)

# ---- Declare executable ----

add_executable(CheapAteDebugger_exe 
    source/main.cpp 
    source/Chip8Display.hpp
    source/Chip8Display.cpp
    source/resources.qrc)
add_executable(CheapAteDebugger::exe ALIAS CheapAteDebugger_exe)

set_property(TARGET CheapAteDebugger_exe PROPERTY OUTPUT_NAME CheapAteDebugger)

target_compile_features(CheapAteDebugger_exe PRIVATE cxx_std_17)

target_link_libraries(CheapAteDebugger_exe PRIVATE CheapAteDebugger_lib KDAB::kddockwidgets)

# ---- Install rules ----

if(NOT CMAKE_SKIP_INSTALL_RULES)
  include(cmake/install-rules.cmake)
endif()

# ---- Developer mode ----

if(NOT CheapAteDebugger_DEVELOPER_MODE)
  return()
elseif(NOT PROJECT_IS_TOP_LEVEL)
  message(
      AUTHOR_WARNING
      "Developer mode is intended for developers of CheapAteDebugger"
  )
endif()

include(cmake/dev-mode.cmake)
