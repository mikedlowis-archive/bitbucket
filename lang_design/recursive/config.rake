PROJECT_ROOT  = File.expand_path(File.dirname(__FILE__))

# Application
APP_NAME = 'parser'
APP_EXT  = '.exe'
APP_OUT  = "#{APP_NAME}#{APP_EXT}"

# Compiler Settings
COMPILER_BIN  = 'g++'
COMPILER_OPTS = '-c -Wall -Werror'

# Linker Settings
LINKER_BIN    = 'g++'
LINKER_OPTS   = ''

# Source Code Settings
SRC_FILES    = FileList['src/**/*.c*']
INCLUDE_DIRS = FileList['src/**/']
DEFINES = []

# Generated Lists
OBJ_FILES    = SRC_FILES.collect{|src| "build/#{File.basename(src).ext('o')}" }
DEFINE_LIST  = DEFINES.collect{|define| "-D#{define}" }
INCLUDE_LIST = INCLUDE_DIRS.collect{|x| "-I#{x} "}

# Clean Task
CLEAN.include( 'build/*.o' )
CLEAN.include( APP_OUT )

