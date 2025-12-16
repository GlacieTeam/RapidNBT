# Copyright © 2025 GlacieTeam.All rights reserved.
#
# This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy
# of the MPL was not distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
#
# SPDX-License-Identifier: MPL-2.0

"""Python bindings for NBT library"""

from ._NBT.tag_type import TagType
from ._NBT.snbt_format import SnbtFormat, SnbtNumberFormat
from ._NBT.compound_tag_variant import CompoundTagVariant
from ._NBT.tag import Tag
from ._NBT.end_tag import EndTag
from ._NBT.byte_tag import ByteTag
from ._NBT.short_tag import ShortTag
from ._NBT.int_tag import IntTag
from ._NBT.long_tag import LongTag
from ._NBT.float_tag import FloatTag
from ._NBT.double_tag import DoubleTag
from ._NBT.byte_array_tag import ByteArrayTag
from ._NBT.string_tag import StringTag
from ._NBT.list_tag import ListTag
from ._NBT.compound_tag import CompoundTag
from ._NBT.int_array_tag import IntArrayTag
from ._NBT.long_array_tag import LongArrayTag
from ._NBT.nbt_file_format import NbtFileFormat
from ._NBT.nbt_compression_level import NbtCompressionLevel
from ._NBT.nbt_compression_type import NbtCompressionType
from ._NBT.nbt_file import NbtFile
from ._NBT import nbtio

__all__ = [
    "TagType",
    "SnbtFormat",
    "SnbtNumberFormat",
    "CompoundTagVariant",
    "Tag",
    "EndTag",
    "ByteTag",
    "ShortTag",
    "IntTag",
    "LongTag",
    "FloatTag",
    "DoubleTag",
    "ByteArrayTag",
    "StringTag",
    "ListTag",
    "CompoundTag",
    "IntArrayTag",
    "LongArrayTag",
    "nbtio",
    "NbtCompressionLevel",
    "NbtCompressionType",
    "NbtFileFormat",
    "NbtFile",
]
