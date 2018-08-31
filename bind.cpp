//
// Created by archiemeng on 18-8-28.
//
#define _DEBUG
#include <Python.h>
#include "DictionaryTree.h"
#include "WordSolver.h"

// DictionaryTree
typedef struct {
    PyObject_HEAD;
    DictionaryTree *dict = NULL;
} DT;

static int
DT_init(DT *self) {
    self->dict = new DictionaryTree;
    return self->dict != nullptr;
}

static void
DT_dealloc(DT *self) {
    delete self->dict;

    PyObject_Del(self);
}

static PyObject *
DT_insert(DT *self, PyObject *args) {
    char *s;
    if(!PyArg_ParseTuple(args, "s", &s)) {
        return NULL;
    }
    self->dict->insert(s);
    Py_RETURN_NONE;
}

static PyObject *
DT_find(DT *self, PyObject *args) {
    char *s;
    if(!PyArg_ParseTuple(args, "s", &s)) {
        return NULL;
    }

    if(self->dict->find(s)) {
        Py_RETURN_TRUE;
    } else {
        Py_RETURN_FALSE;
    }
}

static PyMethodDef DictionaryTree_methods[] = {
   { "insert", (PyCFunction)DT_insert, METH_VARARGS, NULL },
   { "find", (PyCFunction)DT_find, METH_VARARGS, NULL },
   { NULL, NULL, 0, NULL }
};

static PyTypeObject DictionaryTreeType = {
    PyVarObject_HEAD_INIT(NULL, 0)
    "dictionary_tree.DictionaryTree",               /* tp_name */
    sizeof(DT),             /* tp_basicsize */
    0,                       /* tp_itemsize */
    (destructor)DT_dealloc, /* tp_dealloc */
    0,                       /* tp_print */
    0,                       /* tp_getattr */
    0,                       /* tp_setattr */
    0,                       /* tp_compare */
    0,      /* tp_repr */
    0,                       /* tp_as_number */
    0,        /* tp_as_sequence */
    0,         /* tp_as_mapping */
    0,                       /* tp_hash */
    0,                       /* tp_call */
    0,                       /* tp_str */
    0,                       /* tp_getattro */
    0,                       /* tp_setattro */
    0,                       /* tp_as_buffer */
    Py_TPFLAGS_DEFAULT,      /* tp_flags */
    0,                 /* tp_doc */
    0,                       /* tp_traverse */
    0,                       /* tp_clear */
    0,                       /* tp_richcompare */
    0,                       /* tp_weaklistoffset */
    0,                       /* tp_iter */
    0,                       /* tp_iternext */
    DictionaryTree_methods,             /* tp_methods */
    0,                       /* tp_members */
    0,                       /* tp_getset */
    0,                       /* tp_base */
    0,                       /* tp_dict */
    0,                       /* tp_descr_get */
    0,                       /* tp_descr_set */
    0,                       /* tp_dictoffset */
    (initproc)DT_init,       /* tp_init */
    0,                       /* tp_alloc */
    PyType_GenericNew,       /* tp_new */
};

// WordSolver
typedef struct {
    PyObject_HEAD;
    WordSolver *solver = nullptr;
} WS;

static int
WS_init(WS *self) {
    self->solver = new WordSolver;
    return self->solver != nullptr;
}

static void
WS_dealloc(WS *self) {
    delete self->solver;
    PyObject_Del(self);
}

static PyObject *
WS_insert(WS *self, PyObject *args) {
    char *s;
    if(!PyArg_ParseTuple(args, "s", &s)) {
        return nullptr;
    }
    self->solver->insert(s);
    Py_RETURN_NONE;
}

static PyObject *
WS_find(WS *self, PyObject *args) {
    char *s;
    if(!PyArg_ParseTuple(args, "s", &s)) {
        return nullptr;
    }

    if(self->solver->find(s)) {
        Py_RETURN_TRUE;
    } else {
        Py_RETURN_FALSE;
    }
}

// Todo change all PyErr_BadArgument to PyErr_SetString
static PyObject *
WS_solve(WS *self, PyObject *args) {
    Py_ssize_t i, j, mLen, rLen;
    PyObject *row, *o;
    PyObject *list;
    vector<vector<char > > in;
    char *s = nullptr;
    vector<string> ans;

    if (!PyArg_ParseTuple(args, "O", &args)) {
        PyErr_SetString(PyExc_ValueError, "not object type");
        return nullptr;
    }

    mLen = PyObject_Length(args);
    if (mLen < 0) {
        PyErr_SetString(PyExc_ValueError, "input iterable should not be empty.");
        return nullptr;
    }

    for (i = 0; i < mLen; ++i) {
        vector<char> rv;
        row = PyObject_GetItem(args, PyLong_FromSsize_t(i));
        Py_INCREF(row);
        rLen = PyObject_Length(row);
#ifdef DEBUG
        printf("row length:%ld\n", rLen);
#endif
        if (rLen < 0) {
            PyErr_SetString(PyExc_ValueError, "iterable item should not be empty.");
            return nullptr;
        }

        for (j = 0;j < rLen;j++) {
            o = PyList_GetItem((_object*)row, j);
            Py_INCREF(o);
            s = PyUnicode_AsUTF8(o);
            Py_DECREF(o);
#ifdef DEBUG
            printf("s:%p, %s, o: %p, o repr:%s, row repr:%s\n",
                   s, s, o, PyUnicode_AsUTF8(PyObject_Repr(o)), PyUnicode_AsUTF8(PyObject_Repr(row)));
#endif
            if (s) {
                rv.push_back(*s);
            } else {
                PyErr_SetString(PyExc_ValueError, "item should be char.");
                return nullptr;
            }
        }
        Py_DECREF(row);
        in.push_back(rv);
    }
    ans = self->solver->solve(in);
#ifdef DEBUG
    puts("ans output");
    for (auto &iter1: ans) {
        puts(iter1.c_str());
    }
#endif
    list = PyList_New(ans.size());
    Py_ssize_t idx = 0u;
    for (auto &iter: ans) {
        PyList_SetItem(list, idx, PyUnicode_FromString(iter.c_str()));
        idx++;
    }
    return list;
}

static PyMethodDef WordSolver_methods[] = {
        { "insert", (PyCFunction)WS_insert, METH_VARARGS, NULL},
        { "find", (PyCFunction)WS_find, METH_VARARGS, NULL},
        { "solve", (PyCFunction)WS_solve, METH_VARARGS, NULL},
        {nullptr, nullptr, 0, nullptr}
};

static PyTypeObject WordSolverType = {
        PyVarObject_HEAD_INIT(NULL, 0)
        "dictionary_tree.WordSolver",               /* tp_name */
        sizeof(WS),             /* tp_basicsize */
        0,                       /* tp_itemsize */
(destructor)WS_dealloc, /* tp_dealloc */
        0,                       /* tp_print */
        0,                       /* tp_getattr */
        0,                       /* tp_setattr */
        0,                       /* tp_compare */
        0,      /* tp_repr */
        0,                       /* tp_as_number */
        0,        /* tp_as_sequence */
        0,         /* tp_as_mapping */
        0,                       /* tp_hash */
        0,                       /* tp_call */
        0,                       /* tp_str */
        0,                       /* tp_getattro */
        0,                       /* tp_setattro */
        0,                       /* tp_as_buffer */
        Py_TPFLAGS_DEFAULT,      /* tp_flags */
        0,                 /* tp_doc */
        0,                       /* tp_traverse */
        0,                       /* tp_clear */
        0,                       /* tp_richcompare */
        0,                       /* tp_weaklistoffset */
        0,                       /* tp_iter */
        0,                       /* tp_iternext */
        WordSolver_methods,             /* tp_methods */
        0,                       /* tp_members */
        0,                       /* tp_getset */
        0,                       /* tp_base */
        0,                       /* tp_dict */
        0,                       /* tp_descr_get */
        0,                       /* tp_descr_set */
        0,                       /* tp_dictoffset */
(initproc)WS_init,       /* tp_init */
        0,                       /* tp_alloc */
        PyType_GenericNew,       /* tp_new */
};

#if PY_MAJOR_VERSION >= 3
static struct PyModuleDef moduledef = {
    PyModuleDef_HEAD_INIT,
    "dictionary_tree",            /* m_name */
    NULL,          /* m_doc */
    -1,               /* m_size */
    NULL,             /* m_methods */
};
#endif

static PyObject *
moduleinit(void)
{
    PyObject *m;

    if (PyType_Ready(&DictionaryTreeType) < 0)
        return NULL;
    if (PyType_Ready(&WordSolverType) < 0)
        return NULL;

#if PY_MAJOR_VERSION >= 3
    m = PyModule_Create(&moduledef);
#else
    m = Py_InitModule3("dictionary_tree", NULL, NULL);
#endif

    if (m == NULL)
        return NULL;

    Py_INCREF(&DictionaryTreeType);
    Py_INCREF(&WordSolverType);
    PyModule_AddObject(m, "DictionaryTree", (PyObject *) &DictionaryTreeType);
    PyModule_AddObject(m, "WordSolver", (PyObject *) &WordSolverType);

    return m;
}

#if PY_MAJOR_VERSION < 3
PyMODINIT_FUNC
initdictionary_tree(void)
{
    moduleinit();
}
#else
PyMODINIT_FUNC
    PyInit_dictionary_tree(void)
    {
        return moduleinit();
    }
#endif