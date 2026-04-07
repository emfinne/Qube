cmake_minimum_required(VERSION 3.8)
project(qube_controller)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(std_msgs REQUIRED)
find_package(sensor_msgs REQUIRED)

add_library(pid_controller SHARED
        src/pid_controller.cpp
)

target_include_directories(pid_controller PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include/${PROJECT_NAME}>
)



ament_target_dependencies(pid_controller
        rclcpp
        std_msgs
        sensor_msgs
)

add_executable(qube_controller_node
        src/qube_controller_node.cpp
)

target_include_directories(qube_controller_node PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)


target_link_libraries(qube_controller_node
        pid_controller
)

ament_target_dependencies(qube_controller_node
        rclcpp
        std_msgs
        sensor_msgs
)

install(
        TARGETS pid_controller qube_controller_node
        EXPORT export_${PROJECT_NAME}
        ARCHIVE DESTINATION lib
        LIBRARY DESTINATION lib
        RUNTIME DESTINATION lib/${PROJECT_NAME}
)

install(
        DIRECTORY include/
        DESTINATION include/${PROJECT_NAME}
)


ament_export_targets(export_${PROJECT_NAME} HAS_LIBRARY_TARGET)
ament_package()