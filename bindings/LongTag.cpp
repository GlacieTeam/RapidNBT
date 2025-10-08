// Copyright © 2025 GlacieTeam.All rights reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
//
// SPDX-License-Identifier: MPL-2.0

#include "NativeModule.hpp"

namespace rapidnbt {

void bindLongTag(py::module& m) {
    auto sm = m.def_submodule("long_tag", "A tag contains an int64");

    py::class_<nbt::LongTag, nbt::Tag>(sm, "LongTag")
        .def(py::init<>(), "Construct an LongTag with default value (0)")
        .def(
            py::init([](py::int_ value) {
                return std::make_unique<nbt::LongTag>(to_cpp_int<int64_t>(value, "LongTag"));
            }),
            py::arg("value"),
            "Construct an LongTag from an integer value"
        )

        .def(
            "assign",
            [](nbt::LongTag& self, int64_t value) -> nbt::LongTag& {
                self = value;
                return self;
            },
            py::arg("value"),
            py::return_value_policy::reference_internal,
            "Assign a new integer value to this tag"
        )
        .def("get_type", &nbt::LongTag::getType, "Get the NBT type ID (Long)")
        .def("equals", &nbt::LongTag::equals, py::arg("other"), "Check if this tag equals another tag")
        .def("copy", &nbt::LongTag::copy, "Create a deep copy of this tag")
        .def("hash", &nbt::LongTag::hash, "Compute hash value of this tag")

        .def(
            "write",
            [](nbt::LongTag& self, bstream::BinaryStream& stream) { self.write(stream); },
            py::arg("stream"),
            "Write tag to a binary stream"
        )
        .def(
            "load",
            [](nbt::LongTag& self, bstream::ReadOnlyBinaryStream& stream) { self.load(stream); },
            py::arg("stream"),
            "Load tag value from a binary stream"
        )

        .def_property(
            "value",
            [](nbt::LongTag& self) -> int64_t { return self.storage(); },
            [](nbt::LongTag& self, py::int_ value) { self.storage() = to_cpp_int<int64_t>(value, "LongTag"); },
            "Access the integer value of this tag"
        )

        .def(
            "__int__",
            [](nbt::LongTag const& self) { return self.storage(); },
            "Convert to Python int"
        )
        .def("__pos__", &nbt::LongTag::operator+, "Unary plus operator (+)")
        .def("__eq__", &nbt::LongTag::equals, py::arg("other"), "Equality operator (==)")
        .def("__hash__", &nbt::LongTag::hash, "Compute hash value for Python hashing operations")
        .def(
            "__str__",
            [](nbt::LongTag const& self) { return self.toSnbt(nbt::SnbtFormat::Minimize); },
            "String representation (SNBT minimized format)"
        )
        .def(
            "__repr__",
            [](nbt::LongTag const& self) {
                return std::format(
                    "<rapidnbt.LongTag({0}) object at 0x{1:0{2}X}>",
                    self.storage(),
                    reinterpret_cast<uintptr_t>(&self),
                    ADDRESS_LENGTH
                );
            },
            "Official string representation"
        );
}

} // namespace rapidnbt