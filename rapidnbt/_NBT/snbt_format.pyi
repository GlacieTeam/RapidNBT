# Copyright © 2025 GlacieTeam.All rights reserved.
#
# This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy
# of the MPL was not distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
#
# SPDX-License-Identifier: MPL-2.0

from enum import IntFlag

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
    ForceQuote = 32
    Classic = 35
    ForceUppercase = 64
    MarkIntTag = 128
    MarkDoubleTag = 256
    MarkExtra = 384
    CommentMarks = 512
    Jsonify = 551
