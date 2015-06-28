BULLET_LIBS = ['BulletCollision', 'BulletSoftBody', 'BulletDynamics', 'LinearMath']
BOOST_LIBS = ['boost_timer', 'boost_filesystem', 'boost_system', 'boost_thread', 'boost_python', ]
SDL_LIBS = ['SDL2', 'SDL2_ttf', 'SDL2_image', ]
GL_LIBS = ['GL', 'GLEW', 'GLU']
GENERAL_LIBS = ['stdc++', 'pthread', 'python2.7', 'dl', ]
TEST_LIBS = ['gtest', 'gtest_main' ]

ALL_LIBS = GENERAL_LIBS + BOOST_LIBS + SDL_LIBS + GL_LIBS + BULLET_LIBS


env = Environment(CPPPATH=[
    '/usr/include/python2.7',
    '/usr/include/bullet',
    './src/hpp',
])

shared_env = Environment(CPPPATH=[
    '/usr/include/python2.7',
    '/usr/include/bullet',
    './src/hpp',
])

shared_env['SHLIBPREFIX'] = ''

src = './src/cpp/'

shared_env.SharedLibrary('./bin/rendererGL', [

    'src/cpp/renderer/GL/rendererGL.cpp',
    'src/cpp/renderer/rendererAbstract.cpp',


],
                         LIBS=ALL_LIBS,
                         LIBPATH='.'
)
shared_env.Append(LINKFLAGS=['-Wl,-soname,rendererGL.so'])

modules = [
    Glob(src + 'engine.cpp'),
    Glob(src + 'types/*.cpp'),
    Glob(src + 'entities/*.cpp'),
    Glob(src + 'factories/*.cpp'),
    Glob(src + 'loaders/*.cpp'),
    Glob(src + 'libload/*.cpp'),
    Glob(src + 'io/*.cpp'),
    Glob(src + 'config/*.cpp'),
    Glob(src + 'anim/*.cpp'),
    Glob(src + 'misc/*.cpp'),
    Glob(src + 'physics/*.cpp'),
    Glob(src + 'python/*.cpp'),
    Glob(src + 'time/*.cpp'),
    Glob(src + 'ui/*.cpp'),
    Glob(src + 'world/*.cpp'),
    'bin/rendererGL.so',
]

main_modules = modules + [Glob(src + 'main.cpp'),
                          ]

test_modules = modules + [
    src+'test/test.cpp',
]

env.Append(LINKFLAGS='-rdynamic')

env.Program('./bin/ballistic', main_modules, LIBS=ALL_LIBS, LIBPATH='.')

if 'test' in COMMAND_LINE_TARGETS:
    env.Program('./test/test', test_modules, LIBS=ALL_LIBS+TEST_LIBS, LIBPATH='.')


