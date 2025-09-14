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
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/stl/filesystem.h>

namespace py = pybind11;

namespace rapidnbt {

constexpr auto ADDRESS_LENGTH = 2 * sizeof(uintptr_t);

inline py::bytes        to_pybytes(std::string_view sv) { return py::bytes(sv.data(), sv.size()); }
inline py::bytes        to_pybytes(std::string const& s) { return py::bytes(s); }
inline std::string_view to_cppstringview(py::buffer buffer) {
    py::buffer_info info = buffer.request();
    const char*     data = static_cast<const char*>(info.ptr);
    size_t          size = info.size;
    return std::string_view(data, size);
}

std::unique_ptr<nbt::Tag> makeNativeTag(py::object const& obj);

void bindEnums(py::module& m);
void bindCompoundTagVariant(py::module& m);
void bindTag(py::module& m);
void bindEndTag(py::module& m);
void bindByteTag(py::module& m);
void bindShortTag(py::module& m);
void bindIntTag(py::module& m);
void bindInt64Tag(py::module& m);
void bindFloatTag(py::module& m);
void bindDoubleTag(py::module& m);
void bindByteArrayTag(py::module& m);
void bindStringTag(py::module& m);
void bindListTag(py::module& m);
void bindCompoundTag(py::module& m);
void bindIntArrayTag(py::module& m);
void bindLongArrayTag(py::module& m);
void bindNbtIO(py::module& m);

} // namespace rapidnbt