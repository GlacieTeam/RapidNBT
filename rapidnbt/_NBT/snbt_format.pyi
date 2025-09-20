# Copyright © 2025 GlacieTeam.All rights reserved.
#
# This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy
# of the MPL was not distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
#
# SPDX-License-Identifier: MPL-2.0

from enum import Enum

class SnbtFormat(Enum):
    Minimize = 0
    PrettyFilePrint = 1 << 0
    ArrayLineFeed = 1 << 1
    ForceAscii = 1 << 2
    ForceQuote = 1 << 3
    CommentMarks = 1 << 4
    AlwaysLineFeed = PrettyFilePrint | ArrayLineFeed
    Default = PrettyFilePrint
    Classic = PrettyFilePrint | ForceQuote
    Jsonify = AlwaysLineFeed | ForceQuote | CommentMarks

    def __or__(self, value: SnbtFormat) -> SnbtFormat: ...
