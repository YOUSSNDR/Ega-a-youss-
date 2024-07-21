# ROS 2

## Introduction 
For the control of the robot we will be using ROS 2 wich is used a lot in the robotic field. for that we will first install it and see how it work.

### Learning ROS 2

We will be using diffrent online tutorials.

#### ROS 2 (iron irwini for Ubuntu 22.04) install 
To install ROS 2 we use the following link  which give us documentatiohttps://youtu.be/ScDgJJi5Gucn an tutorials for ROS 2. [ROS 2 install](https://docs.ros.org/en/iron/Tutorials.html).


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

we can add services (and modify parameters) by using ```rqt``` (it allow us for exemple to add a turtle)

to control the new turtle: ```ros2 run turtlesim turtle_teleop_key --ros-args --remap turtle1/cmd_vel:=turtle2/cmd_vel``` (with turtle2 the second turtle name)


### Nodes

Each node in ROS should be responsible for a single, modular purpose, e.g. controlling the wheel motors or publishing the sensor data from a laser range-finder. Each node can send and receive data from other nodes via topics, services, actions, or parameters.

The command ```ros2 run``` launches an executable from a package.
full command:  ```ros2 run <package_name> <executable_name>```

ex: ```ros2 run turtlesim turtlesim_node```

To get the currently used nodes name use : ``` ros2 node list```

Remapping allows to reassign default node properties (node name, topic names, service names... and also to custom values)

to acces the informations about the nodes run : ```ros2 node info <node_name>``` 

So a node is a fundamental ROS 2 element that serves a single, modular purpose in a robotics system.

### Topics

ROS 2 breaks complex systems down into many modular nodes. Topics are a vital element of the ROS graph that act as a bus for nodes to exchange messages.
A node may publish data to any number of topics and simultaneously have subscriptions to any number of topics.
Topics are one of the main ways in which data is moved between nodes and therefore between different parts of the system.

To visualize the changing nodes and topics and the connections between them we can use the command :  ```rqt_graph```

```ros2 topic list -t``` will return the  list of topics, this time with the topic type appended in brackets.

To see the data being published on a topic, use: ```ros2 topic echo <topic_name>```

eg: /teleop_turtle publishes data to /turtlesim over /tutle1/cmd_vel topic we cans read the messages with : ```ros2 topic echo /turtle1/cmd_vel```

Topics don’t have to only be one-to-one communication; they can be one-to-many, many-to-one, or many-to-many. to see it witheout the graph we can use: ```ros2 topic info <topic_name>```

Nodes send data over topics using messages. Publishers and subscribers must send and receive the same type of message to communicate.  
To check the data structure expected from message we can run : ```ros2 interface show <msg_name>```

with the message strucure we can directly publish to a topic using: ```ros2 topic pub <topic_name> <msg_type> '<args>'``` 

with ```<args>``` the data we want to pass to the topic. 
It’s important to note that this argument needs to be input in YAML syntax.

you can view the rate at which data is published using:
```ros2 topic hz <topic_name>```

Nodes publish information over topics, which allows any number of other nodes to subscribe to and access that information.

### Services

[Services](https://docs.ros.org/en/iron/Tutorials/Beginner-CLI-Tools/Understanding-ROS2-Services/Understanding-ROS2-Services.html) are another method of communication for nodes in the ROS graph. Services are based on a call-and-response model versus the publisher-subscriber model of topics. While topics allow nodes to subscribe to data streams and get continual updates, services only provide data when they are specifically called by a client.

Services have types that describe how the request and response data of a service is structured. Service types are defined similarly to topic types, except service types have two parts: one message for the request and another for the response.
To find out the type of a service, use the command:
```ros2 service type <service_name>```
 
 to show the type of all active services we can use: ```ros2 service list -t```

 If you want to find all the services of a specific type, you can use the command: ```ros2 service find <type_name>``` 

 We can also call services from command line if we know the structure of the input arguments : ```ros2 interface show <type_name>``` 

 to call use : ```ros2 service call <service_name> <service_type> <arguments>```
 (argument is optional, some services don't have one)

 To see the data communication between a service client and a service server you can echo the service using: ```ros2 service echo <service_name | service_type> <arguments>```

 Nodes can communicate using services in ROS 2. Unlike a topic - a one way communication pattern where a node publishes information that can be consumed by one or more subscribers - a service is a request/response pattern where a client makes a request to a node providing the service and the service processes the request and generates a response.

You generally don’t want to use a service for continuous calls; topics or even actions would be better suited.

### Parameters

A [parameter](https://docs.ros.org/en/iron/Tutorials/Beginner-CLI-Tools/Understanding-ROS2-Parameters/Understanding-ROS2-Parameters.html) is a configuration value of a node. You can think of parameters as node settings. A node can store parameters as integers, floats, booleans, strings, and lists. In ROS 2, each node maintains its own parameters.

to see the parameters of our nodes: ```ros2 param list```

To display the type and current value of a parameter, use the command:
```ros2 param get <node_name> <parameter_name>``` 

To change a parameter’s value at runtime, use the command:
```ros2 param set <node_name> <parameter_name> <value>```

You can view all of a node’s current parameter values by using the command:
```ros2 param dump <node_name>```

The command prints to the standard output (stdout) by default but you can also redirect the parameter values into a file to save them for later. To save your current configuration of /turtlesim’s parameters into the file turtlesim.yaml, enter the command: ```ros2 param dump /turtlesim > turtlesim.yaml```

You can load parameters from a file to a currently running node using the command:
```ros2 param load <node_name> <parameter_file>```

To start the same node using your saved parameter values, use:
```ros2 run <package_name> <executable_name> --ros-args --params-file <file_name>```

### Actions