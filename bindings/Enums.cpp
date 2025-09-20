// Copyright © 2025 GlacieTeam.All rights reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
//
// SPDX-License-Identifier: MPL-2.0

#include "NativeModule.hpp"

namespace py = pybind11;

namespace rapidnbt {

void bindEnums(py::module& m) {
    {
        auto sm = m.def_submodule("tag_type");

        py::enum_<nbt::Tag::Type>(sm, "TagType")
            .value("End", nbt::Tag::Type::End)
            .value("Byte", nbt::Tag::Type::Byte)
            .value("Short", nbt::Tag::Type::Short)
            .value("Int", nbt::Tag::Type::Int)
            .value("Int64", nbt::Tag::Type::Int64)
            .value("Float", nbt::Tag::Type::Float)
            .value("Double", nbt::Tag::Type::Double)
            .value("ByteArray", nbt::Tag::Type::ByteArray)
            .value("String", nbt::Tag::Type::String)
            .value("List", nbt::Tag::Type::List)
            .value("Compound", nbt::Tag::Type::Compound)
            .value("IntArray", nbt::Tag::Type::IntArray)
            .value("LongArray", nbt::Tag::Type::LongArray)
            .export_values();
    }
    {
        auto sm = m.def_submodule("snbt_format");

        py::enum_<nbt::SnbtFormat>(sm, "SnbtFormat", py::arithmetic())
            .value("Minimize", nbt::SnbtFormat::Minimize)
            .value("PrettyFilePrint", nbt::SnbtFormat::PrettyFilePrint)
            .value("ArrayLineFeed", nbt::SnbtFormat::ArrayLineFeed)
            .value("ForceAscii", nbt::SnbtFormat::ForceAscii)
            .value("ForceQuote", nbt::SnbtFormat::ForceQuote)
            .value("CommentMarks", nbt::SnbtFormat::CommentMarks)
            .value("AlwaysLineFeed", nbt::SnbtFormat::AlwaysLineFeed)
            .value("Default", nbt::SnbtFormat::Default)
            .value("Classic", nbt::SnbtFormat::Classic)
            .value("Jsonify", nbt::SnbtFormat::Jsonify)
            .export_values()
            .def("__or__", [](nbt::SnbtFormat lhs, nbt::SnbtFormat rhs) { return lhs | rhs; });
    }
}

} // namespace rapidnbt