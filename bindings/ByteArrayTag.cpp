// Copyright © 2025 GlacieTeam.All rights reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
//
// SPDX-License-Identifier: MPL-2.0

#include "NativeModule.hpp"

namespace rapidnbt {

void bindByteArrayTag(py::module& m) {
    py::class_<nbt::ByteArrayTag, nbt::Tag>(m, "ByteArrayTag")
        .def(py::init<>(), "Construct an empty ByteArrayTag")
        .def(
            py::init<std::vector<uint8_t> const&>(),
            py::arg("arr"),
            "Construct from a list of bytes (e.g., [1, 2, 3])"
        )

        .def("getType", &nbt::ByteArrayTag::getType, "Get the NBT type ID (ByteArray)")
        .def(
            "equals",
            &nbt::ByteArrayTag::equals,
            py::arg("other"),
            "Check if this tag equals another tag (same bytes and type)"
        )
        .def("copy", &nbt::ByteArrayTag::copy, "Create a deep copy of this tag")
        .def("hash", &nbt::ByteArrayTag::hash, "Compute hash value of this tag")

        .def(
            "write",
            [](nbt::ByteArrayTag& self, bstream::BinaryStream& stream) { self.write(stream); },
            py::arg("stream"),
            "Write tag to a binary stream"
        )
        .def(
            "load",
            [](nbt::ByteArrayTag& self, bstream::ReadOnlyBinaryStream& stream) { self.load(stream); },
            py::arg("stream"),
            "Load tag value from a binary stream"
        )

        .def_property(
            "value",
            [](nbt::ByteArrayTag& self) -> py::bytes { return to_pybytes(static_cast<std::string_view>(self)); },
            [](nbt::ByteArrayTag& self, py::buffer value) {
                py::buffer_info info = value.request();
                const char*     data = static_cast<const char*>(info.ptr);
                size_t          size = info.size;
                self                 = std::string_view(data, size);
            },
            "Access the byte array as a list of integers (0-255)"
        )
        .def(
            "data",
            [](nbt::ByteArrayTag& self) { return py::memoryview::from_memory(self.data(), self.size()); },
            "Get a raw memory view of the byte data"
        )

        .def(
            "__getitem__",
            [](nbt::ByteArrayTag& self, size_t index) {
                if (index >= self.size()) { throw py::index_error("Index out of range"); }
                return self[index];
            },
            py::arg("index"),
            "Get byte at specified index"
        )
        .def(
            "__setitem__",
            [](nbt::ByteArrayTag& self, size_t index, uint8_t value) {
                if (index >= self.size()) { throw py::index_error("Index out of range"); }
                self[index] = value;
            },
            py::arg("index"),
            py::arg("value"),
            "Set byte at specified index"
        )

        .def("size", &nbt::ByteArrayTag::size, "Get number of bytes in the array")
        .def("reserve", &nbt::ByteArrayTag::reserve, py::arg("size"), "Preallocate memory for future additions")
        .def("clear", &nbt::ByteArrayTag::clear, "Clear all byte data")
        .def(
            "push_back",
            [](nbt::ByteArrayTag& self, uint8_t value) { self.push_back(value); },
            py::arg("value"),
            "Add a byte to the end of the array"
        )
        .def(
            "remove",
            [](nbt::ByteArrayTag& self, size_t index) { return self.remove(index); },
            py::arg("index"),
            "Remove byte at specified index"
        )
        .def(
            "remove",
            [](nbt::ByteArrayTag& self, size_t start, size_t end) { return self.remove(start, end); },
            py::arg("start_index"),
            py::arg("end_index"),
            "Remove bytes in the range [start_index, end_index)"
        )
        .def(
            "assign",
            [](nbt::ByteArrayTag& self, py::buffer value) {
                py::buffer_info info = value.request();
                const char*     data = static_cast<const char*>(info.ptr);
                size_t          size = info.size;
                self                 = std::string_view(data, size);
                return self;
            },
            py::arg("bytes"),
            py::return_value_policy::reference_internal,
            "Assign new binary data from a list of bytes"
        )

        .def(
            "__bytes__",
            [](const nbt::ByteArrayTag& self) {
                return py::bytes(reinterpret_cast<const char*>(self.data()), self.size());
            },
            "Convert to Python bytes object"
        )
        .def("__len__", &nbt::ByteArrayTag::size, "Get number of bytes in the array")
        .def(
            "__iter__",
            [](nbt::ByteArrayTag& self) { return py::make_iterator(self.storage().begin(), self.storage().end()); },
            py::keep_alive<0, 1>(),
            "Iterate over bytes in the array"
        )
        .def("__eq__", &nbt::ByteArrayTag::equals, py::arg("other"), "Equality operator (==)")
        .def("__hash__", &nbt::ByteArrayTag::hash, "Compute hash value for Python hashing operations")
        .def(
            "__str__",
            [](const nbt::ByteArrayTag& self) { return self.toSnbt(nbt::SnbtFormat::Minimize); },
            "Human-readable string representation"
        )
        .def(
            "__repr__",
            [](const nbt::ByteArrayTag& self) { return std::format("ByteArrayTag(size={})", self.size()); },
            "Official string representation"
        );
}

} // namespace rapidnbt