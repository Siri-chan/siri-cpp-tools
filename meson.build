## Metadata
project('siri-cpp-tools', 'cpp',
  version : '0.1',
  license: 'LGPL-3.0-or-later',
  default_options : [
    'cpp_std=c++23',
    'default_library=shared', 
    'warning_level=3'
  ]
)

## Library
# Note: All of the headers in `include` should be public.
include = include_directories('include')

lib = library('siricxx', 'src/lib.cpp', 'src/assert.cpp', include_directories: include, install: true)
install_subdir('include', install_dir : '')

## Pkg Config
pkg_config = import('pkgconfig')
pkg_config.generate(lib, 
  name: 'libsiricxx', 
  description: 'An eclectic collection of useful C++ functions and data structures.', 
  subdirs: ['.'],
  url: 'https://github.com/Siri-chan/siri-cpp-tools',
  # TODO: Meson 1.9 will support this, but it isnt stable yet.
  #license: meson.project_license(),
)

dep_siricxx = declare_dependency(link_with: lib, include_directories: include)

## Tests
test_sanity = executable('test_sanity', 
              'src/tests/sanity_check.cpp', 
              dependencies: dep_siricxx)

test('sanity_check', test_sanity)

test_recalclazy = executable('test_recalc_lazy',
                            'src/tests/recalculate_lazy.cpp',
                            dependencies: dep_siricxx)

test('recalculate_lazy', test_recalclazy)

test_assert = executable('test_assert', 'src/tests/asserts/assert.cpp',
                          dependencies: dep_siricxx)
test('assert_fail', test_assert, args: ['0'], should_fail: true)
test('assert_success', test_assert, args: ['1'])

test_abort_assert = executable('test_abort_assert', 'src/tests/asserts/abort_assert.cpp',
                          dependencies: dep_siricxx)
test('abort_assert_fail', test_abort_assert, args: ['0'], should_fail: true)
test('abort_assert_success', test_abort_assert, args: ['1'])
