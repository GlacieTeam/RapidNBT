// Copyright © 2025 GlacieTeam.All rights reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
//
// SPDX-License-Identifier: MPL-2.0

#include "NativeModule.hpp"

namespace rapidnbt {

void bindIntTag(py::module& m) {
    py::class_<nbt::IntTag, nbt::Tag>(m, "IntTag")
        .def(py::init<>())
        .def(py::init<int>(), py::arg("value"))

        .def(
            "assign",
            [](nbt::IntTag& self, int value) -> nbt::IntTag& {
                self = value;
                return self;
            },
            py::arg("value"),
            py::return_value_policy::reference_internal
        )

        .def("__int__", [](const nbt::IntTag& self) { return static_cast<int>(self); })
        .def("__index__", [](const nbt::IntTag& self) { return static_cast<int>(self); })
        .def("__pos__", &nbt::IntTag::operator+)

        .def("getType", &nbt::IntTag::getType)
        .def("equals", &nbt::IntTag::equals)
        .def("copy", &nbt::IntTag::copy)
        .def("hash", &nbt::IntTag::hash)

        .def(
            "write",
            [](nbt::IntTag& self, bstream::BinaryStream& stream) { self.write(stream); },
            py::arg("stream")
        )
        .def(
            "load",
            [](nbt::IntTag& self, bstream::ReadOnlyBinaryStream& stream) { self.load(stream); },
            py::arg("stream")
        )

        .def_property(
            "value",
            [](nbt::IntTag& self) -> int { return self.storage(); },
            [](nbt::IntTag& self, int value) { self.storage() = static_cast<int>(value); }
        )

        .def("__str__", [](const nbt::IntTag& self) { return self.toSnbt(nbt::SnbtFormat::Minimize); })
        .def("__repr__", [](const nbt::IntTag& self) { return std::format("rapidnbt.IntTag({})", self.storage()); });
}

} // namespace rapidnbt