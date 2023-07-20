project('emm', 'cpp',
  version : '0.1',
  default_options : ['warning_level=3','cpp_std=c++20'])

exe = executable('emm', 
                 'main.cpp',
                 'MaterialManager.hpp',
                 'MaterialManager.cpp',
                 'Machine.hpp',
                 'Machine.cpp',
                 'StorageFile.cpp',
                 'StorageFile.hpp',
                 'Component.cpp',
                 'Component.hpp',
                 'ControlPanel.cpp',
                 'ControlPanel.hpp',
                 install : true)

test('basic', exe)
