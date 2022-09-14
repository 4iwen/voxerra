#include "Chunk.h"

void Chunk::GenerateChunk(FastNoiseLite iNoise, int iPosX,int iPosY,  int iLength, int iWidth,int iHeight)
{
    cout << ("Generating Chunk");
    posX = iPosX;
    posY = iPosY;

    width = iWidth;
    length = iLength;
    height = iHeight;

    FillEmpty();

    GenerateNoise(iNoise);

    GenerateVertices(); //VERTS ALWAYS FIRST
    GenerateIndicies();

    GenerateGLData();
}

void Chunk::FillEmpty()
{
    for (int x = 0; x < width; x++) // X coordinates
    {
        for (int y = 0; y < height; y++) // Y coordinates
        {
            for (int z = 0; z < length; z++) // Y coordinates
            {
                blockData[x][y][z] = air;
            }
        }
    }
}

void Chunk::GenerateNoise(FastNoiseLite noise)
{
    for (int x = 0; x < width; x++) // X coordinates
    {
        for (int z = 0; z < length; z++) // Y coordinates
        {
            float y = abs(noise.GetNoise((float)x, (float)z) * 50);
            cout << "noise for " << x << z << " is " << (int)y << " height" << endl;
            blockData[x][(int)y][z] = grass;
            for (int j = (int)y; j >= 0; --j)
            {
                blockData[x][j][z] = dirt;
            }
        }
    }
    //FOR WRITING OUT IN THE CONSOLE
    for (int x = 0; x < width; x++) // X coordinates
    {
        for (int z = 0; z < length; z++) // Y coordinates
        {
            if(blockData[x][4][z] != dirt)
            {
                cout<< "#";
            }
            else if(blockData[x][7][z] != dirt)
            {
                cout<< "H";
            }
            else if(blockData[x][10][z] != dirt)
            {
                cout<< "A";
            }
            else
            {
                cout<< "O";
            }
        }
        cout << endl;
    }
}

void Chunk::GenerateVertices()
{
    for (int x = 0; x < width; x++) {
        for (int z = 0; z < length; z++) {
            for (int y = 0; y < height; y++) {
                if(blockData[x][y][z] != air) // If block is occupied we check around.
                    {
                    if(x > 0 && CheckAround(x - 1,y,z)) // Checks Left
                    {
                        AddLeft(x,y,z);
                        cout << "Left x :" << x  - 1 << " y : " << y << " z : " << z << endl;
                    }
                    if(x < width && CheckAround(x + 1,y,z))// Checks Right
                    {
                        AddRight(x,y,z);
                        cout << "right x : " << x + 1 << " y : " << y << " z : " << z << endl;
                    }
                    if(y > 0 && CheckAround(x,y - 1,z))// Checks Down
                    {
                        AddBottom(x,y,z);
                        cout << "bot x : " << x << " y : " << y - 1 << " z : " << z << endl;
                    }
                    if(y < height && CheckAround(x,y + 1,z))// Checks Top
                    {
                        AddTop(x,y,z);
                        cout << "top x : " << x << " y : " << y + 1 << " z : " << z << endl;
                    }

                    if(z >= 0 && CheckAround(x,y,z - 1))// Checks Back
                    {
                        AddBack(x,y,z);
                        cout << "back x : " << x << " y : " << y << " z : " << z - 1 << endl;
                    }
                    if(z < length && CheckAround(x,y,z + 1))// Checks Forth
                    {
                        AddForth(x, y, z);
                        cout << "forth x : " << x << " y : " << y << " z : " << z + 1 << endl;
                    }
                }
            }
        }
    }
    cout<< "Vertices Generated" << endl;
}

bool Chunk::CheckAround(int blockX,int blockY,int blockZ)
{
    return(blockData[blockX][blockY][blockZ] == air);
}



//function that only adds the vertices to the vector if they dont overlap with another vert
void Chunk::AddVert(vert v)
{
    for (int c = 0; c < verts.size(); c++)
    {
        if(verts[c].x == v.x && verts[c].y == v.y && verts[c].z == v.z)
        {
            verts.erase(verts.begin() + c);
            return;
        }
    }
    verts.push_back(v);
}

void Chunk::GenerateIndicies() {
    for(int one = 0; one < verts.size();one++)
    {
        cout << "";
        for(int two = 0; two < verts.size();two++)
        {
            cout << "";
            for(int three = 0; three < verts.size();three++)
            {
                cout << "";
                if(one != two && two != three && one != three)
                {
                    if(verts[one].x == verts[two].x + 1 && verts[one].y == verts[two].y && verts[one].z == verts[two].z)
                    {
                        if(verts[one].x == verts[three].x && verts[one].y == verts[three].y + 1 && verts[one].z == verts[three].z)
                        {
                            indices.push_back(one);
                            indices.push_back(two);
                            indices.push_back(three);
                            //cout << ("Added triangle for ")<< one << " " << two << " " << three << " " << indices.size() << endl;
                        }
                    }
                    if(verts[one].x == verts[two].x - 1 && verts[one].y == verts[two].y && verts[one].z == verts[two].z)
                    {
                        if(verts[one].x == verts[three].x && verts[one].y == verts[three].y - 1 && verts[one].z == verts[three].z)
                        {
                            indices.push_back(one);
                            indices.push_back(two);
                            indices.push_back(three);
                            //cout << ("Added triangle for ")<< one << " " << two << " " << three << " " << indices.size() << endl;
                        }
                    }
                    if(verts[one].x == verts[two].x && verts[one].y == verts[two].y && verts[one].z == verts[two].z + 1)
                    {
                        if(verts[one].x == verts[three].x && verts[one].y == verts[three].y + 1 && verts[one].z == verts[three].z)
                        {
                            indices.push_back(one);
                            indices.push_back(two);
                            indices.push_back(three);
                            //cout << ("Added triangle for ")<< one << " " << two << " " << three << " " << indices.size() << endl;
                        }
                    }
                    if(verts[one].x == verts[two].x && verts[one].y == verts[two].y && verts[one].z == verts[two].z - 1)
                    {
                        if(verts[one].x == verts[three].x && verts[one].y == verts[three].y - 1 && verts[one].z == verts[three].z)
                        {
                            indices.push_back(one);
                            indices.push_back(two);
                            indices.push_back(three);
                            //cout << ("Added triangle for ")<< one << " " << two << " " << three << " " << indices.size() << endl;
                        }
                    }
                }
            }
        }
    }
}

void Chunk::AddTop(int blockX,int blockY,int blockZ)
{
    vert curVert;
    curVert.x = blockX;
    curVert.y = blockY + 1;
    curVert.z = blockZ;
    curVert.red = 1;
    curVert.green = 1;
    curVert.blue = 1;
    AddVert(curVert);

    curVert.x = blockX + 1;
    curVert.y = blockY + 1;
    curVert.z = blockZ;
    curVert.red = 1;
    curVert.green = 1;
    curVert.blue = 1;
    AddVert(curVert);

    curVert.x = blockX + 1;
    curVert.y = blockY + 1;
    curVert.z = blockZ + 1;
    curVert.red = 1;
    curVert.green = 1;
    curVert.blue = 1;
    AddVert(curVert);

    curVert.x = blockX;
    curVert.y = blockY + 1;
    curVert.z = blockZ + 1;
    curVert.red = 1;
    curVert.green = 1;
    curVert.blue = 1;
    AddVert(curVert);

    cout<<"added top"<<endl;
}

void Chunk::AddBottom(int blockX,int blockY,int blockZ)
{
    vert curVert;
    curVert.x = blockX;
    curVert.y = blockY;
    curVert.z = blockZ;
    curVert.red = 1;
    curVert.green = 1;
    curVert.blue = 1;
    AddVert(curVert);

    curVert.x = blockX + 1;
    curVert.y = blockY;
    curVert.z = blockZ;
    curVert.red = 1;
    curVert.green = 1;
    curVert.blue = 1;
    AddVert(curVert);

    curVert.x = blockX + 1;
    curVert.y = blockY;
    curVert.z = blockZ + 1;
    curVert.red = 1;
    curVert.green = 1;
    curVert.blue = 1;
    AddVert(curVert);

    curVert.x = blockX;
    curVert.y = blockY;
    curVert.z = blockZ + 1;
    curVert.red = 1;
    curVert.green = 1;
    curVert.blue = 1;
    AddVert(curVert);

    cout<<"added bottom"<<endl;
}

void Chunk::AddBack(int blockX,int blockY,int blockZ)
{
    vert curVert;
    curVert.x = blockX;
    curVert.y = blockY;
    curVert.z = blockZ;
    curVert.red = 1;
    curVert.green = 1;
    curVert.blue = 1;
    AddVert(curVert);

    curVert.x = blockX;
    curVert.y = blockY;
    curVert.z = blockZ + 1;
    curVert.red = 1;
    curVert.green = 1;
    curVert.blue = 1;
    AddVert(curVert);

    curVert.x = blockX;
    curVert.y = blockY + 1;
    curVert.z = blockZ + 1;
    curVert.red = 1;
    curVert.green = 1;
    curVert.blue = 1;
    AddVert(curVert);

    curVert.x = blockX;
    curVert.y = blockY + 1;
    curVert.z = blockZ;
    curVert.red = 1;
    curVert.green = 1;
    curVert.blue = 1;
    AddVert(curVert);

    cout<<"added back"<<endl;
}

void Chunk::AddForth(int blockX,int blockY,int blockZ)
{
    vert curVert;
    curVert.x = blockX + 1;
    curVert.y = blockY;
    curVert.z = blockZ;
    curVert.red = 1;
    curVert.green = 1;
    curVert.blue = 1;
    AddVert(curVert);

    curVert.x = blockX + 1;
    curVert.y = blockY;
    curVert.z = blockZ + 1;
    curVert.red = 1;
    curVert.green = 1;
    curVert.blue = 1;
    AddVert(curVert);

    curVert.x = blockX + 1;
    curVert.y = blockY + 1;
    curVert.z = blockZ + 1;
    curVert.red = 1;
    curVert.green = 1;
    curVert.blue = 1;
    AddVert(curVert);

    curVert.x = blockX;
    curVert.y = blockY + 1;
    curVert.z = blockZ + 1;
    curVert.red = 1;
    curVert.green = 1;
    curVert.blue = 1;
    AddVert(curVert);

    cout<<"added forth"<<endl;
}

void Chunk::AddLeft(int blockX,int blockY,int blockZ)
{
    vert curVert;
    curVert.x = blockX;
    curVert.y = blockY;
    curVert.z = blockZ;
    curVert.red = 1;
    curVert.green = 1;
    curVert.blue = 1;
    AddVert(curVert);

    curVert.x = blockX + 1;
    curVert.y = blockY;
    curVert.z = blockZ;
    curVert.red = 1;
    curVert.green = 1;
    curVert.blue = 1;
    AddVert(curVert);

    curVert.x = blockX + 1;
    curVert.y = blockY + 1;
    curVert.z = blockZ;
    curVert.red = 1;
    curVert.green = 1;
    curVert.blue = 1;
    AddVert(curVert);

    curVert.x = blockX;
    curVert.y = blockY + 1;
    curVert.z = blockZ;
    curVert.red = 1;
    curVert.green = 1;
    curVert.blue = 1;
    AddVert(curVert);
    cout<<"added lefts"<<endl;
}

void Chunk::AddRight(int blockX,int blockY,int blockZ)
{
    vert curVert;
    curVert.x = blockX + 1;
    curVert.y = blockY;
    curVert.z = blockZ;
    curVert.red = 1;
    curVert.green = 1;
    curVert.blue = 1;
    AddVert(curVert);

    curVert.x = blockX + 1;
    curVert.y = blockY;
    curVert.z = blockZ + 1;
    curVert.red = 1;
    curVert.green = 1;
    curVert.blue = 1;
    AddVert(curVert);

    curVert.x = blockX + 1;
    curVert.y = blockY + 1;
    curVert.z = blockZ + 1;
    curVert.red = 1;
    curVert.green = 1;
    curVert.blue = 1;
    AddVert(curVert);

    curVert.x = blockX;
    curVert.y = blockY + 1;
    curVert.z = blockZ + 1;
    curVert.red = 1;
    curVert.green = 1;
    curVert.blue = 1;
    AddVert(curVert);
    cout<<"added right"<<endl;
}


void Chunk::GenerateGLData()
{
    cout<< indices.size() << endl;
    cout<< verts.size() << endl;

    for (int c = 0; c < verts.size(); c++) // X coordinates
    {
        indices.push_back(verts[c].x);
        indices.push_back(verts[c].y);
        indices.push_back(verts[c].z);
        indices.push_back(verts[c].red);
        indices.push_back(verts[c].green);
        indices.push_back(verts[c].blue);
    }
}


vector<GLuint>* Chunk::ReturnIndecies()
{
    return &GLindices;
}
vector<GLfloat>* Chunk::ReturnVerticies()
{
    return &GLvertices;
}

