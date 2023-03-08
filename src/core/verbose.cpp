/** File Name:       verbose.cpp
 *  Author:          Darian Benam <darian@darianbenam.com>
 *  Date Created:    Friday, March 3, 2023 */

#include "../../include/core/verbose.hpp"
#include <iomanip>
#include <iostream>
#if _WIN32
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#endif

void honeycomb::print_verbose_message(honeycomb::verbose_message_type type, std::string const& tag, std::string const& message, bool printMessage)
{
    if (!printMessage)
    {
        return;
    }

#if _WIN32
    HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);

    if (hStdOut == INVALID_HANDLE_VALUE)
    {
        return;
    }

    DWORD dwCurrentConsoleMode = 0;

    if (GetConsoleMode(hStdOut, &dwCurrentConsoleMode))
    {
        if (!(dwCurrentConsoleMode & ENABLE_VIRTUAL_TERMINAL_PROCESSING))
        {
            DWORD dwConsoleMode = 0;

            if (!GetConsoleMode(hStdOut, &dwConsoleMode))
            {
                return;
            }

            dwConsoleMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;

            if (!SetConsoleMode(hStdOut, dwConsoleMode))
            {
                return;
            }
        }
    }
#endif

    std::cout << get_verbose_message_type_ansi_color(type) << ' ' << tag << " \u001b[0m " << message << '\n';
}
