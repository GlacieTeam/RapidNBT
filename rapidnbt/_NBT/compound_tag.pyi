# Copyright © 2025 GlacieTeam.All rights reserved.
#
# This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy
# of the MPL was not distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
#
# SPDX-License-Identifier: MPL-2.0

from collections.abc import Buffer
from typing import overload, List, Dict, Optional, Any
from rapidnbt._NBT.tag import Tag
from rapidnbt._NBT.tag_type import TagType
from rapidnbt._NBT.compound_tag_variant import CompoundTagVariant

class CompoundTag(Tag):
    """
    A tag contains a tag compound
    """

    @staticmethod
    def from_binary_nbt(
        binary_data: Buffer,
        little_endian: bool = True,
        header: bool = False,
    ) -> Optional[CompoundTag]:
        """
        Deserialize from Binary NBT format
        """

    @staticmethod
    def from_json(
        snbt: str, parsed_length: Optional[int] = None
    ) -> Optional[CompoundTag]:
        """
        Parse from JSON string
        """

    @staticmethod
    def from_network_nbt(
        binary_data: Buffer,
    ) -> Optional[CompoundTag]:
        """
        Deserialize from Network NBT format
        """

    @staticmethod
    def from_snbt(
        snbt: str, parsed_length: Optional[int] = None
    ) -> Optional[CompoundTag]:
        """
        Parse from String NBT (SNBT) format
        """

    def __contains__(self, key: str) -> bool:
        """
        Check if key exists in the compound
        """

    def __delitem__(self, key: str) -> bool:
        """
        Remove key from the compound
        """

    def __eq__(self, other: Tag) -> bool:
        """
        Equality operator (==)
        """

    def __getitem__(self, key: str) -> CompoundTagVariant:
        """

        Get value by key (no exception, auto create if not found)
        """

    def __hash__(self) -> int:
        """
        Compute hash value for Python hashing operations
        """

    @overload
    def __init__(self) -> None:
        """
        Construct an empty CompoundTag
        """

    @overload
    def __init__(self, pairs: Dict[str, Any]) -> None:
        """
        Construct from a Dict[str, Any]
        Example:
            CompoundTag(["key1": 42, "key2": "value"])

        """

    def __iter__(self) -> List[str]:
        """
        Iterate over keys in the compound
        """

    def __len__(self) -> int:
        """

        Get number of key-value pairs
        """

    def __repr__(self) -> str:
        """
        Official string representation
        """

    def __setitem__(self, key: str, value: Any) -> None:
        """
        Set value by key
        """

    def __str__(self) -> str:
        """
        String representation (SNBT minimized format)
        """

    def clear(self) -> None:
        """
        Remove all elements from the compound
        """

    @overload
    def contains(self, key: str) -> bool:
        """
        Check if key exists
        """

    @overload
    def contains(self, key: str, type: TagType) -> bool:
        """
        Check if key exists and value type is the specific type
        """

    def copy(self) -> Tag:
        """
        Create a deep copy of this tag
        """

    def deserialize(self, stream: ...) -> None:
        """
        Deserialize compound from a binary stream
        """

    def empty(self) -> bool:
        """
        Check if the compound is empty
        """

    def equals(self, other: Tag) -> bool:
        """
        Check if this tag equals another tag
        """

    def get(self, key: str) -> CompoundTagVariant:
        """
        Get tag by key
        Throw KeyError if not found
        """

    def get_type(self) -> TagType:
        """
        Get the NBT type ID (Compound)
        """

    def hash(self) -> int:
        """
        Compute hash value of this tag
        """

    def items(self) -> list:
        """
        Get list of (key, value) pairs in the compound
        """

    def keys(self) -> list:
        """
        Get list of all keys in the compound
        """

    def load(self, stream: ...) -> None:
        """
        Load compound from a binary stream
        """

    def merge(self, other: CompoundTag, merge_list: bool = False) -> None:
        """
        Merge another CompoundTag into this one

        Arguments:
            other: CompoundTag to merge from
            merge_list: If true, merge list contents instead of replacing
        """

    def pop(self, key: str) -> bool:
        """
        Remove key from the compound
        """

    def rename(self, old_key: str, new_key: str) -> bool:
        """
        Rename a key in the compound
        """

    def set(self, key: str, value: Any) -> None:
        """
        Set a value into the compound (automatically converted to appropriate tag type)
        """

    def serialize(self, stream: ...) -> None:
        """
        Serialize compound to a binary stream
        """

    def size(self) -> int:
        """
        Get the size of the compound
        """

    def to_binary_nbt(self, little_endian: bool = True, header: bool = False) -> bytes:
        """
        Serialize to binary NBT format
        """

    def to_dict(self) -> dict:
        """
        Convert CompoundTag to a Python dictionary
        """

    def to_network_nbt(self) -> bytes:
        """
        Serialize to Network NBT format (used in Minecraft networking)
        """

    def values(self) -> list:
        """
        Get list of all values in the compound
        """

    def write(self, stream: ...) -> None:
        """
        Write compound to a binary stream
        """

    @property
    def value(self) -> Dict[str, CompoundTagVariant]:
        """
        Access the dict value of this tag
        """

    @value.setter
    def value(self, value: Dict[str, Any]) -> None:
        """
        Access the dict value of this tag
        """
