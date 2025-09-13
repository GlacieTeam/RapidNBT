// Copyright © 2025 GlacieTeam.All rights reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
//
// SPDX-License-Identifier: MPL-2.0

#include "NativeModule.hpp"

namespace rapidnbt {

void bindShortTag(py::module& m) {
    py::class_<nbt::ShortTag, nbt::Tag>(m, "ShortTag")
        .def(py::init<>())
        .def(py::init<int>(), py::arg("value"))

        .def(
            "assign",
            [](nbt::ShortTag& self, short value) -> nbt::ShortTag& {
                self = value;
                return self;
            },
            py::arg("value"),
            py::return_value_policy::reference_internal
        )

        .def("__int__", [](const nbt::ShortTag& self) { return static_cast<short>(self); })
        .def("__index__", [](const nbt::ShortTag& self) { return static_cast<short>(self); })
        .def("__pos__", &nbt::ShortTag::operator+)

        .def("getType", &nbt::ShortTag::getType)
        .def("equals", &nbt::ShortTag::equals)
        .def("copy", &nbt::ShortTag::copy)
        .def("hash", &nbt::ShortTag::hash)

        .def(
            "write",
            [](nbt::ShortTag& self, bstream::BinaryStream& stream) { self.write(stream); },
            py::arg("stream")
        )
        .def(
            "load",
            [](nbt::ShortTag& self, bstream::ReadOnlyBinaryStream& stream) { self.load(stream); },
            py::arg("stream")
        )

        .def_property(
            "value",
            [](nbt::ShortTag& self) -> short { return self.storage(); },
            [](nbt::ShortTag& self, short value) { self.storage() = static_cast<short>(value); }
        )

        .def("__str__", [](const nbt::ShortTag& self) { return self.toSnbt(nbt::SnbtFormat::Minimize); })
        .def("__repr__", [](const nbt::ShortTag& self) {
            return std::format("rapidnbt.ShortTag({})", self.storage());
        });
}

} // namespace rapidnbt