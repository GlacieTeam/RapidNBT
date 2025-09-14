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

    py::enum_<nbt::NbtFileFormat>(sm, "NbtFileFormat", "Enumeration of NBT binary file formats")
        .value("LittleEndian", nbt::NbtFileFormat::LittleEndianBinary)
        .value("LittleEndianWithHeader", nbt::NbtFileFormat::LittleEndianBinaryWithHeader)
        .value("BigEndian", nbt::NbtFileFormat::BigEndianBinary)
        .value("BigEndianWithHeader", nbt::NbtFileFormat::BigEndianBinaryWithHeader)
        .value("BedrockNetwork", nbt::NbtFileFormat::BedrockNetwork)
        .export_values();

    py::enum_<nbt::CompressionType>(sm, "NbtCompressionType", "Enumeration of compression types for NBT serialization")
        .value("NONE", nbt::CompressionType::None)
        .value("GZIP", nbt::CompressionType::Gzip)
        .value("ZLIB", nbt::CompressionType::Zlib)
        .export_values();

    py::enum_<nbt::CompressionLevel>(sm, "NbtCompressionLevel", "Enumeration of compression levels")
        .value("DEFAULT", nbt::CompressionLevel::Default)
        .value("NO_COMPRESSION", nbt::CompressionLevel::NoCompression)
        .value("BEST_SPEED", nbt::CompressionLevel::BestSpeed)
        .value("LOW", nbt::CompressionLevel::Low)
        .value("MEDIUM_LOW", nbt::CompressionLevel::MediumLow)
        .value("MEDIUM", nbt::CompressionLevel::Medium)
        .value("MEDIUM_HIGH", nbt::CompressionLevel::MediumHigh)
        .value("HIGH", nbt::CompressionLevel::High)
        .value("VERY_HIGH", nbt::CompressionLevel::VeryHigh)
        .value("ULTRA", nbt::CompressionLevel::Ultra)
        .value("BEST_COMPRESSION", nbt::CompressionLevel::BestCompression)
        .export_values();

    sm.def(
        "detect_content_format",
        [](py::buffer buffer) { return nbt::checkNbtContentFormat(to_cppstringview(buffer)); },
        py::arg("content"),
        R"(Detect NBT format from binary content
        Args:
            content (bytes): Binary content to analyze
        Returns:
            NbtFileFormat or None if format cannot be determined)"
    );
    sm.def(
        "detect_file_format",
        &nbt::checkNbtFileFormat,
        py::arg("path"),
        py::arg("file_memory_map") = false,
        R"(Detect NBT format from a file
            Args:
                path (str): Path to the file
                    file_memory_map (bool): Use memory mapping for large files (default: False)
            Returns:
                NbtFileFormat or None if format cannot be determined)"
    );
    sm.def(
        "loads",
        [](py::buffer buffer, std::optional<nbt::NbtFileFormat> format) {
            return nbt::parseFromBinary(to_cppstringview(buffer), format);
        },
        py::arg("content"),
        py::arg("format") = py::none(),
        R"(Parse CompoundTag from binary data
            Args:
                content (bytes): Binary NBT data
                format (NbtFileFormat, optional): Force specific format (autodetect if None)
            Returns:
                CompoundTag or None if parsing fails
            Example:
                with open('level.dat', 'rb') as f:
                    nbt = rapidnbt.io.loads(f.read()))"
    );
    sm.def(
        "load",
        &nbt::parseFromFile,
        py::arg("path"),
        py::arg("format")          = py::none(),
        py::arg("file_memory_map") = false,
        R"(Parse CompoundTag from a file
            Args:
                path (str): Path to NBT file
                format (NbtFileFormat, optional): Force specific format (autodetect if None)
                file_memory_map (bool): Use memory mapping for large files (default: False)
            Returns:
                CompoundTag or None if parsing fails)"
    );
    sm.def(
        "dumps",
        [](nbt::CompoundTag const& nbt,
           nbt::NbtFileFormat      format,
           nbt::CompressionType    compressionType,
           nbt::CompressionLevel   compressionLevel) {
            return to_pybytes(nbt::saveAsBinary(nbt, format, compressionType, compressionLevel));
        },
        py::arg("nbt"),
        py::arg("format")            = nbt::NbtFileFormat::LittleEndianBinary,
        py::arg("compression_type")  = nbt::CompressionType::Gzip,
        py::arg("compression_level") = nbt::CompressionLevel::Default,
        R"(Serialize CompoundTag to binary data
            Args:
                nbt (CompoundTag): Tag to serialize
                format (NbtFileFormat): Output format (default: LittleEndian)
                compression_type (CompressionType): Compression method (default: Gzip)
                compression_level (CompressionLevel): Compression level (default: Default)
            Returns:
                bytes: Serialized binary data)"
    );
    sm.def(
        "save",
        &nbt::saveToFile,
        py::arg("nbt"),
        py::arg("path"),
        py::arg("format")            = nbt::NbtFileFormat::LittleEndianBinary,
        py::arg("compression_type")  = nbt::CompressionType::Gzip,
        py::arg("compression_level") = nbt::CompressionLevel::Default,
        R"(Save CompoundTag to a file
            Args:
                nbt (CompoundTag): Tag to save
                path (str): Output file path
                format (NbtFileFormat): Output format (default: LittleEndian)
                compression_type (CompressionType): Compression method (default: Gzip)
                compression_level (CompressionLevel): Compression level (default: Default)
            Returns:
                bool: True if successful, False otherwise)"
    );
    sm.def(
        "load_snbt",
        &nbt::parseSnbtFromFile,
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
        py::arg("path"),
        py::arg("parsed_length") = py::none(),
        R"(Parse CompoundTag from SNBT (String NBT) file
            Args:
                path (str): Path to SNBT file
            Returns:
                CompoundTag or None if parsing fails)"
    );
    sm.def(
        "save_snbt",
        &nbt::saveSnbtToFile,
        py::arg("nbt"),
        py::arg("path"),
        py::arg("format") = nbt::SnbtFormat::PrettyFilePrint,
        py::arg("indent") = 4,
        R"(Save CompoundTag to SNBT (String NBT) file
            Args:
                nbt (CompoundTag): Tag to save
                path (str): Output file path
                format (SnbtFormat): Output formatting style (default: PrettyFilePrint)
                indent (int): Indentation level (default: 4)
            Returns:
                bool: True if successful, False otherwise)"
    );
    sm.def(
        "validate",
        [](py::buffer buffer, nbt::NbtFileFormat format) {
            return nbt::validateContent(to_cppstringview(buffer), format);
        },
        py::arg("content"),
        py::arg("format") = nbt::NbtFileFormat::LittleEndianBinary,
        R"(Validate NBT binary content
            Args:
                content (bytes): Binary data to validate
                format (NbtFileFormat): Expected format (default: LittleEndian)
            Returns:
                bool: True if valid NBT, False otherwise)"
    );
    sm.def(
        "validate_file",
        &nbt::validateFile,
        py::arg("path"),
        py::arg("format")          = nbt::NbtFileFormat::LittleEndianBinary,
        py::arg("file_memory_map") = false,
        R"(Validate NBT file
            Args:
                path (str): File path to validate
                format (NbtFileFormat): Expected format (default: LittleEndian)
                file_memory_map (bool): Use memory mapping (default: False)
            Returns:
                bool: True if valid NBT file, False otherwise)"
    );
    sm.def(
        "loads_base64",
        &nbt::parseFromBsae64,
        py::arg("content"),
        py::arg("format") = py::none(),
        R"(Parse CompoundTag from Base64-encoded NBT
            Args:
                content (str): Base64-encoded NBT data\
                format (NbtFileFormat, optional): Force specific format (autodetect if None)
            Returns:
                CompoundTag or None if parsing fails)"
    );
    sm.def(
        "dumps_base64",
        &nbt::saveAsBase64,
        py::arg("nbt"),
        py::arg("format")            = nbt::NbtFileFormat::LittleEndianBinary,
        py::arg("compression_type")  = nbt::CompressionType::Gzip,
        py::arg("compression_level") = nbt::CompressionLevel::Default,
        R"(Serialize CompoundTag to Base64 string
            Args:
                nbt (CompoundTag): Tag to serialize
                format (NbtFileFormat): Output format (default: LittleEndian)
                compression_type (CompressionType): Compression method (default: Gzip)
                compression_level (CompressionLevel): Compression level (default: Default)
            Returns:
                str: Base64-encoded NBT data)"
    );
}

} // namespace rapidnbt
