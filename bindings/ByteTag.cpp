// Copyright © 2025 GlacieTeam.All rights reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
//
// SPDX-License-Identifier: MPL-2.0

#include "NativeModule.hpp"

namespace rapidnbt {

void bindByteTag(py::module& m) {
    auto sm = m.def_submodule("byte_tag", "A tag contains a byte");

    py::class_<nbt::ByteTag, nbt::Tag>(sm, "ByteTag")
        .def(py::init<>(), "Construct an ByteTag with default value (0)")
        .def(
            py::init([](py::int_ value) {
                return std::make_unique<nbt::ByteTag>(to_cpp_int<uint8_t>(value, "ByteTag"));
            }),
            py::arg("value"),
            "Construct an ByteTag from an integer value"
        )

        .def(
            "assign",
            [](nbt::ByteTag& self, uint8_t value) -> nbt::ByteTag& {
                self = value;
                return self;
            },
            py::arg("value"),
            py::return_value_policy::reference_internal,
            "Assign a new integer value to this tag"
        )
        .def("get_type", &nbt::ByteTag::getType, "Get the NBT type ID (Byte)")
        .def("equals", &nbt::ByteTag::equals, py::arg("other"), "Check if this tag equals another tag")
        .def("copy", &nbt::ByteTag::copy, "Create a deep copy of this tag")
        .def("hash", &nbt::ByteTag::hash, "Compute hash value of this tag")

        .def(
            "write",
            [](nbt::ByteTag& self, bstream::BinaryStream& stream) { self.write(stream); },
            py::arg("stream"),
            "Write tag to a binary stream"
        )
        .def(
            "load",
            [](nbt::ByteTag& self, bstream::ReadOnlyBinaryStream& stream) { self.load(stream); },
            py::arg("stream"),
            "Load tag value from a binary stream"
        )

        .def_property(
            "value",
            [](nbt::ByteTag& self) -> uint8_t { return self.storage(); },
            [](nbt::ByteTag& self, py::int_ value) { self.storage() = to_cpp_int<uint8_t>(value, "ByteTag"); },
            "Access the integer value of this tag"
        )

        .def(
            "__int__",
            [](nbt::ByteTag const& self) { return self.storage(); },
            "Convert to Python int"
        )
        .def("__pos__", &nbt::ByteTag::operator+, "Unary plus operator (+)")
        .def("__eq__", &nbt::ByteTag::equals, py::arg("other"), "Equality operator (==)")
        .def("__hash__", &nbt::ByteTag::hash, "Compute hash value for Python hashing operations")
        .def(
            "__str__",
            [](nbt::ByteTag const& self) { return self.toSnbt(nbt::SnbtFormat::Minimize); },
            "String representation (SNBT minimized format)"
        )
        .def(
            "__repr__",
            [](nbt::ByteTag const& self) {
                return std::format(
                    "<rapidnbt.ByteTag object at 0x{0:0{1}X}>",
                    reinterpret_cast<uintptr_t>(&self),
                    ADDRESS_LENGTH
                );
            },
            "Official string representation"
        );
}

} // namespace rapidnbt