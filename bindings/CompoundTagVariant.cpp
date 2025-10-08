// Copyright © 2025 GlacieTeam.All rights reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
//
// SPDX-License-Identifier: MPL-2.0

#include "NativeModule.hpp"

namespace rapidnbt {

std::unique_ptr<nbt::Tag> makeNativeTag(py::object const& obj) {
    if (py::isinstance<py::bool_>(obj)) {
        return std::make_unique<nbt::ByteTag>(obj.cast<uint8_t>());
    } else if (py::isinstance<py::int_>(obj)) {
        return std::make_unique<nbt::IntTag>(to_cpp_int<int>(obj, "IntTag"));
    } else if (py::isinstance<py::str>(obj)) {
        return std::make_unique<nbt::StringTag>(obj.cast<std::string>());
    } else if (py::isinstance<py::float_>(obj)) {
        return std::make_unique<nbt::FloatTag>(obj.cast<float>());
    } else if (py::isinstance<py::bytes>(obj) || py::isinstance<py::bytearray>(obj)) {
        return std::make_unique<nbt::ByteArrayTag>(nbt::ByteArrayTag(obj.cast<std::string>()));
    } else if (py::isinstance<py::dict>(obj)) {
        auto dict = obj.cast<py::dict>();
        auto tag  = std::make_unique<nbt::CompoundTag>();
        for (auto [k, v] : dict) {
            auto  key   = py::cast<std::string>(k);
            auto& value = static_cast<py::object&>(v);
            if (py::isinstance<nbt::CompoundTagVariant>(value)) {
                (*tag)[key] = *value.cast<nbt::CompoundTagVariant*>();
            } else if (py::isinstance<nbt::Tag>(value)) {
                tag->put(key, value.cast<nbt::Tag*>()->copy());
            } else {
                tag->put(key, makeNativeTag(value));
            }
        }
        return tag;
    } else if (py::isinstance<py::list>(obj)) {
        auto list = obj.cast<py::list>();
        auto tag  = std::make_unique<nbt::ListTag>();
        for (auto t : list) {
            auto& value = static_cast<py::object&>(t);
            auto  type  = tag->getElementType();
            if (auto val = makeListTagElement(value)) {
                if (type == val->getType() || type == nbt::Tag::Type::End) {
                    tag->push_back(*val);
                } else {
                    throw py::value_error(
                        std::format(
                            "Value for ListTag requires values in the list can convert to a same tag type, "
                            "expected type: TagType.{}",
                            magic_enum::enum_name(type)
                        )
                    );
                }
            } else {
                throw py::value_error("Invalid element for ListTag");
            }
        }
        return tag;
    } else if (py::isinstance<nbt::CompoundTagVariant>(obj)) {
        return obj.cast<nbt::CompoundTagVariant>().toUniqueCopy();
    } else if (py::isinstance<py::none>(obj)) {
        return std::make_unique<nbt::EndTag>();
    }
    auto ctypes = py::module::import("ctypes");
    if (py::isinstance(obj, ctypes.attr("c_int8")) || py::isinstance(obj, ctypes.attr("c_uint8"))) {
        return std::make_unique<nbt::ByteTag>(obj.attr("value").cast<uint8_t>());
    } else if (py::isinstance(obj, ctypes.attr("c_int16")) || py::isinstance(obj, ctypes.attr("c_uint16"))) {
        return std::make_unique<nbt::ShortTag>(obj.attr("value").cast<short>());
    } else if (py::isinstance(obj, ctypes.attr("c_int32")) || py::isinstance(obj, ctypes.attr("c_uint32"))) {
        return std::make_unique<nbt::IntTag>(obj.attr("value").cast<int>());
    } else if (py::isinstance(obj, ctypes.attr("c_int64")) || py::isinstance(obj, ctypes.attr("c_uint64"))) {
        return std::make_unique<nbt::LongTag>(obj.attr("value").cast<int64_t>());
    } else if (py::isinstance(obj, ctypes.attr("c_float"))) {
        return std::make_unique<nbt::FloatTag>(obj.attr("value").cast<float>());
    } else if (py::isinstance(obj, ctypes.attr("c_double"))) {
        return std::make_unique<nbt::DoubleTag>(obj.attr("value").cast<double>());
    }
    py::str typeName = py::type::handle_of(obj).attr("__name__");
    throw py::type_error(
        std::format("Invalid tag type: couldn't convert {} instance to any tag type", typeName.cast<std::string>())
    );
}

void bindCompoundTagVariant(py::module& m) {
    auto sm = m.def_submodule("compound_tag_variant", "A warpper of all tags, to provide morden API for NBT");

    py::class_<nbt::CompoundTagVariant>(sm, "CompoundTagVariant")
        .def(py::init<>(), "Default Constructor")
        .def(
            py::init([](py::object const& obj) {
                if (py::isinstance<nbt::CompoundTagVariant>(obj)) {
                    return std::make_unique<nbt::CompoundTagVariant>(*obj.cast<nbt::CompoundTagVariant*>());
                } else if (py::isinstance<nbt::Tag>(obj)) {
                    return std::make_unique<nbt::CompoundTagVariant>(*obj.cast<nbt::Tag*>());
                } else {
                    return std::make_unique<nbt::CompoundTagVariant>(makeNativeTag(obj));
                }
            }),
            py::arg("value"),
            "Construct from any Python object"
        )

        .def("get_type", &nbt::CompoundTagVariant::getType, "Get the NBT type ID")
        .def(
            "hold",
            [](nbt::CompoundTagVariant const& self, nbt::Tag::Type type) -> bool { return self.hold(type); },
            py::arg("type"),
            "Check the NBT type ID"
        )

        .def("is_array", &nbt::CompoundTagVariant::is_array, "Check whether the tag is a ListTag")
        .def(
            "is_binary",
            &nbt::CompoundTagVariant::is_binary,
            "Check whether the tag is a binary tag",
            "Example:",
            "    ByteArrayTag, IntArrayTag, LongArrayTag"
        )
        .def("is_boolean", &nbt::CompoundTagVariant::is_boolean, "Check whether the tag is a ByteTag")
        .def("is_null", &nbt::CompoundTagVariant::is_null, "Check whether the tag is an EndTag")
        .def(
            "is_number_float",
            &nbt::CompoundTagVariant::is_number_float,
            "Check whether the tag is a float number based tag",
            "Example:",
            "    FloatTag, DoubleTag"
        )
        .def(
            "is_number_integer",
            &nbt::CompoundTagVariant::is_number_integer,
            "Check whether the tag is a integer number based tag",
            "Example:",
            "    ByteTag, ShortTag, IntTag, LongTag"
        )
        .def("is_object", &nbt::CompoundTagVariant::is_object, "Check whether the tag is a CompoundTag")
        .def("is_string", &nbt::CompoundTagVariant::is_string, "Check whether the tag is a StringTag")
        .def(
            "is_number",
            &nbt::CompoundTagVariant::is_number,
            "Check whether the tag is a number based tag",
            "Example:",
            "    FloatTag, DoubleTag, ByteTag, ShortTag, IntTag, LongTag"
        )
        .def(
            "is_primitive",
            &nbt::CompoundTagVariant::is_primitive,
            "Check whether the tag is a primitive tag",
            "Example:",
            "    ByteTag, ShortTag, IntTag, LongTag, FloatTag, DoubleTag, StringTag, ByteArrayTag, IntArrayTag, "
            "LongArrayTag"
        )
        .def(
            "is_structured",
            &nbt::CompoundTagVariant::is_structured,
            "Check whether the tag is a structured tag",
            "Example:",
            "    CompoundTag, ListTag"
        )

        .def("size", &nbt::CompoundTagVariant::size, "Get the size of the tag")
        .def(
            "clear",
            &nbt::CompoundTagVariant::clear,
            "Clear the data in the tag\nThrow TypeError if the tag can not be cleared."
        )
        .def(
            "contains",
            [](nbt::CompoundTagVariant& self, std::string_view index) -> bool { return self.contains(index); },
            py::arg("index"),
            "Check if the value is in the CompoundTag.\nThrow TypeError is not hold a CompoundTag."
        )
        .def(
            "contains",
            [](nbt::CompoundTagVariant& self, std::string_view index, nbt::Tag::Type type) -> bool {
                return self.contains(index, type);
            },
            py::arg("index"),
            py::arg("type"),
            "Check if the value is in the CompoundTag and value type is the specific type.\nThrow TypeError is not "
            "hold a CompoundTag."
        )

        .def(
            "__contains__",
            [](nbt::CompoundTagVariant& self, std::string_view index) -> bool { return self.contains(index); },
            py::arg("index"),
            "Check if the value is in the CompoundTag.\nThrow TypeError is not hold a CompoundTag."
        )
        .def(
            "__getitem__",
            [](nbt::CompoundTagVariant& self, size_t index) -> nbt::Tag& { return self[index]; },
            py::arg("index"),
            py::return_value_policy::reference_internal,
            "Get value by object key"
        )
        .def(
            "__getitem__",
            [](nbt::CompoundTagVariant& self, std::string_view index) -> nbt::CompoundTagVariant& {
                return self[index];
            },
            py::arg("index"),
            py::return_value_policy::reference_internal,
            "Get value by array index"
        )

        .def(
            "__setitem__",
            [](nbt::CompoundTagVariant& self, std::string_view key, py::object const& obj) {
                if (py::isinstance<nbt::CompoundTagVariant>(obj)) {
                    self[key] = *obj.cast<nbt::CompoundTagVariant*>();
                } else if (py::isinstance<nbt::Tag>(obj)) {
                    self[key] = *obj.cast<nbt::Tag*>();
                } else {
                    self[key] = makeNativeTag(obj);
                }
            },
            py::arg("index"),
            py::arg("value"),
            "Set value by object key"
        )
        .def(
            "__setitem__",
            [](nbt::CompoundTagVariant& self, size_t index, py::object const& obj) {
                if (py::isinstance<nbt::CompoundTagVariant>(obj)) {
                    self[index] = *obj.cast<nbt::CompoundTagVariant*>();
                } else if (py::isinstance<nbt::Tag>(obj)) {
                    self[index] = *obj.cast<nbt::Tag*>();
                } else {
                    self[index] = *makeNativeTag(obj);
                }
            },
            py::arg("index"),
            py::arg("value"),
            "Set value by array index"
        )

        .def(
            "pop",
            [](nbt::CompoundTagVariant& self, std::string_view index) {
                if (!self.is_object()) { throw py::type_error("tag not hold an object"); }
                return self.remove(index);
            },
            py::arg("index"),
            "Remove key from the CompoundTag",
            "Throw TypeError if wrong type"
        )
        .def(
            "pop",
            [](nbt::CompoundTagVariant& self, size_t index) {
                if (!self.is_array()) { throw py::type_error("tag not hold an array"); }
                return self.remove(index);
            },
            py::arg("index"),
            "Rname a key in the CompoundTag",
            "Throw TypeError if wrong type"
        )
        .def(
            "rename",
            &nbt::CompoundTagVariant::rename,
            "Remove key from the CompoundTag",
            "Throw TypeError if wrong type",
            py::arg("index"),
            py::arg("new_name"),
            "Rename a key in the CompoundTag\nThrow TypeError if wrong type"
        )
        .def(
            "append",
            [](nbt::CompoundTagVariant& self, py::object const& obj) {
                if (self.is_null()) { self = nbt::ListTag(); }
                if (self.hold(nbt::Tag::Type::List)) {
                    auto type = self.as<nbt::ListTag>().getElementType();
                    if (auto tag = makeListTagElement(obj)) {
                        if (type == tag->getType() || type == nbt::Tag::Type::End) {
                            self.push_back(*tag);
                        } else {
                            throw py::value_error(
                                std::format(
                                    "New tag type must be same as the original element type in the ListTag, expected "
                                    "type: TagType.{}",
                                    magic_enum::enum_name(type)
                                )
                            );
                        }
                    } else {
                        throw py::value_error("Invalid element for ListTag");
                    }
                } else {
                    throw py::type_error("tag not hold an array");
                }
            },
            py::arg("value"),
            "Append a Tag element if self is ListTag\nThrow TypeError if wrong type"
        )
        .def(
            "assign",
            [](nbt::CompoundTagVariant& self, py::object const& obj) {
                if (py::isinstance<nbt::CompoundTagVariant>(obj)) {
                    self = *obj.cast<nbt::CompoundTagVariant*>();
                } else if (py::isinstance<nbt::Tag>(obj)) {
                    self = nbt::CompoundTagVariant(*obj.cast<nbt::Tag*>());
                } else {
                    self = makeNativeTag(obj);
                }
            },
            py::arg("value"),
            "Assign value"
        )

        .def(
            "__iter__",
            [](nbt::CompoundTagVariant& self) { return py::make_iterator(self.begin(), self.end()); },
            py::keep_alive<0, 1>(),
            "Iterate over tags in the tag variant"
        )
        .def(
            "items",
            [](nbt::CompoundTagVariant& self) {
                if (!self.hold(nbt::Tag::Type::Compound)) { throw py::type_error("tag not hold an object!"); }
                py::list items;
                for (auto& [key, value] : self.as<nbt::CompoundTag>()) {
                    items.append(py::make_tuple(key, py::cast(value)));
                }
                return items;
            },
            "Get list of (key, value) pairs in this tag\nThrow TypeError if wrong type"
        )

        .def(
            "to_snbt",
            &nbt::CompoundTagVariant::toSnbt,
            py::arg("snbt_format") = nbt::SnbtFormat::Default,
            py::arg("indent")      = 4,
            "Convert tag to SNBT string"
        )
        .def("to_json", &nbt::CompoundTagVariant::toJson, py::arg("indent") = 4, "Convert tag to JSON string")

        .def(
            "merge",
            &nbt::CompoundTagVariant::merge,
            py::arg("other"),
            py::arg("merge_list") = false,
            "Merge another CompoundTag into this one",
            "",
            "Arguments:",
            "    other: CompoundTag to merge from",
            "    merge_list: If true, merge list contents instead of replacing"
        )
        .def("copy", &nbt::CompoundTagVariant::toUniqueCopy, "Create a deep copy of this tag")

        .def(
            "as_byte_tag",
            [](nbt::CompoundTagVariant& self) -> nbt::ByteTag& {
                if (!self.hold(nbt::Tag::Type::Byte)) { throw py::type_error("tag not hold a ByteTag"); }
                return self.as<nbt::ByteTag>();
            },
            py::return_value_policy::reference_internal,
            "Convert to a ByteTag\nThrow TypeError if wrong type"
        )
        .def(
            "as_short_tag",
            [](nbt::CompoundTagVariant& self) -> nbt::ShortTag& {
                if (!self.hold(nbt::Tag::Type::Short)) { throw py::type_error("tag not hold a ShortTag"); }
                return self.as<nbt::ShortTag>();
            },
            py::return_value_policy::reference_internal,
            "Convert to a ShortTag\nThrow TypeError if wrong type"
        )
        .def(
            "as_int_tag",
            [](nbt::CompoundTagVariant& self) -> nbt::IntTag& {
                if (!self.hold(nbt::Tag::Type::Int)) { throw py::type_error("tag not hold an IntTag"); }
                return self.as<nbt::IntTag>();
            },
            py::return_value_policy::reference_internal,
            "Convert to a IntTag\nThrow TypeError if wrong type"
        )
        .def(
            "as_long_tag",
            [](nbt::CompoundTagVariant& self) -> nbt::LongTag& {
                if (!self.hold(nbt::Tag::Type::Long)) { throw py::type_error("tag not hold an LongTag"); }
                return self.as<nbt::LongTag>();
            },
            py::return_value_policy::reference_internal,
            "Convert to a LongTag\nThrow TypeError if wrong type"
        )
        .def(
            "as_float_tag",
            [](nbt::CompoundTagVariant& self) -> nbt::FloatTag& {
                if (!self.hold(nbt::Tag::Type::Float)) { throw py::type_error("tag not hold a FloatTag"); }
                return self.as<nbt::FloatTag>();
            },
            py::return_value_policy::reference_internal,
            "Convert to a FloatTag\nThrow TypeError if wrong type"
        )
        .def(
            "as_double_tag",
            [](nbt::CompoundTagVariant& self) -> nbt::DoubleTag& {
                if (!self.hold(nbt::Tag::Type::Double)) { throw py::type_error("tag not hold a DoubleTag"); }
                return self.as<nbt::DoubleTag>();
            },
            py::return_value_policy::reference_internal,
            "Convert to a DoubleTag\nThrow TypeError if wrong type"
        )
        .def(
            "as_byte_array_tag",
            [](nbt::CompoundTagVariant& self) -> nbt::ByteArrayTag& {
                if (!self.hold(nbt::Tag::Type::ByteArray)) { throw py::type_error("tag not hold a ByteArrayTag"); }
                return self.as<nbt::ByteArrayTag>();
            },
            py::return_value_policy::reference_internal,
            "Convert to a ByteArrayTag\nThrow TypeError if wrong type"
        )
        .def(
            "as_string_tag",
            [](nbt::CompoundTagVariant& self) -> nbt::StringTag& {
                if (!self.hold(nbt::Tag::Type::String)) { throw py::type_error("tag not hold a StringTag"); }
                return self.as<nbt::StringTag>();
            },
            py::return_value_policy::reference_internal,
            "Convert to a StringTag\nThrow TypeError if wrong type"
        )
        .def(
            "as_compound_tag",
            [](nbt::CompoundTagVariant& self) -> nbt::CompoundTag& {
                if (!self.hold(nbt::Tag::Type::Compound)) { throw py::type_error("tag not hold a CompoundTag"); }
                return self.as<nbt::CompoundTag>();
            },
            py::return_value_policy::reference_internal,
            "Convert to a CompoundTag\nThrow TypeError if wrong type"
        )
        .def(
            "as_list_tag",
            [](nbt::CompoundTagVariant& self) -> nbt::ListTag& {
                if (!self.hold(nbt::Tag::Type::List)) { throw py::type_error("tag not hold a ListTag"); }
                return self.as<nbt::ListTag>();
            },
            py::return_value_policy::reference_internal,
            "Convert to a ListTag\nThrow TypeError if wrong type"
        )
        .def(
            "as_int_array_tag",
            [](nbt::CompoundTagVariant& self) -> nbt::IntArrayTag& {
                if (!self.hold(nbt::Tag::Type::IntArray)) { throw py::type_error("tag not hold an IntArrayTag"); }
                return self.as<nbt::IntArrayTag>();
            },
            py::return_value_policy::reference_internal,
            "Convert to a IntArrayTag\nThrow TypeError if wrong type"
        )
        .def(
            "as_long_array_tag",
            [](nbt::CompoundTagVariant& self) -> nbt::LongArrayTag& {
                if (!self.hold(nbt::Tag::Type::LongArray)) { throw py::type_error("tag not hold a LongArrayTag"); }
                return self.as<nbt::LongArrayTag>();
            },
            py::return_value_policy::reference_internal,
            "Convert to a LongArrayTag\nThrow TypeError if wrong type"
        )

        .def(
            "get_byte",
            [](nbt::CompoundTagVariant& self) -> uint8_t {
                if (!self.hold(nbt::Tag::Type::Byte)) { throw py::type_error("tag not hold a ByteTag"); }
                return self.as<nbt::ByteTag>().storage();
            },
            "Get the byte value\nThrow TypeError if wrong type"
        )
        .def(
            "get_short",
            [](nbt::CompoundTagVariant& self) -> short {
                if (!self.hold(nbt::Tag::Type::Short)) { throw py::type_error("tag not hold a ShortTag"); }
                return self.as<nbt::ShortTag>().storage();
            },
            "Get the short value\nThrow TypeError if wrong type"
        )
        .def(
            "get_int",
            [](nbt::CompoundTagVariant& self) -> int {
                if (!self.hold(nbt::Tag::Type::Int)) { throw py::type_error("tag not hold an IntTag"); }
                return self.as<nbt::IntTag>().storage();
            },
            "Get the int value\nThrow TypeError if wrong type"
        )
        .def(
            "get_long",
            [](nbt::CompoundTagVariant& self) -> int64_t {
                if (!self.hold(nbt::Tag::Type::Long)) { throw py::type_error("tag not hold an LongTag"); }
                return self.as<nbt::LongTag>().storage();
            },
            "Get the int64 value\nThrow TypeError if wrong type"
        )
        .def(
            "get_float",
            [](nbt::CompoundTagVariant& self) -> float {
                if (!self.hold(nbt::Tag::Type::Float)) { throw py::type_error("tag not hold a FloatTag"); }
                return self.as<nbt::FloatTag>().storage();
            },
            "Get the float value\nThrow TypeError if wrong type"
        )
        .def(
            "get_double",
            [](nbt::CompoundTagVariant& self) -> double {
                if (!self.hold(nbt::Tag::Type::Double)) { throw py::type_error("tag not hold a DoubleTag"); }
                return self.as<nbt::DoubleTag>().storage();
            },
            "Get the double value\nThrow TypeError if wrong type"
        )
        .def(
            "get_byte_array",
            [](nbt::CompoundTagVariant& self) -> py::bytes {
                if (!self.hold(nbt::Tag::Type::ByteArray)) { throw py::type_error("tag not hold a ByteArrayTag"); }
                return to_pybytes(static_cast<std::string_view>(self.as<nbt::ByteArrayTag>()));
            },
            "Get the byte array value\nThrow TypeError if wrong type"
        )
        .def(
            "get_string",
            [](nbt::CompoundTagVariant& self) -> std::string {
                if (!self.hold(nbt::Tag::Type::String)) { throw py::type_error("tag not hold a StringTag"); }
                return self.as<nbt::StringTag>().storage();
            },
            "Get the string value\nThrow TypeError if wrong type"
        )
        .def(
            "get_bytes",
            [](nbt::CompoundTagVariant& self) -> py::bytes {
                if (!self.hold(nbt::Tag::Type::String)) { throw py::type_error("tag not hold a StringTag"); }
                return to_pybytes(self.as<nbt::StringTag>().storage());
            },
            "Get the original string value (bytes in StringTag)\nThrow TypeError if wrong type"
        )
        .def(
            "get_compound",
            [](nbt::CompoundTagVariant& self) -> py::dict {
                if (!self.hold(nbt::Tag::Type::Compound)) { throw py::type_error("tag not hold a CompoundTag"); }
                py::dict result;
                for (auto& [key, value] : self.as<nbt::CompoundTag>()) { result[py::str(key)] = py::cast(value); }
                return result;
            },
            "Get the CompoundTag as a dict value\nThrow TypeError if wrong type"
        )
        .def(
            "get_list",
            [](nbt::CompoundTagVariant& self) -> py::list {
                if (!self.hold(nbt::Tag::Type::List)) { throw py::type_error("tag not hold a ListTag"); }
                py::list result;
                for (auto& tag : self.as<nbt::ListTag>()) { result.append(py::cast(nbt::CompoundTagVariant(*tag))); }
                return result;
            },
            "Get the ListTag as a list value\nThrow TypeError if wrong type"
        )
        .def(
            "get_int_array",
            [](nbt::CompoundTagVariant& self) -> std::vector<int> {
                if (!self.hold(nbt::Tag::Type::IntArray)) { throw py::type_error("tag not hold an IntArrayTag"); }
                return self.as<nbt::IntArrayTag>().storage();
            },
            "Get the int array value\nThrow TypeError if wrong type"
        )
        .def(
            "get_long_array",
            [](nbt::CompoundTagVariant& self) -> std::vector<int64_t> {
                if (!self.hold(nbt::Tag::Type::LongArray)) { throw py::type_error("tag not hold a LongArrayTag"); }
                return self.as<nbt::LongArrayTag>().storage();
            },
            "Get the long array value\nThrow TypeError if wrong type"
        )

        .def(
            "get",
            [](nbt::CompoundTagVariant& self) -> nbt::CompoundTagVariant::TagVariant { return self.mStorage; },
            "Get the tag variant"
        )
        .def_property(
            "value",
            [](nbt::CompoundTagVariant& self) -> py::object {
                return std::visit(
                    [](auto& value) {
                        using T = std::decay_t<decltype(value)>;
                        if constexpr (std::is_same_v<T, nbt::CompoundTag>) {
                            py::dict result;
                            for (auto& [key, val] : value) { result[py::str(key)] = py::cast(val); }
                            return static_cast<py::object>(result);
                        } else if constexpr (std::is_same_v<T, nbt::ListTag>) {
                            py::list result;
                            for (auto& tag : value) { result.append(py::cast(nbt::CompoundTagVariant(*tag))); }
                            return static_cast<py::object>(result);
                        } else if constexpr (std::is_same_v<T, nbt::StringTag>) {
                            return static_cast<py::object>(to_pybytes(value.storage()));
                        } else if constexpr (requires { value.storage(); }) {
                            return py::cast(value.storage());
                        } else if constexpr (std::is_same_v<T, nbt::EndTag>) {
                            return static_cast<py::object>(py::none());
                        }
                    },
                    self.mStorage
                );
            },
            [](nbt::CompoundTagVariant& self, py::object const& value) {
                std::visit(
                    [&](auto& val) {
                        if constexpr (requires { val.storage(); }) {
                            using T      = std::decay_t<decltype(val.storage())>;
                            auto tagName = std::format("{}Tag", magic_enum::enum_name(val.getType()));
                            if constexpr (std::is_integral_v<T>) {
                                if (py::isinstance<py::int_>(value)) {
                                    val.storage() = to_cpp_int<T>(value, tagName);
                                } else {
                                    throw py::value_error(std::format("Value for {} must be a int", tagName));
                                }
                            } else if constexpr (std::is_floating_point_v<T>) {
                                if (py::isinstance<py::float_>(value)) {
                                    val.storage() = static_cast<T>(value.cast<double>());
                                } else {
                                    throw py::value_error(std::format("Value for {} must be a float", tagName));
                                }
                            } else if constexpr (std::is_same_v<T, std::string>) {
                                if (py::isinstance<py::bytes>(value) || py::isinstance<py::bytearray>(value)
                                    || py::isinstance<py::str>(value)) {
                                    val.storage() = value.cast<std::string>();
                                } else {
                                    throw py::value_error("Value for StringTag must be a str, bytes or bytearray");
                                }
                            } else if constexpr (std::is_same_v<std::decay_t<decltype(val)>, nbt::ListTag>) {
                                if (py::isinstance<py::list>(value)) {
                                    auto list = value.cast<py::list>();
                                    auto tag  = nbt::ListTag();
                                    for (auto t : list) {
                                        auto& e = static_cast<py::object&>(t);
                                        if (auto ele = makeListTagElement(e)) {
                                            auto type = tag.getElementType();
                                            if (type == ele->getType() || type == nbt::Tag::Type::End) {
                                                tag.push_back(*ele);
                                            } else {
                                                throw py::value_error(
                                                    std::format(
                                                        "New tag type must be same as the original element type in the "
                                                        "ListTag , expected type: TagType.{}",
                                                        magic_enum::enum_name(type)
                                                    )
                                                );
                                            }
                                        } else {
                                            throw py::value_error("Invalid element for ListTag");
                                        }
                                    }
                                    val = std::move(tag);
                                } else {
                                    throw py::value_error("Value for ListTag must be a List[Any]");
                                }
                            } else {
                                try {
                                    val.storage() = value.cast<T>();
                                } catch (...) {
                                    throw py::value_error(std::format("Value for {} must be a List[int]", tagName));
                                }
                            }
                        } else if constexpr (std::is_same_v<std::decay_t<decltype(val)>, nbt::EndTag>) {
                            throw py::value_error("Value of EndTag is always None");
                        } else if constexpr (std::is_same_v<std::decay_t<decltype(val)>, nbt::CompoundTag>) {
                            if (py::isinstance<py::dict>(value)) {
                                auto dict = value.cast<py::dict>();
                                auto tag  = nbt::CompoundTag();
                                for (auto [k, v] : dict) {
                                    auto  key = py::cast<std::string>(k);
                                    auto& ele = static_cast<py::object&>(v);
                                    if (py::isinstance<nbt::CompoundTagVariant>(ele)) {
                                        tag[key] = *ele.cast<nbt::CompoundTagVariant*>();
                                    } else if (py::isinstance<nbt::Tag>(ele)) {
                                        tag.put(key, ele.cast<nbt::Tag*>()->copy());
                                    } else {
                                        tag.put(key, makeNativeTag(ele));
                                    }
                                }
                                val = std::move(tag);
                            } else {
                                throw py::value_error("Value for CompoundTag must be a Dict[str, Any]");
                            }
                        }
                    },
                    self.mStorage
                );
            },
            "Access the tag value"
        )

        .def(
            "__int__",
            [](nbt::CompoundTagVariant const& self) { return static_cast<int64_t>(self); },
            "Implicitly convert to int"
        )
        .def(
            "__float__",
            [](nbt::CompoundTagVariant const& self) { return static_cast<double>(self); },
            "Implicitly convert to float"
        )
        .def(
            "__eq__",
            [](nbt::CompoundTagVariant const& self, nbt::CompoundTagVariant const& other) { return self == other; },
            py::arg("other"),
            "Check if this tag equals another tag"
        )
        .def("__len__", &nbt::CompoundTagVariant::size, "Get the size of the tag")
        .def(
            "__str__",
            [](nbt::CompoundTagVariant const& self) { return self.toSnbt(nbt::SnbtFormat::Minimize); },
            "String representation (SNBT minimized format)"
        )
        .def(
            "__repr__",
            [](nbt::CompoundTagVariant const& self) {
                return std::format(
                    "<rapidnbt.CompoundTagVatiant(type={0}) object at 0x{1:0{2}X}>",
                    magic_enum::enum_name(self.getType()),
                    reinterpret_cast<uintptr_t>(&self),
                    ADDRESS_LENGTH
                );
            },
            "Official string representation"
        );
}

} // namespace rapidnbt
