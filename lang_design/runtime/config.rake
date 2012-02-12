PROJECT_ROOT  = File.expand_path(File.dirname(__FILE__))

# Application
APP_NAME = 'stdlib'
STATIC_APP_OUT  = "#{APP_NAME}.a"
SHARED_APP_OUT  = "#{APP_NAME}.so"

# Compiler Settings
COMPILER_BIN  = 'g++'
COMPILER_OPTS = '-c -Wall -Werror'

# Linker Settings
STATIC_LINKER_BIN    = 'ar'
STATIC_LINKER_OPTS   = 'rvs'
SHARED_LINKER_BIN    = 'g++'
SHARED_LINKER_OPTS   = '-shared -o'

# Source Code Settings
SRC_FILES    = FileList['src/**/*.c*']
INCLUDE_DIRS = FileList['src/**/']
DEFINES = [
	'DETECT_MEM_LEAKS'
]

# Generated Lists
OBJ_FILES    = SRC_FILES.collect{|src| "build/#{File.basename(src).ext('o')}" }
DEFINE_LIST  = DEFINES.collect{|define| "-D#{define}" }
INCLUDE_LIST = INCLUDE_DIRS.collect{|x| "-I#{x} "}

# Clean Task
CLEAN.include( 'build/*.o' )
CLEAN.include( STATIC_APP_OUT )
CLEAN.include( SHARED_APP_OUT )

