############################################################
#
# $Id$
#
# Copyright (c) stracking 2020
#
# AUTHOR:
# Sylvain Prigent
# 

# Project name
project(satracking)

## #################################################################
## Define files
## #################################################################

SET(SRC_FILES
  SaCost.cpp
  SaCostEuclidean.cpp
  SaCostStraight.cpp
  SaDetection.cpp
  SaDetectionReader.cpp
  SaFramesReader.cpp
  SaGraph.cpp
  SaTrack.cpp
  SaLinker.cpp
  SaLinkerGraph.cpp
  SaLinkerNaive.cpp
)

SET(HEADERS_FILES
  SaCost.h
  SaCostEuclidean.h
  SaCostStraight.h
  SaDetection.h
  SaDetectionReader.h
  SaFramesReader.h
  SaGraph.h
  SaTrack.h
  SaLinker.h
  SaLinkerGraph.h
  SaLinkerNaive.h
)
  
## #################################################################
## Library target
## #################################################################

add_library(${PROJECT_NAME} ${SRC_FILES} ${HEADERS_FILES})
target_link_libraries(${PROJECT_NAME} score sshape simage simageio ${SL_LIBRARIES})

## #################################################################
## Export header file
## #################################################################

set(CMAKE_CXX_VISIBILITY_PRESET hidden)
set(CMAKE_VISIBILITY_INLINES_HIDDEN 1)

generate_export_header(${PROJECT_NAME}
  EXPORT_FILE_NAME "${PROJECT_NAME}Export.h")

add_custom_command(TARGET ${PROJECT_NAME} PRE_BUILD
  COMMAND ${CMAKE_COMMAND} ARGS -E copy_if_different "${${PROJECT_NAME}_BINARY_DIR}/${PROJECT_NAME}Export.h" "${CMAKE_BINARY_DIR}"
  COMMAND ${CMAKE_COMMAND} ARGS -E copy_if_different "${${PROJECT_NAME}_BINARY_DIR}/${PROJECT_NAME}Export.h" "${CMAKE_BINARY_DIR}/${PROJECT_NAME}Export")
