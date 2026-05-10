%module(directors="1") tdapi

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
#include "iTapAPICommDef.h"
#include "iTapTradeAPIDataType.h"
#include "iTapTradeAPI.h"
%}

%feature("doxygen:ignore:system", range="line");
%feature("doxygen:ignore:company", range="line");
%feature("doxygen:ignore:history", range="line");
%feature("doxygen:ignore:file", range="line");

%feature("python:annotations", "c");
%feature("director") ITapTrade::ITapTradeAPINotify;

// 扁平化 C++ 命名空间
%rename("%s") "";

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

%typemap(out) const char * {
    if ($1) {
        if (!strlen($1)) {
            $result = SWIG_FromCharPtrAndSize("", 0);
        } else {
            const std::string utf8_str = boost::locale::conv::to_utf<char>($1, "GBK");
            $result = SWIG_FromCharPtrAndSize(utf8_str.c_str(), utf8_str.size());
        }
    }
}

// --- TAPIINT32 & ---
%typemap(in) ITapTrade::TAPIINT32 & (ITapTrade::TAPIINT32 temp) {
    if (PyList_Check($input) && PyList_Size($input) == 1) {
        PyObject *item = PyList_GetItem($input, 0);
        if (PyLong_Check(item)) {
            temp = (ITapTrade::TAPIINT32)PyLong_AsLong(item);
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

%typemap(argout) ITapTrade::TAPIINT32 & {
    PyObject *o = PyLong_FromLong((long)(*$1));
    PyList_SetItem($input, 0, o);
}

// --- TAPIUINT32 * ---
%typemap(in) ITapTrade::TAPIUINT32 * (ITapTrade::TAPIUINT32 temp) {
    if (PyList_Check($input) && PyList_Size($input) == 1) {
        PyObject *item = PyList_GetItem($input, 0);
        if (PyLong_Check(item)) {
            temp = (ITapTrade::TAPIUINT32)PyLong_AsLong(item);
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

%typemap(argout) ITapTrade::TAPIUINT32 * {
    PyObject *o = PyLong_FromUnsignedLong((unsigned long)(*$1));
    PyList_SetItem($input, 0, o);
}

// --- TAPISTR_50 * ---
%typemap(in) ITapTrade::TAPISTR_50 * (char temp[51]) {
    if (PyList_Check($input) && PyList_Size($input) == 1) {
        PyObject *item = PyList_GetItem($input, 0);
        if (PyUnicode_Check(item)) {
            const char *s = PyUnicode_AsUTF8(item);
            strncpy(temp, s, 50);
            temp[50] = '\0';
            $1 = (ITapTrade::TAPISTR_50 *)temp;
        } else {
            PyErr_SetString(PyExc_TypeError, "list element must be a string for TAPISTR_50 *");
            SWIG_fail;
        }
    } else {
        PyErr_SetString(PyExc_TypeError, "expected a list with one string for TAPISTR_50 *");
        SWIG_fail;
    }
}

%typemap(argout) ITapTrade::TAPISTR_50 * {
    if ($1) {
        const char *raw = (const char *)$1;
        if (!strlen(raw)) {
            PyObject *o = SWIG_FromCharPtrAndSize("", 0);
            PyList_SetItem($input, 0, o);
        } else {
            const std::string utf8_str = boost::locale::conv::to_utf<char>(raw, "GBK");
            PyObject *o = SWIG_FromCharPtrAndSize(utf8_str.c_str(), utf8_str.size());
            PyList_SetItem($input, 0, o);
        }
    }
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

%include "iTapAPICommDef.h"
%include "iTapTradeAPIDataType.h"
%include "iTapTradeAPI.h"