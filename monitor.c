#include <stdio.h>
#include <windows.h>

#pragma comment(lib, "kernel32.lib")

// -------------------------------
// CPU USAGE
// -------------------------------
double get_cpu_usage() {
    static ULARGE_INTEGER last_idle = {0}, last_kernel = {0}, last_user = {0};

    FILETIME idle_time, kernel_time, user_time;
    ULARGE_INTEGER idle, kernel, user;

    if (!GetSystemTimes(&idle_time, &kernel_time, &user_time))
        return -1.0;

    idle.LowPart   = idle_time.dwLowDateTime;
    idle.HighPart  = idle_time.dwHighDateTime;

    kernel.LowPart  = kernel_time.dwLowDateTime;
    kernel.HighPart = kernel_time.dwHighDateTime;

    user.LowPart  = user_time.dwLowDateTime;
    user.HighPart = user_time.dwHighDateTime;

    if (last_idle.QuadPart == 0) {
        last_idle = idle;
        last_kernel = kernel;
        last_user = user;
        return 0.0;
    }

    ULONGLONG idle_diff   = idle.QuadPart   - last_idle.QuadPart;
    ULONGLONG kernel_diff = kernel.QuadPart - last_kernel.QuadPart;
    ULONGLONG user_diff   = user.QuadPart   - last_user.QuadPart;

    ULONGLONG total = kernel_diff + user_diff;

    last_idle = idle;
    last_kernel = kernel;
    last_user = user;

    if (total == 0) return 0.0;

    return (double)(total - idle_diff) * 100.0 / total;
}

// -------------------------------
// MEMORY USAGE
// -------------------------------
void get_memory_usage(DWORDLONG *total, DWORDLONG *free) {
    MEMORYSTATUSEX mem;
    mem.dwLength = sizeof(mem);

    if (GlobalMemoryStatusEx(&mem)) {
        *total = mem.ullTotalPhys;
        *free  = mem.ullAvailPhys;
    } else {
        *total = *free = 0;
    }
}

// -------------------------------
// CPU CORES
// -------------------------------
int get_cpu_cores() {
    SYSTEM_INFO sysinfo;
    GetSystemInfo(&sysinfo);
    return sysinfo.dwNumberOfProcessors;
}

// -------------------------------
// MAIN
// -------------------------------
int main() {
    printf("Monitor de Sistema - Windows (CPU, RAM, Cores)\n");

    int cores = get_cpu_cores();

    while (1) {
        double cpu = get_cpu_usage();

        DWORDLONG mem_total, mem_free;
        get_memory_usage(&mem_total, &mem_free);

        system("cls");

        printf("=== MONITOR DE SISTEMA ===\n\n");

        printf("CPU: %.2f%%\n", cpu);
        printf("Nucleos: %d\n\n", cores);

        printf("RAM Total: %.2f GB\n", mem_total / (1024.0 * 1024 * 1024));
        printf("RAM Livre: %.2f GB\n", mem_free  / (1024.0 * 1024 * 1024));
        printf("Uso da RAM: %.2f%%\n\n",
               100.0 * (mem_total - mem_free) / mem_total);

        Sleep(1000);
    }

    return 0;
}
