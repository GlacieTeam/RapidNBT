// Copyright © 2025 GlacieTeam.All rights reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
//
// SPDX-License-Identifier: MPL-2.0

#include "NativeModule.hpp"

namespace rapidnbt {

void bindNbtFile(py::module& m) {
    auto sm = m.def_submodule("nbt_file", "NBT file\nUse nbtio.open() to open a NBT file.");

    py::class_<nbt::NbtFile, nbt::CompoundTag>(sm, "NbtFile")
        .def_readonly("file_path", &nbt::NbtFile::mFilePath, "File path")
        .def_readwrite("snbt_format", &nbt::NbtFile::mSnbtFormat, "File Snbt format")
        .def_readwrite("snbt_indent", &nbt::NbtFile::mSnbtIndent, "File Snbt indent")
        .def_readwrite("file_format", &nbt::NbtFile::mFileFormat, "Binary file format")
        .def_readwrite("is_snbt", &nbt::NbtFile::mIsSnbtFile, "File is Snbt File")
        .def_readwrite("compression_type", &nbt::NbtFile::mCompressionType, "File compression type")
        .def_readwrite("compression_level", &nbt::NbtFile::mCompressionLevel, "File compression level")

        .def(
            "flush",
            [](nbt::NbtFile const& self) {
                if (self.mAutoSave) { self.save(); }
                throw py::attribute_error("NbtFile is read only.");
            },
            "flush data to the file."
        )

        .def(
            "__str__",
            [](nbt::NbtFile const& self) {
                return std::format("NbtFile at {}", std::filesystem::absolute(self.mFilePath).string());
            },
            "String representation"
        )
        .def(
            "__repr__",
            [](nbt::NbtFile const& self) {
                return std::format(
                    "<rapidnbt.NbtFile(size={0}) object at 0x{1:0{2}X}>",
                    self.size(),
                    reinterpret_cast<uintptr_t>(&self),
                    ADDRESS_LENGTH
                );
            },
            "Official string representation"
        )

        .def(
            "__enter__",
            [](nbt::NbtFile& self) -> nbt::NbtFile& { return self; },
            py::return_value_policy::reference,
            "Enter context manager"
        )
        .def(
            "__exit__",
            [](nbt::NbtFile& self, py::object, py::object, py::object) {
                if (self.mAutoSave) { self.save(); }
            },
            py::arg("exc_type"),
            py::arg("exc_value"),
            py::arg("traceback"),
            "Exit context manager"
        );
}

} // namespace rapidnbt