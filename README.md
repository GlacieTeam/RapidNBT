# RapidNBT
Python Bindings for High-Performance NBT Library

## Install
```bash
pip install bedrock-protocol-nbt
```

## Usage & Examples
1. load nbt from file / dump nbt to file
```Python
from rapidnbt import nbtio, Int64Tag
from ctypes import c_int16

def example(path: str):
    nbt = nbtio.load("./level.dat") # Automatically detect nbt file format
    # nbt = nbtio.load("./level.dat", NbtFileFormat.BIG_ENDIAN) # You can also specify the file format

    # Modify NBT
    nbt["abc"]["def"] = True # bool will automatically convert to ByteTag(1)
    nbt["ghi"]["hjk"] = c_int16(23) # ctypes.c_int16 will automatically convert to ShortTag(23)
    nbt["lmn"] = ["test1", "test2"] # list will automatically convert to ListTag([StringTag("test1"), StringTag("test2")])
    nbt["opq"]["rst"] = {
        "key1": False,
        "key2": b"2345",  # bytes/bytearray will automatically convert to ByteArrayTag
        "key3": Int64Tag(114514), # You can also directly use Tag
    }
    """
    You need not to create the NBT node first.
    Example:
        nbt["abc"]["def"] = True
        If nbt["abc"]["def"] does not exist, it will be auto created.
    """ 

    
```



```Python
from rapidnbt import nbtio

# Build a nbt
nbt = CompoundTag(
    {
        "string": StringTag("Test String"),
        "byte", ByteTag(114)
        "short", ShortTag(19132)
        "int", IntTag(114514)
        "int64", Int64Tag(1145141919810)
        "float", FloatTag(114.514)
        "double", DoubleTag(3.1415926535897)
        "byte_array", ByteArrayTag(b"13276273923")
        "list", ListTag([StringTag("1111"), StringTag("2222")])
        "compound", nbt
        "int_array", IntArrayTag([1, 2, 3, 4, 5, 6, 7])
    }
)

print(nbt.to_snbt()) # to string nbt
```

# Used Libraries
| Library          | License      | Link                                         |
| ---------------- | ------------ | -------------------------------------------- |
| NBT              | MPL-2.0      | <https://github.com/GlacieTeam/NBT>          |
| pybind11         | pybind11     | <https://github.com/pybind/pybind11>         |
| magic_enum       | MIT          | <https://github.com/Neargye/magic_enum>      |

## License
This project is licensed under the **Mozilla Public License 2.0 (MPL-2.0)**.  

### Key Requirements:
- **Modifications to this project's files** must be released under MPL-2.0.  
- **Using this library in closed-source projects** is allowed (no requirement to disclose your own code).  
- **Patent protection** is explicitly granted to all users.  

For the full license text, see [LICENSE](LICENSE) file or visit [MPL 2.0 Official Page](https://www.mozilla.org/en-US/MPL/2.0/).  

---


### Copyright © 2025 GlacieTeam. All rights reserved.