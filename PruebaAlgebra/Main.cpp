#include <iostream>
#include <raylib.h>

using namespace std;

void CameraHandler(Camera3D& camera, int& cameraMode);
void GetMagnitude(Vector3 endPos, float& magnitude);
void GetFirstPerpendicular(Vector3 endPos, Vector3& perpendicular);
void NormalizeVector(Vector3& vector);
void SetNewMagnitude(Vector3& vector, float designedMagnitude);
void GetVertical(Vector3 endPos, Vector3& vertical);
void DrawInstructions();
void DrawPyramid(Vector3 startPos, Vector3 vectorA, Vector3 vectorB, Vector3 vectorC, float magnitudeC);
float CalculateScalarProduct(Vector3 vector1, Vector3 vector2);

void main()
{
    Vector2 magnitudeTextPos = { 10, 30 };
    Vector2 vectorATextPos = { 10, 50 };
    Vector2 vectorBTextPos = { 10, 70 };
    Vector2 vectorCTextPos = { 10, 90 };

    Vector3 startPos = { 0.0f, 0.0f, 0.0f };

    //Vector3 vectorA = {5.0f,0.0f, 0.0f}; //Vector A 
    Vector3 vectorA = { (float)GetRandomValue(1, 8), (float)GetRandomValue(1, 8), 0 };//(float)GetRandomValue(1, 8)}; //Vector A 
    Vector3 vectorB = { 0.0f, 0.0f, 0.0f }; //Vector B
    Vector3 vectorC = { 0.0f, 0.0f, 0.0f }; //Vector C

    int userInput;

    float magnitudeA = 1; //A magnitude
    float magnitudeB = 1; //B magnitude
    float magnitudeC = 1; //C magnitude

    bool starting = true;

    SetExitKey(27);
    InitWindow(800, 450, "Algebra TP2");

    Model model;

    Camera camera = { 0 };
    camera.position = { 0.0f, 2.0f, 4.0f };    // Camera position
    camera.target = { 0.0f, 2.0f, 0.0f };      // Camera looking at point
    camera.up = { 0.0f, 1.0f, 0.0f };          // Camera up vector (rotation towards target)
    camera.fovy = 100.0f;                                // Camera field-of-view Y
    camera.projection = CAMERA_PERSPECTIVE;             // Camera projection type

    int cameraMode = CAMERA_FIRST_PERSON;

    camera.position = startPos;

    camera.position.x += 2.0f;
    camera.position.y += 2.0f;
    camera.position.z += 2.0f;

    camera.target = startPos;

    DisableCursor();

    SetTargetFPS(60);

    GetMagnitude(vectorA, magnitudeA); //A magnitude
    GetFirstPerpendicular(vectorA, vectorB); //Crea vector B

    SetNewMagnitude(vectorB, magnitudeA); //Normaliza y multiplica magnitud Vector B por la magnitud Vector A
    GetMagnitude(vectorB, magnitudeB); //Magnitud actual de Vector B

    GetVertical(vectorA, vectorC); //Crea Vector C
    

    cout << "\nMagnitud A: " << magnitudeA << endl;
    cout << "\nMagnitud B: " << magnitudeB << endl;

    while (!WindowShouldClose())
    {
        CameraHandler(camera, cameraMode);
        BeginDrawing();
        ClearBackground(RAYWHITE);

        DrawText(TextFormat("Vector A and B magnitude: %.2f", magnitudeA), magnitudeTextPos.x, magnitudeTextPos.y, 15, BLACK);
        DrawText("Vector A: RED", vectorATextPos.x, vectorATextPos.y, 15, BLACK);
        DrawText("Vector B: GREEN", vectorBTextPos.x, vectorBTextPos.y, 15, BLACK);
        DrawText("Vector C: BLUE", vectorCTextPos.x, vectorCTextPos.y, 15, BLACK);

        int key;

        BeginMode3D(camera);

        DrawLine3D(startPos, vectorA, RED); //Dibuja Vector A
        DrawLine3D(startPos, vectorB, GREEN); //Dibuja Vector B
        DrawLine3D(startPos, vectorC, BLUE); //Dibuja Vector C

        DrawPyramid(startPos, vectorA, vectorB, vectorC, magnitudeC);

        EndMode3D();

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

float CalculateScalarProduct(Vector3 vector1, Vector3 vector2)
{
    float scalarProduct = vector1.x * vector2.x + vector1.y * vector2.y + vector1.z * vector2.z;

    return scalarProduct;
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

void DrawPyramid(Vector3 startPos, Vector3 vectorA, Vector3 vectorB, Vector3 vectorC, float magnitudeC)
{
    Vector3 vertex;
    vertex.x = vectorA.x + vectorB.x;
    vertex.y = vectorA.y + vectorB.y;
    vertex.z = vectorA.z + vectorB.z;

    Vector3 verticalA;
    verticalA.x = vectorA.x + vectorC.x;
    verticalA.y = vectorA.y + vectorC.y;
    verticalA.z = vectorA.z + vectorC.z;

    Vector3 verticalB;
    verticalB.x = vectorB.x + vectorC.x;
    verticalB.y = vectorB.y + vectorC.y;
    verticalB.z = vectorB.z + vectorC.z;

    Vector3 verticalC;
    verticalC.x = vertex.x + vectorC.x;
    verticalC.y = vertex.y + vectorC.y;
    verticalC.z = vertex.z + vectorC.z;

    DrawLine3D(vectorB, vertex, PINK); //Dibuja Vector A bis
    DrawLine3D(vectorA, vertex, ORANGE); //Dibuja Vector B bis

    float scalarAB = CalculateScalarProduct(startPos, vertex);
    float scalarSV = CalculateScalarProduct(vectorA, vectorB);

    float scalarAA = CalculateScalarProduct(vertex, verticalA);
    float scalarBB = CalculateScalarProduct(vectorB, verticalC);
    float scalarCC = CalculateScalarProduct(verticalB, startPos);
    float scalarDD = CalculateScalarProduct(vectorC, vectorA);

    float scalarAA2 = CalculateScalarProduct(startPos, verticalA);
    float scalarBB2 = CalculateScalarProduct(vectorC, vectorB);
    float scalarCC2 = CalculateScalarProduct(verticalB, vertex);
    float scalarDD2 = CalculateScalarProduct(verticalC, vectorA);

    cout << "\nScalar AB: " << scalarAB << endl; //90 grados
    cout << "Scalar SV: " << scalarSV << endl; //90 grados
    
    cout << "\nScalar AA: " << scalarAA << endl; //no da
    cout << "Scalar BB: " << scalarBB << endl; //no da
    cout << "Scalar CC: " << scalarCC << endl; //90 grados
    cout << "Scalar DD: " << scalarDD << endl; //90 grados

    cout << "\nScalar AA2: " << scalarAA2 << endl; //90 grados
    cout << "Scalar BB2: " << scalarBB2 << endl; //90 grados
    cout << "Scalar CC2: " << scalarCC2 << endl; //no da
    cout << "Scalar DD2: " << scalarDD2 << endl; //no da

    DrawLine3D(vectorA, verticalA, VIOLET); //Dibuja Vertical A
    DrawLine3D(vectorB, verticalB, VIOLET); //Dibuja Vertical B
    DrawLine3D(vertex, verticalC, VIOLET); //Dibuja Vertical C

    DrawLine3D(vectorC, verticalA, VIOLET); //Dibuja parallel A
    DrawLine3D(verticalA, verticalC, VIOLET); //Dibuja parallel B
    DrawLine3D(verticalC, verticalB, VIOLET); //Dibuja parallel C
    DrawLine3D(verticalB, vectorC, VIOLET); //Dibuja parallel D
}