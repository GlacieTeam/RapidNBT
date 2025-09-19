# Copyright © 2025 GlacieTeam.All rights reserved.
#
# This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy
# of the MPL was not distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
#
# SPDX-License-Identifier: MPL-2.0

"""Python bindings for NBT library"""

from rapidnbt._NBT.tag_type import TagType
from rapidnbt._NBT.snbt_format import SnbtFormat
from rapidnbt._NBT.compound_tag_variant import CompoundTagVariant
from rapidnbt._NBT.tag import Tag
from rapidnbt._NBT.end_tag import EndTag
from rapidnbt._NBT.byte_tag import ByteTag
from rapidnbt._NBT.short_tag import ShortTag
from rapidnbt._NBT.int_tag import IntTag
from rapidnbt._NBT.int64_tag import Int64Tag
from rapidnbt._NBT.float_tag import FloatTag
from rapidnbt._NBT.double_tag import DoubleTag
from rapidnbt._NBT.byte_array_tag import ByteArrayTag
from rapidnbt._NBT.string_tag import StringTag
from rapidnbt._NBT.list_tag import ListTag
from rapidnbt._NBT.compound_tag import CompoundTag
from rapidnbt._NBT.int_array_tag import IntArrayTag
from rapidnbt._NBT.long_array_tag import LongArrayTag
from rapidnbt._NBT.nbtio import NbtCompressionLevel, NbtCompressionType, NbtFileFormat
from rapidnbt._NBT import nbtio

__all__ = [
    "TagType",
    "SnbtFormat",
    "CompoundTagVariant",
    "Tag",
    "EndTag",
    "ByteTag",
    "ShortTag",
    "IntTag",
    "Int64Tag",
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
]
