// Copyright © 2025 GlacieTeam.All rights reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
//
// SPDX-License-Identifier: MPL-2.0

#include "NativeModule.hpp"

namespace rapidnbt {

void bindNbtFile(py::module& m) {
    auto sm = m.def_submodule("nbt_file");

    py::class_<nbt::NbtFile>(sm, "NbtFile")
        .def(
            "__getitem__",
            [](nbt::NbtFile& self, std::string_view key) -> nbt::CompoundTagVariant& { return self[key]; },
            py::return_value_policy::reference_internal,
            py::arg("key"),
            "Get value by key (no exception, auto create if not found)"
        )
        .def(
            "__setitem__",
            [](nbt::NbtFile& self, std::string_view key, py::object value) {
                if (py::isinstance<nbt::CompoundTagVariant>(value)) {
                    self[key] = *value.cast<nbt::CompoundTagVariant*>();
                } else if (py::isinstance<nbt::Tag>(value)) {
                    self[key] = *value.cast<nbt::Tag*>();
                } else {
                    self[key] = makeNativeTag(value);
                }
            },
            py::arg("key"),
            py::arg("value"),
            "Set value by key"
        )

        .def(
            "keys",
            [](nbt::NbtFile& self) {
                py::list keys;
                for (auto& [key, _] : self) { keys.append(key); }
                return keys;
            },
            "Get list of all keys in the compound"
        )
        .def(
            "values",
            [](nbt::NbtFile& self) {
                py::list values;
                for (auto& [_, value] : self) { values.append(py::cast(value)); }
                return values;
            },
            "Get list of all values in the compound"
        )
        .def(
            "items",
            [](nbt::NbtFile& self) {
                py::list items;
                for (auto& [key, value] : self) { items.append(py::make_tuple(key, py::cast(value))); }
                return items;
            },
            "Get list of (key, value) pairs in the compound"
        )

        .def(
            "merge",
            &nbt::NbtFile::merge,
            py::arg("other"),
            py::arg("merge_list") = false,
            "Merge another CompoundTag into this one",
            "",
            "Arguments:",
            "    other: CompoundTag to merge from",
            "    merge_list: If true, merge list contents instead of replacing"
        )
        .def("empty", &nbt::NbtFile::empty, "Check if the compound is empty")
        .def("clear", &nbt::NbtFile::clear, "Remove all elements from the compound")
        .def("rename", &nbt::NbtFile::rename, py::arg("old_key"), py::arg("new_key"), "Rename a key in the compound")

        .def(
            "contains",
            [](nbt::NbtFile const& self, std::string_view key) { return self.contains(key); },
            py::arg("key"),
            "Check if key exists"
        )
        .def(
            "get",
            [](nbt::NbtFile& self, std::string_view key) -> nbt::CompoundTagVariant& {
                if (!self.contains(key)) { throw py::index_error("tag not exist"); }
                return self.at(key);
            },
            py::return_value_policy::reference_internal,
            py::arg("key"),
            "Get tag by key\nThrow IndexError if not found"
        )
        .def(
            "put",
            [](nbt::NbtFile& self, std::string key, py::object value) {
                if (py::isinstance<nbt::CompoundTagVariant>(value)) {
                    if (!self.contains(key)) { self[key] = *value.cast<nbt::CompoundTagVariant*>(); }
                } else if (py::isinstance<nbt::Tag>(value)) {
                    self[key] = value.cast<nbt::Tag*>()->copy();
                } else {
                    self[key] = makeNativeTag(value);
                }
            },
            py::arg("key"),
            py::arg("value"),
            "Put a value into the compound (automatically converted to appropriate tag type)"
        )
        .def(
            "set",
            [](nbt::NbtFile& self, std::string key, py::object value) {
                if (py::isinstance<nbt::CompoundTagVariant>(value)) {
                    self[key] = *value.cast<nbt::CompoundTagVariant*>();
                } else if (py::isinstance<nbt::Tag>(value)) {
                    self[key] = *value.cast<nbt::Tag*>()->copy();
                } else {
                    self[key] = makeNativeTag(value);
                }
            },
            py::arg("key"),
            py::arg("value"),
            "Set value in the compound (automatically converted to appropriate tag type)"
        )

        .def(
            "to_dict",
            [](nbt::NbtFile const& self) {
                py::dict result;
                for (auto& [key, value] : self) { result[py::str(key)] = py::cast(value); }
                return result;
            },
            "Convert CompoundTag to a Python dictionary"
        )

        .def(
            "to_network_nbt",
            [](nbt::NbtFile const& self) { return to_pybytes(self.toNetworkNbt()); },
            "Serialize to Network NBT format (used in Minecraft networking)"
        )
        .def(
            "to_binary_nbt",
            [](nbt::NbtFile const& self, bool little_endian, bool header) {
                if (header) {
                    return to_pybytes(self.toBinaryNbtWithHeader(little_endian));
                } else {
                    return to_pybytes(self.toBinaryNbt(little_endian));
                }
            },
            py::arg("little_endian") = true,
            py::arg("header")        = false,
            "Serialize to binary NBT format"
        )
        .def("pop", &nbt::NbtFile::remove, py::arg("key"), "Remove key from the compound")

        .def(
            "__contains__",
            [](nbt::NbtFile const& self, std::string_view key) { return self.contains(key); },
            py::arg("key"),
            "Check if key exists in the compound"
        )
        .def("__delitem__", &nbt::NbtFile::remove, py::arg("key"), "Remove key from the compound")
        .def("__len__", &nbt::NbtFile::size, "Get number of key-value pairs")
        .def(
            "__iter__",
            [](nbt::NbtFile& self) { return py::make_key_iterator(self.begin(), self.end()); },
            py::keep_alive<0, 1>(),
            "Iterate over keys in the compound"
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

        .def_readwrite("snbt_format", &nbt::NbtFile::mSnbtFormat, "File Snbt format")
        .def_readwrite("snbt_indent", &nbt::NbtFile::mSnbtIndent, "File Snbt indent")
        .def_readwrite("file_format", &nbt::NbtFile::mFileFormat, "Binary file format")
        .def_readwrite("is_snbt", &nbt::NbtFile::mIsSnbtFile, "File is Snbt File")
        .def_readwrite("compression_type", &nbt::NbtFile::mCompressionType, "File compression type")
        .def_readwrite("compression_level", &nbt::NbtFile::mCompressionLevel, "File compression level")
        .def_readwrite("file_data", &nbt::NbtFile::mFileData, "File NBT data")
        .def_readonly("file_path", &nbt::NbtFile::mFilePath, "File path")

        .def_property(
            "value",
            [](nbt::NbtFile& self) -> py::dict {
                py::dict result;
                for (auto& [key, value] : self) { result[py::str(key)] = py::cast(value); }
                return result;
            },
            [](nbt::NbtFile& self, py::dict const& value) {
                self.clear();
                for (auto const& [k, v] : value) {
                    std::string key = py::cast<std::string>(k);
                    auto&       val = static_cast<py::object const&>(v);
                    if (py::isinstance<nbt::CompoundTagVariant>(val)) {
                        self[key] = *val.cast<nbt::CompoundTagVariant*>();
                    } else if (py::isinstance<nbt::Tag>(val)) {
                        self[key] = val.cast<nbt::Tag*>()->copy();
                    } else {
                        self[key] = makeNativeTag(val);
                    }
                }
            },
            "Access the dict value of this file"
        )

        .def(
            "__enter__",
            [](nbt::NbtFile& self) -> nbt::NbtFile& { return self; },
            py::return_value_policy::reference,
            "Enter context manager"
        )
        .def(
            "__exit__",
            [](nbt::NbtFile& self, py::object, py::object, py::object) { self.save(); },
            py::arg("exc_type"),
            py::arg("exc_value"),
            py::arg("traceback"),
            "Exit context manager"
        );
}

} // namespace rapidnbt