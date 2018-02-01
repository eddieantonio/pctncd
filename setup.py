#!/usr/bin/env python3
# -*- coding: UTF-8 -*-

from setuptools import setup, Extension, find_packages


module = Extension('pctncd',
                   sources=['pctncd.c'])


setup(
    name='pctncd',
    packages=find_packages(),
    extras_require={
        'test': ['tox']
    }
)
