HERE = File.expand_path(File.dirname(__FILE__)) + '/'

require 'rake'
require 'rake/clean'
require 'rake/testtask'
require './tools/cmock/rakefile_helper'

include RakefileHelpers

# Load default configuration, for now
DEFAULT_CONFIG_FILE = 'tools/cmock/cmock.yml'
configure_toolchain(DEFAULT_CONFIG_FILE)

desc "Run unit tests"
task :unit do
  run_tests(get_unit_test_files)
end

desc "Generate test summary"
task :summary do
  report_summary
end

desc "Build and test Unity"
task :all => [:clean, :unit, :summary]
task :default => [:clobber, :all]

desc "Load configuration"
task :config, :config_file do |t, args|
  configure_toolchain(args[:config_file])
end
