//
// Copyright(c) 2016 Alexander Dalshov.
// Distributed under the MIT License (http://opensource.org/licenses/MIT)
//

#pragma once


#include <spdlog/sinks/base_sink.h>
#include <spdlog/details/null_mutex.h>

#include <mutex>

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
        auto size = msg.formatted.size(); if (size == 0) { return; }
        auto data = msg.formatted.data();
        ///Hack to remove time part like this one [15:49:49.369] 
        if (size > 16) {
            data = data + 15; //TODO: is there a better way for this ?
            size = size - 15;
        }
        String str;
        str.SetCString(data, size, STRINGENCODING_UTF8);
        GePrint(str);
    }
};

typedef c4d_sink<std::mutex> c4d_sink_mt;
typedef c4d_sink<details::null_mutex> c4d_sink_st;

}
}
