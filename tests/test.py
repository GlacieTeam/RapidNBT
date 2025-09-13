from rapidnbt import *


def main() -> None:
    tag = EndTag()
    print(tag.to_snbt())


if __name__ == "__main__":
    print("-" * 25, "Test", "-" * 25)
    main()
    print("-" * 25, "End", "-" * 25)
