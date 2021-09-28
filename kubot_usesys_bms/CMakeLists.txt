cmake_minimum_required(VERSION 3.0.2)
project(kubot_usesys_bms)

find_package(catkin REQUIRED COMPONENTS
  roscpp
  rospy
  std_msgs
  geometry_msgs
  message_generation
)

add_message_files(
   FILES
   RawJ1939.msg
 )

generate_messages(
   DEPENDENCIES
   std_msgs
   geometry_msgs
 )

catkin_package(
  CATKIN_DEPENDS 
  roscpp 
  rospy 
  std_msgs
  message_runtime
  geometry_msgs
)

include_directories(
  include ${catkin_INCLUDE_DIRS}
  include ${catkin_INCLUDE_DIRS}
  include include/kubot_usesys_bms/
)

add_executable(
  kubot_usesys_bms
  src/usesys_bringup.cpp
)

add_dependencies(
  kubot_usesys_bms
  ${${PROJECT_NAME}_EXPORTED_TARGETS} 
  ${catkin_EXPORTED_TARGETS}
)
target_link_libraries(
  kubot_usesys_bms
  ${catkin_LIBRARIES}
)