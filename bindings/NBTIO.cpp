// Copyright © 2025 GlacieTeam.All rights reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
//
// SPDX-License-Identifier: MPL-2.0

#include "NativeModule.hpp"

namespace rapidnbt {

void bindNbtIO(py::module& m) {
    m.def_submodule("nbtio")
        .def(
            "detect_content_format",
            [](py::buffer buffer, bool strict_match_size) { return nbt::io::detectContentFormat(to_cpp_stringview(buffer), strict_match_size); },
            py::arg("content"),
            py::arg("strict_match_size") = true,
            "Detect NBT format from binary content\nArgs:\n    content (bytes): Binary content to analyzeReturns:\n    NbtFileFormat or None if format cannot "
            "be determined\n    strict_match_size (bool): Strictly match nbt content size (default: True)\nReturns:\n    NbtFileFormat or None if format "
            "cannot be determined"
        )
        .def(
            "detect_file_format",
            &nbt::io::detectFileFormat,
            py::arg("path"),
            py::arg("file_memory_map")   = false,
            py::arg("strict_match_size") = true,
            "Detect NBT format from a file\nArgs:\n    path (os.PathLike): Path to the file\n    file_memory_map (bool): Use memory mapping for large files "
            "(default: False)\n    strict_match_size (bool): Strictly match nbt content size (default: True)\nReturns:\n    NbtFileFormat or None if format "
            "cannot be determined"
        )
        .def(
            "detect_content_compression_type",
            [](py::buffer buffer) -> nbt::NbtCompressionType { return nbt::io::detectContentCompressionType(to_cpp_stringview(buffer)); },
            py::arg("content"),
            "Detect NBT compression type from binary content\nArgs:\n    content (bytes): Binary content to analyzeReturns:\nReturns:\n    NbtCompressionType"
        )
        .def(
            "detect_file_compression_type",
            &nbt::io::detectFileCompressionType,
            py::arg("path"),
            py::arg("file_memory_map") = false,
            "Detect NBT format from a file\nArgs:\n    path (os.PathLike): Path to the file\n    file_memory_map (bool): Use memory mapping for large files "
            "(default: False)\n\nReturns:\nNbtCompressionType"
        )
        .def(
            "loads",
            [](py::buffer buffer, std::optional<nbt::NbtFileFormat> format, bool strict_match_size) {
                return nbt::io::parseFromContent(to_cpp_stringview(buffer), format, strict_match_size);
            },
            py::arg("content"),
            py::arg("format")            = std::nullopt,
            py::arg("strict_match_size") = true,
            "Parse CompoundTag from binary data\nArgs:\n    content (bytes): Binary NBT data\n    format (NbtFileFormat, optional): Force specific format "
            "(autodetect if None)\n    strict_match_size (bool): Strictly match nbt content size (default: True)\nReturns:\n    CompoundTag or None if parsing "
            "fails"
        )
        .def(
            "load",
            &nbt::io::parseFromFile,
            py::arg("path"),
            py::arg("format")            = std::nullopt,
            py::arg("file_memory_map")   = false,
            py::arg("strict_match_size") = true,
            "Parse CompoundTag from a file\nArgs:\n    path (os.PathLike): Path to NBT file\n    format (NbtFileFormat, optional): Force specific format "
            "(autodetect if None)\n    file_memory_map (bool): Use memory mapping for large files (default: False)\n    strict_match_size (bool): Strictly "
            "match nbt content size (default: True)\n\nReturns:\nCompoundTag or None if parsing fails"
        )
        .def(
            "dumps",
            [](nbt::CompoundTag const&  nbt,
               nbt::NbtFileFormat       format,
               nbt::NbtCompressionType  compressionType,
               nbt::NbtCompressionLevel compressionLevel,
               std::optional<int> headerVersion) { return to_py_bytes(nbt::io::saveAsBinary(nbt, format, compressionType, compressionLevel, headerVersion)); },
            py::arg("nbt"),
            py::arg("format")            = nbt::NbtFileFormat::LittleEndian,
            py::arg("compression_type")  = nbt::NbtCompressionType::Gzip,
            py::arg("compression_level") = nbt::NbtCompressionLevel::Default,
            py::arg("header_version")    = std::nullopt,
            "Serialize CompoundTag to binary data\nArgs:\n    nbt (CompoundTag): Tag to serialize\n    format (NbtFileFormat): Output format (default: "
            "LittleEndian)\n    compression_type (CompressionType): Compression method (default: Gzip)\n    compression_level (CompressionLevel): Compression "
            "level (default: Default)\n    header_version (Optional[int]): NBT header storage version\nReturns:\n    bytes: Serialized binary data"
        )
        .def(
            "dump",
            &nbt::io::saveToFile,
            py::arg("nbt"),
            py::arg("path"),
            py::arg("format")            = nbt::NbtFileFormat::LittleEndian,
            py::arg("compression_type")  = nbt::NbtCompressionType::Gzip,
            py::arg("compression_level") = nbt::NbtCompressionLevel::Default,
            py::arg("header_version")    = std::nullopt,
            "Save CompoundTag to a file\nArgs:\n    nbt (CompoundTag): Tag to save\n    path (os.PathLike): Output file path\n    format (NbtFileFormat): "
            "Output format (default: LittleEndian)\n    compression_type (CompressionType): Compression method (default: Gzip)\n    compression_level "
            "(CompressionLevel): Compression level (default: Default)\n    header_version (Optional[int]): NBT header storage version\nReturns:\n    bool: "
            "True if successful, False otherwise"
        )
        .def(
            "load_snbt",
            &nbt::io::parseSnbtFromFile,
            py::arg("path"),
            "Parse CompoundTag from SNBT (String NBT) file\nArgs:\n    path (os.PathLike): Path to SNBT file\nReturns:\n    CompoundTag or None if parsing "
            "fails"
        )
        .def(
            "loads_snbt",
            &nbt::io::parseSnbtFromContent,
            py::arg("content"),
            py::arg("parsed_length") = std::nullopt,
            "Parse CompoundTag from SNBT (String NBT)\nArgs:\n    content (str): SNBT content\nReturns:\n    CompoundTag or None if parsing fails"
        )
        .def(
            "loads_json",
            &nbt::CompoundTag::fromJson,
            py::arg("content"),
            py::arg("parsed_length") = std::nullopt,
            "Parse CompoundTag from JSON\nArgs:\n    content (str): SNBT content\n\nReturns:\n    CompoundTag or None if parsing fails"
        )
        .def(
            "dump_snbt",
            &nbt::io::saveSnbtToFile,
            py::arg("nbt"),
            py::arg("path"),
            py::arg("format")        = nbt::SnbtFormat::Default,
            py::arg("indent")        = 4,
            py::arg("number_format") = nbt::SnbtNumberFormat::Default,
            "Save CompoundTag to SNBT (String NBT) file\nArgs:\n    nbt (CompoundTag): Tag to save\n    path (os.PathLike): Output file path\n    format "
            "(SnbtFormat): Output formatting style (default: Default)\n    indent (int): Indentation level (default: 4)\n\nReturns:\n    bool: True if "
            "successful, False otherwise"
        )
        .def(
            "dumps_snbt",
            [](nbt::CompoundTag const& nbt, nbt::SnbtFormat format, uint8_t indent) { return nbt.toSnbt(format, indent); },
            py::arg("nbt"),
            py::arg("format") = nbt::SnbtFormat::Default,
            py::arg("indent") = 4,
            "Save CompoundTag to SNBT (String NBT) file\nArgs:\n    nbt (CompoundTag): Tag to save\n    format (SnbtFormat): Output formatting style (default: "
            "Default)\n    indent (int): Indentation level (default: 4)\nReturns:\n    str: SNBT string"
        )
        .def(
            "validate_content",
            [](py::buffer buffer, nbt::NbtFileFormat format, bool strict_match_size) {
                return nbt::io::validateContent(to_cpp_stringview(buffer), format, strict_match_size);
            },
            py::arg("content"),
            py::arg("format")            = nbt::NbtFileFormat::LittleEndian,
            py::arg("strict_match_size") = true,
            "Validate NBT binary content\nArgs:\n    content (bytes): Binary data to validate\n    format (NbtFileFormat): Expected format (default: "
            "LittleEndian)\n    strict_match_size (bool): Strictly match nbt content size (default: True)\nReturns:\n    bool: True if valid NBT, False "
            "otherwise"
        )
        .def(
            "validate_file",
            &nbt::io::validateFile,
            py::arg("path"),
            py::arg("format")            = nbt::NbtFileFormat::LittleEndian,
            py::arg("file_memory_map")   = false,
            py::arg("strict_match_size") = true,
            "Validate NBT file\nArgs:\n    path (os.PathLike): File path to validate\n    format (NbtFileFormat): Expected format (default: LittleEndian)\n    "
            "file_memory_map (bool): Use memory mapping (default: False)\n    strict_match_size (bool): Strictly match nbt content size (default: "
            "True)\nReturns:\n    bool: True if valid NBT file, False otherwise"
        )
        .def(
            "loads_base64",
            &nbt::io::parseFromBsae64,
            py::arg("content"),
            py::arg("format")            = std::nullopt,
            py::arg("strict_match_size") = true,
            "Parse CompoundTag from Base64-encoded NBT\nArgs:\n    content (str): Base64-encoded NBT data\n    format (NbtFileFormat, optional): Force "
            "specific format (autodetect if None)\n    strict_match_size (bool): Strictly match nbt content size (default: True)\nReturns:\n    CompoundTag or "
            "None if parsing fails"
        )
        .def(
            "dumps_base64",
            &nbt::io::saveAsBase64,
            py::arg("nbt"),
            py::arg("format")            = nbt::NbtFileFormat::LittleEndian,
            py::arg("compression_type")  = nbt::NbtCompressionType::Gzip,
            py::arg("compression_level") = nbt::NbtCompressionLevel::Default,
            py::arg("header_version")    = std::nullopt,
            "Serialize CompoundTag to Base64 string\nArgs:\n    nbt (CompoundTag): Tag to serialize\n    format (NbtFileFormat): Output format (default: "
            "LittleEndian)\n    compression_type (CompressionType): Compression method (default: Gzip)\n    compression_level (CompressionLevel): Compression "
            "level (default: Default)\n    header_version (Optional[int]): NBT header storage version\nReturns:\n    str: Base64-encoded NBT data"
        )
        .def(
            "open",
            [](std::filesystem::path const& path) { return nbt::open(path); },
            py::arg("path"),
            "Open a NBT file (auto detect)\nArgs:\n    path (os.PathLike): NBT file path\nReturns:\n    Optional[NbtFile]: NbtFile or None if open failed"
        );
}

} // namespace rapidnbt
