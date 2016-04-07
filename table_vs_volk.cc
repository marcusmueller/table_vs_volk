/* This code is under GPLv3 or later.
*/
#include <cmath>
#include <sstream>
#include <vector>
#include <iostream>
#include <boost/timer/timer.hpp>
#include <volk/volk.h>
#include <volk/volk_32f_sin_32f.h>
#include "fxpt.h"
namespace gr {

    const float fxpt::s_sine_table[1 << NBITS][2] = {
        #include "sine_table.h"
    };

    const float fxpt::PI = 3.14159265358979323846;
    const float fxpt::TWO_TO_THE_31 = 2147483648.0;

} /* namespace gr */
using gr::fxpt;

int main(int argc, char** argv) {
    unsigned long num = 100*1000*1000;
    std::stringstream options;
    if(argc > 2) {
        std::cout << "usage" << std::endl
            << argv[0] << " [number_of_ops]"
            << std::endl
            << " number_of_ops: number of operations; defaults to " << num
            << std::endl;
        return -1;
    }
    options << argv[1];
    options >> num;
    std::vector<float> out(num);
    std::vector<float> in(num);
    for(unsigned long i = 0; i < num; i++)
        in[i] = (float)i;

    std::cout << "Doing " << num << " operations." << std::endl;

    std::cout << "fixed point" << std::endl;
    {
        boost::timer::auto_cpu_timer t;
        for(unsigned long i = 0; i < num; i++)
            out[i] = fxpt::sin(in[i]);
    }

    std::cout << "standard libc float32 sin" << std::endl;
    {
        boost::timer::auto_cpu_timer t;
        for(unsigned long i = 0; i < num; i++)
            out[i] = std::sin(in[i]);
    }

    std::cout << "VOLK float32 sin" << std::endl;
    {
        boost::timer::auto_cpu_timer t;
        volk_32f_sin_32f(&(out[0]),&(in[0]), num);
    }
}
