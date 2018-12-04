cmake_minimum_required(VERSION 2.8.3)
project(Miniproject-C2-19)

find_package(catkin REQUIRED roscpp turtlesim geometry_msgs)

catkin_package()

include_directories(
  ${catkin_INCLUDE_DIRS}
)

add_executable(script src/script.cpp)
target_link_libraries(script
  ${catkin_LIBRARIES}
)
