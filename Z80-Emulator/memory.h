/**

    @file      memory.h
    @brief     
    @details   ~
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

#include "memory_types.h"

namespace z80 {


    template<address_t BEGIN, address_t END>
    class memory {

        using byte_array = std::array<byte_t, END - BEGIN + 1>;
        using mem = std::unique_ptr<byte_array>;

    public:

        memory() : bytes(new byte_array{}) {
            randomize();
        }

        memory(const std::string& filename) : bytes(new byte_array{}) {
            load(filename);
        }

        inline byte_t operator[](address_t addr) const {
            return bytes->at(addr - BEGIN);
        }

        inline byte_t& operator[](address_t addr) {
            return bytes->at(addr - BEGIN);
        }

        void dump(address_t begin = BEGIN, address_t end = END + 1) const {
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

        void fill(address_t begin, address_t end, byte_t b) {
            end -= begin;
            begin -= BEGIN;
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
            auto fsize = std::filesystem::file_size(fpath);
            if (fsize < size()) {
                throw std::runtime_error(fpath.string() + std::format(" file size {} bytes smaller than memory size {} bytes", fsize, size()));
            }
            f.open(fpath, std::ios::binary);
            f.read((char*)bytes->data(), size());
            f.close();
        }

        void randomize() {
            for (auto addr{ 0 }; addr < size(); ++addr) {
                bytes->at(addr) = distribution(rand) % 255;
            }
        }

        size_t static size() {
            return END - BEGIN + 1;
        }

    private:

        mem bytes;

        std::mt19937 rand;
        std::uniform_int_distribution<std::mt19937::result_type> distribution;

    };

}