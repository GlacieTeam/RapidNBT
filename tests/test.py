from rapidnbt import *
from ctypes import c_int8, c_uint8, c_int16, c_uint16, c_int64, c_uint64, c_float


def test1():
    tag = CompoundTagVariant(
        [[1, 2, 34, 92873, 52678, -56278], [c_int16(23), c_int16(87)]]
    )
    print(tag.to_snbt())
    for t in tag:
        print(t.to_snbt())


def test2():
    pass


if __name__ == "__main__":
    print("-" * 25, "Test 1", "-" * 25)
    test1()
    print("-" * 25, "Test 2", "-" * 25)
    test2()
    print("-" * 25, "End", "-" * 25)
