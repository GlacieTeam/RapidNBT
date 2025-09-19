# Copyright © 2025 GlacieTeam.All rights reserved.
#
# This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy
# of the MPL was not distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
#
# SPDX-License-Identifier: MPL-2.0

from typing import overload
from rapidnbt._NBT.tag import Tag
from rapidnbt._NBT.tag_type import TagType

class StringTag(Tag):
    def __eq__(self, other: StringTag) -> bool:
        """Equality operator (==), case-sensitive comparison"""

    def __getitem__(self, index: int) -> str:
        """Get character at specified position"""

    def __hash__(self) -> int:
        """Compute hash value for Python hashing operations"""

    @overload
    def __init__(self) -> None:
        """Construct an empty StringTag"""

    @overload
    def __init__(self, str: str) -> None:
        """Construct from a Python string"""

    def __len__(self) -> int:
        """Get the length of the string in bytes"""

    def __repr__(self) -> str:
        """Official representation with quoted content"""

    def __str__(self) -> str:
        """String representation (SNBT minimized format)"""

    def copy(self) -> Tag:
        """Create a deep copy of this tag"""

    def equals(self, other: Tag) -> bool:
        """Check if this tag equals another tag (same content and type)"""

    def get_type(self) -> TagType:
        """Get the NBT type ID (String)"""

    def hash(self) -> int:
        """Compute hash value of this tag (based on string content)"""

    def load(self, stream: ...) -> None:
        """Load tag value from a binary stream (UTF-8)"""

    def size(self) -> int:
        """Get the length of the string in bytes"""

    def write(self, stream: ...) -> None:
        """Write tag to a binary stream (UTF-8 encoded)"""

    @property
    def value(self) -> str:
        """Access the string content of this tag"""

    @value.setter
    def value(self, value: str) -> None: ...
