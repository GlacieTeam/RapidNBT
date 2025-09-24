# Copyright © 2025 GlacieTeam.All rights reserved.
#
# This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy
# of the MPL was not distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
#
# SPDX-License-Identifier: MPL-2.0

from enum import Enum

class NbtFileFormat(Enum):
    """
    Enumeration of NBT binary file formats
    """

    LITTLE_ENDIAN = 0
    LITTLE_ENDIAN_WITH_HEADER = 1
    BIG_ENDIAN = 2
    BIG_ENDIAN_WITH_HEADER = 3
    BEDROCK_NETWORK = 4
