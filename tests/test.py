# Copyright © 2025 GlacieTeam. All rights reserved.
#
# This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
# distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
#
# SPDX-License-Identifier: MPL-2.0

import ctypes
from bstream import BinaryStream
from rapidnbt import (
    IntArrayTag,
    ListTag,
    LongArrayTag,
    CompoundTag,
    IntTag,
    StringTag,
    ByteTag,
    ShortTag,
    SnbtFormat,
    SnbtNumberFormat,
)


def test1():
    nbt = CompoundTag(
        {
            "string_tag": "测试（非ASCII）",
            "byte_tag": ctypes.c_ubyte(114),
            "bool_tag": False,
            "short_tag": ctypes.c_int16(65536),
            "int_tag": 114514,
            "test_list": ["237892", "homo", "114514"],
        }
    )
    nbt["test"]["long_tag"] = ctypes.c_int64(1145141919810)
    nbt["test"]["float_tag"] = 114.514
    nbt["test"]["double_tag"] = ctypes.c_double(3.1415926535897)
    nbt["byte_array_tag"] = b"13276273923"
    nbt["list_tag"] = ["aaaaa", "bbbbb"]
    nbt["list_tag"].append("Homo")
    nbt["compound_tag"] = nbt
    nbt["int_array_tag"] = IntArrayTag([1, 2, 3, 4, 5, 6, 7])
    nbt["long_array_tag"] = LongArrayTag([1, 2, 3, 4, 5, 6, 7])
    nbt["long_array_tag"] = IntTag(2)
    print(
        nbt.to_snbt(
            format=SnbtFormat.Default | SnbtFormat.MarkAllTags | SnbtFormat.MarkSigned,
            number_format=SnbtNumberFormat.UpperHexadecimal,
        )
    )
    print(f'{nbt["test"]["double_tag"]}')
    print(f'{nbt["not_exist"]["not_exist"]}')
    print(f'{nbt["compound_tag"]}')
    print(f'{nbt["list_tag"].value}')


def test2():
    snbt = '{"byte_array_tag": [B;4_9b, 51Sb, 50b, +55b, -54b, 50sB, 0xABsb, 0xFCub, 57ub, 0b1001b, 0x51UB],"double_tag": 3.1_41_5_93,"byte_tag": 114   /*sb*/, "string_tag": "\u6d4b\u8bd5"  , long_array_tag: [L;1UL, 2SL, 3sl, 0x267DFCESl, -5l, 6l, 7l]}'
    nbt = CompoundTag.from_snbt(snbt)
    # print(nbt.to_json())
    bnbt = nbt.to_binary_nbt()
    print(bnbt.hex())
    rnbt = CompoundTag.from_binary_nbt(bnbt)
    print(rnbt.to_snbt())


def test3():
    nbt = CompoundTag()
    nbt.set_string("tag_string", "测试（非ASCII）")
    nbt.set_byte("tag_byte", 114)
    nbt.set_short("tag_short", 26378)
    nbt.set_int("tag_int", 890567)
    nbt.set_long("tag_int64", 3548543263748543827)
    nbt.set_float("tag_float", 1.2345)
    nbt.set_double("tag_double", 1.414213562)
    nbt.set_byte_array("tag_byte_array", b"45678909876")
    nbt.set_list("tag_list", [nbt, nbt])
    nbt.set_int_array("tag_int_array", [1, 2, 3, 4, 5, 6, 7])
    nbt.set_compound("tag_compound", {})
    print(nbt.to_json())
    print(f'{nbt.get_string("tag_string")}')
    print(f'{nbt.get_byte("tag_byte")}')
    print(f'{nbt.get_short("tag_short")}')
    print(f'{nbt.get_int("tag_int")}')
    print(f'{nbt.get_long("tag_int64")}')
    print(f'{nbt.get_float("tag_float")}')
    print(f'{nbt.get_double("tag_double")}')
    print(f'{nbt.get_byte_array("tag_byte_array")}')
    print(f'{nbt.get_list("tag_list")}')
    print(f'{nbt.get_compound("tag_compound")}')
    print(f'{nbt.get_int_array("tag_int_array")}')

    try:
        print(f'{nbt.get_byte("not exist")}')
    except KeyError as e:
        print(e)

    try:
        print(f'{nbt.get_byte("tag_int_array")}')
    except TypeError as e:
        print(e)

    nbt["tag_int_array"].value = IntArrayTag([5, 6, 7, 8, 9, 0])
    print(f'{nbt["tag_int_array"].value}')
    print(f'{nbt["tag_int_array"].as_tag()}')
    print(nbt.value)


def test4():
    testnbt = CompoundTag(
        {
            "string_tag": StringTag("Test String"),
            "byte_tag": ByteTag(114),
            "short_tag": ShortTag(19132),
            "int_tag": IntTag(114514),
        }
    )
    stream = BinaryStream()
    print(testnbt.to_snbt())
    stream.write_byte(23)
    testnbt.serialize(stream)
    buffer = stream.data()
    print(
        f"{buffer.hex()} | {buffer.hex() == '170a000108627974655f746167720307696e745f746167a4fd0d020973686f72745f746167bc4a080a737472696e675f7461670b5465737420537472696e6700'}"
    )
    print(f"{stream.get_byte()}")
    nbt = CompoundTag()
    nbt.deserialize(stream)
    print(f"{nbt.to_snbt()}")
    nbt["aaa"]["bbb"] = [
        {"a": "b", "1": "2"},
        {"c": "d", "3": 4},
        {"e": "f", "5": True},
    ]
    merge_nbt = CompoundTag(
        {
            "string_tag": "测试（非ASCII）",
            "byte_array_tag": b"114514",
            "aaa": {"bbb": [{"c": "d", "3": 4}, {"g": "h", "7": ShortTag(8)}]},
        }
    )
    nbt.merge(merge_nbt, True)
    nbt["test"] = ListTag([-122, 1673892, 9825678])
    nbt["test"] = [233122, 37477]
    print(nbt.to_snbt(SnbtFormat.Default | SnbtFormat.ForceAscii))
    print(nbt["test"].get_type())


if __name__ == "__main__":
    print("-" * 25, "Test1", "-" * 25)
    test1()
    print("-" * 25, "Test2", "-" * 25)
    test2()
    print("-" * 25, "Test3", "-" * 25)
    test3()
    print("-" * 25, "Test4", "-" * 25)
    test4()
    print("-" * 25, "END", "-" * 25)
