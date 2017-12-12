#include "qhsl.h"

QHsl::QHsl(QRgb rgb)
{
    int r = qRed(rgb);
    int g = qGreen(rgb);
    int b = qBlue(rgb);
    int max = (r > g) ? r : g;
    max = (max > b) ? max : b;
    int min = (r < g) ? r : g;
    min = (min < b) ? min : b;

    //hue
    if(max == min) {
        hue = 0;
    } else if (max == r && g >= b) {
        hue = 60*((1.0f*(g - b))/(max - min));
    } else if (max == r && g < b) {
        hue = 60*((1.0f*(g - b))/(max - min)) + 360.0f;
    } else if (max == g) {
        hue = 60*((1.0f*(b - r))/(max - min)) + 120.0f;
    } else {
        hue = 60*((1.0f*(r - g))/(max - min)) + 240.0f;
    }

    //ligntness
    lightness = 0.5*((max + min)/255.0f);
    //saturation
    if(lightness == 0 || max == min) {
        saturation = 0;
    } else if(0 < lightness && lightness <= 0.5){
        saturation = ((max - min)*1.0f)/(max + min);
    } else {
        saturation = ((max - min)/255.0f)/(2 - 2*lightness);
    }

}

QHsl::~QHsl()
{

}

float QHsl::getHue()
{
    return hue;
}


float QHsl::getSaturation()
{
    return saturation;
}

void QHsl::setHue(float value)
{
    hue = value;
}

void QHsl::setSaturation(float value)
{
    saturation = value;
}


QRgb QHsl::toRgb()
{
    int r,g,b;
    if (saturation == 0) {
        r = g = b = floor(lightness*255);
    } else {
        float q,p,h;
        if( lightness < 0.5) {
            q = lightness*(1 + saturation);
        } else {
            q = lightness + saturation - lightness*saturation;
        }
        p = 2*lightness - q;
        h = hue/360;
        //r
        float tr = h + 1/3.0f;
        if(tr < 0) tr += 1.0f;
        if(tr > 1) tr -= 1.0f;
        if(tr < 1/6.0f) {
            r = floor((p + ((q - p)*6*tr))*255);
        } else if(tr >= 1/6.0f && tr < 0.5) {
            r = floor(q*255);
        } else if(tr >=0.5 && tr < 2/3.0f) {
            r = floor((p + ((q - p)*6*(2/3.0 - tr)))*255);
        } else {
            r = floor(p*255);
        }
        //g
        float tg = h;
        if(tg < 0) tg += 1.0f;
        if(tg > 1) tg -= 1.0f;
        if(tg < 1/6.0f) {
            g = floor((p + ((q - p)*6*tg))*255);
        } else if(tg >= 1/6.0f && tg < 0.5) {
            g = floor(q*255);
        } else if(tg >=0.5 && tg < 2/3.0f) {
            g = floor((p + ((q - p)*6*(2/3.0 - tg)))*255);
        } else {
            g = floor(p*255);
        }
        //b
        float tb = h - 1/3.0f;
        if(tb < 0) tb += 1.0f;
        if(tb > 1) tb -= 1.0f;
        if(tb < 1/6.0f) {
            b = floor((p + ((q - p)*6*tb))*255);
        } else if(tb >= 1/6.0f && tb < 0.5) {
            b = floor(q*255);
        } else if(tb >=0.5 && tb < 2/3.0f) {
            b = floor((p + ((q - p)*6*(2/3.0 - tb)))*255);
        } else {
            b = floor(p*255);
        }
    }
    if (r < 0) r = 0;
    if (g < 0) g = 0;
    if (b < 0) b = 0;
    if (r > 255) r = 255;
    if (g > 255) g = 255;
    if (b > 255) b = 255;
    return qRgb(r,g,b);
}


float QHsl::getLightness() const
{
    return lightness;
}

void QHsl::setLightness(float value)
{
    lightness = value;
}
