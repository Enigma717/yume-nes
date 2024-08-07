#include "../../include/cpu/cpu_bus.h"

#include "../../include/cartridge/cartridge.h"
#include "../../include/ppu/ppu.h"
#include "../../include/system/controller.h"

namespace
{
    constexpr std::size_t cpu_ram_bank_size {2048uz};

    constexpr std::uint16_t cpu_ram_upper_bound {0x1FFFu};
    constexpr std::uint16_t apu_and_io_space_start {0x4000u};
    constexpr std::uint16_t controller_address {0x4016u};
    constexpr std::uint16_t ppu_registers_space_start {0x2000u};
    constexpr std::uint16_t prg_ram_space_start {0x6000u};
    constexpr std::uint16_t prg_rom_space_start {0x8000u};
}

/////////
// API //
/////////

CPUBus::CPUBus(PPU& ppu) : ppu_ref{ppu} {};

void CPUBus::insert_cartridge(std::shared_ptr<Cartridge> cartridge)
{
    cartridge_ptr = cartridge;
}

void CPUBus::connect_controller(std::shared_ptr<Controller> controller)
{
    controller_ptr = controller;
}

void CPUBus::clear_memory()
{
    cpu_ram.fill(0x00u);
}

void CPUBus::dispatch_write_to_device(std::uint16_t address, std::uint8_t data)
{
    if (address >= ppu_registers_space_start && address < apu_and_io_space_start)
        send_write_to_ppu(address, data);
    else if (address == controller_address)
        send_write_to_controller(data);
    else if (address >= prg_ram_space_start && address < prg_rom_space_start)
        send_write_to_mapper_prg_ram(address, data);
    else if (address >= prg_rom_space_start)
        return;
    else
        cpu_ram_write(address, data);
}

std::uint8_t CPUBus::dispatch_read_to_device(std::uint16_t address) const
{
    if (address >= ppu_registers_space_start && address < apu_and_io_space_start)
        return send_read_to_ppu(address);
    else if (address == controller_address)
        return send_read_to_controller();
    else if (address >= prg_ram_space_start && address < prg_rom_space_start)
        return send_read_to_mapper_prg_ram(address);
    else if (address >= prg_rom_space_start)
        return send_read_to_mapper_prg_rom(address);
    else
        return cpu_ram_read(address);
}

bool CPUBus::read_ppu_nmi_flag() const
{
    return ppu_ref.force_nmi_in_cpu;
}

void CPUBus::clear_ppu_nmi_flag() const
{
    ppu_ref.force_nmi_in_cpu = false;
}


///////////////////
// Write methods //
///////////////////

void CPUBus::send_write_to_ppu(std::uint16_t address, std::uint8_t data) const
{
    ppu_ref.handle_register_write_from_cpu(address, data);
}

void CPUBus::send_write_to_controller(std::uint8_t data) const
{
    if (!controller_ptr.lock()->handle_state_write(data))
        ppu_ref.app_screen.close();
}

void CPUBus::send_write_to_mapper_prg_ram(std::uint16_t address, std::uint8_t data) const
{
    cartridge_ptr.lock()->mapper.map_prg_ram_write(address, data);
}

void CPUBus::cpu_ram_write(std::uint16_t address, std::uint8_t data)
{
    if (address <= cpu_ram_upper_bound)
        cpu_ram[address % cpu_ram_bank_size] = data;
    else
        cpu_ram[address] = data;
}


//////////////////
// Read methods //
//////////////////

std::uint8_t CPUBus::send_read_to_ppu(std::uint16_t address) const
{
    return ppu_ref.handle_register_read_from_cpu(address);
}

std::uint8_t CPUBus::send_read_to_controller() const
{
    return controller_ptr.lock()->handle_state_read();
}

std::uint8_t CPUBus::send_read_to_mapper_prg_ram(std::uint16_t address) const
{
    return cartridge_ptr.lock()->mapper.map_prg_ram_read(address);
}

std::uint8_t CPUBus::send_read_to_mapper_prg_rom(std::uint16_t address) const
{
    return cartridge_ptr.lock()->mapper.map_prg_rom_read(address);
}

std::uint8_t CPUBus::cpu_ram_read(std::uint16_t address) const
{
    if (address <= cpu_ram_upper_bound)
        return cpu_ram[address % cpu_ram_bank_size];

    return cpu_ram[address];
}
