# Copyright © 2025 GlacieTeam.All rights reserved.
#
# This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy
# of the MPL was not distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
#
# SPDX-License-Identifier: MPL-2.0

from enum import IntFlag, Enum

class SnbtFormat(IntFlag):
    """
    The SNBT format enum
    You can use | operation to combime flags
    Example:
        format = SnbtFormat.Classic | SnbtFormat.ForceUppercase
    """

    Minimize = 0
    CompoundLineFeed = 1
    ListArrayLineFeed = 2
    PrettyFilePrint = 3
    Default = 3
    BinaryArrayLineFeed = 4
    ArrayLineFeed = 6
    AlwaysLineFeed = 7
    ForceLineFeedIgnoreIndent = 8
    ForceAscii = 16
    ForceKeyQuote = 32
    Classic = 35
    ForceValueQuote = 64
    ForceQuote = 96
    ForceUppercase = 128
    MarkIntTag = 256
    MarkDoubleTag = 512
    MarkAllTags = 768
    CommentMarks = 1024
    Jsonify = 1127
    MarkSigned = 2048

class SnbtNumberFormat(Enum):
    Decimal = 0
    LowerHexadecimal = 1
    UpperHexadecimal = 2
    Binary = 3
