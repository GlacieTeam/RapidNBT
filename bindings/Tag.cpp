// Copyright © 2025 GlacieTeam.All rights reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
//
// SPDX-License-Identifier: MPL-2.0

#include "NativeModule.hpp"

namespace rapidnbt {

using TagHolder = std::unique_ptr<nbt::Tag>;

class PyTag : public nbt::Tag {
public:
    Type getType() const override { PYBIND11_OVERLOAD_PURE(Type, nbt::Tag, getType, ); }

    bool equals(Tag const& other) const override { PYBIND11_OVERLOAD_PURE(bool, nbt::Tag, equals, other); }

    std::unique_ptr<Tag> copy() const override { PYBIND11_OVERLOAD_PURE(std::unique_ptr<Tag>, nbt::Tag, copy, ); }

    std::size_t hash() const override { PYBIND11_OVERLOAD_PURE(std::size_t, nbt::Tag, hash, ); }

    void write(bstream::BinaryStream& stream) const override { PYBIND11_OVERLOAD_PURE(void, nbt::Tag, write, stream); }

    void load(bstream::ReadOnlyBinaryStream& stream) override { PYBIND11_OVERLOAD_PURE(void, nbt::Tag, load, stream); }
};

void bindTag(py::module& m) {
    auto sm = m.def_submodule("tag");

    py::class_<nbt::Tag, PyTag, TagHolder>(sm, "Tag", "Base class for all NBT tags")
        .def("get_type", &nbt::Tag::getType, "Get the type of this tag")
        .def("equals", &nbt::Tag::equals, py::arg("other"), "Check if this tag equals another tag")
        .def("copy", &nbt::Tag::copy, "Create a deep copy of this tag")
        .def("hash", &nbt::Tag::hash, "Compute hash value of this tag")
        .def(
            "write",
            [](nbt::Tag& self, bstream::BinaryStream& stream) { self.write(stream); },
            py::arg("stream"),
            "Write tag to binary stream"
        )
        .def(
            "load",
            [](nbt::Tag& self, bstream::ReadOnlyBinaryStream& stream) { self.load(stream); },
            py::arg("stream"),
            "Load tag from binary stream"
        )
        .def(
            "to_snbt",
            [](const nbt::Tag& self, nbt::SnbtFormat format, uint8_t indent, nbt::SnbtNumberFormat number_format) {
                return self.toSnbt(format, indent, number_format);
            },
            py::arg("format")        = nbt::SnbtFormat::Default,
            py::arg("indent")        = 4,
            py::arg("number_format") = nbt::SnbtNumberFormat::Default,
            "Convert tag to SNBT string"
        )
        .def("to_json", &nbt::Tag::toJson, py::arg("indent") = 4, "Convert tag to JSON string")

        .def("__eq__", &nbt::Tag::equals, py::arg("other"), "Compare two tags for equality")
        .def("__hash__", &nbt::Tag::hash, "Compute hash value for Python hashing operations")

        .def_static(
            "new_tag",
            [](nbt::Tag::Type type) -> TagHolder { return nbt::Tag::newTag(type); },
            py::arg("type"),
            "Create a new tag of the given type"
        )

        .def(
            "__str__",
            [](const nbt::Tag& self) { return self.toSnbt(nbt::SnbtFormat::Minimize); },
            "String representation (SNBT minimized format)"
        )
        .def(
            "__repr__",
            [](const nbt::Tag& self) { return std::format("<rapidnbt.Tag(type={0}) object at 0x{1:0{2}X}>", ENUM(self.getType()), ADDRESS); },
            "Official string representation"
        );
}

} // namespace rapidnbt
