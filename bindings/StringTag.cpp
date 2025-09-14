// Copyright © 2025 GlacieTeam.All rights reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
//
// SPDX-License-Identifier: MPL-2.0

#include "NativeModule.hpp"

namespace rapidnbt {

void bindStringTag(py::module& m) {
    auto sm = m.def_submodule("string_tag");

    py::class_<nbt::StringTag, nbt::Tag>(sm, "StringTag")
        .def(py::init<>(), "Construct an empty StringTag")
        .def(py::init<std::string>(), py::arg("str"), "Construct from a Python string")

        .def("get_type", &nbt::StringTag::getType, "Get the NBT type ID (String)")
        .def(
            "equals",
            &nbt::StringTag::equals,
            py::arg("other"),
            "Check if this tag equals another tag (same content and type)"
        )
        .def("copy", &nbt::StringTag::copy, "Create a deep copy of this tag")
        .def("hash", &nbt::StringTag::hash, "Compute hash value of this tag (based on string content)")

        .def(
            "write",
            [](nbt::StringTag& self, bstream::BinaryStream& stream) { self.write(stream); },
            py::arg("stream"),
            "Write tag to a binary stream (UTF-8 encoded)"
        )
        .def(
            "load",
            [](nbt::StringTag& self, bstream::ReadOnlyBinaryStream& stream) { self.load(stream); },
            py::arg("stream"),
            "Load tag value from a binary stream (UTF-8)"
        )

        .def_property(
            "value",
            [](nbt::StringTag& self) -> std::string { return self.storage(); },
            [](nbt::StringTag& self, std::string value) { self.storage() = std::move(value); },
            "Access the string content of this tag"
        )

        .def(
            "size",
            [](nbt::StringTag const& self) { return self.storage().size(); },
            "Get the length of the string in bytes"
        )

        .def(
            "__len__",
            [](nbt::StringTag const& self) { return self.storage().size(); },
            "Get the length of the string in bytes"
        )
        .def(
            "__getitem__",
            [](nbt::StringTag const& self, size_t index) -> char {
                if (index >= self.storage().size()) { throw py::index_error("Index out of range"); }
                return self.storage()[index];
            },
            py::arg("index"),
            "Get character at specified position"
        )
        .def(
            "__eq__",
            [](nbt::StringTag const& self, const nbt::StringTag& other) { return self.equals(other); },
            py::arg("other"),
            "Equality operator (==), case-sensitive comparison"
        )
        .def("__hash__", &nbt::StringTag::hash, "Compute hash value for Python hashing operations")
        .def(
            "__str__",
            [](nbt::StringTag const& self) { return self.toSnbt(nbt::SnbtFormat::Minimize); },
            "String representation (SNBT minimized format)"
        )
        .def(
            "__repr__",
            [](nbt::StringTag const& self) {
                return std::format(
                    "<rapidnbt.StringTag({0}) object at 0x{1:0{2}X}>",
                    self.storage(),
                    reinterpret_cast<uintptr_t>(&self),
                    ADDRESS_LENGTH
                );
            },
            "Official representation with quoted content"
        );
}

} // namespace rapidnbt