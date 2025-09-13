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

namespace py = pybind11;

namespace rapidnbt {

inline py::bytes to_pybytes(std::string_view sv) { return py::bytes(sv.data(), sv.size()); }
inline py::bytes to_pybytes(std::string const& s) { return py::bytes(s); }

void bindEnums(py::module& m);
void bindCompoundTagVariant(py::module& m);
void bindTag(py::module& m);
void bindEndTag(py::module& m);

} // namespace rapidnbt