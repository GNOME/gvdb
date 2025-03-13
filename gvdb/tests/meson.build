# SPDX-FileCopyrightText: 2024 Carlos Garnacho
# SPDX-License-Identifier: LGPL-2.1-or-later

gvdb_tests = {
  'gvdb': {},
}

if cc.get_id() != 'msvc'
  gvdb_tests += {'autoptr': {}}
endif

test_env = environment()
test_env.set('G_TEST_SRCDIR', meson.current_source_dir())
test_env.set('G_TEST_BUILDDIR', meson.current_build_dir())

test_deps = [
  dependency('glib-2.0', version: '>= 2.44'),
  dependency('gio-2.0'),
  gvdb_dep,
]
test_cargs = []
test_cpp_args = ['-UG_DISABLE_ASSERT']

foreach test_name, extra_args : gvdb_tests
  source = extra_args.get('source', test_name + '.c')

  exe = executable(test_name, source,
    c_args: test_cargs + extra_args.get('c_args', []),
    cpp_args: test_cpp_args + extra_args.get('cpp_args', []),
    dependencies: test_deps + extra_args.get('dependencies', []),
    link_args: extra_args.get('link_args', []),
    install: false,
  )

  test(test_name, exe,
    protocol: 'tap',
    env: test_env,
    suite: ['gvdb'],
  )
endforeach
