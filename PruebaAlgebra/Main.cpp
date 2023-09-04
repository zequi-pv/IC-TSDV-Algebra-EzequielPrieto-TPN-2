#include <iostream>
#include <raylib.h>


using namespace std;

void GetMagnitude(Vector3 startPos, Vector3 endPos, float& magnitude);
void GetPerpendicular(Vector3 startPos, Vector3 endPos, Vector3& perpendicular);



void main()
{
    Vector3 startPos = { 1,1,1 };
    Vector3 endPos = { 4,2,9 };
    Color color = RED;

    Vector3 perpendicular;

    float magnitude;

    SetExitKey(27);
    InitWindow(800, 450, "My first Pong");
    Camera3D camera;

    camera = { 0 };
    camera.position = { 0.0f, 13.0f, 10.0f };  // Camera position
    camera.target = { 0.0f, 0.0f, 0.0f };      // Camera looking at point
    camera.up = { 0.0f, 0.5f, 0.0f };          // Camera up vector (rotation towards target)
    camera.fovy = 50.0f;                                // Camera field-of-view Y
    camera.projection = CAMERA_PERSPECTIVE;

    SetTargetFPS(60);


    GetMagnitude(startPos, endPos, magnitude);
    GetPerpendicular(startPos, endPos, perpendicular);

    while (!WindowShouldClose())
    {
        UpdateCamera(&camera, CAMERA_FREE);

        if (IsKeyDown('Z'))
        {
            camera.target = { 0.0f, 0.0f, 0.0f };
        }

        BeginDrawing();
        ClearBackground(RAYWHITE);
        BeginMode3D(camera);

        DrawLine3D(startPos, endPos, color);
        DrawLine3D(startPos, perpendicular, color);

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

void GetPerpendicular(Vector3 startPos, Vector3 endPos, Vector3& perpendicular)
{
    perpendicular.x = ((startPos.y * endPos.z) - (startPos.z * endPos.y)) + startPos.x;
    perpendicular.y = ((startPos.z * endPos.x) - (startPos.x * endPos.z)) + startPos.y;
    perpendicular.z = ((startPos.x * endPos.y) - (startPos.y * endPos.x)) + startPos.z;
}