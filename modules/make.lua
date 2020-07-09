--
-- Created by IntelliJ IDEA.
-- User: chorm
-- Date: 2020-06-07
-- Time: 4:54 p.m.
-- To change this template use File | Settings | File Templates.
--

local generator = {};

function generator.find()
    local makeopt = options.persist"make":get();
    if makeopt then
        return makeopt
    end

    local found,make = lconf.find_program{
        os.getenv"MAKE","make"
    }
    if not found then
        error"Could not find make program. Check to make sure its available on $PATH, or specify the $MAKE environment variable"
    end
    options.write_persist("make",make);
end

function generator.buildTarget(name,builddir,opts)
    local make = generator.find();
    lconf.run_command{
        workingDir = builddir,
        command = {""}
    }
end

generator.find();

return generator;