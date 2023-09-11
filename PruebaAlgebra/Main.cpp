#include <iostream>
#include <raylib.h>

using namespace std;

void GetMagnitude(Vector3 endPos, float& magnitude);
void GetFirstPerpendicular(Vector3 endPos, Vector3& perpendicular);
void NormalizeVector(Vector3& vector);
void SetNewMagnitude(Vector3& vector, float designedMagnitude);
void GetVertical(Vector3 endPos, Vector3& vertical);
void DrawInstructions();

void main()
{
    Vector2 magnitude1Pos = { 10,30 };

    //Vector A datos
    Vector3 startPos = { 0.0f, 0.0f, 0.0f };
    Vector3 endPos = { 5.0f, 0.0f, 0.0f };
    Color color = RED;

    Vector3 perpendicular = { 0.0f, 0.0f, 0.0f }; //Vector B
    Vector3 vertical = { 0.0f, 0.0f, 0.0f }; //Vector C

    int userInput;

    float magnitude = 1; //A magnitude
    float magnitude2 = 1; //B magnitude
    float magnitude3 = 1; //C magnitude

    bool starting = true;

    SetExitKey(27);
    InitWindow(800, 450, "Algebra TP2");
    Camera3D camera;

    camera = { 0 };
    camera.position = { 0.0f, 13.0f, 0.0f };   // Camera position
    camera.target = { 0.0f, 0.0f, 0.0f };      // Camera looking at point
    camera.up = { 0.0f, 0.5f, 0.0f };          // Camera up vector (rotation towards target)
    camera.fovy = 1000.0f;                     // Camera field-of-view Y
    camera.projection = CAMERA_PERSPECTIVE;

    SetTargetFPS(60);

    GetMagnitude(endPos, magnitude); //A magnitude
    GetFirstPerpendicular(endPos, perpendicular); //Crea vector B

    SetNewMagnitude(perpendicular, magnitude); //Normaliza y multiplica magnitud Vector B por la magnitud Vector A
    GetMagnitude(perpendicular, magnitude2); //Magnitud actual de Vector B

    GetVertical(endPos, vertical); //Crea Vector C
    
    camera.position = startPos;

    camera.position.x += 2.0f;
    camera.position.y += 2.0f;
    camera.position.z += 2.0f;

    camera.target = startPos;

    cout << "\nMagnitud A: " << magnitude << endl;
    cout << "\nMagnitud B: " << magnitude2 << endl;

    while (!WindowShouldClose())
    {
        UpdateCamera(&camera, CAMERA_FREE);
        BeginDrawing();
        ClearBackground(RAYWHITE);

        DrawText(TextFormat("Vector magnitude: %01i", magnitude), magnitude1Pos.x, magnitude1Pos.y, 15, BLACK);

        int key;

        BeginMode3D(camera);

        DrawLine3D(startPos, endPos, color);
        DrawLine3D(startPos, perpendicular, GREEN);
        DrawLine3D(startPos, vertical, BLUE);

        EndMode3D();

        if (starting)
        {
            //DrawText(TextFormat("Ingrese el valor deseado: "), ((float)GetScreenWidth() / 2), ((float)GetScreenHeight() / 2), 13, BLACK);
            DrawInstructions();

            key = GetCharPressed() - 48;

            //DrawText(TextFormat("Key: %01i", key), ((float)GetScreenWidth() / 2), ((float)GetScreenHeight() / 2), 13, BLACK);

            if (key > 1 && key < 10)
            {
                SetNewMagnitude(vertical, magnitude / key);
                GetMagnitude(vertical, magnitude3);

                cout << "\nInput: " << key << endl;
                cout << "\nMagnitud C: " << magnitude3 << endl;

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
   
        //BeginMode3D(camera);

        //DrawLine3D(startPos, endPos, color);
        //DrawLine3D(startPos, perpendicular, GREEN);
        //DrawLine3D(startPos, vertical, BLUE);

        //EndMode3D();

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
    NormalizeVector(vector);

    vector.x *= designedMagnitude;
    vector.y *= designedMagnitude;
    vector.z *= designedMagnitude;
}

void GetVertical(Vector3 endPos, Vector3& vertical)
{
    vertical.z = endPos.x;
    vertical.x = -1 *endPos.z;
}

void DrawInstructions()
{
    int recPosX = GetScreenWidth() / 3 * 2 - 40;
    int recPosY = GetScreenHeight() / 12;
    int recWidth = GetScreenWidth() / 3 - 20;
    int recHeight = GetScreenHeight() / 12 * 10;
    Color recColor = BLACK;

    int textX = recPosX + 10;
    int fontSize = 18;
    Color textColor = RAYWHITE;

    int textY1 = recPosY + 10;
    int textY2 = recPosY + 30;
    int textY3 = recPosY + 70;

    DrawRectangle(recPosX, recPosY, recWidth, recHeight, recColor);

    DrawText("Choose a value for n to", textX, textY1, fontSize, textColor);
    DrawText("set Vector C magnitude:", textX, textY2, fontSize, textColor);
    DrawText("(1/n * Vector A magnitude)", textX, textY3, fontSize, textColor);
}
