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
                    if (py::isinstance<nbt::CompoundTagVariant>(value)) {
                        (*tag)[key] = *value.cast<nbt::CompoundTagVariant*>();
                    } else if (py::isinstance<nbt::Tag>(value)) {
                        tag->put(key, value.cast<nbt::Tag*>()->copy());
                    } else {
                        tag->put(key, makeNativeTag(value));
                    }
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
                if (py::isinstance<nbt::CompoundTagVariant>(value)) {
                    self[key] = *value.cast<nbt::CompoundTagVariant*>();
                } else if (py::isinstance<nbt::Tag>(value)) {
                    self[key] = *value.cast<nbt::Tag*>();
                } else {
                    self[key] = makeNativeTag(value);
                }
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
        .def("clone", &nbt::CompoundTag::clone, "Create a deep copy of this compound tag")
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
            "put",
            [](nbt::CompoundTag& self, std::string key, py::object const& value) {
                if (py::isinstance<nbt::CompoundTagVariant>(value)) {
                    if (!self.contains(key)) { self[key] = *value.cast<nbt::CompoundTagVariant*>(); }
                } else if (py::isinstance<nbt::Tag>(value)) {
                    self.put(key, value.cast<nbt::Tag*>()->copy());
                } else {
                    self.put(key, makeNativeTag(value));
                }
            },
            py::arg("key"),
            py::arg("value"),
            "Put a value into the compound (automatically converted to appropriate tag type)"
        )
        .def(
            "set",
            [](nbt::CompoundTag& self, std::string key, py::object const& value) {
                if (py::isinstance<nbt::CompoundTagVariant>(value)) {
                    self[key] = *value.cast<nbt::CompoundTagVariant*>();
                } else if (py::isinstance<nbt::Tag>(value)) {
                    self[key] = *value.cast<nbt::Tag*>()->copy();
                } else {
                    self[key] = makeNativeTag(value);
                }
            },
            py::arg("key"),
            py::arg("value"),
            "Set value in the compound (automatically converted to appropriate tag type)"
        )

        .def("put_byte", &nbt::CompoundTag::putByte, py::arg("key"), py::arg("value"), "Put a byte (uint8) value")
        .def("put_short", &nbt::CompoundTag::putShort, py::arg("key"), py::arg("value"), "Put a short (int16) value")
        .def("put_int", &nbt::CompoundTag::putInt, py::arg("key"), py::arg("value"), "Put an int (int32) value")
        .def("put_long", &nbt::CompoundTag::putLong, py::arg("key"), py::arg("value"), "Put a long (int64) value")
        .def("put_float", &nbt::CompoundTag::putFloat, py::arg("key"), py::arg("value"), "Put a float value")
        .def("put_double", &nbt::CompoundTag::putDouble, py::arg("key"), py::arg("value"), "Put a double value")
        .def("put_string", &nbt::CompoundTag::putString, py::arg("key"), py::arg("value"), "Put a string value")
        .def(
            "put_byte_array",
            [](nbt::CompoundTag& self, std::string_view key, py::buffer value) {
                self.put(key, nbt::ByteArrayTag(to_cppstringview(value)));
            },
            py::arg("key"),
            py::arg("value"),
            "Put a byte array (list of uint8)"
        )
        .def(
            "put_int_array",
            &nbt::CompoundTag::putIntArray,
            py::arg("key"),
            py::arg("value"),
            "Put an int array (list of int32)"
        )
        .def(
            "put_long_array",
            &nbt::CompoundTag::putLongArray,
            py::arg("key"),
            py::arg("value"),
            "Put a long array (list of int64)"
        )
        .def(
            "put_compound",
            [](nbt::CompoundTag& self, std::string key, py::object const& value) {
                if (py::isinstance<nbt::CompoundTag>(value)) {
                    self.putCompound(key, value.cast<nbt::CompoundTag>());
                } else if (py::isinstance<py::dict>(value)) {
                    self.put(key, makeNativeTag(value));
                } else {
                    throw py::type_error("Value must be a CompoundTag or dict");
                }
            },
            py::arg("key"),
            py::arg("value"),
            "Put a CompoundTag value (or dict that will be converted)"
        )
        .def(
            "put_list",
            [](nbt::CompoundTag& self, std::string key, py::object const& value) {
                if (py::isinstance<nbt::ListTag>(value)) {
                    self.putList(key, value.cast<nbt::ListTag>());
                } else if (py::isinstance<py::list>(value)) {
                    self.put(key, makeNativeTag(value));
                } else {
                    throw py::type_error("Value must be a ListTag or list/tuple");
                }
            },
            py::arg("key"),
            py::arg("value"),
            "Put a ListTag value (or list/tuple that will be converted)"
        )

        .def(
            "set_byte",
            [](nbt::CompoundTag& self, std::string_view key, uint8_t value) { self[key] = value; },
            py::arg("key"),
            py::arg("value"),
            "Set a byte (uint8) value"
        )
        .def(
            "set_short",
            [](nbt::CompoundTag& self, std::string_view key, short value) { self[key] = value; },
            py::arg("key"),
            py::arg("value"),
            "Set a short (int16) value"
        )
        .def(
            "set_int",
            [](nbt::CompoundTag& self, std::string_view key, int value) { self[key] = value; },
            py::arg("key"),
            py::arg("value"),
            "Set an int (int32) value"
        )
        .def(
            "set_long",
            [](nbt::CompoundTag& self, std::string_view key, int64_t value) { self[key] = value; },
            py::arg("key"),
            py::arg("value"),
            "Set a long (int64) value"
        )
        .def(
            "set_float",
            [](nbt::CompoundTag& self, std::string_view key, float value) { self[key] = value; },
            py::arg("key"),
            py::arg("value"),
            "Set a float value"
        )
        .def(
            "set_double",
            [](nbt::CompoundTag& self, std::string_view key, double value) { self[key] = value; },
            py::arg("key"),
            py::arg("value"),
            "Set a double value"
        )
        .def(
            "set_string",
            [](nbt::CompoundTag& self, std::string_view key, std::string_view value) { self[key] = value; },
            py::arg("key"),
            py::arg("value"),
            "Set a string value"
        )
        .def(
            "set_byte_array",
            [](nbt::CompoundTag& self, std::string_view key, py::buffer value) {
                self[key] = nbt::ByteArrayTag(to_cppstringview(value));
            },
            py::arg("key"),
            py::arg("value"),
            "Set a byte array (list of uint8)"
        )
        .def(
            "set_int_array",
            [](nbt::CompoundTag& self, std::string_view key, std::vector<int> const& value) { self[key] = value; },
            py::arg("key"),
            py::arg("value"),
            "Set an int array (list of int32)"
        )
        .def(
            "set_long_array",
            [](nbt::CompoundTag& self, std::string_view key, std::vector<int64_t> const& value) { self[key] = value; },
            py::arg("key"),
            py::arg("value"),
            "Set a long array (list of int64)"
        )
        .def(
            "set_compound",
            [](nbt::CompoundTag& self, std::string key, py::object const& value) {
                if (py::isinstance<nbt::CompoundTag>(value)) {
                    self[key] = value.cast<nbt::CompoundTag>();
                } else if (py::isinstance<py::dict>(value)) {
                    self[key] = makeNativeTag(value);
                } else {
                    throw py::type_error("Value must be a CompoundTag or dict");
                }
            },
            py::arg("key"),
            py::arg("value"),
            "Set a CompoundTag value (or dict that will be converted)"
        )
        .def(
            "set_list",
            [](nbt::CompoundTag& self, std::string key, py::object const& value) {
                if (py::isinstance<nbt::ListTag>(value)) {
                    self[key] = value.cast<nbt::ListTag>();
                } else if (py::isinstance<py::list>(value)) {
                    self[key] = makeNativeTag(value);
                } else {
                    throw py::type_error("Value must be a ListTag or list/tuple");
                }
            },
            py::arg("key"),
            py::arg("value"),
            "Set a ListTag value (or list/tuple that will be converted)"
        )

        .def(
            "get_byte_tag",
            [](nbt::CompoundTag& self, std::string_view key) -> nbt::ByteTag* {
                if (!self.contains(key)) { throw py::key_error("tag not exist"); }
                if (!self.at(key).hold(nbt::Tag::Type::Byte)) { throw py::type_error("tag not hold a ByteTag"); }
                return self.getByte(key);
            },
            py::return_value_policy::reference_internal,
            py::arg("key"),
            "Get ByteTag\nThrow KeyError if not found or TypeError if wrong type"
        )
        .def(
            "get_short_tag",
            [](nbt::CompoundTag& self, std::string_view key) -> nbt::ShortTag* {
                if (!self.contains(key)) { throw py::key_error("tag not exist"); }
                if (!self.at(key).hold(nbt::Tag::Type::Short)) { throw py::type_error("tag not hold a ShortTag"); }
                return self.getShort(key);
            },
            py::return_value_policy::reference_internal,
            py::arg("key"),
            "Get ShortTag\nThrow KeyError if not found or TypeError if wrong type"
        )
        .def(
            "get_int_tag",
            [](nbt::CompoundTag& self, std::string_view key) -> nbt::IntTag* {
                if (!self.contains(key)) { throw py::key_error("tag not exist"); }
                if (!self.at(key).hold(nbt::Tag::Type::Int)) { throw py::type_error("tag not hold a IntTag"); }
                return self.getInt(key);
            },
            py::return_value_policy::reference_internal,
            py::arg("key"),
            "Get IntTag\nThrow KeyError if not found or TypeError if wrong type"
        )
        .def(
            "get_long_tag",
            [](nbt::CompoundTag& self, std::string_view key) -> nbt::LongTag* {
                if (!self.contains(key)) { throw py::key_error("tag not exist"); }
                if (!self.at(key).hold(nbt::Tag::Type::Long)) { throw py::type_error("tag not hold a LongTag"); }
                return self.getLong(key);
            },
            py::return_value_policy::reference_internal,
            py::arg("key"),
            "Get LongTag\nThrow KeyError if not found or TypeError if wrong type"
        )
        .def(
            "get_float_tag",
            [](nbt::CompoundTag& self, std::string_view key) -> nbt::FloatTag* {
                if (!self.contains(key)) { throw py::key_error("tag not exist"); }
                if (!self.at(key).hold(nbt::Tag::Type::Float)) { throw py::type_error("tag not hold a FloatTag"); }
                return self.getFloat(key);
            },
            py::return_value_policy::reference_internal,
            py::arg("key"),
            "Get FloatTag\nThrow KeyError if not found or TypeError if wrong type"
        )
        .def(
            "get_double_tag",
            [](nbt::CompoundTag& self, std::string_view key) -> nbt::DoubleTag* {
                if (!self.contains(key)) { throw py::key_error("tag not exist"); }
                if (!self.at(key).hold(nbt::Tag::Type::Double)) { throw py::type_error("tag not hold a DoubleTag"); }
                return self.getDouble(key);
            },
            py::return_value_policy::reference_internal,
            py::arg("key"),
            "Get DoubleTag\nThrow KeyError if not found or TypeError if wrong type"
        )
        .def(
            "get_string_tag",
            [](nbt::CompoundTag& self, std::string_view key) -> nbt::StringTag* {
                if (!self.contains(key)) { throw py::key_error("tag not exist"); }
                if (!self.at(key).hold(nbt::Tag::Type::String)) { throw py::type_error("tag not hold a StringTag"); }
                return self.getString(key);
            },
            py::return_value_policy::reference_internal,
            py::arg("key"),
            "Get StringTag\nThrow KeyError if not found or TypeError if wrong type"
        )
        .def(
            "get_byte_array_tag",
            [](nbt::CompoundTag& self, std::string_view key) -> nbt::ByteArrayTag* {
                if (!self.contains(key)) { throw py::key_error("tag not exist"); }
                if (!self.at(key).hold(nbt::Tag::Type::ByteArray)) {
                    throw py::type_error("tag not hold a ByteArrayTag");
                }
                return self.getByteArray(key);
            },
            py::return_value_policy::reference_internal,
            py::arg("key"),
            "Get ByteArrayTag\nThrow KeyError if not found or TypeError if wrong type"
        )
        .def(
            "get_int_array_tag",
            [](nbt::CompoundTag& self, std::string_view key) -> nbt::IntArrayTag* {
                if (!self.contains(key)) { throw py::key_error("tag not exist"); }
                if (!self.at(key).hold(nbt::Tag::Type::IntArray)) {
                    throw py::type_error("tag not hold a IntArrayTag");
                }
                return self.getIntArray(key);
            },
            py::return_value_policy::reference_internal,
            py::arg("key"),
            "Get IntArrayTag\nThrow KeyError if not found or TypeError if wrong type"
        )
        .def(
            "get_long_array_tag",
            [](nbt::CompoundTag& self, std::string_view key) -> nbt::LongArrayTag* {
                if (!self.contains(key)) { throw py::key_error("tag not exist"); }
                if (!self.at(key).hold(nbt::Tag::Type::LongArray)) {
                    throw py::type_error("tag not hold a LongArrayTag");
                }
                return self.getLongArray(key);
            },
            py::return_value_policy::reference_internal,
            py::arg("key"),
            "Get LongArrayTag\nThrow KeyError if not found or TypeError if wrong type"
        )
        .def(
            "get_compound_tag",
            [](nbt::CompoundTag& self, std::string_view key) -> nbt::CompoundTag* {
                if (!self.contains(key)) { throw py::key_error("tag not exist"); }
                if (!self.at(key).hold(nbt::Tag::Type::Compound)) {
                    throw py::type_error("tag not hold a CompoundTag");
                }
                return self.getCompound(key);
            },
            py::return_value_policy::reference_internal,
            py::arg("key"),
            "Get CompoundTag\nThrow KeyError if not found or TypeError if wrong type"
        )
        .def(
            "get_list_tag",
            [](nbt::CompoundTag& self, std::string_view key) -> nbt::ListTag* {
                if (!self.contains(key)) { throw py::key_error("tag not exist"); }
                if (!self.at(key).hold(nbt::Tag::Type::List)) { throw py::type_error("tag not hold a ListTag"); }
                return self.getList(key);
            },
            py::return_value_policy::reference_internal,
            py::arg("key"),
            "Get ListTag\nThrow KeyError if not found or TypeError if wrong type"
        )

        .def(
            "get_byte",
            [](nbt::CompoundTag& self, std::string_view key) -> uint8_t {
                if (!self.contains(key)) { throw py::key_error("tag not exist"); }
                if (!self.at(key).hold(nbt::Tag::Type::Byte)) { throw py::type_error("tag not hold a ByteTag"); }
                return self.at(key).as<nbt::ByteTag>().storage();
            },
            py::arg("key"),
            "Get byte value\nThrow KeyError if not found or TypeError if wrong type"
        )
        .def(
            "get_short",
            [](nbt::CompoundTag& self, std::string_view key) -> short {
                if (!self.contains(key)) { throw py::key_error("tag not exist"); }
                if (!self.at(key).hold(nbt::Tag::Type::Short)) { throw py::type_error("tag not hold a ShortTag"); }
                return self.at(key).as<nbt::ShortTag>().storage();
            },
            py::arg("key"),
            "Get short value\nThrow KeyError if not found or TypeError if wrong type"
        )
        .def(
            "get_int",
            [](nbt::CompoundTag& self, std::string_view key) -> int {
                if (!self.contains(key)) { throw py::key_error("tag not exist"); }
                if (!self.at(key).hold(nbt::Tag::Type::Int)) { throw py::type_error("tag not hold a IntTag"); }
                return self.at(key).as<nbt::IntTag>().storage();
            },
            py::arg("key"),
            "Get int value\nThrow KeyError if not found or TypeError if wrong type"
        )
        .def(
            "get_long",
            [](nbt::CompoundTag& self, std::string_view key) -> int64_t {
                if (!self.contains(key)) { throw py::key_error("tag not exist"); }
                if (!self.at(key).hold(nbt::Tag::Type::Long)) { throw py::type_error("tag not hold a LongTag"); }
                return self.at(key).as<nbt::LongTag>().storage();
            },
            py::arg("key"),
            "Get long value\nThrow KeyError if not found or TypeError if wrong type"
        )
        .def(
            "get_float",
            [](nbt::CompoundTag& self, std::string_view key) -> float {
                if (!self.contains(key)) { throw py::key_error("tag not exist"); }
                if (!self.at(key).hold(nbt::Tag::Type::Float)) { throw py::type_error("tag not hold a FloatTag"); }
                return self.at(key).as<nbt::FloatTag>().storage();
            },
            py::arg("key"),
            "Get float value\nThrow KeyError if not found or TypeError if wrong type"
        )
        .def(
            "get_double",
            [](nbt::CompoundTag& self, std::string_view key) -> double {
                if (!self.contains(key)) { throw py::key_error("tag not exist"); }
                if (!self.at(key).hold(nbt::Tag::Type::Double)) { throw py::type_error("tag not hold a DoubleTag"); }
                return self.at(key).as<nbt::DoubleTag>().storage();
            },
            py::arg("key"),
            "Get double value\nThrow KeyError if not found or TypeError if wrong type"
        )
        .def(
            "get_string",
            [](nbt::CompoundTag& self, std::string_view key) -> std::string {
                if (!self.contains(key)) { throw py::key_error("tag not exist"); }
                if (!self.at(key).hold(nbt::Tag::Type::String)) { throw py::type_error("tag not hold a StringTag"); }
                return self.at(key).as<nbt::StringTag>().storage();
            },
            py::arg("key"),
            "Get string value\nThrow KeyError if not found or TypeError if wrong type"
        )
        .def(
            "get_byte_array",
            [](nbt::CompoundTag& self, std::string_view key) -> py::bytes {
                if (!self.contains(key)) { throw py::key_error("tag not exist"); }
                if (!self.at(key).hold(nbt::Tag::Type::ByteArray)) {
                    throw py::type_error("tag not hold a ByteArrayTag");
                }
                return to_pybytes(static_cast<std::string_view>(self.at(key).as<nbt::ByteArrayTag>()));
            },
            py::arg("key"),
            "Get byte array\nThrow KeyError if not found or TypeError if wrong type"
        )
        .def(
            "get_int_array",
            [](nbt::CompoundTag& self, std::string_view key) -> std::vector<int> {
                if (!self.contains(key)) { throw py::key_error("tag not exist"); }
                if (!self.at(key).hold(nbt::Tag::Type::IntArray)) {
                    throw py::type_error("tag not hold a IntArrayTag");
                }
                return self.at(key).as<nbt::IntArrayTag>().storage();
            },
            py::arg("key"),
            "Get int array\nThrow KeyError if not found or TypeError if wrong type"
        )
        .def(
            "get_long_array",
            [](nbt::CompoundTag& self, std::string_view key) -> std::vector<int64_t> {
                if (!self.contains(key)) { throw py::key_error("tag not exist"); }
                if (!self.at(key).hold(nbt::Tag::Type::LongArray)) {
                    throw py::type_error("tag not hold a LongArrayTag");
                }
                return self.at(key).as<nbt::LongArrayTag>().storage();
            },
            py::arg("key"),
            "Get long array\nThrow KeyError if not found or TypeError if wrong type"
        )
        .def(
            "get_compound",
            [](nbt::CompoundTag& self, std::string_view key) -> py::dict {
                if (!self.contains(key)) { throw py::key_error("tag not exist"); }
                if (!self.at(key).hold(nbt::Tag::Type::Compound)) {
                    throw py::type_error("tag not hold a CompoundTag");
                }
                py::dict result;
                for (auto& [k, v] : self.at(key).as<nbt::CompoundTag>()) { result[py::str(k)] = py::cast(v); }
                return result;
            },
            py::arg("key"),
            "Get CompoundTag\nThrow KeyError if not found or TypeError if wrong type"
        )
        .def(
            "get_list",
            [](nbt::CompoundTag& self, std::string_view key) -> py::list {
                if (!self.contains(key)) { throw py::key_error("tag not exist"); }
                if (!self.at(key).hold(nbt::Tag::Type::List)) { throw py::type_error("tag not hold a ListTag"); }
                py::list result;
                for (auto& tag : self.at(key).as<nbt::ListTag>()) {
                    result.append(py::cast(nbt::CompoundTagVariant(*tag)));
                }
                return result;
            },
            py::arg("key"),
            "Get ListTag\nThrow KeyError if not found or TypeError if wrong type"
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
            [](nbt::CompoundTag const& self) { return to_pybytes(self.toNetworkNbt()); },
            "Serialize to Network NBT format (used in Minecraft networking)"
        )
        .def(
            "to_binary_nbt",
            [](nbt::CompoundTag const& self, bool little_endian, bool header) {
                if (header) {
                    return to_pybytes(self.toBinaryNbtWithHeader(little_endian));
                } else {
                    return to_pybytes(self.toBinaryNbt(little_endian));
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
                    if (py::isinstance<nbt::CompoundTagVariant>(val)) {
                        self[key] = *val.cast<nbt::CompoundTagVariant*>();
                    } else if (py::isinstance<nbt::Tag>(val)) {
                        self.put(key, val.cast<nbt::Tag*>()->copy());
                    } else {
                        self.put(key, makeNativeTag(val));
                    }
                }
            },
            "Access the dict value of this tag"
        )

        .def_static(
            "from_network_nbt",
            [](py::buffer value) { return nbt::CompoundTag::fromNetworkNbt(to_cppstringview(value)); },
            py::arg("binary_data"),
            "Deserialize from Network NBT format"
        )
        .def_static(
            "from_binary_nbt",
            [](py::buffer value, bool little_endian, bool header) {
                if (header) {
                    return nbt::CompoundTag::fromBinaryNbtWithHeader(to_cppstringview(value), little_endian);
                } else {
                    return nbt::CompoundTag::fromBinaryNbt(to_cppstringview(value), little_endian);
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