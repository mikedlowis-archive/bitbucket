require 'rake'
require 'rake/clean'

# Load the dependencies
load    'config.rake'

task :default => [:release]
task :release => [:generated, APP_OUT]

# Generate the lexer and parser
task :generated => [FLEX_OUT, BISON_OUT]
file FLEX_OUT => [FLEX_IN] do
	sh "#{FLEX_BIN} #{FLEX_OPTS} -o#{FLEX_OUT} #{FLEX_IN}"
end
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
