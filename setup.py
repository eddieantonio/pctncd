#!/usr/bin/env python3
# -*- coding: UTF-8 -*-

from setuptools import setup, Extension, find_packages


c_ext = Extension('_pctncd',
                  sources=['_pctncd.c'])


setup(
    name='pctncd',
    packages=find_packages(),
    ext_modules=[c_ext],
    extras_require={
        'test': ['tox']
    }
)
