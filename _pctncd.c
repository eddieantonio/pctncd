/*
 * Copyright (C) 2018  Eddie Antonio Santos <easantos@ualberta.ca>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <Python.h>

static char module_doctring[] =
    "percent-decoding, done the lame way.";
static char decode_doctring[] =
    "decode a percent-encoded string.";

static PyObject *
pctncd_decode(PyObject *self, PyObject *args)
{
    // "s" format actually encodes as UTF-8, which is fine!
    // It also raises a value error when there's an embedded NUL. Nice!
    const char *buffer;
    if (!PyArg_ParseTuple(args, "s", &buffer))
        return NULL;
    (void)buffer;

    Py_RETURN_NONE;
}


static PyMethodDef PctncdMethods[] = {
    {"decode", pctncd_decode, METH_VARARGS, decode_doctring},

    /* Sentinel */
    {NULL, NULL, 0, NULL}
};


static struct PyModuleDef pctncd_module = {
    PyModuleDef_HEAD_INIT,
    "pctncd",           /* name of module */
    module_doctring,    /* module documentation */
    -1,                 /* size of per-interpret state of the module, or -1 if
                           the module keeps state in global variables... */
    PctncdMethods
};


PyMODINIT_FUNC
PyInit_pctncd(void)
{
    return PyModule_Create(&pctncd_module);
}
