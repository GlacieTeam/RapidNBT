# Copyright © 2025 GlacieTeam.All rights reserved.
#
# This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy
# of the MPL was not distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
#
# SPDX-License-Identifier: MPL-2.0

from enum import Enum

class NbtCompressionLevel(Enum):
    """
    Enumeration of compression levels
    """

    DEFAULT = -1
    NO_COMPRESSION = 0
    BEST_SPEED = 1
    LOW = 2
    MEDIUM_LOW = 3
    MEDIUM = 4
    MEDIUM_HIGH = 5
    HIGH = 6
    VERY_HIGH = 7
    ULTRA = 8
    BEST_COMPRESSION = 9
