// Copyright © 2025 GlacieTeam.All rights reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
//
// SPDX-License-Identifier: MPL-2.0

#include "NativeModule.hpp"

namespace rapidnbt {

void bindByteTag(py::module& m) {
    py::class_<nbt::ByteTag, nbt::Tag>(m, "ByteTag")
        .def(py::init<>())
        .def(py::init<int>(), py::arg("value"))

        .def(
            "assign",
            [](nbt::ByteTag& self, uint8_t value) -> nbt::ByteTag& {
                self = value;
                return self;
            },
            py::arg("value"),
            py::return_value_policy::reference_internal
        )

        .def("__int__", [](const nbt::ByteTag& self) { return static_cast<uint8_t>(self); })
        .def("__index__", [](const nbt::ByteTag& self) { return static_cast<uint8_t>(self); })
        .def("__pos__", &nbt::ByteTag::operator+)

        .def("getType", &nbt::ByteTag::getType)
        .def("equals", &nbt::ByteTag::equals)
        .def("copy", &nbt::ByteTag::copy)
        .def("hash", &nbt::ByteTag::hash)

        .def(
            "write",
            [](nbt::ByteTag& self, bstream::BinaryStream& stream) { self.write(stream); },
            py::arg("stream")
        )
        .def(
            "load",
            [](nbt::ByteTag& self, bstream::ReadOnlyBinaryStream& stream) { self.load(stream); },
            py::arg("stream")
        )

        .def_property(
            "value",
            [](nbt::ByteTag& self) -> uint8_t { return self.storage(); },
            [](nbt::ByteTag& self, uint8_t value) { self.storage() = static_cast<uint8_t>(value); }
        )

        .def("__str__", [](const nbt::ByteTag& self) { return self.toSnbt(nbt::SnbtFormat::Minimize); })
        .def("__repr__", [](const nbt::ByteTag& self) { return std::format("rapidnbt.ByteTag({})", self.storage()); });
}

} // namespace rapidnbt