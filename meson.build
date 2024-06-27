project('microbloq', 'cpp',
  version : '0.1',
  default_options : ['warning_level=3', 'cpp_std=c++20'])

# qt6 = import('qt6')
# qt6_dep = dependency('qt6', modules: ['Core', 'Gui'])

# inc = include_directories('includes')

#moc_files = qt6.compile_moc(headers : 'myclass.h',
#                            extra_arguments: ['-DMAKES_MY_MOC_HEADER_COMPILE'],
#                            include_directories: inc,
#                            dependencies: qt6_dep)

#translations = qt6.compile_translations(ts_files : 'myTranslation_fr.ts', build_by_default : true)

json = dependency('nlohmann_json')
lager = dependency('Lager')
immer = dependency('Immer')

src = []

subdir('src')

executable('microbloq', src, dependencies : [json, lager, immer], include_directories : 'src')
#moc_files,
#           include_directories: inc,
#            dependencies : qt6_dep)
