from setuptools import setup, Extension
import os

os.environ['CC'] = 'g++'
module1 = Extension('dictionary_tree',
                    sources = ['bind.cpp', 'DictionaryTree.cpp', 'WordSolver.cpp'],
                    extra_compile_args=['-O3'])

setup (name = 'dictionary_tree',
       version = '1.0.0',
       description = 'Tree implementation of a dictionary.',
       author='Archie Meng',
       url='https://github.com/ArchieMeng/dictionary_tree',
       license='MIT',
       keywords='tree, dictionary',
       ext_modules=[module1],
       classifiers=[
        'Development Status :: 5 - Production/Stable',
        'Intended Audience :: Developers',
        'License :: OSI Approved :: MIT License',
        'Operating System :: OS Independent',
        'Operating System :: POSIX',
        'Programming Language :: C',
        'Programming Language :: Python :: 2',
        'Programming Language :: Python :: 3',
        'Programming Language :: Python :: Implementation :: CPython',
        'Topic :: Software Development :: Libraries :: Python Modules',
        ],
)
