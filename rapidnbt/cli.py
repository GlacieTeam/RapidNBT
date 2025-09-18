# Copyright © 2025 GlacieTeam.All rights reserved.
#
# This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
# distributed with this file, You can obtain one at http:#mozilla.org/MPL/2.0/.
#
# SPDX-License-Identifier: MPL-2.0

from argparse import ArgumentParser
from rapidnbt import nbtio, SnbtFormat, CompoundTag, NbtFileFormat, NbtCompressionType
from pathlib import Path
import os


def Info(output: str):
    print(f"\033[0m[INFO] {output}\033[0m")


def Warn(output: str):
    print(f"\033[33m[WARN] {output}\033[0m")


def Error(output: str):
    print(f"\033[31m[ERROR] {output}\033[0m")


def parse_file(path: str, format: NbtFileFormat):
    if format is not None:
        return nbtio.load(path, format)
    else:
        return nbtio.load_snbt(path)


def write_snbt(nbt: CompoundTag, output: str, indent: int):
    if indent != 0:
        nbtio.dump_snbt(nbt, output, SnbtFormat.PrettyFilePrint, indent)
    else:
        nbtio.dump_snbt(nbt, output, SnbtFormat.Minimize)


def parse_args():
    parser = ArgumentParser(prog="nbt", description="Perform operations on nbt files.")

    # NBT File
    parser.add_argument("file", metavar="<file>", help="target NBT file")

    # Print Options
    parser.add_argument(
        "-p", "--print", action="store_true", help="print NBT as a formatted string"
    )
    parser.add_argument("-i", "--indent", type=int, default=4, help="NBT format indent")
    parser.add_argument(
        "-j", "--json", action="store_true", help="format NBT as a json string"
    )

    # Write Options
    parser.add_argument("-o", "--output", type=str, help="NBT output file path")

    outfmt = parser.add_mutually_exclusive_group()
    outfmt.add_argument(
        "--little",
        action="store_true",
        help="NBT output should use little endian format",
    )
    outfmt.add_argument(
        "--big",
        action="store_true",
        help="NBT output should use big endian format",
    )
    outfmt.add_argument(
        "--network",
        action="store_true",
        help="NBT output should use bedrock network format",
    )
    outfmt.add_argument(
        "--snbt",
        action="store_true",
        help="NBT output should use a formatted string nbt",
    )

    parser.add_argument(
        "--header",
        action="store_true",
        help="NBT output should write header",
    )
    parser.add_argument(
        "-m",
        "--merge",
        action="store_true",
        help="NBT output should merge exist NBT",
    )
    parser.add_argument(
        "--merge-list",
        action="store_true",
        help="NBT should merge ListTag instead of replace it",
    )
    parser.add_argument(
        "-c",
        "--compression",
        type=str,
        choices=["none", "gzip", "zlib"],
        default="gzip",
        help="NBT output should merge exist NBT",
    )

    return parser.parse_args()


def process_print_options(args, nbt: CompoundTag):
    if args.print == True:
        if args.json:
            print(nbt.to_json(args.indent))
        else:
            if args.indent != 0:
                print(nbt.to_snbt(SnbtFormat.PrettyFilePrint, args.indent))
            else:
                print(nbt.to_snbt(SnbtFormat.Minimize))


def process_write_options(args, nbt: CompoundTag, format: NbtFileFormat):
    if args.output is not None:
        if os.path.isabs(args.output):
            output = args.output
        else:
            output = os.path.join(os.getcwd(), args.output)
        os.makedirs(os.path.dirname(output), exist_ok=True)

        if args.snbt == False:
            if args.little == True:
                if args.header == False:
                    format = NbtFileFormat.LITTLE_ENDIAN
                else:
                    format = NbtFileFormat.LITTLE_ENDIAN_WITH_HEADER
            elif args.big == True:
                if args.big == False:
                    format = NbtFileFormat.BIG_ENDIAN
                else:
                    format = NbtFileFormat.BIG_ENDIAN_WITH_HEADER
            elif args.network:
                format = NbtFileFormat.BEDROCK_NETWORK

            if args.compression == "gzip":
                compression = NbtCompressionType.GZIP
            elif args.compression == "zlib":
                compression = NbtCompressionType.ZLIB
            elif args.compression == "none":
                compression = NbtCompressionType.NONE

            if args.merge == False:
                nbtio.dump(nbt, output, format, compression)
            else:
                old = nbtio.load(output)
                if old is not None:
                    old.merge(nbt, args.merge_list)
                    nbtio.dump(old, output, format, compression)
                else:
                    Warn(
                        f"File {Path(output).absolute()} does not exist, skipping merge."
                    )
                    nbtio.dump(nbt, output, format, compression)

        else:
            if args.merge == False:
                write_snbt(nbt, output, args.indent)
            else:
                old = nbtio.load_snbt(output)
                if old is not None:
                    old.merge(nbt, args.merge_list)
                    write_snbt(old, output, args.indent)
                else:
                    Warn(
                        f"File {Path(output).absolute()} does not exist, skipping merge."
                    )
                    write_snbt(nbt, output, args.indent)

        Info(f"NBT file generated at: {Path(output).absolute()}")


def main():
    args = parse_args()
    fmt = nbtio.detect_file_format(args.file)
    nbt = parse_file(args.file, fmt)
    if nbt is not None:
        process_print_options(args, nbt)
        process_write_options(args, nbt, fmt)
    else:
        Error(f"No file exists to open: {args.file}")
