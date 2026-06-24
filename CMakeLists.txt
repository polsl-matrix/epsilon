cmake_minimum_required(VERSION 3.23)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

project(epsilon VERSION 0.1.0)

set(CORE_SOURCES
  src/core/event/detachment.cpp
)

set(SERVICES_SOURCES
  src/services/serialization/iserializable.cpp
  src/services/serialization/serializer.cpp
  src/services/serialization/deserializer.cpp
  src/services/serialization/deserialization_exception.cpp
  src/services/serialization/json/json_serialization_strategy.cpp
  src/services/serialization/json/json_deserialization_strategy.cpp

  src/services/matrix/requests/request_manager.cpp
  src/services/matrix/requests/authenticated_request_manager.cpp
  src/services/matrix/requests/qt_raw_request_manager.cpp

  src/services/matrix/requests/implementation/common/error.cpp
  src/services/matrix/requests/implementation/common/empty.cpp

  src/services/matrix/requests/implementation/login/login_request_body.cpp
  src/services/matrix/requests/implementation/login/login_request_response.cpp
  src/services/matrix/requests/implementation/login/login_request.cpp
  src/services/matrix/requests/implementation/logout/logout_request.cpp

  src/services/matrix/requests/implementation/registration/registration_request.cpp
  src/services/matrix/requests/implementation/registration/registration_request_body.cpp
  src/services/matrix/requests/implementation/registration/registration_request_response.cpp

  src/services/matrix/requests/implementation/joined_rooms/joined_rooms_request.cpp
  src/services/matrix/requests/implementation/joined_rooms/joined_rooms_request_response.cpp

  src/services/router/page_router.cpp
)

set(MODEL_SOURCES
  src/model/message.cpp
  src/model/room.cpp
  src/model/session.cpp
  src/model/user.cpp
)

set(LIB_SOURCES
  ${CORE_SOURCES}
  ${SERVICES_SOURCES}
  ${MODEL_SOURCES}
)

set(APP_SOURCES
  src/main.cpp

  src/features/login/model/login_model.cpp
  src/features/login/presenter/login_presenter.cpp
  src/features/login/view/login_view.cpp

  src/features/main_page/model/home_model.cpp
  src/features/main_page/presenter/home_presenter.cpp
  src/features/main_page/view/home_view.cpp

  src/features/chat_room/presenter/chat_room_presenter.cpp
  src/features/chat_room/view/chat_room_view.cpp

  src/services/navigation/navigation_service.cpp

  src/features/registration/model/registration_model.cpp
  src/features/registration/presenter/registration_presenter.cpp
  src/features/registration/view/registration_view.cpp
)

set(SOURCES
  ${LIB_SOURCES}
  ${APP_SOURCES}
)

set(CORE_TEST_SOURCES
  src/core/event/event_test.cpp
  src/core/future/future_test.cpp
)

set(SERVICES_TEST_SOURCES
  src/services/serialization/serialization_test.cpp
  src/services/serialization/deserialization_test.cpp

  src/services/matrix/requests/requests_test.cpp
)

set(APP_TEST_SOURCES
  src/test.cpp
)

set(TEST_SOURCES
  ${CORE_TEST_SOURCES}
  ${SERVICES_TEST_SOURCES}
  ${APP_TEST_SOURCES}
)

### Compiler configuration ###

# Disallow warnings
if (MSVC)
  add_compile_options(/W4 /WX)
else()
  add_compile_options(-Wall -Wextra -pedantic -Werror)
endif()

# TODO: Compiler optimizations

### Libraries ###

### Qt configuration ###

find_package(Qt6 COMPONENTS Core Gui Quick Qml Svg REQUIRED)

qt_standard_project_setup()

# Defaults the RESOURCE_PREFIX for qt_add_qml_module to /qt/qml
# where the Qt resources actually live
qt_policy(SET QTP0001 NEW)
# Makes the Qt components available between subdirectories
qt_policy(SET QTP0004 NEW)

if(APPLE)
  qt_add_executable(epsilon MACOSX_BUNDLE ${SOURCES})
else()
  qt_add_executable(epsilon ${SOURCES})
endif()

qt_add_qml_module(epsilon
  URI Main
  QML_FILES
    src/Main.qml
    src/features/login/view/Login.qml
    src/features/main_page/view/Home.qml
    src/features/main_page/view/EmptySpace.qml
    src/features/main_page/view/SideMenu.qml
    src/features/chat_room/view/ChatRoom.qml
    src/components/CustomScrollBar.qml
    src/components/CircleAvatar.qml
    src/features/main_page/view/components/MenuDivider.qml
    src/features/main_page/view/components/UserProfileBar.qml
    src/features/main_page/view/components/SpaceSearchBar.qml
    src/features/main_page/view/components/RoomListView.qml
    src/features/main_page/view/components/CreateServerButton.qml
    src/features/chat_room/view/components/ChatDetailsPopup.qml
    src/components/CustomTextField.qml
    src/features/registration/view/Registration.qml
  RESOURCES
    resources/settings.svg
    resources/search.svg
    resources/users.svg
    resources/plus.svg
    resources/exit.svg
    resources/check.svg
    resources/send.svg
    resources/arrow.svg
)

target_link_libraries(epsilon
  PRIVATE
    Qt6::Core
    Qt6::Gui
    Qt6::Quick
    Qt6::Qml
    Qt6::Network
    Qt6::Svg
)

# Disallow warnings
if (MSVC)
  add_compile_options(/W4 /WX)
else()
  add_compile_options(-Wall -Wextra -pedantic -Werror)
endif()

## Add clang-tidy to the compilation pipeline
#set_target_properties(epsilon PROPERTIES
#  CXX_CLANG_TIDY "clang-tidy"
#)

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

# Force clang to use LLVM's stdlib
if(CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
    target_compile_options(MyQtApp PRIVATE -stdlib=libc++)
    target_link_options(MyQtApp PRIVATE -stdlib=libc++)
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
    ${LIB_SOURCES}
    ${TEST_SOURCES}
  )

  target_link_libraries(
    epsilon_test
    PRIVATE
      GTest::gtest_main
      GTest::gmock
  )

  target_link_libraries(epsilon_test 
    PRIVATE 
      Qt6::Core 
      Qt6::Gui 
      Qt6::Quick
      Qt6::Qml
      Qt6::Network
  )

#  set_target_properties(epsilon_test PROPERTIES
#    CXX_CLANG_TIDY "clang-tidy"
#  )

  include(GoogleTest)
  gtest_discover_tests(epsilon_test)
endif()

### Linter configuration ###

# Export compile commands for clang-tidy
#set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

## Prevent clang-tidy from processing Qt-generated files
#set_target_properties(epsilon PROPERTIES
#    AUTOMOC_COMPILER_PREFE_REWRITE OFF
#)
#
## Explicitly clear the linting property for autogenerated sources
#get_target_property(AUTOGEN_TARGET epsilon AUTOGEN_TARGET_NAME)
#if(AUTOGEN_TARGET)
#    set_target_properties(${AUTOGEN_TARGET} PROPERTIES CXX_CLANG_TIDY "")
#endif()
#
## Don't lint autogenerated files
#set(CMAKE_AUTOGEN_COMMAND_LINE_LENGTH_MAX 0)
#set(CMAKE_SKIP_AUTOGEN_REQUIRED ON)
#set(CMAKE_AUTOGEN_SKIP_LINTING ON)
