#include "../../include/cpu/cpu.h"

#include "../../include/cpu/instruction.h"

#include <algorithm>
#include <iostream>
#include <iomanip>


namespace
{
    constexpr uint8_t carry_flag_mask {0b0000'0001};
    constexpr uint8_t overflow_flag_mask {0b0100'0000};
    constexpr uint8_t negative_flag_mask {0b1000'0000};

    constexpr uint16_t one_byte_overflow_mask {0xFF00};
    constexpr uint16_t zero_page_mask {0x00FF};

    constexpr uint16_t apu_and_io_space_start {0x4000};
    constexpr uint16_t ppu_registers_space_start {0x2000};
    constexpr uint16_t stack_offset {0x0100};

    constexpr uint16_t irq_vector_lsb {0xFFFE};
    constexpr uint16_t irq_vector_msb {0xFFFF};
    constexpr uint16_t nmi_vector_lsb {0xFFFA};
    constexpr uint16_t nmi_vector_msb {0xFFFB};
    constexpr uint16_t reset_vector_lsb {0xFFFC};
    constexpr uint16_t reset_vector_msb {0xFFFD};


    bool check_for_zero_flag(uint8_t reg)
    {
        return reg == 0x00;
    }

    bool check_for_negative_flag(uint8_t reg)
    {
        return reg >> 7;
    }

    bool check_for_flag_with_mask(uint16_t reg, uint16_t mask)
    {
        return (reg & mask) > 0;
    }

    bool check_for_page_crossing(uint16_t first_address, uint16_t second_address)
    {
        return (first_address & one_byte_overflow_mask) != (second_address & one_byte_overflow_mask);
    }

    bool check_for_sign_change(bool a, bool b, bool c)
    {
        return ((a && b) && !c) || (!(a || b) && c);
    }
}


/////////
// API //
/////////

CPU::CPU(PPU& ppu) : memory_bus{ppu} {}

void CPU::connect_bus_with_cartridge(std::shared_ptr<Cartridge> cartridge)
{
    memory_bus.insert_cartridge(cartridge);
}

void CPU::connect_bus_with_controller(std::shared_ptr<Controller> controller)
{
    memory_bus.connect_controller(controller);
}

void CPU::perform_cycle(bool debug_mode)
{
    status.flag.unused = 1;

    if (cycles_queued == 0) {
        next_instruction();

        if (debug_mode)
            log_debug_info();
    }
    else {
        cycles_queued--;
        cycles_executed++;
    }

    if (memory_bus.read_ppu_nmi_flag()) {
        memory_bus.clear_ppu_nmi_flag();
        interrupt_nmi();
    }
}

void CPU::hard_reset()
{
    acc = 0x00;
    x_reg = 0x00;
    y_reg = 0x00;
    stack_ptr = 0xFD;
    pc = read_reset_vector();
    status.word = 0x34;
    memory_bus.clear_memory();
}

void CPU::log_debug_info() const
{
    uint8_t debug_read_data {0x00};

    if (arg_address >= ppu_registers_space_start && arg_address < apu_and_io_space_start)
        debug_read_data = 0xAA;
    else
        debug_read_data = read_from_bus(arg_address);

    std::cout << "[DEBUG CPU] CYCLE: " << std::setw(10) << std::left << std::setfill(' ') << cycles_executed;
    std::cout << std::hex << std::uppercase << std::setfill('0')
        << " | OPCODE: 0x" << std::setw(2) << std::right << static_cast<short>(current_instruction.opcode)
        << " | ARG: 0x" << std::setw(4) << std::right << static_cast<short>(arg_address)
        << " | MEM[ARG]: 0x" << std::setw(2) << std::right << static_cast<short>(debug_read_data)
        << " || A: 0x" << std::setw(2) << std::right << static_cast<short>(acc)
        << " | X: 0x" << std::setw(2) << std::right << static_cast<short>(x_reg)
        << " | Y: 0x" << std::setw(2) << std::right << static_cast<short>(y_reg)
        << " | S: 0x" << std::setw(2) << std::right << static_cast<short>(stack_ptr)
        << " | PC: 0x" << std::setw(4) << std::right << static_cast<short>(pc)
        << " | P: 0x" << std::setw(2) << std::right << static_cast<short>(status.word);
}


////////////////////
// Bus management //
////////////////////

void CPU::write_to_bus(uint16_t address, uint8_t data)
{
    memory_bus.dispatch_write_to_device(address, data);
}

void CPU::stack_push(uint8_t data)
{
    write_to_bus(stack_offset + stack_ptr, data);
    stack_ptr--;
}

uint8_t CPU::read_from_bus(uint16_t address) const
{
    return memory_bus.dispatch_read_to_device(address);
}

uint8_t CPU::stack_pop()
{
    stack_ptr++;
    return read_from_bus(stack_offset + stack_ptr);
}

void CPU::next_instruction()
{
    const auto instruction_opcode {read_from_bus(pc)};
    pc++;

    current_instruction = decode_instruction_from_opcode(instruction_opcode);
    cycles_queued = current_instruction.cycles;

    execute_addressing_mode();
    execute_instruction();
}

//////////////////////////
// Instruction decoding //
//////////////////////////

Instruction CPU::decode_instruction_from_opcode(uint8_t opcode) const
{
    auto instruction_it = std::find_if(
        Lookup::instructions_table.begin(),
        Lookup::instructions_table.end(),
        [&] (const Instruction& instr) { return instr.opcode == opcode; }
        );

    return *instruction_it;
}

void CPU::execute_addressing_mode()
{
    using AM = Instruction::AddressingMode;
    switch (current_instruction.addressing_mode) {
        case AM::immediate:   addressing_mode_immediate();   break;
        case AM::zero_page:   addressing_mode_zero_page();   break;
        case AM::zero_page_x: addressing_mode_zero_page_x(); break;
        case AM::zero_page_y: addressing_mode_zero_page_y(); break;
        case AM::relative:    addressing_mode_relative();    break;
        case AM::absolute:    addressing_mode_absolute();    break;
        case AM::absolute_x:  addressing_mode_absolute_x();  break;
        case AM::absolute_y:  addressing_mode_absolute_y();  break;
        case AM::indirect:    addressing_mode_indirect();    break;
        case AM::indirect_x:  addressing_mode_indirect_x();  break;
        case AM::indirect_y:  addressing_mode_indirect_y();  break;
        default: break;
    }
}

void CPU::execute_instruction()
{
    using MN = Instruction::MnemonicName;
    switch (current_instruction.mnemonic) {
        case MN::ADC: ADC(); break;
        case MN::AND: AND(); break;
        case MN::ASL: ASL(); break;
        case MN::BCC: BCC(); break;
        case MN::BCS: BCS(); break;
        case MN::BEQ: BEQ(); break;
        case MN::BIT: BIT(); break;
        case MN::BMI: BMI(); break;
        case MN::BNE: BNE(); break;
        case MN::BPL: BPL(); break;
        case MN::BRK: BRK(); break;
        case MN::BVC: BVC(); break;
        case MN::BVS: BVS(); break;
        case MN::CLC: CLC(); break;
        case MN::CLD: CLD(); break;
        case MN::CLI: CLI(); break;
        case MN::CLV: CLV(); break;
        case MN::CMP: CMP(); break;
        case MN::CPX: CPX(); break;
        case MN::CPY: CPY(); break;
        case MN::DEC: DEC(); break;
        case MN::DEX: DEX(); break;
        case MN::DEY: DEY(); break;
        case MN::EOR: EOR(); break;
        case MN::INC: INC(); break;
        case MN::INX: INX(); break;
        case MN::INY: INY(); break;
        case MN::JMP: JMP(); break;
        case MN::JSR: JSR(); break;
        case MN::LDA: LDA(); break;
        case MN::LDX: LDX(); break;
        case MN::LDY: LDY(); break;
        case MN::LSR: LSR(); break;
        case MN::NOP: NOP(); break;
        case MN::ORA: ORA(); break;
        case MN::PHA: PHA(); break;
        case MN::PHP: PHP(); break;
        case MN::PLA: PLA(); break;
        case MN::PLP: PLP(); break;
        case MN::ROL: ROL(); break;
        case MN::ROR: ROR(); break;
        case MN::RTI: RTI(); break;
        case MN::RTS: RTS(); break;
        case MN::SBC: SBC(); break;
        case MN::SEC: SEC(); break;
        case MN::SED: SED(); break;
        case MN::SEI: SEI(); break;
        case MN::STA: STA(); break;
        case MN::STX: STX(); break;
        case MN::STY: STY(); break;
        case MN::TAX: TAX(); break;
        case MN::TAY: TAY(); break;
        case MN::TSX: TSX(); break;
        case MN::TXA: TXA(); break;
        case MN::TXS: TXS(); break;
        case MN::TYA: TYA(); break;
        default: ILL(); break;
    }
}


////////////////////////////
// Interrupts + branching //
////////////////////////////

uint16_t CPU::read_nmi_vector() const
{
    auto lsb {read_from_bus(nmi_vector_lsb)};
    auto msb {read_from_bus(nmi_vector_msb)};

    uint16_t address = (msb << 8) | lsb;

    return address;
}

uint16_t CPU::read_reset_vector() const
{
    auto lsb {read_from_bus(reset_vector_lsb)};
    auto msb {read_from_bus(reset_vector_msb)};

    uint16_t address = (msb << 8) | lsb;

    return address;
}

uint16_t CPU::read_irq_vector() const
{
    auto lsb {read_from_bus(irq_vector_lsb)};
    auto msb {read_from_bus(irq_vector_msb)};

    uint16_t address = (msb << 8) | lsb;

    return address;
}

void CPU::interrupt_nmi()
{
    process_interrupt();

    pc = read_nmi_vector();
}

void CPU::interrupt_irq()
{
    if (status.flag.interrupt == 1)
        return;

    process_interrupt();

    pc = read_irq_vector();
}

void CPU::interrupt_reset()
{
    stack_ptr -= 0x03;
    pc = read_reset_vector();
    status.flag.interrupt = 1;
}

void CPU::process_interrupt(bool brk_flag_state)
{
    const auto pc_lsb = static_cast<uint8_t>(pc & zero_page_mask);
    const auto pc_msb = static_cast<uint8_t>(pc >> 8);

    status.flag.brk = brk_flag_state;
    status.flag.unused = 1;
    status.flag.interrupt = 1;

    stack_push(pc_msb);
    stack_push(pc_lsb);
    stack_push(status.word);
}

void CPU::perform_branching()
{
    if (branch_offset & negative_flag_mask)
        branch_offset = branch_offset | one_byte_overflow_mask;

    const uint16_t new_pc = pc + branch_offset;

    if (check_for_page_crossing(pc, new_pc))
        cycles_queued += 2;
    else
        cycles_queued += 1;

    pc = new_pc;
}


//////////////////////
// Addressing modes //
//////////////////////

void CPU::addressing_mode_immediate()
{
    arg_address = pc;
    pc++;
}

void CPU::addressing_mode_zero_page()
{
    arg_address = read_from_bus(pc);
    pc++;

    arg_address = arg_address & zero_page_mask;
}

void CPU::addressing_mode_zero_page_x()
{
    arg_address = read_from_bus(pc) + x_reg;
    pc++;

    arg_address = arg_address & zero_page_mask;
}

void CPU::addressing_mode_zero_page_y()
{
    arg_address = read_from_bus(pc) + y_reg;
    pc++;

    arg_address = arg_address & zero_page_mask;
}

void CPU::addressing_mode_relative()
{
    branch_offset = read_from_bus(pc);
    arg_address = branch_offset;
    pc++;
}

void CPU::addressing_mode_absolute()
{
    auto lsb {read_from_bus(pc)};
    pc++;
    auto msb {read_from_bus(pc)};
    pc++;

    arg_address = (msb << 8) | lsb;
}

void CPU::addressing_mode_absolute_x()
{
    auto lsb {read_from_bus(pc)};
    pc++;
    auto msb {read_from_bus(pc)};
    pc++;

    uint16_t read_address = (msb << 8) | lsb;
    arg_address = read_address + x_reg;

    if (check_for_page_crossing(arg_address, read_address))
        cycles_queued += 1;

}

void CPU::addressing_mode_absolute_y()
{
    auto lsb {read_from_bus(pc)};
    pc++;
    auto msb {read_from_bus(pc)};
    pc++;

    uint16_t read_address = (msb << 8) | lsb;
    arg_address = read_address + y_reg;

    if (check_for_page_crossing(arg_address, read_address))
        cycles_queued += 1;
}

void CPU::addressing_mode_indirect()
{
    auto lsb {read_from_bus(pc)};
    pc++;
    auto msb {read_from_bus(pc)};
    pc++;

    uint16_t temp_address = (msb << 8) | lsb;

    // Original 6502 CPU's indirect jump page crossing bug reproduction:
    // https://www.nesdev.org/obelisk-6502-guide/reference.html#JMP
    if (lsb == 0xFF)
        msb = read_from_bus(temp_address & one_byte_overflow_mask);
    else
        msb = read_from_bus(temp_address + 1);

    lsb = read_from_bus(temp_address);

    arg_address = (msb << 8) | lsb;
}

void CPU::addressing_mode_indirect_x()
{
    const uint16_t temp_address = read_from_bus(pc) + x_reg;
    pc++;

    auto lsb {read_from_bus(temp_address & zero_page_mask)};
    auto msb {read_from_bus((temp_address + 1) & zero_page_mask)};

    arg_address = (msb << 8) | lsb;
}

void CPU::addressing_mode_indirect_y()
{
    const uint16_t temp_address = read_from_bus(pc);
    pc++;

    auto lsb {read_from_bus(temp_address & zero_page_mask)};
    auto msb {read_from_bus((temp_address + 1) & zero_page_mask)};

    const uint16_t read_address = (msb << 8) | lsb;
    arg_address = read_address + y_reg;

    if (check_for_page_crossing(arg_address, read_address))
        cycles_queued += 1;
}


//////////////////
// Instructions //
//////////////////

void CPU::ADC()
{
    const auto value {read_from_bus(arg_address)};
    const auto result = static_cast<uint16_t>(acc + value + status.flag.carry);

    const auto acc_sign {check_for_negative_flag(acc)};
    const auto value_sign {check_for_negative_flag(value)};
    const auto result_sign {check_for_negative_flag(static_cast<uint8_t>(result))};

    acc = static_cast<uint8_t>(result);

    status.flag.carry = check_for_flag_with_mask(result, one_byte_overflow_mask);
    status.flag.zero = check_for_zero_flag(acc);
    status.flag.overflow = check_for_sign_change(acc_sign, value_sign, result_sign);
    status.flag.negative = check_for_negative_flag(acc);
}

void CPU::AND()
{
    const auto value {read_from_bus(arg_address)};

    acc = acc & value;

    status.flag.zero = check_for_zero_flag(acc);
    status.flag.negative = check_for_negative_flag(acc);
}

void CPU::ASL()
{
    if (current_instruction.addressing_mode == Instruction::AddressingMode::accumulator) {
        status.flag.carry = check_for_flag_with_mask(acc, negative_flag_mask);

        acc = acc << 1;

        status.flag.zero = check_for_zero_flag(acc);
        status.flag.negative = check_for_negative_flag(acc);
    }
    else {
        auto result {read_from_bus(arg_address)};
        status.flag.carry = check_for_flag_with_mask(result, negative_flag_mask);

        result = result << 1;
        write_to_bus(arg_address, result);

        status.flag.zero = check_for_zero_flag(result);
        status.flag.negative = check_for_negative_flag(result);
    }
}

void CPU::BCC()
{
    if (status.flag.carry == 0)
        perform_branching();
}

void CPU::BCS()
{
    if (status.flag.carry == 1)
        perform_branching();
}

void CPU::BEQ()
{
    if (status.flag.zero == 1)
        perform_branching();
}

void CPU::BIT()
{
    const auto value {read_from_bus(arg_address)};
    const uint8_t result = acc & value;

    status.flag.zero = check_for_zero_flag(result);
    status.flag.overflow = check_for_flag_with_mask(value, overflow_flag_mask);
    status.flag.negative = check_for_negative_flag(value);
}

void CPU::BMI()
{
    if (status.flag.negative == 1)
        perform_branching();
}

void CPU::BNE()
{
    if (status.flag.zero == 0)
        perform_branching();
}

void CPU::BPL()
{
    if (status.flag.negative == 0)
        perform_branching();
}

void CPU::BRK()
{
    const bool brk_flag_state = 1;

    process_interrupt(brk_flag_state);

    pc = read_irq_vector();
}

void CPU::BVC()
{
    if (status.flag.overflow == 0)
        perform_branching();
}

void CPU::BVS()
{
    if (status.flag.overflow == 1)
        perform_branching();
}

void CPU::CLC()
{
    status.flag.carry = 0;
}

void CPU::CLD()
{
    status.flag.decimal = 0;
}

void CPU::CLI()
{
    status.flag.interrupt = 0;
}

void CPU::CLV()
{
    status.flag.overflow = 0;
}

void CPU::CMP()
{
    const auto value {read_from_bus(arg_address)};
    const uint8_t result = acc - value;

    status.flag.carry = acc >= value;
    status.flag.zero = check_for_zero_flag(result);
    status.flag.negative = check_for_negative_flag(result);
}

void CPU::CPX()
{
    const auto value {read_from_bus(arg_address)};
    const uint8_t result = x_reg - value;

    status.flag.carry = x_reg >= value;
    status.flag.zero = check_for_zero_flag(result);
    status.flag.negative = check_for_negative_flag(result);
}

void CPU::CPY()
{
    const auto value {read_from_bus(arg_address)};
    const uint8_t result = y_reg - value;

    status.flag.carry = y_reg >= value;
    status.flag.zero = check_for_zero_flag(result);
    status.flag.negative = check_for_negative_flag(result);
}

void CPU::DEC()
{
    auto value {read_from_bus(arg_address)};

    value--;
    write_to_bus(arg_address, value);

    status.flag.zero = check_for_zero_flag(value);
    status.flag.negative = check_for_negative_flag(value);
}

void CPU::DEX()
{
    x_reg--;

    status.flag.zero = check_for_zero_flag(x_reg);
    status.flag.negative = check_for_negative_flag(x_reg);
}

void CPU::DEY()
{
    y_reg--;

    status.flag.zero = check_for_zero_flag(y_reg);
    status.flag.negative = check_for_negative_flag(y_reg);
}

void CPU::EOR()
{
    const auto value {read_from_bus(arg_address)};

    acc = acc ^ value;

    status.flag.zero = check_for_zero_flag(acc);
    status.flag.negative = check_for_negative_flag(acc);
}

void CPU::INC()
{
    auto value {read_from_bus(arg_address)};

    value++;
    write_to_bus(arg_address, value);

    status.flag.zero = check_for_zero_flag(value);
    status.flag.negative = check_for_negative_flag(value);
}

void CPU::INX()
{
    x_reg++;

    status.flag.zero = check_for_zero_flag(x_reg);
    status.flag.negative = check_for_negative_flag(x_reg);
}

void CPU::INY()
{
    y_reg++;

    status.flag.zero = check_for_zero_flag(y_reg);
    status.flag.negative = check_for_negative_flag(y_reg);
}

void CPU::JMP()
{
    pc = arg_address;
}

void CPU::JSR()
{
    pc--;

    const auto pc_lsb = static_cast<uint8_t>(pc & zero_page_mask);
    const auto pc_msb = static_cast<uint8_t>(pc >> 8);

    stack_push(pc_msb);
    stack_push(pc_lsb);

    pc = arg_address;
}

void CPU::LDA()
{
    acc = read_from_bus(arg_address);

    status.flag.zero = check_for_zero_flag(acc);
    status.flag.negative = check_for_negative_flag(acc);
}

void CPU::LDX()
{
    x_reg = read_from_bus(arg_address);

    status.flag.zero = check_for_zero_flag(x_reg);
    status.flag.negative = check_for_negative_flag(x_reg);
}

void CPU::LDY()
{
    y_reg = read_from_bus(arg_address);

    status.flag.zero = check_for_zero_flag(y_reg);
    status.flag.negative = check_for_negative_flag(y_reg);
}

void CPU::LSR()
{
    if (current_instruction.addressing_mode == Instruction::AddressingMode::accumulator) {
        status.flag.carry = check_for_flag_with_mask(acc, carry_flag_mask);

        acc = acc >> 1;

        status.flag.zero = check_for_zero_flag(acc);
        status.flag.negative = check_for_negative_flag(acc);
    }
    else {
        auto result {read_from_bus(arg_address)};
        status.flag.carry = check_for_flag_with_mask(result, carry_flag_mask);

        result = result >> 1;
        write_to_bus(arg_address, result);

        status.flag.zero = check_for_zero_flag(result);
        status.flag.negative = check_for_negative_flag(result);
    }
}

void CPU::NOP() {}

void CPU::ORA()
{
    const auto value {read_from_bus(arg_address)};

    acc = acc | value;

    status.flag.zero = check_for_zero_flag(acc);
    status.flag.negative = check_for_negative_flag(acc);
}

void CPU::PHA()
{
    stack_push(acc);
}

void CPU::PHP()
{
    status.flag.brk = 1;
    status.flag.unused = 1;

    stack_push(status.word);

    status.flag.brk = 0;
}

void CPU::PLA()
{
    acc = stack_pop();

    status.flag.zero = check_for_zero_flag(acc);
    status.flag.negative = check_for_negative_flag(acc);
}

void CPU::PLP()
{
    status.word = stack_pop();
    status.flag.brk = 0;
}

void CPU::ROL()
{
    const bool old_carry = status.flag.carry;

    if (current_instruction.addressing_mode == Instruction::AddressingMode::accumulator) {
        status.flag.carry = check_for_flag_with_mask(acc, negative_flag_mask);

        acc = acc << 1;
        acc = acc | old_carry;

        status.flag.zero = check_for_zero_flag(acc);
        status.flag.negative = check_for_negative_flag(acc);
    }
    else {
        auto result {read_from_bus(arg_address)};
        status.flag.carry = check_for_flag_with_mask(result, negative_flag_mask);

        result = result << 1;
        result = result | old_carry;
        write_to_bus(arg_address, result);

        status.flag.zero = check_for_zero_flag(result);
        status.flag.negative = check_for_negative_flag(result);
    }
}

void CPU::ROR()
{
    const bool old_carry = status.flag.carry;

    if (current_instruction.addressing_mode == Instruction::AddressingMode::accumulator) {
        status.flag.carry = check_for_flag_with_mask(acc, carry_flag_mask);

        acc = acc >> 1;
        acc = acc | (old_carry << 7);

        status.flag.zero = check_for_zero_flag(acc);
        status.flag.negative = check_for_negative_flag(acc);
    }
    else {
        auto result {read_from_bus(arg_address)};
        status.flag.carry = check_for_flag_with_mask(result, carry_flag_mask);

        result = result >> 1;
        result = result | (old_carry << 7);
        write_to_bus(arg_address, result);

        status.flag.zero = check_for_zero_flag(result);
        status.flag.negative = check_for_negative_flag(result);
    }
}

void CPU::RTI()
{
    status.word = stack_pop();

    status.flag.brk = 0;
    status.flag.unused = 0;

    auto pc_lsb {stack_pop()};
    auto pc_msb {stack_pop()};

    pc = (pc_msb << 8) | pc_lsb;
}

void CPU::RTS()
{
    auto pc_lsb {stack_pop()};
    auto pc_msb {stack_pop()};

    pc = (pc_msb << 8) | pc_lsb;
    pc++;
}

void CPU::SBC()
{
    auto value {read_from_bus(arg_address)};
    value = static_cast<uint8_t>(~value);

    const auto result = static_cast<uint16_t>(acc + value + status.flag.carry);

    const auto acc_sign {check_for_negative_flag(acc)};
    const auto value_sign {check_for_negative_flag(value)};
    const auto result_sign {check_for_negative_flag(static_cast<uint8_t>(result))};

    acc = static_cast<uint8_t>(result);

    status.flag.carry = check_for_flag_with_mask(result, one_byte_overflow_mask);
    status.flag.zero = check_for_zero_flag(acc);
    status.flag.overflow = check_for_sign_change(acc_sign, value_sign, result_sign);
    status.flag.negative = check_for_negative_flag(acc);
}

void CPU::SEC()
{
    status.flag.carry = 1;
}

void CPU::SED()
{
    status.flag.decimal = 1;
}

void CPU::SEI()
{
    status.flag.interrupt = 1;
}

void CPU::STA()
{
    write_to_bus(arg_address, acc);
}

void CPU::STX()
{
    write_to_bus(arg_address, x_reg);
}

void CPU::STY()
{
    write_to_bus(arg_address, y_reg);
}

void CPU::TAX()
{
    x_reg = acc;

    status.flag.zero = check_for_zero_flag(x_reg);
    status.flag.negative = check_for_negative_flag(x_reg);
}

void CPU::TAY()
{
    y_reg = acc;

    status.flag.zero = check_for_zero_flag(y_reg);
    status.flag.negative = check_for_negative_flag(y_reg);
}

void CPU::TSX()
{
    x_reg = stack_ptr;

    status.flag.zero = check_for_zero_flag(x_reg);
    status.flag.negative = check_for_negative_flag(x_reg);
}

void CPU::TXA()
{
    acc = x_reg;

    status.flag.zero = check_for_zero_flag(acc);
    status.flag.negative = check_for_negative_flag(acc);
}

void CPU::TXS()
{
    stack_ptr = x_reg;
}

void CPU::TYA()
{
    acc = y_reg;

    status.flag.zero = check_for_zero_flag(acc);
    status.flag.negative = check_for_negative_flag(acc);
}

void CPU::ILL() {}
