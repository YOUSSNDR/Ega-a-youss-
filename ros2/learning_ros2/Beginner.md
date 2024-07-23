# Beginner tutorial

## Building packages with ```colcon```

[Using colcon to build packages](https://docs.ros.org/en/iron/Tutorials/Beginner-Client-Libraries/Colcon-Tutorial.html)

A ROS workspace is a directory with a particular structure. Commonly there is a **src** subdirectory. Inside that subdirectory is where the source code of ROS packages will be located. Typically the directory starts otherwise empty.

colcon does out of source builds. By default it will create the following directories as peers of the **src** directory:

The **build** directory will be where intermediate files are stored. For each package a subfolder will be created in which e.g. CMake is being invoked.

The **install** directory is where each package will be installed to. By default each package will be installed into a separate subdirectory.

The **log** directory contains various logging information about each colcon invocation.

first create a workspace (directory with a src file) ```mkdir -p ~/<workspace_name>/src```

when using the ```colcon build --symlink-install``` command my computer had issue making the operations all at once so i had to **add** ```--executor sequential``` to the command so that all **packages are built one by one**.

the command : ```ros2 pkg create``` allows us to create a new package based on a template.

The command ```colcon_cd``` allows you to quickly change the current working directory of your shell to the directory of a package. As an example ```colcon_cd some_ros_package``` would quickly bring you to the directory ```~/ros2_ws/src/some_ros_package```.

- If you do not want to build a specific package place an empty file named ```COLCON_IGNORE``` in the directory and it will not be indexed.

- If you want to run a single particular test from a package: 
```colcon test --packages-select YOUR_PKG_NAME --ctest-args -R YOUR_TEST_IN_PKG```

## Creating a Workspace

A [workspace](https://docs.ros.org/en/iron/Tutorials/Beginner-Client-Libraries/Creating-A-Workspace/Creating-A-Workspace.html) is a directory containing ROS 2 packages. Before using ROS 2, it’s necessary to **source your ROS 2 installation workspace** in the terminal you plan to work in. This makes ROS 2’s packages available for you to use in that terminal.

### Resolve dependancies

Before building the workspace, you need to resolve the package dependencies. You may have all the dependencies already, but best practice is to **check for dependencies every time you clone**. You wouldn’t want a build to fail after a long wait only to realize that you have missing dependencies.

command from the root of the workspace : ```rosdep install -i --from-path src --rosdistro iron -y```

### Build workspace with colcon

basic build: ```colcon build```

Other useful arguments for colcon build:

```--packages-up-to``` builds the package you want, plus all its dependencies, but not the whole workspace (saves time)

```--symlink-install``` saves you from having to rebuild every time you tweak python scripts

```--event-handlers console_direct+``` shows console output while building (can otherwise be found in the **log** directory)

```--executor sequential``` processes the packages one by one instead of using parallelism

colcon create new directories build, install and log.
The ```install``` directory is where your workspace’s setup files are, which you can use to source your overlay.

### Source the overlay

Before sourcing the overlay, it is very important that you open a new terminal, separate from the one where you built the workspace. Sourcing an overlay in the same terminal where you built, or likewise building where an overlay is sourced, may create complex issues.

you have to source the main ROS2 file as the underlay

then at the root of your workspace source your overlay with : ```source install/local_setup.bash```

## Creating a package

A [package](https://docs.ros.org/en/iron/Tutorials/Beginner-Client-Libraries/Creating-Your-First-ROS2-Package.html) is an organizational unit for your ROS 2 code. If you want to be able to install your code or share it with others, then you’ll need it organized in a package. With packages, you can release your ROS 2 work and allow others to build and use it easily.

We will be using Cmake (python is also possible)

here is the minimum required:

- ```CMakeLists.txt``` file that describes how to build the code within the package
- ```include/<package_name>``` directory containing the public headers for the package
- ```package.xml``` file containing meta information about the package
- ```src``` directory containing the source code for the package

The simplest possible package may have a file structure that looks like:

```     
my_package/
    CMakeLists.txt
    include/my_package/
    package.xml
    src/ 
```
Best practice is to have a src folder within your workspace, and to create your packages in there. This keeps the top level of the workspace “clean”.

A trivial workspace might look like:

```
workspace_folder/
    src/
      cpp_package_1/
          CMakeLists.txt
          include/cpp_package_1/
          package.xml
          src/

      py_package_1/
          package.xml
          resource/py_package_1
          setup.cfg
          setup.py
          py_package_1/
      ...
      cpp_package_n/
          CMakeLists.txt
          include/cpp_package_n/
          package.xml
          src/
```
#### pkg création

we create the package in the source file of our workspace.

Command to create a new package:
```ros2 pkg create --build-type ament_cmake --license Apache-2.0 <package_name>```

Putting packages in a workspace is especially valuable because you can build many packages at once by running colcon build in the workspace root. Otherwise, you would have to build each package individually.

to build only a selected package:
```colcon build --packages-select my_package```

to run the executable:
```ros2 run <package_name> <node_name>```

## Writing a simple publisher and subscriber (C++)

[Create and run a publisher and subscriber node using C++.](https://docs.ros.org/en/iron/Tutorials/Beginner-Client-Libraries/Writing-A-Simple-Cpp-Publisher-And-Subscriber.html)

1. create package : ```ros2 pkg create --build-type ament_cmake --license Apache-2.0 <package_name>```

2. Write the publisher Node: in the file **<publisher_name>.cpp**
- include the C++ header
- include ROS2 include :```#include "rclcpp/rclcpp.hpp"```
- message type include : ```#include "std_msgs/msg/string.hpp"```
- create the node class (ex:```class MinimalPublisher : public rclcpp::Node```)
- create the public constructor, ex(name = minimal_publisher,count initialize to 0,string type message,topic name=topic,queue size= 10,timer initialized,):
```
public:
  MinimalPublisher()
  : Node("minimal_publisher"), count_(0)
  {
    publisher_ = this->create_publisher<std_msgs::msg::String>("topic", 10);
    timer_ = this->create_wall_timer(
    500ms, std::bind(&MinimalPublisher::timer_callback, this));
  }
  ```
- create the private constructor. contain the def of timer_callback function, this is where the message data is set and published. ex: 
```
private:
  void timer_callback()
  {
    auto message = std_msgs::msg::String();
    message.data = "Hello, world! " + std::to_string(count_++);
    RCLCPP_INFO(this->get_logger(), "Publishing: '%s'", message.data.c_str());
    publisher_->publish(message);
  }
  ```
  and also in the private the declaration of the timer, publisher, and counter fields.

- the main (where the node executes)
```
int main(int argc, char * argv[])
{
  rclcpp::init(argc, argv); //intialize ros2
  rclcpp::spin(std::make_shared<MinimalPublisher>()); //start the data process from the node
  rclcpp::shutdown();
  return 0;
}
```
3. Add dependencies:
in the **package.xml** file
first fill **description**, **maintener** and **license**. Then add the dependencies.
```
<depend>rclcpp</depend>
<depend>std_msgs</depend>
```
This declares the package needs rclcpp and std_msgs when its code is built and executed.

4. The CMakeLists.txt (publisher)
in the CMakeList file add the dependencies. 
ex: 
```
find_package(rclcpp REQUIRED)
find_package(std_msgs REQUIRED)
```
add the executable and name it ex (here name= talker)(to be run by ros2):
```
add_executable(talker src/publisher_member_function.cpp)
ament_target_dependencies(talker rclcpp std_msgs)
```

Then add the install targets (for ros2 to find the executable)

5. Write the Subscriber node
The subscriber node’s code is nearly identical to the publisher’s. 
- ex: here the node is named minimal_subscriber, and the constructor uses the node’s create_subscription class to execute the callback: 
```
public:
  MinimalSubscriber()
  : Node("minimal_subscriber")
  {
    subscription_ = this->create_subscription<std_msgs::msg::String>(
    "topic", 10, std::bind(&MinimalSubscriber::topic_callback, this, _1));
  }
  ```
- The only field declaration in this class is the subscription.
```
private:
  void topic_callback(const std_msgs::msg::String & msg) const
  {
    RCLCPP_INFO(this->get_logger(), "I heard: '%s'", msg.data.c_str());
  }
  rclcpp::Subscription<std_msgs::msg::String>::SharedPtr subscription_;
```
- The main function is exactly the same, except now it spins the MinimalSubscriber node. For the publisher node, spinning meant starting the timer, but for the subscriber it simply means preparing to receive messages whenever they come.

Since this node has the same dependencies as the publisher node, there’s nothing new to add to package.xml.

6.  The CMakeLists.txt (Subscriber)
reopen the CMake file and add the executable and target for the subscriber node below the publisher's entry.
here we add:
```
add_executable(listener src/subscriber_member_function.cpp)
ament_target_dependencies(listener rclcpp std_msgs)

install(TARGETS
  talker
  listener
  DESTINATION lib/${PROJECT_NAME})
  ```

  now the publisher an subscriber are ready.
  Build and Run:
  
  first let's check for missing dependencies with: ```rosdep install -i --from-path src --rosdistro iron -y``` (in the root of the workspace)

  build in the root : colcon build --packages-select cpp_pubsub (here we only build the package cpp_pubsub)

  Dont forget to source your workspace before running the nodes:
  ```. install/setup.bash``` (source)

```ros2 run <package_name> <node_name>```(run)