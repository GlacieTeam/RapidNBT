// Copyright © 2025 GlacieTeam.All rights reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
//
// SPDX-License-Identifier: MPL-2.0

#include "NativeModule.hpp"

namespace rapidnbt {

void bindInt64Tag(py::module& m) {
    py::class_<nbt::Int64Tag, nbt::Tag>(m, "Int64Tag")
        .def(py::init<>())
        .def(py::init<int>(), py::arg("value"))

        .def(
            "assign",
            [](nbt::Int64Tag& self, int64_t value) -> nbt::Int64Tag& {
                self = value;
                return self;
            },
            py::arg("value"),
            py::return_value_policy::reference_internal
        )

        .def("__int__", [](const nbt::Int64Tag& self) { return static_cast<int64_t>(self); })
        .def("__index__", [](const nbt::Int64Tag& self) { return static_cast<int64_t>(self); })
        .def("__pos__", &nbt::Int64Tag::operator+)

        .def("getType", &nbt::Int64Tag::getType)
        .def("equals", &nbt::Int64Tag::equals)
        .def("copy", &nbt::Int64Tag::copy)
        .def("hash", &nbt::Int64Tag::hash)

        .def(
            "write",
            [](nbt::Int64Tag& self, bstream::BinaryStream& stream) { self.write(stream); },
            py::arg("stream")
        )
        .def(
            "load",
            [](nbt::Int64Tag& self, bstream::ReadOnlyBinaryStream& stream) { self.load(stream); },
            py::arg("stream")
        )

        .def_property(
            "value",
            [](nbt::Int64Tag& self) -> int64_t { return self.storage(); },
            [](nbt::Int64Tag& self, int64_t value) { self.storage() = static_cast<int64_t>(value); }
        )

        .def("__str__", [](const nbt::Int64Tag& self) { return self.toSnbt(nbt::SnbtFormat::Minimize); })
        .def("__repr__", [](const nbt::Int64Tag& self) {
            return std::format("rapidnbt.Int64Tag({})", self.storage());
        });
}

}