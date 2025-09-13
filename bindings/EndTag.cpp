// Copyright © 2025 GlacieTeam.All rights reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
//
// SPDX-License-Identifier: MPL-2.0

#include "NativeModule.hpp"

namespace rapidnbt {

void bindEndTag(py::module& m) {
    py::class_<nbt::EndTag, nbt::Tag>(m, "EndTag")
        .def(py::init<>())

        .def("getType", &nbt::EndTag::getType)
        .def("equals", &nbt::EndTag::equals)
        .def("copy", &nbt::EndTag::copy)
        .def("hash", &nbt::EndTag::hash)
        .def("write", [](nbt::EndTag& self, bstream::BinaryStream& stream) { self.write(stream); })
        .def("load", [](nbt::EndTag& self, bstream::ReadOnlyBinaryStream& stream) { self.load(stream); })

        .def("__str__", [](nbt::EndTag&) { return "EndTag"; })
        .def("__repr__", [](nbt::EndTag&) { return "EndTag"; })
        .def("__eq__", &nbt::EndTag::equals)
        .def("__ne__", [](nbt::EndTag& self, nbt::Tag& other) { return !self.equals(other); })
        .def("__hash__", &nbt::EndTag::hash);
}

} // namespace rapidnbt