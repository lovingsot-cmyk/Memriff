#pragma once
#include <windows.h>
#include <tlhelp32.h>
#include <vector>
#include <string>

namespace memriff {

    // handling
    
    bool attach(const wchar_t* name, DWORD permissions = PROCESS_ALL_ACCESS);
    bool attach(DWORD id, DWORD permissions = PROCESS_ALL_ACCESS);
    void detach();
    
    DWORD pid();
    HANDLE handle();
    
    uintptr_t module(const wchar_t* name);
    
    // memory read
    
    template<typename T>
    T get(uintptr_t address) {
        T buffer{};
        ReadProcessMemory(handle(), (LPCVOID)address, &buffer, sizeof(T), nullptr);
        return buffer;
    }
    
    std::vector<uint8_t> get_bytes(uintptr_t address, size_t size);
    std::string get_string(uintptr_t address, size_t max_len = 64);
    
    // memory write
    
    template<typename T>
    bool set(uintptr_t address, T value) {
        return WriteProcessMemory(handle(), (LPVOID)address, &value, sizeof(T), nullptr);
    }
    
    bool set_bytes(uintptr_t address, const std::vector<uint8_t>& data);
    bool set_string(uintptr_t address, const std::string& str);
    
    // pointer chains
    
    uintptr_t follow(uintptr_t base, const std::vector<uintptr_t>& offsets);
    
    // scanning the patten
    
    uintptr_t scan(uintptr_t module_base, size_t module_size, const std::string& pattern);
    uintptr_t scan_global(const std::string& pattern);
    
    // dll injection
    
    uintptr_t load(const std::wstring& dll_path);
    bool unload(uintptr_t dll_base);
}