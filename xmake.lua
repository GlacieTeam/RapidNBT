add_rules("mode.debug", "mode.release")

add_repositories("groupmountain-repo https://github.com/GroupMountain/xmake-repo.git")

add_requires(
    "nbt 2.3.2",
    "pybind11 3.0.1",
    "magic_enum 0.9.7"
)

if is_plat("windows") and not has_config("vs_runtime") then
    set_runtimes("MD")
end

target("_NBT")
    set_languages("c++23")
    set_kind("shared")
    set_targetdir("./build/bin")
    set_prefixname("")
    set_extension("")
    add_packages(
        "pybind11",
        "nbt",
        "magic_enum"
    )
    add_includedirs("bindings")
    add_files("bindings/**.cpp")
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
            "/Ob3"
        )
    else
        add_cxflags(
            "-Wall",
            "-pedantic",
            "-fexceptions",
            "-fPIC",
            "-O3",
            "-fvisibility=hidden",
            "-fvisibility-inlines-hidden"
        )
        add_shflags(
            "-static-libstdc++",
            "-static-libgcc"
        )
    end