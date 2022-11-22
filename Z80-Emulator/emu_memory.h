/**

    @file      emu_memory.h
    @brief     emulates a block of memory bytes of any size and address location
    @details   as far as teh Z80 emulator is concerned the memory block emulator need only provide 
               the const and non-const array accessors:
               + byte_t operator[](address_t addr) const
               + byte_t& operator[](address_t addr)
    @author    ifknot
    @date      12.11.2022
    @copyright © ifknot, 2022. All right reserved.

**/
#pragma once

#include <array>
#include <filesystem>
#include <format>
#include <fstream>
#include <iostream>
#include <memory>
#include <random>
#include <string>

#include "emu_memory_types.h"

namespace emu {


    template<size_t SIZE>
    class memory {

        using byte_array_t = std::array<byte_t, SIZE>;
        using byte_array_ptr_t = std::unique_ptr<byte_array_t>;

        static constexpr char ASCII_NULL = 0;
        static constexpr char ASCII_SPACE = 32;
        static constexpr char ASCII_DEL = 127;

        static constexpr auto PARAGRAPH = 16;

    public:

        memory(address_t addr) :
            begin_(addr),
            end_(addr + SIZE - 1),
            column_count((size() < PARAGRAPH) ? size() : PARAGRAPH),
            bytes(new byte_array_t{})
        {
            randomize();
        }

        memory(address_t addr, byte_t b) :
            memory(addr)
        {
            fill(b);
        }

        memory(address_t addr, const std::string& filename) :
            memory(addr)
        {
            load(filename);
        }

        inline byte_t operator[](address_t addr) const {
            return bytes->at((size_t)addr - address_begin());
        }

        inline byte_t& operator[](address_t addr) {
            return bytes->at((size_t)addr - address_begin());
        }

        inline address_t address_begin() const {
            return begin_;
        }

        inline address_t address_end() const {
            return end_;
        }

        void dump() const {
            for (auto i{ address_begin()}; i < address_end() + 1; i += PARAGRAPH) {
                dump_paragraph(i);
            }
        }

        void dump(address_t begin, address_t end) const {
            auto dump_size = end - begin;
            if (dump_size > size()) {
                throw std::runtime_error(std::format(" memory overflow: requested dump size {} bytes larger than memory size {} bytes", dump_size, size()));
            }
            for (auto i{ begin }; i < end + 1; i += PARAGRAPH) {
                dump_paragraph(i);
            }
        }

        void dump_paragraph(address_t addr) const {
            std::cout << std::format("${:04X} ", addr);
            addr -= address_begin();
            for (address_t i{ 0 }; i < column_count; ++i) {
                std::cout << std::format("{:02X} ", (uint8_t)bytes->at((size_t)addr + i));
            }
            std::cout << "| ";
            for (address_t i{ 0 }; i < column_count; ++i) {
                char c = bytes->at((size_t)addr + i);
                if ((c == ASCII_DEL) || (c >= ASCII_NULL) && (c < ASCII_SPACE)) std::cout << '.';
                else std::cout << c;
            }
            std::cout << " |\n";
        }

        void fill(byte_t b) {
            for (auto addr{ 0 }; addr < size(); ++addr) {
                bytes->at(addr) = b;
            }
        }

        void fill(byte_t b, address_t begin, address_t end) {
            end -= begin;
            begin -= address_begin();
            auto fill_size = end + 1;
            if (fill_size > size()) {
                throw std::runtime_error(std::format(" memory overflow: requested fill size {} bytes larger than memory size {} bytes", fill_size, size()));
            }
            for (auto i{ begin }; i < fill_size; ++i) {
                bytes->at((size_t)begin++) = b;
            }
        }

        void load(const std::string& filename) {
            const std::filesystem::path fpath(filename);
            if (!std::filesystem::exists(fpath)) {
                throw std::runtime_error("file load error: \"" + fpath.string() + "\" file not found");
            }
            std::ifstream f;
            auto file_size = std::filesystem::file_size(fpath);
            if (file_size > size()) {
                throw std::runtime_error(fpath.string() + std::format(" memory overflow: file size {} bytes larger than memory size {} bytes", file_size, size()));
            }
            f.open(fpath, std::ios::binary);
            f.read((char*)bytes->data(), size());
            f.close();
        }

        void randomize(uint32_t min = 0, uint32_t max = 255) {
            for (auto addr{ 0 }; addr < size(); ++addr) {
                bytes->at(addr) = min + (distribution(rand) % (max - min + 1));
            }
        }

        void save(const std::string& filename) const {
            save(filename, address_begin(), address_end());
        }

        void save(const std::string& filename, address_t begin, address_t end) const {
            auto save_size = end - begin + 1;
            begin -= address_begin();
            if (save_size > size()) {
                throw std::runtime_error(std::format(" memory overflow: requested save size {} bytes larger than memory size {} bytes", save_size, size()));
            }
            const std::filesystem::path fpath(filename);
            if (!std::filesystem::exists(fpath)) {
                std::ofstream f;
                f.open(fpath, std::ios::binary);
                f.write((char*)(bytes->data() + begin), save_size);
                f.close();
            }
            else {
                throw std::runtime_error("file save error: \"" + fpath.string() + "\" file already exists");
            }
        }

        static inline size_t size() {
            return SIZE;
        }

    private:

        address_t begin_;
        address_t end_;

        size_t column_count;

        byte_array_ptr_t bytes;

        static std::mt19937 rand;
        static std::uniform_int_distribution<std::mt19937::result_type> distribution;

    };

     template<size_t SIZE>
     std::mt19937 memory<SIZE>::rand = std::mt19937{};

     template<size_t SIZE>
     std::uniform_int_distribution<std::mt19937::result_type> memory<SIZE>::distribution = std::uniform_int_distribution<std::mt19937::result_type>{};

}