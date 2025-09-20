// Copyright © 2025 GlacieTeam.All rights reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
//
// SPDX-License-Identifier: MPL-2.0

#include "NativeModule.hpp"

namespace rapidnbt {

void bindNbtIO(py::module& m) {
    auto sm = m.def_submodule("nbtio");

    py::enum_<nbt::io::NbtFileFormat>(sm, "NbtFileFormat", "Enumeration of NBT binary file formats")
        .value("LITTLE_ENDIAN", nbt::io::NbtFileFormat::LittleEndian)
        .value("LITTLE_ENDIAN_WITH_HEADER", nbt::io::NbtFileFormat::LittleEndianWithHeader)
        .value("BIG_ENDIAN", nbt::io::NbtFileFormat::BigEndian)
        .value("BIG_ENDIAN_WITH_HEADER", nbt::io::NbtFileFormat::BigEndianWithHeader)
        .value("BEDROCK_NETWORK", nbt::io::NbtFileFormat::BedrockNetwork)
        .export_values();

    py::enum_<nbt::io::CompressionType>(
        sm,
        "NbtCompressionType",
        "Enumeration of compression types for NBT serialization"
    )
        .value("NONE", nbt::io::CompressionType::None)
        .value("GZIP", nbt::io::CompressionType::Gzip)
        .value("ZLIB", nbt::io::CompressionType::Zlib)
        .export_values();

    py::enum_<nbt::io::CompressionLevel>(sm, "NbtCompressionLevel", "Enumeration of compression levels")
        .value("DEFAULT", nbt::io::CompressionLevel::Default)
        .value("NO_COMPRESSION", nbt::io::CompressionLevel::NoCompression)
        .value("BEST_SPEED", nbt::io::CompressionLevel::BestSpeed)
        .value("LOW", nbt::io::CompressionLevel::Low)
        .value("MEDIUM_LOW", nbt::io::CompressionLevel::MediumLow)
        .value("MEDIUM", nbt::io::CompressionLevel::Medium)
        .value("MEDIUM_HIGH", nbt::io::CompressionLevel::MediumHigh)
        .value("HIGH", nbt::io::CompressionLevel::High)
        .value("VERY_HIGH", nbt::io::CompressionLevel::VeryHigh)
        .value("ULTRA", nbt::io::CompressionLevel::Ultra)
        .value("BEST_COMPRESSION", nbt::io::CompressionLevel::BestCompression)
        .export_values();

    sm.def(
        "detect_content_format",
        [](py::buffer buffer, bool strict_match_size) {
            return nbt::io::checkNbtContentFormat(to_cppstringview(buffer), strict_match_size);
        },
        py::arg("content"),
        py::arg("strict_match_size") = true,
        R"(Detect NBT format from binary content
Args:
    content (bytes): Binary content to analyzeReturns:
    NbtFileFormat or None if format cannot be determined
    strict_match_size (bool): Strictly match nbt content size (default: True)
Returns:
    NbtFileFormat or None if format cannot be determined)"
    );
    sm.def(
        "detect_file_format",
        &nbt::io::checkNbtFileFormat,
        py::arg("path"),
        py::arg("file_memory_map")   = false,
        py::arg("strict_match_size") = true,
        R"(Detect NBT format from a file
Args:
    path (str): Path to the file
    file_memory_map (bool): Use memory mapping for large files (default: False)
    strict_match_size (bool): Strictly match nbt content size (default: True)
Returns:
    NbtFileFormat or None if format cannot be determined)"
    );
    sm.def(
        "loads",
        [](py::buffer buffer, std::optional<nbt::io::NbtFileFormat> format, bool strict_match_size) {
            return nbt::io::parseFromContent(to_cppstringview(buffer), format, strict_match_size);
        },
        py::arg("content"),
        py::arg("format")            = std::nullopt,
        py::arg("strict_match_size") = true,
        R"(Parse CompoundTag from binary data
Args:
    content (bytes): Binary NBT data
    format (NbtFileFormat, optional): Force specific format (autodetect if None)
    strict_match_size (bool): Strictly match nbt content size (default: True)
Returns:
    CompoundTag or None if parsing fails)"
    );
    sm.def(
        "load",
        &nbt::io::parseFromFile,
        py::arg("path"),
        py::arg("format")            = std::nullopt,
        py::arg("file_memory_map")   = false,
        py::arg("strict_match_size") = true,
        R"(Parse CompoundTag from a file
Args:
    path (str): Path to NBT file
    format (NbtFileFormat, optional): Force specific format (autodetect if None)
    file_memory_map (bool): Use memory mapping for large files (default: False)
    strict_match_size (bool): Strictly match nbt content size (default: True)
Returns:
    CompoundTag or None if parsing fails)"
    );
    sm.def(
        "dumps",
        [](nbt::CompoundTag const&   nbt,
           nbt::io::NbtFileFormat    format,
           nbt::io::CompressionType  compressionType,
           nbt::io::CompressionLevel compressionLevel,
           std::optional<int>        headerVersion) {
            return to_pybytes(nbt::io::saveAsBinary(nbt, format, compressionType, compressionLevel, headerVersion));
        },
        py::arg("nbt"),
        py::arg("format")            = nbt::io::NbtFileFormat::LittleEndian,
        py::arg("compression_type")  = nbt::io::CompressionType::Gzip,
        py::arg("compression_level") = nbt::io::CompressionLevel::Default,
        py::arg("header_version")    = std::nullopt,
        R"(Serialize CompoundTag to binary data
            Args:
    nbt (CompoundTag): Tag to serialize
    format (NbtFileFormat): Output format (default: LittleEndian)
    compression_type (CompressionType): Compression method (default: Gzip)
    compression_level (CompressionLevel): Compression level (default: Default)
    header_version (Optional[int]): NBT header storage version
Returns:
    bytes: Serialized binary data)"
    );
    sm.def(
        "dump",
        &nbt::io::saveToFile,
        py::arg("nbt"),
        py::arg("path"),
        py::arg("format")            = nbt::io::NbtFileFormat::LittleEndian,
        py::arg("compression_type")  = nbt::io::CompressionType::Gzip,
        py::arg("compression_level") = nbt::io::CompressionLevel::Default,
        py::arg("header_version")    = std::nullopt,
        R"(Save CompoundTag to a file
Args:
    nbt (CompoundTag): Tag to save
    path (str): Output file path
    format (NbtFileFormat): Output format (default: LittleEndian)
    compression_type (CompressionType): Compression method (default: Gzip)
    compression_level (CompressionLevel): Compression level (default: Default)
    header_version (Optional[int]): NBT header storage version
Returns:
    bool: True if successful, False otherwise)"
    );
    sm.def(
        "load_snbt",
        &nbt::io::parseSnbtFromFile,
        py::arg("path"),
        R"(Parse CompoundTag from SNBT (String NBT) file
Args:
    path (str): Path to SNBT file
Returns:
    CompoundTag or None if parsing fails)"
    );
    sm.def(
        "loads_snbt",
        &nbt::CompoundTag::fromSnbt,
        py::arg("content"),
        py::arg("parsed_length") = py::none(),
        R"(Parse CompoundTag from SNBT (String NBT) file
Args:
    content (str): SNBT content
Returns:
    CompoundTag or None if parsing fails)"
    );
    sm.def(
        "dump_snbt",
        &nbt::io::saveSnbtToFile,
        py::arg("nbt"),
        py::arg("path"),
        py::arg("format") = nbt::SnbtFormat::Default,
        py::arg("indent") = 4,
        R"(Save CompoundTag to SNBT (String NBT) file
Args:
    nbt (CompoundTag): Tag to save
    path (str): Output file path
    format (SnbtFormat): Output formatting style (default: Default)
    indent (int): Indentation level (default: 4)
Returns:
    bool: True if successful, False otherwise)"
    );
    sm.def(
        "dumps_snbt",
        [](nbt::CompoundTag const& nbt, nbt::SnbtFormat format, uint8_t indent) { return nbt.toSnbt(format, indent); },
        py::arg("nbt"),
        py::arg("format") = nbt::SnbtFormat::Default,
        py::arg("indent") = 4,
        R"(Save CompoundTag to SNBT (String NBT) file
Args:
    nbt (CompoundTag): Tag to save
    format (SnbtFormat): Output formatting style (default: Default)
    indent (int): Indentation level (default: 4)
Returns:
    str: SNBT string)"
    );
    sm.def(
        "validate_content",
        [](py::buffer buffer, nbt::io::NbtFileFormat format, bool strict_match_size) {
            return nbt::io::validateContent(to_cppstringview(buffer), format, strict_match_size);
        },
        py::arg("content"),
        py::arg("format")            = nbt::io::NbtFileFormat::LittleEndian,
        py::arg("strict_match_size") = true,
        R"(Validate NBT binary content
Args:
    content (bytes): Binary data to validate
    format (NbtFileFormat): Expected format (default: LittleEndian)
    strict_match_size (bool): Strictly match nbt content size (default: True)
Returns:
    bool: True if valid NBT, False otherwise)"
    );
    sm.def(
        "validate_file",
        &nbt::io::validateFile,
        py::arg("path"),
        py::arg("format")            = nbt::io::NbtFileFormat::LittleEndian,
        py::arg("file_memory_map")   = false,
        py::arg("strict_match_size") = true,
        R"(Validate NBT file
Args:
    path (str): File path to validate
    format (NbtFileFormat): Expected format (default: LittleEndian)
    file_memory_map (bool): Use memory mapping (default: False)
    strict_match_size (bool): Strictly match nbt content size (default: True)
Returns:
    bool: True if valid NBT file, False otherwise)"
    );
    sm.def(
        "loads_base64",
        &nbt::io::parseFromBsae64,
        py::arg("content"),
        py::arg("format")            = std::nullopt,
        py::arg("strict_match_size") = true,
        R"(Parse CompoundTag from Base64-encoded NBT
Args:
    content (str): Base64-encoded NBT data\
    format (NbtFileFormat, optional): Force specific format (autodetect if None)
    strict_match_size (bool): Strictly match nbt content size (default: True)
Returns:
    CompoundTag or None if parsing fails)"
    );
    sm.def(
        "dumps_base64",
        &nbt::io::saveAsBase64,
        py::arg("nbt"),
        py::arg("format")            = nbt::io::NbtFileFormat::LittleEndian,
        py::arg("compression_type")  = nbt::io::CompressionType::Gzip,
        py::arg("compression_level") = nbt::io::CompressionLevel::Default,
        py::arg("header_version")    = std::nullopt,
        R"(Serialize CompoundTag to Base64 string
Args:
    nbt (CompoundTag): Tag to serialize
    format (NbtFileFormat): Output format (default: LittleEndian)
    compression_type (CompressionType): Compression method (default: Gzip)
    compression_level (CompressionLevel): Compression level (default: Default)
    header_version (Optional[int]): NBT header storage version
Returns:
    str: Base64-encoded NBT data)"
    );
}

} // namespace rapidnbt
