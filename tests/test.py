from rapidnbt import *
import ctypes


def main() -> None:
    tag = CompoundTagVariant(EndTag())
    print(tag.to_snbt())


if __name__ == "__main__":
    print("-" * 25, "Test", "-" * 25)
    main()
    print("-" * 25, "End", "-" * 25)
