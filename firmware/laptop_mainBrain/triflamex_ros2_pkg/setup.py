from setuptools import setup

package_name = 'triflamex_ros2_pkg'

setup(
    name=package_name,
    version='0.0.0',
    packages=[package_name],
    py_modules=[],
    data_files=[
        ('share/ament_index/resource_index/packages',
            ['resource/' + package_name]),
        ('share/' + package_name, ['package.xml']),
    ],
    install_requires=['setuptools'],
    zip_safe=True,
    maintainer='Mohammed Azab',
    maintainer_email='Mohammed@azab.io',
    description='ROS2 Python package for joystick to command translation',
    license='MIT',
    tests_require=['pytest'],
    entry_points={
        'console_scripts': [
            'joyToCmdNode = triflamex_ros2_pkg.joy_to_cmd_node:main'
        ],
    },
)
