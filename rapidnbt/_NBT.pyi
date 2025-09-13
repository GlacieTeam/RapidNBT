"""
Python bindings for NBT library
"""

from __future__ import annotations
import collections.abc
import typing

__all__: list[str] = [
    "AlwaysLineFeed",
    "ArrayLineFeed",
    "Byte",
    "ByteArray",
    "ByteTag",
    "Classic",
    "CommentMarks",
    "Compound",
    "CompoundTagVariant",
    "Double",
    "End",
    "EndTag",
    "Float",
    "ForceAscii",
    "ForceQuote",
    "Int",
    "Int64",
    "IntArray",
    "Jsonify",
    "List",
    "LongArray",
    "Minimize",
    "NumTagTypes",
    "PrettyFilePrint",
    "Short",
    "SnbtFormat",
    "String",
    "Tag",
    "TagType",
]

class ByteTag(Tag):
    def __index__(self) -> int: ...
    @typing.overload
    def __init__(self) -> None: ...
    @typing.overload
    def __init__(self, value: typing.SupportsInt) -> None: ...
    def __int__(self) -> int: ...
    def __pos__(self) -> ByteTag: ...
    def __repr__(self) -> str: ...
    def __str__(self) -> str: ...
    def assign(self, value: typing.SupportsInt) -> ByteTag: ...
    def copy(self) -> Tag: ...
    def equals(self, arg0: Tag) -> bool: ...
    def getType(self) -> TagType: ...
    def hash(self) -> int: ...
    def load(self, stream: ...) -> None: ...
    def write(self, stream: ...) -> None: ...
    @property
    def value(self) -> int: ...
    @value.setter
    def value(self, arg1: typing.SupportsInt) -> None: ...

class CompoundTagVariant:
    class Iterator:
        def __iter__(self) -> CompoundTagVariant.Iterator: ...
        def __next__(self) -> ...: ...

    __hash__: typing.ClassVar[None] = None
    def __eq__(self, arg0: CompoundTagVariant) -> bool: ...
    def __float__(self) -> float: ...
    @typing.overload
    def __getitem__(self, arg0: typing.SupportsInt) -> ...: ...
    @typing.overload
    def __getitem__(self, arg0: str) -> CompoundTagVariant: ...
    @typing.overload
    def __init__(self) -> None: ...
    @typing.overload
    def __init__(self, arg0: typing.Any) -> None: ...
    def __int__(self) -> int: ...
    def __iter__(self) -> collections.abc.Iterator[...]: ...
    @typing.overload
    def __setitem__(self, arg0: str, arg1: CompoundTagVariant) -> None: ...
    @typing.overload
    def __setitem__(
        self, arg0: typing.SupportsInt, arg1: CompoundTagVariant
    ) -> None: ...
    def as_byte_array(self) -> bytes: ...
    def as_int_array(self) -> list[int]: ...
    def as_long_array(self) -> list[int]: ...
    def as_string(self) -> str: ...
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
    def items(self) -> dict[str, CompoundTagVariant]: ...
    def merge(self, other: CompoundTagVariant, merge_list: bool = False) -> None: ...
    @typing.overload
    def push_back(self, arg0: CompoundTagVariant) -> None: ...
    @typing.overload
    def push_back(self, arg0: ...) -> None: ...
    @typing.overload
    def remove(self, arg0: str) -> bool: ...
    @typing.overload
    def remove(self, arg0: typing.SupportsInt) -> bool: ...
    def rename(self, arg0: str, arg1: str) -> bool: ...
    def size(self) -> int: ...
    def to_json(self, indent: typing.SupportsInt = 4) -> str: ...
    def to_snbt(
        self, snbt_format: SnbtFormat = ..., indent: typing.SupportsInt = 4
    ) -> str: ...

class EndTag(Tag):
    def __eq__(self, arg0: Tag) -> bool: ...
    def __hash__(self) -> int: ...
    def __init__(self) -> None: ...
    def __ne__(self, arg0: Tag) -> bool: ...
    def __repr__(self) -> str: ...
    def __str__(self) -> str: ...
    def copy(self) -> Tag: ...
    def equals(self, arg0: Tag) -> bool: ...
    def getType(self) -> TagType: ...
    def hash(self) -> int: ...
    def load(self, arg0: ...) -> None: ...
    def write(self, arg0: ...) -> None: ...

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

    AlwaysLineFeed: typing.ClassVar[
        SnbtFormat
    ]  # value = <SnbtFormat.AlwaysLineFeed: 3>
    ArrayLineFeed: typing.ClassVar[SnbtFormat]  # value = <SnbtFormat.ArrayLineFeed: 2>
    Classic: typing.ClassVar[SnbtFormat]  # value = <SnbtFormat.Classic: 10>
    CommentMarks: typing.ClassVar[SnbtFormat]  # value = <SnbtFormat.CommentMarks: 16>
    ForceAscii: typing.ClassVar[SnbtFormat]  # value = <SnbtFormat.ForceAscii: 4>
    ForceQuote: typing.ClassVar[SnbtFormat]  # value = <SnbtFormat.ForceQuote: 8>
    Jsonify: typing.ClassVar[SnbtFormat]  # value = <SnbtFormat.Jsonify: 24>
    Minimize: typing.ClassVar[SnbtFormat]  # value = <SnbtFormat.Minimize: 0>
    PrettyFilePrint: typing.ClassVar[
        SnbtFormat
    ]  # value = <SnbtFormat.PrettyFilePrint: 1>
    __members__: typing.ClassVar[
        dict[str, SnbtFormat]
    ]  # value = {'Minimize': <SnbtFormat.Minimize: 0>, 'PrettyFilePrint': <SnbtFormat.PrettyFilePrint: 1>, 'ArrayLineFeed': <SnbtFormat.ArrayLineFeed: 2>, 'ForceAscii': <SnbtFormat.ForceAscii: 4>, 'ForceQuote': <SnbtFormat.ForceQuote: 8>, 'CommentMarks': <SnbtFormat.CommentMarks: 16>, 'Classic': <SnbtFormat.Classic: 10>, 'Jsonify': <SnbtFormat.Jsonify: 24>, 'AlwaysLineFeed': <SnbtFormat.AlwaysLineFeed: 3>}
    def __eq__(self, other: typing.Any) -> bool: ...
    def __ge__(self, other: typing.Any) -> bool: ...
    def __getstate__(self) -> int: ...
    def __gt__(self, other: typing.Any) -> bool: ...
    def __hash__(self) -> int: ...
    def __index__(self) -> int: ...
    def __init__(self, value: typing.SupportsInt) -> None: ...
    def __int__(self) -> int: ...
    def __le__(self, other: typing.Any) -> bool: ...
    def __lt__(self, other: typing.Any) -> bool: ...
    def __ne__(self, other: typing.Any) -> bool: ...
    def __repr__(self) -> str: ...
    def __setstate__(self, state: typing.SupportsInt) -> None: ...
    def __str__(self) -> str: ...
    @property
    def name(self) -> str: ...
    @property
    def value(self) -> int: ...

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
    def __getitem__(self, index: typing.SupportsInt) -> Tag: ...
    @typing.overload
    def __getitem__(self, key: str) -> CompoundTagVariant: ...
    def __hash__(self) -> int: ...
    def __repr__(self) -> str: ...
    def __str__(self) -> str: ...
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
    __members__: typing.ClassVar[
        dict[str, TagType]
    ]  # value = {'End': <TagType.End: 0>, 'Byte': <TagType.Byte: 1>, 'Short': <TagType.Short: 2>, 'Int': <TagType.Int: 3>, 'Int64': <TagType.Int64: 4>, 'Float': <TagType.Float: 5>, 'Double': <TagType.Double: 6>, 'ByteArray': <TagType.ByteArray: 7>, 'String': <TagType.String: 8>, 'List': <TagType.List: 9>, 'Compound': <TagType.Compound: 10>, 'IntArray': <TagType.IntArray: 11>, 'LongArray': <TagType.LongArray: 12>, 'NumTagTypes': <TagType.NumTagTypes: 13>}
    def __eq__(self, other: typing.Any) -> bool: ...
    def __getstate__(self) -> int: ...
    def __hash__(self) -> int: ...
    def __index__(self) -> int: ...
    def __init__(self, value: typing.SupportsInt) -> None: ...
    def __int__(self) -> int: ...
    def __ne__(self, other: typing.Any) -> bool: ...
    def __repr__(self) -> str: ...
    def __setstate__(self, state: typing.SupportsInt) -> None: ...
    def __str__(self) -> str: ...
    @property
    def name(self) -> str: ...
    @property
    def value(self) -> int: ...

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
