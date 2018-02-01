#!/usr/bin/env python3
# -*- coding: UTF-8 -*-

# Copyright (C) 2018  Eddie Antonio Santos <easantos@ualberta.ca>
#
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <http://www.gnu.org/licenses/>.


from string import ascii_letters, digits

import pytest
from hypothesis import given
from hypothesis.strategies import text

from pctncd import decode

ascii_alphanumerics = ascii_letters + digits


def test_callable():
    "Sanity test. Most likely covered by other tests."
    assert decode("") is ""


@pytest.mark.skip
@given(text(alphabet=ascii_alphanumerics))
def test_identity_for_alphanumerics(s):
    assert s == decode(s)


# TODO: make sure I throw in some null characters


# TODO: make sure I throw in some overlong forms.
