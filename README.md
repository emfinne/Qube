# Qube
In this mini project, we will control a Quanser Qube using ros2. The Qube is visualisezd using Rviz2 and utlizises a cloned packaged qube_driver to interface with the qube. The project consist of 4 packages with an additional package called qube_driver provided by the task description

## qube_bringup
The qube_bringup package consist of a launch file and a urdf descripcion of the qube aswell as the qube_driver instance of the hardware interface.

## qube_controller
This package is resposible for controlling the actuating signal to the qube.
The package includes two header-only libraries to create an instance of a delta time and a lowpass filter object. Both libraries is and must be utilized in the pid controller class in order to control the qube. 

### Delta time header library 
This library is used to calculate the delta time between each callback to the pid controller loops. Since the pid controller utlizises a discrete implementation of a pid controller, its nececary to calculate each step-size. 

### Lowpass filter header library
This library was added as a nececary messure to filter the process variable from the hardware interface. We noticed huge spikes from the Qube position encoder which would send our controller into an unstable state. 


## qube_description
this package contains the visual and geometric description of the Quanser Qube. The package includes reusable Xacro and URDF files that define the base, rotating disk, and pointer used to represent the Qube in RViz. It also provides a launch file for quickly visualizing the model and testing its joints and movement.



## reference_gui
The reference_gui package was vibe coded using Chatgpt to make a joint state publisher inspired slider gui. The gui makes it easy to change qube controller reference. 



