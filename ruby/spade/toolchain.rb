module Spade
    def command_exists?(cmd)
        true
    end

    class Toolchain
        def initialize(name,&block)
            # Setup defaults
            @name     = name
            @compiler = nil
            @linker   = nil
            @archiver = nil

            # Execute the DSL
            self.instance_eval(&block)
        end

        # DSL methods
        #---------------
        def compiler(cmd)
            @compiler = cmd
        end

        def linker(cmd)
            @linker = cmd
        end

        def archiver(cmd)
            @archiver = cmd
        end

        # Action methods
        #---------------
        def is_valid?
            Spade.command_exists? @compiler and
            Spade.command_exists? @linker and
            Spade.command_exists? @archiver
        end

        def compile(fin,fout,opts=[])
            sh [ @compiler, '-c', opts, fin, "-o #{fout}" ].flatten.join(" ")
        end

        def link(fin,fout,opts=[])
            sh [ @linker, opts, "-o #{fout}", fin ].flatten.join(" ")
        end

        def archive(fin,fout,opts=[])
            sh [ @archiver, opts, "-o #{fout}", fin ].flatten.join(" ")
        end
    end
end
