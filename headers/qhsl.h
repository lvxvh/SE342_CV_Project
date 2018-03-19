#ifndef QHBS_H
#define QHBS_H
#include <QRgb>

class QHsl {
public:
    QHsl(QRgb rgb);
    ~QHsl();

    float getHue();
    float getLightness() const;
    float getSaturation();

    void setHue(float value);
    void setLightness(float value);
    void setSaturation(float value);



    QRgb toRgb();


private:
    float hue;   //[0,360) 0 means max==min
    float saturation; //[0,1]
    float lightness; //[0,1]
};

#endif // QHBS_H
