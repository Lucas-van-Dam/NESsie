#include "cpu.h"
#include <iostream>
#include <bit>

namespace NESsie {
    CPU::CPU() {
    }

    void CPU::initialize() {
        A = 0;
        X = 0;
        Y = 0;
        PC = 0xFFFC;
        S = 0xFD;
        PS.C = 0;
        PS.Z = 0;
        PS.I = 1;
        PS.D = 0;
        PS.V = 0;
        PS.N = 0;
        PS.pad_ = 0;
    }

    void CPU::initialize(NESsie::MainBus &mainbus, const std::vector<BYTE> &initialMainBus) {
        A = 0;
        X = 0;
        Y = 0;
        PC = 0xFFFC;
        S = 0xFD;
        PS.C = 0;
        PS.Z = 0;
        PS.I = 1;
        PS.D = 0;
        PS.V = 0;
        PS.N = 0;
        PS.pad_ = 0;

        mainbus.initialize(initialMainBus);
    }

    uint32_t CPU::executeCycles(uint32_t cycles, NESsie::MainBus &mainbus) {
        uint32_t cyclesRan = 0;
        while (cycles > 0) {
            BYTE instruction = fetch_byte(mainbus);
            uint32_t executed = executeInstruction(instruction, mainbus);
            if (executed > cycles) {
                std::cerr << "executed more cycles than requested, executed: " << executed << ", left:" << cycles <<
                        std::endl;
                cycles = 0;
            } else {
                cycles -= executed;
            }

            cyclesRan += executed;
        }

        return cyclesRan;
    }

    uint32_t CPU::executeInstruction(BYTE instruction, NESsie::MainBus &mainbus) {
        static bool setInteruptFlagAtNextInstruction = false;
        static bool clearInteruptFlagAtNextInstruction = false;

        if (setInteruptFlagAtNextInstruction) {
            PS.I = 1;
            setInteruptFlagAtNextInstruction = false;
        }
        if (clearInteruptFlagAtNextInstruction) {
            PS.I = 0;
            clearInteruptFlagAtNextInstruction = false;
        }

        switch (instruction) {
            case LDAIM: {
                BYTE constant = fetch_byte(mainbus);
                A = constant;

                if (A == 0x00)
                    PS.Z = 1;
                else
                    PS.Z = 0;
                if (A & 0x80)
                    PS.N = 1;
                else
                    PS.N = 0;

                return 2;
            }
            case LDAZP: {
                BYTE address = fetch_byte(mainbus);
                A = mainbus.read_byte(address);

                if (A == 0x00)
                    PS.Z = 1;
                else
                    PS.Z = 0;
                if (A & 0x80)
                    PS.N = 1;
                else
                    PS.N = 0;

                return 3;
            }
            case LDAZPX: {
                BYTE address = fetch_byte(mainbus);
                address += X;
                BYTE value = mainbus.read_byte(address);
                A = value;

                if (A == 0x00)
                    PS.Z = 1;
                else
                    PS.Z = 0;
                if (A & 0x80)
                    PS.N = 1;
                else
                    PS.N = 0;

                return 4;
            }
            case LDAABS: {
                WORD address = fetch_word(mainbus);
                A = mainbus.read_byte(address);

                if (A == 0x00)
                    PS.Z = 1;
                else
                    PS.Z = 0;
                if (A & 0x80)
                    PS.N = 1;
                else
                    PS.N = 0;

                return 4;
            }
            case LDAABSX: {
                bool crossedPageBoundary = false;
                WORD address = fetch_word(mainbus);
                if ((BYTE) address + X > 0xFF)
                    crossedPageBoundary = true;
                A = mainbus.read_byte(address + X);

                if (A == 0x00)
                    PS.Z = 1;
                else
                    PS.Z = 0;
                if (A & 0x80)
                    PS.N = 1;
                else
                    PS.N = 0;

                return crossedPageBoundary ? 5 : 4;
            }
            case LDAABSY: {
                bool crossedPageBoundary = false;
                WORD address = fetch_word(mainbus);
                if ((BYTE) address + Y > 0xFF)
                    crossedPageBoundary = true;
                A = mainbus.read_byte(address + Y);

                if (A == 0x00)
                    PS.Z = 1;
                else
                    PS.Z = 0;
                if (A & 0x80)
                    PS.N = 1;
                else
                    PS.N = 0;

                return crossedPageBoundary ? 5 : 4;
            }
            case LDAINDX: {
                BYTE zeroPageAddress = fetch_byte(mainbus);
                BYTE lowAddress = static_cast<BYTE>(zeroPageAddress + X);
                BYTE highAddress = static_cast<BYTE>(lowAddress + 1);

                WORD address = mainbus.read_byte(lowAddress);
                address |= static_cast<WORD>(mainbus.read_byte(highAddress)) << 8;

                A = mainbus.read_byte(address);

                if (A == 0x00)
                    PS.Z = 1;
                else
                    PS.Z = 0;
                if (A & 0x80)
                    PS.N = 1;
                else
                    PS.N = 0;

                return 6;
            }
            case LDAINDY: {
                bool crossedPageBoundary = false;
                BYTE zp = fetch_byte(mainbus);

                BYTE lo = mainbus.read_byte(zp);
                BYTE hi = mainbus.read_byte(static_cast<BYTE>(zp + 1));

                WORD address =
                    static_cast<WORD>(lo) |
                    (static_cast<WORD>(hi) << 8);

                if ((address & 0xFF) + Y > 0xFF)
                    crossedPageBoundary = true;

                A = mainbus.read_byte(address + Y);

                if (A == 0x00)
                    PS.Z = 1;
                else
                    PS.Z = 0;
                if (A & 0x80)
                    PS.N = 1;
                else
                    PS.N = 0;

                return crossedPageBoundary ? 6 : 5;
            }

            case LDXIM: {
                BYTE constant = fetch_byte(mainbus);
                X = constant;

                if (X == 0x00)
                    PS.Z = 1;
                else
                    PS.Z = 0;
                if (X & 0x80)
                    PS.N = 1;
                else
                    PS.N = 0;

                return 2;
            }
            case LDXZP: {
                BYTE address = fetch_byte(mainbus);
                X = mainbus.read_byte(address);

                if (X == 0x00)
                    PS.Z = 1;
                else
                    PS.Z = 0;
                if (X & 0x80)
                    PS.N = 1;
                else
                    PS.N = 0;

                return 3;
            }
            case LDXZPY: {
                BYTE address = fetch_byte(mainbus);
                address += Y;
                BYTE value = mainbus.read_byte(address);
                X = value;

                if (X == 0x00)
                    PS.Z = 1;
                else
                    PS.Z = 0;
                if (X & 0x80)
                    PS.N = 1;
                else
                    PS.N = 0;

                return 4;
            }
            case LDXABS: {
                WORD address = fetch_word(mainbus);
                X = mainbus.read_byte(address);

                if (X == 0x00)
                    PS.Z = 1;
                else
                    PS.Z = 0;
                if (X & 0x80)
                    PS.N = 1;
                else
                    PS.N = 0;

                return 4;
            }
            case LDXABSY: {
                bool crossedPageBoundary = false;
                WORD address = fetch_word(mainbus);
                if ((BYTE) address + Y > 0xFF)
                    crossedPageBoundary = true;
                X = mainbus.read_byte(address + Y);

                if (X == 0x00)
                    PS.Z = 1;
                else
                    PS.Z = 0;
                if (X & 0x80)
                    PS.N = 1;
                else
                    PS.N = 0;

                return crossedPageBoundary ? 5 : 4;
            }

            case LDYIM: {
                BYTE constant = fetch_byte(mainbus);
                Y = constant;

                if (Y == 0x00)
                    PS.Z = 1;
                else
                    PS.Z = 0;
                if (Y & 0x80)
                    PS.N = 1;
                else
                    PS.N = 0;

                return 2;
            }
            case LDYZP: {
                BYTE address = fetch_byte(mainbus);
                Y = mainbus.read_byte(address);

                if (Y == 0x00)
                    PS.Z = 1;
                else
                    PS.Z = 0;
                if (Y & 0x80)
                    PS.N = 1;
                else
                    PS.N = 0;

                return 3;
            }
            case LDYZPX: {
                BYTE address = fetch_byte(mainbus);
                address += X;
                BYTE value = mainbus.read_byte(address);
                Y = value;

                if (Y == 0x00)
                    PS.Z = 1;
                else
                    PS.Z = 0;
                if (Y & 0x80)
                    PS.N = 1;
                else
                    PS.N = 0;

                return 4;
            }
            case LDYABS: {
                WORD address = fetch_word(mainbus);
                Y = mainbus.read_byte(address);

                if (Y == 0x00)
                    PS.Z = 1;
                else
                    PS.Z = 0;
                if (Y & 0x80)
                    PS.N = 1;
                else
                    PS.N = 0;

                return 4;
            }
            case LDYABSX: {
                bool crossedPageBoundary = false;
                WORD address = fetch_word(mainbus);
                if ((BYTE) address + X > 0xFF)
                    crossedPageBoundary = true;
                Y = mainbus.read_byte(address + X);

                if (Y == 0x00)
                    PS.Z = 1;
                else
                    PS.Z = 0;
                if (Y & 0x80)
                    PS.N = 1;
                else
                    PS.N = 0;

                return crossedPageBoundary ? 5 : 4;
            }

            case STAZP: {
                BYTE zeroPageAddress = fetch_byte(mainbus);
                mainbus.set_byte(zeroPageAddress, A);

                return 3;
            }
            case STAZPX: {
                BYTE zeroPageAddress = fetch_byte(mainbus);
                zeroPageAddress += X;

                mainbus.set_byte(zeroPageAddress, A);

                return 4;
            }
            case STAABS: {
                WORD address = fetch_word(mainbus);
                mainbus.set_byte(address, A);

                return 4;
            }
            case STAABSX: {
                WORD address = fetch_word(mainbus);
                mainbus.set_byte(address + X, A);

                return 5;
            }
            case STAABSY: {
                WORD address = fetch_word(mainbus);
                mainbus.set_byte(address + Y, A);

                return 5;
            }
            case STAINDX: {
                BYTE zeroPageAddress = fetch_byte(mainbus);
                BYTE lowAddress = static_cast<BYTE>(zeroPageAddress + X);
                BYTE highAddress = static_cast<BYTE>(lowAddress + 1);

                WORD address = mainbus.read_byte(lowAddress);
                address |= static_cast<WORD>(mainbus.read_byte(highAddress)) << 8;

                mainbus.set_byte(address, A);

                return 6;
            }
            case STAINDY: {
                BYTE zp = fetch_byte(mainbus);

                BYTE lo = mainbus.read_byte(zp);
                BYTE hi = mainbus.read_byte(static_cast<BYTE>(zp + 1));

                WORD address =
                    static_cast<WORD>(lo) |
                    (static_cast<WORD>(hi) << 8);

                mainbus.set_byte(address + Y, A);

                return 6;
            }

            case STXZP: {
                BYTE zeroPageAddress = fetch_byte(mainbus);
                mainbus.set_byte(zeroPageAddress, X);

                return 3;
            }
            case STXZPY: {
                BYTE zeroPageAddress = fetch_byte(mainbus);
                zeroPageAddress += Y;

                mainbus.set_byte(zeroPageAddress, X);

                return 4;
            }
            case STXABS: {
                WORD address = fetch_word(mainbus);
                mainbus.set_byte(address, X);

                return 4;
            }

            case STYZP: {
                BYTE zeroPageAddress = fetch_byte(mainbus);
                mainbus.set_byte(zeroPageAddress, Y);

                return 3;
            }
            case STYZPX: {
                BYTE zeroPageAddress = fetch_byte(mainbus);
                zeroPageAddress += X;

                mainbus.set_byte(zeroPageAddress, Y);

                return 4;
            }
            case STYABS: {
                WORD address = fetch_word(mainbus);
                mainbus.set_byte(address, Y);

                return 4;
            }

            case TAX: {
                X = A;

                if (X == 0x00)
                    PS.Z = 1;
                else
                    PS.Z = 0;
                if (X & 0x80)
                    PS.N = 1;
                else
                    PS.N = 0;

                return 2;
            }

            case TXA: {
                A = X;

                if (A == 0x00)
                    PS.Z = 1;
                else
                    PS.Z = 0;
                if (A & 0x80)
                    PS.N = 1;
                else
                    PS.N = 0;

                return 2;
            }

            case TAY: {
                Y = A;

                if (Y == 0x00)
                    PS.Z = 1;
                else
                    PS.Z = 0;
                if (Y & 0x80)
                    PS.N = 1;
                else
                    PS.N = 0;

                return 2;
            }

            case TYA: {
                A = Y;

                if (A == 0x00)
                    PS.Z = 1;
                else
                    PS.Z = 0;
                if (A & 0x80)
                    PS.N = 1;
                else
                    PS.N = 0;

                return 2;
            }

            case TSX: {
                X = S;

                if (X == 0x00)
                    PS.Z = 1;
                else
                    PS.Z = 0;
                if (X & 0x80)
                    PS.N = 1;
                else
                    PS.N = 0;

                return 2;
            }

            case TXS: {
                S = X;

                return 2;
            }

            case PHA: {
                push_byte_to_stack(mainbus, A);

                return 3;
            }

            case PHP: {
                ProcessorStatus pushedStatus = PS;
                pushedStatus.B = 1;
                pushedStatus.pad_ = 1;
                BYTE pushedStatusByte = std::bit_cast<BYTE>(pushedStatus);
                push_byte_to_stack(mainbus, pushedStatusByte);

                return 3;
            }

            case PLA: {
                BYTE value = fetch_byte_from_stack(mainbus);

                A = value;

                if (A == 0x00)
                    PS.Z = 1;
                else
                    PS.Z = 0;
                if (A & 0x80)
                    PS.N = 1;
                else
                    PS.N = 0;

                return 4;
            }

            case PLP: {
                ProcessorStatus pulledPS = std::bit_cast<ProcessorStatus>(fetch_byte_from_stack(mainbus));
                pulledPS.B = 0;
                pulledPS.pad_ = 0;

                if (pulledPS.I) {
                    pulledPS.I = 1;
                    setInteruptFlagAtNextInstruction = true;
                }

                PS = pulledPS;

                return 4;
            }

            case ANDIM: {
                BYTE andValue = fetch_byte(mainbus);

                BYTE result = A & andValue;
                A = result;

                if (A == 0x00)
                    PS.Z = 1;
                else
                    PS.Z = 0;
                if (A & 0x80)
                    PS.N = 1;
                else
                    PS.N = 0;

                if (A == 0x00)
                    PS.Z = 1;
                else
                    PS.Z = 0;
                if (A & 0x80)
                    PS.N = 1;
                else
                    PS.N = 0;

                return 2;
            }
            case ANDZP: {
                BYTE zeroPageAddress = fetch_byte(mainbus);
                BYTE andValue = mainbus.read_byte(zeroPageAddress);

                BYTE result = A & andValue;
                A = result;

                if (A == 0x00)
                    PS.Z = 1;
                else
                    PS.Z = 0;
                if (A & 0x80)
                    PS.N = 1;
                else
                    PS.N = 0;

                return 3;
            }
            case ANDZPX: {
                BYTE zeroPageAddress = fetch_byte(mainbus);
                BYTE andValue = mainbus.read_byte(zeroPageAddress + X);

                BYTE result = A & andValue;
                A = result;

                if (A == 0x00)
                    PS.Z = 1;
                else
                    PS.Z = 0;
                if (A & 0x80)
                    PS.N = 1;
                else
                    PS.N = 0;

                return 4;
            }
            case ANDABS: {
                WORD address = fetch_word(mainbus);
                BYTE andValue = mainbus.read_byte(address);

                BYTE result = A & andValue;
                A = result;

                if (A == 0x00)
                    PS.Z = 1;
                else
                    PS.Z = 0;
                if (A & 0x80)
                    PS.N = 1;
                else
                    PS.N = 0;

                return 4;
            }
            case ANDABSX: {
                bool crossedPageBoundary = false;
                WORD address = fetch_word(mainbus);
                if ((BYTE) address + X > 0xFF)
                    crossedPageBoundary = true;

                BYTE andValue = mainbus.read_byte(address + X);

                BYTE result = A & andValue;
                A = result;

                if (A == 0x00)
                    PS.Z = 1;
                else
                    PS.Z = 0;
                if (A & 0x80)
                    PS.N = 1;
                else
                    PS.N = 0;

                return crossedPageBoundary ? 5 : 4;
            }
            case ANDABSY: {
                bool crossedPageBoundary = false;
                WORD address = fetch_word(mainbus);
                if ((BYTE) address + Y > 0xFF)
                    crossedPageBoundary = true;

                BYTE andValue = mainbus.read_byte(address + Y);

                BYTE result = A & andValue;
                A = result;

                if (A == 0x00)
                    PS.Z = 1;
                else
                    PS.Z = 0;
                if (A & 0x80)
                    PS.N = 1;
                else
                    PS.N = 0;

                return crossedPageBoundary ? 5 : 4;
            }
            case ANDINDX: {
                BYTE zeroPageAddress = fetch_byte(mainbus);
                BYTE lowAddress = static_cast<BYTE>(zeroPageAddress + X);
                BYTE highAddress = static_cast<BYTE>(lowAddress + 1);

                WORD address = mainbus.read_byte(lowAddress);
                address |= static_cast<WORD>(mainbus.read_byte(highAddress)) << 8;

                BYTE andValue = mainbus.read_byte(address);

                BYTE result = A & andValue;
                A = result;

                if (A == 0x00)
                    PS.Z = 1;
                else
                    PS.Z = 0;
                if (A & 0x80)
                    PS.N = 1;
                else
                    PS.N = 0;

                return 6;
            }
            case ANDINDY: {
                bool crossedPageBoundary = false;
                BYTE zp = fetch_byte(mainbus);

                BYTE lo = mainbus.read_byte(zp);
                BYTE hi = mainbus.read_byte(static_cast<BYTE>(zp + 1));

                WORD address =
                    static_cast<WORD>(lo) |
                    (static_cast<WORD>(hi) << 8);

                if ((BYTE) address + Y > 0xFF)
                    crossedPageBoundary = true;

                BYTE andValue = mainbus.read_byte(address + Y);

                BYTE result = A & andValue;
                A = result;

                if (A == 0x00)
                    PS.Z = 1;
                else
                    PS.Z = 0;
                if (A & 0x80)
                    PS.N = 1;
                else
                    PS.N = 0;

                return crossedPageBoundary ? 6 : 5;
            }

            case ORAIM: {
                BYTE andValue = fetch_byte(mainbus);

                BYTE result = A | andValue;
                A = result;

                if (A == 0x00)
                    PS.Z = 1;
                else
                    PS.Z = 0;
                if (A & 0x80)
                    PS.N = 1;
                else
                    PS.N = 0;

                return 2;
            }
            case ORAZP: {
                BYTE zeroPageAddress = fetch_byte(mainbus);
                BYTE andValue = mainbus.read_byte(zeroPageAddress);

                BYTE result = A | andValue;
                A = result;

                if (A == 0x00)
                    PS.Z = 1;
                else
                    PS.Z = 0;
                if (A & 0x80)
                    PS.N = 1;
                else
                    PS.N = 0;

                return 3;
            }
            case ORAZPX: {
                BYTE zeroPageAddress = fetch_byte(mainbus);
                BYTE andValue = mainbus.read_byte(zeroPageAddress + X);

                BYTE result = A | andValue;
                A = result;

                if (A == 0x00)
                    PS.Z = 1;
                else
                    PS.Z = 0;
                if (A & 0x80)
                    PS.N = 1;
                else
                    PS.N = 0;

                return 4;
            }
            case ORAABS: {
                WORD address = fetch_word(mainbus);
                BYTE andValue = mainbus.read_byte(address);

                BYTE result = A | andValue;
                A = result;

                if (A == 0x00)
                    PS.Z = 1;
                else
                    PS.Z = 0;
                if (A & 0x80)
                    PS.N = 1;
                else
                    PS.N = 0;

                return 4;
            }
            case ORAABSX: {
                bool crossedPageBoundary = false;
                WORD address = fetch_word(mainbus);
                if ((BYTE) address + X > 0xFF)
                    crossedPageBoundary = true;

                BYTE andValue = mainbus.read_byte(address + X);

                BYTE result = A | andValue;
                A = result;

                if (A == 0x00)
                    PS.Z = 1;
                else
                    PS.Z = 0;
                if (A & 0x80)
                    PS.N = 1;
                else
                    PS.N = 0;

                return crossedPageBoundary ? 5 : 4;
            }
            case ORAABSY: {
                bool crossedPageBoundary = false;
                WORD address = fetch_word(mainbus);
                if ((BYTE) address + Y > 0xFF)
                    crossedPageBoundary = true;

                BYTE andValue = mainbus.read_byte(address + Y);

                BYTE result = A | andValue;
                A = result;

                if (A == 0x00)
                    PS.Z = 1;
                else
                    PS.Z = 0;
                if (A & 0x80)
                    PS.N = 1;
                else
                    PS.N = 0;

                return crossedPageBoundary ? 5 : 4;
            }
            case ORAINDX: {
                BYTE zeroPageAddress = fetch_byte(mainbus);
                BYTE lowAddress = static_cast<BYTE>(zeroPageAddress + X);
                BYTE highAddress = static_cast<BYTE>(lowAddress + 1);

                WORD address = mainbus.read_byte(lowAddress);
                address |= static_cast<WORD>(mainbus.read_byte(highAddress)) << 8;

                BYTE andValue = mainbus.read_byte(address);

                BYTE result = A | andValue;
                A = result;

                if (A == 0x00)
                    PS.Z = 1;
                else
                    PS.Z = 0;
                if (A & 0x80)
                    PS.N = 1;
                else
                    PS.N = 0;

                return 6;
            }
            case ORAINDY: {
                bool crossedPageBoundary = false;
                BYTE zp = fetch_byte(mainbus);

                BYTE lo = mainbus.read_byte(zp);
                BYTE hi = mainbus.read_byte(static_cast<BYTE>(zp + 1));

                WORD address =
                    static_cast<WORD>(lo) |
                    (static_cast<WORD>(hi) << 8);

                if ((BYTE) address + Y > 0xFF)
                    crossedPageBoundary = true;

                BYTE andValue = mainbus.read_byte(address + Y);

                BYTE result = A | andValue;
                A = result;

                if (A == 0x00)
                    PS.Z = 1;
                else
                    PS.Z = 0;
                if (A & 0x80)
                    PS.N = 1;
                else
                    PS.N = 0;

                return crossedPageBoundary ? 6 : 5;
            }

            case EORIM: {
                BYTE andValue = fetch_byte(mainbus);

                BYTE result = A ^ andValue;
                A = result;

                if (A == 0x00)
                    PS.Z = 1;
                else
                    PS.Z = 0;
                if (A & 0x80)
                    PS.N = 1;
                else
                    PS.N = 0;

                return 2;
            }
            case EORZP: {
                BYTE zeroPageAddress = fetch_byte(mainbus);
                BYTE andValue = mainbus.read_byte(zeroPageAddress);

                BYTE result = A ^ andValue;
                A = result;

                if (A == 0x00)
                    PS.Z = 1;
                else
                    PS.Z = 0;
                if (A & 0x80)
                    PS.N = 1;
                else
                    PS.N = 0;

                return 3;
            }
            case EORZPX: {
                BYTE zeroPageAddress = fetch_byte(mainbus);
                BYTE andValue = mainbus.read_byte(zeroPageAddress + X);

                BYTE result = A ^ andValue;
                A = result;

                if (A == 0x00)
                    PS.Z = 1;
                else
                    PS.Z = 0;
                if (A & 0x80)
                    PS.N = 1;
                else
                    PS.N = 0;

                return 4;
            }
            case EORABS: {
                WORD address = fetch_word(mainbus);
                BYTE andValue = mainbus.read_byte(address);

                BYTE result = A ^ andValue;
                A = result;

                if (A == 0x00)
                    PS.Z = 1;
                else
                    PS.Z = 0;
                if (A & 0x80)
                    PS.N = 1;
                else
                    PS.N = 0;

                return 4;
            }
            case EORABSX: {
                bool crossedPageBoundary = false;
                WORD address = fetch_word(mainbus);
                if ((BYTE) address + X > 0xFF)
                    crossedPageBoundary = true;

                BYTE andValue = mainbus.read_byte(address + X);

                BYTE result = A ^ andValue;
                A = result;

                if (A == 0x00)
                    PS.Z = 1;
                else
                    PS.Z = 0;
                if (A & 0x80)
                    PS.N = 1;
                else
                    PS.N = 0;

                return crossedPageBoundary ? 5 : 4;
            }
            case EORABSY: {
                bool crossedPageBoundary = false;
                WORD address = fetch_word(mainbus);
                if ((BYTE) address + Y > 0xFF)
                    crossedPageBoundary = true;

                BYTE andValue = mainbus.read_byte(address + Y);

                BYTE result = A ^ andValue;
                A = result;

                if (A == 0x00)
                    PS.Z = 1;
                else
                    PS.Z = 0;
                if (A & 0x80)
                    PS.N = 1;
                else
                    PS.N = 0;

                return crossedPageBoundary ? 5 : 4;
            }
            case EORINDX: {
                BYTE zeroPageAddress = fetch_byte(mainbus);
                BYTE lowAddress = static_cast<BYTE>(zeroPageAddress + X);
                BYTE highAddress = static_cast<BYTE>(lowAddress + 1);

                WORD address = mainbus.read_byte(lowAddress);
                address |= static_cast<WORD>(mainbus.read_byte(highAddress)) << 8;

                BYTE andValue = mainbus.read_byte(address);

                BYTE result = A ^ andValue;
                A = result;

                if (A == 0x00)
                    PS.Z = 1;
                else
                    PS.Z = 0;
                if (A & 0x80)
                    PS.N = 1;
                else
                    PS.N = 0;

                return 6;
            }
            case EORINDY: {
                bool crossedPageBoundary = false;
                BYTE zp = fetch_byte(mainbus);

                BYTE lo = mainbus.read_byte(zp);
                BYTE hi = mainbus.read_byte(static_cast<BYTE>(zp + 1));

                WORD address =
                    static_cast<WORD>(lo) |
                    (static_cast<WORD>(hi) << 8);

                if ((BYTE) address + Y > 0xFF)
                    crossedPageBoundary = true;

                BYTE andValue = mainbus.read_byte(address + Y);

                BYTE result = A ^ andValue;
                A = result;

                if (A == 0x00)
                    PS.Z = 1;
                else
                    PS.Z = 0;
                if (A & 0x80)
                    PS.N = 1;
                else
                    PS.N = 0;

                return crossedPageBoundary ? 6 : 5;
            }

            case BITZP: {
                BYTE zeroPageAddress = fetch_byte(mainbus);
                BYTE andValue = mainbus.read_byte(zeroPageAddress);

                BYTE result = A & andValue;

                PS.Z = ((A & andValue) == 0);
                PS.N = (andValue & 0x80) != 0;
                PS.V = (andValue & 0x40) != 0;
                return 3;
            }
            case BITABS: {
                WORD address = fetch_word(mainbus);
                BYTE andValue = mainbus.read_byte(address);

                BYTE result = A & andValue;

                PS.Z = ((A & andValue) == 0);
                PS.N = (andValue & 0x80) != 0;
                PS.V = (andValue & 0x40) != 0;
                return 4;
            }

            case ADCIM: {
                BYTE constant = fetch_byte(mainbus);
                WORD result = A + constant + PS.C;

                if ((result ^ A) & (result ^ constant) & 0x80)
                    PS.V = 1;
                else
                    PS.V = 0;

                A = (BYTE) result;

                if (result > 0xFF)
                    PS.C = 1;
                else
                    PS.C = 0;
                if (A == 0x00)
                    PS.Z = 1;
                else
                    PS.Z = 0;
                if (A & 0x80)
                    PS.N = 1;
                else
                    PS.N = 0;

                return 2;
            }
            case ADCZP: {
                BYTE zeroPageAddress = fetch_byte(mainbus);
                BYTE constant = mainbus.read_byte(zeroPageAddress);
                WORD result = A + constant + PS.C;

                if ((result ^ A) & (result ^ constant) & 0x80)
                    PS.V = 1;
                else
                    PS.V = 0;

                A = (BYTE) result;

                if (result > 0xFF)
                    PS.C = 1;
                else
                    PS.C = 0;
                if (A == 0x00)
                    PS.Z = 1;
                else
                    PS.Z = 0;
                if (A & 0x80)
                    PS.N = 1;
                else
                    PS.N = 0;

                return 3;
            }
            case ADCZPX: {
                BYTE zeroPageAddress = fetch_byte(mainbus) + X;
                BYTE constant = mainbus.read_byte(zeroPageAddress);
                WORD result = A + constant + PS.C;

                if ((result ^ A) & (result ^ constant) & 0x80)
                    PS.V = 1;
                else
                    PS.V = 0;

                A = (BYTE) result;

                if (result > 0xFF)
                    PS.C = 1;
                else
                    PS.C = 0;
                if (A == 0x00)
                    PS.Z = 1;
                else
                    PS.Z = 0;
                if (A & 0x80)
                    PS.N = 1;
                else
                    PS.N = 0;

                return 4;
            }
            case ADCABS: {
                WORD address = fetch_word(mainbus);
                BYTE constant = mainbus.read_byte(address);
                WORD result = A + constant + PS.C;

                if ((result ^ A) & (result ^ constant) & 0x80)
                    PS.V = 1;
                else
                    PS.V = 0;

                A = (BYTE) result;

                if (result > 0xFF)
                    PS.C = 1;
                else
                    PS.C = 0;
                if (A == 0x00)
                    PS.Z = 1;
                else
                    PS.Z = 0;
                if (A & 0x80)
                    PS.N = 1;
                else
                    PS.N = 0;

                return 4;
            }
            case ADCABSX: {
                bool crossedPageBoundary = false;
                WORD address = fetch_word(mainbus);
                if ((BYTE) address + X > 0xFF)
                    crossedPageBoundary = true;

                BYTE constant = mainbus.read_byte(address + X);
                WORD result = A + constant + PS.C;

                if ((result ^ A) & (result ^ constant) & 0x80)
                    PS.V = 1;
                else
                    PS.V = 0;

                A = (BYTE) result;

                if (result > 0xFF)
                    PS.C = 1;
                else
                    PS.C = 0;
                if (A == 0x00)
                    PS.Z = 1;
                else
                    PS.Z = 0;
                if (A & 0x80)
                    PS.N = 1;
                else
                    PS.N = 0;

                return crossedPageBoundary ? 5 : 4;
            }
            case ADCABSY: {
                bool crossedPageBoundary = false;
                WORD address = fetch_word(mainbus);
                if ((BYTE) address + Y > 0xFF)
                    crossedPageBoundary = true;

                BYTE constant = mainbus.read_byte(address + Y);
                WORD result = A + constant + PS.C;

                if ((result ^ A) & (result ^ constant) & 0x80)
                    PS.V = 1;
                else
                    PS.V = 0;

                A = (BYTE) result;

                if (result > 0xFF)
                    PS.C = 1;
                else
                    PS.C = 0;
                if (A == 0x00)
                    PS.Z = 1;
                else
                    PS.Z = 0;
                if (A & 0x80)
                    PS.N = 1;
                else
                    PS.N = 0;

                return crossedPageBoundary ? 5 : 4;
            }
            case ADCINDX: {
                BYTE zeroPageAddress = fetch_byte(mainbus);
                BYTE lowAddress = static_cast<BYTE>(zeroPageAddress + X);
                BYTE highAddress = static_cast<BYTE>(lowAddress + 1);

                WORD address = mainbus.read_byte(lowAddress);
                address |= static_cast<WORD>(mainbus.read_byte(highAddress)) << 8;

                BYTE constant = mainbus.read_byte(address);
                WORD result = A + constant + PS.C;

                if ((result ^ A) & (result ^ constant) & 0x80)
                    PS.V = 1;
                else
                    PS.V = 0;

                A = (BYTE) result;

                if (result > 0xFF)
                    PS.C = 1;
                else
                    PS.C = 0;
                if (A == 0x00)
                    PS.Z = 1;
                else
                    PS.Z = 0;
                if (A & 0x80)
                    PS.N = 1;
                else
                    PS.N = 0;

                return 6;
            }
            case ADCINDY: {
                bool crossedPageBoundary = false;
                BYTE zp = fetch_byte(mainbus);

                BYTE lo = mainbus.read_byte(zp);
                BYTE hi = mainbus.read_byte(static_cast<BYTE>(zp + 1));

                WORD address =
                    static_cast<WORD>(lo) |
                    (static_cast<WORD>(hi) << 8);

                if ((BYTE) address + Y > 0xFF)
                    crossedPageBoundary = true;

                BYTE constant = mainbus.read_byte(address + Y);
                WORD result = A + constant + PS.C;

                if ((result ^ A) & (result ^ constant) & 0x80)
                    PS.V = 1;
                else
                    PS.V = 0;

                A = (BYTE) result;

                if (result > 0xFF)
                    PS.C = 1;
                else
                    PS.C = 0;
                if (A == 0x00)
                    PS.Z = 1;
                else
                    PS.Z = 0;
                if (A & 0x80)
                    PS.N = 1;
                else
                    PS.N = 0;

                return crossedPageBoundary ? 6 : 5;
            }

            case SBCIM: {
                BYTE constant = fetch_byte(mainbus);
                WORD result = A - constant;
                result -= !PS.C;

                if ((result ^ A) & (result ^ ~constant) & 0x80)
                    PS.V = 1;

                A = (BYTE) result;

                if (!(result & 0x100))
                    PS.C = 1;
                else
                    PS.C = 0;
                if (A == 0x00)
                    PS.Z = 1;
                else
                    PS.Z = 0;
                if (A & 0x80)
                    PS.N = 1;
                else
                    PS.N = 0;

                return 2;
            }
            case SBCZP: {
                BYTE zeroPageAddress = fetch_byte(mainbus);
                BYTE constant = mainbus.read_byte(zeroPageAddress);
                WORD result = A - constant;
                result -= !PS.C;

                if ((result ^ A) & (result ^ ~constant) & 0x80)
                    PS.V = 1;

                A = result;

                if (!(result & 0x100))
                    PS.C = 1;
                else
                    PS.C = 0;
                if (A == 0x00)
                    PS.Z = 1;
                else
                    PS.Z = 0;
                if (A & 0x80)
                    PS.N = 1;
                else
                    PS.N = 0;

                return 3;
            }
            case SBCZPX: {
                BYTE zeroPageAddress = fetch_byte(mainbus) + X;
                BYTE constant = mainbus.read_byte(zeroPageAddress);
                WORD result = A - constant;
                result -= !PS.C;

                if ((result ^ A) & (result ^ ~constant) & 0x80)
                    PS.V = 1;

                A = result;

                if (!(result & 0x100))
                    PS.C = 1;
                else
                    PS.C = 0;
                if (A == 0x00)
                    PS.Z = 1;
                else
                    PS.Z = 0;
                if (A & 0x80)
                    PS.N = 1;
                else
                    PS.N = 0;

                return 4;
            }
            case SBCABS: {
                WORD address = fetch_word(mainbus);
                BYTE constant = mainbus.read_byte(address);
                WORD result = A - constant;
                result -= !PS.C;

                if ((result ^ A) & (result ^ ~constant) & 0x80)
                    PS.V = 1;

                A = result;

                if (!(result & 0x100))
                    PS.C = 1;
                else
                    PS.C = 0;
                if (A == 0x00)
                    PS.Z = 1;
                else
                    PS.Z = 0;
                if (A & 0x80)
                    PS.N = 1;
                else
                    PS.N = 0;

                return 4;
            }
            case SBCABSX: {
                bool crossedPageBoundary = false;
                WORD address = fetch_word(mainbus);
                if ((BYTE) address + X > 0xFF)
                    crossedPageBoundary = true;

                BYTE constant = mainbus.read_byte(address + X);
                WORD result = A - constant;
                result -= !PS.C;

                if ((result ^ A) & (result ^ ~constant) & 0x80)
                    PS.V = 1;

                A = result;

                if (!(result & 0x100))
                    PS.C = 1;
                else
                    PS.C = 0;
                if (A == 0x00)
                    PS.Z = 1;
                else
                    PS.Z = 0;
                if (A & 0x80)
                    PS.N = 1;
                else
                    PS.N = 0;

                return crossedPageBoundary ? 5 : 4;
            }
            case SBCABSY: {
                bool crossedPageBoundary = false;
                WORD address = fetch_word(mainbus);
                if ((BYTE) address + Y > 0xFF)
                    crossedPageBoundary = true;

                BYTE constant = mainbus.read_byte(address + Y);
                WORD result = A - constant;
                result -= !PS.C;

                if ((result ^ A) & (result ^ ~constant) & 0x80)
                    PS.V = 1;

                A = result;

                if (!(result & 0x100))
                    PS.C = 1;
                else
                    PS.C = 0;
                if (A == 0x00)
                    PS.Z = 1;
                else
                    PS.Z = 0;
                if (A & 0x80)
                    PS.N = 1;
                else
                    PS.N = 0;

                return crossedPageBoundary ? 5 : 4;
            }
            case SBCINDX: {
                BYTE zeroPageAddress = fetch_byte(mainbus);
                BYTE lowAddress = static_cast<BYTE>(zeroPageAddress + X);
                BYTE highAddress = static_cast<BYTE>(lowAddress + 1);

                WORD address = mainbus.read_byte(lowAddress);
                address |= static_cast<WORD>(mainbus.read_byte(highAddress)) << 8;

                BYTE constant = mainbus.read_byte(address);
                WORD result = A - constant;
                result -= !PS.C;

                if ((result ^ A) & (result ^ ~constant) & 0x80)
                    PS.V = 1;

                A = result;

                if (!(result & 0x100))
                    PS.C = 1;
                else
                    PS.C = 0;
                if (A == 0x00)
                    PS.Z = 1;
                else
                    PS.Z = 0;
                if (A & 0x80)
                    PS.N = 1;
                else
                    PS.N = 0;

                return 6;
            }
            case SBCINDY: {
                bool crossedPageBoundary = false;
                BYTE zp = fetch_byte(mainbus);

                BYTE lo = mainbus.read_byte(zp);
                BYTE hi = mainbus.read_byte(static_cast<BYTE>(zp + 1));

                WORD address =
                    static_cast<WORD>(lo) |
                    (static_cast<WORD>(hi) << 8);

                if ((BYTE) address + Y > 0xFF)
                    crossedPageBoundary = true;

                BYTE constant = mainbus.read_byte(address + Y);
                WORD result = A - constant;
                result -= !PS.C;

                if ((result ^ A) & (result ^ ~constant) & 0x80)
                    PS.V = 1;

                A = result;

                if (!(result & 0x100))
                    PS.C = 1;
                else
                    PS.C = 0;
                if (A == 0x00)
                    PS.Z = 1;
                else
                    PS.Z = 0;
                if (A & 0x80)
                    PS.N = 1;
                else
                    PS.N = 0;

                return crossedPageBoundary ? 6 : 5;
            }

            case INCZP: {
                BYTE zeroPageAddress = fetch_byte(mainbus);
                BYTE constant = mainbus.read_byte(zeroPageAddress);

                BYTE result = constant + 1;

                mainbus.set_byte(zeroPageAddress, constant); // This is some weird hardware behaviour we have to copy
                mainbus.set_byte(zeroPageAddress, result);

                if (result == 0x00)
                    PS.Z = 1;
                else
                    PS.Z = 0;
                if (result & 0x80)
                    PS.N = 1;
                else
                    PS.N = 0;

                return 5;
            }
            case INCZPX: {
                BYTE zeroPageAddress = fetch_byte(mainbus) + X;
                BYTE constant = mainbus.read_byte(zeroPageAddress);

                BYTE result = constant + 1;

                mainbus.set_byte(zeroPageAddress, constant); // This is some weird hardware behaviour we have to copy
                mainbus.set_byte(zeroPageAddress, result);

                if (result == 0x00)
                    PS.Z = 1;
                else
                    PS.Z = 0;
                if (result & 0x80)
                    PS.N = 1;
                else
                    PS.N = 0;

                return 6;
            }
            case INCABS: {
                WORD address = fetch_word(mainbus);
                BYTE constant = mainbus.read_byte(address);
                BYTE result = constant + 1;

                mainbus.set_byte(address, constant); // This is some weird hardware behaviour we have to copy
                mainbus.set_byte(address, result);

                if (result == 0x00)
                    PS.Z = 1;
                else
                    PS.Z = 0;
                if (result & 0x80)
                    PS.N = 1;
                else
                    PS.N = 0;

                return 6;
            }
            case INCABSX: {
                WORD address = fetch_word(mainbus) + X;
                BYTE constant = mainbus.read_byte(address);
                BYTE result = constant + 1;

                mainbus.set_byte(address, constant); // This is some weird hardware behaviour we have to copy
                mainbus.set_byte(address, result);

                if (result == 0x00)
                    PS.Z = 1;
                else
                    PS.Z = 0;
                if (result & 0x80)
                    PS.N = 1;
                else
                    PS.N = 0;
                return 7;
            }

            case DECZP: {
                BYTE zeroPageAddress = fetch_byte(mainbus);
                BYTE constant = mainbus.read_byte(zeroPageAddress);

                BYTE result = constant - 1;

                mainbus.set_byte(zeroPageAddress, constant); // This is some weird hardware behaviour we have to copy
                mainbus.set_byte(zeroPageAddress, result);

                if (result == 0x00)
                    PS.Z = 1;
                else
                    PS.Z = 0;
                if (result & 0x80)
                    PS.N = 1;
                else
                    PS.N = 0;

                return 5;
            }
            case DECZPX: {
                BYTE zeroPageAddress = fetch_byte(mainbus) + X;
                BYTE constant = mainbus.read_byte(zeroPageAddress);

                BYTE result = constant - 1;

                mainbus.set_byte(zeroPageAddress, constant); // This is some weird hardware behaviour we have to copy
                mainbus.set_byte(zeroPageAddress, result);

                if (result == 0x00)
                    PS.Z = 1;
                else
                    PS.Z = 0;
                if (result & 0x80)
                    PS.N = 1;
                else
                    PS.N = 0;

                return 6;
            }
            case DECABS: {
                WORD address = fetch_word(mainbus);
                BYTE constant = mainbus.read_byte(address);
                BYTE result = constant - 1;

                mainbus.set_byte(address, constant); // This is some weird hardware behaviour we have to copy
                mainbus.set_byte(address, result);

                if (result == 0x00)
                    PS.Z = 1;
                else
                    PS.Z = 0;
                if (result & 0x80)
                    PS.N = 1;
                else
                    PS.N = 0;

                return 6;
            }
            case DECABSX: {
                WORD address = fetch_word(mainbus) + X;
                BYTE constant = mainbus.read_byte(address);
                BYTE result = constant - 1;

                mainbus.set_byte(address, constant); // This is some weird hardware behaviour we have to copy
                mainbus.set_byte(address, result);

                if (result == 0x00)
                    PS.Z = 1;
                else
                    PS.Z = 0;
                if (result & 0x80)
                    PS.N = 1;
                else
                    PS.N = 0;

                return 7;
            }

            case INX: {
                X = X + 1;

                if (X == 0x00)
                    PS.Z = 1;
                else
                    PS.Z = 0;
                if (X & 0x80)
                    PS.N = 1;
                else
                    PS.N = 0;

                return 2;
            }

            case DEX: {
                X = X - 1;

                if (X == 0x00)
                    PS.Z = 1;
                else
                    PS.Z = 0;
                if (X & 0x80)
                    PS.N = 1;
                else
                    PS.N = 0;

                return 2;
            }

            case INY: {
                Y = Y + 1;

                if (Y == 0x00)
                    PS.Z = 1;
                else
                    PS.Z = 0;

                if (Y & 0x80)
                    PS.N = 1;
                else
                    PS.N = 0;

                return 2;
            }

            case DEY: {
                Y = Y - 1;

                if (Y == 0x00)
                    PS.Z = 1;
                else
                    PS.Z = 0;
                if (Y & 0x80)
                    PS.N = 1;
                else
                    PS.N = 0;

                return 2;
            }

            case ASLAC: {
                if (A & 0b10000000)
                    PS.C = 1;
                else
                    PS.C = 0;

                A = A << 1;

                if (A == 0x00)
                    PS.Z = 1;
                else
                    PS.Z = 0;
                if (A & 0x80)
                    PS.N = 1;
                else
                    PS.N = 0;

                return 2;
            }
            case ASLZP: {
                BYTE zeroPageAddress = fetch_byte(mainbus);
                BYTE constant = mainbus.read_byte(zeroPageAddress);

                if (constant & 0b10000000)
                    PS.C = 1;
                else
                    PS.C = 0;

                mainbus.set_byte(zeroPageAddress, constant); // hardware quirk, need to do this for proper emulation
                constant = constant << 1;
                mainbus.set_byte(zeroPageAddress, constant);

                if (constant == 0x00)
                    PS.Z = 1;
                else
                    PS.Z = 0;
                if (constant & 0x80)
                    PS.N = 1;
                else
                    PS.N = 0;

                return 5;
            }
            case ASLZPX: {
                BYTE zeroPageAddress = fetch_byte(mainbus) + X;
                BYTE constant = mainbus.read_byte(zeroPageAddress);

                if (constant & 0b10000000)
                    PS.C = 1;
                else
                    PS.C = 0;

                mainbus.set_byte(zeroPageAddress, constant); // hardware quirk, need to do this for proper emulation
                constant = constant << 1;
                mainbus.set_byte(zeroPageAddress, constant);

                if (constant == 0x00)
                    PS.Z = 1;
                else
                    PS.Z = 0;
                if (constant & 0x80)
                    PS.N = 1;
                else
                    PS.N = 0;

                return 6;
            }
            case ASLABS: {
                WORD address = fetch_word(mainbus);
                BYTE constant = mainbus.read_byte(address);

                if (constant & 0b10000000)
                    PS.C = 1;
                else
                    PS.C = 0;

                mainbus.set_byte(address, constant); // hardware quirk, need to do this for proper emulation
                constant = constant << 1;
                mainbus.set_byte(address, constant);

                if (constant == 0x00)
                    PS.Z = 1;
                else
                    PS.Z = 0;
                if (constant & 0x80)
                    PS.N = 1;
                else
                    PS.N = 0;

                return 6;
            }
            case ASLABSX: {
                WORD address = fetch_word(mainbus) + X;
                BYTE constant = mainbus.read_byte(address);

                if (constant & 0b10000000)
                    PS.C = 1;
                else
                    PS.C = 0;

                mainbus.set_byte(address, constant); // hardware quirk, need to do this for proper emulation
                constant = constant << 1;
                mainbus.set_byte(address, constant);

                if (constant == 0x00)
                    PS.Z = 1;
                else
                    PS.Z = 0;
                if (constant & 0x80)
                    PS.N = 1;
                else
                    PS.N = 0;

                return 7;
            }

            case LSRAC: {
                if (A & 0b00000001)
                    PS.C = 1;
                else
                    PS.C = 0;

                A = A >> 1;

                if (A == 0x00)
                    PS.Z = 1;
                else
                    PS.Z = 0;
                if (A & 0x80)
                    PS.N = 1;
                else
                    PS.N = 0;

                return 2;
            }
            case LSRZP: {
                BYTE zeroPageAddress = fetch_byte(mainbus);
                BYTE constant = mainbus.read_byte(zeroPageAddress);

                if (constant & 0b00000001)
                    PS.C = 1;
                else
                    PS.C = 0;

                mainbus.set_byte(zeroPageAddress, constant); // hardware quirk, need to do this for proper emulation
                constant = constant >> 1;
                mainbus.set_byte(zeroPageAddress, constant);

                if (constant == 0x00)
                    PS.Z = 1;
                else
                    PS.Z = 0;
                if (constant & 0x80)
                    PS.N = 1;
                else
                    PS.N = 0;

                return 5;
            }
            case LSRZPX: {
                BYTE zeroPageAddress = fetch_byte(mainbus) + X;
                BYTE constant = mainbus.read_byte(zeroPageAddress);

                if (constant & 0b00000001)
                    PS.C = 1;
                else
                    PS.C = 0;

                mainbus.set_byte(zeroPageAddress, constant); // hardware quirk, need to do this for proper emulation
                constant = constant >> 1;
                mainbus.set_byte(zeroPageAddress, constant);

                if (constant == 0x00)
                    PS.Z = 1;
                else
                    PS.Z = 0;
                if (constant & 0x80)
                    PS.N = 1;
                else
                    PS.N = 0;

                return 6;
            }
            case LSRABS: {
                WORD address = fetch_word(mainbus);
                BYTE constant = mainbus.read_byte(address);

                if (constant & 0b00000001)
                    PS.C = 1;
                else
                    PS.C = 0;

                mainbus.set_byte(address, constant); // hardware quirk, need to do this for proper emulation
                constant = constant >> 1;
                mainbus.set_byte(address, constant);

                if (constant == 0x00)
                    PS.Z = 1;
                else
                    PS.Z = 0;
                if (constant & 0x80)
                    PS.N = 1;
                else
                    PS.N = 0;

                return 6;
            }
            case LSRABSX: {
                WORD address = fetch_word(mainbus) + X;
                BYTE constant = mainbus.read_byte(address);

                if (constant & 0b00000001)
                    PS.C = 1;
                else
                    PS.C = 0;

                mainbus.set_byte(address, constant); // hardware quirk, need to do this for proper emulation
                constant = constant >> 1;
                mainbus.set_byte(address, constant);

                if (constant == 0x00)
                    PS.Z = 1;
                else
                    PS.Z = 0;
                if (constant & 0x80)
                    PS.N = 1;
                else
                    PS.N = 0;

                return 7;
            }

            case ROLAC: {
                bool carry = PS.C;

                if (A & 0b10000000)
                    PS.C = 1;
                else
                    PS.C = 0;

                A = A << 1;
                A |= carry;

                if (A == 0x00)
                    PS.Z = 1;
                else
                    PS.Z = 0;
                if (A & 0x80)
                    PS.N = 1;
                else
                    PS.N = 0;

                return 2;
            }
            case ROLZP: {
                BYTE zeroPageAddress = fetch_byte(mainbus);
                BYTE constant = mainbus.read_byte(zeroPageAddress);

                bool carry = PS.C;

                if (constant & 0b10000000)
                    PS.C = 1;
                else
                    PS.C = 0;

                mainbus.set_byte(zeroPageAddress, constant); // hardware quirk, need to do this for proper emulation
                constant = constant << 1;
                constant |= carry;
                mainbus.set_byte(zeroPageAddress, constant);

                if (constant == 0x00)
                    PS.Z = 1;
                else
                    PS.Z = 0;
                if (constant & 0x80)
                    PS.N = 1;
                else
                    PS.N = 0;

                return 5;
            }
            case ROLZPX: {
                BYTE zeroPageAddress = fetch_byte(mainbus) + X;
                BYTE constant = mainbus.read_byte(zeroPageAddress);

                bool carry = PS.C;

                if (constant & 0b10000000)
                    PS.C = 1;
                else
                    PS.C = 0;

                mainbus.set_byte(zeroPageAddress, constant); // hardware quirk, need to do this for proper emulation
                constant = constant << 1;
                constant |= carry;
                mainbus.set_byte(zeroPageAddress, constant);

                if (constant == 0x00)
                    PS.Z = 1;
                else
                    PS.Z = 0;
                if (constant & 0x80)
                    PS.N = 1;
                else
                    PS.N = 0;

                return 6;
            }
            case ROLABS: {
                WORD address = fetch_word(mainbus);
                BYTE constant = mainbus.read_byte(address);

                bool carry = PS.C;

                if (constant & 0b10000000)
                    PS.C = 1;
                else
                    PS.C = 0;

                mainbus.set_byte(address, constant); // hardware quirk, need to do this for proper emulation
                constant = constant << 1;
                constant |= carry;
                mainbus.set_byte(address, constant);

                if (constant == 0x00)
                    PS.Z = 1;
                else
                    PS.Z = 0;
                if (constant & 0x80)
                    PS.N = 1;
                else
                    PS.N = 0;

                return 6;
            }
            case ROLABSX: {
                WORD address = fetch_word(mainbus) + X;
                BYTE constant = mainbus.read_byte(address);

                bool carry = PS.C;

                if (constant & 0b10000000)
                    PS.C = 1;
                else
                    PS.C = 0;

                mainbus.set_byte(address, constant); // hardware quirk, need to do this for proper emulation
                constant = constant << 1;
                constant |= carry;
                mainbus.set_byte(address, constant);

                if (constant == 0x00)
                    PS.Z = 1;
                else
                    PS.Z = 0;
                if (constant & 0x80)
                    PS.N = 1;
                else
                    PS.N = 0;

                return 7;
            }

            case RORAC: {
                bool carry = PS.C;

                if (A & 0b00000001)
                    PS.C = 1;
                else
                    PS.C = 0;

                A = A >> 1;
                A |= carry << 7;

                if (A == 0x00)
                    PS.Z = 1;
                else
                    PS.Z = 0;
                if (A & 0x80)
                    PS.N = 1;
                else
                    PS.N = 0;

                return 2;
            }
            case RORZP: {
                BYTE zeroPageAddress = fetch_byte(mainbus);
                BYTE constant = mainbus.read_byte(zeroPageAddress);

                bool carry = PS.C;

                if (constant & 0b00000001)
                    PS.C = 1;
                else
                    PS.C = 0;

                mainbus.set_byte(zeroPageAddress, constant); // hardware quirk, need to do this for proper emulation
                constant = constant >> 1;
                constant |= carry << 7;
                mainbus.set_byte(zeroPageAddress, constant);

                if (constant == 0x00)
                    PS.Z = 1;
                else
                    PS.Z = 0;
                if (constant & 0x80)
                    PS.N = 1;
                else
                    PS.N = 0;

                return 5;
            }
            case RORZPX: {
                BYTE zeroPageAddress = fetch_byte(mainbus) + X;
                BYTE constant = mainbus.read_byte(zeroPageAddress);

                bool carry = PS.C;

                if (constant & 0b00000001)
                    PS.C = 1;
                else
                    PS.C = 0;

                mainbus.set_byte(zeroPageAddress, constant); // hardware quirk, need to do this for proper emulation
                constant = constant >> 1;
                constant |= carry << 7;
                mainbus.set_byte(zeroPageAddress, constant);

                if (constant == 0x00)
                    PS.Z = 1;
                else
                    PS.Z = 0;
                if (constant & 0x80)
                    PS.N = 1;
                else
                    PS.N = 0;

                return 6;
            }
            case RORABS: {
                WORD address = fetch_word(mainbus);
                BYTE constant = mainbus.read_byte(address);

                bool carry = PS.C;

                if (constant & 0b00000001)
                    PS.C = 1;
                else
                    PS.C = 0;

                mainbus.set_byte(address, constant); // hardware quirk, need to do this for proper emulation
                constant = constant >> 1;
                constant |= carry << 7;
                mainbus.set_byte(address, constant);

                if (constant == 0x00)
                    PS.Z = 1;
                else
                    PS.Z = 0;
                if (constant & 0x80)
                    PS.N = 1;
                else
                    PS.N = 0;

                return 6;
            }
            case RORABSX: {
                WORD address = fetch_word(mainbus) + X;
                BYTE constant = mainbus.read_byte(address);

                bool carry = PS.C;

                if (constant & 0b00000001)
                    PS.C = 1;
                else
                    PS.C = 0;

                mainbus.set_byte(address, constant); // hardware quirk, need to do this for proper emulation
                constant = constant >> 1;
                constant |= carry << 7;
                mainbus.set_byte(address, constant);

                if (constant == 0x00)
                    PS.Z = 1;
                else
                    PS.Z = 0;
                if (constant & 0x80)
                    PS.N = 1;
                else
                    PS.N = 0;

                return 7;
            }

            case CMPIM: {
                BYTE constant = fetch_byte(mainbus);
                BYTE result = A - constant;

                if (A >= constant)
                    PS.C = 1;
                else
                    PS.C = 0;
                if (result == 0x00)
                    PS.Z = 1;
                else
                    PS.Z = 0;
                if (result & 0x80)
                    PS.N = 1;
                else
                    PS.N = 0;

                return 2;
            }
            case CMPZP: {
                BYTE address = fetch_byte(mainbus);
                BYTE constant = mainbus.read_byte(address);
                BYTE result = A - constant;

                if (A >= constant)
                    PS.C = 1;
                else
                    PS.C = 0;
                if (result == 0x00)
                    PS.Z = 1;
                else
                    PS.Z = 0;
                if (result & 0x80)
                    PS.N = 1;
                else
                    PS.N = 0;

                return 3;
            }
            case CMPZPX: {
                BYTE address = fetch_byte(mainbus) + X;
                BYTE constant = mainbus.read_byte(address);
                BYTE result = A - constant;

                if (A >= constant)
                    PS.C = 1;
                else
                    PS.C = 0;
                if (result == 0x00)
                    PS.Z = 1;
                else
                    PS.Z = 0;
                if (result & 0x80)
                    PS.N = 1;
                else
                    PS.N = 0;

                return 4;
            }
            case CMPABS: {
                WORD address = fetch_word(mainbus);
                BYTE constant = mainbus.read_byte(address);
                BYTE result = A - constant;

                if (A >= constant)
                    PS.C = 1;
                else
                    PS.C = 0;
                if (result == 0x00)
                    PS.Z = 1;
                else
                    PS.Z = 0;
                if (result & 0x80)
                    PS.N = 1;
                else
                    PS.N = 0;

                return 4;
            }
            case CMPABSX: {
                bool crossedPageBoundary = false;
                WORD address = fetch_word(mainbus);
                if ((BYTE) address + X > 0xFF)
                    crossedPageBoundary = true;
                BYTE constant = mainbus.read_byte(address + X);
                BYTE result = A - constant;

                if (A >= constant)
                    PS.C = 1;
                else
                    PS.C = 0;
                if (result == 0x00)
                    PS.Z = 1;
                else
                    PS.Z = 0;
                if (result & 0x80)
                    PS.N = 1;
                else
                    PS.N = 0;

                return crossedPageBoundary ? 5 : 4;
            }
            case CMPABSY: {
                bool crossedPageBoundary = false;
                WORD address = fetch_word(mainbus);
                if ((BYTE) address + Y > 0xFF)
                    crossedPageBoundary = true;
                BYTE constant = mainbus.read_byte(address + Y);
                BYTE result = A - constant;

                if (A >= constant)
                    PS.C = 1;
                else
                    PS.C = 0;
                if (result == 0x00)
                    PS.Z = 1;
                else
                    PS.Z = 0;
                if (result & 0x80)
                    PS.N = 1;
                else
                    PS.N = 0;

                return crossedPageBoundary ? 5 : 4;
            }
            case CMPINDX: {
                BYTE zeroPageAddress = fetch_byte(mainbus);
                BYTE lowAddress = static_cast<BYTE>(zeroPageAddress + X);
                BYTE highAddress = static_cast<BYTE>(lowAddress + 1);

                WORD address = mainbus.read_byte(lowAddress);
                address |= static_cast<WORD>(mainbus.read_byte(highAddress)) << 8;

                BYTE constant = mainbus.read_byte(address);
                WORD result = A - constant;

                if (A >= constant)
                    PS.C = 1;
                else
                    PS.C = 0;
                if (result == 0x00)
                    PS.Z = 1;
                else
                    PS.Z = 0;
                if (result & 0x80)
                    PS.N = 1;
                else
                    PS.N = 0;

                return 6;
            }
            case CMPINDY: {
                bool crossedPageBoundary = false;
                BYTE zp = fetch_byte(mainbus);

                BYTE lo = mainbus.read_byte(zp);
                BYTE hi = mainbus.read_byte(static_cast<BYTE>(zp + 1));

                WORD address =
                    static_cast<WORD>(lo) |
                    (static_cast<WORD>(hi) << 8);

                if ((BYTE) address + Y > 0xFF)
                    crossedPageBoundary = true;

                BYTE constant = mainbus.read_byte(address + Y);
                WORD result = A - constant;

                if (A >= constant)
                    PS.C = 1;
                else
                    PS.C = 0;
                if (result == 0x00)
                    PS.Z = 1;
                else
                    PS.Z = 0;
                if (result & 0x80)
                    PS.N = 1;
                else
                    PS.N = 0;

                return crossedPageBoundary ? 6 : 5;
            }

            case CPXIM: {
                BYTE constant = fetch_byte(mainbus);
                BYTE result = X - constant;

                if (X >= constant)
                    PS.C = 1;
                else
                    PS.C = 0;
                if (result == 0x00)
                    PS.Z = 1;
                else
                    PS.Z = 0;
                if (result & 0x80)
                    PS.N = 1;
                else
                    PS.N = 0;

                return 2;
            }
            case CPXZP: {
                BYTE address = fetch_byte(mainbus);
                BYTE constant = mainbus.read_byte(address);
                BYTE result = X - constant;

                if (X >= constant)
                    PS.C = 1;
                else
                    PS.C = 0;
                if (result == 0x00)
                    PS.Z = 1;
                else
                    PS.Z = 0;
                if (result & 0x80)
                    PS.N = 1;
                else
                    PS.N = 0;

                return 3;
            }
            case CPXABS: {
                WORD address = fetch_word(mainbus);
                BYTE constant = mainbus.read_byte(address);
                BYTE result = X - constant;

                if (X >= constant)
                    PS.C = 1;
                else
                    PS.C = 0;
                if (result == 0x00)
                    PS.Z = 1;
                else
                    PS.Z = 0;
                if (result & 0x80)
                    PS.N = 1;
                else
                    PS.N = 0;

                return 4;
            }

            case CPYIM: {
                BYTE constant = fetch_byte(mainbus);
                BYTE result = Y - constant;

                if (Y >= constant)
                    PS.C = 1;
                else
                    PS.C = 0;
                if (result == 0x00)
                    PS.Z = 1;
                else
                    PS.Z = 0;
                if (result & 0x80)
                    PS.N = 1;
                else
                    PS.N = 0;

                return 2;
            }
            case CPYZP: {
                BYTE address = fetch_byte(mainbus);
                BYTE constant = mainbus.read_byte(address);
                BYTE result = Y - constant;

                if (Y >= constant)
                    PS.C = 1;
                else
                    PS.C = 0;
                if (result == 0x00)
                    PS.Z = 1;
                else
                    PS.Z = 0;
                if (result & 0x80)
                    PS.N = 1;
                else
                    PS.N = 0;

                return 3;
            }
            case CPYABS: {
                WORD address = fetch_word(mainbus);
                BYTE constant = mainbus.read_byte(address);
                BYTE result = Y - constant;

                if (Y >= constant)
                    PS.C = 1;
                else
                    PS.C = 0;
                if (result == 0x00)
                    PS.Z = 1;
                else
                    PS.Z = 0;
                if (result & 0x80)
                    PS.N = 1;
                else
                    PS.N = 0;

                return 4;
            }

            case BCC: {
                if (PS.C) {
                    fetch_byte(mainbus); // just to make PC be correct
                    return 2;
                } else {
                    bool pageBoundaryCrossed = false;
                    SIGNEDBYTE offset = fetch_byte(mainbus);
                    SIGNEDBYTE minusOffset = (-offset);
                    BYTE programCounter = PC;
                    if ((BYTE) PC + offset > 0xFF || (BYTE) PC < (-offset))
                        pageBoundaryCrossed = true;

                    PC = PC + offset;

                    return pageBoundaryCrossed ? 4 : 3;
                }
            }

            case BCS: {
                if (!PS.C) {
                    fetch_byte(mainbus); // just to make PC be correct
                    return 2;
                } else {
                    bool pageBoundaryCrossed = false;
                    SIGNEDBYTE offset = fetch_byte(mainbus);
                    SIGNEDBYTE minusOffset = (-offset);
                    BYTE programCounter = PC;
                    if ((BYTE) PC + offset > 0xFF || (BYTE) PC < (-offset))
                        pageBoundaryCrossed = true;

                    PC = PC + offset;

                    return pageBoundaryCrossed ? 4 : 3;
                }
            }

            case BEQ: {
                if (!PS.Z) {
                    fetch_byte(mainbus); // just to make PC be correct
                    return 2;
                } else {
                    bool pageBoundaryCrossed = false;
                    SIGNEDBYTE offset = fetch_byte(mainbus);
                    SIGNEDBYTE minusOffset = (-offset);
                    BYTE programCounter = PC;
                    if ((BYTE) PC + offset > 0xFF || (BYTE) PC < (-offset))
                        pageBoundaryCrossed = true;

                    PC = PC + offset;

                    return pageBoundaryCrossed ? 4 : 3;
                }
            }

            case BNE: {
                if (PS.Z) {
                    fetch_byte(mainbus); // just to make PC be correct
                    return 2;
                } else {
                    bool pageBoundaryCrossed = false;
                    SIGNEDBYTE offset = fetch_byte(mainbus);
                    SIGNEDBYTE minusOffset = (-offset);
                    BYTE programCounter = PC;
                    if ((BYTE) PC + offset > 0xFF || (BYTE) PC < (-offset))
                        pageBoundaryCrossed = true;

                    PC = PC + offset;

                    return pageBoundaryCrossed ? 4 : 3;
                }
            }

            case BPL: {
                if (PS.N) {
                    fetch_byte(mainbus); // just to make PC be correct
                    return 2;
                } else {
                    bool pageBoundaryCrossed = false;
                    SIGNEDBYTE offset = fetch_byte(mainbus);
                    SIGNEDBYTE minusOffset = (-offset);
                    BYTE programCounter = PC;
                    if ((BYTE) PC + offset > 0xFF || (BYTE) PC < (-offset))
                        pageBoundaryCrossed = true;

                    PC = PC + offset;

                    return pageBoundaryCrossed ? 4 : 3;
                }
            }

            case BMI: {
                if (!PS.N) {
                    fetch_byte(mainbus); // just to make PC be correct
                    return 2;
                } else {
                    bool pageBoundaryCrossed = false;
                    SIGNEDBYTE offset = fetch_byte(mainbus);
                    SIGNEDBYTE minusOffset = (-offset);
                    BYTE programCounter = PC;
                    if ((BYTE) PC + offset > 0xFF || (BYTE) PC < (-offset))
                        pageBoundaryCrossed = true;

                    PC = PC + offset;

                    return pageBoundaryCrossed ? 4 : 3;
                }
            }

            case BVC: {
                if (PS.V) {
                    fetch_byte(mainbus); // just to make PC be correct
                    return 2;
                } else {
                    bool pageBoundaryCrossed = false;
                    SIGNEDBYTE offset = fetch_byte(mainbus);
                    SIGNEDBYTE minusOffset = (-offset);
                    BYTE programCounter = PC;
                    if ((BYTE) PC + offset > 0xFF || (BYTE) PC < (-offset))
                        pageBoundaryCrossed = true;

                    PC = PC + offset;

                    return pageBoundaryCrossed ? 4 : 3;
                }
            }

            case BVS: {
                if (!PS.V) {
                    fetch_byte(mainbus); // just to make PC be correct
                    return 2;
                } else {
                    bool pageBoundaryCrossed = false;
                    SIGNEDBYTE offset = fetch_byte(mainbus);
                    SIGNEDBYTE minusOffset = (-offset);
                    BYTE programCounter = PC;
                    if ((BYTE) PC + offset > 0xFF || (BYTE) PC < (-offset))
                        pageBoundaryCrossed = true;

                    PC = PC + offset;

                    return pageBoundaryCrossed ? 4 : 3;
                }
            }

            case JMPABS: {
                WORD programCounter = fetch_word(mainbus);

                PC = programCounter;

                return 3;
            }
            case JMPIND: {
                WORD pointer = fetch_word(mainbus);

                // read word manually to simulate a page boundary bug with JMP indirect
                WORD value = mainbus.read_byte(pointer);
                WORD incrementedPointer = (pointer & 0xFF00) + (BYTE) (pointer + 1);
                value |= mainbus.read_byte(incrementedPointer) << 8;

                PC = value;

                return 5;
            }

            case JSR: {
                WORD programCounter = fetch_word(mainbus);

                push_byte_to_stack(mainbus, (PC - 1) >> 8);
                push_byte_to_stack(mainbus, PC - 1);

                PC = programCounter;

                return 6;
            }

            case RTS: {
                WORD programCounter = fetch_byte_from_stack(mainbus);
                programCounter |= fetch_byte_from_stack(mainbus) << 8;

                PC = programCounter + 1;

                return 6;
            }

            case BRK: {
                push_byte_to_stack(mainbus, (PC + 1) >> 8);
                push_byte_to_stack(mainbus, PC + 1);

                ProcessorStatus pushedStatus = PS;
                pushedStatus.B = 1;
                pushedStatus.pad_ = 1;
                BYTE pushedStatusByte = std::bit_cast<BYTE>(pushedStatus);
                push_byte_to_stack(mainbus, pushedStatusByte);

                PS.I = 1;

                PC = mainbus.read_word(0xFFFE);

                return 7;
            }

            case RTI: {
                ProcessorStatus pulledPS = std::bit_cast<ProcessorStatus>(fetch_byte_from_stack(mainbus));
                pulledPS.B = 0;
                pulledPS.pad_ = 0;

                PS = pulledPS;

                WORD programCounter = fetch_byte_from_stack(mainbus);
                programCounter |= fetch_byte_from_stack(mainbus) << 8;

                PC = programCounter;

                return 6;
            }

            case CLC: {
                PS.C = 0;

                return 2;
            }

            case SEC: {
                PS.C = 1;

                return 2;
            }

            case CLI: {
                PS.I = 0;
                clearInteruptFlagAtNextInstruction = true;

                return 2;
            }

            case SEI: {
                PS.I = 1;
                setInteruptFlagAtNextInstruction = true;

                return 2;
            }

            case CLD: {
                PS.D = 0;

                return 2;
            }

            case SED: {
                PS.D = 1;

                return 2;
            }

            case CLV: {
                PS.V = 0;

                return 2;
            }

            case NOP: {
                return 2;
            }

            default: {
                std::cerr
    << "Unknown opcode $" << std::hex
    << static_cast<int>(instruction)
    << " at PC $" << static_cast<WORD>(PC - 1)
    << '\n';
                throw std::runtime_error("Unsupported opcode");
                return 0;
            }

        }
    }

    void CPU::step(MainBus &mainbus) {
        //todo: do it actually properly cycle by cycle, idk if its even possible or if this shortcut will give issues, but lets try it

        if (skipCycles > 0) {
            skipCycles--;
            return;
        }

        BYTE instruction = fetch_byte(mainbus);

        uint32_t executed = executeInstruction(instruction, mainbus);

        skipCycles += executed - 1;
    }

    void CPU::start(NESsie::MainBus &mainbus) {
        WORD initialPC = fetch_word(mainbus);

        PC = initialPC;
    }

    BYTE CPU::fetch_byte(NESsie::MainBus &mainbus) {
        BYTE byte = mainbus.read_byte(PC);
        PC++;
        return byte;
    }

    WORD CPU::fetch_word(NESsie::MainBus &mainbus) {
        WORD word = mainbus.read_word(PC);
        PC += 2;
        return word;
    }

    BYTE CPU::fetch_byte_from_stack(NESsie::MainBus &mainbus) {
        WORD stackAddress = 0x0100;
        S++;
        BYTE value = mainbus.read_byte(stackAddress + S);
        return value;
    }

    void CPU::push_byte_to_stack(NESsie::MainBus &mainbus, BYTE value) {
        WORD stackAddress = 0x0100;
        mainbus.set_byte(stackAddress + S, value);
        S--;
    }

    BYTE CPU::peek_byte_from_stack(NESsie::MainBus &mainbus) {
        WORD stackAddress = 0x0100;
        BYTE value = mainbus.read_byte(stackAddress + S + 1);
        return value;
    }

    void CPU::NMI_handler(MainBus &mainbus) {
        push_byte_to_stack(mainbus, (PC) >> 8);
        push_byte_to_stack(mainbus, PC);

        ProcessorStatus pushedStatus = PS;
        pushedStatus.B = 0;
        pushedStatus.pad_ = 1;
        BYTE pushedStatusByte = std::bit_cast<BYTE>(pushedStatus);
        push_byte_to_stack(mainbus, pushedStatusByte);

        PS.I = 1;

        WORD programCounter = mainbus.read_word(0xFFFA);

        PC = programCounter;
    }
}
