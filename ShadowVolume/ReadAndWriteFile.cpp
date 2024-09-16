////#pragma
//#include "Object.h"
//#include <stdio.h>
//#include <iostream>
//#include "GLFW/glfw3.h"
//#include "glad/glad.h"
//#include "ReadAndWriteFile.h"
//namespace IOUtils {
//    static bool readObject(const char* filename, ShadowedObject& object) {
//        FILE* pInputFile;
//        int i;
//        pInputFile = fopen(filename, "r");
//        if (pInputFile == NULL)
//        {
//            std::cerr << "Unable to open the object file: " << filename << std::endl;
//            return false;
//        }
//        // Read Vertices
//        fscanf(pInputFile, "%d", &object.nVertices);
//        object.pVertices = new Point3f[object.nVertices];
//        for (i = 0; i < object.nVertices; i++)
//        {
//            fscanf(pInputFile, "%f", &object.pVertices[i].x);
//            fscanf(pInputFile, "%f", &object.pVertices[i].y);
//            fscanf(pInputFile, "%f", &object.pVertices[i].z);
//        }
//
//        // Read Faces
//        fscanf(pInputFile, "%d", &object.nFaces);
//        object.pFaces = new Face[object.nFaces];
//        for (i = 0; i < object.nFaces; i++)
//        {
//            int j;
//            Face* pFace = &object.pFaces[i];
//
//            for (j = 0; j < 3; j++)
//                pFace->neighbourIndices[j] = -1; // No Neigbours Set Up Yet
//
//            for (j = 0; j < 3; j++)
//            {
//                fscanf(pInputFile, "%d", &pFace->vertexIndices[j]);
//                pFace->vertexIndices[j]--;       // Files Specify Them With A 1 Array Base, But We Use A 0 Array Base
//            }
//
//            for (j = 0; j < 3; j++)
//            {
//                fscanf(pInputFile, "%f", &pFace->normals[j].x);
//                fscanf(pInputFile, "%f", &pFace->normals[j].y);
//                fscanf(pInputFile, "%f", &pFace->normals[j].z);
//            }
//        }
//        return true;
//    }
//    static void killObject(ShadowedObject& object)
//    {
//        delete[] object.pFaces;
//        object.pFaces = NULL;
//        object.nFaces = 0;
//
//        delete[] object.pVertices;
//        object.pVertices = NULL;
//        object.nVertices = 0;
//    }
//
//    static void perspectiveGL(GLdouble fovY, GLdouble aspect, GLdouble zNear, GLdouble zFar)
//    {
//        const GLdouble pi = 3.1415926535897932384626433832795;
//        GLdouble       fW, fH;
//
//        // fH = tan( (fovY / 2) / 180 * pi ) * zNear;
//        fH = tan(fovY / 360 * pi) * zNear;
//        fW = fH * aspect;
//
//        glFrustum(-fW, fW, -fH, fH, zNear, zFar);
//    }
//    static void drawObject(const ShadowedObject& object
//    ,double _width,double _height){
//        //for (int i=)
//        //glViewport(0, 0, _width, _height);
//        glMatrixMode(GL_PROJECTION);
//        glLoadIdentity();
//        perspectiveGL(45.0,                             // The camera angle
//            (double)_width / (double)_height, // The width-to-height ratio
//            1.0,                   // The near z clipping coordinate
//            200.0);
//        //glMatrixMode();
//        glMatrixMode(GL_MODELVIEW);
//        glLoadIdentity();
//        glBegin(GL_QUADS); // Begin quadrilateral coordinates
//
//        // Trapezoid
//        glVertex3f(-0.7f, -1.5f, -5.0f);
//        glVertex3f(0.7f, -1.5f, -5.0f);
//        glVertex3f(0.4f, -0.5f, -5.0f);
//        glVertex3f(-0.4f, -0.5f, -5.0f);
//
//        glEnd();
//    }
//}