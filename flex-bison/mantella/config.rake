PROJECT_ROOT  = File.expand_path(File.dirname(__FILE__))

# Application
APP_NAME = 'ducky'
APP_EXT  = '.exe'
APP_OUT  = "#{APP_NAME}#{APP_EXT}"

# GNU Flex Settings
FLEX_BIN  =  'flex'
FLEX_OPTS =  ''
FLEX_IN   =  'src/lexer/lexer.l'
FLEX_OUT  =  'src/lexer/lex.yy.c'

# GNU Bison Settings
BISON_BIN  = 'bison'
BISON_OPTS = '-d'
BISON_IN   = 'src/grammar/grammar.y'
BISON_OUT  = 'src/grammar/grammar.tab.c'

# Compiler Settings
COMPILER_BIN  = 'g++'
COMPILER_OPTS = '-c -Wall -Werror'

# Linker Settings
LINKER_BIN    = 'g++'
LINKER_OPTS   = ''

# Source Code Settings
SRC_FILES    = (FileList['src/**/*.c*'] + [ FLEX_OUT, BISON_OUT ]).uniq
INCLUDE_DIRS = FileList['src/**/']
DEFINES = [
	#'DEBUG_LEXER',
	#'DETECT_MEM_LEAKS',
	'PURE_PARSER'
]

# Generated Lists
OBJ_FILES    = SRC_FILES.collect{|src| "build/#{File.basename(src).ext('o')}" }
DEFINE_LIST  = DEFINES.collect{|define| "-D#{define}" }
INCLUDE_LIST = INCLUDE_DIRS.collect{|x| "-I#{x} "}

# Clean Task
CLEAN.include( 'build/*.o' )
CLEAN.include( FLEX_OUT )
CLEAN.include( BISON_OUT )
CLEAN.include( APP_OUT )

