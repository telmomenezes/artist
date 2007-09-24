#!/usr/bin/python

from distutils.core import setup, Extension
import sipdistutils

setup(name='pycasso',
      version='0.2',
      description='Cross-platform 2D graphics library with hardware acceleration support',
      author='Telmo Menezes',
      author_email='telmo@telmomenezes.com',
      url='http://www.telmomenezes.com/pycasso',
      ext_modules=[Extension('pyc', ['sip/pyc.sip', 'src/Pycasso.cpp', 'src/Window.cpp', 'src/Layer.cpp', 'src/Font.cpp', 'src/EventQ.cpp', 'src/LayerOpenGL.cpp', 'src/WindowSDLOpenGL.cpp', 'src/EventQSDL.cpp', 'src/FontOpenGL.cpp'],
                include_dirs=['include', 'src', '/usr/include/SDL', '/usr/include/freetype2'],
                libraries=['SDL', 'GL', 'GLU', 'png', 'freetype'],
		define_macros=[('__PYCASSO_SYSTEM_SDLOPENGL', None)]
        )],
      cmdclass = {'build_ext': sipdistutils.build_ext}
      )
