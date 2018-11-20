cmake_minimum_required(VERSION 2.8.3)
project(p3dx_ufsc)

find_package(catkin REQUIRED COMPONENTS
  geometry_msgs
  rosaria
  roscpp
  rospy
  sensor_msgs
  std_msgs
  std_srvs
)
find_package(Boost REQUIRED COMPONENTS thread)
find_package(Aria QUIET)
if(Aria_FOUND)
	if(EXISTS "${Aria_INCLUDE_DIRS}/Aria.h")
		add_definitions(-DADEPT_PKG)
	endif()
  include_directories(${Aria_INCLUDE_DIRS})
  link_directories(${Aria_LIBRARY_DIRS})
else()
	# The installation package provided by Adept doesn't follow Debian policies
	if(EXISTS "/usr/local/Aria/include/Aria.h")
	  add_definitions(-DADEPT_PKG)
	  include_directories( /usr/local/Aria/include)
	  link_directories(/usr/local/Aria/lib)
	endif()
endif()
include_directories(${catkin_INCLUDE_DIRS} ${Boost_INCLUDE_DIRS} )


catkin_package(
#  INCLUDE_DIRS include
#  LIBRARIES p3dx_ufsc
  CATKIN_DEPENDS geometry_msgs libaria rosaria roscpp rospy sensor_msgs std_msgs std_srvs
#  DEPENDS system_lib
)




add_executable(p3dx_ufsc_main src/main.cpp)
add_executable(p3dx_ufsc_socket src/socket.cpp)
add_executable(p3dx_ufsc_socket_info src/socket_info.cpp)


target_link_libraries(p3dx_ufsc_main ${catkin_LIBRARIES} ${Boost_LIBRARIES} Aria pthread dl rt)
target_link_libraries(p3dx_ufsc_socket ${catkin_LIBRARIES} ${Boost_LIBRARIES} Aria pthread dl rt)
target_link_libraries(p3dx_ufsc_socket_info ${catkin_LIBRARIES} ${Boost_LIBRARIES} Aria pthread dl rt)



add_compile_options(-std=c++11)






