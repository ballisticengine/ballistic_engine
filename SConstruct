from common_flags import *
BULLET_LIBS = ['BulletCollision', 'BulletSoftBody', 'BulletDynamics', 'LinearMath']
BOOST_LIBS = ['boost_timer', 'boost_filesystem', 'boost_system', 'boost_thread', 'boost_python', ]
SDL_LIBS = ['SDL2', 'SDL2_ttf', 'SDL2_image', ]
GL_LIBS = ['GL', 'GLEW', 'GLU']
GENERAL_LIBS = ['stdc++', 'pthread', 'python2.7', 'dl', ]
TEST_LIBS = ['gtest', 'gtest_main' ]

ALL_LIBS = GENERAL_LIBS + BOOST_LIBS + SDL_LIBS + GL_LIBS + BULLET_LIBS + ROCKET_LIBS

src = './src/'


env = Environment(CPPPATH=[
    '/usr/include/python2.7',
    '/usr/include/bullet',
    './src/ui/librocket_interfaces',
    '/usr/local/include/Rocket',
    './src',
])

main_env = Environment(CPPPATH=[
    './src',
     '/usr/include/python2.7',
    '/usr/include/bullet',
    './src/ui/librocket_interfaces',
    '/usr/local/include/Rocket',
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
    Glob(src + 'resources/WorldLoader.cpp'),
    Glob(src + 'resources/Loader.cpp'),
    Glob(src + 'world/*.cpp'),
    Glob(src + 'python/*.cpp'),
    Glob(src + 'engine/*.cpp'),
    Glob(src + 'io/*.cpp'),
    Glob(src + 'renderer/*.cpp'),
    Glob(src + 'renderer/actions/*.cpp'),
    Glob('./src/ui/librocket_interfaces/*.cpp'),
]

main_modules =  [Glob(src + 'main.cpp'),]

test_modules = modules + [
    src + '/test/test.cpp',


]

env.Append(LINKFLAGS=['-rdynamic'])

env.SharedLibrary('./bin/engine', modules, LIBS=ALL_LIBS, LIBPATH='.', CXXFLAGS=COMMON_CXX_FLAGS, )
env.Append(LINKFLAGS=['-Wl,-soname,libengine.so'])

main_env.Program('./bin/ballistic', main_modules, LIBS=['engine']+ALL_LIBS, LIBPATH='./bin', CXXFLAGS=COMMON_CXX_FLAGS, )
main_env.Append(LINKFLAGS=['-rdynamic'])

SConscript(src+'resources/SConstruct')
SConscript(src+'renderer/SConstruct')

if 'test' in COMMAND_LINE_TARGETS:
    test = env.Program('./test/test', test_modules, LIBS=ALL_LIBS+TEST_LIBS, LIBPATH='.', CXXFLAGS=COMMON_CXX_FLAGS, )
    test_cmd = env.Command( None, None, "./test/test" )






