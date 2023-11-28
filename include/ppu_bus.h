#pragma once

#include "../include/cartridge.h"

#include <array>
#include <cstdint>
#include <memory>


namespace PPUBusConsts
{
    constexpr size_t oam_size {64};
    constexpr size_t vram_size {2048};
    constexpr size_t palettes_ram_size {32};
}


class PPUBus {
public:
    void insert_cartridge(std::shared_ptr<Cartridge> cartridge);
    void clear_memory();

    void    dispatch_write_to_device(uint16_t address, uint8_t data);
    uint8_t dispatch_read_to_device(uint16_t address) const;

private:
    struct OAMEntry {
        uint8_t position_y {0x00};
        uint8_t tile_index {0x00};
        uint8_t attributes {0x00};
        uint8_t position_x {0x00};
    };

    using CartridgePtr = std::weak_ptr<Cartridge>;
    using OamMemory    = std::array<OAMEntry, PPUBusConsts::oam_size>;
    using VRamMemory   = std::array<uint8_t, PPUBusConsts::vram_size>;
    using PalettesRam  = std::array<uint8_t, PPUBusConsts::palettes_ram_size>;

    CartridgePtr cartridge_ptr {};
    Cartridge::MirroringType current_mirroring_mode {};


    OamMemory   oam          {};
    VRamMemory  vram         {};
    PalettesRam palettes_ram {};


    void process_vram_write(uint16_t address, uint8_t data);
    void process_palettes_ram_write(uint16_t address, uint8_t data);

    uint8_t send_read_to_mapper_chr_rom(uint16_t address) const;
    uint8_t process_vram_read(uint16_t address) const;
    uint8_t process_palettes_ram_read(uint16_t address) const;

    uint16_t normalize_vram_address(uint16_t address) const;
    uint16_t normalize_palettes_address(uint16_t address, bool is_reading = false) const;
    bool     check_for_palette_mirroring(uint16_t address) const;
    bool     check_for_background_read(uint16_t address) const;
};
