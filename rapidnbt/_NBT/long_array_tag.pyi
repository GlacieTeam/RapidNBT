# Copyright © 2025 GlacieTeam.All rights reserved.
#
# This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy
# of the MPL was not distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
#
# SPDX-License-Identifier: MPL-2.0

from typing import overload, List
from rapidnbt._NBT.tag import Tag
from rapidnbt._NBT.tag_type import TagType

class LongArrayTag(Tag):
    def __hash__(self) -> int: ...
    def __contains__(self, value: int) -> bool:
        """Check if value is in the array"""

    def __eq__(self, other: LongArrayTag) -> bool: ...
    def __getitem__(self, index: int) -> int:
        """Get element at index without bounds checking"""

    @overload
    def __init__(self) -> None:
        """Construct an empty LongArrayTag"""

    @overload
    def __init__(self, values: List[int]) -> None:
        """Construct from a list of integers
        Example:
            LongArrayTag([1, 2, 3])
        """

    def __iter__(self) -> List[int]:
        """Iterate over elements in the array
        Example:
            for value in int_array:
                print(value)
        """

    def __repr__(self) -> str:
        """Official string representation"""

    def __setitem__(self, index: int, value: int) -> None:
        """Set element at index"""

    def __str__(self) -> str:
        """String representation (SNBT minimized format)"""

    def append(self, value: int) -> None:
        """Append an integer to the end of the array"""

    def assign(self, values: List[int]) -> LongArrayTag:
        """Assign new values to the array
        Returns the modified array
        """

    def clear(self) -> None:
        """Remove all elements from the array"""

    def copy(self) -> Tag:
        """Create a deep copy of this tag"""

    def empty(self) -> bool:
        """Check if the array is empty"""

    def equals(self, other: Tag) -> bool:
        """Check if this tag equals another tag"""

    def get_type(self) -> TagType:
        """Get the NBT type ID (int array)"""

    def hash(self) -> int:
        """Compute hash value of this tag"""

    def load(self, stream: ...) -> None:
        """Load int array from a binary stream"""

    @overload
    def pop(self, index: int) -> bool:
        """Remove element at specified index
        Returns True if successful, False if index out of range
        """

    @overload
    def pop(self, start_index: int, end_index: int) -> bool:
        """Remove elements in the range [start_index, end_index)
        Arguments:
            start_index: First index to remove (inclusive)\\n"
            end_index: End index (exclusive)\\n"
        Returns True if successful, False if indices out of range
        """

    def reserve(self, capacity: int) -> None:
        """Reserve storage capacity for the array
        Arguments:
            capacity: Minimum capacity to reserv)
        """

    def size(self) -> int:
        """Get number of elements in the array"""

    def write(self, stream: ...) -> None:
        """Write int array to a binary stream"""
