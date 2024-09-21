project('microbloq', 'cpp',
  version : '0.1',
  default_options : ['warning_level=3', 'cpp_std=c++20'])

json = dependency('nlohmann_json')
lager = dependency('Lager')
immer = dependency('Immer')

qt6 = import('qt6')
qt6_dep = dependency('qt6', modules: ['Core', 'Gui', 'Widgets'])

src = []
ui = []
moc_headers = []

subdir('src')

# inc = include_directories('includes')
src += qt6.compile_ui(sources : ui)
src += qt6.compile_moc(headers : moc_headers,
                       extra_args: ['-DMAKES_MY_MOC_HEADER_COMPILE'],
#                      include_directories: inc,
                       dependencies: qt6_dep)


#translations = qt6.compile_translations(ts_files : 'myTranslation_fr.ts', build_by_default : true)


executable('microbloq', src, dependencies : [json, lager, immer, qt6_dep], include_directories : 'src')
#moc_files,
#           include_directories: inc,
#            dependencies : qt6_dep)
