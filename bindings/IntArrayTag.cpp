// Copyright © 2025 GlacieTeam.All rights reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
//
// SPDX-License-Identifier: MPL-2.0

#include "NativeModule.hpp"

namespace rapidnbt {

void bindIntArrayTag(py::module& m) {
    auto sm = m.def_submodule("int_array_tag", "A tag contains an int array");

    py::class_<nbt::IntArrayTag, nbt::Tag>(sm, "IntArrayTag")
        .def(py::init<>(), "Construct an empty IntArrayTag")
        .def(
            py::init<std::vector<int> const&>(),
            py::arg("values"),
            "Construct from a list of integers",
            "Example:",
            "    IntArrayTag([1, 2, 3]))"
        )

        .def("get_type", &nbt::IntArrayTag::getType, "Get the NBT type ID (int array)")
        .def("equals", &nbt::IntArrayTag::equals, py::arg("other"), "Check if this tag equals another tag")
        .def("copy", &nbt::IntArrayTag::copy, "Create a deep copy of this tag")
        .def("hash", &nbt::IntArrayTag::hash, "Compute hash value of this tag")
        .def(
            "write",
            [](nbt::IntArrayTag& self, bstream::BinaryStream& stream) { self.write(stream); },
            py::arg("stream"),
            "Write int array to a binary stream"
        )
        .def(
            "load",
            [](nbt::IntArrayTag& self, bstream::ReadOnlyBinaryStream& stream) { self.load(stream); },
            py::arg("stream"),
            "Load int array from a binary stream"
        )

        .def("size", &nbt::IntArrayTag::size, "Get number of elements in the array")
        .def(
            "empty",
            [](nbt::IntArrayTag const& self) { return self.size() == 0; },
            "Check if the array is empty"
        )
        .def(
            "reserve",
            &nbt::IntArrayTag::reserve,
            py::arg("capacity"),
            R"(Reserve storage capacity for the array
            
            Arguments:
                capacity: Minimum capacity to reserv))"
        )
        .def("clear", &nbt::IntArrayTag::clear, "Remove all elements from the array")
        .def(
            "__getitem__",
            [](nbt::IntArrayTag const& self, size_t index) {
                if (index >= self.size()) { throw py::index_error("index out of range"); }
                return self[index];
            },
            py::arg("index"),
            "Get element at index without bounds checking"
        )
        .def(
            "__setitem__",
            [](nbt::IntArrayTag& self, size_t index, int value) {
                if (index >= self.size()) { throw py::index_error("index out of range"); }
                self[index] = value;
            },
            py::arg("index"),
            py::arg("value"),
            "Set element at index"
        )
        .def("append", &nbt::IntArrayTag::push_back, py::arg("value"), "Append an integer to the end of the array")
        .def(
            "pop",
            py::overload_cast<size_t>(&nbt::IntArrayTag::remove),
            py::arg("index"),
            "Remove element at specified index\nReturns:    True if successful, False if index out of range"
        )
        .def(
            "pop",
            py::overload_cast<size_t, size_t>(&nbt::IntArrayTag::remove),
            py::arg("start_index"),
            py::arg("end_index"),
            R"(Remove elements in the range [start_index, end_index)

            Arguments:
                start_index: First index to remove (inclusive)
                end_index: End index (exclusive)

            Returns:
                 True if successful, False if indices out of range)"
        )
        .def(
            "assign",
            [](nbt::IntArrayTag& self, std::vector<int> const& values) {
                self = values;
                return self;
            },
            py::arg("values"),
            R"(Assign new values to the array
            Returns the modified array)"
        )

        .def_property(
            "value",
            [](nbt::IntArrayTag& self) -> std::vector<int> { return self.storage(); },
            [](nbt::IntArrayTag& self, std::vector<int> const& value) { self.storage() = value; },
            "Access the int array as a list of integers"
        )

        .def(
            "__eq__",
            [](nbt::IntArrayTag const& self, nbt::IntArrayTag const& other) { return self.equals(other); },
            py::arg("other")
        )
        .def("__hash__", &nbt::IntArrayTag::hash, "Compute hash value for Python hashing operations")
        .def(
            "__iter__",
            [](nbt::IntArrayTag const& self) {
                return py::make_iterator(self.storage().begin(), self.storage().end());
            },
            py::keep_alive<0, 1>(),
            R"(Iterate over elements in the array
            Example:
                for value in int_array:
                    print(value))"
        )
        .def(
            "__contains__",
            [](nbt::IntArrayTag const& self, int value) {
                const auto& vec = self.storage();
                return std::find(vec.begin(), vec.end(), value) != vec.end();
            },
            py::arg("value"),
            "Check if value is in the array"
        )
        .def("__len__", &nbt::IntArrayTag::size, "Get number of int in the array")
        .def(
            "__str__",
            [](nbt::IntArrayTag const& self) { return self.toSnbt(nbt::SnbtFormat::Minimize); },
            "String representation (SNBT minimized format)"
        )
        .def(
            "__repr__",
            [](nbt::IntArrayTag const& self) {
                return std::format(
                    "<rapidnbt.IntArrayTag(size={0}) object at 0x{1:0{2}X}>",
                    self.size(),
                    reinterpret_cast<uintptr_t>(&self),
                    ADDRESS_LENGTH
                );
            },
            "Official string representation"
        );
}

} // namespace rapidnbt