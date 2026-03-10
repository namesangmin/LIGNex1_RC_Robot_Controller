#ifndef ICONTROLLER_HPP
#define ICONTROLLER_HPP

#include "main.h"
#include "UGV_Packet.hpp" 

class IController 
{
public:

virtual ~IController() {} 
virtual void update(Data* data) = 0;
};

#endif