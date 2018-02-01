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


from urllib.parse import quote
from string import ascii_letters, digits, printable

import pytest
from hypothesis import given
from hypothesis.strategies import text

from pctncd import decode

ascii_alphanumerics = ascii_letters + digits


@given(text(alphabet=ascii_alphanumerics))
def test_identity_for_alphanumerics(s):
    "Alphanumerics should be returned verbatim."
    assert s == decode(s)


@given(text(alphabet=printable))
def test_ascii_printable(s):
    "Some printable ASCII characters should be quoted."
    assert s == decode(quote(s))


def test_bad_pct_escape():
    "Tests an invalid percent escape."
    s = "hello%2gworld"
    with pytest.raises(ValueError):
        decode(s)


def test_decode_nul():
    "Test decoding the ␀ character."
    assert "\x00" == decode("%00")


@given(text())
def test_full_unicode_range(s):
    "Some printable ASCII characters should be quoted."
    assert s == decode(quote(s))


# TODO: make sure I throw in some overlong forms.
