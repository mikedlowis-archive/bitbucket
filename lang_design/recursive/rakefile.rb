require 'rake'
require 'rake/clean'

# Load the dependencies
load    'config.rake'

task :default => [:release]
task :release => [APP_OUT]

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
