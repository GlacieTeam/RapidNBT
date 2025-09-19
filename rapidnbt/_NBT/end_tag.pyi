# Copyright © 2025 GlacieTeam.All rights reserved.
#
# This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy
# of the MPL was not distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
#
# SPDX-License-Identifier: MPL-2.0

from rapidnbt._NBT.tag import Tag
from rapidnbt._NBT.tag_type import TagType

class EndTag(Tag):
    def __eq__(self, other: Tag) -> bool:
        """Equality operator (==), all EndTags are equal"""

    def __hash__(self) -> int:
        """Compute hash value for Python hashing operations"""

    def __init__(self) -> None:
        """Construct an EndTag"""

    def __repr__(self) -> str:
        """Official string representation"""

    def __str__(self) -> str:
        """String representation (SNBT minimized format)"""

    def copy(self) -> Tag:
        """Create a deep copy of this tag"""

    def equals(self, other: Tag) -> bool:
        """Check if this tag equals another tag (all EndTags are equal)"""

    def get_type(self) -> TagType:
        """Get the NBT type ID (End)"""

    def hash(self) -> int:
        """Compute hash value of this tag"""

    def load(self, stream: ...) -> None:
        """Load tag value from a binary stream (no data for EndTag)"""

    def write(self, stream: ...) -> None:
        """Write tag to a binary stream (no data for EndTag)"""
