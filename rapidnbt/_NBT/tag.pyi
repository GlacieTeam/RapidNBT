# Copyright © 2025 GlacieTeam.All rights reserved.
#
# This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy
# of the MPL was not distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
#
# SPDX-License-Identifier: MPL-2.0

from typing import overload
from abc import ABC, abstractmethod
from rapidnbt._NBT.compound_tag_variant import CompoundTagVariant
from rapidnbt._NBT.snbt_format import SnbtFormat
from rapidnbt._NBT.tag_type import TagType
from rapidnbt._NBT.byte_tag import ByteTag
from rapidnbt._NBT.short_tag import ShortTag
from rapidnbt._NBT.int_tag import IntTag
from rapidnbt._NBT.long_tag import LongTag
from rapidnbt._NBT.float_tag import FloatTag
from rapidnbt._NBT.double_tag import DoubleTag
from rapidnbt._NBT.byte_array_tag import ByteArrayTag
from rapidnbt._NBT.string_tag import StringTag
from rapidnbt._NBT.list_tag import ListTag
from rapidnbt._NBT.compound_tag import CompoundTag
from rapidnbt._NBT.int_array_tag import IntArrayTag
from rapidnbt._NBT.long_array_tag import LongArrayTag

class Tag(ABC):
    """
    Base class for all NBT tags
    """

    @staticmethod
    def new_tag(type: TagType) -> Tag:
        """
        Create a new tag of the given type
        """

    def __eq__(self, other: Tag) -> bool:
        """
        Compare two tags for equality
        """

    @overload
    def __getitem__(self, index: int) -> Tag: ...
    @overload
    def __getitem__(self, key: str) -> CompoundTagVariant: ...
    def __hash__(self) -> int:
        """
        Compute hash value for Python hashing operations
        """

    def __repr__(self) -> str: ...
    def __str__(self) -> str: ...
    def as_byte_tag(self) -> ByteTag:
        """
        Convert to a ByteTag
        Throw TypeError if wrong type
        """

    def as_byte_array_tag(self) -> ByteArrayTag:
        """
        Convert to a ByteArrayTag
        Throw TypeError if wrong type
        """

    def as_compound_tag(self) -> CompoundTag:
        """
        Convert to a CompoundTag
        Throw TypeError if wrong type
        """

    def as_double_tag(self) -> DoubleTag:
        """
        Convert to a DoubleTag
        Throw TypeError if wrong type
        """

    def as_float_tag(self) -> FloatTag:
        """
        Convert to a FLoatTag
        Throw TypeError if wrong type
        """

    def as_int_tag(self) -> IntTag:
        """
        Convert to a IntTag
        Throw TypeError if wrong type
        """

    def as_long_tag(self) -> LongTag:
        """
        Convert to a LongTag
        Throw TypeError if wrong type
        """

    def as_int_array_tag(self) -> IntArrayTag:
        """
        Convert to a IntArrayTag
        Throw TypeError if wrong type
        """

    def as_list_tag(self) -> ListTag:
        """
        Convert to a ListTag
        Throw TypeError if wrong type
        """

    def as_long_array_tag(self) -> LongArrayTag:
        """
        Convert to a LongArrayTag
        Throw TypeError if wrong type
        """

    def as_short_tag(self) -> ShortTag:
        """
        Convert to a ShortTag
        Throw TypeError if wrong type
        """

    def as_string_tag(self) -> StringTag:
        """
        Convert to a StringTag
        Throw TypeError if wrong type
        """

    @abstractmethod
    def copy(self) -> Tag:
        """
        Create a deep copy of this tag
        """

    @abstractmethod
    def equals(self, other: Tag) -> bool:
        """
        Check if this tag equals another tag
        """

    @abstractmethod
    def get_type(self) -> TagType:
        """
        Get the type of this tag
        """

    @abstractmethod
    def hash(self) -> int:
        """
        Compute hash value of this tag
        """

    @abstractmethod
    def load(self, stream: ...) -> None:
        """
        Load tag from binary stream
        """

    @abstractmethod
    def write(self, stream: ...) -> None:
        """
        Write tag to binary stream
        """

    def to_json(self, indent: int = 4) -> str:
        """
        Convert tag to JSON string
        """

    def to_snbt(self, format: SnbtFormat = SnbtFormat.Default, indent: int = 4) -> str:
        """
        Convert tag to SNBT string
        """
