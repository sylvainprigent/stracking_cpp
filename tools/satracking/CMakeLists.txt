############################################################
#
# $Id$
#
# Copyright (c) satrcking 2021
#
# AUTHOR:
# Sylvain Prigent
# 

# Project name
project(SaTrackingTools)

## #################################################################
## Define files
## #################################################################
include_directories(${stracking_SRC_INCLUDE_DIR})

SET(SRC_FILES 
	)

## #################################################################
## Exe generation
## #################################################################
SET(NAME AssociationTracker)
SET(FILE ${SRC_FILES} main.cpp SaFactories.h SaFactories.cpp)
add_executable(${NAME} ${FILE})
target_link_libraries(${NAME} ${SL_LIBRARIES} satracking simage simageio sshape sdata sdataio scli)
