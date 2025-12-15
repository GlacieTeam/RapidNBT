# Copyright © 2025 GlacieTeam. All rights reserved.
#
# This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
# distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
#
# SPDX-License-Identifier: MPL-2.0

from rapidnbt import nbtio


def main():
    snbt = """
    // comment 1
    
    /**
    * comments 2
    */
    
    {
           byte: 0b,
    "byte_array": [   /*B;*/   0b100111b, -32sb, -0x3FSb, 0xFcuB, 45ub, -86 
    /*sb*/, 0x45     /*ub*/],
    compound: {
        'numpy': [I;11111si, 22222ui, 0x33333]   /* comments */,
        str: '\u7b80\u4f53\u4e2d\u6587'     /* comments */
    },
    
    // comments
    
    double: 1.4142135d,
    float: 3.1415f,
    
    /**
    * comments
    */
    
    int: 245673112si,     // comments
    int_array: [I;23476, 56278, 256718],    /* comments */
    list: [
        'string1',    /* comments */
        string2,     // comments
        "string3"
    ],
    long: 4567289187654l,    /* comments */
    long_array: [L;1234567l, 367819l, 6789023l],  /* comments */
    short: 26382s
}
    """
    nbt = nbtio.loads_snbt(snbt)
    print(nbt.to_snbt())


if __name__ == "__main__":
    main()
