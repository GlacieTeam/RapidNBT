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
            [](const nbt::Tag& self, nbt::SnbtFormat format = nbt::SnbtFormat::Default, uint8_t indent = 4) {
                return self.toSnbt(format, indent);
            },
            py::arg("format") = nbt::SnbtFormat::Default,
            py::arg("indent") = 4,
            "Convert tag to SNBT string"
        )
        .def("to_json", &nbt::Tag::toJson, py::arg("indent") = 4, "Convert tag to JSON string")

        .def("__eq__", &nbt::Tag::equals, py::arg("other"), "Compare two tags for equality")
        .def("__hash__", &nbt::Tag::hash, "Compute hash value for Python hashing operations")

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
            "as_byte_tag",
            [](nbt::Tag& self) -> nbt::ByteTag& {
                if (self.getType() != nbt::Tag::Type::Byte) { throw py::type_error("tag is not a ByteTag"); }
                return self.as<nbt::ByteTag>();
            },
            py::return_value_policy::reference_internal,
            "Convert to a ByteTag\nThrow TypeError if wrong type"
        )
        .def(
            "as_short_tag",
            [](nbt::Tag& self) -> nbt::ShortTag& {
                if (self.getType() != nbt::Tag::Type::Short) { throw py::type_error("tag is not a ShortTag"); }
                return self.as<nbt::ShortTag>();
            },
            py::return_value_policy::reference_internal,
            "Convert to a ShortTag\nThrow TypeError if wrong type"
        )
        .def(
            "as_int_tag",
            [](nbt::Tag& self) -> nbt::IntTag& {
                if (self.getType() != nbt::Tag::Type::Int) { throw py::type_error("tag not hold an IntTag"); }
                return self.as<nbt::IntTag>();
            },
            py::return_value_policy::reference_internal,
            "Convert to a IntTag\nThrow TypeError if wrong type"
        )
        .def(
            "as_long_tag",
            [](nbt::Tag& self) -> nbt::LongTag& {
                if (self.getType() != nbt::Tag::Type::Long) { throw py::type_error("tag not hold an LongTag"); }
                return self.as<nbt::LongTag>();
            },
            py::return_value_policy::reference_internal,
            "Convert to a LongTag\nThrow TypeError if wrong type"
        )
        .def(
            "as_float_tag",
            [](nbt::Tag& self) -> nbt::FloatTag& {
                if (self.getType() != nbt::Tag::Type::Float) { throw py::type_error("tag is not a FloatTag"); }
                return self.as<nbt::FloatTag>();
            },
            py::return_value_policy::reference_internal,
            "Convert to a FloatTag\nThrow TypeError if wrong type"
        )
        .def(
            "as_double_tag",
            [](nbt::Tag& self) -> nbt::DoubleTag& {
                if (self.getType() != nbt::Tag::Type::Double) { throw py::type_error("tag is not a DoubleTag"); }
                return self.as<nbt::DoubleTag>();
            },
            py::return_value_policy::reference_internal,
            "Convert to a DoubleTag\nThrow TypeError if wrong type"
        )
        .def(
            "as_byte_array_tag",
            [](nbt::Tag& self) -> nbt::ByteArrayTag& {
                if (self.getType() != nbt::Tag::Type::ByteArray) { throw py::type_error("tag is not a ByteArrayTag"); }
                return self.as<nbt::ByteArrayTag>();
            },
            py::return_value_policy::reference_internal,
            "Convert to a ByteArrayTag\nThrow TypeError if wrong type"
        )
        .def(
            "as_string_tag",
            [](nbt::Tag& self) -> nbt::StringTag& {
                if (self.getType() != nbt::Tag::Type::String) { throw py::type_error("tag is not a StringTag"); }
                return self.as<nbt::StringTag>();
            },
            py::return_value_policy::reference_internal,
            "Convert to a StringTag\nThrow TypeError if wrong type"
        )
        .def(
            "as_compound_tag",
            [](nbt::Tag& self) -> nbt::CompoundTag& {
                if (self.getType() != nbt::Tag::Type::Compound) { throw py::type_error("tag is not a CompoundTag"); }
                return self.as<nbt::CompoundTag>();
            },
            py::return_value_policy::reference_internal,
            "Convert to a CompoundTag\nThrow TypeError if wrong type"
        )
        .def(
            "as_list_tag",
            [](nbt::Tag& self) -> nbt::ListTag& {
                if (self.getType() != nbt::Tag::Type::List) { throw py::type_error("tag is not a ListTag"); }
                return self.as<nbt::ListTag>();
            },
            py::return_value_policy::reference_internal,
            "Convert to a ListTag\nThrow TypeError if wrong type"
        )
        .def(
            "as_int_array_tag",
            [](nbt::Tag& self) -> nbt::IntArrayTag& {
                if (self.getType() != nbt::Tag::Type::IntArray) { throw py::type_error("tag not hold an IntArrayTag"); }
                return self.as<nbt::IntArrayTag>();
            },
            py::return_value_policy::reference_internal,
            "Convert to a IntArrayTag\nThrow TypeError if wrong type"
        )
        .def(
            "as_long_array_tag",
            [](nbt::Tag& self) -> nbt::LongArrayTag& {
                if (self.getType() != nbt::Tag::Type::LongArray) { throw py::type_error("tag is not a LongArrayTag"); }
                return self.as<nbt::LongArrayTag>();
            },
            py::return_value_policy::reference_internal,
            "Convert to a LongArrayTag\nThrow TypeError if wrong type"
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
