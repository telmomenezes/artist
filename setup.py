from distutils.core import setup, Extension

setup(name='pycasso',
      version='0.1',
      description='Cross-platform 2D graphics library with hardware acceleration support',
      author='Telmo Menezes',
      author_email='telmo@telmomenezes.com',
      url='http://www.telmomenezes.com/pycasso',
      ext_modules=[Extension('_pycasso', ['pycasso.i', 'src/Session.cpp', 'src/Stage.cpp', 'src/StageObject.cpp', 'src/Object2D.cpp', 'src/Object3D.cpp', 'src/Shape3D.cpp', 'src/PhysicalObject.cpp', 'src/Light.cpp', 'src/EventHandler.cpp', 'src/Mouse.cpp', 'src/Keyboard.cpp', 'src/functions.cpp', 'src/PycassoError.cpp'],
                swig_opts=['-c++'],
                include_dirs=['src', '/usr/include/irrlicht'],
                libraries=['Irrlicht', 'ode', 'GL', 'GLU', 'Xxf86vm', 'Xext', 'X11']
        )],
      options={'build_ext':{'swig_opts':'-c++'}},
      py_modules=['pycasso']
      )
