#!/usr/bin/python

from distutils.core import setup, Extension
import sipdistutils

setup(name='pycasso',
      version='0.2',
      description='Cross-platform 2D graphics library with hardware acceleration support',
      author='Telmo Menezes',
      author_email='telmo@telmomenezes.com',
      url='http://www.telmomenezes.com/pycasso',
      ext_modules=[Extension('pyc', ['sip/pyc.sip', 'src/Pycasso.cpp', 'src/Window.cpp', 'src/Layer.cpp', 'src/EventQ.cpp', 'src/PycassoException.cpp', 'src/LayerOpenGL.cpp', 'src/LayerSDLOpenGL.cpp', 'src/WindowSDLOpenGL.cpp', 'src/EventQSDL.cpp'],
                include_dirs=['include', 'src', '/usr/include/SDL'],
                libraries=['SDL', 'GL', 'GLU', 'png'],
		define_macros=[('__PYCASSO_SYSTEM_SDLOPENGL', None)]
        )],
      cmdclass = {'build_ext': sipdistutils.build_ext}
      )
