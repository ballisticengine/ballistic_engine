BULLET_LIBS = ['BulletCollision', 'BulletSoftBody', 'BulletDynamics', 'LinearMath' ]
BOOST_LIBS = ['boost_timer', 'boost_filesystem', 'boost_system', 'boost_thread', 'boost_python', ]
SDL_LIBS = ['SDL2', 'SDL2_ttf', 'SDL2_image', ]
GL_LIBS = ['GL', 'GLEW', ]
GENERAL_LIBS = ['stdc++', 'pthread', 'python2.7', 'ldl', ]

ALL_LIBS = GENERAL_LIBS + BOOST_LIBS + SDL_LIBS + GL_LIBS + BULLET_LIBS

env = Environment(CPPPATH=[
    '/usr/include/python2.7',
    '/usr/include/bullet',
    './hpp',
])



env.SharedLibrary('./bin/rendererGL', [
    'cpp/renderer/rendererAbstract.cpp',
    'cpp/renderer/GL/rendererGL.cpp',
    #'cpp/renderer/GL/*',
    ]
)