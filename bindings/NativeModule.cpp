// Copyright © 2025 GlacieTeam.All rights reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
//
// SPDX-License-Identifier: MPL-2.0

#include "NativeModule.hpp"

namespace rapidnbt {

PYBIND11_MODULE(_NBT, m) {
    m.doc() = "Python bindings for NBT library";
    bindEnums(m);
    bindCompoundTagVariant(m);
    bindTag(m);
    bindEndTag(m);
    bindByteTag(m);
    bindShortTag(m);
    bindIntTag(m);
    bindLongTag(m);
    bindFloatTag(m);
    bindDoubleTag(m);
    bindByteArrayTag(m);
    bindStringTag(m);
    bindListTag(m);
    bindCompoundTag(m);
    bindIntArrayTag(m);
    bindLongArrayTag(m);
    bindNbtIO(m);
    bindNbtFile(m);
}

} // namespace rapidnbt