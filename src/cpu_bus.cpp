#include "../include/cpu_bus.h"

#include "../include/cartridge.h"
#include "../include/ppu.h"


namespace
{
    constexpr size_t   cpu_ram_bank_size {2048};
    constexpr uint16_t cpu_ram_upper_bound {0x1FFF};
    constexpr uint16_t apu_and_io_space_start {0x4000};
    constexpr uint16_t ppu_registers_space_start {0x2000};
    constexpr uint16_t prg_ram_space_start {0x6000};
    constexpr uint16_t prg_rom_space_start {0x8000};
}


CPUBus::CPUBus(PPU& ppu) : ppu_ref{ppu} {};

void CPUBus::insert_cartridge(std::shared_ptr<Cartridge> cartridge)
{
    cartridge_ptr = cartridge;
}

void CPUBus::clear_memory()
{
    cpu_ram.fill(0x00);
}

void CPUBus::dispatch_write_to_device(uint16_t address, uint8_t data)
{
    if (address >= ppu_registers_space_start && address < apu_and_io_space_start)
        send_write_to_ppu(address, data);
    else if (address >= prg_ram_space_start && address < prg_rom_space_start)
        send_write_to_mapper_prg_ram(address, data);
    else if (address >= prg_rom_space_start)
        send_write_to_mapper_prg_rom(address, data);
    else
        cpu_ram_write(address, data);
}

uint8_t CPUBus::dispatch_read_to_device(uint16_t address) const
{
    if (address >= ppu_registers_space_start && address < apu_and_io_space_start)
        return send_read_to_ppu(address);
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


void CPUBus::send_write_to_ppu(uint16_t address, uint8_t data) const
{
    ppu_ref.handle_write_from_cpu(address, data);
}

void CPUBus::send_write_to_mapper_prg_ram(uint16_t address, uint8_t data) const
{
    cartridge_ptr.lock()->mapper.map_prg_ram_write(address, data);
}

void CPUBus::send_write_to_mapper_prg_rom(uint16_t address, uint8_t data) const
{
    cartridge_ptr.lock()->mapper.map_prg_rom_write(address, data);
}

void CPUBus::cpu_ram_write(uint16_t address, uint8_t data)
{
    if (address <= cpu_ram_upper_bound)
        cpu_ram.at(address % cpu_ram_bank_size) = data;
    else
        cpu_ram.at(address) = data;
}

uint8_t CPUBus::send_read_to_ppu(uint16_t address) const
{
    return ppu_ref.handle_read_from_cpu(address);
}

uint8_t CPUBus::send_read_to_mapper_prg_ram(uint16_t address) const
{
    return cartridge_ptr.lock()->mapper.map_prg_ram_read(address);
}

uint8_t CPUBus::send_read_to_mapper_prg_rom(uint16_t address) const
{
    return cartridge_ptr.lock()->mapper.map_prg_rom_read(address);
}

uint8_t CPUBus::cpu_ram_read(uint16_t address) const
{
    if (address <= cpu_ram_upper_bound)
        return cpu_ram.at(address % cpu_ram_bank_size);

    return cpu_ram.at(address);
}
