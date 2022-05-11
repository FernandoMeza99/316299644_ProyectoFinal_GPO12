#include <iostream>
#include <cmath>

// Std. Includes
#include <string>

// GLEW
#include <GL/glew.h>

// GLFW
#include <GLFW/glfw3.h>

// Other Libs
#include "SOIL2/SOIL2.h"
#include "stb_image.h"

// GL includes
#include "Shader.h"
#include "Camera.h"
#include "Model.h"

// GLM Mathemtics
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


// Properties
const GLuint WIDTH = 800, HEIGHT = 600;
int SCREEN_WIDTH, SCREEN_HEIGHT;

// Function prototypes
void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mode);
void MouseCallback(GLFWwindow* window, double xPos, double yPos);
void DoMovement();
void animacion();
void animacionBotas();
void animacionCerveza();
void animacionLibro();


// Camera
Camera camera(glm::vec3(0.0f, 0.0f, 0.0f));
bool keys[1024];
GLfloat lastX = 400, lastY = 300;
bool firstMouse = true;


// Light attributes
glm::vec3 lightPos(0.5f, 0.5f, 2.5f);
glm::vec3 PosIni(-5.993f, 1.47f, -4.544f);
float movelightPosX = 0.0f;
float movelightPosY = 0.0f;
float movelightPosZ = 0.0f;
GLfloat deltaTime = 0.0f;
GLfloat lastFrame = 0.0f;



// Positions of the point lights
glm::vec3 pointLightPositions[] = {
    glm::vec3(0.0f,0.0f, 0.0f),
    glm::vec3(0.0f,0.0f, 0.0f),
    glm::vec3(0.0f,0.0f,  0.0f),
    glm::vec3(0.0f,0.0f, 0.0f)
};

//Variables Animación Cabra

float gravedad = 9.8;
float velocidadI = 5;
float tiempo = 0.0;
float rotKit = 0.0;
float movKitY = 0.0;
float movKitX = 0.0;
float movKitYaux = velocidadI * sin(rotKit);
float movKitXaux = velocidadI * cos(rotKit);


// variables bota //

float alturaBotaI = 0.0; 
float alturaBotaD = 0.0;

// -- variables cerveza -- //

float alturaBeer = 0.0;
float inclinarBeer = 0.0;

// -- Variables del Libro -- 

float rot = 0.0f;

//controlar los estados de animacion de la cabra

bool cabraBool = false;
bool recorrido1 = true;
bool recorrido2 = false;
bool recorrido3 = false;
bool recorrido4 = false;


// controlar los estados de animacion del libro
bool librobool = false;
bool abierto = true;
bool cerrado = false;

// controlar los estados de animacion de las botas

bool botaBool = false;
bool arribaI = true;
bool abajoI = false;
bool arribaD = false;
bool abajoD = false;

// controlar los estados de animacion de la cerveza

bool cervezaBool = false;
bool arribaCerveza = true;
bool servir = false;
bool noServir = false;
bool abajoCerveza = false;



float vertices[] = {
      -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
         0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
         0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
         0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,

        -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
         0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,

        -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
        -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
        -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
        -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
        -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
        -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,

         0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
         0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
         0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
         0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
         0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
         0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,

        -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
         0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
         0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
         0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,

        -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
         0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
        -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f
};

glm::vec3 Light1 = glm::vec3(0);


int main()
{
    // Init GLFW
    glfwInit();
    // Set all the required options for GLFW
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

    // Create a GLFWwindow object that we can use for GLFW's functions
    GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "Proyecto Final", nullptr, nullptr);

    if (nullptr == window)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();

        return EXIT_FAILURE;
    }

    glfwMakeContextCurrent(window);

    glfwGetFramebufferSize(window, &SCREEN_WIDTH, &SCREEN_HEIGHT);

    // Set the required callback functions
    glfwSetKeyCallback(window, KeyCallback);
    glfwSetCursorPosCallback(window, MouseCallback);

    // GLFW Options
    glfwSetInputMode( window, GLFW_CURSOR, GLFW_CURSOR_DISABLED );

    // Set this to true so GLEW knows to use a modern approach to retrieving function pointers and extensions
    glewExperimental = GL_TRUE;
    // Initialize GLEW to setup the OpenGL Function pointers
    if (GLEW_OK != glewInit())
    {
        std::cout << "Failed to initialize GLEW" << std::endl;
        return EXIT_FAILURE;
    }

    // Define the viewport dimensions
    glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);

    // OpenGL options
   // glEnable(GL_DEPTH_TEST);

    // Setup and compile our shaders
    Shader lightingShader("Shaders/lighting.vs", "Shaders/lighting.frag");
    Shader lampShader("Shaders/lamp2.vs", "Shaders/lamp2.frag");
    Shader shader("Shaders/modelLoading.vs", "Shaders/modelLoading.frag");
    



    // Load models
    
    Model beer((char*)"Models/Beer/mclarensS.obj");
    Model sillon((char*)"Models/Sillon/sillon.obj");
    Model sillon2((char*)"Models/Sillon/sillon2.obj");
    Model sombrilla((char*)"Models/Sombrilla/SombrillaAmarilla.obj");
    Model libroA((char*)"Models/Libro/libroA.obj");
    Model libroB((char*)"Models/Libro/libroB.obj");
    Model cabra((char*)"Models/Cabra/Goat.obj");
    Model mesa((char*)"Models/Mesa/mesa.obj");
    Model botaI((char*)"Models/Bota/botaIzq.obj");
    Model botaD((char*)"Models/Bota/botaDer.obj");
    Model piso((char*)"Models/Fachada/piso.obj");
    Model pared1((char*)"Models/Fachada/pared1.obj");
    Model pared2((char*)"Models/Fachada/pared2.obj");
    Model pared3((char*)"Models/Fachada/pared3.obj");
    Model pared4((char*)"Models/Fachada/pared4.obj");
    Model ladrillosG1((char*)"Models/Fachada/ladrillosG1.obj");
    Model ladrillosGVentana((char*)"Models/Fachada/ladrillosGVentana.obj");
    Model ladrillosGPuerta((char*)"Models/Fachada/ladrillosGPuerta.obj");
    Model ladrillosGPiso((char*)"Models/Fachada/ladrillosGPiso.obj");
    Model ladrillosGTecho((char*)"Models/Fachada/ladrillosGTecho.obj");
    Model barandal((char*)"Models/Fachada/barandal.obj");
    Model logo((char*)"Models/Fachada/logo.obj");
    Model puerta((char*)"Models/Fachada/puerta.obj");
    Model ventana1((char*)"Models/Fachada/ventanaIzq.obj");
    Model ventana2((char*)"Models/Fachada/ventanaDer.obj");

   // glm::mat4 projection = glm::perspective(camera.GetZoom(), (float)SCREEN_WIDTH / (float)SCREEN_HEIGHT, 0.1f, 100.0f);

    

    // First, set the container's VAO (and VBO)
    GLuint VBO, VAO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    // Position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(0);
    // normal attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    // Load textures

    lightingShader.Use();
    glUniform1i(glGetUniformLocation(lightingShader.Program, "material.diffuse"), 0);

    glm::mat4 projection = glm::perspective(camera.GetZoom(), (GLfloat)SCREEN_WIDTH / (GLfloat)SCREEN_HEIGHT, 0.1f, 100.0f);
    
    // Game loop
    while (!glfwWindowShouldClose(window))
    {
        // Set frame time
        GLfloat currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        // Check and call events
        glfwPollEvents();
        DoMovement();
        animacion();
        animacionBotas();
        animacionCerveza();
        animacionLibro();

        // Clear the colorbuffer
        glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // OpenGL options
        glEnable(GL_DEPTH_TEST);

        // -- CARGANDO MODELOS -- 

        lightingShader.Use();
        //GLint lightPosLoc = glGetUniformLocation(lightingShader.Program, "light.position");
        GLint viewPosLoc = glGetUniformLocation(lightingShader.Program, "viewPos");
        //glUniform3f(lightPosLoc, lightPos.x + movelightPosX, lightPos.y + movelightPosY, lightPos.z + movelightPosZ);
        glUniform3f(viewPosLoc, camera.GetPosition().x, camera.GetPosition().y, camera.GetPosition().z);


        

        // Directional light
        glUniform3f(glGetUniformLocation(lightingShader.Program, "dirLight.direction"), -0.2f, -1.0f, -0.3f);
        glUniform3f(glGetUniformLocation(lightingShader.Program, "dirLight.ambient"), 0.5f, 0.5f, 0.5f);
        glUniform3f(glGetUniformLocation(lightingShader.Program, "dirLight.diffuse"), 0.1f, 0.1f, 0.1f);
        glUniform3f(glGetUniformLocation(lightingShader.Program, "dirLight.specular"), 0.7f, 0.7f, 0.7f);
        
        // Point light 1
        glm::vec3 lightColor;
        lightColor.x = abs(sin(glfwGetTime() * Light1.x));
        lightColor.y = abs(sin(glfwGetTime() * Light1.y));
        lightColor.z = abs(sin(glfwGetTime() * Light1.z));


        glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[0].position"), pointLightPositions[0].x, pointLightPositions[0].y, pointLightPositions[0].z);
        glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[0].ambient"), lightColor.x, lightColor.y, lightColor.z);
        glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[0].diffuse"), lightColor.x, lightColor.y, lightColor.z);
        glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[0].specular"), 0.0f, 0.0f, 0.0f);
        glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[0].constant"), 1.0f);
        glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[0].linear"), 0.7f);
        glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[0].quadratic"), 1.8f);

        // SpotLight
        glUniform3f(glGetUniformLocation(lightingShader.Program, "spotLight.position"), camera.GetPosition().x, camera.GetPosition().y, camera.GetPosition().z);
        glUniform3f(glGetUniformLocation(lightingShader.Program, "spotLight.direction"), camera.GetFront().x, camera.GetFront().y, camera.GetFront().z);
        glUniform3f(glGetUniformLocation(lightingShader.Program, "spotLight.ambient"), 1.0f, 1.0f, 1.0f);
        glUniform3f(glGetUniformLocation(lightingShader.Program, "spotLight.diffuse"), 1.0f, 1.0f, 1.0f);
        glUniform3f(glGetUniformLocation(lightingShader.Program, "spotLight.specular"), 0.5f, 0.5f, 0.5f);
        glUniform1f(glGetUniformLocation(lightingShader.Program, "spotLight.constant"), 1.0f);
        glUniform1f(glGetUniformLocation(lightingShader.Program, "spotLight.linear"), 0.07f);
        glUniform1f(glGetUniformLocation(lightingShader.Program, "spotLight.quadratic"), 0.17f);
        glUniform1f(glGetUniformLocation(lightingShader.Program, "spotLight.cutOff"), glm::cos(glm::radians(12.5f)));
        glUniform1f(glGetUniformLocation(lightingShader.Program, "spotLight.outerCutOff"), glm::cos(glm::radians(15.0f)));

        // Set material properties
        glUniform1f(glGetUniformLocation(lightingShader.Program, "material.shininess"), 16.0f);
        


        glm::mat4 view = camera.GetViewMatrix();
        //glUniformMatrix4fv(glGetUniformLocation(lightingShader.Program, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
        //glUniformMatrix4fv(glGetUniformLocation(lightingShader.Program, "view"), 1, GL_FALSE, glm::value_ptr(view));

        // Get the uniform locations
        GLint modelLoc = glGetUniformLocation(lightingShader.Program, "model");
        GLint viewLoc = glGetUniformLocation(lightingShader.Program, "view");
        GLint projLoc = glGetUniformLocation(lightingShader.Program, "projection");

        glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
        glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));


        glm::mat4 model(1);
       //lBindVertexArray(0);

        // Set material properties

        //glUniform3f(glGetUniformLocation(lightingShader.Program, "material.ambient"), 0.19225f, 0.19225f, 0.19225f);
        //glUniform3f(glGetUniformLocation(lightingShader.Program, "material.diffuse"), 0.50754f, 0.50754f, 0.50754f);  //color del objeto
        //glUniform3f(glGetUniformLocation(lightingShader.Program, "material.specular"), 0.50754f, 0.50754f, 0.50754f);   // si queremos
        //glUniform1f(glGetUniformLocation(lightingShader.Program, "material.shininess"), 0.4f);             //que sea mas opaca

        //BEER

        model = glm::mat4(1);
        model = glm::translate(model, glm::vec3(4.558f, 3.694f + alturaBeer, 2.559f));
        model = glm::rotate(model, glm::radians(-inclinarBeer), glm::vec3(1.0f, 0.0f, 0.0f));
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        beer.Draw(lightingShader);
        glUniform4f(glGetUniformLocation(lightingShader.Program, "colorAlpha"), 1.0, 1.0, 1.0, 1.0);

        // SILLON
        model = glm::mat4(1);
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));   
        sillon.Draw(lightingShader);
   
        // -- Sillon 2 --

        model = glm::mat4(1);
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        sillon2.Draw(lightingShader);
   
        // -- SOMBRILLA --

        model = glm::mat4(1);
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        sombrilla.Draw(lightingShader);

        // -- LIBRO ---

        model = glm::mat4(1);
        model = glm::translate(model, glm::vec3(3.0f, 3.65f, 3.0f));
        model = glm::rotate(model, glm::radians(rot), glm::vec3(0.0f, 0.0f, 1.0f));
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        libroA.Draw(lightingShader);


        model = glm::mat4(1);
        model = glm::translate(model, glm::vec3(3.0f, 3.65f, 3.0f));
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        libroB.Draw(lightingShader);
        // -- CABRA --

        model = glm::mat4(1);
        model = glm::translate(model, PosIni + glm::vec3(movKitX, movKitY, 0));
        model = glm::rotate(model, glm::radians(rotKit), glm::vec3(0.0f, 1.0f, 0.0));
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        cabra.Draw(lightingShader);

        // -- MESA --

        model = glm::mat4(1);
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        mesa.Draw(lightingShader);

        // -- BOTA Izquierda--
        model = glm::mat4(1);
        model = glm::translate(model, glm::vec3(0.0f, 0.15 + alturaBotaI, -1.587f));
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        botaI.Draw(lightingShader);

        // -- Bota Derecha -- 
        model = glm::mat4(1);
        model = glm::translate(model, glm::vec3(0.0f, 0.15 + alturaBotaD, -2.713));
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        botaD.Draw(lightingShader);
   

        // -- PISO --
        model = glm::mat4(1);
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        piso.Draw(lightingShader);

        // --PARED 1--
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        pared1.Draw(lightingShader);

        // --PARED 2 --
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        pared2.Draw(lightingShader);
        // -- PARED 3 --
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        pared3.Draw(lightingShader);
        // -- PARED 4 --
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        pared4.Draw(lightingShader);

        // -- Pared ladrillos grises 1
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        ladrillosG1.Draw(lightingShader);

        // -- Pared ladrillos grises Ventana
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        ladrillosGVentana.Draw(lightingShader);

        // -- Pared ladrillos grises Puerta
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        ladrillosGPuerta.Draw(lightingShader);

        // -- Ladrillos grises piso

        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        ladrillosGPiso.Draw(lightingShader);

        // -- Ladrillos grises techo

        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        ladrillosGTecho.Draw(lightingShader);

        // -- BARANDAL --
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        barandal.Draw(lightingShader);

        // -- Logo --
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        logo.Draw(lightingShader);

        // -- Puerta --
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        puerta.Draw(lightingShader);

        // -- Ventana Izquierda --

        glEnable(GL_BLEND);//Avtiva la funcionalidad para trabajar el canal alfa
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        model = glm::mat4(1);
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        glUniform1i(glGetUniformLocation(lightingShader.Program, "activaTransparencia"), 0);
        glUniform4f(glGetUniformLocation(lightingShader.Program, "colorAlpha"), 1.0, 1.0, 1.0, 0.5);
        ventana1.Draw(lightingShader);
        glDisable(GL_BLEND);


        // -- Ventana Derecha

        glEnable(GL_BLEND);//Avtiva la funcionalidad para trabajar el canal alfa
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        model = glm::mat4(1);
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        glUniform1i(glGetUniformLocation(lightingShader.Program, "activaTransparencia"), 0);
        glUniform4f(glGetUniformLocation(lightingShader.Program, "colorAlpha"), 1.0, 1.0, 1.0, 0.5);
        ventana2.Draw(lightingShader);
        glDisable(GL_BLEND);

        glBindVertexArray(0);


        //simular mi luz y ver donde esta ubicada
        lampShader.Use();
        glUniformMatrix4fv(glGetUniformLocation(lampShader.Program, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
        glUniformMatrix4fv(glGetUniformLocation(lampShader.Program, "view"), 1, GL_FALSE, glm::value_ptr(view));
        model = glm::mat4(1.0f);
        model = glm::translate(model, lightPos + movelightPosX + movelightPosY + movelightPosZ);
        model = glm::scale(model, glm::vec3(0.02f));
        glUniformMatrix4fv(glGetUniformLocation(lampShader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 36);
        glBindVertexArray(0);

        // Swap the buffers
        glfwSwapBuffers(window);
    }

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);

    glfwTerminate();
    return 0;
}


// Moves/alters the camera positions based on user input
void DoMovement()
{
    // Camera controls
    if (keys[GLFW_KEY_W] || keys[GLFW_KEY_UP])
    {
        camera.ProcessKeyboard(FORWARD, deltaTime);
    }

    if (keys[GLFW_KEY_S] || keys[GLFW_KEY_DOWN])
    {
        camera.ProcessKeyboard(BACKWARD, deltaTime);
    }

    if (keys[GLFW_KEY_A] || keys[GLFW_KEY_LEFT])
    {
        camera.ProcessKeyboard(LEFT, deltaTime);
    }

    if (keys[GLFW_KEY_D] || keys[GLFW_KEY_RIGHT])
    {
        camera.ProcessKeyboard(RIGHT, deltaTime);
    }

    

    if (keys[GLFW_KEY_I])
    {
        pointLightPositions[3].x += 0.1f;
        pointLightPositions[3].y += 0.1f;
        pointLightPositions[3].z += 0.1f;
        cabraBool = true;
    }

    // Teclas animacion cabra

    if (keys[GLFW_KEY_O])
    {
        cabraBool = false;
    }

    if (keys[GLFW_KEY_M])
    {
        librobool = true;
    }


    // teclas animacion libro //
    if (keys[GLFW_KEY_M])
    {
        librobool = true;
    }
    if (keys[GLFW_KEY_N])
    {
        librobool = false;
    }

    // teclas animacion botas

    if (keys[GLFW_KEY_B])
    {
        botaBool = true;
    }
    if (keys[GLFW_KEY_V])
    {
        botaBool = false;
    }

    // -- teclas animacion cerveza --

    if (keys[GLFW_KEY_P])
    {
        cervezaBool = true;
    }
    if (keys[GLFW_KEY_O])
    {
        cervezaBool = false;
    }



}

void animacionCerveza() {
    // -- MOVIMIENTO CERVEZA --

    if (cervezaBool) {
        
        if (arribaCerveza) {
            alturaBeer += 0.025f;

            if (alturaBeer > 1.0) {

                servir = true;
                arribaCerveza = false;
            }
        }

        if (servir) {

            inclinarBeer += 0.2;

            if (inclinarBeer > 120) {

                servir = false;
                noServir = true;
            }
        }

        if (noServir) {

            inclinarBeer -= 0.2;

            if (inclinarBeer < 0.0) {
                noServir = false;
                abajoCerveza = true;
            }

        }

        if (abajoCerveza) {

            alturaBeer -= 0.01f;

            if (alturaBeer < 0.0) {
                abajoCerveza = false;
                arribaCerveza = true;
            }
        }
    }
}

void animacionLibro() {
    // -- movimiento libro -- //
    if (librobool) {

        if (abierto) {
            rot += 0.5f;

            if (rot > 90) {
                abierto = false;
                cerrado = true;
            }
        }

        if (cerrado) {
            rot -= 0.5f;

            if (rot < 0) {
                abierto = true;
                cerrado = false;
            }
        }
    }
}

void animacionBotas() {
    // -- movimiento botas --  //
    if (botaBool) {
        if (arribaI) {
            alturaBotaI += 0.05f;

            if (alturaBotaI > 2.0) {
                arribaI = false;
                abajoI = true;
            }
        }

        if (abajoI) {

            alturaBotaI -= 0.05f;

            if (alturaBotaI < 0.15) {
                arribaD = true;
                abajoI = false;

            }
        }

        if (arribaD) {

            alturaBotaD += 0.05f;

            if (alturaBotaD > 2.0) {

                arribaD = false;
                abajoD = true;
            }
        }

        if (abajoD) {

            alturaBotaD -= 0.05;

            if (alturaBotaD < 0.15) {
                abajoD = false;
                arribaI = true;
            }
        }


    }

}

void animacion()
{


    //Movimiento Cabra
    if (cabraBool)
    {

        if (recorrido1)
        {
            
            movKitYaux = velocidadI + (-gravedad * tiempo);
            tiempo += 0.001;
            movKitYaux = movKitYaux / 1000;
            movKitY += movKitYaux;
            movKitX += 0.009f;
            if (movKitYaux < 0)
            {
                movKitXaux = 0.09;
                recorrido1 = false;
                recorrido2 = true;
            }
        }
        if (recorrido2)
        {
            movKitYaux = velocidadI + (-gravedad * tiempo);
            tiempo += 0.001;
            movKitYaux = movKitYaux / 1000;
            movKitXaux += 0.09f;

            movKitY += movKitYaux;
            movKitX += 0.009f;
            if (movKitXaux > 47)
            {
                tiempo = 0;
                recorrido3 = true;
                recorrido2 = false;

            }
        }

        if (recorrido3)
        {

            rotKit = 180;
            movKitYaux = velocidadI + (-gravedad * tiempo);
            tiempo += 0.001;
            movKitYaux = movKitYaux / 1000;
            //movKitZaux += 0.09f;

            movKitY += movKitYaux;
            movKitX -= 0.009f;
            if (movKitYaux < 0)
            {
                movKitXaux = 122;
                recorrido4 = true;
                recorrido3 = false;

            }
        }

        if (recorrido4)
        {
            rotKit = 180;
            movKitYaux = velocidadI + (-gravedad * tiempo);
            tiempo += 0.001;
            movKitYaux = movKitYaux / 1000;
            movKitXaux -= 0.09f;

            movKitY += movKitYaux;
            movKitX -= 0.009f;
            if (movKitXaux < 78)
            {
                rotKit = 0;
                tiempo = 0;
                recorrido1 = true;
                recorrido4 = false;
            }
        }
        


    }
}

// Is called whenever a key is pressed/released via GLFW
void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
    if (GLFW_KEY_ESCAPE == key && GLFW_PRESS == action)
    {
        glfwSetWindowShouldClose(window, GL_TRUE);
    }

    if (key >= 0 && key < 1024)
    {
        if (action == GLFW_PRESS)
        {
            keys[key] = true;
        }
        else if (action == GLFW_RELEASE)
        {
            keys[key] = false;
        }
    }

    if (keys[GLFW_KEY_L])
    {   //DERECHA
        //activanim = true;
        movelightPosX += 0.1f;
    }

    if (keys[GLFW_KEY_H])
    {   //IZQUIERDA
        //activanim = true;
        movelightPosX -= 0.1f;
    }

    if (keys[GLFW_KEY_M])
    {   //ARRIBA
        //activanim = true;
        movelightPosY += 0.1f;
    }

    if (keys[GLFW_KEY_N])
    {   //ABAJO
        //activanim = true;
        movelightPosY -= 0.1f;
    }

    if (keys[GLFW_KEY_J])
    {   //ATRAS
        //activanim = true;
        movelightPosZ += 0.1f;
    }

    if (keys[GLFW_KEY_U])
    {   //ADELANTESSSS
        //activanim = true;
        movelightPosZ -= 0.1f;
    }

    
}

void MouseCallback(GLFWwindow* window, double xPos, double yPos)
{
    if (firstMouse)
    {
        lastX = xPos;
        lastY = yPos;
        firstMouse = false;
    }

    GLfloat xOffset = xPos - lastX;
    GLfloat yOffset = lastY - yPos;  // Reversed since y-coordinates go from bottom to left

    lastX = xPos;
    lastY = yPos;

    camera.ProcessMouseMovement(xOffset, yOffset);
}
