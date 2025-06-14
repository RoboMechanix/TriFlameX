
```
├── build
├── cad
│   └── design_files
│       └── 3DPrintingTips.txt
├── CONTRIBUTING.md
├── docs
│   ├── md_output
│   │   ├── index.md
│   │   ├── modules.md
│   │   └── my_module.md
│   └── source
│       ├── modules.rst
│       ├── TriFlameX.my_module.rst
│       └── TriFlameX.rst
├── firmware
│   ├── esp32
│   │   ├── CommunicationFlow.scss
│   │   ├── include
│   │   │   ├── comm.h
│   │   │   ├── ledAsIndicator.h
│   │   │   ├── lidar.h
│   │   │   ├── main.h
│   │   │   ├── mqtt_utils.h
│   │   │   ├── serial_utils.h
│   │   │   ├── TOF_Sense.h
│   │   │   ├── util.h
│   │   │   └── wifi_utils.h
│   │   ├── lidar
│   │   │   ├── BLSER_demo
│   │   │   │   ├── BLSER_demo.ino
│   │   │   │   ├── BLSER_interface.h
│   │   │   │   └── BLSER_program.cpp
│   │   │   ├── Lidar
│   │   │   │   ├── Lidar.ino
│   │   │   │   ├── TOF_Sense.cpp
│   │   │   │   └── TOF_Sense.h
│   │   │   └── Lidar_stepper
│   │   │       ├── Lidar_stepper.ino
│   │   │       ├── TOF_Sense.cpp
│   │   │       └── TOF_Sense.h
│   │   ├── platformio.ini
│   │   ├── src
│   │   │   ├── comms.cpp
│   │   │   ├── ledAsIndicator.cpp
│   │   │   ├── lidar.cpp
│   │   │   ├── main.cpp
│   │   │   ├── mqtt_utils.cpp
│   │   │   ├── serial_utils.cpp
│   │   │   ├── TOF_Sense.cpp
│   │   │   ├── util.cpp
│   │   │   └── wifi_utils.cpp
│   │   └── test
│   │       └── test_main.cpp
│   ├── laptop_mainBrain
│   │   ├── build
│   │   │   ├── COLCON_IGNORE
│   │   │   └── triflamex_ros2_pkg
│   │   │       ├── build
│   │   │       │   └── lib
│   │   │       │       └── triflamex_ros2_pkg
│   │   │       │           ├── __init__.py
│   │   │       │           ├── joy_to_cmd_node.py
│   │   │       │           └── UTIL.py
│   │   │       ├── colcon_build.rc
│   │   │       ├── colcon_command_prefix_setup_py.sh
│   │   │       ├── colcon_command_prefix_setup_py.sh.env
│   │   │       ├── prefix_override
│   │   │       │   ├── __pycache__
│   │   │       │   │   └── sitecustomize.cpython-310.pyc
│   │   │       │   └── sitecustomize.py
│   │   │       └── triflamex_ros2_pkg.egg-info
│   │   │           ├── dependency_links.txt
│   │   │           ├── entry_points.txt
│   │   │           ├── PKG-INFO
│   │   │           ├── requires.txt
│   │   │           ├── SOURCES.txt
│   │   │           ├── top_level.txt
│   │   │           └── zip-safe
│   │   ├── checkWifi.py
│   │   ├── config.py
│   │   ├── enableMQTT.py
│   │   ├── install
│   │   │   ├── COLCON_IGNORE
│   │   │   ├── local_setup.bash
│   │   │   ├── local_setup.ps1
│   │   │   ├── local_setup.sh
│   │   │   ├── _local_setup_util_ps1.py
│   │   │   ├── _local_setup_util_sh.py
│   │   │   ├── local_setup.zsh
│   │   │   ├── setup.bash
│   │   │   ├── setup.ps1
│   │   │   ├── setup.sh
│   │   │   ├── setup.zsh
│   │   │   └── triflamex_ros2_pkg
│   │   │       ├── lib
│   │   │       │   └── python3.10
│   │   │       │       └── site-packages
│   │   │       │           └── triflamex_ros2_pkg
│   │   │       │               ├── __init__.py
│   │   │       │               ├── joy_to_cmd_node.py
│   │   │       │               ├── __pycache__
│   │   │       │               │   ├── __init__.cpython-310.pyc
│   │   │       │               │   ├── joy_to_cmd_node.cpython-310.pyc
│   │   │       │               │   └── UTIL.cpython-310.pyc
│   │   │       │               └── UTIL.py
│   │   │       └── share
│   │   │           ├── ament_index
│   │   │           │   └── resource_index
│   │   │           │       └── packages
│   │   │           └── triflamex_ros2_pkg
│   │   │               └── hook
│   │   │                   ├── ament_prefix_path.dsv
│   │   │                   ├── ament_prefix_path.ps1
│   │   │                   └── ament_prefix_path.sh
│   │   ├── laptop_pub.py
│   │   ├── laptop_sub.py
│   │   ├── log
│   │   │   ├── build_2025-06-13_11-23-23
│   │   │   │   ├── events.log
│   │   │   │   ├── logger_all.log
│   │   │   │   └── triflamex_ros2_pkg
│   │   │   │       ├── command.log
│   │   │   │       ├── stderr.log
│   │   │   │       ├── stdout.log
│   │   │   │       ├── stdout_stderr.log
│   │   │   │       └── streams.log
│   │   │   ├── COLCON_IGNORE
│   │   │   ├── latest -> latest_build
│   │   │   └── latest_build -> build_2025-06-13_11-23-23
│   │   ├── mqtt_client.py
│   │   ├── __pycache__
│   │   │   ├── checkWifi.cpython-310.pyc
│   │   │   ├── config.cpython-310.pyc
│   │   │   ├── laptop_pub.cpython-310.pyc
│   │   │   └── laptop_sub.cpython-310.pyc
│   │   └── triflamex_ros2_pkg
│   │       ├── build
│   │       │   ├── COLCON_IGNORE
│   │       │   └── triflamex_ros2_pkg
│   │       │       ├── build
│   │       │       │   └── lib
│   │       │       │       └── triflamex_ros2_pkg
│   │       │       │           ├── __init__.py
│   │       │       │           ├── joy_to_cmd_node.py
│   │       │       │           └── UTIL.py
│   │       │       ├── colcon_build.rc
│   │       │       ├── colcon_command_prefix_setup_py.sh
│   │       │       ├── colcon_command_prefix_setup_py.sh.env
│   │       │       ├── install.log
│   │       │       ├── prefix_override
│   │       │       │   ├── __pycache__
│   │       │       │   │   └── sitecustomize.cpython-310.pyc
│   │       │       │   └── sitecustomize.py
│   │       │       └── triflamex_ros2_pkg.egg-info
│   │       │           ├── dependency_links.txt
│   │       │           ├── entry_points.txt
│   │       │           ├── PKG-INFO
│   │       │           ├── requires.txt
│   │       │           ├── SOURCES.txt
│   │       │           ├── top_level.txt
│   │       │           └── zip-safe
│   │       ├── install
│   │       │   ├── COLCON_IGNORE
│   │       │   ├── local_setup.bash
│   │       │   ├── local_setup.ps1
│   │       │   ├── local_setup.sh
│   │       │   ├── _local_setup_util_ps1.py
│   │       │   ├── _local_setup_util_sh.py
│   │       │   ├── local_setup.zsh
│   │       │   ├── setup.bash
│   │       │   ├── setup.ps1
│   │       │   ├── setup.sh
│   │       │   ├── setup.zsh
│   │       │   └── triflamex_ros2_pkg
│   │       │       ├── lib
│   │       │       │   ├── python3.10
│   │       │       │   │   └── site-packages
│   │       │       │   │       ├── triflamex_ros2_pkg
│   │       │       │   │       │   ├── __init__.py
│   │       │       │   │       │   ├── joy_to_cmd_node.py
│   │       │       │   │       │   ├── __pycache__
│   │       │       │   │       │   │   ├── __init__.cpython-310.pyc
│   │       │       │   │       │   │   ├── joy_to_cmd_node.cpython-310.pyc
│   │       │       │   │       │   │   └── UTIL.cpython-310.pyc
│   │       │       │   │       │   └── UTIL.py
│   │       │       │   │       └── triflamex_ros2_pkg-0.0.0-py3.10.egg-info
│   │       │       │   │           ├── dependency_links.txt
│   │       │       │   │           ├── entry_points.txt
│   │       │       │   │           ├── PKG-INFO
│   │       │       │   │           ├── requires.txt
│   │       │       │   │           ├── SOURCES.txt
│   │       │       │   │           ├── top_level.txt
│   │       │       │   │           └── zip-safe
│   │       │       │   └── triflamex_ros2_pkg
│   │       │       │       └── joyToCmdNode
│   │       │       └── share
│   │       │           ├── ament_index
│   │       │           │   └── resource_index
│   │       │           │       └── packages
│   │       │           │           └── triflamex_ros2_pkg
│   │       │           ├── colcon-core
│   │       │           │   └── packages
│   │       │           │       └── triflamex_ros2_pkg
│   │       │           └── triflamex_ros2_pkg
│   │       │               ├── hook
│   │       │               │   ├── ament_prefix_path.dsv
│   │       │               │   ├── ament_prefix_path.ps1
│   │       │               │   ├── ament_prefix_path.sh
│   │       │               │   ├── pythonpath.dsv
│   │       │               │   ├── pythonpath.ps1
│   │       │               │   └── pythonpath.sh
│   │       │               ├── package.bash
│   │       │               ├── package.dsv
│   │       │               ├── package.ps1
│   │       │               ├── package.sh
│   │       │               ├── package.xml
│   │       │               └── package.zsh
│   │       ├── log
│   │       │   ├── build_2025-06-11_22-32-02
│   │       │   │   ├── events.log
│   │       │   │   ├── logger_all.log
│   │       │   │   └── triflamex_ros2_pkg
│   │       │   │       ├── command.log
│   │       │   │       ├── stderr.log
│   │       │   │       ├── stdout.log
│   │       │   │       ├── stdout_stderr.log
│   │       │   │       └── streams.log
│   │       │   ├── build_2025-06-11_22-40-57
│   │       │   │   ├── events.log
│   │       │   │   ├── logger_all.log
│   │       │   │   └── triflamex_ros2_pkg
│   │       │   │       ├── command.log
│   │       │   │       ├── stderr.log
│   │       │   │       ├── stdout.log
│   │       │   │       ├── stdout_stderr.log
│   │       │   │       └── streams.log
│   │       │   ├── build_2025-06-11_22-42-17
│   │       │   │   ├── events.log
│   │       │   │   ├── logger_all.log
│   │       │   │   └── triflamex_ros2_pkg
│   │       │   │       ├── command.log
│   │       │   │       ├── stderr.log
│   │       │   │       ├── stdout.log
│   │       │   │       ├── stdout_stderr.log
│   │       │   │       └── streams.log
│   │       │   ├── build_2025-06-11_22-43-40
│   │       │   │   ├── events.log
│   │       │   │   ├── logger_all.log
│   │       │   │   └── triflamex_ros2_pkg
│   │       │   │       ├── command.log
│   │       │   │       ├── stderr.log
│   │       │   │       ├── stdout.log
│   │       │   │       ├── stdout_stderr.log
│   │       │   │       └── streams.log
│   │       │   ├── build_2025-06-11_22-46-19
│   │       │   │   ├── events.log
│   │       │   │   ├── logger_all.log
│   │       │   │   └── triflamex_ros2_pkg
│   │       │   │       ├── command.log
│   │       │   │       ├── stderr.log
│   │       │   │       ├── stdout.log
│   │       │   │       ├── stdout_stderr.log
│   │       │   │       └── streams.log
│   │       │   ├── build_2025-06-11_22-48-59
│   │       │   │   ├── events.log
│   │       │   │   ├── logger_all.log
│   │       │   │   └── triflamex_ros2_pkg
│   │       │   │       ├── command.log
│   │       │   │       ├── stderr.log
│   │       │   │       ├── stdout.log
│   │       │   │       ├── stdout_stderr.log
│   │       │   │       └── streams.log
│   │       │   ├── build_2025-06-11_22-52-20
│   │       │   │   ├── events.log
│   │       │   │   ├── logger_all.log
│   │       │   │   └── triflamex_ros2_pkg
│   │       │   │       ├── command.log
│   │       │   │       ├── stderr.log
│   │       │   │       ├── stdout.log
│   │       │   │       ├── stdout_stderr.log
│   │       │   │       └── streams.log
│   │       │   ├── build_2025-06-11_23-05-02
│   │       │   │   ├── events.log
│   │       │   │   ├── logger_all.log
│   │       │   │   └── triflamex_ros2_pkg
│   │       │   │       ├── command.log
│   │       │   │       ├── stderr.log
│   │       │   │       ├── stdout.log
│   │       │   │       ├── stdout_stderr.log
│   │       │   │       └── streams.log
│   │       │   ├── build_2025-06-11_23-21-44
│   │       │   │   ├── events.log
│   │       │   │   ├── logger_all.log
│   │       │   │   └── triflamex_ros2_pkg
│   │       │   │       ├── command.log
│   │       │   │       ├── stderr.log
│   │       │   │       ├── stdout.log
│   │       │   │       ├── stdout_stderr.log
│   │       │   │       └── streams.log
│   │       │   ├── build_2025-06-11_23-27-36
│   │       │   │   ├── events.log
│   │       │   │   ├── logger_all.log
│   │       │   │   └── triflamex_ros2_pkg
│   │       │   │       ├── command.log
│   │       │   │       ├── stderr.log
│   │       │   │       ├── stdout.log
│   │       │   │       ├── stdout_stderr.log
│   │       │   │       └── streams.log
│   │       │   ├── build_2025-06-11_23-46-32
│   │       │   │   ├── events.log
│   │       │   │   ├── logger_all.log
│   │       │   │   └── triflamex_ros2_pkg
│   │       │   │       ├── command.log
│   │       │   │       ├── stderr.log
│   │       │   │       ├── stdout.log
│   │       │   │       ├── stdout_stderr.log
│   │       │   │       └── streams.log
│   │       │   ├── build_2025-06-12_18-24-58
│   │       │   │   ├── events.log
│   │       │   │   ├── logger_all.log
│   │       │   │   └── triflamex_ros2_pkg
│   │       │   │       ├── command.log
│   │       │   │       ├── stderr.log
│   │       │   │       ├── stdout.log
│   │       │   │       ├── stdout_stderr.log
│   │       │   │       └── streams.log
│   │       │   ├── build_2025-06-13_04-26-34
│   │       │   │   ├── events.log
│   │       │   │   ├── logger_all.log
│   │       │   │   └── triflamex_ros2_pkg
│   │       │   │       ├── command.log
│   │       │   │       ├── stderr.log
│   │       │   │       ├── stdout.log
│   │       │   │       ├── stdout_stderr.log
│   │       │   │       └── streams.log
│   │       │   ├── build_2025-06-13_04-30-40
│   │       │   │   ├── events.log
│   │       │   │   ├── logger_all.log
│   │       │   │   └── triflamex_ros2_pkg
│   │       │   │       ├── command.log
│   │       │   │       ├── stderr.log
│   │       │   │       ├── stdout.log
│   │       │   │       ├── stdout_stderr.log
│   │       │   │       └── streams.log
│   │       │   ├── build_2025-06-13_04-43-51
│   │       │   │   ├── events.log
│   │       │   │   ├── logger_all.log
│   │       │   │   └── triflamex_ros2_pkg
│   │       │   │       ├── command.log
│   │       │   │       ├── stderr.log
│   │       │   │       ├── stdout.log
│   │       │   │       ├── stdout_stderr.log
│   │       │   │       └── streams.log
│   │       │   ├── build_2025-06-13_04-46-21
│   │       │   │   ├── events.log
│   │       │   │   ├── logger_all.log
│   │       │   │   └── triflamex_ros2_pkg
│   │       │   │       ├── command.log
│   │       │   │       ├── stderr.log
│   │       │   │       ├── stdout.log
│   │       │   │       ├── stdout_stderr.log
│   │       │   │       └── streams.log
│   │       │   ├── build_2025-06-13_04-48-56
│   │       │   │   ├── events.log
│   │       │   │   ├── logger_all.log
│   │       │   │   └── triflamex_ros2_pkg
│   │       │   │       ├── command.log
│   │       │   │       ├── stderr.log
│   │       │   │       ├── stdout.log
│   │       │   │       ├── stdout_stderr.log
│   │       │   │       └── streams.log
│   │       │   ├── build_2025-06-13_04-55-08
│   │       │   │   ├── events.log
│   │       │   │   ├── logger_all.log
│   │       │   │   └── triflamex_ros2_pkg
│   │       │   │       ├── command.log
│   │       │   │       ├── stderr.log
│   │       │   │       ├── stdout.log
│   │       │   │       ├── stdout_stderr.log
│   │       │   │       └── streams.log
│   │       │   ├── build_2025-06-13_05-39-34
│   │       │   │   ├── events.log
│   │       │   │   ├── logger_all.log
│   │       │   │   └── triflamex_ros2_pkg
│   │       │   │       ├── command.log
│   │       │   │       ├── stderr.log
│   │       │   │       ├── stdout.log
│   │       │   │       ├── stdout_stderr.log
│   │       │   │       └── streams.log
│   │       │   ├── build_2025-06-13_05-42-40
│   │       │   │   ├── events.log
│   │       │   │   ├── logger_all.log
│   │       │   │   └── triflamex_ros2_pkg
│   │       │   │       ├── command.log
│   │       │   │       ├── stderr.log
│   │       │   │       ├── stdout.log
│   │       │   │       ├── stdout_stderr.log
│   │       │   │       └── streams.log
│   │       │   ├── build_2025-06-13_05-45-08
│   │       │   │   ├── events.log
│   │       │   │   ├── logger_all.log
│   │       │   │   └── triflamex_ros2_pkg
│   │       │   │       ├── command.log
│   │       │   │       ├── stderr.log
│   │       │   │       ├── stdout.log
│   │       │   │       ├── stdout_stderr.log
│   │       │   │       └── streams.log
│   │       │   ├── build_2025-06-13_05-58-47
│   │       │   │   ├── events.log
│   │       │   │   ├── logger_all.log
│   │       │   │   └── triflamex_ros2_pkg
│   │       │   │       ├── command.log
│   │       │   │       ├── stderr.log
│   │       │   │       ├── stdout.log
│   │       │   │       ├── stdout_stderr.log
│   │       │   │       └── streams.log
│   │       │   ├── build_2025-06-13_05-59-07
│   │       │   │   ├── events.log
│   │       │   │   ├── logger_all.log
│   │       │   │   └── triflamex_ros2_pkg
│   │       │   │       ├── command.log
│   │       │   │       ├── stderr.log
│   │       │   │       ├── stdout.log
│   │       │   │       ├── stdout_stderr.log
│   │       │   │       └── streams.log
│   │       │   ├── build_2025-06-13_06-00-14
│   │       │   │   ├── events.log
│   │       │   │   ├── logger_all.log
│   │       │   │   └── triflamex_ros2_pkg
│   │       │   │       ├── command.log
│   │       │   │       ├── stderr.log
│   │       │   │       ├── stdout.log
│   │       │   │       ├── stdout_stderr.log
│   │       │   │       └── streams.log
│   │       │   ├── build_2025-06-13_06-19-10
│   │       │   │   ├── events.log
│   │       │   │   ├── logger_all.log
│   │       │   │   └── triflamex_ros2_pkg
│   │       │   │       ├── command.log
│   │       │   │       ├── stderr.log
│   │       │   │       ├── stdout.log
│   │       │   │       ├── stdout_stderr.log
│   │       │   │       └── streams.log
│   │       │   ├── build_2025-06-13_06-22-39
│   │       │   │   ├── events.log
│   │       │   │   ├── logger_all.log
│   │       │   │   └── triflamex_ros2_pkg
│   │       │   │       ├── command.log
│   │       │   │       ├── stderr.log
│   │       │   │       ├── stdout.log
│   │       │   │       ├── stdout_stderr.log
│   │       │   │       └── streams.log
│   │       │   ├── build_2025-06-13_07-20-27
│   │       │   │   ├── events.log
│   │       │   │   ├── logger_all.log
│   │       │   │   └── triflamex_ros2_pkg
│   │       │   │       ├── command.log
│   │       │   │       ├── stderr.log
│   │       │   │       ├── stdout.log
│   │       │   │       ├── stdout_stderr.log
│   │       │   │       └── streams.log
│   │       │   ├── build_2025-06-13_07-21-15
│   │       │   │   ├── events.log
│   │       │   │   ├── logger_all.log
│   │       │   │   └── triflamex_ros2_pkg
│   │       │   │       ├── command.log
│   │       │   │       ├── stderr.log
│   │       │   │       ├── stdout.log
│   │       │   │       ├── stdout_stderr.log
│   │       │   │       └── streams.log
│   │       │   ├── build_2025-06-13_07-22-21
│   │       │   │   ├── events.log
│   │       │   │   ├── logger_all.log
│   │       │   │   └── triflamex_ros2_pkg
│   │       │   │       ├── command.log
│   │       │   │       ├── stderr.log
│   │       │   │       ├── stdout.log
│   │       │   │       ├── stdout_stderr.log
│   │       │   │       └── streams.log
│   │       │   ├── build_2025-06-13_07-43-31
│   │       │   │   ├── events.log
│   │       │   │   ├── logger_all.log
│   │       │   │   └── triflamex_ros2_pkg
│   │       │   │       ├── command.log
│   │       │   │       ├── stderr.log
│   │       │   │       ├── stdout.log
│   │       │   │       ├── stdout_stderr.log
│   │       │   │       └── streams.log
│   │       │   ├── build_2025-06-13_07-49-16
│   │       │   │   ├── events.log
│   │       │   │   ├── logger_all.log
│   │       │   │   └── triflamex_ros2_pkg
│   │       │   │       ├── command.log
│   │       │   │       ├── stderr.log
│   │       │   │       ├── stdout.log
│   │       │   │       ├── stdout_stderr.log
│   │       │   │       └── streams.log
│   │       │   ├── build_2025-06-13_09-26-04
│   │       │   │   ├── events.log
│   │       │   │   ├── logger_all.log
│   │       │   │   └── triflamex_ros2_pkg
│   │       │   │       ├── command.log
│   │       │   │       ├── stderr.log
│   │       │   │       ├── stdout.log
│   │       │   │       ├── stdout_stderr.log
│   │       │   │       └── streams.log
│   │       │   ├── build_2025-06-13_09-45-12
│   │       │   │   ├── events.log
│   │       │   │   ├── logger_all.log
│   │       │   │   └── triflamex_ros2_pkg
│   │       │   │       ├── command.log
│   │       │   │       ├── stderr.log
│   │       │   │       ├── stdout.log
│   │       │   │       ├── stdout_stderr.log
│   │       │   │       └── streams.log
│   │       │   ├── build_2025-06-13_11-16-43
│   │       │   │   ├── events.log
│   │       │   │   ├── logger_all.log
│   │       │   │   └── triflamex_ros2_pkg
│   │       │   │       ├── command.log
│   │       │   │       ├── stderr.log
│   │       │   │       ├── stdout.log
│   │       │   │       ├── stdout_stderr.log
│   │       │   │       └── streams.log
│   │       │   ├── build_2025-06-13_11-17-42
│   │       │   │   ├── events.log
│   │       │   │   ├── logger_all.log
│   │       │   │   └── triflamex_ros2_pkg
│   │       │   │       ├── command.log
│   │       │   │       ├── stderr.log
│   │       │   │       ├── stdout.log
│   │       │   │       ├── stdout_stderr.log
│   │       │   │       └── streams.log
│   │       │   ├── build_2025-06-13_11-19-00
│   │       │   │   ├── events.log
│   │       │   │   ├── logger_all.log
│   │       │   │   └── triflamex_ros2_pkg
│   │       │   │       ├── command.log
│   │       │   │       ├── stderr.log
│   │       │   │       ├── stdout.log
│   │       │   │       ├── stdout_stderr.log
│   │       │   │       └── streams.log
│   │       │   ├── build_2025-06-13_11-21-07
│   │       │   │   ├── events.log
│   │       │   │   ├── logger_all.log
│   │       │   │   └── triflamex_ros2_pkg
│   │       │   │       ├── command.log
│   │       │   │       ├── stderr.log
│   │       │   │       ├── stdout.log
│   │       │   │       ├── stdout_stderr.log
│   │       │   │       └── streams.log
│   │       │   ├── build_2025-06-13_11-23-37
│   │       │   │   ├── events.log
│   │       │   │   ├── logger_all.log
│   │       │   │   └── triflamex_ros2_pkg
│   │       │   │       ├── command.log
│   │       │   │       ├── stderr.log
│   │       │   │       ├── stdout.log
│   │       │   │       ├── stdout_stderr.log
│   │       │   │       └── streams.log
│   │       │   ├── build_2025-06-13_11-24-26
│   │       │   │   ├── events.log
│   │       │   │   ├── logger_all.log
│   │       │   │   └── triflamex_ros2_pkg
│   │       │   │       ├── command.log
│   │       │   │       ├── stderr.log
│   │       │   │       ├── stdout.log
│   │       │   │       ├── stdout_stderr.log
│   │       │   │       └── streams.log
│   │       │   ├── build_2025-06-13_11-26-17
│   │       │   │   ├── events.log
│   │       │   │   ├── logger_all.log
│   │       │   │   └── triflamex_ros2_pkg
│   │       │   │       ├── command.log
│   │       │   │       ├── stderr.log
│   │       │   │       ├── stdout.log
│   │       │   │       ├── stdout_stderr.log
│   │       │   │       └── streams.log
│   │       │   ├── build_2025-06-13_11-28-35
│   │       │   │   ├── events.log
│   │       │   │   ├── logger_all.log
│   │       │   │   └── triflamex_ros2_pkg
│   │       │   │       ├── command.log
│   │       │   │       ├── stderr.log
│   │       │   │       ├── stdout.log
│   │       │   │       ├── stdout_stderr.log
│   │       │   │       └── streams.log
│   │       │   ├── build_2025-06-13_11-31-56
│   │       │   │   ├── events.log
│   │       │   │   ├── logger_all.log
│   │       │   │   └── triflamex_ros2_pkg
│   │       │   │       ├── command.log
│   │       │   │       ├── stderr.log
│   │       │   │       ├── stdout.log
│   │       │   │       ├── stdout_stderr.log
│   │       │   │       └── streams.log
│   │       │   ├── COLCON_IGNORE
│   │       │   ├── latest -> latest_build
│   │       │   └── latest_build -> build_2025-06-13_11-31-56
│   │       ├── package.xml
│   │       ├── resource
│   │       │   └── triflamex_ros2_pkg
│   │       ├── setup.cfg
│   │       ├── setup.py
│   │       └── triflamex_ros2_pkg
│   │           ├── build
│   │           │   └── COLCON_IGNORE
│   │           ├── __init__.py
│   │           ├── install
│   │           │   ├── COLCON_IGNORE
│   │           │   ├── local_setup.bash
│   │           │   ├── local_setup.ps1
│   │           │   ├── local_setup.sh
│   │           │   ├── _local_setup_util_ps1.py
│   │           │   ├── _local_setup_util_sh.py
│   │           │   ├── local_setup.zsh
│   │           │   ├── setup.bash
│   │           │   ├── setup.ps1
│   │           │   ├── setup.sh
│   │           │   └── setup.zsh
│   │           ├── joy_to_cmd_node.py
│   │           ├── log
│   │           │   ├── build_2025-06-13_11-30-55
│   │           │   │   ├── events.log
│   │           │   │   └── logger_all.log
│   │           │   ├── COLCON_IGNORE
│   │           │   ├── latest -> latest_build
│   │           │   └── latest_build -> build_2025-06-13_11-30-55
│   │           └── UTIL.py
│   ├── lidar_visualizer
│   │   ├── lidar.pde
│   │   └── sketch.properties
│   └── stm32
│       ├── Core
│       │   ├── Inc
│       │   │   ├── FreeRTOSConfig.h
│       │   │   ├── main.h
│       │   │   ├── stm32f1xx_hal_conf.h
│       │   │   └── stm32f1xx_it.h
│       │   ├── Src
│       │   │   ├── freertos.c
│       │   │   ├── main.c
│       │   │   ├── stm32f1xx_hal_msp.c
│       │   │   ├── stm32f1xx_it.c
│       │   │   ├── syscalls.c
│       │   │   ├── sysmem.c
│       │   │   └── system_stm32f1xx.c
│       │   └── Startup
│       │       └── startup_stm32f103c8tx.s
│       ├── Debug
│       │   ├── Core
│       │   │   ├── Src
│       │   │   │   ├── freertos.cyclo
│       │   │   │   ├── freertos.d
│       │   │   │   ├── freertos.o
│       │   │   │   ├── freertos.su
│       │   │   │   ├── main.cyclo
│       │   │   │   ├── main.d
│       │   │   │   ├── main.o
│       │   │   │   ├── main.su
│       │   │   │   ├── stm32f1xx_hal_msp.cyclo
│       │   │   │   ├── stm32f1xx_hal_msp.d
│       │   │   │   ├── stm32f1xx_hal_msp.o
│       │   │   │   ├── stm32f1xx_hal_msp.su
│       │   │   │   ├── stm32f1xx_it.cyclo
│       │   │   │   ├── stm32f1xx_it.d
│       │   │   │   ├── stm32f1xx_it.o
│       │   │   │   ├── stm32f1xx_it.su
│       │   │   │   ├── subdir.mk
│       │   │   │   ├── syscalls.cyclo
│       │   │   │   ├── syscalls.d
│       │   │   │   ├── syscalls.o
│       │   │   │   ├── syscalls.su
│       │   │   │   ├── sysmem.cyclo
│       │   │   │   ├── sysmem.d
│       │   │   │   ├── sysmem.o
│       │   │   │   ├── sysmem.su
│       │   │   │   ├── system_stm32f1xx.cyclo
│       │   │   │   ├── system_stm32f1xx.d
│       │   │   │   ├── system_stm32f1xx.o
│       │   │   │   └── system_stm32f1xx.su
│       │   │   └── Startup
│       │   │       ├── startup_stm32f103c8tx.d
│       │   │       ├── startup_stm32f103c8tx.o
│       │   │       └── subdir.mk
│       │   ├── Drivers
│       │   │   └── STM32F1xx_HAL_Driver
│       │   │       └── Src
│       │   │           ├── stm32f1xx_hal_cortex.cyclo
│       │   │           ├── stm32f1xx_hal_cortex.d
│       │   │           ├── stm32f1xx_hal_cortex.o
│       │   │           ├── stm32f1xx_hal_cortex.su
│       │   │           ├── stm32f1xx_hal.cyclo
│       │   │           ├── stm32f1xx_hal.d
│       │   │           ├── stm32f1xx_hal_dma.cyclo
│       │   │           ├── stm32f1xx_hal_dma.d
│       │   │           ├── stm32f1xx_hal_dma.o
│       │   │           ├── stm32f1xx_hal_dma.su
│       │   │           ├── stm32f1xx_hal_exti.cyclo
│       │   │           ├── stm32f1xx_hal_exti.d
│       │   │           ├── stm32f1xx_hal_exti.o
│       │   │           ├── stm32f1xx_hal_exti.su
│       │   │           ├── stm32f1xx_hal_flash.cyclo
│       │   │           ├── stm32f1xx_hal_flash.d
│       │   │           ├── stm32f1xx_hal_flash_ex.cyclo
│       │   │           ├── stm32f1xx_hal_flash_ex.d
│       │   │           ├── stm32f1xx_hal_flash_ex.o
│       │   │           ├── stm32f1xx_hal_flash_ex.su
│       │   │           ├── stm32f1xx_hal_flash.o
│       │   │           ├── stm32f1xx_hal_flash.su
│       │   │           ├── stm32f1xx_hal_gpio.cyclo
│       │   │           ├── stm32f1xx_hal_gpio.d
│       │   │           ├── stm32f1xx_hal_gpio_ex.cyclo
│       │   │           ├── stm32f1xx_hal_gpio_ex.d
│       │   │           ├── stm32f1xx_hal_gpio_ex.o
│       │   │           ├── stm32f1xx_hal_gpio_ex.su
│       │   │           ├── stm32f1xx_hal_gpio.o
│       │   │           ├── stm32f1xx_hal_gpio.su
│       │   │           ├── stm32f1xx_hal.o
│       │   │           ├── stm32f1xx_hal_pwr.cyclo
│       │   │           ├── stm32f1xx_hal_pwr.d
│       │   │           ├── stm32f1xx_hal_pwr.o
│       │   │           ├── stm32f1xx_hal_pwr.su
│       │   │           ├── stm32f1xx_hal_rcc.cyclo
│       │   │           ├── stm32f1xx_hal_rcc.d
│       │   │           ├── stm32f1xx_hal_rcc_ex.cyclo
│       │   │           ├── stm32f1xx_hal_rcc_ex.d
│       │   │           ├── stm32f1xx_hal_rcc_ex.o
│       │   │           ├── stm32f1xx_hal_rcc_ex.su
│       │   │           ├── stm32f1xx_hal_rcc.o
│       │   │           ├── stm32f1xx_hal_rcc.su
│       │   │           ├── stm32f1xx_hal.su
│       │   │           └── subdir.mk
│       │   ├── makefile
│       │   ├── Middlewares
│       │   │   ├── ENTITY
│       │   │   │   ├── motor.cyclo
│       │   │   │   ├── motor.d
│       │   │   │   ├── motor.o
│       │   │   │   ├── motor.su
│       │   │   │   └── subdir.mk
│       │   │   ├── HAL
│       │   │   │   ├── CAR
│       │   │   │   │   ├── CAR_program.cyclo
│       │   │   │   │   ├── CAR_program.d
│       │   │   │   │   ├── CAR_program.o
│       │   │   │   │   ├── CAR_program.su
│       │   │   │   │   └── subdir.mk
│       │   │   │   ├── CONTROL
│       │   │   │   │   ├── CONTROL_program.cyclo
│       │   │   │   │   ├── CONTROL_program.d
│       │   │   │   │   ├── CONTROL_program.o
│       │   │   │   │   ├── CONTROL_program.su
│       │   │   │   │   └── subdir.mk
│       │   │   │   └── SERVO
│       │   │   │       ├── SER_program.cyclo
│       │   │   │       ├── SER_program.d
│       │   │   │       ├── SER_program.o
│       │   │   │       ├── SER_program.su
│       │   │   │       └── subdir.mk
│       │   │   ├── MCAL
│       │   │   │   ├── GPIO
│       │   │   │   │   ├── GPIO_program.cyclo
│       │   │   │   │   ├── GPIO_program.d
│       │   │   │   │   ├── GPIO_program.o
│       │   │   │   │   ├── GPIO_program.su
│       │   │   │   │   └── subdir.mk
│       │   │   │   ├── TIMR
│       │   │   │   │   ├── subdir.mk
│       │   │   │   │   ├── TIM_program.cyclo
│       │   │   │   │   ├── TIM_program.d
│       │   │   │   │   ├── TIM_program.o
│       │   │   │   │   └── TIM_program.su
│       │   │   │   └── UART
│       │   │   │       ├── subdir.mk
│       │   │   │       ├── UART_program.cyclo
│       │   │   │       ├── UART_program.d
│       │   │   │       ├── UART_program.o
│       │   │   │       └── UART_program.su
│       │   │   ├── Third_Party
│       │   │   │   └── FreeRTOS
│       │   │   │       └── Source
│       │   │   │           ├── CMSIS_RTOS
│       │   │   │           │   ├── cmsis_os.cyclo
│       │   │   │           │   ├── cmsis_os.d
│       │   │   │           │   ├── cmsis_os.o
│       │   │   │           │   ├── cmsis_os.su
│       │   │   │           │   └── subdir.mk
│       │   │   │           ├── croutine.cyclo
│       │   │   │           ├── croutine.d
│       │   │   │           ├── croutine.o
│       │   │   │           ├── croutine.su
│       │   │   │           ├── event_groups.cyclo
│       │   │   │           ├── event_groups.d
│       │   │   │           ├── event_groups.o
│       │   │   │           ├── event_groups.su
│       │   │   │           ├── list.cyclo
│       │   │   │           ├── list.d
│       │   │   │           ├── list.o
│       │   │   │           ├── list.su
│       │   │   │           ├── portable
│       │   │   │           │   ├── GCC
│       │   │   │           │   │   └── ARM_CM3
│       │   │   │           │   │       ├── port.cyclo
│       │   │   │           │   │       ├── port.d
│       │   │   │           │   │       ├── port.o
│       │   │   │           │   │       ├── port.su
│       │   │   │           │   │       └── subdir.mk
│       │   │   │           │   └── MemMang
│       │   │   │           │       ├── heap_4.cyclo
│       │   │   │           │       ├── heap_4.d
│       │   │   │           │       ├── heap_4.o
│       │   │   │           │       ├── heap_4.su
│       │   │   │           │       └── subdir.mk
│       │   │   │           ├── queue.cyclo
│       │   │   │           ├── queue.d
│       │   │   │           ├── queue.o
│       │   │   │           ├── queue.su
│       │   │   │           ├── stream_buffer.cyclo
│       │   │   │           ├── stream_buffer.d
│       │   │   │           ├── stream_buffer.o
│       │   │   │           ├── stream_buffer.su
│       │   │   │           ├── subdir.mk
│       │   │   │           ├── tasks.cyclo
│       │   │   │           ├── tasks.d
│       │   │   │           ├── tasks.o
│       │   │   │           ├── tasks.su
│       │   │   │           ├── timers.cyclo
│       │   │   │           ├── timers.d
│       │   │   │           ├── timers.o
│       │   │   │           └── timers.su
│       │   │   └── UTIL
│       │   │       ├── parsing.cyclo
│       │   │       ├── parsing.d
│       │   │       ├── parsing.o
│       │   │       ├── parsing.su
│       │   │       └── subdir.mk
│       │   ├── objects.list
│       │   ├── objects.mk
│       │   ├── sources.mk
│       │   ├── stm32.elf
│       │   ├── stm32.list
│       │   └── stm32.map
│       ├── Drivers
│       │   ├── CMSIS
│       │   │   ├── Device
│       │   │   │   └── ST
│       │   │   │       └── STM32F1xx
│       │   │   │           ├── Include
│       │   │   │           │   ├── stm32f103xb.h
│       │   │   │           │   ├── stm32f1xx.h
│       │   │   │           │   └── system_stm32f1xx.h
│       │   │   │           └── LICENSE.txt
│       │   │   ├── Include
│       │   │   │   ├── cmsis_armcc.h
│       │   │   │   ├── cmsis_armclang.h
│       │   │   │   ├── cmsis_compiler.h
│       │   │   │   ├── cmsis_gcc.h
│       │   │   │   ├── cmsis_iccarm.h
│       │   │   │   ├── cmsis_version.h
│       │   │   │   ├── core_armv8mbl.h
│       │   │   │   ├── core_armv8mml.h
│       │   │   │   ├── core_cm0.h
│       │   │   │   ├── core_cm0plus.h
│       │   │   │   ├── core_cm1.h
│       │   │   │   ├── core_cm23.h
│       │   │   │   ├── core_cm33.h
│       │   │   │   ├── core_cm3.h
│       │   │   │   ├── core_cm4.h
│       │   │   │   ├── core_cm7.h
│       │   │   │   ├── core_sc000.h
│       │   │   │   ├── core_sc300.h
│       │   │   │   ├── mpu_armv7.h
│       │   │   │   ├── mpu_armv8.h
│       │   │   │   └── tz_context.h
│       │   │   └── LICENSE.txt
│       │   └── STM32F1xx_HAL_Driver
│       │       ├── Inc
│       │       │   ├── Legacy
│       │       │   │   └── stm32_hal_legacy.h
│       │       │   ├── stm32f1xx_hal_cortex.h
│       │       │   ├── stm32f1xx_hal_def.h
│       │       │   ├── stm32f1xx_hal_dma_ex.h
│       │       │   ├── stm32f1xx_hal_dma.h
│       │       │   ├── stm32f1xx_hal_exti.h
│       │       │   ├── stm32f1xx_hal_flash_ex.h
│       │       │   ├── stm32f1xx_hal_flash.h
│       │       │   ├── stm32f1xx_hal_gpio_ex.h
│       │       │   ├── stm32f1xx_hal_gpio.h
│       │       │   ├── stm32f1xx_hal.h
│       │       │   ├── stm32f1xx_hal_pwr.h
│       │       │   ├── stm32f1xx_hal_rcc_ex.h
│       │       │   ├── stm32f1xx_hal_rcc.h
│       │       │   ├── stm32f1xx_ll_bus.h
│       │       │   ├── stm32f1xx_ll_cortex.h
│       │       │   ├── stm32f1xx_ll_dma.h
│       │       │   ├── stm32f1xx_ll_exti.h
│       │       │   ├── stm32f1xx_ll_gpio.h
│       │       │   ├── stm32f1xx_ll_pwr.h
│       │       │   ├── stm32f1xx_ll_rcc.h
│       │       │   ├── stm32f1xx_ll_system.h
│       │       │   └── stm32f1xx_ll_utils.h
│       │       ├── LICENSE.txt
│       │       └── Src
│       │           ├── stm32f1xx_hal.c
│       │           ├── stm32f1xx_hal_cortex.c
│       │           ├── stm32f1xx_hal_dma.c
│       │           ├── stm32f1xx_hal_exti.c
│       │           ├── stm32f1xx_hal_flash.c
│       │           ├── stm32f1xx_hal_flash_ex.c
│       │           ├── stm32f1xx_hal_gpio.c
│       │           ├── stm32f1xx_hal_gpio_ex.c
│       │           ├── stm32f1xx_hal_pwr.c
│       │           ├── stm32f1xx_hal_rcc.c
│       │           └── stm32f1xx_hal_rcc_ex.c
│       ├── Middlewares
│       │   ├── ENTITY
│       │   │   ├── motor.c
│       │   │   └── motor.h
│       │   ├── HAL
│       │   │   ├── CAR
│       │   │   │   ├── CAR_interface.h
│       │   │   │   └── CAR_program.c
│       │   │   ├── CONTROL
│       │   │   │   ├── CONTROL_interface.h
│       │   │   │   └── CONTROL_program.c
│       │   │   └── SERVO
│       │   │       ├── SER_interface.h
│       │   │       └── SER_program.c
│       │   ├── MCAL
│       │   │   ├── GPIO
│       │   │   │   ├── GPIO_interface.h
│       │   │   │   └── GPIO_program.c
│       │   │   ├── TIMR
│       │   │   │   ├── TIM_interface.h
│       │   │   │   └── TIM_program.c
│       │   │   └── UART
│       │   │       ├── UART_interface.h
│       │   │       └── UART_program.c
│       │   ├── Third_Party
│       │   │   └── FreeRTOS
│       │   │       └── Source
│       │   │           ├── CMSIS_RTOS
│       │   │           │   ├── cmsis_os.c
│       │   │           │   └── cmsis_os.h
│       │   │           ├── croutine.c
│       │   │           ├── event_groups.c
│       │   │           ├── include
│       │   │           │   ├── croutine.h
│       │   │           │   ├── deprecated_definitions.h
│       │   │           │   ├── event_groups.h
│       │   │           │   ├── FreeRTOS.h
│       │   │           │   ├── list.h
│       │   │           │   ├── message_buffer.h
│       │   │           │   ├── mpu_prototypes.h
│       │   │           │   ├── mpu_wrappers.h
│       │   │           │   ├── portable.h
│       │   │           │   ├── projdefs.h
│       │   │           │   ├── queue.h
│       │   │           │   ├── semphr.h
│       │   │           │   ├── stack_macros.h
│       │   │           │   ├── StackMacros.h
│       │   │           │   ├── stream_buffer.h
│       │   │           │   ├── task.h
│       │   │           │   └── timers.h
│       │   │           ├── LICENSE
│       │   │           ├── list.c
│       │   │           ├── portable
│       │   │           │   ├── GCC
│       │   │           │   │   └── ARM_CM3
│       │   │           │   │       ├── port.c
│       │   │           │   │       └── portmacro.h
│       │   │           │   └── MemMang
│       │   │           │       └── heap_4.c
│       │   │           ├── queue.c
│       │   │           ├── stream_buffer.c
│       │   │           ├── tasks.c
│       │   │           └── timers.c
│       │   └── UTIL
│       │       ├── BIT_MATH.h
│       │       ├── parsing.c
│       │       ├── parsing.h
│       │       └── types.h
│       ├── sheemy.txt
│       ├── stm32 Debug.launch
│       ├── STM32F103C8TX_FLASH.ld
│       └── stm32.ioc
├── generateMD.py
├── hardware
│   └── BlazeRobot_Hardware
├── __init__.py
├── LICENSE
├── make.bat
├── Makefile
├── projectSkeleton.md
├── README.md
├── skeleton.md
├── source
│   ├── conf.py
│   ├── index.rst
│   ├── _static
│   └── _templates
├── system_architecture.md
├── test
│   ├── flame_response_test.c
│   └── sensor_validation
│       ├── ErrLogging.log
│       └── SensorData.csv
└── tree_output.txt

```
