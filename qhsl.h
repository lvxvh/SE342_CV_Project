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
    float hue;
    float saturation;
    float lightness;
};

#endif // QHBS_H
