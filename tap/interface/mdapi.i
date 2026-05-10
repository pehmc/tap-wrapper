%module(directors="1") mdapi

%pythonbegin %{
"""
Copyright (c) 2026 pehmc. Apache 2.0 License.
See LICENSE file in the project root for full license information.
"""
%}

%{
#include <iostream>
#include <string>
#include <boost/locale.hpp>
#include "TapAPICommDef.h"
#include "TapQuoteAPIDataType.h"
#include "TapQuoteAPI.h"
%}

%feature("python:annotations", "c");
%feature("director") ITapQuoteAPINotify;


%typemap(out) char[ANY], char[] {
    if ($1) {
        if (!strlen($1)) {
            $result = SWIG_FromCharPtrAndSize("", 0);
        } else {
            const std::string utf8_str = boost::locale::conv::to_utf<char>($1, "GBK");
            $result = SWIG_FromCharPtrAndSize(utf8_str.c_str(), utf8_str.size());
        }
    }
}


%typemap(in) TAPIINT32 & (TAPIINT32 temp) {
    if (PyList_Check($input) && PyList_Size($input) == 1) {
        PyObject *item = PyList_GetItem($input, 0);
        if (PyLong_Check(item)) {
            temp = (TAPIINT32)PyLong_AsLong(item);
            $1 = &temp;
        } else {
            PyErr_SetString(PyExc_TypeError, "list element must be an integer for TAPIINT32 &");
            SWIG_fail;
        }
    } else {
        PyErr_SetString(PyExc_TypeError, "expected a list with one integer for TAPIINT32 &");
        SWIG_fail;
    }
}

%typemap(argout) TAPIINT32 & {
    PyObject *o = PyLong_FromLong((long)(*$1));
    PyList_SetItem($input, 0, o);
}

%typemap(in) TAPIUINT32 * (TAPIUINT32 temp) {
    if (PyList_Check($input) && PyList_Size($input) == 1) {
        PyObject *item = PyList_GetItem($input, 0);
        if (PyLong_Check(item)) {
            temp = (TAPIUINT32)PyLong_AsLong(item);
            $1 = &temp;
        } else {
            PyErr_SetString(PyExc_TypeError, "list element must be an integer for TAPIUINT32 *");
            SWIG_fail;
        }
    } else {
        PyErr_SetString(PyExc_TypeError, "expected a list with one integer for TAPIUINT32 *");
        SWIG_fail;
    }
}

%typemap(argout) TAPIUINT32 * {
    PyObject *o = PyLong_FromUnsignedLong((unsigned long)(*$1));
    PyList_SetItem($input, 0, o);
}


%feature("director:except") {
    if ($error != NULL) {
        if (PyErr_ExceptionMatches(PyExc_SystemExit)) {
            throw Swig::DirectorMethodException("Exception: SystemExit");
        } else if (PyErr_ExceptionMatches(PyExc_SystemError)) {
            throw Swig::DirectorMethodException("Exception: SystemError");
        } else {
            PyErr_Print();
        }
    }
}


%include "TapAPICommDef.h"
%include "TapQuoteAPIDataType.h"
%include "TapQuoteAPI.h"