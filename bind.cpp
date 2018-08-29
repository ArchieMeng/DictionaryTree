//
// Created by archiemeng on 18-8-28.
//

#include <Python.h>
#include "DictionaryTree.h"

typedef struct {
    PyObject_HEAD;
    int size = 0;
    DictionaryTree* dict = NULL;
} DT;

static int
init(DT *self) {
    self->dict = new DictionaryTree;
    return !!(self->dict);
}

static void
dealloc(DT *self) {
    if (self->dict) {
        delete self->dict;
    }
    PyObject_Del((PyObject*) self);
}

static PyObject *
insert(DT *self, PyObject *args) {
    char *s;
    if(!PyArg_ParseTuple(args, "s", &s)) {
        return NULL;
    }
    self->dict->insert(s);
    Py_RETURN_NONE;
}

static PyObject *
find(DT *self, PyObject *args) {
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

static PyMethodDef methods[] = {
   { "insert", (PyCFunction)insert, METH_VARARGS, NULL },
   { "find", (PyCFunction)find, METH_VARARGS, NULL },
   { NULL, NULL, 0, NULL }
};

static PyTypeObject DictionaryTreeType = {
    PyVarObject_HEAD_INIT(NULL, 0)
    "dictionary_tree.DictionaryTree",               /* tp_name */
    sizeof(DT),             /* tp_basicsize */
    0,                       /* tp_itemsize */
    (destructor)dealloc, /* tp_dealloc */
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
    methods,             /* tp_methods */
    0,                       /* tp_members */
    0,                       /* tp_getset */
    0,                       /* tp_base */
    0,                       /* tp_dict */
    0,                       /* tp_descr_get */
    0,                       /* tp_descr_set */
    0,                       /* tp_dictoffset */
    (initproc)init,      /* tp_init */
    0,                       /* tp_alloc */
    PyType_GenericNew,                       /* tp_new */
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

#if PY_MAJOR_VERSION >= 3
    m = PyModule_Create(&moduledef);
#else
    m = Py_InitModule3("dictionary_tree", NULL, NULL);
#endif

    if (m == NULL)
        return NULL;

    Py_INCREF(&DictionaryTreeType);
    PyModule_AddObject(m, "DictionaryTree", (PyObject *) &DictionaryTreeType);

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