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
        return std::make_unique<nbt::IntTag>(obj.cast<int>());
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
            if (py::isinstance<nbt::Tag>(value)) {
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
            if (py::isinstance<nbt::Tag>(value)) {
                tag->push_back(value.cast<nbt::Tag*>()->copy());
            } else {
                tag->push_back(makeNativeTag(value));
            }
        }
        return tag;
    } else if (py::isinstance<nbt::CompoundTagVariant>(obj)) {
        return obj.cast<nbt::CompoundTagVariant>().toUniqueCopy();
    }
    auto ctypes = py::module::import("ctypes");
    if (py::isinstance(obj, ctypes.attr("c_int8")) || py::isinstance(obj, ctypes.attr("c_uint8"))) {
        return std::make_unique<nbt::ByteTag>(obj.attr("value").cast<uint8_t>());
    } else if (py::isinstance(obj, ctypes.attr("c_int16")) || py::isinstance(obj, ctypes.attr("c_uint16"))) {
        return std::make_unique<nbt::ShortTag>(obj.attr("value").cast<short>());
    } else if (py::isinstance(obj, ctypes.attr("c_int32")) || py::isinstance(obj, ctypes.attr("c_uint32"))) {
        return std::make_unique<nbt::IntTag>(obj.attr("value").cast<int>());
    } else if (py::isinstance(obj, ctypes.attr("c_int64")) || py::isinstance(obj, ctypes.attr("c_uint64"))) {
        return std::make_unique<nbt::Int64Tag>(obj.attr("value").cast<int64_t>());
    } else if (py::isinstance(obj, ctypes.attr("c_float"))) {
        return std::make_unique<nbt::FloatTag>(obj.attr("value").cast<float>());
    } else if (py::isinstance(obj, ctypes.attr("c_double"))) {
        return std::make_unique<nbt::DoubleTag>(obj.attr("value").cast<double>());
    }
    return nullptr;
}

void bindCompoundTagVariant(py::module& m) {
    auto sm = m.def_submodule("compound_tag_variant");

    py::class_<nbt::CompoundTagVariant>(sm, "CompoundTagVariant")
        .def(py::init<>())
        .def(py::init([](py::object const& obj) {
            if (py::isinstance<nbt::Tag>(obj)) {
                return std::make_unique<nbt::CompoundTagVariant>(*obj.cast<nbt::Tag*>());
            } else {
                return std::make_unique<nbt::CompoundTagVariant>(makeNativeTag(obj));
            }
        }))

        .def("get_type", &nbt::CompoundTagVariant::getType)
        .def("hold", [](nbt::CompoundTagVariant const& self, nbt::Tag::Type type) -> bool { return self.hold(type); })

        .def("is_array", &nbt::CompoundTagVariant::is_array)
        .def("is_binary", &nbt::CompoundTagVariant::is_binary)
        .def("is_boolean", &nbt::CompoundTagVariant::is_boolean)
        .def("is_null", &nbt::CompoundTagVariant::is_null)
        .def("is_number_float", &nbt::CompoundTagVariant::is_number_float)
        .def("is_number_integer", &nbt::CompoundTagVariant::is_number_integer)
        .def("is_object", &nbt::CompoundTagVariant::is_object)
        .def("is_string", &nbt::CompoundTagVariant::is_string)
        .def("is_number", &nbt::CompoundTagVariant::is_number)
        .def("is_primitive", &nbt::CompoundTagVariant::is_primitive)
        .def("is_structured", &nbt::CompoundTagVariant::is_structured)

        .def("size", &nbt::CompoundTagVariant::size)
        .def(
            "contains",
            [](nbt::CompoundTagVariant& self, std::string_view index) -> bool { return self.contains(index); },
            py::arg("index"),
            "Check if the value is in the CompoundTag.\nThrow TypeError is not hold a CompoundTag."
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
            py::return_value_policy::reference_internal,
            "Get value by object key"
        )
        .def(
            "__getitem__",
            [](nbt::CompoundTagVariant& self, std::string_view index) -> nbt::CompoundTagVariant& {
                return self[index];
            },
            py::return_value_policy::reference_internal,
            "Get value by array index"
        )

        .def(
            "__setitem__",
            [](nbt::CompoundTagVariant& self, std::string_view key, py::object const& obj) {
                if (py::isinstance<nbt::Tag>(obj)) {
                    self[key] = *obj.cast<nbt::Tag*>();
                } else {
                    self[key] = makeNativeTag(obj);
                }
            },
            "Set value by object key"
        )
        .def(
            "__setitem__",
            [](nbt::CompoundTagVariant& self, size_t index, py::object const& obj) {
                if (py::isinstance<nbt::Tag>(obj)) {
                    self[index] = *obj.cast<nbt::Tag*>();
                } else {
                    self[index] = *makeNativeTag(obj);
                }
            },
            "Set value by array index"
        )

        .def("pop", py::overload_cast<std::string_view>(&nbt::CompoundTagVariant::remove))
        .def("pop", py::overload_cast<size_t>(&nbt::CompoundTagVariant::remove))
        .def("rename", &nbt::CompoundTagVariant::rename)
        .def(
            "append",
            [](nbt::CompoundTagVariant& self, py::object const& obj) {
                if (py::isinstance<nbt::Tag>(obj)) {
                    self.push_back(*obj.cast<nbt::Tag*>());
                } else {
                    self.push_back(makeNativeTag(obj));
                }
            }
        )
        .def(
            "assign",
            [](nbt::CompoundTagVariant& self, py::object const& obj) {
                if (py::isinstance<nbt::Tag>(obj)) {
                    self = *obj.cast<nbt::Tag*>();
                } else {
                    self = makeNativeTag(obj);
                }
            }
        )

        .def(
            "__iter__",
            [](nbt::CompoundTagVariant& self) { return py::make_iterator(self.begin(), self.end()); },
            py::keep_alive<0, 1>()
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
            }
        )

        .def(
            "to_snbt",
            &nbt::CompoundTagVariant::toSnbt,
            py::arg("snbt_format") = nbt::SnbtFormat::Default,
            py::arg("indent")      = 4
        )
        .def("to_json", &nbt::CompoundTagVariant::toJson, py::arg("indent") = 4)

        .def("merge", &nbt::CompoundTagVariant::merge, py::arg("other"), py::arg("merge_list") = false)
        .def("copy", &nbt::CompoundTagVariant::toUniqueCopy)

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
            "as_int64_tag",
            [](nbt::CompoundTagVariant& self) -> nbt::Int64Tag& {
                if (!self.hold(nbt::Tag::Type::Int64)) { throw py::type_error("tag not hold an Int64Tag"); }
                return self.as<nbt::Int64Tag>();
            },
            py::return_value_policy::reference_internal,
            "Convert to a Int64Tag\nThrow TypeError if wrong type"
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
            }
        )
        .def(
            "get_short",
            [](nbt::CompoundTagVariant& self) -> short {
                if (!self.hold(nbt::Tag::Type::Short)) { throw py::type_error("tag not hold a ShortTag"); }
                return self.as<nbt::ShortTag>().storage();
            }
        )
        .def(
            "get_int",
            [](nbt::CompoundTagVariant& self) -> int {
                if (!self.hold(nbt::Tag::Type::Int)) { throw py::type_error("tag not hold an IntTag"); }
                return self.as<nbt::IntTag>().storage();
            }
        )
        .def(
            "get_int64",
            [](nbt::CompoundTagVariant& self) -> int64_t {
                if (!self.hold(nbt::Tag::Type::Int64)) { throw py::type_error("tag not hold an Int64Tag"); }
                return self.as<nbt::Int64Tag>().storage();
            }
        )
        .def(
            "get_float",
            [](nbt::CompoundTagVariant& self) -> float {
                if (!self.hold(nbt::Tag::Type::Float)) { throw py::type_error("tag not hold a FloatTag"); }
                return self.as<nbt::FloatTag>().storage();
            }
        )
        .def(
            "get_double",
            [](nbt::CompoundTagVariant& self) -> double {
                if (!self.hold(nbt::Tag::Type::Double)) { throw py::type_error("tag not hold a DoubleTag"); }
                return self.as<nbt::DoubleTag>().storage();
            }
        )
        .def(
            "get_byte_array",
            [](nbt::CompoundTagVariant& self) -> py::bytes {
                if (!self.hold(nbt::Tag::Type::ByteArray)) { throw py::type_error("tag not hold a ByteArrayTag"); }
                return to_pybytes(static_cast<std::string_view>(self.as<nbt::ByteArrayTag>()));
            }
        )
        .def(
            "get_string",
            [](nbt::CompoundTagVariant& self) -> std::string {
                if (!self.hold(nbt::Tag::Type::String)) { throw py::type_error("tag not hold a StringTag"); }
                return self.as<nbt::StringTag>().storage();
            }
        )
        .def(
            "get_compound",
            [](nbt::CompoundTagVariant& self) -> py::dict {
                if (!self.hold(nbt::Tag::Type::Compound)) { throw py::type_error("tag not hold a CompoundTag"); }
                py::dict result;
                for (auto& [key, value] : self.as<nbt::CompoundTag>()) { result[py::str(key)] = py::cast(value); }
                return result;
            }
        )
        .def(
            "get_list",
            [](nbt::CompoundTagVariant& self) -> py::list {
                if (!self.hold(nbt::Tag::Type::List)) { throw py::type_error("tag not hold a ListTag"); }
                py::list result;
                for (auto& tag : self.as<nbt::ListTag>()) { result.append(py::cast(nbt::CompoundTagVariant(*tag))); }
                return result;
            }
        )
        .def(
            "get_int_array",
            [](nbt::CompoundTagVariant& self) -> std::vector<int> {
                if (!self.hold(nbt::Tag::Type::IntArray)) { throw py::type_error("tag not hold an IntArrayTag"); }
                return self.as<nbt::IntArrayTag>().storage();
            }
        )
        .def(
            "get_long_array",
            [](nbt::CompoundTagVariant& self) -> std::vector<int64_t> {
                if (!self.hold(nbt::Tag::Type::LongArray)) { throw py::type_error("tag not hold a LongArrayTag"); }
                return self.as<nbt::LongArrayTag>().storage();
            }
        )

        .def_property(
            "value",
            [](nbt::CompoundTagVariant& self) -> nbt::CompoundTagVariant::TagVariant { return self.mStorage; },
            [](nbt::CompoundTagVariant& self, nbt::CompoundTagVariant::TagVariant const& value) {
                self.mStorage = value;
            },
            "Access the tag variant"
        )

        .def("__int__", [](nbt::CompoundTagVariant const& self) { return static_cast<int64_t>(self); })
        .def("__float__", [](nbt::CompoundTagVariant const& self) { return static_cast<double>(self); })
        .def(
            "__eq__",
            [](nbt::CompoundTagVariant const& self, nbt::CompoundTagVariant const& other) { return self == other; }
        )
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
