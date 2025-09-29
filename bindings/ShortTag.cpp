// Copyright © 2025 GlacieTeam.All rights reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
//
// SPDX-License-Identifier: MPL-2.0

#include "NativeModule.hpp"

namespace rapidnbt {

void bindShortTag(py::module& m) {
    auto sm = m.def_submodule("short_tag");

    py::class_<nbt::ShortTag, nbt::Tag>(sm, "ShortTag", "A tag contains a short")
        .def(py::init<>(), "Construct an ShortTag with default value (0)")
        .def(
            py::init([](py::int_ value) {
                return std::make_unique<nbt::ShortTag>(to_cpp_int<short>(value, "ShortTag"));
            }),
            py::arg("value"),
            "Construct an ShortTag from an integer value"
        )

        .def(
            "assign",
            [](nbt::ShortTag& self, short value) -> nbt::ShortTag& {
                self = value;
                return self;
            },
            py::arg("value"),
            py::return_value_policy::reference_internal,
            "Assign a new integer value to this tag"
        )
        .def("get_type", &nbt::ShortTag::getType, "Get the NBT type ID (Short)")
        .def("equals", &nbt::ShortTag::equals, py::arg("other"), "Check if this tag equals another tag")
        .def("copy", &nbt::ShortTag::copy, "Create a deep copy of this tag")
        .def("hash", &nbt::ShortTag::hash, "Compute hash value of this tag")

        .def(
            "write",
            [](nbt::ShortTag& self, bstream::BinaryStream& stream) { self.write(stream); },
            py::arg("stream"),
            "Write tag to a binary stream"
        )
        .def(
            "load",
            [](nbt::ShortTag& self, bstream::ReadOnlyBinaryStream& stream) { self.load(stream); },
            py::arg("stream"),
            "Load tag value from a binary stream"
        )

        .def_property(
            "value",
            [](nbt::ShortTag& self) -> short { return self.storage(); },
            [](nbt::ShortTag& self, py::int_ value) { self.storage() = to_cpp_int<short>(value, "ShortTag"); },
            "Access the integer value of this tag"
        )

        .def(
            "__int__",
            [](nbt::ShortTag const& self) { return static_cast<short>(self); },
            "Convert to Python int"
        )
        .def("__pos__", &nbt::ShortTag::operator+, "Unary plus operator (+)")
        .def("__eq__", &nbt::ShortTag::equals, py::arg("other"), "Equality operator (==)")
        .def("__hash__", &nbt::ShortTag::hash, "Compute hash value for Python hashing operations")
        .def(
            "__str__",
            [](nbt::ShortTag const& self) { return self.toSnbt(nbt::SnbtFormat::Minimize); },
            "String representation (SNBT minimized format)"
        )
        .def(
            "__repr__",
            [](nbt::ShortTag const& self) {
                return std::format(
                    "<rapidnbt.ShortTag({0}) object at 0x{1:0{2}X}>",
                    self.storage(),
                    reinterpret_cast<uintptr_t>(&self),
                    ADDRESS_LENGTH
                );
            },
            "Official string representation"
        );
}

} // namespace rapidnbt