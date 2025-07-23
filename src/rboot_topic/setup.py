from setuptools import setup

package_name = 'rboot_topic'

setup(
    name=package_name,
    version='0.0.1',
    packages=[package_name],
    data_files=[
        ('share/ament_index/resource_index/packages',
            ['resource/' + package_name]),
        ('share/' + package_name, ['package.xml']),
    ],
    install_requires=['setuptools'],
    zip_safe=True,
    maintainer='muzixiaowen',
    maintainer_email='xin.li@switchpi.com',
    description='TODO: Package description',
    license='TODO: License declaration',
    tests_require=['pytest'],
    entry_points={
        'console_scripts': [
         'dummy2_ros_controller  = rboot_topic.dummy2_ros_controller:main',
        ],
    },
)
