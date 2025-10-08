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
            [](py::buffer buffer, bool strict_match_size) {
                return nbt::io::detectContentFormat(to_cppstringview(buffer), strict_match_size);
            },
            py::arg("content"),
            py::arg("strict_match_size") = true,
            "Detect NBT format from binary content",
            "Args:",
            "    content (bytes): Binary content to analyzeReturns:",
            "    NbtFileFormat or None if format cannot be determined",
            "    strict_match_size (bool): Strictly match nbt content size (default: True)",
            "Returns:",
            "    NbtFileFormat or None if format cannot be determined)"
        )
        .def(
            "detect_file_format",
            &nbt::io::detectFileFormat,
            py::arg("path"),
            py::arg("file_memory_map")   = false,
            py::arg("strict_match_size") = true,
            R"(Detect NBT format from a file
        Args:
            path (os.PathLike): Path to the file
            file_memory_map (bool): Use memory mapping for large files (default: False)
            strict_match_size (bool): Strictly match nbt content size (default: True)
        Returns:
            NbtFileFormat or None if format cannot be determined)"
        )
        .def(
            "detect_content_compression_type",
            [](py::buffer buffer) -> nbt::NbtCompressionType {
                return nbt::io::detectContentCompressionType(to_cppstringview(buffer));
            },
            py::arg("content"),
            "Detect NBT compression type from binary content",
            "Args:",
            "    content (bytes): Binary content to analyzeReturns:",
            "Returns:",
            "    NbtCompressionType)"
        )
        .def(
            "detect_file_compression_type",
            &nbt::io::detectFileCompressionType,
            py::arg("path"),
            py::arg("file_memory_map") = false,
            R"(Detect NBT format from a file
        Args:
            path (os.PathLike): Path to the file
            file_memory_map (bool): Use memory mapping for large files (default: False)

        Returns:
            NbtCompressionType)"
        )
        .def(
            "loads",
            [](py::buffer buffer, std::optional<nbt::NbtFileFormat> format, bool strict_match_size) {
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
        )
        .def(
            "load",
            &nbt::io::parseFromFile,
            py::arg("path"),
            py::arg("format")            = std::nullopt,
            py::arg("file_memory_map")   = false,
            py::arg("strict_match_size") = true,
            R"(Parse CompoundTag from a file
        Args:
            path (os.PathLike): Path to NBT file
            format (NbtFileFormat, optional): Force specific format (autodetect if None)
            file_memory_map (bool): Use memory mapping for large files (default: False)
            strict_match_size (bool): Strictly match nbt content size (default: True)
        Returns:
            CompoundTag or None if parsing fails)"
        )
        .def(
            "dumps",
            [](nbt::CompoundTag const&  nbt,
               nbt::NbtFileFormat       format,
               nbt::NbtCompressionType  compressionType,
               nbt::NbtCompressionLevel compressionLevel,
               std::optional<int>       headerVersion) {
                return to_pybytes(nbt::io::saveAsBinary(nbt, format, compressionType, compressionLevel, headerVersion));
            },
            py::arg("nbt"),
            py::arg("format")            = nbt::NbtFileFormat::LittleEndian,
            py::arg("compression_type")  = nbt::NbtCompressionType::Gzip,
            py::arg("compression_level") = nbt::NbtCompressionLevel::Default,
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
            R"(Save CompoundTag to a file
        Args:
            nbt (CompoundTag): Tag to save
            path (os.PathLike): Output file path
            format (NbtFileFormat): Output format (default: LittleEndian)
            compression_type (CompressionType): Compression method (default: Gzip)
            compression_level (CompressionLevel): Compression level (default: Default)
            header_version (Optional[int]): NBT header storage version
        Returns:
            bool: True if successful, False otherwise)"
        )
        .def(
            "load_snbt",
            &nbt::io::parseSnbtFromFile,
            py::arg("path"),
            R"(Parse CompoundTag from SNBT (String NBT) file
        Args:
            path (os.PathLike): Path to SNBT file
        Returns:
            CompoundTag or None if parsing fails)"
        )
        .def(
            "loads_snbt",
            &nbt::io::parseSnbtFromContent,
            py::arg("content"),
            py::arg("parsed_length") = std::nullopt,
            R"(Parse CompoundTag from SNBT (String NBT) file
        Args:
            content (str): SNBT content
        Returns:
            CompoundTag or None if parsing fails)"
        )
        .def(
            "dump_snbt",
            &nbt::io::saveSnbtToFile,
            py::arg("nbt"),
            py::arg("path"),
            py::arg("format") = nbt::SnbtFormat::Default,
            py::arg("indent") = 4,
            R"(Save CompoundTag to SNBT (String NBT) file
        Args:
            nbt (CompoundTag): Tag to save
            path (os.PathLike): Output file path
            format (SnbtFormat): Output formatting style (default: Default)
            indent (int): Indentation level (default: 4)
        Returns:
            bool: True if successful, False otherwise)"
        )
        .def(
            "dumps_snbt",
            [](nbt::CompoundTag const& nbt, nbt::SnbtFormat format, uint8_t indent) {
                return nbt.toSnbt(format, indent);
            },
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
        )
        .def(
            "validate_content",
            [](py::buffer buffer, nbt::NbtFileFormat format, bool strict_match_size) {
                return nbt::io::validateContent(to_cppstringview(buffer), format, strict_match_size);
            },
            py::arg("content"),
            py::arg("format")            = nbt::NbtFileFormat::LittleEndian,
            py::arg("strict_match_size") = true,
            R"(Validate NBT binary content
        Args:
            content (bytes): Binary data to validate
            format (NbtFileFormat): Expected format (default: LittleEndian)
            strict_match_size (bool): Strictly match nbt content size (default: True)
        Returns:
            bool: True if valid NBT, False otherwise)"
        )
        .def(
            "validate_file",
            &nbt::io::validateFile,
            py::arg("path"),
            py::arg("format")            = nbt::NbtFileFormat::LittleEndian,
            py::arg("file_memory_map")   = false,
            py::arg("strict_match_size") = true,
            "Validate NBT file",
            "Args:",
            "    path (os.PathLike): File path to validate",
            "    format (NbtFileFormat): Expected format (default: LittleEndian)",
            "    file_memory_map (bool): Use memory mapping (default: False)",
            "    strict_match_size (bool): Strictly match nbt content size (default: True)",
            "Returns:",
            "    bool: True if valid NBT file, False otherwise"
        )
        .def(
            "loads_base64",
            &nbt::io::parseFromBsae64,
            py::arg("content"),
            py::arg("format")            = std::nullopt,
            py::arg("strict_match_size") = true,
            "Parse CompoundTag from Base64-encoded NBT",
            "Args:",
            "    content (str): Base64-encoded NBT data",
            "    format (NbtFileFormat, optional): Force specific format (autodetect if None)",
            "    strict_match_size (bool): Strictly match nbt content size (default: True)",
            "Returns:",
            "    CompoundTag or None if parsing fails"
        )
        .def(
            "dumps_base64",
            &nbt::io::saveAsBase64,
            py::arg("nbt"),
            py::arg("format")            = nbt::NbtFileFormat::LittleEndian,
            py::arg("compression_type")  = nbt::NbtCompressionType::Gzip,
            py::arg("compression_level") = nbt::NbtCompressionLevel::Default,
            py::arg("header_version")    = std::nullopt,
            "Serialize CompoundTag to Base64 string",
            "Args:",
            "    nbt (CompoundTag): Tag to serialize",
            "    format (NbtFileFormat): Output format (default: LittleEndian)",
            "    compression_type (CompressionType): Compression method (default: Gzip)",
            "    compression_level (CompressionLevel): Compression level (default: Default)",
            "    header_version (Optional[int]): NBT header storage version",
            "Returns:",
            "    str: Base64-encoded NBT data"
        )
        .def(
            "open",
            [](std::filesystem::path const& path) { return nbt::open(path); },
            py::arg("path"),
            "Open a NBT file (auto detect)",
            "Args:",
            "    path (os.PathLike): NBT file path",
            "Returns:",
            "    Optional[NbtFile]: NbtFile or None if open failed"
        );
}

} // namespace rapidnbt
