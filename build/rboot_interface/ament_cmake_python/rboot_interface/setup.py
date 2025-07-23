from setuptools import find_packages
from setuptools import setup

setup(
    name='rboot_interface',
    version='0.0.0',
    packages=find_packages(
        include=('rboot_interface', 'rboot_interface.*')),
)
