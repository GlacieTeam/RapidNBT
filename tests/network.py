# Copyright © 2025 GlacieTeam. All rights reserved.
#
# This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
# distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
#
# SPDX-License-Identifier: MPL-2.0


from bstream import BinaryStream
from rapidnbt import CompoundTag, ByteTag, StringTag, ShortTag, IntTag


def main():
    nbt = CompoundTag(
        {
            "string_tag": StringTag("Test String"),
            "byte_tag": ByteTag(114),
            "short_tag": ShortTag(19132),
            "int_tag": IntTag(114514),
        }
    )

    stream = BinaryStream()

    # Serialize test
    stream.write_byte(23)
    nbt.serialize(stream)

    buffer = stream.data()
    print(f"stream buffer: {buffer.hex()}")
    check = (
        buffer.hex()
        == "170a000108627974655f746167720307696e745f746167a4fd0d020973686f72745f746167bc4a080a737472696e675f7461670b5465737420537472696e6700"
    )
    print(f"stream check: {check}")

    # Deserialize test
    header = stream.get_byte()
    print(f"header: {header}")

    nbt2 = CompoundTag()
    nbt2.deserialize(stream)
    print(f"{nbt2.to_snbt()}")


if __name__ == "__main__":
    main()
