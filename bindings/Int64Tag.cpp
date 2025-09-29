// Copyright © 2025 GlacieTeam.All rights reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
//
// SPDX-License-Identifier: MPL-2.0

#include "NativeModule.hpp"

namespace rapidnbt {

void bindInt64Tag(py::module& m) {
    auto sm = m.def_submodule("int64_tag", "A tag contains an int64");

    py::class_<nbt::Int64Tag, nbt::Tag>(sm, "Int64Tag")
        .def(py::init<>(), "Construct an Int64Tag with default value (0)")
        .def(
            py::init([](py::int_ value) {
                return std::make_unique<nbt::Int64Tag>(to_cpp_int<int64_t>(value, "Int64Tag"));
            }),
            py::arg("value"),
            "Construct an Int64Tag from an integer value"
        )

        .def(
            "assign",
            [](nbt::Int64Tag& self, int64_t value) -> nbt::Int64Tag& {
                self = value;
                return self;
            },
            py::arg("value"),
            py::return_value_policy::reference_internal,
            "Assign a new integer value to this tag"
        )
        .def("get_type", &nbt::Int64Tag::getType, "Get the NBT type ID (Int64)")
        .def("equals", &nbt::Int64Tag::equals, py::arg("other"), "Check if this tag equals another tag")
        .def("copy", &nbt::Int64Tag::copy, "Create a deep copy of this tag")
        .def("hash", &nbt::Int64Tag::hash, "Compute hash value of this tag")

        .def(
            "write",
            [](nbt::Int64Tag& self, bstream::BinaryStream& stream) { self.write(stream); },
            py::arg("stream"),
            "Write tag to a binary stream"
        )
        .def(
            "load",
            [](nbt::Int64Tag& self, bstream::ReadOnlyBinaryStream& stream) { self.load(stream); },
            py::arg("stream"),
            "Load tag value from a binary stream"
        )

        .def_property(
            "value",
            [](nbt::Int64Tag& self) -> int64_t { return self.storage(); },
            [](nbt::Int64Tag& self, py::int_ value) { self.storage() = to_cpp_int<int64_t>(value, "Int64Tag"); },
            "Access the integer value of this tag"
        )

        .def(
            "__int__",
            [](nbt::Int64Tag const& self) { return self.storage(); },
            "Convert to Python int"
        )
        .def("__pos__", &nbt::Int64Tag::operator+, "Unary plus operator (+)")
        .def("__eq__", &nbt::Int64Tag::equals, py::arg("other"), "Equality operator (==)")
        .def("__hash__", &nbt::Int64Tag::hash, "Compute hash value for Python hashing operations")
        .def(
            "__str__",
            [](nbt::Int64Tag const& self) { return self.toSnbt(nbt::SnbtFormat::Minimize); },
            "String representation (SNBT minimized format)"
        )
        .def(
            "__repr__",
            [](nbt::Int64Tag const& self) {
                return std::format(
                    "<rapidnbt.Int64Tag({0}) object at 0x{1:0{2}X}>",
                    self.storage(),
                    reinterpret_cast<uintptr_t>(&self),
                    ADDRESS_LENGTH
                );
            },
            "Official string representation"
        );
}

} // namespace rapidnbt