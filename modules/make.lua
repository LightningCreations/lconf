--
-- Created by IntelliJ IDEA.
-- User: chorm
-- Date: 2020-06-07
-- Time: 4:54 p.m.
-- To change this template use File | Settings | File Templates.
--

function writeTarget() end

function buildTarget(name,builddir)
    lconf.run_command{
        workingDir = builddir,
        command = {""}
    }
end
