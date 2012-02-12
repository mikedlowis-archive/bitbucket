require 'rake'
require 'rake/clean'

# Load the dependencies
load    'config.rake'

task :default => [:release]
task :release => [STATIC_APP_OUT, SHARED_APP_OUT]

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
task STATIC_APP_OUT => OBJ_FILES do
	puts "Linking #{STATIC_APP_OUT}..."
	sh "#{STATIC_LINKER_BIN} #{STATIC_LINKER_OPTS} #{STATIC_APP_OUT} #{OBJ_FILES.collect{|x| x + ' '}}"
end

task SHARED_APP_OUT => OBJ_FILES do
	puts "Linking #{SHARED_APP_OUT}..."
	sh "#{SHARED_LINKER_BIN} #{SHARED_LINKER_OPTS} #{SHARED_APP_OUT} #{OBJ_FILES.collect{|x| x + ' '}}"
end

task :test => OBJ_FILES do
	puts "compiling test_main..."
	sh "#{COMPILER_BIN} #{COMPILER_OPTS} #{INCLUDE_LIST} #{DEFINE_LIST} -o build/test_main.o test/test_main.cpp"
	puts "Linking test_runner.exe..."
	sh "#{SHARED_LINKER_BIN} -o test_runner.exe #{OBJ_FILES.collect{|x| x + ' '}} build/test_main.o"
end
