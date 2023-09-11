#include <iostream>
#include <raylib.h>


using namespace std;

void GetMagnitude(Vector3 startPos, Vector3 endPos, float& magnitude);
void GetFirstPerpendicular(Vector3 startPos, Vector3 endPos, Vector3& perpendicular);
void NormalizeVector(Vector3& vector, float vectorMagnitude);
void SetNewMagnitude(Vector3& vector, float designedMagnitude);



void main()
{
    Vector2 magnitude1Pos = { 10,10 };
    Vector2 magnitude2Pos = { 10,50 };
    Vector2 magnitude3Pos = { 10,90 };
    //int key;

    Vector3 startPos = { 0.0f, 0.0f, 0.0f };
    Vector3 endPos = { 5.0f, 0.0f, 0.0f };
    Color color = RED;

    Vector3 perpendicular;

    int userInput;

    float magnitude;
    float magnitude2;


    
    bool starting = true;

    SetExitKey(27);
    InitWindow(800, 450, "Algebra TP2");
    Camera3D camera;

    camera = { 0 };
    camera.position = { 0.0f, 13.0f, 0.0f };  // Camera position
    camera.target = { 0.0f, 0.0f, 0.0f };      // Camera looking at point
    camera.up = { 0.0f, 0.5f, 0.0f };          // Camera up vector (rotation towards target)
    camera.fovy = 1000.0f;                                // Camera field-of-view Y
    camera.projection = CAMERA_PERSPECTIVE;

    SetTargetFPS(60);


    GetMagnitude(startPos, endPos, magnitude);
    GetFirstPerpendicular(startPos, endPos, perpendicular);
    GetMagnitude(startPos, perpendicular, magnitude2);
    NormalizeVector(perpendicular, magnitude2);
    GetMagnitude(startPos, perpendicular, magnitude2);
    SetNewMagnitude(perpendicular, magnitude);
    GetMagnitude(startPos, perpendicular, magnitude2);

    Vector3 camPos = startPos;

    camPos.x += 2.0f;
    camPos.y += 2.0f;
    camPos.z += 2.0f;

    camera.position = camPos;
    camera.target = startPos;


    cout << endl << magnitude << endl << magnitude2 << endl;

    while (!WindowShouldClose())
    {
        UpdateCamera(&camera, CAMERA_FREE);
        BeginDrawing();

        DrawLine3D(startPos, endPos, color);
        DrawLine3D(startPos, perpendicular, GREEN);
        DrawText(TextFormat("Vector magnitude: %01i", magnitude), magnitude1Pos.x, magnitude1Pos.y, 30, BLACK);
        
        if (starting)
        {
            DrawText(TextFormat("Ingrese el valor deseado: "), ((float)GetScreenWidth() / 2), ((float)GetScreenHeight() / 2), 13, BLACK);
            
            for (int key = 0; key < 9; key++)
            {
                if (IsKeyDown(key))
                {    
                    userInput = key;
                    starting = false;
             
                }
            }   
        }
        else
        {

        }

        if (IsKeyDown('Z'))
        {
            camera.target = startPos;
        }

        ClearBackground(RAYWHITE);
        BeginMode3D(camera);

        

        EndMode3D();
        DrawFPS(10, 10);
        EndDrawing();
    }

    CloseWindow();
}


void GetMagnitude(Vector3 startPos, Vector3 endPos, float& magnitude)
{
    magnitude = sqrt(pow(endPos.x - startPos.x, 2.0f) + pow(endPos.y - startPos.y, 2.0f) + pow(endPos.z - startPos.z, 2.0f));
}

void GetFirstPerpendicular(Vector3 startPos, Vector3 endPos, Vector3& perpendicular)
{
    perpendicular.x = endPos.y;
    perpendicular.y = -1 * endPos.x;
   
}

void NormalizeVector(Vector3& vector,float vectorMagnitude)
{
    vector.x /= vectorMagnitude;
    vector.y /= vectorMagnitude;
    vector.z /= vectorMagnitude;
}

void SetNewMagnitude(Vector3& vector, float designedMagnitude)
{
    vector.x *= designedMagnitude;
    vector.y *= designedMagnitude;
    vector.z *= designedMagnitude;
}

void SetHeight(Vector3& vector, float designedMagnitude)
{

}
