# Qube
In this mini project, we will control a Quanser Qube using ros2. The Qube is visualisez using Rviz2 and utlizises a cloned packaged qube_driver to interface with the qube. The project consist of 5 packages where each package 

## qube_bringup
The qube_bringup package consist of a launce file and a urdf descripcion of the qube aswell as the qube_driver instance of the hardware interface.

## qube_controller
This package is resposible for controlling the actuating signal to the qube. The package includes two header-only libraries to create an instance of a delta time object and a lowpass filter. Both libraries is utilized in the pid controller class 

### Delta time header library 
This library is used to calculate the delta time between each callback to the pid controller loops. Since the pid controller utlizises a discrete implementation of a pid controller, its nececary to 

### Lowpass filter header library


## qube_description
this package contains the visual and geometric description of the Quanser Qube. The package includes reusable Xacro and URDF files that define the base, rotating disk, and pointer used to represent the Qube in RViz. It also provides a launch file for quickly visualizing the model and testing its joints and movement.



## reference_gui



