# RapidNBT

[![GitHub Actions Workflow Status](https://img.shields.io/github/actions/workflow/status/GlacieTeam/RapidNBT/build.yml)](https://github.com/GlacieTeam/RapidNBT/actions)
[![GitHub License](https://img.shields.io/github/license/GlacieTeam/RapidNBT)](https://www.mozilla.org/en-US/MPL/2.0/)
[![C++23](https://img.shields.io/badge/C++-23-blue?logo=C%2B%2B&logoColor=41a3ed)](https://en.cppreference.com/w/cpp/compiler_support.html)   
[![PyPI - Version](https://img.shields.io/pypi/v/rapidnbt)](https://pypi.org/project/rapidnbt)
[![Python](https://img.shields.io/pypi/pyversions/rapidnbt?logo=python&logoColor=white)](https://www.python.org/)  
[![PyPI - Downloads](https://img.shields.io/pypi/dm/rapidnbt)](https://pypi.org/project/rapidnbt/)


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

**Full SNBT support** - Full SNBT format support, include the new SNBT format since Java Edition 1.21.5

## Benchmarks 🚀
Comparing with some popular NBT libraries.  

Parsing NBT file (870 MB, little-endian binary NBT)

| Library          | Link                                      | Time         | Performance    | Memory Usage |
| ---------------- | ------------------------------------------| ------------ | -------------- | ------------ |
| RapidNBT         | <https://github.com/GlacieTeam/RapidNBT>  | 5.2s         | 100%           | 4800MB       |
| nbtlib           | <https://github.com/vberlier/nbtlib>      | 33.9s        | 15.3%          | 6500MB       |
| PyNBT            | <https://github.com/TkTech/PyNBT>         | 33.4s        | 15.6%          | 8900MB       |

> Tested on Intel i7 14700-HX with 32GB DDR5-5400 using 720MB little-endian binary NBT

## Quick Start 🚀
RapidNBT provides a morden and safe API, and it is easy to use.

1. Load NBT from file and modify it
```Python
from rapidnbt import nbtio, LongTag
from ctypes import c_int16

def example():
    nbt = nbtio.load("./level.dat") # Automatically detect nbt file format and decompress (if compressed)
    # nbt = nbtio.load("./level.dat", NbtFileFormat.BIG_ENDIAN) # You can also specify the file format

    # Modify NBT
    nbt["abc"]["def"] = True # bool will automatically convert to ByteTag(1)
    nbt["ghi"]["hjk"] = c_int16(23) # ctypes.c_int16 will automatically convert to ShortTag(23)
    nbt["lmn"] = ["test1", "test2"] # Python list will automatically convert to ListTag([StringTag("test1"), StringTag("test2")])
    nbt["opq"]["rst"] = { # Python dict will automatically convert to CompoundTag
        "key1": False,
        "key2": b"2345",  # bytes/bytearray will automatically convert to ByteArrayTag
        "key3": LongTag(114514), # You can also directly use Tag
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
from rapidnbt import nbtio, CompoundTag, ShortTag, LongTag, DoubleTag, IntArrayTag, NbtFileFormat
from ctypes import c_uint8, c_double

# Create a NBT in memory
nbt = CompoundTag(
    {
        "string": "Test String",
        "byte": c_uint8(114),
        "short": ShortTag(19132),
        "int": 114514,
        "int64": LongTag(1145141919810),
        "float": 1.4142,
        "double": c_double(3.1415926535897),
        "byte_array": b"13276273923",
        "list": ["string1", "string2"],
        "compound": nbt,
        "int_array": IntArrayTag([1, 2, 3, 4, 5, 6, 7]),
        "long_array": LongArrayTag([1, 2, 3, 4, 5, 6, 7]),
    }
)

# Print SNBT
print(nbt.to_snbt()) 
# Or you can specify SNBT format
print(file.to_snbt(format=SnbtFormat.Classic | SnbtFormat.MarkExtra, indent=4))
# Use | to combime format 

# Save NBT to file
nbtio.dump(nbt, "./test.nbt", NbtFileFormat.LITTLE_ENDIAN)

```
3. Use context manager to operate NBT file
```Python
from rapidnbt import LongTag, nbtio

# use context manager
with nbtio.open("level.dat") as file:
    file["RandomSeed"] = LongTag(1145141919810) # modify NBT
    # Auto save file as original format when exit context manager
```

4. Read NBT data
```Python
from rapidnbt import nbtio

def example():
    nbt = nbtio.load("./test.nbt") # Automatically detect nbt file format and decompress (if compressed)
    
    value1 = nbt["abc"]["def"].value # Use .value method to get any tag value, and returns a Python object (Python int, str, dict, etc...)

    value2 = nbt["ghi"]["hjk"].get_short() # Use .get_xxx method to safely get tag value, and will throw TypeError if tag is wrong type

    exits = "lmn" in nbt # Check if a tag exist in this NBT
    # exits = nbt.contains("lmn") You can also use .contains() method to check

    del nbt["opq"]["rst"] # Delete a tag in NBT
    # nbt["opq"].remove("rst") You can also use .remove() method to delete
    
    nbt.rename("abc", "ABC") # Rename a key in NBT
```

> ### More details please see the docstring in `.pyi` file

## CLI 🔧
You can use CLI commands to opeartor NBT files easily.  
Use `nbt` or `python -m rapidnbt` to run CLI
```bash
options:
  -h, --help            show this help message and exit
  -p, --print           print NBT as a formatted string
  -i, --indent INDENT   NBT format indent
  -j, --json            format NBT as a json string
  -o, --output OUTPUT   NBT output file path
  --little              NBT output should use little endian format
  --big                 NBT output should use big endian format
  --network             NBT output should use bedrock network format
  --snbt                NBT output should use a formatted string nbt
  --header              NBT output should write header
  -m, --merge           NBT output should merge exist NBT
  --merge-list          NBT should merge ListTag instead of replace it
  -c, --compression {none,gzip,zlib}
                        NBT output should merge exist NBT
```

**1. Print a NBT file as SNBT**  
eg. level.dat
```bash
nbt level.dat -p
```

**2. Print a NBT file as a json**  
eg. level.dat, indent = 2
```bash
nbt level.dat -pj --indent=2
```

**3. Convert a NBT file to other format**  
eg. convert level.dat to SNBT and save as level.snbt
```bash
python -m rapidnbt level.dat --output=level.snbt --indent=0
```

**4. Merge NBT**  
eg. use player1.nbt to patch player2.nbt (little-endian, no compression)
```bash
nbt player1.dat --output=player2.nbt --merge --little --compression=none
```

## Used Libraries 📖
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