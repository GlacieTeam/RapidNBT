"""
Python bindings for NBT library
"""
from __future__ import annotations
import collections.abc
import typing
__all__: list[str] = ['AlwaysLineFeed', 'ArrayLineFeed', 'Byte', 'ByteArray', 'ByteArrayTag', 'ByteTag', 'Classic', 'CommentMarks', 'Compound', 'CompoundTagVariant', 'Double', 'DoubleTag', 'End', 'EndTag', 'Float', 'FloatTag', 'ForceAscii', 'ForceQuote', 'Int', 'Int64', 'Int64Tag', 'IntArray', 'IntTag', 'Jsonify', 'List', 'ListTag', 'LongArray', 'Minimize', 'NumTagTypes', 'PrettyFilePrint', 'Short', 'ShortTag', 'SnbtFormat', 'String', 'StringTag', 'Tag', 'TagType']
class ByteArrayTag(Tag):
    def __bytes__(self) -> bytes:
        """
        Convert to Python bytes object
        """
    def __eq__(self, other: Tag) -> bool:
        """
        Equality operator (==)
        """
    def __getitem__(self, index: typing.SupportsInt) -> int:
        """
        Get byte at specified index
        """
    def __hash__(self) -> int:
        """
        Compute hash value for Python hashing operations
        """
    @typing.overload
    def __init__(self) -> None:
        """
        Construct an empty ByteArrayTag
        """
    @typing.overload
    def __init__(self, arr: collections.abc.Sequence[typing.SupportsInt]) -> None:
        """
        Construct from a list of bytes (e.g., [1, 2, 3])
        """
    def __iter__(self) -> collections.abc.Iterator[int]:
        """
        Iterate over bytes in the array
        """
    def __len__(self) -> int:
        """
        Get number of bytes in the array
        """
    def __repr__(self) -> str:
        """
        Official string representation
        """
    def __setitem__(self, index: typing.SupportsInt, value: typing.SupportsInt) -> None:
        """
        Set byte at specified index
        """
    def __str__(self) -> str:
        """
        String representation (SNBT minimized format)
        """
    def assign(self, bytes: collections.abc.Buffer) -> ByteArrayTag:
        """
        Assign new binary data from a list of bytes
        """
    def clear(self) -> None:
        """
        Clear all byte data
        """
    def copy(self) -> Tag:
        """
        Create a deep copy of this tag
        """
    def data(self) -> memoryview:
        """
        Get a raw memory view of the byte data
        """
    def equals(self, other: Tag) -> bool:
        """
        Check if this tag equals another tag (same bytes and type)
        """
    def getType(self) -> TagType:
        """
        Get the NBT type ID (ByteArray)
        """
    def hash(self) -> int:
        """
        Compute hash value of this tag
        """
    def load(self, stream: ...) -> None:
        """
        Load tag value from a binary stream
        """
    def push_back(self, value: typing.SupportsInt) -> None:
        """
        Add a byte to the end of the array
        """
    @typing.overload
    def remove(self, index: typing.SupportsInt) -> bool:
        """
        Remove byte at specified index
        """
    @typing.overload
    def remove(self, start_index: typing.SupportsInt, end_index: typing.SupportsInt) -> bool:
        """
        Remove bytes in the range [start_index, end_index)
        """
    def reserve(self, size: typing.SupportsInt) -> None:
        """
        Preallocate memory for future additions
        """
    def size(self) -> int:
        """
        Get number of bytes in the array
        """
    def write(self, stream: ...) -> None:
        """
        Write tag to a binary stream
        """
    @property
    def value(self) -> bytes:
        """
        Access the byte array as a list of integers (0-255)
        """
    @value.setter
    def value(self, arg1: collections.abc.Buffer) -> None:
        ...
class ByteTag(Tag):
    def __eq__(self, other: Tag) -> bool:
        """
        Equality operator (==)
        """
    def __hash__(self) -> int:
        """
        Compute hash value for Python hashing operations
        """
    @typing.overload
    def __init__(self) -> None:
        """
        Construct an ByteTag with default value (0)
        """
    @typing.overload
    def __init__(self, value: typing.SupportsInt) -> None:
        """
        Construct an ByteTag from an integer value
        """
    def __int__(self) -> int:
        """
        Convert to Python int
        """
    def __pos__(self) -> ByteTag:
        """
        Unary plus operator (+)
        """
    def __repr__(self) -> str:
        """
        Official string representation
        """
    def __str__(self) -> str:
        """
        String representation (SNBT minimized format)
        """
    def assign(self, value: typing.SupportsInt) -> ByteTag:
        """
        Assign a new integer value to this tag
        """
    def copy(self) -> Tag:
        """
        Create a deep copy of this tag
        """
    def equals(self, other: Tag) -> bool:
        """
        Check if this tag equals another tag
        """
    def getType(self) -> TagType:
        """
        Get the NBT type ID (Byte)
        """
    def hash(self) -> int:
        """
        Compute hash value of this tag
        """
    def load(self, stream: ...) -> None:
        """
        Load tag value from a binary stream
        """
    def write(self, stream: ...) -> None:
        """
        Write tag to a binary stream
        """
    @property
    def value(self) -> int:
        """
        Access the integer value of this tag
        """
    @value.setter
    def value(self, arg1: typing.SupportsInt) -> None:
        ...
class CompoundTagVariant:
    class Iterator:
        def __iter__(self) -> CompoundTagVariant.Iterator:
            ...
        def __next__(self) -> ...:
            ...
    __hash__: typing.ClassVar[None] = None
    def __eq__(self, arg0: CompoundTagVariant) -> bool:
        ...
    def __float__(self) -> float:
        ...
    @typing.overload
    def __getitem__(self, arg0: typing.SupportsInt) -> ...:
        ...
    @typing.overload
    def __getitem__(self, arg0: str) -> CompoundTagVariant:
        ...
    @typing.overload
    def __init__(self) -> None:
        ...
    @typing.overload
    def __init__(self, arg0: typing.Any) -> None:
        ...
    def __int__(self) -> int:
        ...
    def __iter__(self) -> collections.abc.Iterator[...]:
        ...
    @typing.overload
    def __setitem__(self, arg0: str, arg1: CompoundTagVariant) -> None:
        ...
    @typing.overload
    def __setitem__(self, arg0: typing.SupportsInt, arg1: CompoundTagVariant) -> None:
        ...
    def as_byte_array(self) -> bytes:
        ...
    def as_int_array(self) -> list[int]:
        ...
    def as_long_array(self) -> list[int]:
        ...
    def as_string(self) -> str:
        ...
    def contains(self, arg0: str) -> bool:
        ...
    def copy(self) -> ...:
        ...
    def get_type(self) -> TagType:
        ...
    def hold(self, arg0: TagType) -> bool:
        ...
    def is_array(self) -> bool:
        ...
    def is_binary(self) -> bool:
        ...
    def is_boolean(self) -> bool:
        ...
    def is_null(self) -> bool:
        ...
    def is_number(self) -> bool:
        ...
    def is_number_float(self) -> bool:
        ...
    def is_number_integer(self) -> bool:
        ...
    def is_object(self) -> bool:
        ...
    def is_primitive(self) -> bool:
        ...
    def is_string(self) -> bool:
        ...
    def is_structured(self) -> bool:
        ...
    def items(self) -> dict[str, CompoundTagVariant]:
        ...
    def merge(self, other: CompoundTagVariant, merge_list: bool = False) -> None:
        ...
    @typing.overload
    def push_back(self, arg0: CompoundTagVariant) -> None:
        ...
    @typing.overload
    def push_back(self, arg0: ...) -> None:
        ...
    @typing.overload
    def remove(self, arg0: str) -> bool:
        ...
    @typing.overload
    def remove(self, arg0: typing.SupportsInt) -> bool:
        ...
    def rename(self, arg0: str, arg1: str) -> bool:
        ...
    def size(self) -> int:
        ...
    def to_json(self, indent: typing.SupportsInt = 4) -> str:
        ...
    def to_snbt(self, snbt_format: SnbtFormat = ..., indent: typing.SupportsInt = 4) -> str:
        ...
class DoubleTag(Tag):
    def __eq__(self, other: Tag) -> bool:
        """
        Equality operator (==)
        """
    def __float__(self) -> float:
        """
        Convert to Python float (for float(tag) operations)
        """
    def __hash__(self) -> int:
        """
        Compute hash value for Python hashing operations
        """
    @typing.overload
    def __init__(self) -> None:
        """
        Construct a DoubleTag with default value (0.0)
        """
    @typing.overload
    def __init__(self, value: typing.SupportsFloat) -> None:
        """
        Construct a DoubleTag from a floating-point value
        """
    def __repr__(self) -> str:
        """
        Official string representation including type information
        """
    def __str__(self) -> str:
        """
        String representation (SNBT minimized format)
        """
    def assign(self, value: typing.SupportsFloat) -> DoubleTag:
        """
        Assign a new floating-point value to this tag
        """
    def copy(self) -> Tag:
        """
        Create a deep copy of this tag
        """
    def equals(self, other: Tag) -> bool:
        """
        Check if this tag equals another tag
        """
    def getType(self) -> TagType:
        """
        Get the NBT type ID (Double)
        """
    def hash(self) -> int:
        """
        Compute hash value of this tag
        """
    def load(self, stream: ...) -> None:
        """
        Load tag value from a binary stream
        """
    def write(self, stream: ...) -> None:
        """
        Write tag to a binary stream
        """
    @property
    def value(self) -> float:
        """
        Access the floating-point value of this tag
        """
    @value.setter
    def value(self, arg1: typing.SupportsFloat) -> None:
        ...
class EndTag(Tag):
    def __eq__(self, other: Tag) -> bool:
        """
        Equality operator (==), all EndTags are equal
        """
    def __hash__(self) -> int:
        """
        Compute hash value for Python hashing operations
        """
    def __init__(self) -> None:
        """
        Construct an EndTag
        """
    def __repr__(self) -> str:
        """
        Official string representation
        """
    def __str__(self) -> str:
        """
        String representation (SNBT minimized format)
        """
    def copy(self) -> Tag:
        """
        Create a deep copy of this tag
        """
    def equals(self, other: Tag) -> bool:
        """
        Check if this tag equals another tag (all EndTags are equal)
        """
    def getType(self) -> TagType:
        """
        Get the NBT type ID (End)
        """
    def hash(self) -> int:
        """
        Compute hash value of this tag
        """
    def load(self, stream: ...) -> None:
        """
        Load tag value from a binary stream (no data for EndTag)
        """
    def write(self, stream: ...) -> None:
        """
        Write tag to a binary stream (no data for EndTag)
        """
class FloatTag(Tag):
    def __eq__(self, other: Tag) -> bool:
        """
        Equality operator (==)
        """
    def __float__(self) -> float:
        """
        Convert to Python float (for float(tag) operations)
        """
    def __hash__(self) -> int:
        """
        Compute hash value for Python hashing operations
        """
    @typing.overload
    def __init__(self) -> None:
        """
        Construct a FloatTag with default value (0.0)
        """
    @typing.overload
    def __init__(self, value: typing.SupportsFloat) -> None:
        """
        Construct a FloatTag from a floating-point value
        """
    def __repr__(self) -> str:
        """
        Official string representation including type information
        """
    def __str__(self) -> str:
        """
        String representation (SNBT minimized format)
        """
    def assign(self, value: typing.SupportsFloat) -> FloatTag:
        """
        Assign a new floating-point value to this tag
        """
    def copy(self) -> Tag:
        """
        Create a deep copy of this tag
        """
    def equals(self, other: Tag) -> bool:
        """
        Check if this tag equals another tag
        """
    def getType(self) -> TagType:
        """
        Get the NBT type ID (Float)
        """
    def hash(self) -> int:
        """
        Compute hash value of this tag
        """
    def load(self, stream: ...) -> None:
        """
        Load tag value from a binary stream
        """
    def write(self, stream: ...) -> None:
        """
        Write tag to a binary stream
        """
    @property
    def value(self) -> float:
        """
        Access the floating-point value of this tag
        """
    @value.setter
    def value(self, arg1: typing.SupportsFloat) -> None:
        ...
class Int64Tag(Tag):
    def __eq__(self, other: Tag) -> bool:
        """
        Equality operator (==)
        """
    def __hash__(self) -> int:
        """
        Compute hash value for Python hashing operations
        """
    @typing.overload
    def __init__(self) -> None:
        """
        Construct an Int64Tag with default value (0)
        """
    @typing.overload
    def __init__(self, value: typing.SupportsInt) -> None:
        """
        Construct an Int64Tag from an integer value
        """
    def __int__(self) -> int:
        """
        Convert to Python int
        """
    def __pos__(self) -> Int64Tag:
        """
        Unary plus operator (+)
        """
    def __repr__(self) -> str:
        """
        Official string representation
        """
    def __str__(self) -> str:
        """
        String representation (SNBT minimized format)
        """
    def assign(self, value: typing.SupportsInt) -> Int64Tag:
        """
        Assign a new integer value to this tag
        """
    def copy(self) -> Tag:
        """
        Create a deep copy of this tag
        """
    def equals(self, other: Tag) -> bool:
        """
        Check if this tag equals another tag
        """
    def getType(self) -> TagType:
        """
        Get the NBT type ID (Int64)
        """
    def hash(self) -> int:
        """
        Compute hash value of this tag
        """
    def load(self, stream: ...) -> None:
        """
        Load tag value from a binary stream
        """
    def write(self, stream: ...) -> None:
        """
        Write tag to a binary stream
        """
    @property
    def value(self) -> int:
        """
        Access the integer value of this tag
        """
    @value.setter
    def value(self, arg1: typing.SupportsInt) -> None:
        ...
class IntTag(Tag):
    def __eq__(self, other: Tag) -> bool:
        """
        Equality operator (==)
        """
    def __hash__(self) -> int:
        """
        Compute hash value for Python hashing operations
        """
    @typing.overload
    def __init__(self) -> None:
        """
        Construct an IntTag with default value (0)
        """
    @typing.overload
    def __init__(self, value: typing.SupportsInt) -> None:
        """
        Construct an IntTag from an integer value
        """
    def __int__(self) -> int:
        """
        Convert to Python int
        """
    def __pos__(self) -> IntTag:
        """
        Unary plus operator (+)
        """
    def __repr__(self) -> str:
        """
        Official string representation
        """
    def __str__(self) -> str:
        """
        String representation (SNBT minimized format)
        """
    def assign(self, value: typing.SupportsInt) -> IntTag:
        """
        Assign a new integer value to this tag
        """
    def copy(self) -> Tag:
        """
        Create a deep copy of this tag
        """
    def equals(self, other: Tag) -> bool:
        """
        Check if this tag equals another tag
        """
    def getType(self) -> TagType:
        """
        Get the NBT type ID (Int)
        """
    def hash(self) -> int:
        """
        Compute hash value of this tag
        """
    def load(self, stream: ...) -> None:
        """
        Load tag value from a binary stream
        """
    def write(self, stream: ...) -> None:
        """
        Write tag to a binary stream
        """
    @property
    def value(self) -> int:
        """
        Access the integer value of this tag
        """
    @value.setter
    def value(self, arg1: typing.SupportsInt) -> None:
        ...
class ListTag(Tag):
    def __eq__(self, other: Tag) -> bool:
        """
        Equality operator (==)
        """
    def __getitem__(self, index: typing.SupportsInt) -> Tag:
        """
        Get element at specified index
        """
    def __hash__(self) -> int:
        """
        Compute hash value for Python hashing operations
        """
    @typing.overload
    def __init__(self) -> None:
        """
        Construct an empty ListTag
        """
    @typing.overload
    def __init__(self, elements: collections.abc.Sequence[typing.Any]) -> None:
        """
        Construct from a list of Tag elements (e.g., [IntTag(1), StringTag('test')])
        """
    def __iter__(self) -> collections.abc.Iterator[Tag]:
        """
        Iterate over elements in the list
        """
    def __len__(self) -> int:
        """
        Get number of elements in the list
        """
    def __repr__(self) -> str:
        """
        Official string representation
        """
    def __setitem__(self, index: typing.SupportsInt, element: typing.Any) -> bool:
        """
        Set element at specified index
        """
    def __str__(self) -> str:
        """
        String representation (SNBT minimized format)
        """
    def append(self, element: typing.Any) -> None:
        """
        Append a Tag element to the list
        """
    def clear(self) -> None:
        """
        Remove all elements from the list
        """
    def copy(self) -> Tag:
        """
        Create a deep copy of this tag
        """
    def copy_list(self) -> ListTag:
        """
        Create a deep copy of this list (same as copy() but returns ListTag)
        """
    def empty(self) -> bool:
        """
        Check if the list is empty
        """
    def equals(self, other: Tag) -> bool:
        """
        Check if this tag equals another tag (same elements in same order)
        """
    def getType(self) -> TagType:
        """
        Get the NBT type ID (List)
        """
    def get_element_type(self) -> TagType:
        """
        Get the type of elements in this list (returns nbt.Type enum)
        """
    def hash(self) -> int:
        """
        Compute hash value of this tag
        """
    def insert(self, index: typing.SupportsInt, element: typing.Any) -> None:
        """
        Insert element at specified position
        """
    def load(self, stream: ...) -> None:
        """
        Load list from a binary stream
        """
    def merge(self, other: ListTag) -> None:
        """
        Merge another ListTag into this one (appends all elements)
        """
    @typing.overload
    def remove(self, index: typing.SupportsInt) -> bool:
        """
        Remove element at specified index
        """
    @typing.overload
    def remove(self, start_index: typing.SupportsInt, end_index: typing.SupportsInt) -> bool:
        """
        Remove elements in the range [start_index, end_index)
        """
    def reserve(self, size: typing.SupportsInt) -> None:
        """
        Preallocate memory for future additions
        """
    def size(self) -> int:
        """
        Get number of elements in the list
        """
    def write(self, stream: ...) -> None:
        """
        Write list to a binary stream
        """
class ShortTag(Tag):
    def __eq__(self, other: Tag) -> bool:
        """
        Equality operator (==)
        """
    def __hash__(self) -> int:
        """
        Compute hash value for Python hashing operations
        """
    @typing.overload
    def __init__(self) -> None:
        """
        Construct an ShortTag with default value (0)
        """
    @typing.overload
    def __init__(self, value: typing.SupportsInt) -> None:
        """
        Construct an ShortTag from an integer value
        """
    def __int__(self) -> int:
        """
        Convert to Python int
        """
    def __pos__(self) -> ShortTag:
        """
        Unary plus operator (+)
        """
    def __repr__(self) -> str:
        """
        Official string representation
        """
    def __str__(self) -> str:
        """
        String representation (SNBT minimized format)
        """
    def assign(self, value: typing.SupportsInt) -> ShortTag:
        """
        Assign a new integer value to this tag
        """
    def copy(self) -> Tag:
        """
        Create a deep copy of this tag
        """
    def equals(self, other: Tag) -> bool:
        """
        Check if this tag equals another tag
        """
    def getType(self) -> TagType:
        """
        Get the NBT type ID (Short)
        """
    def hash(self) -> int:
        """
        Compute hash value of this tag
        """
    def load(self, stream: ...) -> None:
        """
        Load tag value from a binary stream
        """
    def write(self, stream: ...) -> None:
        """
        Write tag to a binary stream
        """
    @property
    def value(self) -> int:
        """
        Access the integer value of this tag
        """
    @value.setter
    def value(self, arg1: typing.SupportsInt) -> None:
        ...
class SnbtFormat:
    """
    Members:
    
      Minimize
    
      PrettyFilePrint
    
      ArrayLineFeed
    
      ForceAscii
    
      ForceQuote
    
      CommentMarks
    
      Classic
    
      Jsonify
    
      AlwaysLineFeed
    """
    AlwaysLineFeed: typing.ClassVar[SnbtFormat]  # value = <SnbtFormat.AlwaysLineFeed: 3>
    ArrayLineFeed: typing.ClassVar[SnbtFormat]  # value = <SnbtFormat.ArrayLineFeed: 2>
    Classic: typing.ClassVar[SnbtFormat]  # value = <SnbtFormat.Classic: 10>
    CommentMarks: typing.ClassVar[SnbtFormat]  # value = <SnbtFormat.CommentMarks: 16>
    ForceAscii: typing.ClassVar[SnbtFormat]  # value = <SnbtFormat.ForceAscii: 4>
    ForceQuote: typing.ClassVar[SnbtFormat]  # value = <SnbtFormat.ForceQuote: 8>
    Jsonify: typing.ClassVar[SnbtFormat]  # value = <SnbtFormat.Jsonify: 24>
    Minimize: typing.ClassVar[SnbtFormat]  # value = <SnbtFormat.Minimize: 0>
    PrettyFilePrint: typing.ClassVar[SnbtFormat]  # value = <SnbtFormat.PrettyFilePrint: 1>
    __members__: typing.ClassVar[dict[str, SnbtFormat]]  # value = {'Minimize': <SnbtFormat.Minimize: 0>, 'PrettyFilePrint': <SnbtFormat.PrettyFilePrint: 1>, 'ArrayLineFeed': <SnbtFormat.ArrayLineFeed: 2>, 'ForceAscii': <SnbtFormat.ForceAscii: 4>, 'ForceQuote': <SnbtFormat.ForceQuote: 8>, 'CommentMarks': <SnbtFormat.CommentMarks: 16>, 'Classic': <SnbtFormat.Classic: 10>, 'Jsonify': <SnbtFormat.Jsonify: 24>, 'AlwaysLineFeed': <SnbtFormat.AlwaysLineFeed: 3>}
    def __eq__(self, other: typing.Any) -> bool:
        ...
    def __ge__(self, other: typing.Any) -> bool:
        ...
    def __getstate__(self) -> int:
        ...
    def __gt__(self, other: typing.Any) -> bool:
        ...
    def __hash__(self) -> int:
        ...
    def __index__(self) -> int:
        ...
    def __init__(self, value: typing.SupportsInt) -> None:
        ...
    def __int__(self) -> int:
        ...
    def __le__(self, other: typing.Any) -> bool:
        ...
    def __lt__(self, other: typing.Any) -> bool:
        ...
    def __ne__(self, other: typing.Any) -> bool:
        ...
    def __repr__(self) -> str:
        ...
    def __setstate__(self, state: typing.SupportsInt) -> None:
        ...
    def __str__(self) -> str:
        ...
    @property
    def name(self) -> str:
        ...
    @property
    def value(self) -> int:
        ...
class StringTag(Tag):
    def __eq__(self, other: StringTag) -> bool:
        """
        Equality operator (==), case-sensitive comparison
        """
    def __getitem__(self, index: typing.SupportsInt) -> str:
        """
        Get character at specified position
        """
    def __hash__(self) -> int:
        """
        Compute hash value for Python hashing operations
        """
    @typing.overload
    def __init__(self) -> None:
        """
        Construct an empty StringTag
        """
    @typing.overload
    def __init__(self, str: str) -> None:
        """
        Construct from a Python string
        """
    def __len__(self) -> int:
        """
        Get the length of the string in bytes
        """
    def __repr__(self) -> str:
        """
        Official representation with quoted content
        """
    def __str__(self) -> str:
        """
        String representation (SNBT minimized format)
        """
    def copy(self) -> Tag:
        """
        Create a deep copy of this tag
        """
    def equals(self, other: Tag) -> bool:
        """
        Check if this tag equals another tag (same content and type)
        """
    def getType(self) -> TagType:
        """
        Get the NBT type ID (String)
        """
    def hash(self) -> int:
        """
        Compute hash value of this tag (based on string content)
        """
    def load(self, stream: ...) -> None:
        """
        Load tag value from a binary stream (UTF-8)
        """
    def size(self) -> int:
        """
        Get the length of the string in bytes
        """
    def write(self, stream: ...) -> None:
        """
        Write tag to a binary stream (UTF-8 encoded)
        """
    @property
    def value(self) -> str:
        """
        Access the string content of this tag
        """
    @value.setter
    def value(self, arg1: str) -> None:
        ...
class Tag:
    """
    Base class for all NBT tags
    """
    @staticmethod
    def new_tag(type: TagType) -> Tag:
        """
        Create a new tag of the given type
        """
    def __eq__(self, arg0: Tag) -> bool:
        """
        Compare two tags for equality
        """
    @typing.overload
    def __getitem__(self, index: typing.SupportsInt) -> Tag:
        ...
    @typing.overload
    def __getitem__(self, key: str) -> CompoundTagVariant:
        ...
    def __hash__(self) -> int:
        ...
    def __repr__(self) -> str:
        ...
    def __str__(self) -> str:
        ...
    def as_bytes(self) -> bytes:
        """
        Convert tag to bytes
        """
    def as_string(self) -> str:
        """
        Convert tag to string
        """
    def copy(self) -> Tag:
        """
        Create a deep copy of this tag
        """
    def equals(self, other: Tag) -> bool:
        """
        Check if this tag equals another tag
        """
    def get_type(self) -> TagType:
        """
        Get the type of this tag
        """
    def hash(self) -> int:
        """
        Compute hash value of this tag
        """
    def load(self, stream: ...) -> None:
        """
        Load tag from binary stream
        """
    def to_json(self, indent: typing.SupportsInt = 4) -> str:
        """
        Convert tag to JSON string
        """
    def to_snbt(self, format: SnbtFormat = ..., indent: typing.SupportsInt = 4) -> str:
        """
        Convert tag to SNBT string
        """
    def write(self, stream: ...) -> None:
        """
        Write tag to binary stream
        """
class TagType:
    """
    Members:
    
      End
    
      Byte
    
      Short
    
      Int
    
      Int64
    
      Float
    
      Double
    
      ByteArray
    
      String
    
      List
    
      Compound
    
      IntArray
    
      LongArray
    
      NumTagTypes
    """
    Byte: typing.ClassVar[TagType]  # value = <TagType.Byte: 1>
    ByteArray: typing.ClassVar[TagType]  # value = <TagType.ByteArray: 7>
    Compound: typing.ClassVar[TagType]  # value = <TagType.Compound: 10>
    Double: typing.ClassVar[TagType]  # value = <TagType.Double: 6>
    End: typing.ClassVar[TagType]  # value = <TagType.End: 0>
    Float: typing.ClassVar[TagType]  # value = <TagType.Float: 5>
    Int: typing.ClassVar[TagType]  # value = <TagType.Int: 3>
    Int64: typing.ClassVar[TagType]  # value = <TagType.Int64: 4>
    IntArray: typing.ClassVar[TagType]  # value = <TagType.IntArray: 11>
    List: typing.ClassVar[TagType]  # value = <TagType.List: 9>
    LongArray: typing.ClassVar[TagType]  # value = <TagType.LongArray: 12>
    NumTagTypes: typing.ClassVar[TagType]  # value = <TagType.NumTagTypes: 13>
    Short: typing.ClassVar[TagType]  # value = <TagType.Short: 2>
    String: typing.ClassVar[TagType]  # value = <TagType.String: 8>
    __members__: typing.ClassVar[dict[str, TagType]]  # value = {'End': <TagType.End: 0>, 'Byte': <TagType.Byte: 1>, 'Short': <TagType.Short: 2>, 'Int': <TagType.Int: 3>, 'Int64': <TagType.Int64: 4>, 'Float': <TagType.Float: 5>, 'Double': <TagType.Double: 6>, 'ByteArray': <TagType.ByteArray: 7>, 'String': <TagType.String: 8>, 'List': <TagType.List: 9>, 'Compound': <TagType.Compound: 10>, 'IntArray': <TagType.IntArray: 11>, 'LongArray': <TagType.LongArray: 12>, 'NumTagTypes': <TagType.NumTagTypes: 13>}
    def __eq__(self, other: typing.Any) -> bool:
        ...
    def __getstate__(self) -> int:
        ...
    def __hash__(self) -> int:
        ...
    def __index__(self) -> int:
        ...
    def __init__(self, value: typing.SupportsInt) -> None:
        ...
    def __int__(self) -> int:
        ...
    def __ne__(self, other: typing.Any) -> bool:
        ...
    def __repr__(self) -> str:
        ...
    def __setstate__(self, state: typing.SupportsInt) -> None:
        ...
    def __str__(self) -> str:
        ...
    @property
    def name(self) -> str:
        ...
    @property
    def value(self) -> int:
        ...
AlwaysLineFeed: SnbtFormat  # value = <SnbtFormat.AlwaysLineFeed: 3>
ArrayLineFeed: SnbtFormat  # value = <SnbtFormat.ArrayLineFeed: 2>
Byte: TagType  # value = <TagType.Byte: 1>
ByteArray: TagType  # value = <TagType.ByteArray: 7>
Classic: SnbtFormat  # value = <SnbtFormat.Classic: 10>
CommentMarks: SnbtFormat  # value = <SnbtFormat.CommentMarks: 16>
Compound: TagType  # value = <TagType.Compound: 10>
Double: TagType  # value = <TagType.Double: 6>
End: TagType  # value = <TagType.End: 0>
Float: TagType  # value = <TagType.Float: 5>
ForceAscii: SnbtFormat  # value = <SnbtFormat.ForceAscii: 4>
ForceQuote: SnbtFormat  # value = <SnbtFormat.ForceQuote: 8>
Int: TagType  # value = <TagType.Int: 3>
Int64: TagType  # value = <TagType.Int64: 4>
IntArray: TagType  # value = <TagType.IntArray: 11>
Jsonify: SnbtFormat  # value = <SnbtFormat.Jsonify: 24>
List: TagType  # value = <TagType.List: 9>
LongArray: TagType  # value = <TagType.LongArray: 12>
Minimize: SnbtFormat  # value = <SnbtFormat.Minimize: 0>
NumTagTypes: TagType  # value = <TagType.NumTagTypes: 13>
PrettyFilePrint: SnbtFormat  # value = <SnbtFormat.PrettyFilePrint: 1>
Short: TagType  # value = <TagType.Short: 2>
String: TagType  # value = <TagType.String: 8>
