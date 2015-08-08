import os
from SCons.Script import *
#BOOST_LIBS = ['boost_timer', 'boost_filesystem', 'boost_system', 'boost_thread', 'boost_python', ]
WD = os.path.dirname(__file__)+'/..'
PYTHON_DIR = WD + '/python'
BOOST_DIR = WD + '/boost'
PYTHON_LIB_DIR = PYTHON_DIR + '/lib'
BOOST_LIB_DIR=BOOST_DIR+'/lib'
COMMON_CXX_FLAGS = "-std=c++1y"

LIBPATH = PYTHON_LIB_DIR+':'+BOOST_DIR+'/lib'

"""BOOST_LIBS = [File(BOOST_LIB_DIR+'/'+'libboost_system.a'),
              File(BOOST_LIB_DIR+'/'+'libboost_filesystem.a'),
              File(BOOST_LIB_DIR+'/'+'libboost_thread.a'),
              File(BOOST_LIB_DIR+'/'+'libboost_python.a'),
              File(BOOST_LIB_DIR+'/'+'libboost_timer.a'),              ]
"""
print "dbg" , BOOST_LIB_DIR+'/'+'libboost_timer.a'