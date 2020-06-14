--
-- Created by IntelliJ IDEA.
-- User: chorm
-- Date: 2020-06-07
-- Time: 3:43 p.m.
-- To change this template use File | Settings | File Templates.
--

local generators2cmake = {
    make = "Unix Makefiles",
    ninja = "Ninja",
    msvc = "Visual Studio"
}

local function split(str,at)
    local ret = {};

end

function configureDirectory(srcDir,binDir,opts)
    local cmd = {"cmake"}
    for k,v in pairs(opts) do
        cmd[#cmd] =  "-D"..k.."="..v;
    end
    cmd[#cmd] = "-G\""..options.generator:name().."\"";
    cmd[#cmd] = srcDir;
    lconf.run_command{
        workingDir = binDir,
        command = cmd
    }
end

function buildTarget() end


return lconf.configuration