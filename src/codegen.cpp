#include <codegen.h>

namespace backend
{

    std::map<GPR, Register> gpr_map;

    void init_gpr_map()
    {
        for (int i = 0; i < 32; ++i)
        {
            GPR reg = static_cast<GPR>(i);
            gpr_map[reg] = Register();
            gpr_map[reg].reg_name = get_gpr_name(reg);
        }
    }

    std::string get_gpr_name(GPR reg)
    {
        switch (reg)
        {
        case r0:
            return "$zero";
        case at:
            return "$at";
        case v0:
            return "$v0";
        case v1:
            return "$v1";
        case a0:
            return "$a0";
        case a1:
            return "$a1";
        case a2:
            return "$a2";
        case a3:
            return "$a3";
        case t0:
            return "$t0";
        case t1:
            return "$t1";
        case t2:
            return "$t2";
        case t3:
            return "$t3";
        case t4:
            return "$t4";
        case t5:
            return "$t5";
        case t6:
            return "$t6";
        case t7:
            return "$t7";
        case s0:
            return "$s0";
        case s1:
            return "$s1";
        case s2:
            return "$s2";
        case s3:
            return "$s3";
        case s4:
            return "$s4";
        case s5:
            return "$s5";
        case s6:
            return "$s6";
        case s7:
            return "$s7";
        case t8:
            return "$t8";
        case t9:
            return "$t9";
        case k0:
            return "$k0";
        case k1:
            return "$k1";
        case gp:
            return "$gp";
        case sp:
            return "$sp";
        case fp:
            return "$fp";
        case ra:
            return "$ra";
        }
    }

}