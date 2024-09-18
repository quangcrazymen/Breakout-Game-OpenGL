//#pragma once
//
//#include "Object.h"
//#include <stdio.h>
//#include <iostream>
////#define GLFW_INCLUDE_NONE
//#include "GLFW/glfw3.h"
//#include "glad/glad.h"
//#include "ReadAndWriteFile.h"
//
//// vertex in 3d-coordinate system
//struct sPoint {
//    float x, y, z;
//};
//
//// plane equation
//struct sPlaneEq {
//    float a, b, c, d;
//};
//
//// structure describing an object's face
//struct sPlane {
//    unsigned int p[3];
//    sPoint normals[3];
//    unsigned int neigh[3];
//    sPlaneEq PlaneEq;
//    bool visible;
//};
//
//typedef float GLvector4f[4];
//typedef float GLmatrix16f[16];
//
//// object structure
////struct glObject {
////    GLuint nPlanes, nPoints;
////    Point3f points[100];
////    Plane planes[200];
////} obj;
//
//// object structure
//struct glObject {
//    GLuint nPlanes, nPoints;
//    sPoint points[100];
//    sPlane planes[200];
//} obj;
//
//namespace IOUtils {
//    //static bool readObject(const char* filename, glObject& object) {
//
//    //    FILE* pInputFile;
//    //    int i;
//    //    pInputFile = fopen(filename, "r");
//    //    if (pInputFile == NULL)
//    //    {
//    //        std::cerr << "Unable to open the object file: " << filename << std::endl;
//    //        return false;
//    //    }
//    //    // Read Vertices
//    //    fscanf(pInputFile, "%d", &object.nVertices);
//    //    object.pVertices = new Point3f[object.nVertices];
//    //    for (i = 0; i < object.nVertices; i++)
//    //    {
//    //        fscanf(pInputFile, "%f", &object.pVertices[i].x);
//    //        fscanf(pInputFile, "%f", &object.pVertices[i].y);
//    //        fscanf(pInputFile, "%f", &object.pVertices[i].z);
//    //    }
//
//    //    // Read Faces
//    //    fscanf(pInputFile, "%d", &object.nFaces);
//    //    object.pFaces = new Face[object.nFaces];
//    //    for (i = 0; i < object.nFaces; i++)
//    //    {
//    //        int j;
//    //        Face* pFace = &object.pFaces[i];
//
//    //        for (j = 0; j < 3; j++)
//    //            pFace->neighbourIndices[j] = -1; // No Neigbours Set Up Yet
//
//    //        for (j = 0; j < 3; j++)
//    //        {
//    //            fscanf(pInputFile, "%d", &pFace->vertexIndices[j]);
//    //            pFace->vertexIndices[j]--;       // Files Specify Them With A 1 Array Base, But We Use A 0 Array Base
//    //        }
//
//    //        for (j = 0; j < 3; j++)
//    //        {
//    //            fscanf(pInputFile, "%f", &pFace->normals[j].x);
//    //            fscanf(pInputFile, "%f", &pFace->normals[j].y);
//    //            fscanf(pInputFile, "%f", &pFace->normals[j].z);
//    //        }
//    //    }
//    //    return true;
//    //}
//    //static void killObject(glObject& object)
//    //{
//    //    delete[] object.pFaces;
//    //    object.pFaces = NULL;
//    //    object.nFaces = 0;
//
//    //    delete[] object.pVertices;
//    //    object.pVertices = NULL;
//    //    object.nVertices = 0;
//    //}
//
//    // load object
//    inline int ReadObject(char* st, glObject* o) {
//        FILE* file;
//        unsigned int i;
//
//        file = fopen(st, "r");
//        if (!file) return false;
//        //points
//        fscanf(file, "%d", &(o->nPoints));
//        for (i = 1; i <= o->nPoints; i++) {
//            fscanf(file, "%f", &(o->points[i].x));
//            fscanf(file, "%f", &(o->points[i].y));
//            fscanf(file, "%f", &(o->points[i].z));
//        }
//        //planes
//        fscanf(file, "%d", &(o->nPlanes));
//        for (i = 0; i < o->nPlanes; i++) {
//            fscanf(file, "%d", &(o->planes[i].p[0]));
//            fscanf(file, "%d", &(o->planes[i].p[1]));
//            fscanf(file, "%d", &(o->planes[i].p[2]));
//
//            fscanf(file, "%f", &(o->planes[i].normals[0].x));
//            fscanf(file, "%f", &(o->planes[i].normals[0].y));
//            fscanf(file, "%f", &(o->planes[i].normals[0].z));
//            fscanf(file, "%f", &(o->planes[i].normals[1].x));
//            fscanf(file, "%f", &(o->planes[i].normals[1].y));
//            fscanf(file, "%f", &(o->planes[i].normals[1].z));
//            fscanf(file, "%f", &(o->planes[i].normals[2].x));
//            fscanf(file, "%f", &(o->planes[i].normals[2].y));
//            fscanf(file, "%f", &(o->planes[i].normals[2].z));
//        }
//        return true;
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
//    static void drawObject(const glObject& object
//        , double _width, double _height) {
//        for (int i=0 ; i<object.nFaces; i++)
//        {
//            const Face& face = object.pFaces[i];
//            for (int j = 0; j < 3; j++) {
//                const Point3f& vertex = object.pVertices[face.vertexIndices[j]];
//                glNormal3f(face.normals[j].x, face.normals[j].y, face.normals[j].z);
//                glVertex3f(vertex.x, vertex.y, vertex.z);
//            }
//            glEnd();
//        }
//        abs(2);
//        //glViewport(0, 0, _width, _height);
//        //glMatrixMode(GL_PROJECTION);
//        //glLoadIdentity();
//        //perspectiveGL(45.0,                             // The camera angle
//        //    (double)_width / (double)_height, // The width-to-height ratio
//        //    1.0,                   // The near z clipping coordinate
//        //    200.0);
//        ////glMatrixMode();
//        //glMatrixMode(GL_MODELVIEW);
//        //glLoadIdentity();
//        //glBegin(GL_QUADS); // Begin quadrilateral coordinates
//
//        //// Trapezoid
//        //glVertex3f(-0.7f, -1.5f, -5.0f);
//        //glVertex3f(0.7f, -1.5f, -5.0f);
//        //glVertex3f(0.4f, -0.5f, -5.0f);
//        //glVertex3f(-0.4f, -0.5f, -5.0f);
//
//        //glEnd();
//    }
//    static void calculatePlane(const glObject& object, Face& face)
//    {
//        // Get Shortened Names For The Vertices Of The Face
//        const Point3f& v1 = object.pVertices[face.vertexIndices[0]];
//        const Point3f& v2 = object.pVertices[face.vertexIndices[1]];
//        const Point3f& v3 = object.pVertices[face.vertexIndices[2]];
//
//        // Actually doing some cross product here
//        face.planeEquation.a = v1.y * (v2.z - v3.z) + v2.y * (v3.z - v1.z) + v3.y * (v1.z - v2.z);
//        face.planeEquation.b = v1.z * (v2.x - v3.x) + v2.z * (v3.x - v1.x) + v3.z * (v1.x - v2.x);
//        face.planeEquation.c = v1.x * (v2.y - v3.y) + v2.x * (v3.y - v1.y) + v3.x * (v1.y - v2.y);
//        face.planeEquation.d = -(v1.x * (v2.y * v3.z - v3.y * v2.z) +
//            v2.x * (v3.y * v1.z - v1.y * v3.z) +
//            v3.x * (v1.y * v2.z - v2.y * v1.z));
//    }
//    static void castShadow(glObject& object, GLfloat* lightPosition)
//    {
//        // Determine Which Faces Are Visible By The Light.
//        for (int i = 0; i < object.nFaces; i++)
//        {
//            const Plane& plane = object.pFaces[i].planeEquation;
//
//            GLfloat side = plane.a * lightPosition[0] +
//                plane.b * lightPosition[1] +
//                plane.c * lightPosition[2] +
//                plane.d;
//
//            if (side > 0)
//                object.pFaces[i].visible = true;
//            else
//                object.pFaces[i].visible = false;
//        }
//        glPushAttrib(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_ENABLE_BIT | GL_POLYGON_BIT | GL_STENCIL_BUFFER_BIT);
//        glDisable(GL_LIGHTING);
//        glDepthMask(GL_false);
//        glDepthFunc(GL_LEQUAL);
//        glEnable(GL_STENCIL_TEST);
//        glColorMask(GL_false, GL_false, GL_false, GL_false);
//        //glStencilFunc(GL_ALWAYS, 1, -1);
//        glStencilFunc(GL_ALWAYS, 1, 0xFFFFFFFFL);
//
//        // Frontfacing triangle is counter-clockwise
//        // This call the first pass increase stencil value if front facing
//        glFrontFace(GL_CCW);
//        glStencilOp(GL_KEEP, GL_KEEP, GL_INCR);
//        //doShadowPass(object, lightPosition);
//        // Conversely decrease stencil value second pass
//        glFrontFace(GL_CW);
//        glStencilOp(GL_KEEP, GL_KEEP, GL_DECR);
//        //doShadowPass(object, lightPosition);
//    
//        glFrontFace(GL_CCW);
//        glColorMask(GL_true, GL_true, GL_true, GL_true);  // Enable Rendering To Colour Buffer For All Components
//
//        // Draw a shadow rectangle covering the entire screen
//        glColor4f(0.0f, 0.0f, 0.0f, 0.4f);
//        glEnable(GL_BLEND);
//        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
//        glStencilFunc(GL_NOTEQUAL, 0, 0xFFFFFFFFL);
//
//        // TEST DRAWING TRIANGLE STRIP
//    }
//    static void DrawGLRoom()                           // Draw The Room (Box)
//    {
//        glBegin(GL_QUADS);                      // Begin Drawing Quads
//        // Floor
//        glNormal3f(0.0f, 1.0f, 0.0f);               // Normal Pointing Up
//        glVertex3f(-10.0f, -10.0f, -20.0f);           // Back Left
//        glVertex3f(-10.0f, -10.0f, 20.0f);           // Front Left
//        glVertex3f(10.0f, -10.0f, 20.0f);           // Front Right
//        glVertex3f(10.0f, -10.0f, -20.0f);           // Back Right
//        // Ceiling
//        glNormal3f(0.0f, -1.0f, 0.0f);               // Normal Point Down
//        glVertex3f(-10.0f, 10.0f, 20.0f);           // Front Left
//        glVertex3f(-10.0f, 10.0f, -20.0f);           // Back Left
//        glVertex3f(10.0f, 10.0f, -20.0f);           // Back Right
//        glVertex3f(10.0f, 10.0f, 20.0f);           // Front Right
//        // Front Wall
//        glNormal3f(0.0f, 0.0f, 1.0f);               // Normal Pointing Away From Viewer
//        glVertex3f(-10.0f, 10.0f, -20.0f);           // Top Left
//        glVertex3f(-10.0f, -10.0f, -20.0f);           // Bottom Left
//        glVertex3f(10.0f, -10.0f, -20.0f);           // Bottom Right
//        glVertex3f(10.0f, 10.0f, -20.0f);           // Top Right
//        // Back Wall
//        glNormal3f(0.0f, 0.0f, -1.0f);               // Normal Pointing Towards Viewer
//        glVertex3f(10.0f, 10.0f, 20.0f);           // Top Right
//        glVertex3f(10.0f, -10.0f, 20.0f);           // Bottom Right
//        glVertex3f(-10.0f, -10.0f, 20.0f);           // Bottom Left
//        glVertex3f(-10.0f, 10.0f, 20.0f);           // Top Left
//        // Left Wall
//        glNormal3f(1.0f, 0.0f, 0.0f);               // Normal Pointing Right
//        glVertex3f(-10.0f, 10.0f, 20.0f);           // Top Front
//        glVertex3f(-10.0f, -10.0f, 20.0f);           // Bottom Front
//        glVertex3f(-10.0f, -10.0f, -20.0f);           // Bottom Back
//        glVertex3f(-10.0f, 10.0f, -20.0f);           // Top Back
//        // Right Wall
//        glNormal3f(-1.0f, 0.0f, 0.0f);              // Normal Pointing Left
//        glVertex3f(10.0f, 10.0f, -20.0f);           // Top Back
//        glVertex3f(10.0f, -10.0f, -20.0f);           // Bottom Back
//        glVertex3f(10.0f, -10.0f, 20.0f);           // Bottom Front
//        glVertex3f(10.0f, 10.0f, 20.0f);           // Top Front
//        glEnd();                            // Done Drawing Quads
//    }
//    static int InitGL(GLvoid) {
//        float LightPos[] = { 0.0f, 5.0f,-4.0f, 1.0f };			// Light Position
//        float LightAmb[] = { 0.2f, 0.2f, 0.2f, 1.0f };			// Ambient Light Values
//        float LightDif[] = { 0.6f, 0.6f, 0.6f, 1.0f };			// Diffuse Light Values
//        float LightSpc[] = { -0.2f, -0.2f, -0.2f, 1.0f };			// Specular Light Values
//
//        float MatAmb[] = { 0.4f, 0.4f, 0.4f, 1.0f };				// Material - Ambient Values
//        float MatDif[] = { 0.2f, 0.6f, 0.9f, 1.0f };				// Material - Diffuse Values
//        float MatSpc[] = { 0.0f, 0.0f, 0.0f, 1.0f };				// Material - Specular Values
//        float MatShn[] = { 0.0f };								// Material - Shininess
//
//        //if (!InitGLObjects()) return false;					// Function For Initializing Our Object(s)
//        glShadeModel(GL_SMOOTH);							// Enable Smooth Shading
//        glClearColor(0.0f, 0.0f, 0.0f, 0.5f);				// Black Background
//        glClearDepth(1.0f);									// Depth Buffer Setup
//        glClearStencil(0);									// Stencil Buffer Setup
//        glEnable(GL_DEPTH_TEST);							// Enables Depth Testing
//        glDepthFunc(GL_LEQUAL);								// The Type Of Depth Testing To Do
//        glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);	// Really Nice Perspective Calculations
//
//        glLightfv(GL_LIGHT1, GL_POSITION, LightPos);		// Set Light1 Position
//        glLightfv(GL_LIGHT1, GL_AMBIENT, LightAmb);			// Set Light1 Ambience
//        glLightfv(GL_LIGHT1, GL_DIFFUSE, LightDif);			// Set Light1 Diffuse
//        glLightfv(GL_LIGHT1, GL_SPECULAR, LightSpc);		// Set Light1 Specular
//        glEnable(GL_LIGHT1);								// Enable Light1
//        glEnable(GL_LIGHTING);								// Enable Lighting
//
//        glMaterialfv(GL_FRONT, GL_AMBIENT, MatAmb);			// Set Material Ambience
//        glMaterialfv(GL_FRONT, GL_DIFFUSE, MatDif);			// Set Material Diffuse
//        glMaterialfv(GL_FRONT, GL_SPECULAR, MatSpc);		// Set Material Specular
//        glMaterialfv(GL_FRONT, GL_SHININESS, MatShn);		// Set Material Shininess
//
//        glCullFace(GL_BACK);								// Set Culling Face To Back Face
//        glEnable(GL_CULL_FACE);								// Enable Culling
//        glClearColor(0.1f, 1.0f, 0.5f, 1.0f);				// Set Clear Color (Greenish Color)
//
//        //q = gluNewQuadric();								// Initialize Quadratic
//        //gluQuadricNormals(q, GL_SMOOTH);					// Enable Smooth Normal Generation
//        //gluQuadricTexture(q, GL_false);						// Disable Auto Texture Coords
//
//        return true;
//    }
//
//    static int InitGLObjects()                         // Initialize Objects
//    {
//        if (!ReadObject("Data/Object2.txt", obj))           // Read Object2 Into obj
//        {
//            return false;                       // If Failed Return false
//        }
//
//        setConnectivity(obj);                       // Set Face To Face Connectivity
//
//        for (int i = 0; i < obj.nFaces; i++)                // Loop Through All Object Faces
//            calculatePlane(obj, obj.pFaces[i]);         // Compute Plane Equations For All Faces
//
//        return true;                            // Return true
//    }
//
//    static void SetConnectivity(glObject* o) {
//        /*unsigned*/ int p1i, p2i, p1j, p2j;
//        /*unsigned*/ int P1i, P2i, P1j, P2j;
//        /*unsigned*/ int i, j, ki, kj;
//        for (i = 0; i < o->nPlanes - 1; i++)
//            for (j = i + 1; j < o->nPlanes; j++)
//                for (ki = 0; ki < 3; ki++)
//                    if (!o->planes[i].neigh[ki]) {
//                        for (kj = 0; kj < 3; kj++) {
//                            p1i = ki;
//                            p1j = kj;
//                            p2i = (ki + 1) % 3;
//                            p2j = (kj + 1) % 3;
//
//                            p1i = o->planes[i].p[p1i];
//                            p2i = o->planes[i].p[p2i];
//                            p1j = o->planes[j].p[p1j];
//                            p2j = o->planes[j].p[p2j];
//
//                            P1i = ((p1i + p2i) - abs(p1i - p2i)) / 2;
//                            P2i = ((p1i + p2i) + abs(p1i - p2i)) / 2;
//                            P1j = ((p1j + p2j) - abs(p1j - p2j)) / 2;
//                            P2j = ((p1j + p2j) + abs(p1j - p2j)) / 2;
//
//                            if ((P1i == P1j) && (P2i == P2j)) {  //they are neighbours
//                                o->planes[i].neigh[ki] = j + 1;
//                                o->planes[j].neigh[kj] = i + 1;
//                            }
//                        }
//                    }
//    }
//
//    void VMatMult(GLmatrix16f M, GLvector4f v)
//    {
//        GLfloat res[4];										// Hold Calculated Results
//        res[0] = M[0] * v[0] + M[4] * v[1] + M[8] * v[2] + M[12] * v[3];
//        res[1] = M[1] * v[0] + M[5] * v[1] + M[9] * v[2] + M[13] * v[3];
//        res[2] = M[2] * v[0] + M[6] * v[1] + M[10] * v[2] + M[14] * v[3];
//        res[3] = M[3] * v[0] + M[7] * v[1] + M[11] * v[2] + M[15] * v[3];
//        v[0] = res[0];										// Results Are Stored Back In v[]
//        v[1] = res[1];
//        v[2] = res[2];
//        v[3] = res[3];										// Homogenous Coordinate
//    }
//}
