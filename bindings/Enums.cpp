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

        py::native_enum<nbt::Tag::Type>(sm, "TagType", "enum.Enum", "The tag type enum")
            .value("End", nbt::Tag::Type::End)
            .value("Byte", nbt::Tag::Type::Byte)
            .value("Short", nbt::Tag::Type::Short)
            .value("Int", nbt::Tag::Type::Int)
            .value("Long", nbt::Tag::Type::Long)
            .value("Float", nbt::Tag::Type::Float)
            .value("Double", nbt::Tag::Type::Double)
            .value("ByteArray", nbt::Tag::Type::ByteArray)
            .value("String", nbt::Tag::Type::String)
            .value("List", nbt::Tag::Type::List)
            .value("Compound", nbt::Tag::Type::Compound)
            .value("IntArray", nbt::Tag::Type::IntArray)
            .value("LongArray", nbt::Tag::Type::LongArray)
            .export_values()
            .finalize();
    }
    {
        auto sm = m.def_submodule(
            "snbt_format",
            "The SNBT format enum\nYou can use | operation to combime flags\nExample:\n    format = SnbtFormat.Classic | SnbtFormat.ForceUppercase"
        );

        py::native_enum<nbt::SnbtFormat>(sm, "SnbtFormat", "enum.IntFlag")
            .value("Minimize", nbt::SnbtFormat::Minimize)
            .value("CompoundLineFeed", nbt::SnbtFormat::CompoundLineFeed)
            .value("ListArrayLineFeed", nbt::SnbtFormat::ListArrayLineFeed)
            .value("BinaryArrayLineFeed", nbt::SnbtFormat::BinaryArrayLineFeed)
            .value("ForceLineFeedIgnoreIndent", nbt::SnbtFormat::ForceLineFeedIgnoreIndent)
            .value("ForceAscii", nbt::SnbtFormat::ForceAscii)
            .value("ForceKeyQuote", nbt::SnbtFormat::ForceKeyQuote)
            .value("ForceValueQuote", nbt::SnbtFormat::ForceValueQuote)
            .value("ForceUppercase", nbt::SnbtFormat::ForceUppercase)
            .value("MarkIntTag", nbt::SnbtFormat::MarkIntTag)
            .value("MarkDoubleTag", nbt::SnbtFormat::MarkDoubleTag)
            .value("CommentMarks", nbt::SnbtFormat::CommentMarks)
            .value("MarkSigned", nbt::SnbtFormat::MarkSigned)
            .value("ArrayLineFeed", nbt::SnbtFormat::ArrayLineFeed)
            .value("AlwaysLineFeed", nbt::SnbtFormat::AlwaysLineFeed)
            .value("MarkAllTags", nbt::SnbtFormat::MarkAllTags)
            .value("PrettyFilePrint", nbt::SnbtFormat::PrettyFilePrint)
            .value("ForceQuote", nbt::SnbtFormat::ForceQuote)
            .value("Classic", nbt::SnbtFormat::Classic)
            .value("Jsonify", nbt::SnbtFormat::Jsonify)
            .value("Default", nbt::SnbtFormat::Default)
            .export_values()
            .finalize();

        py::native_enum<nbt::SnbtNumberFormat>(sm, "SnbtNumberFormat", "enum.Enum")
            .value("Decimal", nbt::SnbtNumberFormat::Decimal)
            .value("LowerHexadecimal", nbt::SnbtNumberFormat::LowerHexadecimal)
            .value("UpperHexadecimal", nbt::SnbtNumberFormat::UpperHexadecimal)
            .value("Binary", nbt::SnbtNumberFormat::Binary)
            .export_values()
            .finalize();
    }
    {
        auto sm = m.def_submodule("nbt_file_format");

        py::native_enum<nbt::NbtFileFormat>(sm, "NbtFileFormat", "enum.Enum", "Enumeration of NBT binary file formats")
            .value("LITTLE_ENDIAN", nbt::NbtFileFormat::LittleEndian)
            .value("LITTLE_ENDIAN_WITH_HEADER", nbt::NbtFileFormat::LittleEndianWithHeader)
            .value("BIG_ENDIAN", nbt::NbtFileFormat::BigEndian)
            .value("BIG_ENDIAN_WITH_HEADER", nbt::NbtFileFormat::BigEndianWithHeader)
            .value("BEDROCK_NETWORK", nbt::NbtFileFormat::BedrockNetwork)
            .export_values()
            .finalize();
    }
    {
        auto sm = m.def_submodule("nbt_compression_type");

        py::native_enum<nbt::NbtCompressionType>(sm, "NbtCompressionType", "enum.Enum", "Enumeration of compression types for NBT serialization")
            .value("NONE", nbt::NbtCompressionType::None)
            .value("GZIP", nbt::NbtCompressionType::Gzip)
            .value("ZLIB", nbt::NbtCompressionType::Zlib)
            .export_values()
            .finalize();
    }
    {
        auto sm = m.def_submodule("nbt_compression_level");

        py::native_enum<nbt::NbtCompressionLevel>(sm, "NbtCompressionLevel", "enum.IntEnum", "Enumeration of compression levels")
            .value("DEFAULT", nbt::NbtCompressionLevel::Default)
            .value("NO_COMPRESSION", nbt::NbtCompressionLevel::NoCompression)
            .value("BEST_SPEED", nbt::NbtCompressionLevel::BestSpeed)
            .value("LOW", nbt::NbtCompressionLevel::Low)
            .value("MEDIUM_LOW", nbt::NbtCompressionLevel::MediumLow)
            .value("MEDIUM", nbt::NbtCompressionLevel::Medium)
            .value("MEDIUM_HIGH", nbt::NbtCompressionLevel::MediumHigh)
            .value("HIGH", nbt::NbtCompressionLevel::High)
            .value("VERY_HIGH", nbt::NbtCompressionLevel::VeryHigh)
            .value("ULTRA", nbt::NbtCompressionLevel::Ultra)
            .value("BEST_COMPRESSION", nbt::NbtCompressionLevel::BestCompression)
            .export_values()
            .finalize();
    }
}

} // namespace rapidnbt