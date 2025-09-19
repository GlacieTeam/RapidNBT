# Copyright © 2025 GlacieTeam.All rights reserved.
#
# This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy
# of the MPL was not distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
#
# SPDX-License-Identifier: MPL-2.0

from typing import overload, List, Dict, Union, Optional, Any
from rapidnbt._NBT.tag import Tag
from rapidnbt._NBT.tag_type import TagType
from rapidnbt._NBT.compound_tag_variant import CompoundTagVariant
from rapidnbt._NBT.byte_tag import ByteTag
from rapidnbt._NBT.short_tag import ShortTag
from rapidnbt._NBT.int_tag import IntTag
from rapidnbt._NBT.int64_tag import Int64Tag
from rapidnbt._NBT.float_tag import FloatTag
from rapidnbt._NBT.double_tag import DoubleTag
from rapidnbt._NBT.byte_array_tag import ByteArrayTag
from rapidnbt._NBT.string_tag import StringTag
from rapidnbt._NBT.list_tag import ListTag
from rapidnbt._NBT.int_array_tag import IntArrayTag
from rapidnbt._NBT.long_array_tag import LongArrayTag

class CompoundTag(Tag):
    @staticmethod
    def from_binary_nbt(
        binary_data: Union[bytes, bytearray],
        little_endian: bool = True,
        header: bool = False,
    ) -> Optional[CompoundTag]:
        """Deserialize from binary NBT format"""

    @staticmethod
    def from_network_nbt(
        binary_data: Union[bytes, bytearray],
    ) -> Optional[CompoundTag]:
        """Deserialize from Network NBT format"""

    @staticmethod
    def from_snbt(
        snbt: str, parsed_length: Optional[int] = None
    ) -> Optional[CompoundTag]:
        """Parse from String NBT (SNBT) format"""

    def __contains__(self, key: str) -> bool:
        """Check if key exists in the compound"""

    def __delitem__(self, key: str) -> bool:
        """Remove key from the compound"""

    def __eq__(self, other: Tag) -> bool:
        """Equality operator (==)"""

    def __getitem__(self, key: str) -> CompoundTagVariant:
        """Get value by key (no exception, auto create if not found)"""

    def __hash__(self) -> int:
        """Compute hash value for Python hashing operations"""

    @overload
    def __init__(self) -> None:
        """Construct an empty CompoundTag"""

    @overload
    def __init__(self, pairs: Dict[str, Any]) -> None:
        """Construct from a Dict[str, Any]
        Example:
            CompoundTag(["key1": 42, "key2": "value"])
        """

    def __iter__(self) -> List[str]:
        """Iterate over keys in the compound"""

    def __len__(self) -> int:
        """Get number of key-value pairs"""

    def __repr__(self) -> str:
        """Official string representation"""

    def __setitem__(self, key: str, value: Any) -> None:
        """Set value by key"""

    def __str__(self) -> str:
        """String representation (SNBT minimized format)"""

    def clear(self) -> None:
        """Remove all elements from the compound"""

    def clone(self) -> CompoundTag:
        """Create a deep copy of this compound tag"""

    def contains(self, key: str) -> bool:
        """Check if key exists"""

    def copy(self) -> Tag:
        """Create a deep copy of this tag"""

    def deserialize(self, stream: ...) -> None:
        """Deserialize compound from a binary stream"""

    def empty(self) -> bool:
        """Check if the compound is empty"""

    def equals(self, other: Tag) -> bool:
        """Check if this tag equals another tag"""

    def get(self, key: str) -> Tag:
        """Get tag by key or None if not found"""

    def get_byte_tag(self, key: str) -> Optional[ByteTag]:
        """Get ByteTag or None if not found or wrong type"""

    def get_byte_array_tag(self, key: str) -> Optional[ByteArrayTag]:
        """Get ByteArrayTag or None if not found or wrong type"""

    def get_compound_tag(self, key: str) -> Optional[CompoundTag]:
        """Get CompoundTag or None if not found or wrong type"""

    def get_double_tag(self, key: str) -> Optional[DoubleTag]:
        """Get DoubleTag or None if not found or wrong type"""

    def get_float_tag(self, key: str) -> Optional[FloatTag]:
        """Get FloatTag value or None if not found or wrong type"""

    def get_int_tag(self, key: str) -> Optional[IntTag]:
        """Get IntTag or None if not found or wrong type"""

    def get_int64_tag(self, key: str) -> Optional[Int64Tag]:
        """Get Int64Tag or None if not found or wrong type"""

    def get_int_array_tag(self, key: str) -> Optional[IntArrayTag]:
        """Get IntArrayTag or None if not found or wrong type"""

    def get_list_tag(self, key: str) -> Optional[ListTag]:
        """Get ListTag or None if not found or wrong type"""

    def get_long_array_tag(self, key: str) -> Optional[LongArrayTag]:
        """Get LongArrayTag or None if not found or wrong type"""

    def get_short_tag(self, key: str) -> Optional[ShortTag]:
        """Get ShortTag or None if not found or wrong type"""

    def get_string_tag(self, key: str) -> Optional[StringTag]:
        """Get StringTag or None if not found or wrong type"""

    def get_byte(self, key: str) -> Optional[int]:
        """Get byte value or None if not found or wrong type"""

    def get_byte_array(self, key: str) -> Optional[bytes]:
        """Get byte array or None if not found or wrong type"""

    def get_compound(self, key: str) -> Optional[Dict[str, CompoundTagVariant]]:
        """Get CompoundTag or None if not found or wrong type"""

    def get_double(self, key: str) -> Optional[float]:
        """Get double value or None if not found or wrong type"""

    def get_float(self, key: str) -> Optional[float]:
        """Get float value or None if not found or wrong type"""

    def get_int(self, key: str) -> Optional[int]:
        """Get int value or None if not found or wrong type"""

    def get_int64(self, key: str) -> Optional[int]:
        """Get long value or None if not found or wrong type"""

    def get_int_array(self, key: str) -> Optional[List[int]]:
        """Get int array or None if not found or wrong type"""

    def get_list(self, key: str) -> Optional[List[CompoundTagVariant]]:
        """Get ListTag or None if not found or wrong type"""

    def get_long_array(self, key: str) -> Optional[List[int]]:
        """Get long array or None if not found or wrong type"""

    def get_short(self, key: str) -> Optional[int]:
        """Get short value or None if not found or wrong type"""

    def get_string(self, key: str) -> Optional[str]:
        """Get string value or None if not found or wrong type"""

    def get_type(self) -> TagType:
        """Get the NBT type ID (Compound)"""

    def hash(self) -> int:
        """Compute hash value of this tag"""

    def items(self) -> list:
        """Get list of (key, value) pairs in the compound"""

    def keys(self) -> list:
        """Get list of all keys in the compound"""

    def load(self, stream: ...) -> None:
        """Load compound from a binary stream"""

    def merge(self, other: CompoundTag, merge_list: bool = False) -> None:
        """Merge another CompoundTag into this one
        Arguments:
            other: CompoundTag to merge from
            merge_list: If true, merge list contents instead of replacing
        """

    def put(self, key: str, value: Any) -> None:
        """Put a value into the compound (automatically converted to appropriate tag type)"""

    def put_byte(self, key: str, value: int) -> None:
        """Put a byte (uint8) value"""

    def put_byte_array(self, key: str, value: Union[bytes, bytearray]) -> None:
        """Put a byte array (list of uint8)"""

    def put_compound(self, key: str, value: Any) -> None:
        """Put a CompoundTag value (or dict that will be converted)"""

    def put_double(self, key: str, value: float) -> None:
        """Put a double value"""

    def put_float(self, key: str, value: float) -> None:
        """Put a float value"""

    def put_int(self, key: str, value: int) -> None:
        """Put an int (int32) value"""

    def put_int64(self, key: str, value: int) -> None:
        """Put a long (int64) value"""

    def put_int_array(self, key: str, value: List[int]) -> None:
        """Put an int array (list of int32)"""

    def put_list(self, key: str, value: Any) -> None:
        """Put a ListTag value (or list/tuple that will be converted)"""

    def put_long_array(self, key: str, value: List[int]) -> None:
        """Put a long array (list of int64)"""

    def put_short(self, key: str, value: int) -> None:
        """Put a short (int16) value"""

    def put_string(self, key: str, value: str) -> None:
        """Put a string value"""

    def rename(self, old_key: str, new_key: str) -> bool:
        """Rename a key in the compound"""

    def set(self, key: str, value: Any) -> None:
        """Set a value into the compound (automatically converted to appropriate tag type)"""

    def set_byte(self, key: str, value: int) -> None:
        """Set a byte (uint8) value"""

    def set_byte_array(self, key: str, value: Union[bytes, bytearray]) -> None:
        """Set a byte array (list of uint8)"""

    def set_compound(self, key: str, value: Any) -> None:
        """Set a CompoundTag value (or dict that will be converted)"""

    def set_double(self, key: str, value: float) -> None:
        """Set a double value"""

    def set_float(self, key: str, value: float) -> None:
        """Set a float value"""

    def set_int(self, key: str, value: int) -> None:
        """Set an int (int32) value"""

    def set_int64(self, key: str, value: int) -> None:
        """Set a long (int64) value"""

    def set_int_array(self, key: str, value: List[int]) -> None:
        """Set an int array (list of int32)"""

    def set_list(self, key: str, value: Any) -> None:
        """Set a ListTag value (or list/tuple that will be converted)"""

    def set_long_array(self, key: str, value: List[int]) -> None:
        """Set a long array (list of int64)"""

    def set_short(self, key: str, value: int) -> None:
        """Set a short (int16) value"""

    def set_string(self, key: str, value: str) -> None:
        """Set a string value"""

    def serialize(self, stream: ...) -> None:
        """Serialize compound to a binary stream"""

    def to_binary_nbt(self, little_endian: bool = True, header: bool = False) -> bytes:
        """Serialize to binary NBT format"""

    def to_dict(self) -> dict:
        """Convert CompoundTag to a Python dictionary"""

    def to_network_nbt(self) -> bytes:
        """Serialize to Network NBT format (used in Minecraft networking)"""

    def values(self) -> list:
        """Get list of all values in the compound"""

    def write(self, stream: ...) -> None:
        """Write compound to a binary stream"""
