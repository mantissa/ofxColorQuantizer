#pragma once
#include "ofMain.h"

/*
 
 Converting RGB image to LAB in order to get 'Chroma' or colorfullness of a color
 
 */

class ColorConverter {
public:
    static ofVec3f rgbToXyz( const ofFloatColor &rgb ) {
        float r = rgb.r;
        float g = rgb.g;
        float b = rgb.b;
        
        if ( r > 0.04045f ) {
            r = pow( ( r + 0.055f ) / 1.055f, 2.4f );
        } else {
            r = r / 12.92f;
        }
        
        if ( g > 0.04045f ) {
            g = pow( ( g + 0.055f ) / 1.055f, 2.4f );
        }
        else {
            g = g / 12.92f;
        }
        
        if ( b > 0.04045f ) {
            b = pow( ( b + 0.055f ) / 1.055f, 2.4f );
        }
        else {
            b = b / 12.92f;
        }
        
        r = r * 100.0f;
        g = g * 100.0f;
        b = b * 100.0f;
        
        // Observer = 2°, Illuminant = D65
        return ofVec3f( r * 0.4124f + g * 0.3576f + b * 0.1805f,
                       r * 0.2126f + g * 0.7152f + b * 0.0722f,
                       r * 0.0193f + g * 0.1192f + b * 0.9505f );
    }
    
    static ofFloatColor xyzToRgb( const ofVec3f &xyz ) {
        float x = xyz.x / 100.0f; // X from 0 to  95.047 (Observer = 2°, Illuminant = D65)
        float y = xyz.y / 100.0f; // X from 0 to 100.000
        float z = xyz.z / 100.0f; // X from 0 to 108.883
        
        float r = x *  3.2406f + y * -1.5372f + z * -0.4986f;
        float g = x * -0.9689f + y *  1.8758f + z *  0.0415f;
        float b = x *  0.0557f + y * -0.2040f + z *  1.0570f;
        
        if ( r > 0.0031308f ) {
            r = 1.055f * pow( r, ( 1.0f / 2.4f ) ) - 0.055f;
        }
        else {
            r = 12.92f * r;
        }
        
        if ( g > 0.0031308f ) {
            g = 1.055f * pow( g, ( 1.0f / 2.4f ) ) - 0.055f;
        }
        else {
            g = 12.92f * g;
        }
        
        if ( b > 0.0031308f ) {
            b = 1.055f * pow( b, ( 1.0f / 2.4f ) ) - 0.055f;
        }
        else {
            b = 12.92f * b;
        }
        
        return ofColor( r, g, b );
    }
    
    static ofVec3f xyzToLab( const ofVec3f &xyz ) {
        // Observer = 2°, Illuminant = D65
        const float refX = 95.047f;
        const float refY = 100.0f;
        const float refZ = 108.883f;
        
        float x = xyz.x / refX;
        float y = xyz.y / refY;
        float z = xyz.z / refZ;
        
        if ( x > 0.008856f ) {
            x = pow( x, 1.0f / 3.0f );
        }
        else {
            x = ( 7.787f * x ) + ( 16.0f / 116.0f );
        }
        
        if ( y > 0.008856f ) {
            y = pow( y, 1.0f / 3.0f );
        }
        else {
            y = ( 7.787f * y ) + ( 16.0f / 116.0f );
        }
        
        if ( z > 0.008856f ) {
            z = pow( z, 1.0f / 3.0f );
        }
        else {
            z = ( 7.787f * z ) + ( 16.0f / 116.0f );
        }
        
        return ofVec3f( ( 116.0f * y ) - 16.0f,
                       500.0f * ( x - y ),
                       200.0f * ( y - z ) );
    }
    
    static ofVec3f labToXyz( const ofVec3f &lab ) {
        float y = ( lab.x + 16.0f ) / 116.0f;
        float x = lab.y / 500.0f + y;
        float z = y - lab.z / 200.0f;
        
        float x3 = pow( x, 3.0f );
        float y3 = pow( y, 3.0f );
        float z3 = pow( z, 3.0f );
        
        if ( x3 > 0.008856f ) {
            x = x3;
        }
        else {
            x = ( x - 16.0f / 116.0f ) / 7.787f;
        }
        
        if ( y3 > 0.008856f ) {
            y = y3;
        }
        else {
            y = ( y - 16.0f / 116.0f ) / 7.787f;
        }
        
        if ( z3 > 0.008856f ) {
            z = z3;
        }
        else {
            z = ( z - 16.0f / 116.0f ) / 7.787f;
        }
        
        
        // Observer = 2°, Illuminant = D65
        const float refX = 95.047f;
        const float refY = 100.0f;
        const float refZ = 108.883f;
        return ofVec3f( x * refX, y * refY, z * refZ );
    }
    
    static ofVec3f labToLch( const ofVec3f &lab ) {
        return ofVec3f( lab.x,
                       sqrt( lab.y * lab.y + lab.z * lab.z ),
                       atan2( lab.z, lab.y ) );
    }
    
    static ofVec3f lchToLab( const ofVec3f &lch ) {
        return ofVec3f( lch.x,
                       lch.y * cos( lch.z ),
                       lch.y * sin( lch.z ) );
    }
    
    static ofVec3f rgbToLab( const ofFloatColor &rgb ) {
        return xyzToLab( rgbToXyz( rgb ) );
    }
    
    static ofFloatColor labToRgb( const ofVec3f &lab ) {
        return xyzToRgb( labToXyz( lab ) );
    }
    
    static float calcSaturation( const ofVec3f &lab ) {
        float C2 = lab.y * lab.y + lab.z * lab.z;
        float C = sqrt( C2 );
        float S = C / sqrt( C2 + lab.x * lab.x );
        return S;
    }
    
    static float calcChroma( const ofVec3f &lab ) {
        const float maxChromaInv = 1.0f / sqrt( 128.0f * 128.0f + 128.0f * 128.0f );
        float C2 = lab.y * lab.y + lab.z * lab.z;
        float C = sqrt( C2 );
        float CH = C * maxChromaInv;
        return CH;
    }
    
    static float distLab( const ofVec3f c1, const ofVec3f c2){
        float dL = c1.x - c2.x;
        float da = c1.y - c2.y;
        float db = c1.z - c2.z;
        return sqrt(dL*dL + da*da + db*db);
    }
};
