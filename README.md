# RapidNBT

[![GitHub Actions Workflow Status](https://img.shields.io/github/actions/workflow/status/GlacieTeam/NBT/build.yml)](https://github.com/GlacieTeam/NBT/actions)
[![GitHub License](https://img.shields.io/github/license/GlacieTeam/NBT)](https://www.mozilla.org/en-US/MPL/2.0/)
[![C++23](https://img.shields.io/badge/C++-23-blue?logo=C%2B%2B&logoColor=41a3ed)](https://en.cppreference.com/w/cpp/compiler_support.html)   
[![PyPI - Version](https://img.shields.io/pypi/v/rapidnbt)](https://pypi.org/project/rapidnbt)
[![Python](https://img.shields.io/pypi/pyversions/rapidnbt?logo=python&logoColor=white)](https://www.python.org/)

Python Bindings for a High-Performance NBT Library  

[![Readme Card](https://github-readme-stats.vercel.app/api/pin/?username=GlacieTeam&repo=NBT)](https://github.com/GlacieTeam/NBT)

## Install 🔧
```bash
pip install rapidnbt
```

## Supported NBT format 📖

| NBT Format                        | Minecraft Edition      | Support Status     |
| --------------------------------- | ---------------------- | ------------------ |
| Little Endian Binary              | Bedrock Edition        | :white_check_mark: |
| Little Endian Binary with Header  | Bedrock Edition        | :white_check_mark: |
| Big Endian Binary                 | Java Edition           | :white_check_mark: |
| Big Endian Binary with Header     | Java Edition           | :white_check_mark: |
| Bedrock Network (VarInt Encoding) | Bedrock Edition        | :white_check_mark: |
| Formatted String (SNBT)           | Bedrock & Java Edition | :white_check_mark: |

## Benchmarks 🚀
Comparing with some popular NBT libraries.  

Parsing NBT file (870 MB, little-endian binary NBT)

| Library          | Link                                      | Time         | Performance    | Memory Usage |
| ---------------- | ------------------------------------------| ------------ | -------------- | ------------ |
| RapidNBT         | <https://github.com/GlacieTeam/RapidNBT>  | 5.2s         | 100%           | 4800MB       |
| nbtlib           | <https://github.com/vberlier/nbtlib>      | 33.9s        | 15.3%          | 6500MB       |
| PyNBT            | <https://github.com/TkTech/PyNBT>         | 33.4s        | 15.6%          | 8900MB       |

> Tested on Intel i7 14700-HX with 32GB DDR5-5400 using 720MB little-endian binary NBT

## Usage & Examples
1. Load NBT from file and modify it
```Python
from rapidnbt import nbtio, Int64Tag
from ctypes import c_int16

def example(path: str):
    nbt = nbtio.load("./level.dat") # Automatically detect nbt file format and decompress (if compressed)
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

2. Create a NBT in memory and save it to file
```Python
from rapidnbt import nbtio, CompoundTag, ShortTag, Int64Tag, DoubleTag, IntArrayTag, NbtFileFormat
from ctypes import c_uint8, c_double

# Create a NBT in memory
nbt = CompoundTag(
    {
        "string": "Test String",
        "byte": c_uint8(114),
        "short": ShortTag(19132),
        "int": 114514,
        "int64": Int64Tag(1145141919810),
        "float": 1.4142,
        "double": c_double(3.1415926535897),
        "byte_array": b"13276273923",
        "list": ["string1", "string2"],
        "compound": nbt,
        "int_array": IntArrayTag([1, 2, 3, 4, 5, 6, 7]),
        "long_array": LongArrayTag([1, 2, 3, 4, 5, 6, 7]),
    }
)

print(nbt.to_snbt()) # Print SNBT

# Save NBT to file
nbtio.dump(nbt, "./test.nbt", NbtFileFormat.LITTLE_ENDIAN)

```

# Used Libraries 📖
| Library          | License      | Link                                         |
| ---------------- | ------------ | -------------------------------------------- |
| NBT              | MPL-2.0      | <https://github.com/GlacieTeam/NBT>          |
| pybind11         | BSD-3-Clause | <https://github.com/pybind/pybind11>         |
| magic_enum       | MIT          | <https://github.com/Neargye/magic_enum>      |

## Contributing 🤝
Contributions are welcome! Please follow these steps:

1. Fork the repository and create your feature branch
2. Add tests for any new functionality
3. Submit a pull request with detailed description


## License 📄
This project is licensed under the **Mozilla Public License 2.0 (MPL-2.0)**.  

### Key Requirements:
- **Modifications to this project's files** must be released under MPL-2.0.  
- **Using this library in closed-source projects** is allowed (no requirement to disclose your own code).  
- **Patent protection** is explicitly granted to all users.  

For the full license text, see [LICENSE](LICENSE) file or visit [MPL 2.0 Official Page](https://www.mozilla.org/en-US/MPL/2.0/).  

---


### Copyright © 2025 GlacieTeam. All rights reserved.