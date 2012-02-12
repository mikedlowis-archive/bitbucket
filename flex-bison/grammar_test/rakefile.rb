require 'rake'
require 'rake/clean'


# Application
APP_NAME = 'grammar'
APP_EXT  = '.exe'
APP_OUT  = "#{APP_NAME}#{APP_EXT}"

# GNU Flex Settings
FLEX_BIN  =  'flex'
FLEX_OPTS =  ''
FLEX_IN   =  'src/lexer.l'
FLEX_OUT  =  'src/lex.yy.c'

# GNU Bison Settings
BISON_BIN  = 'bison'
BISON_OPTS = '-d'
BISON_IN   = 'src/grammar.y'
BISON_OUT  = 'src/grammar.tab.c'

# Compiler Settings
COMPILER_BIN  = 'g++'
COMPILER_OPTS = '-c -Wall'

# Linker Settings
LINKER_BIN    = 'g++'
LINKER_OPTS   = ''

# Source Code Settings
SRC_FILES    = [FLEX_OUT,BISON_OUT, 'src/ast.cpp'] 
INCLUDE_DIRS = FileList['src/**/']
DEFINES = []

# Generated Options
OBJ_FILES    = SRC_FILES.collect{|src| "build/#{File.basename(src).ext('o')}" }
DEFINE_LIST  = DEFINES.collect{|define| "-D#{define}" }
INCLUDE_LIST = INCLUDE_DIRS.collect{|x| "-I#{x} "}

# Clean Task
CLEAN.include( 'build/*.o' )
CLEAN.include( 'src/grammar.tab.c' )
CLEAN.include( 'src/grammar.tab.h' )
CLEAN.include( 'src/lex.yy.c' )
CLEAN.include( 'src/lex.yy.h' )
CLEAN.include( APP_OUT )

#------------------------------------------------------------------------------

task :default => [:release]
task :release => [:generated, APP_OUT]
task :generated => [FLEX_OUT,BISON_OUT]

# Generate Lexer
file FLEX_OUT => [FLEX_IN] do
	sh "#{FLEX_BIN} #{FLEX_OPTS} -o#{FLEX_OUT} #{FLEX_IN}"
end

# Generate Parser
file BISON_OUT => [BISON_IN] do
	sh "#{BISON_BIN} #{BISON_OPTS} -o#{BISON_OUT} #{BISON_IN}"
end

# Find and compile all source files
def FindSourceByObj(obj)
	return SRC_FILES.find { |s| 
		(File.basename(s, '.c') == File.basename(obj, '.o')) ||
		(File.basename(s, '.cpp') == File.basename(obj, '.o'))
	}
end
rule '.o' => lambda{|obj| FindSourceByObj(obj) } do |t|
	sh "#{COMPILER_BIN} #{COMPILER_OPTS} #{INCLUDE_LIST} #{DEFINE_LIST} -o #{t.name} #{t.source}"
end

# Link the object files together
task APP_OUT => OBJ_FILES do
	puts "Linking #{APP_OUT}..."
	sh "#{LINKER_BIN} #{LINKER_OPTS} -o #{APP_NAME} #{OBJ_FILES.collect{|x| x + ' '}}"
end
