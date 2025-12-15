// Copyright © 2025 GlacieTeam.All rights reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
//
// SPDX-License-Identifier: MPL-2.0

#include "NativeModule.hpp"

namespace rapidnbt {

std::unique_ptr<nbt::Tag> makeNativeTag(py::object const& obj) {
    if (py::isinstance<nbt::CompoundTagVariant>(obj)) {
        return obj.cast<nbt::CompoundTagVariant>().toUniqueCopy();
    } else if (py::isinstance<nbt::Tag>(obj)) {
        return obj.cast<nbt::Tag*>()->copy();
    } else if (py::isinstance<py::bool_>(obj)) {
        return std::make_unique<nbt::ByteTag>(obj.cast<uint8_t>());
    } else if (py::isinstance<py::int_>(obj)) {
        return std::make_unique<nbt::IntTag>(to_cpp_int<int>(obj, "IntTag"));
    } else if (py::isinstance<py::str>(obj)) {
        return std::make_unique<nbt::StringTag>(obj.cast<std::string>());
    } else if (py::isinstance<py::float_>(obj)) {
        return std::make_unique<nbt::FloatTag>(obj.cast<float>());
    } else if (py::isinstance<py::bytes>(obj) || py::isinstance<py::bytearray>(obj)) {
        return std::make_unique<nbt::ByteArrayTag>(nbt::ByteArrayTag(to_cpp_stringview(obj)));
    } else if (py::isinstance<py::dict>(obj)) {
        auto dict = obj.cast<py::dict>();
        auto tag  = std::make_unique<nbt::CompoundTag>();
        for (auto [k, v] : dict) {
            auto  key   = py::cast<std::string>(k);
            auto& value = static_cast<py::object&>(v);
            tag->set(key, makeNativeTag(value));
        }
        return tag;
    } else if (py::isinstance<py::list>(obj) || py::isinstance<py::tuple>(obj) || py::isinstance<py::array>(obj)) {
        auto list = obj.cast<std::vector<py::object>>();
        auto tag  = std::make_unique<nbt::ListTag>();
        for (auto t : list) {
            auto& value = static_cast<py::object&>(t);
            auto  type  = tag->getElementType();
            if (auto val = makeNativeTag(value)) {
                if (type == val->getType() || type == nbt::Tag::Type::End) {
                    tag->push_back(*val);
                } else {
                    throw py::value_error(
                        std::format(
                            "Value for ListTag[{1}] requires values in the list can be converted to a same tag type, "
                            "received type: {0}, expected types can be converted to {1}Tag",
                            py_type_name(value),
                            magic_enum::enum_name(type)
                        )
                    );
                }
            } else {
                throw py::value_error("Invalid element for ListTag");
            }
        }
        return tag;
    } else if (py::isinstance<py::none>(obj)) {
        return std::make_unique<nbt::EndTag>();
    }
    auto ctypes = py::module::import("ctypes");
    if (py::isinstance(obj, ctypes.attr("c_int8")) || py::isinstance(obj, ctypes.attr("c_uint8"))) {
        return std::make_unique<nbt::ByteTag>(to_cpp_int<uint8_t>(obj.attr("value").cast<py::int_>(), "ByteTag"));
    } else if (py::isinstance(obj, ctypes.attr("c_int16")) || py::isinstance(obj, ctypes.attr("c_uint16"))) {
        return std::make_unique<nbt::ShortTag>(to_cpp_int<short>(obj.attr("value").cast<py::int_>(), "ShortTag"));
    } else if (py::isinstance(obj, ctypes.attr("c_int32")) || py::isinstance(obj, ctypes.attr("c_uint32"))) {
        return std::make_unique<nbt::IntTag>(to_cpp_int<int>(obj.attr("value").cast<py::int_>(), "IntTag"));
    } else if (py::isinstance(obj, ctypes.attr("c_int64")) || py::isinstance(obj, ctypes.attr("c_uint64"))) {
        return std::make_unique<nbt::LongTag>(to_cpp_int<int64_t>(obj.attr("value").cast<py::int_>(), "LongTag"));
    } else if (py::isinstance(obj, ctypes.attr("c_float"))) {
        return std::make_unique<nbt::FloatTag>(obj.attr("value").cast<float>());
    } else if (py::isinstance(obj, ctypes.attr("c_double"))) {
        return std::make_unique<nbt::DoubleTag>(obj.attr("value").cast<double>());
    }
    throw py::type_error(
        std::format("Invalid tag type: couldn't convert {} instance to any tag type", py_type_name(obj))
    );
}

void bindCompoundTagVariant(py::module& m) {
    auto sm = m.def_submodule("compound_tag_variant", "A warpper of all tags, to provide morden API for NBT");

    py::class_<nbt::CompoundTagVariant>(sm, "CompoundTagVariant")
        .def(py::init<>(), "Default Constructor")
        .def(
            py::init([](py::object const& obj) {
                return std::make_unique<nbt::CompoundTagVariant>(makeNativeTag(obj));
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
        .def("hash", &nbt::CompoundTagVariant::hash, "Get the hash of the tag")
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
            [](nbt::CompoundTagVariant& self, size_t index) -> nbt::CompoundTagVariant& { return self[index]; },
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
                self[key] = makeNativeTag(obj);
            },
            py::arg("index"),
            py::arg("value"),
            "Set value by object key"
        )
        .def(
            "__setitem__",
            [](nbt::CompoundTagVariant& self, size_t index, py::object const& obj) {
                self[index] = makeNativeTag(obj);
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
                    if (auto tag = makeNativeTag(obj)) {
                        if (type == tag->getType() || type == nbt::Tag::Type::End) {
                            self.push_back(*tag);
                        } else {
                            throw py::value_error(
                                std::format(
                                    "New tag type must be same as the original element type in the ListTag[{1}], "
                                    "received type: {0}, expected types can be converted to {1}Tag",
                                    py_type_name(obj),
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
            [](nbt::CompoundTagVariant& self, py::object const& obj) { self = makeNativeTag(obj); },
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
            py::arg("snbt_format")   = nbt::SnbtFormat::Default,
            py::arg("indent")        = 4,
            py::arg("number_format") = nbt::SnbtNumberFormat::Default,
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
            "as_tag",
            [](nbt::CompoundTagVariant& self) -> nbt::Tag& { return *self; },
            py::return_value_policy::reference_internal,
            "Convert to a Tag"
        )

        .def(
            "get_byte",
            [](nbt::CompoundTagVariant& self, bool isSigned) -> uint8_t {
                if (!self.hold(nbt::Tag::Type::Byte)) { throw py::type_error("tag not hold a ByteTag"); }
                return isSigned ? static_cast<int8_t>(self.as<nbt::ByteTag>().storage())
                                : self.as<nbt::ByteTag>().storage();
            },
            py::arg("signed") = false,
            "Get the byte value\nThrow TypeError if wrong type"
        )
        .def(
            "get_short",
            [](nbt::CompoundTagVariant& self, bool isSigned) -> short {
                if (!self.hold(nbt::Tag::Type::Short)) { throw py::type_error("tag not hold a ShortTag"); }
                return isSigned ? self.as<nbt::ShortTag>().storage()
                                : static_cast<uint16_t>(self.as<nbt::ShortTag>().storage());
            },
            py::arg("signed") = true,
            "Get the short value\nThrow TypeError if wrong type"
        )
        .def(
            "get_int",
            [](nbt::CompoundTagVariant& self, bool isSigned) -> int {
                if (!self.hold(nbt::Tag::Type::Int)) { throw py::type_error("tag not hold an IntTag"); }
                return isSigned ? self.as<nbt::IntTag>().storage()
                                : static_cast<uint32_t>(self.as<nbt::IntTag>().storage());
            },
            py::arg("signed") = true,
            "Get the int value\nThrow TypeError if wrong type"
        )
        .def(
            "get_long",
            [](nbt::CompoundTagVariant& self, bool isSigned) -> int64_t {
                if (!self.hold(nbt::Tag::Type::Long)) { throw py::type_error("tag not hold a LongTag"); }
                return isSigned ? self.as<nbt::LongTag>().storage()
                                : static_cast<uint64_t>(self.as<nbt::LongTag>().storage());
            },
            py::arg("signed") = true,
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
                return to_py_bytes(self.as<nbt::ByteArrayTag>());
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
                return to_py_bytes(self.as<nbt::StringTag>().storage());
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
                for (auto& tag : self.as<nbt::ListTag>()) { result.append(py::cast(tag)); }
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
            "write",
            [](nbt::CompoundTagVariant& self, bstream::BinaryStream& stream) { self.write(stream); },
            py::arg("stream"),
            "Write tag to a binary stream"
        )
        .def(
            "load",
            [](nbt::CompoundTagVariant& self, bstream::ReadOnlyBinaryStream& stream) { self.load(stream); },
            py::arg("stream"),
            "Load tag value from a binary stream"
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
                            for (auto& tag : value) { result.append(py::cast(tag)); }
                            return static_cast<py::object>(result);
                        } else if constexpr (std::is_same_v<T, nbt::StringTag>) {
                            return static_cast<py::object>(to_py_bytes(value.storage()));
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
                                    throw py::value_error(std::format("Value of {} must be an int", tagName));
                                }
                            } else if constexpr (std::is_floating_point_v<T>) {
                                if (py::isinstance<py::float_>(value)) {
                                    val.storage() = static_cast<T>(value.cast<double>());
                                } else {
                                    throw py::value_error(std::format("Value of {} must be a float", tagName));
                                }
                            } else if constexpr (std::is_same_v<T, std::string>) {
                                if (py::isinstance<py::bytes>(value) || py::isinstance<py::bytearray>(value)
                                    || py::isinstance<py::str>(value)) {
                                    val.storage() = value.cast<std::string>();
                                } else {
                                    throw py::value_error("Value of StringTag must be a str, bytes or bytearray");
                                }
                            } else if constexpr (std::is_same_v<std::decay_t<decltype(val)>, nbt::ListTag>) {
                                if (py::isinstance<py::list>(value)) {
                                    auto list = value.cast<py::list>();
                                    auto tag  = nbt::ListTag();
                                    for (auto t : list) {
                                        auto& e = static_cast<py::object&>(t);
                                        if (auto ele = makeNativeTag(e)) {
                                            auto type = tag.getElementType();
                                            if (type == ele->getType() || type == nbt::Tag::Type::End) {
                                                tag.push_back(*ele);
                                            } else {
                                                throw py::value_error(
                                                    std::format(
                                                        "New tag type must be same as the original element type in the "
                                                        "ListTag[{1}], received type: {0}, expected types can be "
                                                        "converted to {1}Tag",
                                                        py_type_name(e),
                                                        magic_enum::enum_name(type)
                                                    )
                                                );
                                            }
                                        } else {
                                            throw py::value_error("Invalid element of ListTag");
                                        }
                                    }
                                    val = std::move(tag);
                                } else {
                                    throw py::value_error("Value of ListTag must be a List[Any]");
                                }
                            } else if constexpr (std::is_same_v<std::decay_t<decltype(val)>, nbt::CompoundTag>) {
                                if (py::isinstance<py::dict>(value)) {
                                    auto dict = value.cast<py::dict>();
                                    auto tag  = nbt::CompoundTag();
                                    for (auto [k, v] : dict) {
                                        auto  key = py::cast<std::string>(k);
                                        auto& ele = static_cast<py::object&>(v);
                                        tag.set(key, makeNativeTag(ele));
                                    }
                                    val = std::move(tag);
                                } else {
                                    throw py::value_error("Value of CompoundTag must be a Dict[str, Any]");
                                }
                            } else {
                                try {
                                    val.storage() = value.cast<T>();
                                } catch (...) {
                                    throw py::value_error(std::format("Value of {} must be a List[int]", tagName));
                                }
                            }
                        } else {
                            self = makeNativeTag(value);
                        }
                    },
                    self.mStorage
                );
            },
            "Access the tag value"
        )

        .def(
            "__int__",
            [](nbt::CompoundTagVariant const& self) {
                if (self.is_number_integer()) { return static_cast<int64_t>(self); }
                throw py::type_error("Tag not hold an integer");
            },
            "Implicitly convert to int"
        )
        .def(
            "__float__",
            [](nbt::CompoundTagVariant const& self) {
                if (self.is_number_float()) { return static_cast<double>(self); }
                throw py::type_error("Tag not hold a floating point number");
            },
            "Implicitly convert to float"
        )
        .def(
            "__bytes__",
            [](nbt::CompoundTagVariant const& self) {
                if (self.hold(nbt::Tag::Type::ByteArray)) { return to_py_bytes(self.as<nbt::ByteArrayTag>()); }
                throw py::type_error("Tag not hold a byte array");
            },
            "Implicitly convert to bytes"
        )
        .def(
            "__eq__",
            [](nbt::CompoundTagVariant const& self, nbt::CompoundTagVariant const& other) { return self == other; },
            py::arg("other"),
            "Check if this tag equals another tag"
        )
        .def("__len__", &nbt::CompoundTagVariant::size, "Get the size of the tag")
        .def("__hash__", &nbt::CompoundTagVariant::hash, "Get the hash of the tag")
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
