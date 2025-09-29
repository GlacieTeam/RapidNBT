// Copyright © 2025 GlacieTeam.All rights reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
//
// SPDX-License-Identifier: MPL-2.0

#include "NativeModule.hpp"

namespace rapidnbt {

void bindIntTag(py::module& m) {
    auto sm = m.def_submodule("int_tag", "A tag contains an int");

    py::class_<nbt::IntTag, nbt::Tag>(sm, "IntTag")
        .def(py::init<>(), "Construct an IntTag with default value (0)")
        .def(
            py::init([](py::int_ value) { return std::make_unique<nbt::IntTag>(to_cpp_int<int>(value, "IntTag")); }),
            py::arg("value"),
            "Construct an IntTag from an integer value"
        )

        .def(
            "assign",
            [](nbt::IntTag& self, int value) -> nbt::IntTag& {
                self = value;
                return self;
            },
            py::arg("value"),
            py::return_value_policy::reference_internal,
            "Assign a new integer value to this tag"
        )
        .def("get_type", &nbt::IntTag::getType, "Get the NBT type ID (Int)")
        .def("equals", &nbt::IntTag::equals, py::arg("other"), "Check if this tag equals another tag")
        .def("copy", &nbt::IntTag::copy, "Create a deep copy of this tag")
        .def("hash", &nbt::IntTag::hash, "Compute hash value of this tag")

        .def(
            "write",
            [](nbt::IntTag& self, bstream::BinaryStream& stream) { self.write(stream); },
            py::arg("stream"),
            "Write tag to a binary stream"
        )
        .def(
            "load",
            [](nbt::IntTag& self, bstream::ReadOnlyBinaryStream& stream) { self.load(stream); },
            py::arg("stream"),
            "Load tag value from a binary stream"
        )

        .def_property(
            "value",
            [](nbt::IntTag& self) -> int { return self.storage(); },
            [](nbt::IntTag& self, py::int_ value) { self.storage() = to_cpp_int<int>(value, "IntTag"); },
            "Access the integer value of this tag"
        )

        .def(
            "__int__",
            [](nbt::IntTag const& self) { return self.storage(); },
            "Convert to Python int"
        )
        .def("__pos__", &nbt::IntTag::operator+, "Unary plus operator (+)")
        .def("__eq__", &nbt::IntTag::equals, py::arg("other"), "Equality operator (==)")
        .def("__hash__", &nbt::IntTag::hash, "Compute hash value for Python hashing operations")
        .def(
            "__str__",
            [](nbt::IntTag const& self) { return self.toSnbt(nbt::SnbtFormat::Minimize); },
            "String representation (SNBT minimized format)"
        )
        .def(
            "__repr__",
            [](nbt::IntTag const& self) {
                return std::format(
                    "<rapidnbt.IntTag({0}) object at 0x{1:0{2}X}>",
                    self.storage(),
                    reinterpret_cast<uintptr_t>(&self),
                    ADDRESS_LENGTH
                );
            },
            "Official string representation"
        );
}

} // namespace rapidnbt