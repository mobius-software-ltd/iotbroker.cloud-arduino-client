#ifndef COAPOPTION_H
#define COAPOPTION_H

class CoapOption
{
private:
    int number;
    int length;
    unsigned char * value;
public:
    CoapOption();
    CoapOption(int number, int length, unsigned char * value);

    static bool numberLessThan(const CoapOption &op1, const CoapOption &op2);

    int getNumber() const;
    void setNumber(int value);
    int getLength() const;
    void setLength(int value);
    void setValue(const unsigned char * &value);
    unsigned char * getValue() const;
};

#endif // COAPOPTION_H
