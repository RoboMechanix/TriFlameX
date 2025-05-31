import sys
if sys.prefix == '/usr':
    sys.real_prefix = sys.prefix
    sys.prefix = sys.exec_prefix = '/home/mohammedazab/myRepo/TriFlameX/firmware/laptop_mainBrain/triFlameX_ros2_pkg/install/triFlameX_ros2_pkg'
