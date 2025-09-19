# Copyright © 2025 GlacieTeam.All rights reserved.
#
# This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy
# of the MPL was not distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
#
# SPDX-License-Identifier: MPL-2.0

from typing import overload
from rapidnbt._NBT.tag import Tag
from rapidnbt._NBT.tag_type import TagType

class FloatTag(Tag):
    def __eq__(self, other: Tag) -> bool:
        """Equality operator (==)"""

    def __float__(self) -> float:
        """Convert to Python float (for float(tag) operations)"""

    def __hash__(self) -> int:
        """Compute hash value for Python hashing operations"""

    @overload
    def __init__(self) -> None:
        """Construct a FloatTag with default value (0.0)"""

    @overload
    def __init__(self, value: float) -> None:
        """Construct a FloatTag from a floating-point value"""

    def __repr__(self) -> str:
        """Official string representation including type information"""

    def __str__(self) -> str:
        """String representation (SNBT minimized format)"""

    def assign(self, value: float) -> FloatTag:
        """Assign a new floating-point value to this tag"""

    def copy(self) -> Tag:
        """Create a deep copy of this tag"""

    def equals(self, other: Tag) -> bool:
        """Check if this tag equals another tag"""

    def get_type(self) -> TagType:
        """Get the NBT type ID (Float)"""

    def hash(self) -> int:
        """Compute hash value of this tag"""

    def load(self, stream: ...) -> None:
        """Load tag value from a binary stream"""

    def write(self, stream: ...) -> None:
        """Write tag to a binary stream"""

    @property
    def value(self) -> float:
        """Access the floating-point value of this tag"""

    @value.setter
    def value(self, value: float) -> None: ...
