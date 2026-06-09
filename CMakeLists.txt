cmake_minimum_required(VERSION 3.23)

project(epsilon VERSION 0.1.0)

### Compiler configuration ###

# Disallow warnings
if (MSVC)
  add_compile_options(/W4 /WX)
else()
  add_compile_options(-Wall -Wextra -pedantic -Werror)
endif()

# TODO: Compiler optimizations

### Qt configuration ###

find_package(Qt6 COMPONENTS Core Gui Quick Qml REQUIRED)

qt_standard_project_setup()

# Defaults the RESOURCE_PREFIX for qt_add_qml_module to /qt/qml
# where the Qt resources actually live
qt_policy(SET QTP0001 NEW)
# Makes the Qt components available between subdirectories
qt_policy(SET QTP0004 NEW)

if(APPLE)
  qt_add_executable(epsilon MACOSX_BUNDLE src/main.cpp)
else()
  qt_add_executable(epsilon src/main.cpp)
endif()

qt_add_qml_module(epsilon
  URI Main
  QML_FILES
        src/Main.qml
        src/Login.qml
)

target_link_libraries(epsilon 
  PRIVATE 
    Qt6::Core 
    Qt6::Gui 
    Qt6::Quick
    Qt6::Qml
)

# Disallow warnings
if (MSVC)
  add_compile_options(/W4 /WX)
else()
  add_compile_options(-Wall -Wextra -pedantic -Werror)
endif()

# TODO: Compiler optimizations

if(WIN32)
  find_program(WINDEPLOYQT_EXECUTABLE windeployqt PATHS ENV PATH)
  if(WINDEPLOYQT_EXECUTABLE)
    add_custom_command(TARGET epsilon POST_BUILD
    COMMAND "${WINDEPLOYQT_EXECUTABLE}" 
      --no-compiler-runtime 
      --qmldir "${CMAKE_CURRENT_SOURCE_DIR}" 
      "$<TARGET_FILE:epsilon>"
    COMMENT "Deploying Qt libraries for Windows..."
  )
endif()

elseif(APPLE)
  get_target_property(_qt_qmake_executable Qt6::qmake IMPORTED_LOCATION)
  get_filename_component(_qt_bin_dir "${_qt_qmake_executable}" DIRECTORY)

  find_program(MACDEPLOYQT_EXECUTABLE macdeployqt HINTS "${_qt_bin_dir}")

  if(MACDEPLOYQT_EXECUTABLE AND CMAKE_BUILD_TYPE STREQUAL "Release")
    add_custom_command(TARGET epsilon POST_BUILD
            COMMAND "${MACDEPLOYQT_EXECUTABLE}"
            "$<TARGET_BUNDLE_DIR:epsilon>"
            -qmldir="${CMAKE_CURRENT_SOURCE_DIR}"
            -always-overwrite
    )
  endif()

elseif(UNIX AND NOT APPLE)
    # Use RPATH to point the executable to the system Qt installation.
    # No physical file copying is needed for local development.
    set_target_properties(epsilon PROPERTIES
        INSTALL_RPATH "${CMAKE_PREFIX_PATH}/lib"
        BUILD_WITH_INSTALL_RPATH TRUE
    )
endif()

### Google Test configuration ###

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
  if(WIN32)
    set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
  endif()

  find_package(GTest REQUIRED)

  enable_testing()

  add_executable(
    epsilon_test
    src/test.cpp
  )

  target_link_libraries(
    epsilon_test
    PRIVATE
      GTest::gtest_main
  )

  include(GoogleTest)
  gtest_discover_tests(epsilon_test)
endif()
