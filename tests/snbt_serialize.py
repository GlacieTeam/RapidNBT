# Copyright © 2025 GlacieTeam. All rights reserved.
#
# This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
# distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
#
# SPDX-License-Identifier: MPL-2.0


from ctypes import c_int16
import numpy as np
from rapidnbt import (
    CompoundTag,
    LongTag,
    DoubleTag,
    StringTag,
    ByteArrayTag,
    IntArrayTag,
    LongArrayTag,
    SnbtFormat,
    SnbtNumberFormat,
)


def main():
    nbt = CompoundTag(
        {
            "byte": True,
            "short": c_int16(26382),
            "int": 245673112,
            "long": LongTag(4567289187654),
            "float": 3.1415,
            "double": DoubleTag(1.414213562),
            "list": ["string1", StringTag("string2"), "string3"],
            "compound": {
                "str": "简体中文(not ASCII)",
                "numpy": IntArrayTag(
                    np.array(
                        [
                            11111,
                            22222,
                            33333,
                        ]
                    )
                ),
            },
            "byte_array": ByteArrayTag([1, 2, 3, 4, 5, 6, 7]),  # list
            "int_array": IntArrayTag((23476, 56278, 256718)),  # tuple
            "long_array": LongArrayTag({1234567, 367819, 6789023}),  # set
        }
    )

    print(
        nbt.to_snbt(
            format=SnbtFormat.Default
            | SnbtFormat.ForceAscii
            | SnbtFormat.ForceValueQuote
            | SnbtFormat.ForceLineFeedIgnoreIndent,
            indent=0,
            number_format=SnbtNumberFormat.LowerHexadecimal,
        )
    )


if __name__ == "__main__":
    main()
