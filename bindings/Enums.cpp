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

        py::enum_<nbt::Tag::Type>(sm, "TagType", "The tag type enum")
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
        auto sm = m.def_submodule(
            "snbt_format",
            R"(The SNBT format enum
You can use | operation to combime flags
Example:
    format = SnbtFormat.Classic | SnbtFormat.ForceUppercase)"
        );

        py::enum_<nbt::SnbtFormat>(sm, "SnbtFormat", py::arithmetic())
            .value("Minimize", nbt::SnbtFormat::Minimize)
            .value("CompoundLineFeed", nbt::SnbtFormat::CompoundLineFeed)
            .value("ListArrayLineFeed", nbt::SnbtFormat::ListArrayLineFeed)
            .value("BinaryArrayLineFeed", nbt::SnbtFormat::BinaryArrayLineFeed)
            .value("ForceLineFeedIgnoreIndent", nbt::SnbtFormat::ForceLineFeedIgnoreIndent)
            .value("ForceAscii", nbt::SnbtFormat::ForceAscii)
            .value("ForceQuote", nbt::SnbtFormat::ForceQuote)
            .value("ForceUppercase", nbt::SnbtFormat::ForceUppercase)
            .value("CommentMarks", nbt::SnbtFormat::CommentMarks)
            .value("ArrayLineFeed", nbt::SnbtFormat::ArrayLineFeed)
            .value("AlwaysLineFeed", nbt::SnbtFormat::AlwaysLineFeed)
            .value("PrettyFilePrint", nbt::SnbtFormat::PrettyFilePrint)
            .value("Classic", nbt::SnbtFormat::Classic)
            .value("Jsonify", nbt::SnbtFormat::Jsonify)
            .value("Default", nbt::SnbtFormat::Default)
            .export_values()
            .def(
                "__or__",
                [](nbt::SnbtFormat lhs, nbt::SnbtFormat rhs) { return lhs | rhs; },
                "operation |"
            )
            .def("__and__", [](nbt::SnbtFormat lhs, nbt::SnbtFormat rhs) { return lhs & rhs; }, "operation &");
    }
}

} // namespace rapidnbt