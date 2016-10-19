//
// Copyright(c) 2016 Alexander Dalshov.
// Distributed under the MIT License (http://opensource.org/licenses/MIT)
//

#pragma once

#if defined(_MSC_VER)

#include <spdlog/sinks/base_sink.h>
#include <spdlog/details/null_mutex.h>

#include <mutex>
#include <string>

namespace spdlog
{
namespace sinks
{
/*
* Maxon C4D sink (logging using GePrint)
*/
template<class Mutex>
class c4d_sink : public base_sink < Mutex >
{
public:
    explicit c4d_sink() { }
    void flush() override { }

protected:
    void _sink_it(const details::log_msg& msg) override {
        GePrint(String(msg.formatted.c_str(), STRINGENCODING_UTF8));
    }
};

typedef c4d_sink<std::mutex> c4d_sink_mt;
typedef c4d_sink<details::null_mutex> c4d_sink_st;

}
}

#endif
