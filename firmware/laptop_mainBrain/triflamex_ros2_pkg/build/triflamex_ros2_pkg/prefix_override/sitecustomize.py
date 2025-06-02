import sys
if sys.prefix == '/usr':
    sys.real_prefix = sys.prefix
    sys.prefix = sys.exec_prefix = '/home/mohammedazab/myRepo/TriFlameX/firmware/laptop_mainBrain/triflamex_ros2_pkg/install/triflamex_ros2_pkg'
