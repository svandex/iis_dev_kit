#include "sub_test.h"

void nicard_attr(NICard &nic)
{
    ViChar intfdesc[MAX_CNT];
    nic.run(tv::MakeRigFunctor_s(viGetAttribute), nic.m_instr, VI_ATTR_INTF_INST_NAME, intfdesc);
    std::printf("Interface Description:%s \n", intfdesc);

    nic.run(tv::MakeRigFunctor_s(viGetAttribute), nic.m_instr, VI_ATTR_RSRC_MANF_NAME, intfdesc);
    std::printf("Manufactory Name: %s \n", intfdesc);

    ViUInt16 deviceID;
    nic.run(tv::MakeRigFunctor_s(viGetAttribute), nic.m_instr, VI_ATTR_RSRC_MANF_ID, &deviceID);
    std::printf("Manufactory ID: %d \n", deviceID);

    //protocal
    //nic.run(tv::MakeRigFunctor_s(viSetAttribute), nic.m_instr, VI_ATTR_IO_PROT, VI_PROT_4882_STRS);
    ViUInt16 t_prot = 0;
//    nic.run(tv::MakeRigFunctor_s(viGetAttribute), nic.m_instr, VI_ATTR_USB_PROTOCOL, &t_prot);
    std::cout << "Protocal : " << t_prot << std::endl;

    //Attribute Setting
    nic.run(tv::MakeRigFunctor_s(viSetAttribute), nic.m_instr, VI_ATTR_TMO_VALUE, 2000);
    //nic.run(tv::MakeRigFunctor_s(viSetAttribute), nic.m_instr, VI_ATTR_TERMCHAR, 0x0D);
    //nic.run(tv::MakeRigFunctor_s(viSetAttribute), nic.m_instr, VI_ATTR_TERMCHAR_EN, VI_TRUE);
    //nic.run(tv::MakeRigFunctor_s(viSetAttribute), nic.m_instr, VI_ATTR_SEND_END_EN, VI_FALSE);
}

void nicard_lla(NICard &nic)
{
    ViAddr address;
    ViUInt16 value;
    nic.run(tv::MakeRigFunctor_s(viMapAddress), nic.m_instr, VI_A16_SPACE, 0, 0x40, VI_FALSE, (void *)VI_NULL, &address);
    viPeek16(nic.m_instr, address, &value);
    std::cout << "value: " << value << std::endl;
    nic.run(tv::MakeRigFunctor_s(viUnmapAddress), nic.m_instr);
}

void nicard_hla(NICard &nic)
{
    ViUInt16 deviceID;
    nic.run(tv::MakeRigFunctor_s(viIn16), nic.m_instr, VI_A16_SPACE, 0, &deviceID);
    std::cout << "Device ID: " << deviceID << std::endl;
}

void nicard_scpi(NICard &nic)
{
    nic.run(tv::MakeRigFunctor_s(viClear), nic.m_instr);
    //nic.run(tv::MakeRigFunctor_s(viWrite), nic.m_instr, (ViConstBuf) "READ:WAVFM:CH1\n", 14, &nic.m_ret_cnt);
    nic.run(tv::MakeRigFunctor_s(viWrite), nic.m_instr, (ViConstBuf) "*IDN?\n", 6, &nic.m_ret_cnt);
    std::cout << "Write Completed." << std::endl;
    ViByte buf[1024];
    nic.run(tv::MakeRigFunctor_s(viAssertTrigger), nic.m_instr, VI_TRIG_PROT_DEFAULT);
    nic.run(tv::MakeRigFunctor_s(viRead), nic.m_instr, buf, 1024, &nic.m_ret_cnt);
    std::cout << "nicard: " << buf << std::endl;
}