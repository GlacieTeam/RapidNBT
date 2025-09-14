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
            std::string key = py::cast<std::string>(k);
            tag->put(key, makeNativeTag(static_cast<py::object&&>(v)));
        }
        return tag;
    } else if (py::isinstance<py::list>(obj)) {
        auto list = obj.cast<py::list>();
        auto tag  = std::make_unique<nbt::ListTag>();
        for (auto t : list) { tag->push_back(makeNativeTag(static_cast<py::object&&>(t))); }
        return tag;
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
    py::class_<nbt::CompoundTagVariant> variant(m, "CompoundTagVariant");

    py::class_<nbt::CompoundTagVariant::iterator>(variant, "Iterator")
        .def("__iter__", [](nbt::CompoundTagVariant::iterator& it) -> nbt::CompoundTagVariant::iterator& { return it; })
        .def(
            "__next__",
            [](nbt::CompoundTagVariant::iterator& it) -> nbt::Tag& {
                if (it == nbt::CompoundTagVariant::iterator()) throw py::stop_iteration();
                nbt::Tag& value = *it;
                ++it;
                return value;
            },
            py::return_value_policy::reference_internal
        );

    variant.def(py::init<>())
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
            [](nbt::CompoundTagVariant& self, std::string_view index) -> bool { return self.contains(index); }
        )

        .def(
            "__getitem__",
            [](nbt::CompoundTagVariant& self, size_t index) -> nbt::Tag& { return self[index]; },
            py::return_value_policy::reference_internal
        )
        .def(
            "__getitem__",
            [](nbt::CompoundTagVariant& self, std::string_view index) -> nbt::CompoundTagVariant& {
                return self[index];
            },
            py::return_value_policy::reference_internal
        )

        // TODO: 隐式构造
        .def(
            "__setitem__",
            [](nbt::CompoundTagVariant& self, std::string_view key, nbt::CompoundTagVariant const& value) {
                self[key] = value;
            }
        )
        .def(
            "__setitem__",
            [](nbt::CompoundTagVariant& self, size_t index, nbt::CompoundTagVariant const& value) {
                self[index] = value;
            }
        )

        .def("remove", py::overload_cast<std::string_view>(&nbt::CompoundTagVariant::remove))
        .def("remove", py::overload_cast<size_t>(&nbt::CompoundTagVariant::remove))
        .def("rename", &nbt::CompoundTagVariant::rename)

        // TODO: 隐式构造
        .def("push_back", py::overload_cast<nbt::CompoundTagVariant>(&nbt::CompoundTagVariant::push_back))
        .def("push_back", py::overload_cast<const nbt::Tag&>(&nbt::CompoundTagVariant::push_back))

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
            },
            py::return_value_policy::reference_internal
        )

        .def(
            "to_snbt",
            &nbt::CompoundTagVariant::toSnbt,
            py::arg("snbt_format") = nbt::SnbtFormat::PrettyFilePrint,
            py::arg("indent")      = 4
        )
        .def("to_json", &nbt::CompoundTagVariant::toJson, py::arg("indent") = 4)

        .def("merge", &nbt::CompoundTagVariant::merge, py::arg("other"), py::arg("merge_list") = false)
        .def("copy", &nbt::CompoundTagVariant::toUniqueCopy)

        .def(
            "as_byte",
            [](nbt::CompoundTagVariant& self) -> nbt::ByteTag& { return self.as<nbt::ByteTag>(); },
            py::return_value_policy::reference_internal
        )
        .def(
            "as_short",
            [](nbt::CompoundTagVariant& self) -> nbt::ShortTag& { return self.as<nbt::ShortTag>(); },
            py::return_value_policy::reference_internal
        )
        .def(
            "as_int",
            [](nbt::CompoundTagVariant& self) -> nbt::IntTag& { return self.as<nbt::IntTag>(); },
            py::return_value_policy::reference_internal
        )
        .def(
            "as_int64",
            [](nbt::CompoundTagVariant& self) -> nbt::Int64Tag& { return self.as<nbt::Int64Tag>(); },
            py::return_value_policy::reference_internal
        )
        .def(
            "as_float",
            [](nbt::CompoundTagVariant& self) -> nbt::FloatTag& { return self.as<nbt::FloatTag>(); },
            py::return_value_policy::reference_internal
        )
        .def(
            "as_double",
            [](nbt::CompoundTagVariant& self) -> nbt::DoubleTag& { return self.as<nbt::DoubleTag>(); },
            py::return_value_policy::reference_internal
        )
        .def(
            "as_byte_array",
            [](nbt::CompoundTagVariant& self) -> nbt::ByteArrayTag& { return self.as<nbt::ByteArrayTag>(); },
            py::return_value_policy::reference_internal
        )
        .def(
            "as_string",
            [](nbt::CompoundTagVariant& self) -> nbt::StringTag& { return self.as<nbt::StringTag>(); },
            py::return_value_policy::reference_internal
        )
        .def(
            "as_compound",
            [](nbt::CompoundTagVariant& self) -> nbt::CompoundTag& { return self.as<nbt::CompoundTag>(); },
            py::return_value_policy::reference_internal
        )
        .def(
            "as_list",
            [](nbt::CompoundTagVariant& self) -> nbt::ListTag& { return self.as<nbt::ListTag>(); },
            py::return_value_policy::reference_internal
        )
        .def(
            "as_int_array",
            [](nbt::CompoundTagVariant& self) -> nbt::IntArrayTag& { return self.as<nbt::IntArrayTag>(); },
            py::return_value_policy::reference_internal
        )
        .def(
            "as_long_array",
            [](nbt::CompoundTagVariant& self) -> nbt::LongArrayTag& { return self.as<nbt::LongArrayTag>(); },
            py::return_value_policy::reference_internal
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
