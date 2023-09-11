#include <iostream>
#include <raylib.h>


using namespace std;

void GetMagnitude(Vector3 endPos, float& magnitude);
void GetFirstPerpendicular(Vector3 endPos, Vector3& perpendicular);
void NormalizeVector(Vector3& vector);
void SetNewMagnitude(Vector3& vector, float designedMagnitude);
void GetVertical(Vector3 endPos, Vector3& vertical);



void main()
{
    Vector2 magnitude1Pos = { 10,10 };
    Vector2 magnitude2Pos = { 10,50 };
    Vector2 magnitude3Pos = { 10,90 };
    //int key;

    Vector3 startPos = { 0.0f, 0.0f, 0.0f };
    Vector3 endPos = { 5.0f, 0.0f, 0.0f };
    Color color = RED;

    Vector3 perpendicular = { 0.0f, 0.0f, 0.0f };
    Vector3 vertical = { 0.0f, 0.0f, 0.0f };

    int userInput;

    float magnitude = 1;
    float magnitude2 = 1;
    float magnitude3 = 1;


    
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


    GetMagnitude(endPos, magnitude);
    GetFirstPerpendicular(endPos, perpendicular);
    GetMagnitude(perpendicular, magnitude2);
    NormalizeVector(perpendicular);
    GetMagnitude(perpendicular, magnitude2);
    SetNewMagnitude(perpendicular, magnitude);
    GetMagnitude(perpendicular, magnitude2);

    GetVertical(endPos, vertical);
    GetMagnitude(vertical, magnitude3);
    NormalizeVector(vertical);
    


    camera.position = startPos;

    camera.position.x += 2.0f;
    camera.position.y += 2.0f;
    camera.position.z += 2.0f;

    camera.target = startPos;


    cout << endl << magnitude << endl << magnitude2 << endl << magnitude3 << endl;

    while (!WindowShouldClose())
    {
        UpdateCamera(&camera, CAMERA_FREE);
        BeginDrawing();
        ClearBackground(RAYWHITE);

        
        DrawText(TextFormat("Vector magnitude: %01i", magnitude), magnitude1Pos.x, magnitude1Pos.y, 30, BLACK);
        int key;
        if (starting)
        {
            DrawText(TextFormat("Ingrese el valor deseado: "), ((float)GetScreenWidth() / 2), ((float)GetScreenHeight() / 2), 13, BLACK);
            
            key = GetCharPressed() - 48;
            //DrawText(TextFormat("Key: %01i", key), ((float)GetScreenWidth() / 2), ((float)GetScreenHeight() / 2), 13, BLACK);
            if (key > 1 && key < 10)
            {
                SetNewMagnitude(vertical, magnitude / key);
                cout << key << endl << magnitude3 << endl;
                starting = false;
            }
           
        }
        else
        {
            if (IsKeyDown('Z'))
            {
                camera.target = startPos;
            }

        }
   
        BeginMode3D(camera);

        DrawLine3D(startPos, endPos, color);
        DrawLine3D(startPos, perpendicular, GREEN);
        DrawLine3D(startPos, vertical, BLUE);

        EndMode3D();
        DrawFPS(10, 10);
        EndDrawing();
    }

    CloseWindow();
}


void GetMagnitude(Vector3 endPos, float& magnitude)
{
    magnitude = sqrt(pow(endPos.x, 2.0f) + pow(endPos.y, 2.0f) + pow(endPos.z, 2.0f));
}

void GetFirstPerpendicular(Vector3 endPos, Vector3& perpendicular)
{
    perpendicular.x = endPos.y;
    perpendicular.y = -1 * endPos.x;
   
}

void NormalizeVector(Vector3& vector)
{
    float vectorMagnitude;

    GetMagnitude(vector, vectorMagnitude);

    vector.x /= vectorMagnitude;
    vector.y /= vectorMagnitude;
    vector.z /= vectorMagnitude;
}

void SetNewMagnitude(Vector3& vector, float designedMagnitude)
{
    NormalizeVector( vector);

    vector.x *= designedMagnitude;
    vector.y *= designedMagnitude;
    vector.z *= designedMagnitude;
}

void GetVertical(Vector3 endPos, Vector3& vertical)
{
    vertical.z = endPos.x;
    vertical.x = -1 *endPos.z;
}

void SetHeight(Vector3& vector, float designedMagnitude)
{

}
