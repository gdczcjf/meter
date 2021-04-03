#ifndef METERTYPE_H
#define METERTYPE_H

enum MeterType {

    OFF     =   0,

    U1_200V =   1,
    U1_15V  =   2,
    U1_3V   =   3,
    U1_200mV=   4,

    I1_3A  =   5,
    I1_0A6  =   6,
    I1_50mA =   7,
    I1_5mA  =   8,
    I1_300uA=   9,
    I1_50uA =   10,

    U2_200V =   11,
    U2_15V  =   12,
    U2_3V   =   13,
    U2_200mV=   14,


    I2_3A   =   15,
    I2_0A6  =   16,
    I2_50mA =   17,
    I2_5mA  =   18,
    I2_300uA=   19,
    I2_50uA =   20

};


struct MeterTypeInfo{
    const char *name;
    //const char *picFile;

    double valuefactor;
    float zeroAngle ;
    double valueMin;
    double valueMax;

};

struct MeterScaleInfo{
    int bigScaleCount;//最大刻度包括多少个最小刻度
    int mediumScaleCount;//中等刻度包括多少个最小刻度
    int smallScaleCount;//最小刻度数

    double minAbove;
    double scaleValueAbove;
    double minUnder;
    double scaleValueUnder;

    const char *symble;
    int lineStartX;
};



#endif // METERTYPE_H
