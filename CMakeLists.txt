cmake_minimum_required(VERSION 2.8.3)
project(qpoases)

find_package(catkin REQUIRED COMPONENTS
  roscpp
  rospy
  std_msgs
)

find_package(cmake_modules REQUIRED)


catkin_package(
  INCLUDE_DIRS include
  LIBRARIES ${PROJECT_NAME})


include_directories(
  ${catkin_INCLUDE_DIRS}
  ${Eigen_INCLUDE_DIRS}
)

include_directories(include ${catkin_INCLUDE_DIRS})

##############
## Building ##
##############

include_directories(include)

#
# suppress any printline output from qpOASES
#
add_definitions(-D__SUPPRESSANYOUTPUT__)

#
# building qpOASES LIBRARY
#
set(SRCS
  src/BLASReplacement.cpp
  src/Constraints.cpp
  src/Indexlist.cpp
  src/Matrices.cpp
  src/Options.cpp
  src/QProblemB.cpp
  src/SolutionAnalysis.cpp
  src/SubjectTo.cpp
  src/Bounds.cpp
  src/Flipper.cpp
  src/LAPACKReplacement.cpp
  src/MessageHandling.cpp
  src/OQPinterface.cpp 
  src/QProblem.cpp
  src/SQProblem.cpp
  src/Utils.cpp)
add_library(${PROJECT_NAME} ${SRCS})

#
# building example applications
#
set(EXAMPLES
  example1
  example1a
  example1b
  example2
  example3
  example3b
  example4
  example5
  exampleLP
  qrecipe
  yutest
  )
 
foreach(EXAMPLE ${EXAMPLES})
  add_executable(${EXAMPLE} examples/${EXAMPLE}.cpp)
  target_link_libraries(${EXAMPLE} ${PROJECT_NAME})
endforeach(EXAMPLE)

################
## Installing ##
################

install(TARGETS ${PROJECT_NAME} ${EXAMPLES}
  ARCHIVE DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
  LIBRARY DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
  RUNTIME DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION})

install(DIRECTORY include/
  DESTINATION ${CATKIN_PACKAGE_INCLUDE_DESTINATION}
  FILES_MATCHING PATTERN "*.hpp"
  PATTERN ".svn" EXCLUDE)
  
  
  target_link_libraries(example1a
   ${catkin_LIBRARIES}
)
