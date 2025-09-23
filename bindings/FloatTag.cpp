// Copyright © 2025 GlacieTeam.All rights reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
//
// SPDX-License-Identifier: MPL-2.0

#include "NativeModule.hpp"

namespace rapidnbt {

void bindFloatTag(py::module& m) {
    auto sm = m.def_submodule("float_tag", "A tag contains a float");

    py::class_<nbt::FloatTag, nbt::Tag>(sm, "FloatTag")
        .def(py::init<>(), "Construct a FloatTag with default value (0.0)")
        .def(py::init<float>(), py::arg("value"), "Construct a FloatTag from a floating-point value")

        .def(
            "assign",
            [](nbt::FloatTag& self, float value) -> nbt::FloatTag& {
                self = value;
                return self;
            },
            py::arg("value"),
            py::return_value_policy::reference_internal,
            "Assign a new floating-point value to this tag"
        )

        .def("get_type", &nbt::FloatTag::getType, "Get the NBT type ID (Float)")
        .def("equals", &nbt::FloatTag::equals, py::arg("other"), "Check if this tag equals another tag")
        .def("copy", &nbt::FloatTag::copy, "Create a deep copy of this tag")
        .def("hash", &nbt::FloatTag::hash, "Compute hash value of this tag")

        .def(
            "write",
            [](nbt::FloatTag& self, bstream::BinaryStream& stream) { self.write(stream); },
            py::arg("stream"),
            "Write tag to a binary stream"
        )
        .def(
            "load",
            [](nbt::FloatTag& self, bstream::ReadOnlyBinaryStream& stream) { self.load(stream); },
            py::arg("stream"),
            "Load tag value from a binary stream"
        )

        .def_property(
            "value",
            [](nbt::FloatTag& self) -> float { return self.storage(); },
            [](nbt::FloatTag& self, float value) { self.storage() = value; },
            "Access the floating-point value of this tag"
        )

        .def(
            "__float__",
            [](nbt::FloatTag const& self) { return self.storage(); },
            "Convert to Python float (for float(tag) operations)"
        )
        .def("__hash__", &nbt::FloatTag::hash, "Compute hash value for Python hashing operations")
        .def("__eq__", &nbt::FloatTag::equals, py::arg("other"), "Equality operator (==)")
        .def(
            "__str__",
            [](nbt::FloatTag const& self) { return self.toSnbt(nbt::SnbtFormat::Minimize); },
            "String representation (SNBT minimized format)"
        )
        .def(
            "__repr__",
            [](nbt::FloatTag const& self) {
                return std::format(
                    "<rapidnbt.FloatTag({0}) object at 0x{1:0{2}X}>",
                    self.storage(),
                    reinterpret_cast<uintptr_t>(&self),
                    ADDRESS_LENGTH
                );
            },
            "Official string representation including type information"
        );
}

} // namespace rapidnbt