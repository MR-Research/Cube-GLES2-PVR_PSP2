cmake_minimum_required(VERSION 2.8)

if(NOT DEFINED CMAKE_TOOLCHAIN_FILE)
  if(DEFINED ENV{VITASDK})
    set(CMAKE_TOOLCHAIN_FILE "$ENV{VITASDK}/share/vita.toolchain.cmake" CACHE PATH "toolchain file")
  else()
    message(FATAL_ERROR "Please define VITASDK to point to your SDK path!")
  endif()
endif()

project(Cube-GLES2-PVR_PSP2)
include("${VITASDK}/share/vita.cmake" REQUIRED)

set(VITA_APP_NAME "Cube GLES2 Demo")
set(VITA_TITLEID  "PVRD00001")
set(VITA_VERSION  "01.00")

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -std=c++11")
set(VITA_MKSFOEX_FLAGS "${VITA_MKSFOEX_FLAGS} -d PARENTAL_LEVEL=1")
set(VITA_MKSFOEX_FLAGS "${VITA_MKSFOEX_FLAGS} -d ATTRIBUTE2=12")

# Add any additional include paths here
include_directories(
)

# Add any additional library paths here
# ${CMAKE_CURRENT_BINARY_DIR} lets you use any library currently being built
link_directories(
  ${CMAKE_CURRENT_BINARY_DIR}
)

## Build and link
# Add all the files needed to compile here
add_executable(${PROJECT_NAME}
  src/main.cpp

)

target_link_libraries(${PROJECT_NAME}
    
  #SCE
  SceCtrl_stub
  SceDisplay_stub
    
  #PVR_PSP2
  libIMGEGL_stub_weak
  libgpu_es4_ext_stub_weak
  libGLESv2_stub_weak
  m
)

## Create Vita files
vita_create_self(${PROJECT_NAME}.self ${PROJECT_NAME} UNSAFE)
# The FILE directive lets you add additional files to the VPK, the syntax is
# FILE src_path dst_path_in_vpk. In this case, we add the LiveArea paths.
vita_create_vpk(${PROJECT_NAME}.vpk ${VITA_TITLEID} ${PROJECT_NAME}.self
  VERSION ${VITA_VERSION}
  NAME ${VITA_APP_NAME}

  #SCE
  FILE sce_sys/icon0.png sce_sys/icon0.png
  FILE sce_sys/livearea/contents/bg.png sce_sys/livearea/contents/bg.png
  FILE sce_sys/livearea/contents/startup.png sce_sys/livearea/contents/startup.png
  FILE sce_sys/livearea/contents/template.xml sce_sys/livearea/contents/template.xml

  #suprx
  FILE module/libGLESv2.suprx module/libGLESv2.suprx
  FILE module/libgpu_es4_ext.suprx module/libgpu_es4_ext.suprx
  FILE module/libIMGEGL.suprx module/libIMGEGL.suprx
  FILE module/libpvrPSP2_WSEGL.suprx module/libpvrPSP2_WSEGL.suprx
)
