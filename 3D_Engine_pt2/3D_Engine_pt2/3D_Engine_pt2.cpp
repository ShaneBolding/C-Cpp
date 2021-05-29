#include <iostream>
#include "olcConsoleGameEngine.h"
using namespace std;

struct vec3d    //sets up the vectors needed to make triangle
{
    float x, y, z;
};

struct tri      //sets up an array of vectors needed to make triangle
{
    vec3d p[3];
};

struct mesh
{
    vector<tri> tris;   //vector of triangles to make the shape
};

struct mat4x4
{
    float m[4][4] = { 0 };

};


class Engine3D : public olcConsoleGameEngine
{
public:
    Engine3D()
    {
        m_sAppName = L"3D Engine Demo";
    }

private:
    mesh meshCube;
    mat4x4 matProjection;

    float fTheta = 0.0f;

    void multMat(vec3d& input, vec3d& output, mat4x4& m)
    {
        output.x = input.x * m.m[0][0] + input.y * m.m[1][0] + input.z * m.m[2][0] + m.m[3][0];
        output.y = input.x * m.m[0][1] + input.y * m.m[1][1] + input.z * m.m[2][1] + m.m[3][1];
        output.z = input.x * m.m[0][2] + input.y * m.m[1][2] + input.z * m.m[2][2] + m.m[3][2];
        float w = input.x * m.m[0][3] + input.y * m.m[1][3] + input.z * m.m[2][3] + m.m[3][3];

        if (w != 0.0f)
        {
            output.x /= w; output.y /= w; output.z /= w;
        }
    }

public:
    bool OnUserCreate() override
    {
        meshCube.tris = {
        
        //South
            { 0.0f, 0.0f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 1.0f, 0.0f },
            { 0.0f, 0.0f, 0.0f,   1.0f, 1.0f, 0.0f,   1.0f, 0.0f, 0.0f },

        //East
            { 1.0f, 0.0f, 0.0f,   1.0f, 1.0f, 0.0f,   1.0f, 1.0f, 1.0f },
            { 1.0f, 0.0f, 0.0f,   1.0f, 1.0f, 1.0f,   1.0f, 0.0f, 1.0f },

        //North
            { 1.0f, 0.0f, 1.0f,   1.0f, 1.0f, 1.0f,   0.0f, 1.0f, 1.0f },
            { 1.0f, 0.0f, 1.0f,   0.0f, 1.0f, 1.0f,   0.0f, 0.0f, 1.0f },

        //West
            { 0.0f, 0.0f, 1.0f,   0.0f, 1.0f, 1.0f,   0.0f, 1.0f, 0.0f },
            { 0.0f, 0.0f, 1.0f,   0.0f, 1.0f, 0.0f,   0.0f, 0.0f, 0.0f },

        //Top
            { 0.0f, 1.0f, 0.0f,   0.0f, 1.0f, 1.0f,   1.0f, 1.0f, 1.0f },
            { 0.0f, 1.0f, 0.0f,   1.0f, 1.0f, 1.0f,   1.0f, 1.0f, 0.0f },

        //Bottom
            { 1.0f, 0.0f, 1.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f, 0.0f },
            { 1.0f, 0.0f, 1.0f,   0.0f, 0.0f, 0.0f,   1.0f, 0.0f, 0.0f },
        };

        // projection matrix
        float nearPlane = 0.1f;
        float farPlane = 1000.0f;
        float fov = 90.0f;
        float aspectRatio = (float)ScreenHeight() / (float)ScreenWidth();
        //get fov in radians
        float fovRad = 1.0f / tanf(fov * 0.5f / 180.0f * 3.14159f);

        //using projection x,y,z -> (1/tan(theta/2) * (((w/h) * x),y))/z,
        //normalize z: z * [zfar/(zfar-znear) - (zfar*znear/(zfar-znear))] 
        matProjection.m[0][0] = aspectRatio * fovRad;
        matProjection.m[1][1] = fovRad;
        matProjection.m[2][2] = farPlane / (farPlane - nearPlane);
        matProjection.m[3][2] = (-farPlane * nearPlane) / (farPlane - nearPlane);
        matProjection.m[2][3] = 1.0f;
        matProjection.m[3][3] = 0.0f;

        return true;
    }
    
    bool OnUserUpdate(float fdt) override
    {
        //fill screen black
        Fill(0, 0, ScreenWidth(), ScreenHeight(), PIXEL_SOLID, FG_BLACK);

        mat4x4 matRotz, matRotx; //add matricies to rotate

        fTheta += 1.0f * fdt;

        //rotation Z
        matRotz.m[0][0] = cosf(fTheta);
        matRotz.m[0][1] = sinf(fTheta);
        matRotz.m[1][0] = -sinf(fTheta);
        matRotz.m[1][1] = cosf(fTheta);
        matRotz.m[2][2] = 1;
        matRotz.m[3][3] = 1;

        //rotation X
        matRotx.m[0][0] = 1;
        matRotx.m[1][1] = cosf(fTheta * 0.5f);
        matRotx.m[1][2] = sinf(fTheta * 0.5f);
        matRotx.m[2][1] = -sinf(fTheta * 0.5f);
        matRotx.m[2][2] = cosf(fTheta * 0.5f);
        matRotx.m[3][3] = 1;


        //draw triangles
        for (auto i : meshCube.tris)
        {
            tri triProjected, triTranslated, triRotatedZ, triRotatedZX;

            //rotate the cube around z axis
            multMat(i.p[0], triRotatedZ.p[0], matRotz);
            multMat(i.p[1], triRotatedZ.p[1], matRotz);
            multMat(i.p[2], triRotatedZ.p[2], matRotz);

            //rotate the cube simultanuously around x axis
            multMat(triRotatedZ.p[0], triRotatedZX.p[0], matRotx);
            multMat(triRotatedZ.p[1], triRotatedZX.p[1], matRotx);
            multMat(triRotatedZ.p[2], triRotatedZX.p[2], matRotx);

            //translate so viewer isn't in cube
            triTranslated = triRotatedZX;
            triTranslated.p[0].z = triRotatedZX.p[0].z + 3.0f;
            triTranslated.p[1].z = triRotatedZX.p[1].z + 3.0f;
            triTranslated.p[2].z = triRotatedZX.p[2].z + 3.0f;

            vec3d normal, line1, line2;
            line1.x = triTranslated.p[1].x - triTranslated.p[0].x;
            line1.y = triTranslated.p[1].y - triTranslated.p[0].y;
            line1.z = triTranslated.p[1].z - triTranslated.p[0].z;

            line2.x = triTranslated.p[2].x - triTranslated.p[0].x;
            line2.y = triTranslated.p[2].y - triTranslated.p[0].y;
            line2.z = triTranslated.p[2].z - triTranslated.p[0].z;

            //cross product
            normal.x = line1.y * line2.z - line1.z * line2.y;
            normal.y = line1.z * line2.x - line1.x * line2.z;
            normal.z = line1.x * line2.y - line1.y * line2.x;

            float len = sqrtf(normal.x * normal.x + normal.y * normal.y + normal.z * normal.z);
            normal.x /= 1; normal.y /= 1; normal.z /= 1;

            if (normal.z < 0)
            {
                //project trianges by multiplying matricies (3d -> 2d)
                multMat(triTranslated.p[0], triProjected.p[0], matProjection);
                multMat(triTranslated.p[1], triProjected.p[1], matProjection);
                multMat(triTranslated.p[2], triProjected.p[2], matProjection);

                //scale triange into view 
                triProjected.p[0].x += 1.0f; triProjected.p[0].y += 1.0f;
                triProjected.p[1].x += 1.0f; triProjected.p[1].y += 1.0f;
                triProjected.p[2].x += 1.0f; triProjected.p[2].y += 1.0f;

                //now have to scale by half the screenwidth/height
                triProjected.p[0].x *= 0.5f * (float)ScreenWidth();
                triProjected.p[0].y *= 0.5f * (float)ScreenHeight();
                triProjected.p[1].x *= 0.5f * (float)ScreenWidth();
                triProjected.p[1].y *= 0.5f * (float)ScreenHeight();
                triProjected.p[2].x *= 0.5f * (float)ScreenWidth();
                triProjected.p[2].y *= 0.5f * (float)ScreenHeight();


                //simple function that draws three lines given 3 points
                DrawTriangle(triProjected.p[0].x, triProjected.p[0].y,
                    triProjected.p[1].x, triProjected.p[1].y,
                    triProjected.p[2].x, triProjected.p[2].y,
                    PIXEL_SOLID, FG_WHITE);
            }
        }

        return true;
    }
};

int main()
{
    Engine3D demo;
    if (demo.ConstructConsole(256, 240, 4, 4)) //constructs console if error isn't returned
    {
        demo.Start(); //start the thread in the engine class
    }
    return 0;
}

