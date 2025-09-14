from rapidnbt import *


def test1():
    tag = CompoundTagVariant(StringTag("homo114514"))
    print(tag.to_snbt())


def test2():
    pass


if __name__ == "__main__":
    print("-" * 25, "Test 1", "-" * 25)
    test1()
    print("-" * 25, "Test 2", "-" * 25)
    test2()
    print("-" * 25, "End", "-" * 25)
