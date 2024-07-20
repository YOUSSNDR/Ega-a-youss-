# ROS 2

## Introduction 
For the control of the robot we will be using ROS 2 wich is used a lot in the robotic field. for that we will first install it and see how it work.

### Learning ROS 2

We will be using diffrent online tutorials.

#### ROS 2 (iron irwini for Ubuntu 22.04) install 
To install ROS 2 we use the following link  which give us documentation an tutorials for ROS 2. [ROS 2 install](https://docs.ros.org/en/iron/Tutorials.html).


### Using ROS 2

to [acces ros 2](https://docs.ros.org/en/iron/Tutorials/Beginner-CLI-Tools/Configuring-ROS2-Environment.html) commands we need to source the setup file
 using the next line ```source /opt/ros/iron/setup.bash``` (the path might change depending your installation)

 if you don t want to  source the setup file for every shell you can add the next command to the shell startup:
 ```echo "source /opt/ros/iron/setup.bash" >> ~/.bashrc```  (this can be undone)

 Ros domain ID =9 (don't add space)

The ROS 2 development environment needs to be correctly configured before use. This can be done in two ways: either sourcing the setup files in every new shell you open, or adding the source command to your startup script.

If you ever face any problems locating or using packages with ROS 2, the first thing you should do is check your environment variables and ensure they are set to the version and distro you intended. (see the link above)