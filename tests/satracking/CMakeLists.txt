### CMakeLists.txt --- 
##
######################################################################
## 
### Commentary: 
## 
######################################################################
## 
### Change log:
## 
######################################################################
project(satrackingTest)

enable_testing()

## #################################################################
## Input
## #################################################################

set(${PROJECT_NAME}_MAIN_SOURCES
  BellmanFord1Test.cpp
  BellmanFord2Test.cpp
  LinkerGraphTest.cpp
  LinkerNaiveTest.cpp
)

## ###################################################################
## Configure file
## ###################################################################

if(EXISTS ${PROJECT_SOURCE_DIR}/../data/tracks1/frames.txt)
  set(TRACKS1_FRAMES ${PROJECT_SOURCE_DIR}/../data/tracks1/frames.txt)
endif()

if(EXISTS ${PROJECT_SOURCE_DIR}/../data/tracks1/detections.txt)
  set(TRACKS1_DETECTIONS ${PROJECT_SOURCE_DIR}/../data/tracks1/detections.txt)
endif()

if(EXISTS ${PROJECT_SOURCE_DIR}/SaTrackingTestConfig.h.in)
  configure_file(SaTrackingTestConfig.h.in ${CMAKE_BINARY_DIR}/SaTrackingTestConfig.h)
endif()

## #################################################################
## Build rules
## #################################################################

SET(TESTS "")

foreach (test ${${PROJECT_NAME}_MAIN_SOURCES})
  get_filename_component(TName ${test} NAME_WE)

  add_executable(${TName} ${test})
  target_link_libraries(${TName} satracking ${SL_LIBRARIES})

  add_test(${TName} ${EXECUTABLE_OUTPUT_PATH}/${TName})

  set(TEST ${TESTS} ${EXECUTABLE_OUTPUT_PATH}/${TName})
endforeach()

add_custom_target(testsatracking COMMAND ${CMAKE_CTEST_COMMAND} DEPENDS ${TESTS})

## #################################################################
## Source file layout in development environments like Visual Studio
## #################################################################
SOURCE_GROUP("Header Files" REGULAR_EXPRESSION .*\\.h\$)
SOURCE_GROUP("Source Files" REGULAR_EXPRESSION .*\\.cpp\$)
