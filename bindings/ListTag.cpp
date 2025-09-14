// Copyright © 2025 GlacieTeam.All rights reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
//
// SPDX-License-Identifier: MPL-2.0

#include "NativeModule.hpp"

namespace rapidnbt {

void bindListTag(py::module& m) {
    py::class_<nbt::ListTag, nbt::Tag>(m, "ListTag")
        .def(py::init<>(), "Construct an empty ListTag")
        .def(
            py::init([](std::vector<py::object> elements) {
                auto tag = std::make_unique<nbt::ListTag>();
                for (auto& element : elements) {
                    auto& value = static_cast<py::object&>(element);
                    if (py::isinstance<nbt::Tag>(value)) {
                        tag->push_back(value.cast<nbt::Tag*>()->copy());
                    } else {
                        tag->push_back(makeNativeTag(value));
                    }
                }
                return tag;
            }),
            py::arg("elements"),
            "Construct from a list of Tag elements (e.g., [IntTag(1), StringTag('test')])"
        )

        .def("get_type", &nbt::ListTag::getType, "Get the NBT type ID (List)")
        .def(
            "equals",
            &nbt::ListTag::equals,
            py::arg("other"),
            "Check if this tag equals another tag (same elements in same order)"
        )
        .def("copy", &nbt::ListTag::copy, "Create a deep copy of this tag")
        .def(
            "copy_list",
            &nbt::ListTag::copyList,
            "Create a deep copy of this list (same as copy() but returns ListTag)"
        )
        .def("hash", &nbt::ListTag::hash, "Compute hash value of this tag")

        .def(
            "write",
            [](nbt::ListTag& self, bstream::BinaryStream& stream) { self.write(stream); },
            py::arg("stream"),
            "Write list to a binary stream"
        )
        .def(
            "load",
            [](nbt::ListTag& self, bstream::ReadOnlyBinaryStream& stream) { self.load(stream); },
            py::arg("stream"),
            "Load list from a binary stream"
        )

        .def(
            "append",
            [](nbt::ListTag& self, py::object element) {
                if (py::isinstance<nbt::Tag>(element)) {
                    self.push_back(element.cast<nbt::Tag*>()->copy());
                } else {
                    self.push_back(makeNativeTag(element));
                }
            },
            py::arg("element"),
            "Append a Tag element to the list"
        )

        .def(
            "__getitem__",
            [](nbt::ListTag& self, size_t index) -> nbt::Tag& {
                if (index >= self.size()) { throw py::index_error("Index out of range"); }
                return self[index];
            },
            py::return_value_policy::reference_internal,
            py::arg("index"),
            "Get element at specified index"
        )
        .def(
            "__setitem__",
            [](nbt::ListTag& self, size_t index, py::object const& element) {
                if (index >= self.size()) { throw py::index_error("Index out of range"); }
                if (py::isinstance<nbt::Tag>(element)) {
                    self[index] = *element.cast<nbt::Tag*>();
                } else {
                    self[index] = *makeNativeTag(element);
                }
            },
            py::arg("index"),
            py::arg("element"),
            "Set element at specified index"
        )

        .def("size", &nbt::ListTag::size, "Get number of elements in the list")
        .def("empty", &nbt::ListTag::empty, "Check if the list is empty")
        .def(
            "get_element_type",
            [](nbt::ListTag const& self) { return self.getElementType(); },
            "Get the type of elements in this list (returns nbt.Type enum)"
        )
        .def("reserve", &nbt::ListTag::reserve, py::arg("size"), "Preallocate memory for future additions")
        .def(
            "pop",
            [](nbt::ListTag& self, size_t index) { return self.remove(index); },
            py::arg("index"),
            "Remove element at specified index"
        )
        .def(
            "pop",
            [](nbt::ListTag& self, size_t start, size_t end) { return self.remove(start, end); },
            py::arg("start_index"),
            py::arg("end_index"),
            "Remove elements in the range [start_index, end_index)"
        )
        .def("clear", &nbt::ListTag::clear, "Remove all elements from the list")
        .def(
            "merge",
            &nbt::ListTag::merge,
            py::arg("other"),
            "Merge another ListTag into this one (appends all elements)"
        )

        .def(
            "insert",
            [](nbt::ListTag& self, size_t index, py::object element) {
                if (index > self.size()) { throw py::index_error("Index out of range"); }
                auto it = self.begin();
                std::advance(it, index);
                if (py::isinstance<nbt::Tag>(element)) {
                    self.storage().insert(it, element.cast<nbt::Tag*>()->copy());
                } else {
                    self.storage().insert(it, makeNativeTag(element));
                }
            },
            py::arg("index"),
            py::arg("element"),
            "Insert element at specified position"
        )

        .def("__len__", &nbt::ListTag::size, "Get number of elements in the list")
        .def(
            "__iter__",
            [](nbt::ListTag& self) { return py::make_iterator(self.begin(), self.end()); },
            py::keep_alive<0, 1>(),
            "Iterate over elements in the list"
        )
        .def("__eq__", &nbt::ListTag::equals, py::arg("other"), "Equality operator (==)")
        .def("__hash__", &nbt::ListTag::hash, "Compute hash value for Python hashing operations")
        .def(
            "__str__",
            [](nbt::ListTag const& self) { return self.toSnbt(nbt::SnbtFormat::Minimize); },
            "String representation (SNBT minimized format)"
        )
        .def(
            "__repr__",
            [](nbt::ListTag const& self) {
                return std::format(
                    "<rapidnbt.ListTag(size={0}) object at 0x{1:0{2}X}>",
                    self.size(),
                    reinterpret_cast<uintptr_t>(&self),
                    ADDRESS_LENGTH
                );
            },
            "Official string representation"
        );
}

} // namespace rapidnbt