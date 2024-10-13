cmake_minimum_required(VERSION 3.29)
project(Broadcaster)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(PkgConfig REQUIRED)
find_package(OpenSSL REQUIRED)

pkg_search_module(gstreamer REQUIRED IMPORTED_TARGET gstreamer-1.0>=1.4)
pkg_search_module(gstreamer-sdp REQUIRED IMPORTED_TARGET gstreamer-sdp-1.0>=1.4)
pkg_search_module(gstreamer-app REQUIRED IMPORTED_TARGET gstreamer-app-1.0>=1.4)
pkg_search_module(gstreamer-video REQUIRED IMPORTED_TARGET gstreamer-video-1.0>=1.4)

include(FetchContent)
set(wxBUILD_SHARED OFF)
message(STATUS "Fetching wxWidgets...")
FetchContent_Declare(
        wxWidgets
        GIT_REPOSITORY https://github.com/wxWidgets/wxWidgets.git
        GIT_TAG v3.2.6
)
FetchContent_MakeAvailable(wxWidgets)

set(SRCS src/main.cpp
        src/main.h
        src/GuiWindows/HelloWorldWindow.cpp
        src/GuiWindows/HelloWorldWindow.h
        src/GuiWindows/MainWindow.cpp
        src/GuiWindows/MainWindow.h
        src/Models/Channel.cpp
        src/Models/Channel.h
        src/ORM/BaseModel.cpp
        src/ORM/BaseModel.h
        src/AppDispatcher.cpp
        src/AppDispatcher.h
        src/ORM/DbConnection.cpp
        src/ORM/DbConnection.h
        src/Models/LogMessage.cpp
        src/Models/LogMessage.h
        src/ORM/QueryBuilder.cpp
        src/ORM/QueryBuilder.h
        src/ORM/DbField.h
)

if(APPLE)
    # create bundle on apple compiles
    add_executable(main MACOSX_BUNDLE ${SRCS})

    # Set a custom plist file for the app bundle - needed for Mac OS Retina display
    set_target_properties(main PROPERTIES MACOSX_BUNDLE_INFO_PLIST ${CMAKE_CURRENT_SOURCE_DIR}/Info.plist)
else()
    # the WIN32 is needed for Windows in order for it to look for WinMain
    # instead of the main function. This is ignored on other systems,
    # so it works on all platforms
    add_executable(main WIN32 ${SRCS} main.exe.manifest)
endif()

set(MYSQL_CONNECTOR_CPP_DIR /Users/ruslanmoskvitin/APPENDES_SDK/mysql-connector-c++-9.0.0-macos14-arm64)
include_directories(${MYSQL_CONNECTOR_CPP_DIR}/include)
include_directories(${MYSQL_CONNECTOR_CPP_DIR}/include/jdbc)
link_directories(${MYSQL_CONNECTOR_CPP_DIR}/lib64)

add_library(libmysqlcppconn STATIC IMPORTED)
add_library(libssl3 SHARED IMPORTED)
set_property(TARGET libmysqlcppconn PROPERTY IMPORTED_LOCATION ${MYSQL_CONNECTOR_CPP_DIR}/lib64/libmysqlcppconn-static.a)
set_property(TARGET libssl3 PROPERTY IMPORTED_LOCATION ${MYSQL_CONNECTOR_CPP_DIR}/lib64/libssl.3.dylib)

target_link_libraries(main PRIVATE
        wxcore wxnet
        PkgConfig::gstreamer PkgConfig::gstreamer-app PkgConfig::gstreamer-video
        curl libmysqlcppconn OpenSSL::SSL resolv
)
target_compile_features(main PRIVATE cxx_range_for)