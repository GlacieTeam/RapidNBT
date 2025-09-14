# Copyright © 2025 GlacieTeam.All rights reserved.
#
# This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
# distributed with this file, You can obtain one at http:#mozilla.org/MPL/2.0/.
#
# SPDX-License-Identifier: MPL-2.0

from typing import overload, List, Dict, Union, Optional, Any
from enum import Enum
from abc import ABC, abstractmethod

"""Python bindings for NBT library"""

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
    def value(self, arg1: Union[bytes, bytearray]) -> None: ...

class ByteTag(Tag):
    def __eq__(self, other: Tag) -> bool:
        """Equality operator (==)"""

    def __hash__(self) -> int:
        """Compute hash value for Python hashing operations"""

    @overload
    def __init__(self) -> None:
        """Construct an ByteTag with default value (0)"""

    @overload
    def __init__(self, value: int) -> None:
        """Construct an ByteTag from an integer value"""

    def __int__(self) -> int:
        """Convert to Python int"""

    def __pos__(self) -> ByteTag:
        """Unary plus operator (+)"""

    def __repr__(self) -> str:
        """Official string representation"""

    def __str__(self) -> str:
        """String representation (SNBT minimized format)"""

    def assign(self, value: int) -> ByteTag:
        """Assign a new integer value to this tag"""

    def copy(self) -> Tag:
        """Create a deep copy of this tag"""

    def equals(self, other: Tag) -> bool:
        """Check if this tag equals another tag"""

    def get_type(self) -> TagType:
        """Get the NBT type ID (Byte)"""

    def hash(self) -> int:
        """Compute hash value of this tag"""

    def load(self, stream: ...) -> None:
        """Load tag value from a binary stream"""

    def write(self, stream: ...) -> None:
        """Write tag to a binary stream"""

    @property
    def value(self) -> int:
        """Access the integer value of this tag"""

    @value.setter
    def value(self, arg1: int) -> None: ...

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
    def __init__(self, pairs: dict) -> None:
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

    def get_byte(self, key: str) -> ByteTag:
        """Get byte value or None if not found or wrong type"""

    def get_byte_array(self, key: str) -> ByteArrayTag:
        """Get byte array or None if not found or wrong type"""

    def get_compound(self, key: str) -> CompoundTag:
        """Get CompoundTag or None if not found or wrong type"""

    def get_double(self, key: str) -> DoubleTag:
        """Get double value or None if not found or wrong type"""

    def get_float(self, key: str) -> FloatTag:
        """Get float value or None if not found or wrong type"""

    def get_int(self, key: str) -> IntTag:
        """Get int value or None if not found or wrong type"""

    def get_int64(self, key: str) -> Int64Tag:
        """Get long value or None if not found or wrong type"""

    def get_int_array(self, key: str) -> ...:
        """Get int array or None if not found or wrong type"""

    def get_list(self, key: str) -> ListTag:
        """Get ListTag or None if not found or wrong type"""

    def get_long_array(self, key: str) -> ...:
        """Get long array or None if not found or wrong type"""

    def get_short(self, key: str) -> ShortTag:
        """Get short value or None if not found or wrong type"""

    def get_string(self, key: str) -> StringTag:
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

class CompoundTagVariant:
    def __eq__(self, arg0: CompoundTagVariant) -> bool: ...
    def __float__(self) -> float: ...
    @overload
    def __getitem__(self, arg0: int) -> ...: ...
    @overload
    def __getitem__(self, arg0: str) -> CompoundTagVariant: ...
    @overload
    def __init__(self) -> None: ...
    @overload
    def __init__(self, arg0: Any) -> None: ...
    def __int__(self) -> int: ...
    def __iter__(self) -> List[CompoundTagVariant]: ...
    def __repr__(self) -> str:
        """Official string representation"""

    @overload
    def __setitem__(self, arg0: str, arg1: Any) -> None: ...
    @overload
    def __setitem__(self, arg0: int, arg1: Any) -> None: ...
    def __str__(self) -> str:
        """String representation (SNBT minimized format)"""

    def append(self, arg0: Any) -> None: ...
    def as_byte(self) -> ...: ...
    def as_byte_array(self) -> ...: ...
    def as_compound(self) -> ...: ...
    def as_double(self) -> ...: ...
    def as_float(self) -> ...: ...
    def as_int(self) -> ...: ...
    def as_int64(self) -> ...: ...
    def as_int_array(self) -> ...: ...
    def as_list(self) -> ...: ...
    def as_long_array(self) -> ...: ...
    def as_short(self) -> ...: ...
    def as_string(self) -> ...: ...
    def contains(self, arg0: str) -> bool: ...
    def copy(self) -> ...: ...
    def get_type(self) -> TagType: ...
    def hold(self, arg0: TagType) -> bool: ...
    def is_array(self) -> bool: ...
    def is_binary(self) -> bool: ...
    def is_boolean(self) -> bool: ...
    def is_null(self) -> bool: ...
    def is_number(self) -> bool: ...
    def is_number_float(self) -> bool: ...
    def is_number_integer(self) -> bool: ...
    def is_object(self) -> bool: ...
    def is_primitive(self) -> bool: ...
    def is_string(self) -> bool: ...
    def is_structured(self) -> bool: ...
    def items(self) -> list: ...
    def merge(self, other: CompoundTagVariant, merge_list: bool = False) -> None: ...
    @overload
    def pop(self, arg0: str) -> bool: ...
    @overload
    def pop(self, arg0: int) -> bool: ...
    def rename(self, arg0: str, arg1: str) -> bool: ...
    def size(self) -> int: ...
    def to_json(self, indent: int = 4) -> str: ...
    def to_snbt(self, snbt_format: SnbtFormat = ..., indent: int = 4) -> str: ...

class DoubleTag(Tag):
    def __eq__(self, other: Tag) -> bool:
        """Equality operator (==)"""

    def __float__(self) -> float:
        """Convert to Python float (for float(tag) operations)"""

    def __hash__(self) -> int:
        """Compute hash value for Python hashing operations"""

    @overload
    def __init__(self) -> None:
        """Construct a DoubleTag with default value (0.0)"""

    @overload
    def __init__(self, value: float) -> None:
        """Construct a DoubleTag from a floating-point value"""

    def __repr__(self) -> str:
        """Official string representation including type information"""

    def __str__(self) -> str:
        """String representation (SNBT minimized format)"""

    def assign(self, value: float) -> DoubleTag:
        """Assign a new floating-point value to this tag"""

    def copy(self) -> Tag:
        """Create a deep copy of this tag"""

    def equals(self, other: Tag) -> bool:
        """Check if this tag equals another tag"""

    def get_type(self) -> TagType:
        """Get the NBT type ID (Double)"""

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
    def value(self, arg1: float) -> None: ...

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
    def value(self, arg1: float) -> None: ...

class Int64Tag(Tag):
    def __eq__(self, other: Tag) -> bool:
        """Equality operator (==)"""

    def __hash__(self) -> int:
        """Compute hash value for Python hashing operations"""

    @overload
    def __init__(self) -> None:
        """Construct an Int64Tag with default value (0)"""

    @overload
    def __init__(self, value: int) -> None:
        """Construct an Int64Tag from an integer value"""

    def __int__(self) -> int:
        """Convert to Python int"""

    def __pos__(self) -> Int64Tag:
        """Unary plus operator (+)"""

    def __repr__(self) -> str:
        """Official string representation"""

    def __str__(self) -> str:
        """String representation (SNBT minimized format)"""

    def assign(self, value: int) -> Int64Tag:
        """Assign a new integer value to this tag"""

    def copy(self) -> Tag:
        """Create a deep copy of this tag"""

    def equals(self, other: Tag) -> bool:
        """Check if this tag equals another tag"""

    def get_type(self) -> TagType:
        """Get the NBT type ID (Int64)"""

    def hash(self) -> int:
        """Compute hash value of this tag"""

    def load(self, stream: ...) -> None:
        """Load tag value from a binary stream"""

    def write(self, stream: ...) -> None:
        """Write tag to a binary stream"""

    @property
    def value(self) -> int:
        """Access the integer value of this tag"""

    @value.setter
    def value(self, arg1: int) -> None: ...

class IntArrayTag(Tag):
    def __hash__(self) -> int: ...
    def __contains__(self, value: int) -> bool:
        """Check if value is in the array"""

    def __eq__(self, other: IntArrayTag) -> bool: ...
    def __getitem__(self, index: int) -> int:
        """Get element at index without bounds checking"""

    @overload
    def __init__(self) -> None:
        """Construct an empty IntArrayTag"""

    @overload
    def __init__(self, values: List[int]) -> None:
        """Construct from a list of integers
        Example:
            IntArrayTag([1, 2, 3])
        """

    def __iter__(self) -> List[int]:
        """Iterate over elements in the array
        Example:
            for value in int_array:
                print(value)
        """

    def __list__(self) -> Any:
        """Convert to Python list of integers"""

    def __repr__(self) -> str:
        """Official string representation"""

    def __setitem__(self, index: int, value: int) -> None:
        """Set element at index"""

    def __str__(self) -> str:
        """String representation (SNBT minimized format)"""

    def append(self, value: int) -> None:
        """Append an integer to the end of the array"""

    def assign(self, values: List[int]) -> IntArrayTag:
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

class IntTag(Tag):
    def __eq__(self, other: Tag) -> bool:
        """Equality operator (==)"""

    def __hash__(self) -> int:
        """Compute hash value for Python hashing operations"""

    @overload
    def __init__(self) -> None:
        """Construct an IntTag with default value (0)"""

    @overload
    def __init__(self, value: int) -> None:
        """Construct an IntTag from an integer value"""

    def __int__(self) -> int:
        """Convert to Python int"""

    def __pos__(self) -> IntTag:
        """Unary plus operator (+)"""

    def __repr__(self) -> str:
        """Official string representation"""

    def __str__(self) -> str:
        """String representation (SNBT minimized format)"""

    def assign(self, value: int) -> IntTag:
        """Assign a new integer value to this tag"""

    def copy(self) -> Tag:
        """Create a deep copy of this tag"""

    def equals(self, other: Tag) -> bool:
        """Check if this tag equals another tag"""

    def get_type(self) -> TagType:
        """Get the NBT type ID (Int)"""

    def hash(self) -> int:
        """Compute hash value of this tag"""

    def load(self, stream: ...) -> None:
        """Load tag value from a binary stream"""

    def write(self, stream: ...) -> None:
        """Write tag to a binary stream"""

    @property
    def value(self) -> int:
        """Access the integer value of this tag"""

    @value.setter
    def value(self, arg1: int) -> None: ...

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

    def __list__(self) -> Any:
        """Convert to Python list of integers"""

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

class ShortTag(Tag):
    def __eq__(self, other: Tag) -> bool:
        """Equality operator (==)"""

    def __hash__(self) -> int:
        """Compute hash value for Python hashing operations"""

    @overload
    def __init__(self) -> None:
        """Construct an ShortTag with default value (0)"""

    @overload
    def __init__(self, value: int) -> None:
        """Construct an ShortTag from an integer value"""

    def __int__(self) -> int:
        """Convert to Python int"""

    def __pos__(self) -> ShortTag:
        """Unary plus operator (+)"""

    def __repr__(self) -> str:
        """Official string representation"""

    def __str__(self) -> str:
        """String representation (SNBT minimized format)"""

    def assign(self, value: int) -> ShortTag:
        """Assign a new integer value to this tag"""

    def copy(self) -> Tag:
        """Create a deep copy of this tag"""

    def equals(self, other: Tag) -> bool:
        """Check if this tag equals another tag"""

    def get_type(self) -> TagType:
        """Get the NBT type ID (Short)"""

    def hash(self) -> int:
        """Compute hash value of this tag"""

    def load(self, stream: ...) -> None:
        """Load tag value from a binary stream"""

    def write(self, stream: ...) -> None:
        """Write tag to a binary stream"""

    @property
    def value(self) -> int:
        """Access the integer value of this tag"""

    @value.setter
    def value(self, arg1: int) -> None: ...

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
    def value(self, arg1: str) -> None: ...

class Tag(ABC):
    """
    Base class for all NBT tags
    """

    @staticmethod
    def new_tag(type: TagType) -> Tag:
        """Create a new tag of the given type"""

    def __eq__(self, arg0: Tag) -> bool:
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

    def to_snbt(self, format: SnbtFormat = ..., indent: int = 4) -> str:
        """Convert tag to SNBT string"""

def detect_content_format(
    content: Union[bytes, bytearray],
) -> Optional[NbtFileFormat]:
    """Detect NBT format from binary content
    Args:
        content (bytes): Binary content to analyze
    Returns:
        NbtFileFormat or None if format cannot be determined
    """

def detect_file_format(
    path: str, file_memory_map: bool = False
) -> Optional[NbtFileFormat]:
    """Detect NBT format from a file
    Args:
        path (str): Path to the file
        file_memory_map (bool): Use memory mapping for large files (default: False)
    Returns:
        NbtFileFormat or None if format cannot be determined
    """

def dumps(
    nbt: CompoundTag,
    format: NbtFileFormat = NbtFileFormat.LittleEndian,
    compression_type: NbtCompressionType = NbtCompressionType.GZIP,
    compression_level: NbtCompressionLevel = NbtCompressionLevel.DEFAULT,
) -> bytes:
    """Serialize CompoundTag to binary data
    Args:
        nbt (CompoundTag): Tag to serialize
        format (NbtFileFormat): Output format (default: LittleEndian)
        compression_type (CompressionType): Compression method (default: Gzip)
        compression_level (CompressionLevel): Compression level (default: Default)
    Returns:
        bytes: Serialized binary data
    """

def dumps_base64(
    nbt: CompoundTag,
    format: NbtFileFormat = NbtFileFormat.LittleEndian,
    compression_type: NbtCompressionType = NbtCompressionType.GZIP,
    compression_level: NbtCompressionLevel = NbtCompressionLevel.DEFAULT,
) -> str:
    """Serialize CompoundTag to Base64 string
    Args:
        nbt (CompoundTag): Tag to serialize
        format (NbtFileFormat): Output format (default: LittleEndian)
        compression_type (CompressionType): Compression method (default: Gzip)
        compression_level (CompressionLevel): Compression level (default: Default)
    Returns:
        str: Base64-encoded NBT data
    """

def load(
    path: str,
    format: Optional[NbtFileFormat] = None,
    file_memory_map: bool = False,
) -> Optional[CompoundTag]:
    """Parse CompoundTag from a file
    Args:
        path (str): Path to NBT file
        format (NbtFileFormat, optional): Force specific format (autodetect if None)
        file_memory_map (bool): Use memory mapping for large files (default: False)
    Returns:
        CompoundTag or None if parsing fails
    """

def load_snbt(path: str) -> Optional[CompoundTag]:
    """Parse CompoundTag from SNBT (String NBT) file
    Args:
        path (str): Path to SNBT file
    Returns:
        CompoundTag or None if parsing fails
    """

def loads(
    content: Union[bytes, bytearray], format: Optional[NbtFileFormat] = None
) -> Optional[CompoundTag]:
    """Parse CompoundTag from binary data
    Args:
        content (bytes): Binary NBT data
        format (NbtFileFormat, optional): Force specific format (autodetect if None)
    Returns:
        CompoundTag or None if parsing fails
    """

def loads_base64(
    content: str, format: Optional[NbtFileFormat] = None
) -> Optional[CompoundTag]:
    """Parse CompoundTag from Base64-encoded NBT
    Args:
        content (str): Base64-encoded NBT data\\
        format (NbtFileFormat, optional): Force specific format (autodetect if None)
    Returns:
        CompoundTag or None if parsing fails
    """

def loads_snbt(path: str, parsed_length: int | None = None) -> Optional[CompoundTag]:
    """Parse CompoundTag from SNBT (String NBT) file
    Args:
        path (str): Path to SNBT file
    Returns:
        CompoundTag or None if parsing fails
    """

def save(
    nbt: CompoundTag,
    path: str,
    format: NbtFileFormat = NbtFileFormat.LittleEndian,
    compression_type: NbtCompressionType = NbtCompressionType.GZIP,
    compression_level: NbtCompressionLevel = NbtCompressionLevel.DEFAULT,
) -> bool:
    """Save CompoundTag to a file
    Args:
        nbt (CompoundTag): Tag to save
        path (str): Output file path
        format (NbtFileFormat): Output format (default: LittleEndian)
        compression_type (CompressionType): Compression method (default: Gzip)
        compression_level (CompressionLevel): Compression level (default: Default)
    Returns:
        bool: True if successful, False otherwise
    """

def save_snbt(
    nbt: CompoundTag,
    path: str,
    format: SnbtFormat = SnbtFormat.PrettyFilePrint,
    indent: int = 4,
) -> bool:
    """Save CompoundTag to SNBT (String NBT) file
    Args:
        nbt (CompoundTag): Tag to save
        path (str): Output file path
        format (SnbtFormat): Output formatting style (default: PrettyFilePrint)
        indent (int): Indentation level (default: 4)
    Returns:
        bool: True if successful, False otherwise
    """

def validate(
    content: Union[bytes, bytearray], format: NbtFileFormat = NbtFileFormat.LittleEndian
) -> bool:
    """Validate NBT binary content
    Args:
        content (bytes): Binary data to validate
        format (NbtFileFormat): Expected format (default: LittleEndian)
    Returns:
        bool: True if valid NBT, False otherwise
    """

def validate_file(
    path: str, format: NbtFileFormat = ..., file_memory_map: bool = False
) -> bool:
    """Validate NBT file
    Args:
        path (str): File path to validate
        format (NbtFileFormat): Expected format (default: LittleEndian)
        file_memory_map (bool): Use memory mapping (default: False)
    Returns:
        bool: True if valid NBT file, False otherwise
    """

class NbtCompressionLevel(Enum):
    DEFAULT = -1
    NO_COMPRESSION = 0
    BEST_SPEED = 1
    LOW = 2
    MEDIUM_LOW = 3
    MEDIUM = 4
    MEDIUM_HIGH = 5
    HIGH = 6
    VERY_HIGH = 7
    ULTRA = 8
    BEST_COMPRESSION = 9

class NbtCompressionType(Enum):
    NONE = 0
    GZIP = 1
    ZLIB = 2

class NbtFileFormat(Enum):
    LittleEndian = 0
    LittleEndianWithHeader = 1
    BigEndian = 2
    BigEndianWithHeader = 3
    BedrockNetwork = 4

class SnbtFormat(Enum):
    Minimize = 0
    PrettyFilePrint = 1
    ArrayLineFeed = 2
    AlwaysLineFeed = 3
    ForceAscii = 4
    ForceQuote = 8
    Classic = 10
    CommentMarks = 16
    Jsonify = 24

class TagType(Enum):
    End = 0
    Byte = 1
    Short = 2
    Int = 3
    Int64 = 4
    Float = 5
    Double = 6
    ByteArray = 7
    String = 8
    List = 9
    Compound = 10
    IntArray = 11
    LongArray = 12
