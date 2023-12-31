#pragma once

#include <array>
#include <cstdint>
#include <memory>


class Cartridge;
class Controller;
class PPU;

namespace CPUBusConsts
{
    constexpr size_t memory_size {24576};
}


class CPUBus {
public:
    CPUBus() = delete;
    CPUBus(PPU& ppu);


    void insert_cartridge(std::shared_ptr<Cartridge> cartridge);
    void connect_controller(std::shared_ptr<Controller> controller);
    void clear_memory();

    void    dispatch_write_to_device(uint16_t address, uint8_t data);
    uint8_t dispatch_read_to_device(uint16_t address) const;

    bool read_ppu_nmi_flag() const;
    void clear_ppu_nmi_flag() const;

private:
    using CartridgePtr = std::weak_ptr<Cartridge>;
    using ControllerPtr = std::weak_ptr<Controller>;
    using CpuRamMemory = std::array<uint8_t, CPUBusConsts::memory_size>;

    CpuRamMemory cpu_ram {};
    CartridgePtr cartridge_ptr {};
    ControllerPtr controller_ptr {};
    PPU& ppu_ref;


    void send_write_to_ppu(uint16_t address, uint8_t data) const;
    void send_write_to_controller(uint8_t data) const;
    void send_write_to_mapper_prg_ram(uint16_t address, uint8_t data) const;
    void cpu_ram_write(uint16_t address, uint8_t data);

    uint8_t send_read_to_ppu(uint16_t address) const;
    uint8_t send_read_to_controller() const;
    uint8_t send_read_to_mapper_prg_ram(uint16_t address) const;
    uint8_t send_read_to_mapper_prg_rom(uint16_t address) const;
    uint8_t cpu_ram_read(uint16_t address) const;
};
