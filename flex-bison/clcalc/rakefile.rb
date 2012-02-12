require 'rake'

PROJECT_ROOT  = File.expand_path(File.dirname(__FILE__))

APP_NAME = 'mark1'
APP_EXT  = '.exe'
APP_OUT  = "#{APP_NAME}#{APP_EXT}"

FLEX_BIN  =  'flex'
FLEX_OPTS =  '--header-file=src/control/parse/lexer/lex.yy.h'
FLEX_IN   =  'src/control/parse/lexer/lexer.l'
FLEX_OUT  =  'src/control/parse/lexer/lex.yy.c'

BISON_BIN  = 'bison'
BISON_OPTS = '-d'
BISON_IN   = 'src/control/parse/grammar/grammar.y'
BISON_OUT  = 'src/control/parse/grammar/grammar.tab.c'

COMPILER_BIN  = 'gcc'
COMPILER_OPTS = '-c -Wall -Werror'

LINKER_BIN    = 'gcc'
LINKER_OPTS   = ''

SRC_FILES    = (FileList[
	'src/**/*.c',
	'modules/data-structures/src/**/*.c',
	'modules/common-includes/src/**/*.c'
] + [ BISON_OUT, FLEX_OUT ]).uniq
INCLUDE_DIRS = FileList[
	'src/**/',
	'modules/data-structures/src/**',
	'modules/common-includes/src/**'
]
OBJ_FILES    = SRC_FILES.collect{|src| "build/#{File.basename(src).ext('o')}" }

#------------------------------------------------------------------------------

load 'tools/ceedling/lib/rakefile.rb'

def FindSourceByObj(obj)
	puts obj
	return SRC_FILES.find { |s| File.basename(s, '.c') == File.basename(obj, '.o') }
end

task :default => [:clobber, 'build:all']

namespace :build do
	includes = INCLUDE_DIRS.collect{|x| "-I#{x} "} 

	desc "Run all tasks in the 'build' namespace"
	task :all => [ :generated, :test, :bin, :docs]

	desc "Run all unit tests"
	task :test => [ :generated, 'test:all' ]

	desc "Generate all auto-generated source files"
	task :generated => [ BISON_IN, FLEX_IN ] do
		sh "#{BISON_BIN} #{BISON_OPTS} -o#{BISON_OUT} #{BISON_IN}"
		sh "#{FLEX_BIN} #{FLEX_OPTS} -o#{FLEX_OUT} #{FLEX_IN}"
	end
	
	desc "Link object files to build application"
	task :bin => [:generated, APP_OUT]
	task APP_OUT => OBJ_FILES do
		puts "Linking #{APP_OUT}..."
		sh "#{LINKER_BIN} #{LINKER_OPTS} #{includes} -o #{APP_NAME} #{OBJ_FILES.collect{|x| x + ' '}}"
	end

	rule '.o' => lambda{|obj| FindSourceByObj(obj) } do |t|
		sh "#{COMPILER_BIN} #{COMPILER_OPTS} #{includes} -o #{t.name} #{t.source}"
	end
	
	desc "Generate doxygen documentation"
	task :docs => [:generated] do
		sh 'doxygen'
	end
end

# Clean Task
CLEAN.include( BISON_OUT )
CLEAN.include( BISON_OUT.ext('h') )
CLEAN.include( FLEX_OUT )
CLEAN.include( FLEX_OUT.ext('h') )
CLEAN.include( 'build/*.o' )
CLEAN.include( APP_OUT )

