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
            [](const nbt::Tag& self, nbt::SnbtFormat format = nbt::SnbtFormat::PrettyFilePrint, uint8_t indent = 4) {
                return self.toSnbt(format, indent);
            },
            py::arg("format") = nbt::SnbtFormat::PrettyFilePrint,
            py::arg("indent") = 4,
            "Convert tag to SNBT string"
        )
        .def("to_json", &nbt::Tag::toJson, py::arg("indent") = 4, "Convert tag to JSON string")

        .def("__eq__", &nbt::Tag::equals, "Compare two tags for equality")
        .def("__hash__", &nbt::Tag::hash)

        .def(
            "__getitem__",
            [](nbt::Tag& self, size_t index) -> nbt::Tag& { return self[index]; },
            py::arg("index"),
            py::return_value_policy::reference_internal
        )
        .def(
            "__getitem__",
            [](nbt::Tag& self, std::string_view key) -> nbt::CompoundTagVariant& { return self[key]; },
            py::arg("key"),
            py::return_value_policy::reference_internal
        )

        .def(
            "as_string",
            [](nbt::Tag& self) -> std::string { return static_cast<std::string>(self); },
            "Convert tag to string"
        )

        .def(
            "as_bytes",
            [](const nbt::Tag& self) -> py::bytes { return py::bytes(static_cast<std::string>(self)); },
            "Convert tag to bytes"
        )

        .def_static(
            "new_tag",
            [](nbt::Tag::Type type) -> TagHolder { return nbt::Tag::newTag(type); },
            py::arg("type"),
            "Create a new tag of the given type"
        )

        .def("__str__", [](const nbt::Tag& self) { return self.toSnbt(nbt::SnbtFormat::Minimize); })
        .def("__repr__", [](const nbt::Tag& self) {
            return std::format(
                "<rapidnbt.Tag(type={0}) object at 0x{1:0{2}X}>",
                magic_enum::enum_name(self.getType()),
                reinterpret_cast<uintptr_t>(&self),
                ADDRESS_LENGTH
            );
        });
}

} // namespace rapidnbt
