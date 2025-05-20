## Metadata
project('siri-cpp-tools', 'cpp',
  version : '0.1',
  default_options : ['default_library=shared', 'warning_level=3'])

## Library
# Note: All of the headers in `include` should be public.
include = include_directories('include')

lib = library('siricxx', 'src/lib.cpp', include_directories: include)

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
