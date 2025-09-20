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

class Tag(ABC):
    """
    Base class for all NBT tags
    """

    @staticmethod
    def new_tag(type: TagType) -> Tag:
        """Create a new tag of the given type"""

    def __eq__(self, other: Tag) -> bool:
        """Compare two tags for equality"""

    @overload
    def __getitem__(self, index: int) -> Tag: ...
    @overload
    def __getitem__(self, key: str) -> CompoundTagVariant: ...
    def __hash__(self) -> int: ...
    def __repr__(self) -> str: ...
    def __str__(self) -> str: ...
    def as_bytes(self) -> bytes:
        """Convert tag to bytes"""

    def as_string(self) -> str:
        """Convert tag to string"""

    @abstractmethod
    def copy(self) -> Tag:
        """Create a deep copy of this tag"""

    @abstractmethod
    def equals(self, other: Tag) -> bool:
        """Check if this tag equals another tag"""

    @abstractmethod
    def get_type(self) -> TagType:
        """Get the type of this tag"""

    @abstractmethod
    def hash(self) -> int:
        """Compute hash value of this tag"""

    @abstractmethod
    def load(self, stream: ...) -> None:
        """Load tag from binary stream"""

    @abstractmethod
    def write(self, stream: ...) -> None:
        """Write tag to binary stream"""

    def to_json(self, indent: int = 4) -> str:
        """Convert tag to JSON string"""

    def to_snbt(self, format: SnbtFormat = SnbtFormat.Default, indent: int = 4) -> str:
        """Convert tag to SNBT string"""
