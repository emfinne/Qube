# Qube
In this mini project, we control a Quanser Qube using ROS 2. The Qube is visualized in RViz2 and utilizes a cloned package, qube_driver, to interface with the hardware. Each package is described in the following sections.
## qube_bringup
The qube_bringup package consist of a launch file and a urdf descripcion of the qube aswell as the qube_driver instance of the hardware interface.

## qube_controller
This package is responsible for controlling the actuation signal to the Qube.
The package includes two header-only libraries for creating instances of a delta time object and a low-pass filter object. Both libraries are, and must be, utilized in the PID controller class in order to control the Qube.
The PID controller is implemented as a separate class and is instantiated within the Qube controller node class to interface with ROS2-specific code.
### Delta time header library 
This library is used to calculate the delta time between each callback in the PID controller loop. Since the PID controller utilizes a discrete implementation, it is necessary to compute the step size for each iteration.
### Lowpass filter header library

This library was added as a necessary measure to filter the process variable from the hardware interface. We observed significant spikes in the Qube position encoder, which caused the controller to enter an unstable state.
## qube_description

This package contains the visual and geometric description of the Quanser Qube. It includes reusable Xacro and URDF files that define the base, rotating disk, and pointer used to represent the Qube in RViz.
Additionally, the package provides a launch file for quickly visualizing the model and testing its joints and movement.


## reference_gui
The reference_gui package was vibe coded using Chatgpt to make a joint state publisher inspired slider gui. The gui makes it easy to change qube controller reference. 



