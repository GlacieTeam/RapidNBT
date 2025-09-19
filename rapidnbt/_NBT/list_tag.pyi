# Copyright © 2025 GlacieTeam.All rights reserved.
#
# This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy
# of the MPL was not distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
#
# SPDX-License-Identifier: MPL-2.0

from typing import overload, List, Any
from rapidnbt._NBT.tag import Tag
from rapidnbt._NBT.tag_type import TagType

class ListTag(Tag):
    def __eq__(self, other: Tag) -> bool:
        """Equality operator (==)"""

    def __getitem__(self, index: int) -> Tag:
        """Get element at specified index"""

    def __hash__(self) -> int:
        """Compute hash value for Python hashing operations"""

    @overload
    def __init__(self) -> None:
        """Construct an empty ListTag"""

    @overload
    def __init__(self, elements: List[Any]) -> None:
        """Construct from a list of Tag elements (e.g., [IntTag(1), StringTag('test')])"""

    def __iter__(self) -> List[Tag]:
        """Iterate over elements in the list"""

    def __len__(self) -> int:
        """Get number of elements in the list"""

    def __repr__(self) -> str:
        """Official string representation"""

    def __setitem__(self, index: int, element: Any) -> None:
        """Set element at specified index"""

    def __str__(self) -> str:
        """String representation (SNBT minimized format)"""

    def append(self, element: Any) -> None:
        """Append a Tag element to the list"""

    def clear(self) -> None:
        """Remove all elements from the list"""

    def copy(self) -> Tag:
        """Create a deep copy of this tag"""

    def copy_list(self) -> ListTag:
        """Create a deep copy of this list (same as copy() but returns ListTag)"""

    def empty(self) -> bool:
        """Check if the list is empty"""

    def equals(self, other: Tag) -> bool:
        """Check if this tag equals another tag (same elements in same order)"""

    def get_element_type(self) -> TagType:
        """Get the type of elements in this list (returns nbt.Type enum)"""

    def get_type(self) -> TagType:
        """Get the NBT type ID (List)"""

    def hash(self) -> int:
        """Compute hash value of this tag"""

    def insert(self, index: int, element: Any) -> None:
        """Insert element at specified position"""

    def load(self, stream: ...) -> None:
        """Load list from a binary stream"""

    def merge(self, other: ListTag) -> None:
        """Merge another ListTag into this one (appends all elements)"""

    @overload
    def pop(self, index: int) -> bool:
        """Remove element at specified index"""

    @overload
    def pop(self, start_index: int, end_index: int) -> bool:
        """Remove elements in the range [start_index, end_index)"""

    def reserve(self, size: int) -> None:
        """Preallocate memory for future additions"""

    def size(self) -> int:
        """Get number of elements in the list"""

    def write(self, stream: ...) -> None:
        """Write list to a binary stream"""
