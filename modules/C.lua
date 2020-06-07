--
-- Created by IntelliJ IDEA.
-- User: chorm
-- Date: 2020-06-07
-- Time: 10:10 a.m.
-- To change this template use File | Settings | File Templates.
--

-- Find the C Compiler
function findcc()
    if toolchains.haveCompiler"C" then
       return toolchains.getCompiler"C"
    end
    local CC = os.getenv"CC" or options.getCompilerName"C";
    if not CC then
        local found;
         found,CC = findProgram{"cc", "gcc", "clang"}
        if not found then
            return error"Could not find C Compiler for the system, make sure cc is on the PATH or specify it explicitly with CC=<c compiler name>"
        end
        return CC
    end
end


function writeLinkRule(generator, linker, outputFile, inputFiles, linkOptions, rpath, libraries, libdirs, linkDependencies)
    local linkcmd = linker;
    return generator
        :linkRule(outputFile)
        :depends(inputFiles)
        :depends(linkDependencies)
        :runCommand()
end

