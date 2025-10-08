# Copyright © 2025 GlacieTeam.All rights reserved.
#
# This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy
# of the MPL was not distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
#
# SPDX-License-Identifier: MPL-2.0

from typing import Any, Optional
from pathlib import Path
from rapidnbt._NBT.compound_tag import CompoundTag
from rapidnbt._NBT.nbt_compression_level import NbtCompressionLevel
from rapidnbt._NBT.nbt_compression_type import NbtCompressionType
from rapidnbt._NBT.nbt_file_format import NbtFileFormat
from rapidnbt._NBT.snbt_format import SnbtFormat

class NbtFile(CompoundTag):
    """
    NBT file
    Use nbtio.open() to open a NBT file.
    """

    def __enter__(self) -> NbtFile:
        """
        Enter context manager
        """

    def __exit__(self, exc_type: Any, exc_value: Any, traceback: Any) -> None:
        """
        Exit context manager
        """

    def __repr__(self) -> str:
        """
        Official string representation
        """

    def __str__(self) -> str:
        """
        String representation
        """

    def flush(self) -> None:
        """
        flush data to the file.
        """

    @property
    def compression_level(
        self,
    ) -> Optional[NbtCompressionLevel]:
        """
        File compression level
        """

    @compression_level.setter
    def compression_level(self, arg0: Optional[NbtCompressionLevel]) -> None: ...
    @property
    def compression_type(
        self,
    ) -> Optional[NbtCompressionType]:
        """
        File compression type
        """

    @compression_type.setter
    def compression_type(self, arg0: Optional[NbtCompressionType]) -> None:
        """
        File compression type
        """

    @property
    def file_format(self) -> Optional[NbtFileFormat]:
        """
        Binary file format
        """

    @file_format.setter
    def file_format(self, arg0: Optional[NbtFileFormat]) -> None:
        """
        Binary file format
        """

    @property
    def file_path(self) -> Path:
        """
        File path
        """

    @property
    def is_snbt(self) -> bool:
        """
        File is Snbt File
        """

    @is_snbt.setter
    def is_snbt(self, arg0: bool) -> None:
        """
        File is Snbt File
        """

    @property
    def snbt_format(self) -> Optional[SnbtFormat]:
        """
        File Snbt format
        """

    @snbt_format.setter
    def snbt_format(self, arg0: Optional[SnbtFormat]) -> None:
        """
        File Snbt format
        """

    @property
    def snbt_indent(self) -> Optional[int]:
        """
        File Snbt indent
        """

    @snbt_indent.setter
    def snbt_indent(self, arg0: Optional[int]) -> None:
        """
        File Snbt indent
        """
