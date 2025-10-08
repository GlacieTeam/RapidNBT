# Copyright © 2025 GlacieTeam.All rights reserved.
#
# This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy
# of the MPL was not distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
#
# SPDX-License-Identifier: MPL-2.0

from typing import overload, List, Any, Dict, Union
from rapidnbt._NBT.snbt_format import SnbtFormat
from rapidnbt._NBT.tag_type import TagType
from rapidnbt._NBT.tag import Tag
from rapidnbt._NBT.end_tag import EndTag
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

TagVariant = Union[
    EndTag,
    ByteTag,
    ShortTag,
    IntTag,
    LongTag,
    FloatTag,
    DoubleTag,
    StringTag,
    ByteArrayTag,
    CompoundTag,
    ListTag,
    IntArrayTag,
    LongArrayTag,
]

class CompoundTagVariant:
    """
    A warpper of all tags, to provide morden API for NBT
    """

    def __contains__(self, index: str) -> bool:
        """
        Check if the value is in the CompoundTag.
        Throw TypeError is not hold a CompoundTag.
        """

    def __eq__(self, other: CompoundTagVariant) -> bool:
        """
        Check if this tag equals another tag"""

    def __float__(self) -> float:
        """
        Implicitly convert to float"""

    @overload
    def __getitem__(self, index: int) -> Tag:
        """
        Get value by object key
        """

    @overload
    def __getitem__(self, index: str) -> CompoundTagVariant:
        """
        Get value by array index
        """

    @overload
    def __init__(self) -> None:
        """
        Default Constructor
        """

    @overload
    def __init__(self, value: Any) -> None:
        """
        Construct from any Python object
        """

    def __int__(self) -> int:
        """
        Implicitly convert to int
        """

    def __iter__(self) -> List[CompoundTagVariant]:
        """
        Iterate over tags in the tag variant"""

    def __len__(self) -> int:
        """
        Get the size of the tag
        """

    def __repr__(self) -> str:
        """
        Official string representation
        """

    @overload
    def __setitem__(self, index: str, value: Any) -> None:
        """
        Set value by object key
        """

    @overload
    def __setitem__(self, index: int, value: Any) -> None:
        """
        Set value by array index
        """

    def __str__(self) -> str:
        """
        String representation (SNBT minimized format)
        """

    def append(self, value: Any) -> None:
        """
        Append a Tag element if self is ListTag
        Throw TypeError if wrong type
        """

    def assign(self, value: Any) -> None:
        """Assign value"""

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

    def get(self) -> TagVariant:
        """
        Get the tag variant
        """

    def get_byte(self) -> int:
        """
        Get the byte value
        Throw TypeError if wrong type
        """

    def get_bytes(self) -> bytes:
        """
        Get the original string value (bytes in StringTag)
        Throw TypeError if wrong type
        """

    def get_byte_array(self) -> bytes:
        """
        Get the byte array value
        Throw TypeError if wrong type
        """

    def get_compound(self) -> Dict[str, CompoundTagVariant]:
        """
        Get the CompoundTag as a dict value
        Throw TypeError if wrong type
        """

    def get_double(self) -> float:
        """
        Get the double value
        Throw TypeError if wrong type
        """

    def get_float(self) -> float:
        """
        Get the float value
        Throw TypeError if wrong type
        """

    def get_int(self) -> int:
        """
        Get the int value
        Throw TypeError if wrong type
        """

    def get_long(self) -> int:
        """
        Get the int64 value
        Throw TypeError if wrong type
        """

    def get_int_array(self) -> List[int]:
        """
        Get the int array value
        Throw TypeError if wrong type
        """

    def get_list(self) -> List[CompoundTagVariant]:
        """
        Get the ListTag as a list value
        Throw TypeError if wrong type
        """

    def get_long_array(self) -> List[int]:
        """
        Get the long array value
        Throw TypeError if wrong type
        """

    def get_short(self) -> int:
        """
        Get the short value
        Throw TypeError if wrong type
        """

    def get_string(self) -> str:
        """
        Get the string value
        Throw TypeError if wrong type
        """

    @overload
    def contains(self, index: str) -> bool:
        """
        Check if the value is in the CompoundTag.
        Throw TypeError is not hold a CompoundTag.
        """

    @overload
    def contains(self, key: str, type: TagType) -> bool:
        """
        Check if the value is in the CompoundTag and value type is the specific type.
        Throw TypeError is not hold a CompoundTag.
        """

    def clear(self) -> None:
        """
        Clear the data in the tag
        Throw TypeError if the tag can not be cleared.
        """

    def copy(self) -> Tag:
        """
        Create a deep copy of this tag
        """

    def get_type(self) -> TagType:
        """
        Get the NBT type ID
        """

    def hold(self, type: TagType) -> bool:
        """
        Check the NBT type ID
        """

    def is_array(self) -> bool:
        """
        Check whether the tag is a ListTag
        """

    def is_binary(self) -> bool:
        """
        Check whether the tag is a binary tag
        Example:
            ByteArrayTag, IntArrayTag, LongArrayTag
        """

    def is_boolean(self) -> bool:
        """
        Check whether the tag is a ByteTag
        """

    def is_null(self) -> bool:
        """
        Check whether the tag is an EndTag
        """

    def is_number(self) -> bool:
        """
        Check whether the tag is a number based tag
        Example:
            ByteTag, ShortTag, IntTag, LongTag, FloatTag, DoubleTag
        """

    def is_number_float(self) -> bool:
        """
        Check whether the tag is a float number based tag
        Example:
            FloatTag, DoubleTag
        """

    def is_number_integer(self) -> bool:
        """
        Check whether the tag is a integer number based tag
        Example:
            ByteTag, ShortTag, IntTag, LongTag
        """

    def is_object(self) -> bool:
        """
        Check whether the tag is a CompoundTag
        """

    def is_primitive(self) -> bool:
        """
        Check whether the tag is a primitive tag
        Example:
            ByteTag, ShortTag, IntTag, LongTag, FloatTag, DoubleTag, StringTag, ByteArrayTag, IntArrayTag, LongArrayTag
        """

    def is_string(self) -> bool:
        """
        Check whether the tag is a StringTag
        """

    def is_structured(self) -> bool:
        """
        Check whether the tag is a structured tag
        Example:
            CompoundTag, ListTag
        """

    def items(self) -> list:
        """
        Get list of (key, value) pairs in this tag
        Throw TypeError if wrong type
        """

    def merge(self, other: CompoundTagVariant, merge_list: bool = False) -> None:
        """
        Merge another CompoundTag into this one

        Arguments:
            other: CompoundTag to merge from
            merge_list: If true, merge list contents instead of replacing
        """

    @overload
    def pop(self, index: str) -> bool:
        """
        Remove key from the CompoundTag
        Throw TypeError if wrong type
        """

    @overload
    def pop(self, index: int) -> bool:
        """
        Remove key from the ListTag
        Throw TypeError if wrong type
        """

    def rename(self, index: str, new_name: str) -> bool:
        """
        Rename a key in the CompoundTag
        Throw TypeError if wrong type
        """

    def size(self) -> int:
        """
        Get the size of the tag
        """

    def to_json(self, indent: int = 4) -> str:
        """
        Convert tag to JSON string
        """

    def to_snbt(
        self, snbt_format: SnbtFormat = SnbtFormat.Default, indent: int = 4
    ) -> str:
        """
        Convert tag to SNBT string
        """

    @property
    def value(self) -> Any:
        """
        Access the tag value
        """

    @value.setter
    def value(self, value: Any) -> None:
        """
        Access the tag value
        """
