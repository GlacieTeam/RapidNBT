// Copyright © 2025 GlacieTeam.All rights reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
//
// SPDX-License-Identifier: MPL-2.0

#include "NativeModule.hpp"

namespace rapidnbt {

namespace {

py::module& get_ctypes() {
    static auto instance = py::module::import("ctypes");
    return instance;
}

bool is_cint8(py::object const& obj) {
    return py::isinstance(obj, get_ctypes().attr("c_int8")) || py::isinstance(obj, get_ctypes().attr("c_uint8"))
        || py::isinstance<py::bool_>(obj);
}

bool is_cint16(py::object const& obj) {
    return py::isinstance(obj, get_ctypes().attr("c_int16")) || py::isinstance(obj, get_ctypes().attr("c_uint16"));
}

bool is_cint32(py::object const& obj) {
    return py::isinstance(obj, get_ctypes().attr("c_int32")) || py::isinstance(obj, get_ctypes().attr("c_uint32"))
        || (py::isinstance<py::int_>(obj) && !py::isinstance<py::bool_>(obj));
}

bool is_cint64(py::object const& obj) {
    return py::isinstance(obj, get_ctypes().attr("c_int64")) || py::isinstance(obj, get_ctypes().attr("c_uint64"));
}

bool is_cfloat(py::object const& obj) {
    return py::isinstance(obj, get_ctypes().attr("c_float")) || py::isinstance<py::float_>(obj);
}

bool is_cdouble(py::object const& obj) { return py::isinstance(obj, get_ctypes().attr("c_double")); }

} // namespace


void bind_compound_tag_variant(py::module& m) {
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

    // 构造函数绑定
    variant.def(py::init<>())
        .def(py::init([](py::object const& obj) {
            if (is_cint8(obj)) {
                return new nbt::CompoundTagVariant(obj.cast<uint8_t>());
            } else if (is_cint16(obj)) {
                return new nbt::CompoundTagVariant(obj.cast<short>());
            } else if (is_cint32(obj)) {
                return new nbt::CompoundTagVariant(obj.cast<int>());
            } else if (is_cint64(obj)) {
                return new nbt::CompoundTagVariant(obj.cast<int64_t>());
            } else if (is_cfloat(obj)) {
                return new nbt::CompoundTagVariant(obj.cast<float>());
            } else if (is_cdouble(obj)) {
                return new nbt::CompoundTagVariant(obj.cast<double>());
            } else if (py::isinstance<py::str>(obj)) {
                return new nbt::CompoundTagVariant(obj.cast<std::string>());
            } else if (py::isinstance<py::bytes>(obj) || py::isinstance<py::bytearray>(obj)) {
                return new nbt::CompoundTagVariant(nbt::ByteArrayTag(obj.cast<std::string>()));
            } else if (py::isinstance<py::dict>(obj)) {
                //
            } else if (py::isinstance<py::list>(obj)) {
                //
            } else {
                return new nbt::CompoundTagVariant(nullptr);
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
            [](nbt::CompoundTagVariant& self) -> nbt::CompoundTag::TagMap& { return self.items(); },
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

        .def("__int__", [](nbt::CompoundTagVariant const& self) { return static_cast<int64_t>(self); })
        .def("__float__", [](nbt::CompoundTagVariant const& self) { return static_cast<double>(self); })
        .def(
            "as_string",
            [](nbt::CompoundTagVariant& self) -> std::string& { return static_cast<std::string&>(self); },
            py::return_value_policy::reference_internal
        )
        .def(
            "as_byte_array",
            [](nbt::CompoundTagVariant& self) -> py::bytes {
                return to_pybytes(static_cast<std::string_view>(self.as<nbt::ByteArrayTag>()));
            }
        )
        .def(
            "as_int_array",
            [](nbt::CompoundTagVariant& self) -> std::vector<int32_t>& {
                return static_cast<std::vector<int32_t>&>(self);
            },
            py::return_value_policy::reference_internal
        )
        .def(
            "as_long_array",
            [](nbt::CompoundTagVariant& self) -> std::vector<int64_t>& {
                return static_cast<std::vector<int64_t>&>(self);
            },
            py::return_value_policy::reference_internal
        )
        .def(
            "__eq__",
            [](nbt::CompoundTagVariant const& self, nbt::CompoundTagVariant const& other) { return self == other; }
        )

        .def_static(
            "object",
            &nbt::CompoundTagVariant::object,
            py::arg("init") = std::initializer_list<nbt::CompoundTag::TagMap::value_type>{}
        )
        .def_static(
            "array",
            &nbt::CompoundTagVariant::array,
            py::arg("init") = std::initializer_list<nbt::CompoundTagVariant>{}
        )
        .def_static(
            "parse",
            &nbt::CompoundTagVariant::parse,
            py::arg("snbt"),
            py::arg("parsed_length") = std::optional<size_t>{}
        );
}

} // namespace rapidnbt


/*
// 绑定常量迭代器 (仅声明)
py::class_<nbt::CompoundTagVariant::const_iterator>(variant, "ConstIterator")
    .def(
        "__iter__",
        [](nbt::CompoundTagVariant::const_iterator& it) -> nbt::CompoundTagVariant::const_iterator& { return it; }
    )
    .def(
        "__next__",
        [](nbt::CompoundTagVariant::const_iterator& it) -> const nbt::Tag& {
            if (it == nbt::CompoundTagVariant::const_iterator()) throw py::stop_iteration();
            const nbt::Tag& value = *it;
            ++it;
            return value;
        },
        py::return_value_policy::reference_internal
    );
*/