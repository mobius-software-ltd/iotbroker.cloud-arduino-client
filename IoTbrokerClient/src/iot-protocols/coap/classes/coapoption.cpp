#include "coapoption.h"

int CoapOption::getNumber() const
{
    return number;
}

void CoapOption::setNumber(int value)
{
    number = value;
}

int CoapOption::getLength() const
{
    return length;
}

void CoapOption::setLength(int value)
{
    length = value;
}

void CoapOption::setValue(const unsigned char  *value)
{
    this->value = value;
}

unsigned char * CoapOption::getValue() const
{
    return value;
}

CoapOption::CoapOption()
{

}

CoapOption::CoapOption(int number, int length, unsigned char * value)
{
    this->number = number;
    this->length = length;
    this->value = value;
}

bool CoapOption::numberLessThan(const CoapOption &op1, const CoapOption &op2)
{
    return op1.getNumber() < op2.getNumber();
}
