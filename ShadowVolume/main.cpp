/*******************************************************************
** This code is part of Breakout.
**
** Breakout is free software: you can redistribute it and/or modify
** it under the terms of the CC BY 4.0 license as published by
** Creative Commons, either version 4 of the License, or (at your
** option) any later version.
******************************************************************/
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "glm/glm.hpp"
#include <iostream>
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
//#include "ReadAndWriteFile.h"
#include "ThreeDObject.h"

// Global variable
typedef float GLvector4f[4];							// Typedef's For VMatMult Procedure
typedef float GLmatrix16f[16];							// Typedef's For VMatMult Procedure

glObject	obj;										// Object
GLfloat		xrot = 0, xspeed = 0;							// X Rotation & X Speed
GLfloat		yrot = 0, yspeed = 0;							// Y Rotation & Y Speed

float LightPos[] = { 0.0f, 5.0f,-4.0f, 1.0f };			// Light Position
float LightAmb[] = { 0.2f, 0.2f, 0.2f, 1.0f };			// Ambient Light Values
float LightDif[] = { 0.6f, 0.6f, 0.6f, 1.0f };			// Diffuse Light Values
float LightSpc[] = { -0.2f, -0.2f, -0.2f, 1.0f };			// Specular Light Values

float MatAmb[] = { 0.4f, 0.4f, 0.4f, 1.0f };				// Material - Ambient Values
float MatDif[] = { 0.2f, 0.6f, 0.9f, 1.0f };				// Material - Diffuse Values
float MatSpc[] = { 0.0f, 0.0f, 0.0f, 1.0f };				// Material - Specular Values
float MatShn[] = { 0.0f };								// Material - Shininess
float MatEms[] = { 0.2f, 0.0f, 0.0f, 1.0f };

float ObjPos[] = { -2.0f,-2.0f,-5.0f };

void VMatMult(GLmatrix16f M, GLvector4f v)
{
    GLfloat res[4];										// Hold Calculated Results
    res[0] = M[0] * v[0] + M[4] * v[1] + M[8] * v[2] + M[12] * v[3];
    res[1] = M[1] * v[0] + M[5] * v[1] + M[9] * v[2] + M[13] * v[3];
    res[2] = M[2] * v[0] + M[6] * v[1] + M[10] * v[2] + M[14] * v[3];
    res[3] = M[3] * v[0] + M[7] * v[1] + M[11] * v[2] + M[15] * v[3];
    v[0] = res[0];										// Results Are Stored Back In v[]
    v[1] = res[1];
    v[2] = res[2];
    v[3] = res[3];										// Homogenous Coordinate
}
// GLFW function declarations
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);

// The Width of the screen
const unsigned int SCREEN_WIDTH = 800;
// The height of the screen
const unsigned int SCREEN_HEIGHT = 600;

    static void perspectiveGL(GLdouble fovY, GLdouble aspect, GLdouble zNear, GLdouble zFar)
    {
        const GLdouble pi = 3.1415926535897932384626433832795;
        GLdouble       fW, fH;

        // fH = tan( (fovY / 2) / 180 * pi ) * zNear;
        fH = tan(fovY / 360 * pi) * zNear;
        fW = fH * aspect;

        glFrustum(-fW, fW, -fH, fH, zNear, zFar);
        //glClear();
    }

    int InitGLObjects()										// Initialize Objects
    {
        if (!ReadObject("Data/Object2.txt", &obj))			// Read Object2 Into obj
        {
            return false;									// If Failed Return False
    }

        SetConnectivity(&obj);								// Set Face To Face Connectivity

        for (unsigned int i = 0; i < obj.nPlanes; i++)			// Loop Through All Object Planes
            CalcPlane(obj, &(obj.planes[i]));				// Compute Plane Equations For All Faces

        return true;										// Return True
}

    int InitGL(GLvoid)										// All Setup For OpenGL Goes Here
    {
        if (!InitGLObjects()) return false;					// Function For Initializing Our Object(s)
        glShadeModel(GL_SMOOTH);							// Enable Smooth Shading
        glClearColor(0.0f, 0.0f, 0.0f, 0.5f);				// Black Background
        glClearDepth(1.0f);									// Depth Buffer Setup
        glClearStencil(0);									// Stencil Buffer Setup
        glEnable(GL_DEPTH_TEST);							// Enables Depth Testing
        glDepthFunc(GL_LEQUAL);								// The Type Of Depth Testing To Do
        glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);	// Really Nice Perspective Calculations

        glLightfv(GL_LIGHT1, GL_POSITION, LightPos);		// Set Light1 Position
        glLightfv(GL_LIGHT1, GL_AMBIENT, LightAmb);			// Set Light1 Ambience
        glLightfv(GL_LIGHT1, GL_DIFFUSE, LightDif);			// Set Light1 Diffuse
        glLightfv(GL_LIGHT1, GL_SPECULAR, LightSpc);		// Set Light1 Specular
        glEnable(GL_LIGHT1);								// Enable Light1
        glEnable(GL_LIGHTING);								// Enable Lighting

        glMaterialfv(GL_FRONT, GL_AMBIENT, MatAmb);			// Set Material Ambience
        glMaterialfv(GL_FRONT, GL_DIFFUSE, MatDif);			// Set Material Diffuse
        glMaterialfv(GL_FRONT, GL_SPECULAR, MatSpc);		// Set Material Specular
        glMaterialfv(GL_FRONT, GL_SHININESS, MatShn);		// Set Material Shininess
        glMaterialfv(GL_FRONT, GL_EMISSION, MatEms);

        glCullFace(GL_BACK);								// Set Culling Face To Back Face
        glEnable(GL_CULL_FACE);								// Enable Culling
        glClearColor(0.1f, 1.0f, 0.5f, 1.0f);				// Set Clear Color (Greenish Color)

        //q = gluNewQuadric();								// Initialize Quadratic
        //gluQuadricNormals(q, GL_SMOOTH);					// Enable Smooth Normal Generation
        //gluQuadricTexture(q, GL_FALSE);						// Disable Auto Texture Coords

        return true;										// Initialization Went OK
    }

    void DrawGLRoom()										// Draw The Room (Box)
    {
        glBegin(GL_QUADS);									// Begin Drawing Quads
        // Floor
        glNormal3f(0.0f, 1.0f, 0.0f);					// Normal Pointing Up
        glVertex3f(-10.0f, -10.0f, -20.0f);				// Back Left
        glVertex3f(-10.0f, -10.0f, 20.0f);				// Front Left
        glVertex3f(10.0f, -10.0f, 20.0f);				// Front Right
        glVertex3f(10.0f, -10.0f, -20.0f);				// Back Right
        // Ceiling
        glNormal3f(0.0f, -1.0f, 0.0f);					// Normal Point Down
        glVertex3f(-10.0f, 10.0f, 20.0f);				// Front Left
        glVertex3f(-10.0f, 10.0f, -20.0f);				// Back Left
        glVertex3f(10.0f, 10.0f, -20.0f);				// Back Right
        glVertex3f(10.0f, 10.0f, 20.0f);				// Front Right
        // Front Wall
        glNormal3f(0.0f, 0.0f, 1.0f);					// Normal Pointing Away From Viewer
        glVertex3f(-10.0f, 10.0f, -20.0f);				// Top Left
        glVertex3f(-10.0f, -10.0f, -20.0f);				// Bottom Left
        glVertex3f(10.0f, -10.0f, -20.0f);				// Bottom Right
        glVertex3f(10.0f, 10.0f, -20.0f);				// Top Right
        // Back Wall
        glNormal3f(0.0f, 0.0f, -1.0f);					// Normal Pointing Towards Viewer
        glVertex3f(10.0f, 10.0f, 20.0f);				// Top Right
        glVertex3f(10.0f, -10.0f, 20.0f);				// Bottom Right
        glVertex3f(-10.0f, -10.0f, 20.0f);				// Bottom Left
        glVertex3f(-10.0f, 10.0f, 20.0f);				// Top Left
        // Left Wall
        glNormal3f(1.0f, 0.0f, 0.0f);					// Normal Pointing Right
        glVertex3f(-10.0f, 10.0f, 20.0f);				// Top Front
        glVertex3f(-10.0f, -10.0f, 20.0f);				// Bottom Front
        glVertex3f(-10.0f, -10.0f, -20.0f);				// Bottom Back
        glVertex3f(-10.0f, 10.0f, -20.0f);				// Top Back
        // Right Wall
        glNormal3f(-1.0f, 0.0f, 0.0f);					// Normal Pointing Left
        glVertex3f(10.0f, 10.0f, -20.0f);				// Top Back
        glVertex3f(10.0f, -10.0f, -20.0f);				// Bottom Back
        glVertex3f(10.0f, -10.0f, 20.0f);				// Bottom Front
        glVertex3f(10.0f, 10.0f, 20.0f);				// Top Front
        glEnd();											// Done Drawing Quads
    }

    int DrawGLScene(GLvoid)									// Main Drawing Routine
    {
        GLmatrix16f Minv;
        GLvector4f wlp, lp;

        // Clear Color Buffer, Depth Buffer, Stencil Buffer
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

        glLoadIdentity();									// Reset Modelview Matrix
        glTranslatef(0.0f, 0.0f, -20.0f);					// Zoom Into Screen 20 Units
        glLightfv(GL_LIGHT1, GL_POSITION, LightPos);		// Position Light1
        //glTranslatef(SpherePos[0], SpherePos[1], SpherePos[2]);	// Position The Sphere
        //gluSphere(q, 1.5f, 32, 16);							// Draw A Sphere

        // calculate light's position relative to local coordinate system
        // dunno if this is the best way to do it, but it actually works
        // if u find another aproach, let me know ;)

        // we build the inversed matrix by doing all the actions in reverse order
        // and with reverse parameters (notice -xrot, -yrot, -ObjPos[], etc.)
        glLoadIdentity();									// Reset Matrix
        glRotatef(-yrot, 0.0f, 1.0f, 0.0f);					// Rotate By -yrot On Y Axis
        glRotatef(-xrot, 1.0f, 0.0f, 0.0f);					// Rotate By -xrot On X Axis
        glGetFloatv(GL_MODELVIEW_MATRIX, Minv);				// Retrieve ModelView Matrix (Stores In Minv)
        lp[0] = LightPos[0];								// Store Light Position X In lp[0]
        lp[1] = LightPos[1];								// Store Light Position Y In lp[1]
        lp[2] = LightPos[2];								// Store Light Position Z In lp[2]
        lp[3] = LightPos[3];								// Store Light Direction In lp[3]
        VMatMult(Minv, lp);									// We Store Rotated Light Vector In 'lp' Array
        glTranslatef(-ObjPos[0], -ObjPos[1], -ObjPos[2]);	// Move Negative On All Axis Based On ObjPos[] Values (X, Y, Z)
        glGetFloatv(GL_MODELVIEW_MATRIX, Minv);				// Retrieve ModelView Matrix From Minv
        wlp[0] = 0.0f;										// World Local Coord X To 0
        wlp[1] = 0.0f;										// World Local Coord Y To 0
        wlp[2] = 0.0f;										// World Local Coord Z To 0
        wlp[3] = 1.0f;
        VMatMult(Minv, wlp);								// We Store The Position Of The World Origin Relative To The
        // Local Coord. System In 'wlp' Array
        lp[0] += wlp[0];									// Adding These Two Gives Us The
        lp[1] += wlp[1];									// Position Of The Light Relative To
        lp[2] += wlp[2];									// The Local Coordinate System

        glColor4f(0.7f, 0.4f, 0.0f, 1.0f);					// Set Color To An Orange
        glLoadIdentity();									// Reset Modelview Matrix
        glTranslatef(0.0f, 0.0f, -20.0f);					// Zoom Into The Screen 20 Units
        DrawGLRoom();										// Draw The Room
        glTranslatef(ObjPos[0], ObjPos[1], ObjPos[2]);		// Position The Object
        glRotatef(xrot, 1.0f, 0.0f, 0.0f);					// Spin It On The X Axis By xrot
        glRotatef(yrot, 0.0f, 1.0f, 0.0f);					// Spin It On The Y Axis By yrot
        DrawGLObject(obj);									// Procedure For Drawing The Loaded Object
        CastShadow(&obj, lp);								// Procedure For Casting The Shadow Based On The Silhouette

        glColor4f(0.7f, 0.4f, 0.0f, 1.0f);					// Set Color To Purplish Blue
        glDisable(GL_LIGHTING);								// Disable Lighting
        glDepthMask(GL_FALSE);								// Disable Depth Mask
        glTranslatef(lp[0], lp[1], lp[2]);					// Translate To Light's Position
        // Notice We're Still In Local Coordinate System
        //gluSphere(q, 0.2f, 16, 8);							// Draw A Little Yellow Sphere (Represents Light)
        glEnable(GL_LIGHTING);								// Enable Lighting
        glDepthMask(GL_TRUE);								// Enable Depth Mask

        xrot += xspeed;										// Increase xrot By xspeed
        yrot += yspeed;										// Increase yrot By yspeed

        glFlush();											// Flush The OpenGL Pipeline
        return true;										// Everything Went OK
    }
    GLvoid ReSizeGLScene(GLsizei width, GLsizei height)		// Resize And Initialize The GL Window
    {
        if (height == 0)										// Prevent A Divide By Zero By
        {
            height = 1;										// Making Height Equal One
        }

        glViewport(0, 0, width, height);						// Reset The Current Viewport

        glMatrixMode(GL_PROJECTION);						// Select The Projection Matrix
        glLoadIdentity();									// Reset The Projection Matrix

        // Calculate The Aspect Ratio Of The Window
        perspectiveGL(45.0f, (GLfloat)width / (GLfloat)height, 0.001f, 100.0f);

        glMatrixMode(GL_MODELVIEW);							// Select The Modelview Matrix
        glLoadIdentity();									// Reset The Modelview Matrix
        }

    bool initGLSL() ;

int main(int argc, char* argv[])
{
    glfwInit();
#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
    //glfwWindowHint(GLFW_RESIZABLE, false);

    GLFWwindow* window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Shadow Volume", nullptr, nullptr);
    glfwMakeContextCurrent(window);

    // glad: load all OpenGL function pointers
    // ---------------------------------------
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    glfwSetKeyCallback(window, key_callback);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // OpenGL configuration
    // --------------------
    glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
    //glEnable(GL_BLEND);
    //glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    // Decide GL+GLSL versions
#if defined(IMGUI_IMPL_OPENGL_ES2)
    // GL ES 2.0 + GLSL 100
    const char* glsl_version = "#version 100";
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
    glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_ES_API);
#elif defined(__APPLE__)
    // GL 3.2 + GLSL 150
    const char* glsl_version = "#version 150";
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);  // 3.2+ only
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);            // Required on Mac
#else
    // GL 3.0 + GLSL 130
    const char* glsl_version = "#version 130";
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
    //glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);  // 3.2+ only
    //glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);            // 3.0+ only
#endif

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;         // Enable Docking
    io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;       // Enable Multi-Viewport / Platform Windows
    //io.ConfigViewportsNoAutoMerge = true;
    //io.ConfigViewportsNoTaskBarIcon = true;

    // Setup Dear ImGui style
    ImGui::StyleColorsDark();
    //ImGui::StyleColorsLight();

    // When viewports are enabled we tweak WindowRounding/WindowBg so platform windows can look identical to regular ones.
    ImGuiStyle& style = ImGui::GetStyle();
    if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
    {
        style.WindowRounding = 0.0f;
        style.Colors[ImGuiCol_WindowBg].w = 1.0f;
    }

    // Setup Platform/Renderer backends
    ImGui_ImplGlfw_InitForOpenGL(window, true);
#ifdef __EMSCRIPTEN__
    ImGui_ImplGlfw_InstallEmscriptenCanvasResizeCallback("#canvas");
#endif
    ImGui_ImplOpenGL3_Init(glsl_version);

    // Our state
    bool show_demo_window = true;
    bool show_another_window = false;
    ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

    //IOUtils::InitGL();
    // initialize game
    // ---------------
    //Breakout.Init();

    // deltaTime variables
    // -------------------
    float deltaTime = 0.0f;
    float lastFrame = 0.0f;

    //glm::mat4 projection = glm::ortho(0.0f, 800.0f, 600.0f, 0.0f, -1.0f, 1.0f);
    ReSizeGLScene(SCREEN_WIDTH, SCREEN_HEIGHT);
    InitGL();

    while (!glfwWindowShouldClose(window))
    {
        // calculate delta time
        // --------------------
        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;
        glfwPollEvents();

        int depth;
        glGetIntegerv(GL_MODELVIEW_STACK_DEPTH, &depth);

        DrawGLScene();
        
        // @todo seperate this into layers to render
        // Start the Dear ImGui frame
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        // 1. Show the big demo window (Most of the sample code is in ImGui::ShowDemoWindow()! You can browse its code to learn more about Dear ImGui!).
        if (show_demo_window)
            ImGui::ShowDemoWindow(&show_demo_window);

        // 2. Show a simple window that we create ourselves. We use a Begin/End pair to create a named window.
        {
            // Background music volume
            static float volume = 0.0f;
            static int counter = 0;

            ImGui::Begin("Cheat");                          // Create a window called "Hello, world!" and append into it.

            ImGui::Text("List of all the cheat in game: ");               // Display some text (you can use a format strings too)
            ImGui::Checkbox("Demo Window", &show_demo_window);      // Edit bools storing our window open/close state
            ImGui::Checkbox("Another Window", &show_another_window);

            ImGui::SliderFloat("Background music", &volume, 0.0f, 1.0f);            // Edit 1 float using a slider from 0.0f to 1.0f
            //Breakout.BackgroundMusic->setVolume(volume);
            ImGui::ColorEdit3("clear color", (float*)&clear_color); // Edit 3 floats representing a color

            //static float vec4a[4] = { 0.10f, 0.20f, 0.30f, 0.44f };
            ImGui::InputFloat3("Shadowed object pos", ObjPos);

            if (ImGui::Button("Button"))                            // Buttons return true when clicked (most widgets return true when edited/activated)
                counter++;
            ImGui::SameLine();
            ImGui::Text("counter = %d", counter);

            ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / io.Framerate, io.Framerate);
            ImGui::End();
        }

        // 3. Show another simple window.
        if (show_another_window)
        {
            ImGui::Begin("Another Window", &show_another_window);   // Pass a pointer to our bool variable (the window will have a closing button that will clear the bool when clicked)
            ImGui::Text("Hello from another window!");
            if (ImGui::Button("Close Me"))
                show_another_window = false;
            ImGui::End();
        }

        // Rendering
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        // Update and Render additional Platform Windows
        // (Platform functions may change the current OpenGL context, so we save/restore it to make it easier to paste this code elsewhere.
        //  For this specific demo app we could also call glfwMakeContextCurrent(window) directly)
        if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
        {
            GLFWwindow* backup_current_context = glfwGetCurrentContext();
            ImGui::UpdatePlatformWindows();
            ImGui::RenderPlatformWindowsDefault();
            glfwMakeContextCurrent(backup_current_context);
        }
        glfwSwapBuffers(window);

    }

    // delete all resources as loaded using the resource manager
    // ---------------------------------------------------------
    //ResourceManager::Clear();

    glfwTerminate();
    return 0;
}

//bool initGLSL() {
//    const int MAX_LENGTH
//}


void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
    // when a user presses the escape key, we set the WindowShouldClose property to true, closing the application
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
    //if (key >= 0 && key < 1024)
    //{
    //    if (action == GLFW_PRESS)
    //        Breakout.Keys[key] = true;
    //    else if (action == GLFW_RELEASE) {
    //        Breakout.Keys[key] = false;
    //        Breakout.KeysProcessed[key] = false;
    //    }

    //}
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and 
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}