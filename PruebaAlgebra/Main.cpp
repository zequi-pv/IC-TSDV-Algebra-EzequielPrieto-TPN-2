#include <iostream>
#include <raylib.h>
#include <raymath.h>

using namespace std;

void SetCamera(Camera& camera, Vector3 startPos);
void ShowMenu(float magnitudeA);
void CameraHandler(Camera3D& camera, int& cameraMode);
void GetMagnitude(Vector3 endPos, float& magnitude);
void GetFirstPerpendicular(Vector3 endPos, Vector3& perpendicular);
void NormalizeVector(Vector3& vector);
void SetNewMagnitude(Vector3& vector, float designedMagnitude);
void CrossProduct(Vector3 vector1, Vector3 vector2, Vector3 vertex, Vector3& vectorPerp);
void GetVertical(Vector3 endPos, Vector3& vertical);
void DrawInstructions();
void DrawPyramid(Vector3 startPos, Vector3 vectorA, Vector3 vectorB, Vector3 vectorC, float magnitudeC, float userInput, float& perimeter, float& surface, float& volume);
float CalculateScalarProduct(Vector3 vector1, Vector3 vector2);
void ShowFinalCalcResults(float perimeter, float surface, float volume);

void main()
{
    SetRandomSeed(time(NULL));

    Vector3 startPos = { 0.0f, 0.0f, 0.0f };

    Vector3 vectorA = { (float)GetRandomValue(2.0f, 8.0f), (float)GetRandomValue(2.0f, 8.0f), (float)GetRandomValue(2.0f, 8.0f)}; //Vector A 
    Vector3 vectorB = { 0.0f, 0.0f, 0.0f }; //Vector B
    Vector3 vectorC = { 0.0f, 0.0f, 0.0f }; //Vector C

    float userInput = 0;

    float magnitudeA = 1; //A magnitude
    float magnitudeB = 1; //B magnitude
    float magnitudeC = 1; //C magnitude

    bool starting = true;

    SetExitKey(27);
    InitWindow(800, 450, "Algebra TP2");

    Camera camera = { 0 };
    SetCamera(camera, startPos);
    int cameraMode = CAMERA_FIRST_PERSON;

    DisableCursor();

    SetTargetFPS(60);

    GetMagnitude(vectorA, magnitudeA); //A magnitude
    GetFirstPerpendicular(vectorA, vectorB); //Crea vector B

    SetNewMagnitude(vectorB, magnitudeA); //Normaliza y multiplica magnitud Vector B por la magnitud Vector A
    GetMagnitude(vectorB, magnitudeB); //Magnitud actual de Vector B

    //GetVertical(vectorA, vectorC); //Crea Vector C
    CrossProduct(vectorA, vectorB, startPos, vectorC);

    cout << "\nMagnitud A: " << magnitudeA << endl;
    cout << "\nMagnitud B: " << magnitudeB << endl;

    while (!WindowShouldClose())
    {
        int key;
        float perimeter{};
        float surface{};
        float volume{};

        CameraHandler(camera, cameraMode);
        BeginDrawing();
        ClearBackground(RAYWHITE);

        ShowMenu(magnitudeA);

        BeginMode3D(camera);

        DrawPyramid(startPos, vectorA, vectorB, vectorC, magnitudeC, userInput, perimeter, surface, volume);

        EndMode3D();

        ShowFinalCalcResults(perimeter, surface, volume);

        if (starting)
        {
            DrawInstructions();

            key = GetCharPressed() - 48;

            if (key > 1 && key < 10)
            {
                SetNewMagnitude(vectorC, magnitudeA / key); //Normaliza el Vector C y le da la magnitud deseada por el usuario
                GetMagnitude(vectorC, magnitudeC); //Vector C magnitude actual

                cout << "\nInput: " << key << endl;
                cout << "\nMagnitud C: " << magnitudeC << endl;

                userInput = (float)key;

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

        DrawFPS(10, 10);
        EndDrawing();
    }

    CloseWindow();
}

void SetCamera(Camera& camera, Vector3 startPos)
{
    camera.position = { 0.0f, 2.0f, 4.0f };    // Camera position
    camera.target = { 0.0f, 2.0f, 0.0f };      // Camera looking at point
    camera.up = { 0.0f, 1.0f, 0.0f };          // Camera up vector (rotation towards target)
    camera.fovy = 100.0f;                                // Camera field-of-view Y
    camera.projection = CAMERA_PERSPECTIVE;             // Camera projection type

    camera.position = startPos;

    camera.position.x += 2.0f;
    camera.position.y += 2.0f;
    camera.position.z += 2.0f;

    camera.target = startPos;
}

void ShowMenu(float magnitudeA)
{
    Vector2 magnitudeTextPos = { 10, 30 };
    Vector2 vectorATextPos = { 10, 50 };
    Vector2 vectorBTextPos = { 10, 70 };
    Vector2 vectorCTextPos = { 10, 90 };


    DrawText(TextFormat("Vector A and B magnitude: %.2f", magnitudeA), magnitudeTextPos.x, magnitudeTextPos.y, 15, BLACK);
    DrawText("Vector A: RED", vectorATextPos.x, vectorATextPos.y, 15, BLACK);
    DrawText("Vector B: GREEN", vectorBTextPos.x, vectorBTextPos.y, 15, BLACK);
    DrawText("Vector C: BLUE", vectorCTextPos.x, vectorCTextPos.y, 15, BLACK);
}

void CameraHandler(Camera3D& camera, int& cameraMode)
{
    if (IsKeyPressed(KEY_F))
    {
        cameraMode = CAMERA_FREE;
        camera.up = { 0.0f, 1.0f, 0.0f };
    }

    if (IsKeyPressed(KEY_G))
    {
        cameraMode = CAMERA_FIRST_PERSON;
        camera.up = { 0.0f, 1.0f, 0.0f };
    }

    if (IsKeyPressed(KEY_H))
    {
        cameraMode = CAMERA_THIRD_PERSON;
        camera.up = { 0.0f, 1.0f, 0.0f };
    }

    if (IsKeyPressed(KEY_J))
    {
        cameraMode = CAMERA_ORBITAL;
        camera.up = { 0.0f, 1.0f, 0.0f };
    }

    if (IsKeyPressed(KEY_P))
    {
        if (camera.projection == CAMERA_PERSPECTIVE)
        {
            cameraMode = CAMERA_THIRD_PERSON;
            camera.position = { 0.0f, 2.0f, -100.0f };
            camera.target = { 0.0f, 2.0f, 0.0f };
            camera.up = { 0.0f, 1.0f, 0.0f };
            camera.projection = CAMERA_ORTHOGRAPHIC;
            camera.fovy = 20.0f; 
        }
        else if (camera.projection == CAMERA_ORTHOGRAPHIC)
        {
            cameraMode = CAMERA_THIRD_PERSON;
            camera.position = { 0.0f, 2.0f, 10.0f };
            camera.target = { 0.0f, 2.0f, 0.0f };
            camera.up = { 0.0f, 1.0f, 0.0f };
            camera.projection = CAMERA_PERSPECTIVE;
            camera.fovy = 60.0f;
        }
    }

    UpdateCamera(&camera, cameraMode);
}

//float CalculateScalarProduct(Vector3 vector1, Vector3 vector2)
//{
//    float scalarProduct = (vector1.x * vector2.x) + (vector1.y * vector2.y) + (vector1.z * vector2.z);
//
//    return scalarProduct;
//}

void GetMagnitude(Vector3 endPos, float& magnitude)
{
    magnitude = sqrt(pow(endPos.x, 2.0f) + pow(endPos.y, 2.0f) + pow(endPos.z, 2.0f));
}

void GetFirstPerpendicular(Vector3 endPos, Vector3& perpendicular)
{
    perpendicular.x = endPos.z;
    perpendicular.z = -1 * endPos.x;
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

void CrossProduct(Vector3 vector1, Vector3 vector2, Vector3 vertex, Vector3& vectorPerp)
{
    vectorPerp.x = ((vector1.y * vector2.z) - (vector1.z * vector2.y)) + vertex.x;
    vectorPerp.y = ((vector1.z * vector2.x) - (vector1.x * vector2.z)) + vertex.y;
    vectorPerp.z = ((vector1.x * vector2.y) - (vector1.y * vector2.x)) + vertex.z;
}

//void GetVertical(Vector3 endPos, Vector3& vertical)
//{
//    vertical.y = endPos.x;
//    vertical.x = -1 *endPos.y;
//}

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
    int textY4 = recPosY + 110;
    int textY5 = recPosY + 140;
    int textY6 = recPosY + 170;
    int textY7 = recPosY + 200;
    int textY8 = recPosY + 230;
    int textY9 = recPosY + 260;
    int textY10 = recPosY + 290;
    int textY11 = recPosY + 320;

    DrawRectangle(recPosX, recPosY, recWidth, recHeight, recColor);

    DrawText("Choose a value for n to", textX, textY1, fontSize, textColor);
    DrawText("set Vector C magnitude:", textX, textY2, fontSize, textColor);
    DrawText("(1/n * Vector A magnitude)", textX, textY3, fontSize, textColor);

    DrawText("Press key 2 = 1/2", textX, textY4, fontSize, textColor);
    DrawText("Press key 3 = 1/3", textX, textY5, fontSize, textColor);
    DrawText("Press key 4 = 1/4", textX, textY6, fontSize, textColor);
    DrawText("Press key 5 = 1/5", textX, textY7, fontSize, textColor);
    DrawText("Press key 6 = 1/6", textX, textY8, fontSize, textColor);
    DrawText("Press key 7 = 1/7", textX, textY9, fontSize, textColor);
    DrawText("Press key 8 = 1/8", textX, textY10, fontSize, textColor);
    DrawText("Press key 9 = 1/9", textX, textY11, fontSize, textColor);
}

void DrawPyramid(Vector3 startPos, Vector3 vectorA, Vector3 vectorB, Vector3 vectorC, float magnitudeC, float userInput, float& perimeter, float& surface, float& volume)
{
    Vector3 transformX; //Es el desplazamiento para cada piso en x
    transformX.x = vectorA.x / userInput;
    transformX.y = vectorA.y / userInput;
    transformX.z = vectorA.z / userInput;

    Vector3 transformY; //Es el desplazamiento para cada piso en y
    transformY.x = vectorB.x / userInput;
    transformY.y = vectorB.y / userInput;
    transformY.z = vectorB.z / userInput;

    //Es la reducción en diagonal desde el vértice correspondiente por cada piso
    Vector3 reductionStartPos = Vector3Add(transformX, transformY);
    Vector3 reductionA = Vector3Add(Vector3Scale(transformX, -1.0f), transformY);
    Vector3 reductionB = Vector3Subtract(transformX, transformY);
    Vector3 reductionC = Vector3Subtract(Vector3Scale(transformX, -1.0f), transformY);

    //Auxiliares para no modificar los valores originales
    Vector3 dinamicStartPos = startPos;
    Vector3 dinamicA = vectorA;
    Vector3 dinamicB = vectorB;
    Vector3 dinamicC = Vector3Add(vectorA, vectorB);

    DrawLine3D(startPos, vectorA, RED); //Dibuja Vector A
    DrawLine3D(startPos, vectorB, GREEN); //Dibuja Vector B
    DrawLine3D(startPos, vectorC, BLUE); //Dibuja Vector C

    float floorQnty = userInput / 2; //Cantidad de veces que se repetirá el for que dibuja los pisos. 
    
    float actualMagnitude{};

    actualMagnitude = Vector3Distance(dinamicStartPos, Vector3Scale(reductionStartPos, 0)), Vector3Add(dinamicA, Vector3Scale(reductionA, 0));

    surface += (actualMagnitude * actualMagnitude) * 2;//////////perdon :)

    for (int i = 0; i < floorQnty; i++)
    {
        //verticals
        DrawLine3D(Vector3Add(dinamicStartPos, (Vector3Scale(reductionStartPos, i))), Vector3Add(Vector3Add(dinamicStartPos, (Vector3Scale(reductionStartPos, i))), vectorC), PINK);
        DrawLine3D(Vector3Add(dinamicA, (Vector3Scale(reductionA, i))), Vector3Add(Vector3Add(dinamicA, (Vector3Scale(reductionA, i))), vectorC), PINK);
        DrawLine3D(Vector3Add(dinamicB, (Vector3Scale(reductionB, i))), Vector3Add(Vector3Add(dinamicB, (Vector3Scale(reductionB, i))), vectorC), PINK);
        DrawLine3D(Vector3Add(dinamicC, (Vector3Scale(reductionC, i))), Vector3Add(Vector3Add(dinamicC, (Vector3Scale(reductionC, i))), vectorC), PINK); 

        DrawLine3D(Vector3Add(dinamicStartPos, Vector3Scale(reductionStartPos, i)), Vector3Add(dinamicA, Vector3Scale(reductionA, i)), VIOLET);
        actualMagnitude = Vector3Distance(dinamicStartPos, Vector3Scale(reductionStartPos, i)), Vector3Add(dinamicA, Vector3Scale(reductionA, i));
        perimeter += ((actualMagnitude * 8.0f) + (magnitudeC * 4.0f));
        surface +=  (actualMagnitude * 4.0f) * magnitudeC;
        volume += ((actualMagnitude * actualMagnitude) * magnitudeC);
       
        DrawLine3D(Vector3Add(dinamicStartPos, Vector3Scale(reductionStartPos, i)), Vector3Add(dinamicB, Vector3Scale(reductionB, i)), VIOLET);
        DrawLine3D(Vector3Add(dinamicC, Vector3Scale(reductionC, i)), Vector3Add(dinamicA, Vector3Scale(reductionA, i)), VIOLET);
        DrawLine3D(Vector3Add(dinamicC, Vector3Scale(reductionC, i)), Vector3Add(dinamicB, Vector3Scale(reductionB, i)), VIOLET);

        dinamicStartPos = Vector3Add(dinamicStartPos, vectorC);
        dinamicA = Vector3Add(dinamicA, vectorC);
        dinamicB = Vector3Add(dinamicB, vectorC);
        dinamicC = Vector3Add(dinamicC, vectorC);

        DrawLine3D(Vector3Add(dinamicStartPos, Vector3Scale(reductionStartPos, i)), Vector3Add(dinamicA, Vector3Scale(reductionA, i)), VIOLET);
        DrawLine3D(Vector3Add(dinamicStartPos, Vector3Scale(reductionStartPos, i)), Vector3Add(dinamicB, Vector3Scale(reductionB, i)), VIOLET);
        DrawLine3D(Vector3Add(dinamicC, Vector3Scale(reductionC, i)), Vector3Add(dinamicA, Vector3Scale(reductionA, i)), VIOLET);
        DrawLine3D(Vector3Add(dinamicC, Vector3Scale(reductionC, i)), Vector3Add(dinamicB, Vector3Scale(reductionB, i)), VIOLET);
    }
}

void ShowFinalCalcResults(float perimeter, float surface, float volume)
{
    Vector2 perimeterTextPos = { 600, 30 };
    Vector2 surfaceTextPos = { 600, 50 };
    Vector2 volumeTextPos = { 600, 70 };

    DrawText(TextFormat("Pyramid Perimeter: %.2f", perimeter), perimeterTextPos.x, perimeterTextPos.y, 15, BLACK);
    DrawText(TextFormat("Pyramid Surface: %.2f", surface), surfaceTextPos.x, surfaceTextPos.y, 15, BLACK);
    DrawText(TextFormat("Pyramid Volume: %.2f", volume), volumeTextPos.x, volumeTextPos.y, 15, BLACK);
}
