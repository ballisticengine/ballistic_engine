from common_flags import *
BULLET_LIBS = ['BulletCollision', 'BulletSoftBody', 'BulletDynamics', 'LinearMath']
BOOST_LIBS = ['boost_timer', 'boost_filesystem', 'boost_system', 'boost_thread', 'boost_python-py34', ]
SDL_LIBS = ['SDL2', 'SDL2_ttf', 'SDL2_image', ]
GL_LIBS = ['GL', 'GLEW', 'GLU']
GENERAL_LIBS = ['stdc++', 'pthread', 'python3.4m', 'dl', ]
TEST_LIBS = ['gtest', 'gtest_main' ]

ALL_LIBS = GENERAL_LIBS + BOOST_LIBS + SDL_LIBS + GL_LIBS + BULLET_LIBS

src = './src/cpp/'


SConscript(src+'resources/SConstruct')
SConscript(src+'renderer/SConstruct')


env = Environment(CPPPATH=[
    '/usr/include/python3.4m',
    '/usr/include/bullet',
    './src/hpp',
])



modules = [

    Glob(src + 'types/*.cpp'),
    Glob(src + 'entities/*.cpp'),
    Glob(src + 'libload/*.cpp'),
    Glob(src + 'config/*.cpp'),
    Glob(src + 'anim/*.cpp'),
    Glob(src + 'misc/*.cpp'),
    Glob(src + 'physics/*.cpp'),
    Glob(src + 'time/*.cpp'),
    Glob(src + 'ui/*.cpp'),
    Glob(src + 'resources/ResourceManager.cpp'),
    Glob(src + 'resources/LevelManager.cpp'),
    Glob(src + 'resources/exceptions.cpp'),
    Glob(src + 'world/*.cpp'),
    Glob(src + 'python/*.cpp'),
    Glob(src + 'engine.cpp'),
    Glob(src + 'io/*.cpp'),
    Glob(src + 'renderer/*.cpp')

]

main_modules = modules + [Glob(src + 'main.cpp'),



                          ]

test_modules = modules + [
    src + '/test/test.cpp',


]

env.Append(LINKFLAGS='-rdynamic')

env.Program('./bin/ballistic', main_modules, LIBS=ALL_LIBS, LIBPATH='.', CXXFLAGS=COMMON_CXX_FLAGS, )



if 'test' in COMMAND_LINE_TARGETS:
    test = env.Program('./test/test', test_modules, LIBS=ALL_LIBS+TEST_LIBS, LIBPATH='.', CXXFLAGS=COMMON_CXX_FLAGS, )
    test_cmd = env.Command( None, None, "./test/test" )






