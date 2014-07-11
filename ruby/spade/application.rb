require 'rake'
include Rake::DSL

module Spade
    class Application
        # Attributes
        attr_reader :files

        def initialize(name,&block)
            # Setup the defaults
            @name = name
            @build_dir = '.'
            @toolchain = nil
            @files = []

            # Execute the DSL
            self.instance_eval(&block)

            # Validate the toolchain or pick one to use
            @toolchain = Spade.find_valid_toolchain( @toolchain )
        end

        def build_dir(dir)
            @build_dir = dir
        end

        def toolchain(tc)
            @toolchain = tc
        end

        def get_toolchain()
            @toolchain
        end

        def source(sflst)
            if sflst.class == Array then
                sflst.map! {|pat| FileList[pat] }
            else
                sflst = FileList[sflst]
            end
            @files.push( sflst.uniq ).flatten!
        end

        def exclude(sflst)
            if sflst.class == Array then
                sflst.map! {|pat| FileList[pat] }.flatten!
            else
                sflst = FileList[sflst]
            end
            sflst.each {|file| @files.delete(file) }
        end

        def output_file()
            File.join(@build_dir,'out.exe')
        end

        # Method to create all of the necessary rake tasks to build the project
        def generate()
            objects = []

            # generate object file tasks
            files.each do |fname|
                output_file = File.join(@build_dir, File.basename(fname).ext('o'))
                objects.push output_file
                file output_file => [ fname ] do
                    get_toolchain().compile( fname, output_file )
                end
            end

            # Link object files
            file output_file() => objects do
                get_toolchain().link( objects, output_file() )
            end

            # Create top level task
            desc "Build the #{@name} application"
            task @name => [ output_file() ]
        end
    end
end

