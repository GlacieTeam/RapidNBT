# Copyright © 2025 GlacieTeam.All rights reserved.
#
# This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy
# of the MPL was not distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
#
# SPDX-License-Identifier: MPL-2.0

from typing import overload, List, Union
from rapidnbt._NBT.tag import Tag
from rapidnbt._NBT.tag_type import TagType

class ByteArrayTag(Tag):
    def __bytes__(self) -> bytes:
        """Convert to Python bytes object"""

    def __eq__(self, other: Tag) -> bool:
        """Equality operator (==)"""

    def __getitem__(self, index: int) -> int:
        """Get byte at specified index"""

    def __hash__(self) -> int:
        """Compute hash value for Python hashing operations"""

    @overload
    def __init__(self) -> None:
        """Construct an empty ByteArrayTag"""

    @overload
    def __init__(self, arr: List[int]) -> None:
        """Construct from a list of bytes (e.g., [1, 2, 3])"""

    def __iter__(self) -> List[int]:
        """Iterate over bytes in the array"""

    def __len__(self) -> int:
        """Get number of bytes in the array"""

    def __repr__(self) -> str:
        """Official string representation"""

    def __setitem__(self, index: int, value: int) -> None:
        """Set byte at specified index"""

    def __str__(self) -> str:
        """String representation (SNBT minimized format)"""

    def append(self, value: int) -> None:
        """Add a byte to the end of the array"""

    def assign(self, bytes: Union[bytes, bytearray]) -> ByteArrayTag:
        """Assign new binary data from a list of bytes"""

    def clear(self) -> None:
        """Clear all byte data"""

    def copy(self) -> Tag:
        """Create a deep copy of this tag"""

    def data(self) -> memoryview:
        """Get a raw memory view of the byte data"""

    def equals(self, other: Tag) -> bool:
        """Check if this tag equals another tag (same bytes and type)"""

    def get_type(self) -> TagType:
        """Get the NBT type ID (ByteArray)"""

    def hash(self) -> int:
        """Compute hash value of this tag"""

    def load(self, stream: ...) -> None:
        """Load tag value from a binary stream"""

    @overload
    def pop(self, index: int) -> bool:
        """Remove byte at specified index"""

    @overload
    def pop(self, start_index: int, end_index: int) -> bool:
        """Remove bytes in the range [start_index, end_index)"""

    def reserve(self, size: int) -> None:
        """Preallocate memory for future additions"""

    def size(self) -> int:
        """Get number of bytes in the array"""

    def write(self, stream: ...) -> None:
        """Write tag to a binary stream"""

    @property
    def value(self) -> bytes:
        """Access the byte array as a list of integers (0-255)"""

    @value.setter
    def value(self, value: Union[bytes, bytearray]) -> None: ...
