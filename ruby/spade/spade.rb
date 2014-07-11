module Spade
    Toolchains = {}
    Artifacts = {}

    module DSL
        def toolchain(name,&block)
            Toolchains[name] = Toolchain.new(name, &block)
        end

        def application(name,&block)
            Artifacts[name] = Application.new(name, &block)
            Artifacts[name].generate()
        end

        def shared_lib(name,&block)
        end

        def static_lib(name,&block)
        end
    end

    def Spade.command_exists?(cmd)
        true
    end

    def Spade.find_valid_toolchain(name=nil)
        if not name.nil? then
            raise "No toolchain found for #{name}" if Spade::Toolchains[name].nil?
            return Spade::Toolchains[name]
        else
            Spade::Toolchains.each_pair {|name,tc|
                return tc if tc.is_valid?
            }
            raise "No valid toolchains were found in the registry"
        end
    end
end

require './spade/toolchain'
require './spade/application'

