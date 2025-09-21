# Copyright © 2025 GlacieTeam.All rights reserved.
#
# This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy
# of the MPL was not distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
#
# SPDX-License-Identifier: MPL-2.0

from enum import Enum

class SnbtFormat(Enum):
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
    CommentMarks = 128
    Jsonify = 167

    def __or__(self, value: SnbtFormat) -> SnbtFormat: ...
    def __and__(self, value: SnbtFormat) -> SnbtFormat: ...
