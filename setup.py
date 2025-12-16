# Copyright © 2025 GlacieTeam. All rights reserved.
#
# This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
# distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
#
# SPDX-License-Identifier: MPL-2.0

import os
import sys
import struct
import platform
import sysconfig
import shutil
import subprocess
from setuptools import Distribution, setup
from setuptools.command.build_ext import build_ext
from setuptools.command.build_py import build_py

PACKAGE_NAME = "rapidnbt"
EXTENSION_FILENAME = "_NBT"


class XMakeBuild(build_ext):
    def _clean(self) -> None:
        for root, _, files in os.walk(f"./{PACKAGE_NAME}"):
            for file_name in files:
                file_path = os.path.join(root, file_name)
                if file_path.endswith((".so", ".pyd")):
                    os.remove(file_path)

    def _copy_binary(self) -> None:
        shutil.copy(
            f"./build/bin/{EXTENSION_FILENAME}",
            os.path.join(
                f"./{PACKAGE_NAME}", self.get_ext_filename(EXTENSION_FILENAME)
            ),
        )

    def get_arch(self) -> str:
        if sys.platform == "darwin":
            return "arm64"

        machine = platform.machine().lower()
        is_32bit = struct.calcsize("P") == 4
        is_arm = ("arm" in machine) or ("aarch" in machine)
        arch = ""
        if is_arm:
            arch = "arm" if is_32bit else "arm64"
        else:
            if sys.platform == "win32":
                arch = "x86" if is_32bit else "x64"
            else:
                arch = "x86" if is_32bit else "x86_64"
        return arch

    def run(self) -> None:
        self._clean()
        includedir = sysconfig.get_path("include")
        if sys.platform == "win32":
            linkdir = f"{sysconfig.get_config_var('installed_base')}\\libs"
        else:
            linkdir = sysconfig.get_config_var("LIBDIR")
        subprocess.run(
            [
                "xmake",
                "f",
                "--mode=release",
                f"--pyincludedir={includedir}",
                f"--pylinkdir={linkdir}",
                f"--pyinfo={sys.version}",
                f"--arch={self.get_arch()}",
                "-y",
                "--root",
            ],
            check=True,
        )
        subprocess.run(["xmake", "--all", "-y", "--root"], check=True)
        self._copy_binary()


class XmakeDistribution(Distribution):
    def has_ext_modules(self):
        return True


class XmakeCommand(build_py):
    def run(self):
        self.run_command("build_ext")
        super().run()


setup(
    cmdclass={
        "build_ext": XMakeBuild,
        "build_py": XmakeCommand,
    },
    distclass=XmakeDistribution,
)
