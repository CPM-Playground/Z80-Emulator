/**

    @file      memory.h
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

#include "z80_memory_types.h"

namespace z80 {


    template<address_t BEGIN, address_t END>
    class memory {

        using byte_array_t = std::array<byte_t, END - BEGIN + 1>;
        using byte_array_ptr_t = std::unique_ptr<byte_array_t>;

    public:

        memory() : bytes(new byte_array_t{}) {
            randomize();
        }

        memory(byte_t b) : bytes(new byte_array_t{}) {
            fill(b);
        }

        memory(const std::string& filename) : bytes(new byte_array_t{}) {
            load(filename);
        }

        inline byte_t operator[](address_t addr) const {
            return bytes->at(addr - BEGIN);
        }

        inline byte_t& operator[](address_t addr) {
            return bytes->at(addr - BEGIN);
        }

        void dump(address_t begin = BEGIN, address_t end = END + 1) const {
            auto dump_size = end - begin;
            if (dump_size > size()) {
                throw std::runtime_error(std::format(" memory overflow: requested dump size {} bytes larger than memory size {} bytes", dump_size, size()));
            }
            for (auto i{ begin }; i < end; i += 16) {
                dump_paragraph(i);
            }
        }

        void dump_paragraph(address_t addr) const {
            std::cout << std::format("${:04X} ", addr);
            addr -= BEGIN;
            for (auto i{ 0 }; i < 16; ++i) {
                std::cout << std::format("{:02X} ", (uint8_t)bytes->at(addr + i));
            }
            std::cout << "| ";
            for (auto i{ 0 }; i < 16; ++i) {
                char c = bytes->at(addr + i);
                if ((c == 127) || (c >= 0) && (c < 32)) std::cout << '.';
                else std::cout << c;
            }
            std::cout << " |\n";
        }

        void fill(byte_t b, address_t begin = BEGIN, address_t end = END + 1) {
            end -= begin;
            begin -= BEGIN;
            auto fill_size = end - begin;
            if (fill_size > size()) {
                throw std::runtime_error(std::format(" memory overflow: requested fill size {} bytes larger than memory size {} bytes", fill_size, size()));
            }
            for (auto i{ 0 }; i < end; ++i) {
                bytes->at(begin + i) = b;
            }
        }

        void load(const std::string& filename) {
            const std::filesystem::path fpath(filename);
            if (!std::filesystem::exists(fpath)) {
                throw std::runtime_error(fpath.string() + " file not found");
            }
            std::ifstream f;
            auto file_size = std::filesystem::file_size(fpath);
            if (file_size < size()) {
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

        void save(const std::string& filename, address_t begin = BEGIN, address_t end = END + 1) const {
            auto save_size = end - begin;
            begin -= BEGIN;
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
                throw std::runtime_error(fpath.string() + " file already exists");
            }
        }

        size_t static size() {
            return END - BEGIN + 1;
        }

    private:

        byte_array_ptr_t bytes;

        static std::mt19937 rand;
        static std::uniform_int_distribution<std::mt19937::result_type> distribution;

    };

     template<address_t BEGIN, address_t END>
     std::mt19937 memory<BEGIN, END>::rand = std::mt19937{};

     template<address_t BEGIN, address_t END>
     std::uniform_int_distribution<std::mt19937::result_type> memory<BEGIN, END>::distribution = std::uniform_int_distribution<std::mt19937::result_type>{};

}