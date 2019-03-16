/* EVMC: Ethereum Client-VM Connector API.
 * Copyright 2018 The EVMC Authors.
 * Licensed under the Apache License, Version 2.0. See the LICENSE file.
 */

#include <evmc/instructions.h>

static const char* constantinople_names[256] = {
    /* 0x00 */ "STOP",
    /* 0x01 */ "ADD",
    /* 0x02 */ "MUL",
    /* 0x03 */ "SUB",
    /* 0x04 */ "DIV",
    /* 0x05 */ "SDIV",
    /* 0x06 */ "MOD",
    /* 0x07 */ "SMOD",
    /* 0x08 */ "ADDMOD",
    /* 0x09 */ "MULMOD",
    /* 0x0a */ "EXP",
    /* 0x0b */ "SIGNEXTEND",
    /* 0x0c */ "SADD",
    /* 0x0d */ "SSUB",
    /* 0x0e */ "SMUL",
    /* 0x0f */ NULL,
    /* 0x10 */ "LT",
    /* 0x11 */ "GT",
    /* 0x12 */ "SLT",
    /* 0x13 */ "SGT",
    /* 0x14 */ "EQ",
    /* 0x15 */ "ISZERO",
    /* 0x16 */ "AND",
    /* 0x17 */ "OR",
    /* 0x18 */ "XOR",
    /* 0x19 */ "NOT",
    /* 0x1a */ "BYTE",
    /* 0x1b */ "SHL",
    /* 0x1c */ "SHR",
    /* 0x1d */ "SAR",
    /* 0x1e */ NULL,
    /* 0x1f */ NULL,
    /* 0x20 */ "SHA3",
    /* 0x21 */ NULL,
    /* 0x22 */ NULL,
    /* 0x23 */ NULL,
    /* 0x24 */ NULL,
    /* 0x25 */ NULL,
    /* 0x26 */ NULL,
    /* 0x27 */ NULL,
    /* 0x28 */ NULL,
    /* 0x29 */ NULL,
    /* 0x2a */ "FMUL",
    /* 0x2b */ "SFMUL",
    /* 0x2c */ "FDIV",
    /* 0x2d */ "SFDIV",
    /* 0x2e */ NULL,
    /* 0x2f */ NULL,
    /* 0x30 */ "ADDRESS",
    /* 0x31 */ "BALANCE",
    /* 0x32 */ "ORIGIN",
    /* 0x33 */ "CALLER",
    /* 0x34 */ "CALLVALUE",
    /* 0x35 */ "CALLDATALOAD",
    /* 0x36 */ "CALLDATASIZE",
    /* 0x37 */ "CALLDATACOPY",
    /* 0x38 */ "CODESIZE",
    /* 0x39 */ "CODECOPY",
    /* 0x3a */ "GASPRICE",
    /* 0x3b */ "EXTCODESIZE",
    /* 0x3c */ "EXTCODECOPY",
    /* 0x3d */ "RETURNDATASIZE",
    /* 0x3e */ "RETURNDATACOPY",
    /* 0x3f */ "EXTCODEHASH",
    /* 0x40 */ "BLOCKHASH",
    /* 0x41 */ "COINBASE",
    /* 0x42 */ "TIMESTAMP",
    /* 0x43 */ "NUMBER",
    /* 0x44 */ "DIFFICULTY",
    /* 0x45 */ "GASLIMIT",
    /* 0x46 */ NULL,
    /* 0x47 */ NULL,
    /* 0x48 */ NULL,
    /* 0x49 */ NULL,
    /* 0x4a */ NULL,
    /* 0x4b */ NULL,
    /* 0x4c */ NULL,
    /* 0x4d */ NULL,
    /* 0x4e */ NULL,
    /* 0x4f */ NULL,
    /* 0x50 */ "POP",
    /* 0x51 */ "MLOAD",
    /* 0x52 */ "MSTORE",
    /* 0x53 */ "MSTORE8",
    /* 0x54 */ "SLOAD",
    /* 0x55 */ "SSTORE",
    /* 0x56 */ "JUMP",
    /* 0x57 */ "JUMPI",
    /* 0x58 */ "PC",
    /* 0x59 */ "MSIZE",
    /* 0x5a */ "GAS",
    /* 0x5b */ "JUMPDEST",
    /* 0x5c */ NULL,
    /* 0x5d */ NULL,
    /* 0x5e */ NULL,
    /* 0x5f */ NULL,
    /* 0x60 */ "PUSH1",
    /* 0x61 */ "PUSH2",
    /* 0x62 */ "PUSH3",
    /* 0x63 */ "PUSH4",
    /* 0x64 */ "PUSH5",
    /* 0x65 */ "PUSH6",
    /* 0x66 */ "PUSH7",
    /* 0x67 */ "PUSH8",
    /* 0x68 */ "PUSH9",
    /* 0x69 */ "PUSH10",
    /* 0x6a */ "PUSH11",
    /* 0x6b */ "PUSH12",
    /* 0x6c */ "PUSH13",
    /* 0x6d */ "PUSH14",
    /* 0x6e */ "PUSH15",
    /* 0x6f */ "PUSH16",
    /* 0x70 */ "PUSH17",
    /* 0x71 */ "PUSH18",
    /* 0x72 */ "PUSH19",
    /* 0x73 */ "PUSH20",
    /* 0x74 */ "PUSH21",
    /* 0x75 */ "PUSH22",
    /* 0x76 */ "PUSH23",
    /* 0x77 */ "PUSH24",
    /* 0x78 */ "PUSH25",
    /* 0x79 */ "PUSH26",
    /* 0x7a */ "PUSH27",
    /* 0x7b */ "PUSH28",
    /* 0x7c */ "PUSH29",
    /* 0x7d */ "PUSH30",
    /* 0x7e */ "PUSH31",
    /* 0x7f */ "PUSH32",
    /* 0x80 */ "DUP1",
    /* 0x81 */ "DUP2",
    /* 0x82 */ "DUP3",
    /* 0x83 */ "DUP4",
    /* 0x84 */ "DUP5",
    /* 0x85 */ "DUP6",
    /* 0x86 */ "DUP7",
    /* 0x87 */ "DUP8",
    /* 0x88 */ "DUP9",
    /* 0x89 */ "DUP10",
    /* 0x8a */ "DUP11",
    /* 0x8b */ "DUP12",
    /* 0x8c */ "DUP13",
    /* 0x8d */ "DUP14",
    /* 0x8e */ "DUP15",
    /* 0x8f */ "DUP16",
    /* 0x90 */ "SWAP1",
    /* 0x91 */ "SWAP2",
    /* 0x92 */ "SWAP3",
    /* 0x93 */ "SWAP4",
    /* 0x94 */ "SWAP5",
    /* 0x95 */ "SWAP6",
    /* 0x96 */ "SWAP7",
    /* 0x97 */ "SWAP8",
    /* 0x98 */ "SWAP9",
    /* 0x99 */ "SWAP10",
    /* 0x9a */ "SWAP11",
    /* 0x9b */ "SWAP12",
    /* 0x9c */ "SWAP13",
    /* 0x9d */ "SWAP14",
    /* 0x9e */ "SWAP15",
    /* 0x9f */ "SWAP16",
    /* 0xa0 */ "LOG0",
    /* 0xa1 */ "LOG1",
    /* 0xa2 */ "LOG2",
    /* 0xa3 */ "LOG3",
    /* 0xa4 */ "LOG4",
    /* 0xa5 */ NULL,
    /* 0xa6 */ NULL,
    /* 0xa7 */ NULL,
    /* 0xa8 */ NULL,
    /* 0xa9 */ NULL,
    /* 0xaa */ NULL,
    /* 0xab */ NULL,
    /* 0xac */ NULL,
    /* 0xad */ NULL,
    /* 0xae */ NULL,
    /* 0xaf */ NULL,
    /* 0xb0 */ NULL,
    /* 0xb1 */ NULL,
    /* 0xb2 */ NULL,
    /* 0xb3 */ NULL,
    /* 0xb4 */ NULL,
    /* 0xb5 */ NULL,
    /* 0xb6 */ NULL,
    /* 0xb7 */ NULL,
    /* 0xb8 */ NULL,
    /* 0xb9 */ NULL,
    /* 0xba */ NULL,
    /* 0xbb */ NULL,
    /* 0xbc */ NULL,
    /* 0xbd */ NULL,
    /* 0xbe */ NULL,
    /* 0xbf */ NULL,
    /* 0xc0 */ "SADD",
    /* 0xc1 */ "UADD",
    /* 0xc2 */ "SSUB",
    /* 0xc3 */ "USUB",
    /* 0xc4 */ "SMUL",
    /* 0xc5 */ "UMUL",
    /* 0xc6 */ NULL,
    /* 0xc7 */ NULL,
    /* 0xc8 */ NULL,
    /* 0xc9 */ NULL,
    /* 0xca */ NULL,
    /* 0xcb */ NULL,
    /* 0xcc */ NULL,
    /* 0xcd */ NULL,
    /* 0xce */ NULL,
    /* 0xcf */ NULL,
    /* 0xd0 */ NULL,
    /* 0xd1 */ NULL,
    /* 0xd2 */ NULL,
    /* 0xd3 */ NULL,
    /* 0xd4 */ NULL,
    /* 0xd5 */ NULL,
    /* 0xd6 */ NULL,
    /* 0xd7 */ NULL,
    /* 0xd8 */ NULL,
    /* 0xd9 */ NULL,
    /* 0xda */ NULL,
    /* 0xdb */ NULL,
    /* 0xdc */ NULL,
    /* 0xdd */ NULL,
    /* 0xde */ NULL,
    /* 0xdf */ NULL,
    /* 0xe0 */ NULL,
    /* 0xe1 */ NULL,
    /* 0xe2 */ NULL,
    /* 0xe3 */ NULL,
    /* 0xe4 */ NULL,
    /* 0xe5 */ NULL,
    /* 0xe6 */ NULL,
    /* 0xe7 */ NULL,
    /* 0xe8 */ NULL,
    /* 0xe9 */ NULL,
    /* 0xea */ NULL,
    /* 0xeb */ NULL,
    /* 0xec */ NULL,
    /* 0xed */ NULL,
    /* 0xee */ NULL,
    /* 0xef */ NULL,
    /* 0xf0 */ "CREATE",
    /* 0xf1 */ "CALL",
    /* 0xf2 */ "CALLCODE",
    /* 0xf3 */ "RETURN",
    /* 0xf4 */ "DELEGATECALL",
    /* 0xf5 */ "ENI",
    /* 0xf6 */ NULL,
    /* 0xf7 */ NULL,
    /* 0xf8 */ NULL,
    /* 0xf9 */ NULL,
    /* 0xfa */ "STATICCALL",
    /* 0xfb */ NULL,
    /* 0xfc */ NULL,
    /* 0xfd */ "REVERT",
    /* 0xfe */ "INVALID",
    /* 0xff */ "SELFDESTRUCT",
};

static const char* byzantium_names[256] = {
    /* 0x00 */ "STOP",
    /* 0x01 */ "ADD",
    /* 0x02 */ "MUL",
    /* 0x03 */ "SUB",
    /* 0x04 */ "DIV",
    /* 0x05 */ "SDIV",
    /* 0x06 */ "MOD",
    /* 0x07 */ "SMOD",
    /* 0x08 */ "ADDMOD",
    /* 0x09 */ "MULMOD",
    /* 0x0a */ "EXP",
    /* 0x0b */ "SIGNEXTEND",
    /* 0x0c */ "SADD",
    /* 0x0d */ "SSUB",
    /* 0x0e */ "SMUL",
    /* 0x0f */ NULL,
    /* 0x10 */ "LT",
    /* 0x11 */ "GT",
    /* 0x12 */ "SLT",
    /* 0x13 */ "SGT",
    /* 0x14 */ "EQ",
    /* 0x15 */ "ISZERO",
    /* 0x16 */ "AND",
    /* 0x17 */ "OR",
    /* 0x18 */ "XOR",
    /* 0x19 */ "NOT",
    /* 0x1a */ "BYTE",
    /* 0x1b */ NULL,
    /* 0x1c */ NULL,
    /* 0x1d */ NULL,
    /* 0x1e */ NULL,
    /* 0x1f */ NULL,
    /* 0x20 */ "SHA3",
    /* 0x21 */ NULL,
    /* 0x22 */ NULL,
    /* 0x23 */ NULL,
    /* 0x24 */ NULL,
    /* 0x25 */ NULL,
    /* 0x26 */ NULL,
    /* 0x27 */ NULL,
    /* 0x28 */ NULL,
    /* 0x29 */ NULL,
    /* 0x2a */ NULL,
    /* 0x2b */ NULL,
    /* 0x2c */ NULL,
    /* 0x2d */ NULL,
    /* 0x2e */ NULL,
    /* 0x2f */ NULL,
    /* 0x30 */ "ADDRESS",
    /* 0x31 */ "BALANCE",
    /* 0x32 */ "ORIGIN",
    /* 0x33 */ "CALLER",
    /* 0x34 */ "CALLVALUE",
    /* 0x35 */ "CALLDATALOAD",
    /* 0x36 */ "CALLDATASIZE",
    /* 0x37 */ "CALLDATACOPY",
    /* 0x38 */ "CODESIZE",
    /* 0x39 */ "CODECOPY",
    /* 0x3a */ "GASPRICE",
    /* 0x3b */ "EXTCODESIZE",
    /* 0x3c */ "EXTCODECOPY",
    /* 0x3d */ "RETURNDATASIZE",
    /* 0x3e */ "RETURNDATACOPY",
    /* 0x3f */ NULL,
    /* 0x40 */ "BLOCKHASH",
    /* 0x41 */ "COINBASE",
    /* 0x42 */ "TIMESTAMP",
    /* 0x43 */ "NUMBER",
    /* 0x44 */ "DIFFICULTY",
    /* 0x45 */ "GASLIMIT",
    /* 0x46 */ NULL,
    /* 0x47 */ NULL,
    /* 0x48 */ NULL,
    /* 0x49 */ NULL,
    /* 0x4a */ NULL,
    /* 0x4b */ NULL,
    /* 0x4c */ NULL,
    /* 0x4d */ NULL,
    /* 0x4e */ NULL,
    /* 0x4f */ NULL,
    /* 0x50 */ "POP",
    /* 0x51 */ "MLOAD",
    /* 0x52 */ "MSTORE",
    /* 0x53 */ "MSTORE8",
    /* 0x54 */ "SLOAD",
    /* 0x55 */ "SSTORE",
    /* 0x56 */ "JUMP",
    /* 0x57 */ "JUMPI",
    /* 0x58 */ "PC",
    /* 0x59 */ "MSIZE",
    /* 0x5a */ "GAS",
    /* 0x5b */ "JUMPDEST",
    /* 0x5c */ NULL,
    /* 0x5d */ NULL,
    /* 0x5e */ NULL,
    /* 0x5f */ NULL,
    /* 0x60 */ "PUSH1",
    /* 0x61 */ "PUSH2",
    /* 0x62 */ "PUSH3",
    /* 0x63 */ "PUSH4",
    /* 0x64 */ "PUSH5",
    /* 0x65 */ "PUSH6",
    /* 0x66 */ "PUSH7",
    /* 0x67 */ "PUSH8",
    /* 0x68 */ "PUSH9",
    /* 0x69 */ "PUSH10",
    /* 0x6a */ "PUSH11",
    /* 0x6b */ "PUSH12",
    /* 0x6c */ "PUSH13",
    /* 0x6d */ "PUSH14",
    /* 0x6e */ "PUSH15",
    /* 0x6f */ "PUSH16",
    /* 0x70 */ "PUSH17",
    /* 0x71 */ "PUSH18",
    /* 0x72 */ "PUSH19",
    /* 0x73 */ "PUSH20",
    /* 0x74 */ "PUSH21",
    /* 0x75 */ "PUSH22",
    /* 0x76 */ "PUSH23",
    /* 0x77 */ "PUSH24",
    /* 0x78 */ "PUSH25",
    /* 0x79 */ "PUSH26",
    /* 0x7a */ "PUSH27",
    /* 0x7b */ "PUSH28",
    /* 0x7c */ "PUSH29",
    /* 0x7d */ "PUSH30",
    /* 0x7e */ "PUSH31",
    /* 0x7f */ "PUSH32",
    /* 0x80 */ "DUP1",
    /* 0x81 */ "DUP2",
    /* 0x82 */ "DUP3",
    /* 0x83 */ "DUP4",
    /* 0x84 */ "DUP5",
    /* 0x85 */ "DUP6",
    /* 0x86 */ "DUP7",
    /* 0x87 */ "DUP8",
    /* 0x88 */ "DUP9",
    /* 0x89 */ "DUP10",
    /* 0x8a */ "DUP11",
    /* 0x8b */ "DUP12",
    /* 0x8c */ "DUP13",
    /* 0x8d */ "DUP14",
    /* 0x8e */ "DUP15",
    /* 0x8f */ "DUP16",
    /* 0x90 */ "SWAP1",
    /* 0x91 */ "SWAP2",
    /* 0x92 */ "SWAP3",
    /* 0x93 */ "SWAP4",
    /* 0x94 */ "SWAP5",
    /* 0x95 */ "SWAP6",
    /* 0x96 */ "SWAP7",
    /* 0x97 */ "SWAP8",
    /* 0x98 */ "SWAP9",
    /* 0x99 */ "SWAP10",
    /* 0x9a */ "SWAP11",
    /* 0x9b */ "SWAP12",
    /* 0x9c */ "SWAP13",
    /* 0x9d */ "SWAP14",
    /* 0x9e */ "SWAP15",
    /* 0x9f */ "SWAP16",
    /* 0xa0 */ "LOG0",
    /* 0xa1 */ "LOG1",
    /* 0xa2 */ "LOG2",
    /* 0xa3 */ "LOG3",
    /* 0xa4 */ "LOG4",
    /* 0xa5 */ NULL,
    /* 0xa6 */ NULL,
    /* 0xa7 */ NULL,
    /* 0xa8 */ NULL,
    /* 0xa9 */ NULL,
    /* 0xaa */ NULL,
    /* 0xab */ NULL,
    /* 0xac */ NULL,
    /* 0xad */ NULL,
    /* 0xae */ NULL,
    /* 0xaf */ NULL,
    /* 0xb0 */ NULL,
    /* 0xb1 */ NULL,
    /* 0xb2 */ NULL,
    /* 0xb3 */ NULL,
    /* 0xb4 */ NULL,
    /* 0xb5 */ NULL,
    /* 0xb6 */ NULL,
    /* 0xb7 */ NULL,
    /* 0xb8 */ NULL,
    /* 0xb9 */ NULL,
    /* 0xba */ NULL,
    /* 0xbb */ NULL,
    /* 0xbc */ NULL,
    /* 0xbd */ NULL,
    /* 0xbe */ NULL,
    /* 0xbf */ NULL,
    /* 0xc0 */ "SADD",
    /* 0xc1 */ "UADD",
    /* 0xc2 */ "SSUB",
    /* 0xc3 */ "USUB",
    /* 0xc4 */ "SMUL",
    /* 0xc5 */ "UMUL",
    /* 0xc6 */ NULL,
    /* 0xc7 */ NULL,
    /* 0xc8 */ NULL,
    /* 0xc9 */ NULL,
    /* 0xca */ NULL,
    /* 0xcb */ NULL,
    /* 0xcc */ NULL,
    /* 0xcd */ NULL,
    /* 0xce */ NULL,
    /* 0xcf */ NULL,
    /* 0xd0 */ NULL,
    /* 0xd1 */ NULL,
    /* 0xd2 */ NULL,
    /* 0xd3 */ NULL,
    /* 0xd4 */ NULL,
    /* 0xd5 */ NULL,
    /* 0xd6 */ NULL,
    /* 0xd7 */ NULL,
    /* 0xd8 */ NULL,
    /* 0xd9 */ NULL,
    /* 0xda */ NULL,
    /* 0xdb */ NULL,
    /* 0xdc */ NULL,
    /* 0xdd */ NULL,
    /* 0xde */ NULL,
    /* 0xdf */ NULL,
    /* 0xe0 */ NULL,
    /* 0xe1 */ NULL,
    /* 0xe2 */ NULL,
    /* 0xe3 */ NULL,
    /* 0xe4 */ NULL,
    /* 0xe5 */ NULL,
    /* 0xe6 */ NULL,
    /* 0xe7 */ NULL,
    /* 0xe8 */ NULL,
    /* 0xe9 */ NULL,
    /* 0xea */ NULL,
    /* 0xeb */ NULL,
    /* 0xec */ NULL,
    /* 0xed */ NULL,
    /* 0xee */ NULL,
    /* 0xef */ NULL,
    /* 0xf0 */ "CREATE",
    /* 0xf1 */ "CALL",
    /* 0xf2 */ "CALLCODE",
    /* 0xf3 */ "RETURN",
    /* 0xf4 */ "DELEGATECALL",
    /* 0xf5 */ "ENI",
    /* 0xf6 */ NULL,
    /* 0xf7 */ NULL,
    /* 0xf8 */ NULL,
    /* 0xf9 */ NULL,
    /* 0xfa */ "STATICCALL",
    /* 0xfb */ NULL,
    /* 0xfc */ NULL,
    /* 0xfd */ "REVERT",
    /* 0xfe */ "INVALID",
    /* 0xff */ "SELFDESTRUCT",
};

static const char* homestead_names[256] = {
    /* 0x00 */ "STOP",
    /* 0x01 */ "ADD",
    /* 0x02 */ "MUL",
    /* 0x03 */ "SUB",
    /* 0x04 */ "DIV",
    /* 0x05 */ "SDIV",
    /* 0x06 */ "MOD",
    /* 0x07 */ "SMOD",
    /* 0x08 */ "ADDMOD",
    /* 0x09 */ "MULMOD",
    /* 0x0a */ "EXP",
    /* 0x0b */ "SIGNEXTEND",
    /* 0x0c */ "SADD",
    /* 0x0d */ "SSUB",
    /* 0x0e */ "SMUL",
    /* 0x0f */ NULL,
    /* 0x10 */ "LT",
    /* 0x11 */ "GT",
    /* 0x12 */ "SLT",
    /* 0x13 */ "SGT",
    /* 0x14 */ "EQ",
    /* 0x15 */ "ISZERO",
    /* 0x16 */ "AND",
    /* 0x17 */ "OR",
    /* 0x18 */ "XOR",
    /* 0x19 */ "NOT",
    /* 0x1a */ "BYTE",
    /* 0x1b */ NULL,
    /* 0x1c */ NULL,
    /* 0x1d */ NULL,
    /* 0x1e */ NULL,
    /* 0x1f */ NULL,
    /* 0x20 */ "SHA3",
    /* 0x21 */ NULL,
    /* 0x22 */ NULL,
    /* 0x23 */ NULL,
    /* 0x24 */ NULL,
    /* 0x25 */ NULL,
    /* 0x26 */ NULL,
    /* 0x27 */ NULL,
    /* 0x28 */ NULL,
    /* 0x29 */ NULL,
    /* 0x2a */ NULL,
    /* 0x2b */ NULL,
    /* 0x2c */ NULL,
    /* 0x2d */ NULL,
    /* 0x2e */ NULL,
    /* 0x2f */ NULL,
    /* 0x30 */ "ADDRESS",
    /* 0x31 */ "BALANCE",
    /* 0x32 */ "ORIGIN",
    /* 0x33 */ "CALLER",
    /* 0x34 */ "CALLVALUE",
    /* 0x35 */ "CALLDATALOAD",
    /* 0x36 */ "CALLDATASIZE",
    /* 0x37 */ "CALLDATACOPY",
    /* 0x38 */ "CODESIZE",
    /* 0x39 */ "CODECOPY",
    /* 0x3a */ "GASPRICE",
    /* 0x3b */ "EXTCODESIZE",
    /* 0x3c */ "EXTCODECOPY",
    /* 0x3d */ NULL,
    /* 0x3e */ NULL,
    /* 0x3f */ NULL,
    /* 0x40 */ "BLOCKHASH",
    /* 0x41 */ "COINBASE",
    /* 0x42 */ "TIMESTAMP",
    /* 0x43 */ "NUMBER",
    /* 0x44 */ "DIFFICULTY",
    /* 0x45 */ "GASLIMIT",
    /* 0x46 */ NULL,
    /* 0x47 */ NULL,
    /* 0x48 */ NULL,
    /* 0x49 */ NULL,
    /* 0x4a */ NULL,
    /* 0x4b */ NULL,
    /* 0x4c */ NULL,
    /* 0x4d */ NULL,
    /* 0x4e */ NULL,
    /* 0x4f */ NULL,
    /* 0x50 */ "POP",
    /* 0x51 */ "MLOAD",
    /* 0x52 */ "MSTORE",
    /* 0x53 */ "MSTORE8",
    /* 0x54 */ "SLOAD",
    /* 0x55 */ "SSTORE",
    /* 0x56 */ "JUMP",
    /* 0x57 */ "JUMPI",
    /* 0x58 */ "PC",
    /* 0x59 */ "MSIZE",
    /* 0x5a */ "GAS",
    /* 0x5b */ "JUMPDEST",
    /* 0x5c */ NULL,
    /* 0x5d */ NULL,
    /* 0x5e */ NULL,
    /* 0x5f */ NULL,
    /* 0x60 */ "PUSH1",
    /* 0x61 */ "PUSH2",
    /* 0x62 */ "PUSH3",
    /* 0x63 */ "PUSH4",
    /* 0x64 */ "PUSH5",
    /* 0x65 */ "PUSH6",
    /* 0x66 */ "PUSH7",
    /* 0x67 */ "PUSH8",
    /* 0x68 */ "PUSH9",
    /* 0x69 */ "PUSH10",
    /* 0x6a */ "PUSH11",
    /* 0x6b */ "PUSH12",
    /* 0x6c */ "PUSH13",
    /* 0x6d */ "PUSH14",
    /* 0x6e */ "PUSH15",
    /* 0x6f */ "PUSH16",
    /* 0x70 */ "PUSH17",
    /* 0x71 */ "PUSH18",
    /* 0x72 */ "PUSH19",
    /* 0x73 */ "PUSH20",
    /* 0x74 */ "PUSH21",
    /* 0x75 */ "PUSH22",
    /* 0x76 */ "PUSH23",
    /* 0x77 */ "PUSH24",
    /* 0x78 */ "PUSH25",
    /* 0x79 */ "PUSH26",
    /* 0x7a */ "PUSH27",
    /* 0x7b */ "PUSH28",
    /* 0x7c */ "PUSH29",
    /* 0x7d */ "PUSH30",
    /* 0x7e */ "PUSH31",
    /* 0x7f */ "PUSH32",
    /* 0x80 */ "DUP1",
    /* 0x81 */ "DUP2",
    /* 0x82 */ "DUP3",
    /* 0x83 */ "DUP4",
    /* 0x84 */ "DUP5",
    /* 0x85 */ "DUP6",
    /* 0x86 */ "DUP7",
    /* 0x87 */ "DUP8",
    /* 0x88 */ "DUP9",
    /* 0x89 */ "DUP10",
    /* 0x8a */ "DUP11",
    /* 0x8b */ "DUP12",
    /* 0x8c */ "DUP13",
    /* 0x8d */ "DUP14",
    /* 0x8e */ "DUP15",
    /* 0x8f */ "DUP16",
    /* 0x90 */ "SWAP1",
    /* 0x91 */ "SWAP2",
    /* 0x92 */ "SWAP3",
    /* 0x93 */ "SWAP4",
    /* 0x94 */ "SWAP5",
    /* 0x95 */ "SWAP6",
    /* 0x96 */ "SWAP7",
    /* 0x97 */ "SWAP8",
    /* 0x98 */ "SWAP9",
    /* 0x99 */ "SWAP10",
    /* 0x9a */ "SWAP11",
    /* 0x9b */ "SWAP12",
    /* 0x9c */ "SWAP13",
    /* 0x9d */ "SWAP14",
    /* 0x9e */ "SWAP15",
    /* 0x9f */ "SWAP16",
    /* 0xa0 */ "LOG0",
    /* 0xa1 */ "LOG1",
    /* 0xa2 */ "LOG2",
    /* 0xa3 */ "LOG3",
    /* 0xa4 */ "LOG4",
    /* 0xa5 */ NULL,
    /* 0xa6 */ NULL,
    /* 0xa7 */ NULL,
    /* 0xa8 */ NULL,
    /* 0xa9 */ NULL,
    /* 0xaa */ NULL,
    /* 0xab */ NULL,
    /* 0xac */ NULL,
    /* 0xad */ NULL,
    /* 0xae */ NULL,
    /* 0xaf */ NULL,
    /* 0xb0 */ NULL,
    /* 0xb1 */ NULL,
    /* 0xb2 */ NULL,
    /* 0xb3 */ NULL,
    /* 0xb4 */ NULL,
    /* 0xb5 */ NULL,
    /* 0xb6 */ NULL,
    /* 0xb7 */ NULL,
    /* 0xb8 */ NULL,
    /* 0xb9 */ NULL,
    /* 0xba */ NULL,
    /* 0xbb */ NULL,
    /* 0xbc */ NULL,
    /* 0xbd */ NULL,
    /* 0xbe */ NULL,
    /* 0xbf */ NULL,
    /* 0xc0 */ "SADD",
    /* 0xc1 */ "UADD",
    /* 0xc2 */ "SSUB",
    /* 0xc3 */ "USUB",
    /* 0xc4 */ "SMUL",
    /* 0xc5 */ "UMUL",
    /* 0xc6 */ NULL,
    /* 0xc7 */ NULL,
    /* 0xc8 */ NULL,
    /* 0xc9 */ NULL,
    /* 0xca */ NULL,
    /* 0xcb */ NULL,
    /* 0xcc */ NULL,
    /* 0xcd */ NULL,
    /* 0xce */ NULL,
    /* 0xcf */ NULL,
    /* 0xd0 */ NULL,
    /* 0xd1 */ NULL,
    /* 0xd2 */ NULL,
    /* 0xd3 */ NULL,
    /* 0xd4 */ NULL,
    /* 0xd5 */ NULL,
    /* 0xd6 */ NULL,
    /* 0xd7 */ NULL,
    /* 0xd8 */ NULL,
    /* 0xd9 */ NULL,
    /* 0xda */ NULL,
    /* 0xdb */ NULL,
    /* 0xdc */ NULL,
    /* 0xdd */ NULL,
    /* 0xde */ NULL,
    /* 0xdf */ NULL,
    /* 0xe0 */ NULL,
    /* 0xe1 */ NULL,
    /* 0xe2 */ NULL,
    /* 0xe3 */ NULL,
    /* 0xe4 */ NULL,
    /* 0xe5 */ NULL,
    /* 0xe6 */ NULL,
    /* 0xe7 */ NULL,
    /* 0xe8 */ NULL,
    /* 0xe9 */ NULL,
    /* 0xea */ NULL,
    /* 0xeb */ NULL,
    /* 0xec */ NULL,
    /* 0xed */ NULL,
    /* 0xee */ NULL,
    /* 0xef */ NULL,
    /* 0xf0 */ "CREATE",
    /* 0xf1 */ "CALL",
    /* 0xf2 */ "CALLCODE",
    /* 0xf3 */ "RETURN",
    /* 0xf4 */ "DELEGATECALL",
    /* 0xf5 */ "ENI",
    /* 0xf6 */ NULL,
    /* 0xf7 */ NULL,
    /* 0xf8 */ NULL,
    /* 0xf9 */ NULL,
    /* 0xfa */ NULL,
    /* 0xfb */ NULL,
    /* 0xfc */ NULL,
    /* 0xfd */ NULL,
    /* 0xfe */ "INVALID",
    /* 0xff */ "SELFDESTRUCT",
};

static const char* frontier_names[256] = {
    /* 0x00 */ "STOP",
    /* 0x01 */ "ADD",
    /* 0x02 */ "MUL",
    /* 0x03 */ "SUB",
    /* 0x04 */ "DIV",
    /* 0x05 */ "SDIV",
    /* 0x06 */ "MOD",
    /* 0x07 */ "SMOD",
    /* 0x08 */ "ADDMOD",
    /* 0x09 */ "MULMOD",
    /* 0x0a */ "EXP",
    /* 0x0b */ "SIGNEXTEND",
    /* 0x0c */ NULL,
    /* 0x0d */ NULL,
    /* 0x0e */ NULL,
    /* 0x0f */ NULL,
    /* 0x10 */ "LT",
    /* 0x11 */ "GT",
    /* 0x12 */ "SLT",
    /* 0x13 */ "SGT",
    /* 0x14 */ "EQ",
    /* 0x15 */ "ISZERO",
    /* 0x16 */ "AND",
    /* 0x17 */ "OR",
    /* 0x18 */ "XOR",
    /* 0x19 */ "NOT",
    /* 0x1a */ "BYTE",
    /* 0x1b */ NULL,
    /* 0x1c */ NULL,
    /* 0x1d */ NULL,
    /* 0x1e */ NULL,
    /* 0x1f */ NULL,
    /* 0x20 */ "SHA3",
    /* 0x21 */ NULL,
    /* 0x22 */ NULL,
    /* 0x23 */ NULL,
    /* 0x24 */ NULL,
    /* 0x25 */ NULL,
    /* 0x26 */ NULL,
    /* 0x27 */ NULL,
    /* 0x28 */ NULL,
    /* 0x29 */ NULL,
    /* 0x2a */ NULL,
    /* 0x2b */ NULL,
    /* 0x2c */ NULL,
    /* 0x2d */ NULL,
    /* 0x2e */ NULL,
    /* 0x2f */ NULL,
    /* 0x30 */ "ADDRESS",
    /* 0x31 */ "BALANCE",
    /* 0x32 */ "ORIGIN",
    /* 0x33 */ "CALLER",
    /* 0x34 */ "CALLVALUE",
    /* 0x35 */ "CALLDATALOAD",
    /* 0x36 */ "CALLDATASIZE",
    /* 0x37 */ "CALLDATACOPY",
    /* 0x38 */ "CODESIZE",
    /* 0x39 */ "CODECOPY",
    /* 0x3a */ "GASPRICE",
    /* 0x3b */ "EXTCODESIZE",
    /* 0x3c */ "EXTCODECOPY",
    /* 0x3d */ NULL,
    /* 0x3e */ NULL,
    /* 0x3f */ NULL,
    /* 0x40 */ "BLOCKHASH",
    /* 0x41 */ "COINBASE",
    /* 0x42 */ "TIMESTAMP",
    /* 0x43 */ "NUMBER",
    /* 0x44 */ "DIFFICULTY",
    /* 0x45 */ "GASLIMIT",
    /* 0x46 */ NULL,
    /* 0x47 */ NULL,
    /* 0x48 */ NULL,
    /* 0x49 */ NULL,
    /* 0x4a */ NULL,
    /* 0x4b */ NULL,
    /* 0x4c */ NULL,
    /* 0x4d */ NULL,
    /* 0x4e */ NULL,
    /* 0x4f */ NULL,
    /* 0x50 */ "POP",
    /* 0x51 */ "MLOAD",
    /* 0x52 */ "MSTORE",
    /* 0x53 */ "MSTORE8",
    /* 0x54 */ "SLOAD",
    /* 0x55 */ "SSTORE",
    /* 0x56 */ "JUMP",
    /* 0x57 */ "JUMPI",
    /* 0x58 */ "PC",
    /* 0x59 */ "MSIZE",
    /* 0x5a */ "GAS",
    /* 0x5b */ "JUMPDEST",
    /* 0x5c */ NULL,
    /* 0x5d */ NULL,
    /* 0x5e */ NULL,
    /* 0x5f */ NULL,
    /* 0x60 */ "PUSH1",
    /* 0x61 */ "PUSH2",
    /* 0x62 */ "PUSH3",
    /* 0x63 */ "PUSH4",
    /* 0x64 */ "PUSH5",
    /* 0x65 */ "PUSH6",
    /* 0x66 */ "PUSH7",
    /* 0x67 */ "PUSH8",
    /* 0x68 */ "PUSH9",
    /* 0x69 */ "PUSH10",
    /* 0x6a */ "PUSH11",
    /* 0x6b */ "PUSH12",
    /* 0x6c */ "PUSH13",
    /* 0x6d */ "PUSH14",
    /* 0x6e */ "PUSH15",
    /* 0x6f */ "PUSH16",
    /* 0x70 */ "PUSH17",
    /* 0x71 */ "PUSH18",
    /* 0x72 */ "PUSH19",
    /* 0x73 */ "PUSH20",
    /* 0x74 */ "PUSH21",
    /* 0x75 */ "PUSH22",
    /* 0x76 */ "PUSH23",
    /* 0x77 */ "PUSH24",
    /* 0x78 */ "PUSH25",
    /* 0x79 */ "PUSH26",
    /* 0x7a */ "PUSH27",
    /* 0x7b */ "PUSH28",
    /* 0x7c */ "PUSH29",
    /* 0x7d */ "PUSH30",
    /* 0x7e */ "PUSH31",
    /* 0x7f */ "PUSH32",
    /* 0x80 */ "DUP1",
    /* 0x81 */ "DUP2",
    /* 0x82 */ "DUP3",
    /* 0x83 */ "DUP4",
    /* 0x84 */ "DUP5",
    /* 0x85 */ "DUP6",
    /* 0x86 */ "DUP7",
    /* 0x87 */ "DUP8",
    /* 0x88 */ "DUP9",
    /* 0x89 */ "DUP10",
    /* 0x8a */ "DUP11",
    /* 0x8b */ "DUP12",
    /* 0x8c */ "DUP13",
    /* 0x8d */ "DUP14",
    /* 0x8e */ "DUP15",
    /* 0x8f */ "DUP16",
    /* 0x90 */ "SWAP1",
    /* 0x91 */ "SWAP2",
    /* 0x92 */ "SWAP3",
    /* 0x93 */ "SWAP4",
    /* 0x94 */ "SWAP5",
    /* 0x95 */ "SWAP6",
    /* 0x96 */ "SWAP7",
    /* 0x97 */ "SWAP8",
    /* 0x98 */ "SWAP9",
    /* 0x99 */ "SWAP10",
    /* 0x9a */ "SWAP11",
    /* 0x9b */ "SWAP12",
    /* 0x9c */ "SWAP13",
    /* 0x9d */ "SWAP14",
    /* 0x9e */ "SWAP15",
    /* 0x9f */ "SWAP16",
    /* 0xa0 */ "LOG0",
    /* 0xa1 */ "LOG1",
    /* 0xa2 */ "LOG2",
    /* 0xa3 */ "LOG3",
    /* 0xa4 */ "LOG4",
    /* 0xa5 */ NULL,
    /* 0xa6 */ NULL,
    /* 0xa7 */ NULL,
    /* 0xa8 */ NULL,
    /* 0xa9 */ NULL,
    /* 0xaa */ NULL,
    /* 0xab */ NULL,
    /* 0xac */ NULL,
    /* 0xad */ NULL,
    /* 0xae */ NULL,
    /* 0xaf */ NULL,
    /* 0xb0 */ NULL,
    /* 0xb1 */ NULL,
    /* 0xb2 */ NULL,
    /* 0xb3 */ NULL,
    /* 0xb4 */ NULL,
    /* 0xb5 */ NULL,
    /* 0xb6 */ NULL,
    /* 0xb7 */ NULL,
    /* 0xb8 */ NULL,
    /* 0xb9 */ NULL,
    /* 0xba */ NULL,
    /* 0xbb */ NULL,
    /* 0xbc */ NULL,
    /* 0xbd */ NULL,
    /* 0xbe */ NULL,
    /* 0xbf */ NULL,
    /* 0xc0 */ "SADD",
    /* 0xc1 */ "UADD",
    /* 0xc2 */ "SSUB",
    /* 0xc3 */ "USUB",
    /* 0xc4 */ "SMUL",
    /* 0xc5 */ "UMUL",
    /* 0xc6 */ NULL,
    /* 0xc7 */ NULL,
    /* 0xc8 */ NULL,
    /* 0xc9 */ NULL,
    /* 0xca */ NULL,
    /* 0xcb */ NULL,
    /* 0xcc */ NULL,
    /* 0xcd */ NULL,
    /* 0xce */ NULL,
    /* 0xcf */ NULL,
    /* 0xd0 */ NULL,
    /* 0xd1 */ NULL,
    /* 0xd2 */ NULL,
    /* 0xd3 */ NULL,
    /* 0xd4 */ NULL,
    /* 0xd5 */ NULL,
    /* 0xd6 */ NULL,
    /* 0xd7 */ NULL,
    /* 0xd8 */ NULL,
    /* 0xd9 */ NULL,
    /* 0xda */ NULL,
    /* 0xdb */ NULL,
    /* 0xdc */ NULL,
    /* 0xdd */ NULL,
    /* 0xde */ NULL,
    /* 0xdf */ NULL,
    /* 0xe0 */ NULL,
    /* 0xe1 */ NULL,
    /* 0xe2 */ NULL,
    /* 0xe3 */ NULL,
    /* 0xe4 */ NULL,
    /* 0xe5 */ NULL,
    /* 0xe6 */ NULL,
    /* 0xe7 */ NULL,
    /* 0xe8 */ NULL,
    /* 0xe9 */ NULL,
    /* 0xea */ NULL,
    /* 0xeb */ NULL,
    /* 0xec */ NULL,
    /* 0xed */ NULL,
    /* 0xee */ NULL,
    /* 0xef */ NULL,
    /* 0xf0 */ "CREATE",
    /* 0xf1 */ "CALL",
    /* 0xf2 */ "CALLCODE",
    /* 0xf3 */ "RETURN",
    /* 0xf4 */ NULL,
    /* 0xf5 */ "ENI",
    /* 0xf6 */ NULL,
    /* 0xf7 */ NULL,
    /* 0xf8 */ NULL,
    /* 0xf9 */ NULL,
    /* 0xfa */ NULL,
    /* 0xfb */ NULL,
    /* 0xfc */ NULL,
    /* 0xfd */ NULL,
    /* 0xfe */ "INVALID",
    /* 0xff */ "SELFDESTRUCT",
};

const char* const* evmc_get_instruction_names_table(enum evmc_revision revision)
{
    switch (revision)
    {
    case EVMC_CONSTANTINOPLE:
        return constantinople_names;
    case EVMC_BYZANTIUM:
        return byzantium_names;
    case EVMC_SPURIOUS_DRAGON:
    case EVMC_TANGERINE_WHISTLE:
    case EVMC_HOMESTEAD:
        return homestead_names;
    case EVMC_FRONTIER:
        return frontier_names;
    }
    return NULL;
}
