#pragma once
// by Tony Van Eerd
#include <mutex>
#include <iostream>

std::mutex outMu;

template <typename T0, typename T1, typename T2>
void out(T0 const& t0, T1 const& t1, T2 const& t2)
{
    std::lock_guard<std::mutex> lock(outMu);
    std::cout << t0 << ' ' << t1 << ' ' << t2 << '\n';
}
template <typename T0, typename T1>
void out(T0 const& t0, T1 const& t1)
{
    std::lock_guard<std::mutex> lock(outMu);
    std::cout << t0 << ' ' << t1 << '\n';
}
template <typename T0>
void out(T0 const& t0)
{
    std::lock_guard<std::mutex> lock(outMu);
    std::cout << t0 << '\n';
}
template <typename T0, typename T1>
void lout(T0 const& t0, T1 const& t1)
{
    out(">", t0, t1);
}
template <typename T0>
void lout(T0 const& t0)
{
    out(">", t0);
}