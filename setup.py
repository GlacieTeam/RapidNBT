import subprocess, os, shutil
from setuptools import setup, Distribution
from setuptools.command.build_ext import build_ext
from setuptools.command.build_py import build_py


class XMakeBuild(build_ext):
    def _clean(self):
        for root, _, files in os.walk("./rapidnbt"):
            for file_name in files:
                file_path = os.path.join(root, file_name)
                if file_path.endswith((".so", ".pyd")):
                    os.remove(file_path)

    def _copy_binary(self):
        shutil.copy(
            "./build/bin/_NBT",
            os.path.join("./rapidnbt", self.get_ext_filename("_NBT")),
        )

    def run(self):
        self._clean()
        subprocess.run(["xmake", "f", "--mode=release", "-y"], check=True)
        subprocess.run(["xmake", "--all", "-y"], check=True)
        self._copy_binary()


class BinaryDistribution(Distribution):
    def has_ext_modules(self):
        return True


class InstallCommand(build_py):
    def run(self):
        self.run_command("build_ext")
        super().run()


setup(
    name="rapidnbt",
    version="1.0.0",
    packages=["rapidnbt"],
    include_package_data=True,
    package_data={"rapidnbt": ["*.so", "*.pyd"]},
    cmdclass={
        "build_ext": XMakeBuild,
        "build_py": InstallCommand,
    },
    distclass=BinaryDistribution,
    zip_safe=False,
)
