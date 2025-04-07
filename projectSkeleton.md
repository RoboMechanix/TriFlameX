```
boombot-firefighter/
├── docs/
│   ├── images/
│   ├── hardware_diagram.png
│   ├── software_architecture.md
│   └── README.md
├── firmware/                    # STM32 Embedded Code
│   └──stm32/
│       ├── src/
│       │    ├── main.c
│       │    ├── motor_control.c
│       │    ├── flame_sensor.c
│       │    ├── ultrasonic_sensor.c
│       │    └── extinguisher_control.c
│       ├── inc/
│           └── headers here
├── cad/                         
│   ├── 3d_model/
│   │   ├── base_bot.stl
│   │   ├── fire_module.stl
│   │   └── wheel_mount.stl
│   ├── design_files/
│   │   ├── boombot_cad.sldprt     # SolidWorks / Fusion360
│   │   └── boombot_assembly.sldasm
│   └── exploded_views/
│       └── boombot_exploded.png
├── hardware/                    # Schematics and Wiring
│   ├── circuit_diagram.kicad
│   ├── power_distribution.png
│   ├── pin_mapping.md
│   └── BOM.md
├── software/                    # Optional PC or AI code
│   ├── interface/               # GUI, monitoring, etc.
│   └── scripts/                 # Data logging, control testing
├── test/
│   ├── sensor_validation/
│   └── flame_response_test.md
├── simulation/                  # Optional: Webots or Gazebo
│   └── robot_model/
├── media/                       # For README visuals
│   ├── demo.gif
│   └── build_pics/
├── LICENSE
├── README.md
├── CONTRIBUTING.md
└── .gitignore
```
