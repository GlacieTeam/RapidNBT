// Copyright © 2025 GlacieTeam.All rights reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
//
// SPDX-License-Identifier: MPL-2.0

#include "NativeModule.hpp"

namespace rapidnbt {

void bindEndTag(py::module& m) {
    auto sm = m.def_submodule("end_tag", "A tag contains nothing, used as the end flag");

    py::class_<nbt::EndTag, nbt::Tag>(sm, "EndTag")
        .def(py::init<>(), "Construct an EndTag")

        .def("get_type", &nbt::EndTag::getType, "Get the NBT type ID (End)")
        .def(
            "equals",
            &nbt::EndTag::equals,
            py::arg("other"),
            "Check if this tag equals another tag (all EndTags are equal)"
        )
        .def("copy", &nbt::EndTag::copy, "Create a deep copy of this tag")
        .def("hash", &nbt::EndTag::hash, "Compute hash value of this tag")
        .def(
            "write",
            [](nbt::EndTag& self, bstream::BinaryStream& stream) { self.write(stream); },
            py::arg("stream"),
            "Write tag to a binary stream (no data for EndTag)"
        )
        .def(
            "load",
            [](nbt::EndTag& self, bstream::ReadOnlyBinaryStream& stream) { self.load(stream); },
            py::arg("stream"),
            "Load tag value from a binary stream (no data for EndTag)"
        )

        .def("__eq__", &nbt::EndTag::equals, py::arg("other"), "Equality operator (==), all EndTags are equal")
        .def("__hash__", &nbt::EndTag::hash, "Compute hash value for Python hashing operations")
        .def(
            "__str__",
            [](nbt::EndTag const& self) { return self.toSnbt(nbt::SnbtFormat::Minimize); },
            "String representation (SNBT minimized format)"
        )
        .def("__repr__", [](nbt::EndTag const&) { return "rapidnbt.EndTag"; }, "Official string representation");
}

} // namespace rapidnbt