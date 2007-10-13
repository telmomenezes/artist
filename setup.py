#!/usr/bin/python

from distutils.core import setup, Extension
import sipdistutils
import os

moduleName = 'pycasso'
moduleVersion = '0.3'
moduleDescription = 'Cross-platform graphics library with hardware acceleration support'
moduleAuthor = 'Telmo Menezes'
moduleAuthorEmail = 'telmo@telmomenezes.com'
moduleURL = 'http://www.telmomenezes.com/pycasso'
modulePythonName = 'pyc'
sourceFiles = ['sip/pyc.sip', 'src/Pycasso.cpp', 'src/Window.cpp', 'src/Layer.cpp', 'src/Layer2D.cpp', 'src/Font.cpp', 'src/EventQ.cpp', 'src/Layer2DOpenGL.cpp', 'src/WindowSDLOpenGL.cpp', 'src/EventQSDL.cpp', 'src/FontOpenGL.cpp']
macros = [('__PYCASSO_SYSTEM_SDLOPENGL', None)] 

libs = []
includeDirs = []

if os.name == 'nt':
    libs = ['SDL', 'opengl32', 'glu32', 'png', 'freetype']
    includeDirs =['include', 'src']
else:
    libs = ['SDL', 'GL', 'GLU', 'png', 'freetype']
    includeDirs =['include', 'src', '/usr/include/SDL', '/usr/include/freetype2']


setup(name=moduleName,
      version=moduleVersion,
      description=moduleDescription,
      author=moduleAuthor,
      author_email=moduleAuthorEmail,
      url=moduleURL,
      ext_modules=[Extension(modulePythonName, sourceFiles,
                      include_dirs=includeDirs,
                      libraries=libs,
		      define_macros=macros
      )],
      cmdclass = {'build_ext': sipdistutils.build_ext}
)
