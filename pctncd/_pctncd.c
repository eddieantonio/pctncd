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

#include <stdbool.h>
#include <assert.h>


/* Error value when the decoded character is not a nibble! */
#define INVALID_NIBBLE 0xF0

static char module_doctring[] =
    "percent-decoding, done the lame way.";
static char decode_doctring[] =
    "decode a percent-encoded string.";


/* Gross function that decodes a single hexadecimal digit in ASCII to its
 * appropriate integer value (a nibble).
 * Returns false if the digit is not a hexadecimal digit. */
static uint8_t decode_nibble(const char c) {
    switch (c) {
        case '0': return 0;
        case '1': return 1;
        case '2': return 2;
        case '3': return 3;
        case '4': return 4;
        case '5': return 5;
        case '6': return 6;
        case '7': return 7;
        case '8': return 8;
        case '9': return 9;
        case 'A': case 'a': return 10;
        case 'B': case 'b': return 11;
        case 'C': case 'c': return 12;
        case 'D': case 'd': return 13;
        case 'E': case 'e': return 14;
        case 'F': case 'f': return 15;
        default: return INVALID_NIBBLE;
    }
}

/* Decode two hexadecimal digits to one byte, placing the result in dest.
 * Returns false if the digits are not hexadecimal. */
static bool from_hex(const char * restrict src, char * restrict dest) {
    uint8_t upper = 0x00, lower = 0x00;
    if ((upper = decode_nibble(src[0])) != INVALID_NIBBLE) {
        if ((lower = decode_nibble(src[1])) != INVALID_NIBBLE) {
            *dest = upper << 4 | lower;
            return true;
        }
    }
    return false;
}


static PyObject *
pctncd_decode(PyObject *self, PyObject *args)
{
    PyObject *result = NULL;
    const char * restrict original;
    char * restrict dest;
    size_t decoded_size, capacity;

    // "s" format actually encodes as UTF-8, which is fine!
    // It also raises a ValueError when there's an embedded NUL. Nice!
    if (!PyArg_ParseTuple(args, "s", &original))
        return NULL;
    // TODO: use s# format?

    // assumption: original is a zero-terminated string.
    capacity = strlen(original);

    // Got an empty string? Return an empty string!
    // Avoids a zero-length allocation later.
    if (capacity == 0) {
        return PyUnicode_FromString("");       
    }

    /* Create an output array that we will slowly populate;
     * if the string does not contain any '%', its length will be
     * capacity. */
    char *output = malloc(capacity);
    if (output == NULL) {
        // XXX: Shouldn't I throw a memory error here?
        return NULL;
    }

    /* FROM THIS POINT ON, it's okay to goto finalize; */

    /* Start copying bytes one-by-one. */
    dest = output;
    decoded_size = 0;
    for (size_t srcidx = 0; original[srcidx] != '\0'; /* manual */) {
        if (original[srcidx] == '%') {
            /* Percent found! The next two bytes should be hex digits. */
            // TODO: ensure there are at least three characters at srcidx
            if (from_hex(&original[srcidx + 1], dest) == false) {
                PyErr_SetString(PyExc_ValueError, "invalid hex escape");
                goto finalize;
            }
            srcidx += 3; /* Skip the %XX */
            dest++;
        } else {
            /* Copy that byte over! */
            *dest++ = original[srcidx++];
        }
        decoded_size++;
    }
    assert(decoded_size <= capacity);

    result = PyUnicode_DecodeUTF8(output, decoded_size, NULL);

finalize:
    free(output);
    return result;
}


static PyMethodDef PctncdMethods[] = {
    {"decode", pctncd_decode, METH_VARARGS, decode_doctring},

    /* Sentinel */
    {NULL, NULL, 0, NULL}
};


static struct PyModuleDef pctncd_module = {
    PyModuleDef_HEAD_INIT,
    "_pctncd",          /* name of module */
    module_doctring,    /* module documentation */
    -1,                 /* size of per-interpret state of the module, or -1 if
                           the module keeps state in global variables... */
    PctncdMethods
};


PyMODINIT_FUNC
PyInit__pctncd(void)
{
    return PyModule_Create(&pctncd_module);
}
