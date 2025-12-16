add_rules("mode.debug", "mode.release")

add_repositories("groupmountain-repo https://github.com/GroupMountain/xmake-repo.git")

add_requires(
    "nbt 2.6.3",
    "pybind11-header 3.0.1",
    "magic_enum 0.9.7"
)

if is_plat("windows") and not has_config("vs_runtime") then
    set_runtimes("MD")
end

option("pyincludedir")
    set_default("unset")
    set_values({})
option_end()

option("pylinkdir")
    set_default("unset")
    set_values({})
option_end()

option("pyinfo")
    set_default("unset")
    set_values({})
option_end()

target("_NBT")
    set_languages("c++23")
    set_kind("shared")
    set_targetdir("./build/bin")
    set_prefixname("")
    set_extension("")
    add_packages(
        "pybind11-header",
        "nbt",
        "magic_enum"
    )
    add_includedirs("bindings")
    add_files("bindings/**.cpp")
    add_includedirs(get_config("pyincludedir"))
    add_linkdirs(get_config("pylinkdir"))
    if is_plat("windows") then
        add_defines(
            "NOMINMAX",
            "UNICODE"
        )
        add_cxflags(
            "/EHsc",
            "/utf-8",
            "/W4",
            "/O2",
            "/Ob3",
            "/GL"
        )
        add_shflags(
            "/LTCG"
        )
    else
        set_policy("build.optimization.lto", true)
        add_cxflags(
            "-Wall",
            "-pedantic",
            "-fexceptions",
            "-fPIC",
            "-O3",
            "-fvisibility=hidden",
            "-fvisibility-inlines-hidden",
            "-flto"
        )
        add_shflags(
            "-static-libstdc++",
            "-flto"
        )

        if is_plat("linux") then 
            add_shflags(
                "-static-libgcc",
                "-Wl,--exclude-libs,ALL"
            )
        end
        if is_plat("macosx") then
            add_mxflags(
                "-target arm64-apple-macos11.0", 
                "-mmacosx-version-min=11.0"
            )
            add_ldflags(
                "-target arm64-apple-macos11.0",
                "-mmacosx-version-min=11.0"
            )
            add_shflags(
                "-dynamiclib",
                "-target arm64-apple-macos11.0",
                "-mmacosx-version-min=11.0"
            )
        end
    end
    before_build(function (tagret) 
        cprint("${bright green}[Python]:${reset} version: " .. get_config("pyinfo"))
        cprint("${bright green}[Python]:${reset} include: " .. get_config("pyincludedir"))
        cprint("${bright green}[Python]:${reset} links: " .. get_config("pylinkdir"))
    end)