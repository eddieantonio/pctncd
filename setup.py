#!/usr/bin/env python3
# -*- coding: UTF-8 -*-

from setuptools import setup, find_packages


setup(
    name='pctncd',
    packages=find_packages(),
    extra_require={
        'test': ['tox', 'pytest', 'hypothesis']
    }
)
