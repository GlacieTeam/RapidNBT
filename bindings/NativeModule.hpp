// Copyright © 2025 GlacieTeam.All rights reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
//
// SPDX-License-Identifier: MPL-2.0

#pragma once
#include <format>
#include <magic_enum/magic_enum.hpp>
#include <nbt/NBT.hpp>
#include <pybind11/buffer_info.h>
#include <pybind11/functional.h>
#include <pybind11/native_enum.h>
#include <pybind11/numpy.h>
#include <pybind11/operators.h>
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/stl/filesystem.h>

namespace py = pybind11;

namespace rapidnbt {

#define ADDRESS reinterpret_cast<uintptr_t>(&self), 2 * sizeof(uintptr_t)
#define ENUM(x) magic_enum::enum_name(x)

inline py::bytes to_py_bytes(std::string_view sv) { return py::bytes(sv.data(), sv.size()); }

inline std::string_view to_cpp_stringview(py::buffer const& buf) {
    py::buffer_info info = buf.request();
    return std::string_view(static_cast<const char*>(info.ptr), info.size);
}

template <std::integral T>
inline T to_cpp_int(py::int_ const& value, std::string_view typeName) {
    using UT = std::make_unsigned<T>::type;
    using ST = std::make_signed<T>::type;
    if (value >= py::int_(0)) {
        if (value >= py::int_(std::numeric_limits<UT>::min()) && value <= py::int_(std::numeric_limits<UT>::max())) { return value.cast<UT>(); }
    } else {
        if (value >= py::int_(std::numeric_limits<ST>::min()) && value <= py::int_(std::numeric_limits<ST>::max())) { return value.cast<ST>(); }
    }
    throw py::value_error(
        std::format(
            "Integer out of range for {0}, received value: {1}, "
            "expected value range: {2}(signed min) ~ {3}(unsigned max)",
            typeName,
            py::str(static_cast<py::object>(value)).cast<std::string>(),
            std::numeric_limits<ST>::min(),
            std::numeric_limits<UT>::max()
        )
    );
}

inline std::string py_type_name(py::object const& obj) {
    auto typeName   = py::type::handle_of(obj).attr("__name__").cast<std::string>();
    auto typeModule = py::type::handle_of(obj).attr("__module__").cast<std::string>();
    if (typeModule.starts_with("rapidnbt._NBT")) {
        typeModule = "rapidnbt";
    } else if (typeModule == "builtins") {
        typeModule.clear();
    }
    if (!typeModule.empty()) { typeName = std::format("{}.{}", typeModule, typeName); }
    return typeName;
}

std::unique_ptr<nbt::Tag> makeNativeTag(py::object const& obj);

void bindEnums(py::module& m);
void bindCompoundTagVariant(py::module& m);
void bindTag(py::module& m);
void bindEndTag(py::module& m);
void bindByteTag(py::module& m);
void bindShortTag(py::module& m);
void bindIntTag(py::module& m);
void bindLongTag(py::module& m);
void bindFloatTag(py::module& m);
void bindDoubleTag(py::module& m);
void bindByteArrayTag(py::module& m);
void bindStringTag(py::module& m);
void bindListTag(py::module& m);
void bindCompoundTag(py::module& m);
void bindIntArrayTag(py::module& m);
void bindLongArrayTag(py::module& m);
void bindNbtIO(py::module& m);
void bindNbtFile(py::module& m);

} // namespace rapidnbt