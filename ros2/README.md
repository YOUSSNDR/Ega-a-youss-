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


### Turtlesim 
turtlesim will be our trainingsubject more info on the install [here](https://docs.ros.org/en/iron/Tutorials/Beginner-CLI-Tools/Introducing-Turtlesim/Introducing-Turtlesim.html).

to run turtlesim (after installation): ```ros2 run turtlesim turtlesim_node``` 

control basic turtle : ```ros2 run turtlesim turtle_teleop_key```

to see nodes, topics services and action we can use the next commands:

```ros2 node list```

```ros2 topic list```

```ros2 service list```

```ros2 action list```

we can add services by using ```rqt``` (it allow us for exemple to add a turtle)

to control the new turtle: ```ros2 run turtlesim turtle_teleop_key --ros-args --remap turtle1/cmd_vel:=turtle2/cmd_vel``` (with turtle2 the second turtle name)


### Nodes

Each node in ROS should be responsible for a single, modular purpose, e.g. controlling the wheel motors or publishing the sensor data from a laser range-finder. Each node can send and receive data from other nodes via topics, services, actions, or parameters.

The command ```ros2 run``` launches an executable from a package.
full command:  ```ros2 run <package_name> <executable_name>```

ex: ```ros2 run turtlesim turtlesim_node```

To get the currently used nodes name use : ``` ros2 node list```

Remapping allows to reassign default node properties (node name, topic namesd, service names... and also to custom values)

to acces the informations about the nodes run : ```ros2 node info <node_name>``` 

So a node is a fundamental ROS 2 element that serves a single, modular purpose in a robotics system.

### Topics

ROS 2 breaks complex systems down into many modular nodes. Topics are a vital element of the ROS graph that act as a bus for nodes to exchange messages.
A node may publish data to any number of topics and simultaneously have subscriptions to any number of topics.
Topics are one of the main ways in which data is moved between nodes and therefore between different parts of the system.