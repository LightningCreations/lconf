--
-- Created by IntelliJ IDEA.
-- User: chorm
-- Date: 2020-06-07
-- Time: 10:10 a.m.
-- To change this template use File | Settings | File Templates.
--

local c_standards = {"89", "95","99","11","18",["2x"]={"2x","23"}};

local lang = {};

-- Find the C Compiler
-- For now, assume the C Compiler accepts gnu style options
function lang.findCompiler()
    if toolchains.default:haveCompiler"C" then
       return toolchains.default:getCompiler"C"
    end
    local found,CC = lconf.find_program{os.getenv"CC"}
    if not found then
        found,CC = lconf.find_program{"cc", "gcc", "clang"}
        if not found then
            return error"Could not find C Compiler for the system, make sure cc is on the PATH or specify it explicitly with CC=<c compiler name>"
        end
    end
    local cc = toolchains.newCompiler"C";
    cc.command = CC;
    local compile,path = lconf.tempf();
    compile:write("int main(){}")
    compile:close();
    cc.supportedStandards = {};
    for k,v in pairs(c_standards) do
       if type(v)=="string" then
           -- Don't care about the key, just test the value
           if lconf:run_command{
               CC, "-std=c"..v, path
           } then
              cc.supportedStandards[v] = v;
           end
       elseif type(v)=="table" then
           for _,v in ipairs(v) do
               if lconf:run_command{
                   CC, "-std=c"..v, path
               } then
                   cc.supportedStandards[k] = v;
               end
           end
       end
    end
end

function testCompilerRun() end

function writeCompileRule(generator,compiler,opts)
    local compilecmd = {compiler:cmd()};

end

function writeLinkRule(generator, linker, opts)
    local linkcmd = {linker:cmd()};

end

