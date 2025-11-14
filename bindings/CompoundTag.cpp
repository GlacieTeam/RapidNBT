// Copyright © 2025 GlacieTeam.All rights reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
//
// SPDX-License-Identifier: MPL-2.0

#include "NativeModule.hpp"

namespace rapidnbt {

void bindCompoundTag(py::module& m) {
    auto sm = m.def_submodule("compound_tag", "A tag contains a tag compound");

    py::class_<nbt::CompoundTag, nbt::Tag>(sm, "CompoundTag")
        .def(py::init<>(), "Construct an empty CompoundTag")
        .def(
            py::init([](py::dict obj) {
                auto tag = std::make_unique<nbt::CompoundTag>();
                for (auto [k, v] : obj) {
                    std::string key   = py::cast<std::string>(k);
                    auto&       value = static_cast<py::object&>(v);
                    tag->set(key, makeNativeTag(value));
                }
                return tag;
            }),
            py::arg("pairs"),
            "Construct from a Dict[str, Any]",
            "Example:",
            "    CompoundTag([\" key1 \": 42, \" key2 \": \" value \"])"
        )

        .def(
            "__getitem__",
            [](nbt::CompoundTag& self, std::string_view key) -> nbt::CompoundTagVariant& { return self[key]; },
            py::return_value_policy::reference_internal,
            py::arg("key"),
            "Get value by key (no exception, auto create if not found)"
        )
        .def(
            "__setitem__",
            [](nbt::CompoundTag& self, std::string_view key, py::object const& value) {
                self[key] = makeNativeTag(value);
            },
            py::arg("key"),
            py::arg("value"),
            "Set value by key"
        )

        .def("size", &nbt::CompoundTag::size, "Get the size of the compound")
        .def(
            "keys",
            [](nbt::CompoundTag& self) {
                py::list keys;
                for (auto& [key, _] : self) { keys.append(key); }
                return keys;
            },
            "Get list of all keys in the compound"
        )
        .def(
            "values",
            [](nbt::CompoundTag& self) {
                py::list values;
                for (auto& [_, value] : self) { values.append(py::cast(value)); }
                return values;
            },
            "Get list of all values in the compound"
        )
        .def(
            "items",
            [](nbt::CompoundTag& self) {
                py::list items;
                for (auto& [key, value] : self) { items.append(py::make_tuple(key, py::cast(value))); }
                return items;
            },
            "Get list of (key, value) pairs in the compound"
        )

        .def("get_type", &nbt::CompoundTag::getType, "Get the NBT type ID (Compound)")
        .def("equals", &nbt::CompoundTag::equals, py::arg("other"), "Check if this tag equals another tag")
        .def("copy", &nbt::CompoundTag::copy, "Create a deep copy of this tag")
        .def("hash", &nbt::CompoundTag::hash, "Compute hash value of this tag")

        .def(
            "write",
            [](nbt::CompoundTag& self, bstream::BinaryStream& stream) { self.write(stream); },
            py::arg("stream"),
            "Write compound to a binary stream"
        )
        .def(
            "load",
            [](nbt::CompoundTag& self, bstream::ReadOnlyBinaryStream& stream) { self.load(stream); },
            py::arg("stream"),
            "Load compound from a binary stream"
        )

        .def(
            "serialize",
            [](nbt::CompoundTag const& self, bstream::BinaryStream& stream) { self.serialize(stream); },
            py::arg("stream"),
            "Serialize compound to a binary stream"
        )
        .def(
            "deserialize",
            [](nbt::CompoundTag& self, bstream::ReadOnlyBinaryStream& stream) { self.deserialize(stream); },
            py::arg("stream"),
            "Deserialize compound from a binary stream"
        )

        .def(
            "merge",
            &nbt::CompoundTag::merge,
            py::arg("other"),
            py::arg("merge_list") = false,
            "Merge another CompoundTag into this one",
            "",
            "Arguments:",
            "    other: CompoundTag to merge from",
            "    merge_list: If true, merge list contents instead of replacing"
        )
        .def("empty", &nbt::CompoundTag::empty, "Check if the compound is empty")
        .def("clear", &nbt::CompoundTag::clear, "Remove all elements from the compound")
        .def(
            "rename",
            &nbt::CompoundTag::rename,
            py::arg("old_key"),
            py::arg("new_key"),
            "Rename a key in the compound"
        )

        .def(
            "contains",
            [](nbt::CompoundTag const& self, std::string_view key) { return self.contains(key); },
            py::arg("key"),
            "Check if key exists"
        )
        .def(
            "contains",
            [](nbt::CompoundTag const& self, std::string_view key, nbt::Tag::Type type) {
                return self.contains(key, type);
            },
            py::arg("key"),
            py::arg("type"),
            "Check if key exists and value type is the specific type"
        )
        .def(
            "get",
            [](nbt::CompoundTag& self, std::string_view key) -> nbt::CompoundTagVariant& {
                if (!self.contains(key)) { throw py::key_error("tag not exist"); }
                return self.at(key);
            },
            py::return_value_policy::reference_internal,
            py::arg("key"),
            "Get tag by key\nThrow KeyError if not found"
        )
        .def(
            "set",
            [](nbt::CompoundTag& self, std::string key, py::object const& value) { self[key] = makeNativeTag(value); },
            py::arg("key"),
            py::arg("value"),
            "Set value in the compound (automatically converted to appropriate tag type)"
        )

        .def(
            "to_dict",
            [](nbt::CompoundTag const& self) {
                py::dict result;
                for (auto& [key, value] : self) { result[py::str(key)] = py::cast(value); }
                return result;
            },
            "Convert CompoundTag to a Python dictionary"
        )

        .def(
            "to_network_nbt",
            [](nbt::CompoundTag const& self) { return to_py_bytes(self.toNetworkNbt()); },
            "Serialize to Network NBT format (used in Minecraft networking)"
        )
        .def(
            "to_binary_nbt",
            [](nbt::CompoundTag const& self, bool little_endian, bool header) {
                if (header) {
                    return to_py_bytes(self.toBinaryNbtWithHeader(little_endian));
                } else {
                    return to_py_bytes(self.toBinaryNbt(little_endian));
                }
            },
            py::arg("little_endian") = true,
            py::arg("header")        = false,
            "Serialize to binary NBT format"
        )
        .def("pop", &nbt::CompoundTag::remove, py::arg("key"), "Remove key from the compound")

        .def(
            "__contains__",
            [](nbt::CompoundTag const& self, std::string_view key) { return self.contains(key); },
            py::arg("key"),
            "Check if key exists in the compound"
        )
        .def("__delitem__", &nbt::CompoundTag::remove, py::arg("key"), "Remove key from the compound")
        .def("__len__", &nbt::CompoundTag::size, "Get number of key-value pairs")
        .def(
            "__iter__",
            [](nbt::CompoundTag& self) { return py::make_key_iterator(self.begin(), self.end()); },
            py::keep_alive<0, 1>(),
            "Iterate over keys in the compound"
        )
        .def("__eq__", &nbt::CompoundTag::equals, py::arg("other"), "Equality operator (==)")
        .def("__hash__", &nbt::CompoundTag::hash, "Compute hash value for Python hashing operations")
        .def(
            "__str__",
            [](nbt::CompoundTag const& self) { return self.toSnbt(nbt::SnbtFormat::Minimize); },
            "String representation (SNBT minimized format)"
        )
        .def(
            "__repr__",
            [](nbt::CompoundTag const& self) {
                return std::format(
                    "<rapidnbt.CompoundTag(size={0}) object at 0x{1:0{2}X}>",
                    self.size(),
                    reinterpret_cast<uintptr_t>(&self),
                    ADDRESS_LENGTH
                );
            },
            "Official string representation"
        )

        .def_property(
            "value",
            [](nbt::CompoundTag& self) -> py::dict {
                py::dict result;
                for (auto& [key, value] : self) { result[py::str(key)] = py::cast(value); }
                return result;
            },
            [](nbt::CompoundTag& self, py::dict const& value) {
                self.clear();
                for (auto const& [k, v] : value) {
                    std::string key = py::cast<std::string>(k);
                    auto&       val = static_cast<py::object const&>(v);
                    self.set(key, makeNativeTag(val));
                }
            },
            "Access the dict value of this tag"
        )

        .def_static(
            "from_network_nbt",
            [](py::buffer value) { return nbt::CompoundTag::fromNetworkNbt(to_cpp_stringview(value)); },
            py::arg("binary_data"),
            "Deserialize from Network NBT format"
        )
        .def_static(
            "from_binary_nbt",
            [](py::buffer value, bool little_endian, bool header) {
                if (header) {
                    return nbt::CompoundTag::fromBinaryNbtWithHeader(to_cpp_stringview(value), little_endian);
                } else {
                    return nbt::CompoundTag::fromBinaryNbt(to_cpp_stringview(value), little_endian);
                }
            },
            py::arg("binary_data"),
            py::arg("little_endian") = true,
            py::arg("header")        = false,
            "Deserialize from binary NBT format"
        )
        .def_static(
            "from_snbt",
            &nbt::CompoundTag::fromSnbt,
            py::arg("snbt"),
            py::arg("parsed_length") = std::nullopt,
            "Parse from String NBT (SNBT) format"
        );
}

} // namespace rapidnbt