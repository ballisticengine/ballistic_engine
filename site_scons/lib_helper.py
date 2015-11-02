import os
from SCons.Script import *
from common_flags import *


def make_shared(target_file, sources, target_path, LIBS):
    root = os.path.dirname(__file__)+'/..'
    print "ROOT", root
    print "Making shared library", file

    env = Environment(CPPPATH=[
    '/usr/include/python2.7',
    '/usr/include/bullet',

    root + '/src',
    ])

    env['SHLIBPREFIX'] = ''

    lib = env.SharedLibrary(target_file,
                            sources,
                         LIBS=LIBS+['engine'],
                         LIBPATH='../../bin',
                        CXXFLAGS=COMMON_CXX_FLAGS,
    )
    fn = target_file+".so"
    env.Append(LINKFLAGS=['-Wl,-soname,'+fn])
    print "CP to", root+'/'+target_path+'/'+fn
    c = Command(target = root+'/'+target_path+'/'+fn,
        source = lib,
        action = Copy("$TARGET", "$SOURCE"))
    env.AlwaysBuild( c )