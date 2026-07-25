cmake_minimum_required(VERSION 3.28...3.30)

include("${CMAKE_CURRENT_SOURCE_DIR}/cmake/common/bootstrap.cmake" NO_POLICY_SCOPE)

project(${_name} VERSION ${_version})

set(CMAKE_BUILD_TYPE Release CACHE STRING "Build type" FORCE)
option(ENABLE_FRONTEND_API "Use obs-frontend-api for UI functionality" ON)
option(ENABLE_QT "Use Qt functionality" ON)

# Force the Windows SDK version before the project loads
set(CMAKE_SYSTEM_VERSION "10.0.22621.0" CACHE STRING "Force Windows SDK" FORCE)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTOMOC ON)

include(compilerconfig)
include(defaults)
include(helpers)

# ============================================================
# THIS IS THE KEY FIX — uncomment and define your target
# ============================================================
add_library(${CMAKE_PROJECT_NAME} MODULE
        src/plugin-main.c
        src/qt-bridge.cpp
        src/qt-bridge.h
        src/WISDialog.cpp
        src/WISDialog.h
        src/WISDisplay.cpp  # add if needed
        src/WISDisplay.h    # add if needed
)

find_package(libobs REQUIRED)
target_link_libraries(${CMAKE_PROJECT_NAME} PRIVATE OBS::libobs)

if(ENABLE_FRONTEND_API)
  find_package(obs-frontend-api REQUIRED)
  target_link_libraries(${CMAKE_PROJECT_NAME} PRIVATE OBS::obs-frontend-api)
endif()

if(ENABLE_QT)
  find_package(Qt6 COMPONENTS Widgets Core)
  target_link_libraries(${CMAKE_PROJECT_NAME} PRIVATE Qt6::Core Qt6::Widgets)
  target_compile_options(
          ${CMAKE_PROJECT_NAME}
          PRIVATE $<$<C_COMPILER_ID:Clang,AppleClang>:-Wno-quoted-include-in-framework-header -Wno-comma>
  )
  set_target_properties(
          ${CMAKE_PROJECT_NAME}
          PROPERTIES AUTOMOC ON AUTOUIC ON AUTORCC ON
  )
endif()

# No need to call target_sources again — files are already in add_library above
# target_sources(${CMAKE_PROJECT_NAME} PRIVATE src/plugin-main.c ...)

add_custom_command(TARGET ${CMAKE_PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
        $<TARGET_FILE:${CMAKE_PROJECT_NAME}>
        "$<IF:$<EQUAL:${CMAKE_SIZEOF_VOID_P},8>,C:/Program Files/obs-studio/obs-plugins/64bit,C:/Program Files/obs-studio/obs-plugins/32bit>/$<TARGET_FILE_NAME:${CMAKE_PROJECT_NAME}>"
        COMMENT "Copying compiled plugin DLL to OBS Studio directory..."
)

set_target_properties_plugin(${CMAKE_PROJECT_NAME} PROPERTIES OUTPUT_NAME ${_name})
