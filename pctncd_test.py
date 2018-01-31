#!/usr/bin/env python3
# -*- coding: UTF-8 -*-

from pctncd import decode
from string import ascii_letters, digits

from hypothesis import given
from hypothesis.strategies import text


ascii_alphanumerics = ascii_letters + digits


@given(text(alphabet=ascii_alphanumerics))
def test_identity_for_alphanumerics(s):
    assert s == decode(s)
