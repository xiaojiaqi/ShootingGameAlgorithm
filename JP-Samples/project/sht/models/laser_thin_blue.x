xof 0302txt 0064
template Header {
 <3D82AB43-62DA-11cf-AB39-0020AF71E433>
 WORD major;
 WORD minor;
 DWORD flags;
}

template Vector {
 <3D82AB5E-62DA-11cf-AB39-0020AF71E433>
 FLOAT x;
 FLOAT y;
 FLOAT z;
}

template Coords2d {
 <F6F23F44-7686-11cf-8F52-0040333594A3>
 FLOAT u;
 FLOAT v;
}

template Matrix4x4 {
 <F6F23F45-7686-11cf-8F52-0040333594A3>
 array FLOAT matrix[16];
}

template ColorRGBA {
 <35FF44E0-6C7C-11cf-8F52-0040333594A3>
 FLOAT red;
 FLOAT green;
 FLOAT blue;
 FLOAT alpha;
}

template ColorRGB {
 <D3E16E81-7835-11cf-8F52-0040333594A3>
 FLOAT red;
 FLOAT green;
 FLOAT blue;
}

template IndexedColor {
 <1630B820-7842-11cf-8F52-0040333594A3>
 DWORD index;
 ColorRGBA indexColor;
}

template Boolean {
 <4885AE61-78E8-11cf-8F52-0040333594A3>
 WORD truefalse;
}

template Boolean2d {
 <4885AE63-78E8-11cf-8F52-0040333594A3>
 Boolean u;
 Boolean v;
}

template MaterialWrap {
 <4885AE60-78E8-11cf-8F52-0040333594A3>
 Boolean u;
 Boolean v;
}

template TextureFilename {
 <A42790E1-7810-11cf-8F52-0040333594A3>
 STRING filename;
}

template Material {
 <3D82AB4D-62DA-11cf-AB39-0020AF71E433>
 ColorRGBA faceColor;
 FLOAT power;
 ColorRGB specularColor;
 ColorRGB emissiveColor;
 [...]
}

template MeshFace {
 <3D82AB5F-62DA-11cf-AB39-0020AF71E433>
 DWORD nFaceVertexIndices;
 array DWORD faceVertexIndices[nFaceVertexIndices];
}

template MeshFaceWraps {
 <4885AE62-78E8-11cf-8F52-0040333594A3>
 DWORD nFaceWrapValues;
 Boolean2d faceWrapValues;
}

template MeshTextureCoords {
 <F6F23F40-7686-11cf-8F52-0040333594A3>
 DWORD nTextureCoords;
 array Coords2d textureCoords[nTextureCoords];
}

template MeshMaterialList {
 <F6F23F42-7686-11cf-8F52-0040333594A3>
 DWORD nMaterials;
 DWORD nFaceIndexes;
 array DWORD faceIndexes[nFaceIndexes];
 [Material]
}

template MeshNormals {
 <F6F23F43-7686-11cf-8F52-0040333594A3>
 DWORD nNormals;
 array Vector normals[nNormals];
 DWORD nFaceNormals;
 array MeshFace faceNormals[nFaceNormals];
}

template MeshVertexColors {
 <1630B821-7842-11cf-8F52-0040333594A3>
 DWORD nVertexColors;
 array IndexedColor vertexColors[nVertexColors];
}

template Mesh {
 <3D82AB44-62DA-11cf-AB39-0020AF71E433>
 DWORD nVertices;
 array Vector vertices[nVertices];
 DWORD nFaces;
 array MeshFace faces[nFaces];
 [...]
}

Header{
1;
0;
1;
}

Mesh {
 24;
 -0.50000;0.30000;1.70000;,
 -0.30000;0.50000;1.90000;,
 -0.30000;0.50000;-1.90000;,
 -0.50000;0.30000;-1.70000;,
 0.30000;0.50000;1.90000;,
 0.50000;0.30000;1.70000;,
 0.50000;0.30000;-1.70000;,
 0.30000;0.50000;-1.90000;,
 -0.10000;0.60000;2.00000;,
 -0.10000;0.60000;-2.00000;,
 0.10000;0.60000;2.00000;,
 0.10000;0.60000;-2.00000;,
 -0.70000;0.00000;-1.50000;,
 -0.70000;0.00000;1.50000;,
 0.70000;0.00000;1.50000;,
 0.70000;0.00000;-1.50000;,
 -1.40000;0.00000;1.00000;,
 -0.00000;0.00000;2.00000;,
 0.00000;0.00000;-2.00000;,
 -1.00000;0.00000;-1.50000;,
 1.40000;0.00000;1.00000;,
 1.00000;0.00000;-1.50000;,
 0.00000;0.00000;-2.00000;,
 0.00000;0.00000;2.00000;;
 
 9;
 4;0,1,2,3;,
 4;4,5,6,7;,
 4;8,9,2,1;,
 4;10,4,7,11;,
 4;10,11,9,8;,
 4;3,12,13,0;,
 4;5,14,15,6;,
 4;16,17,18,19;,
 4;20,21,22,23;;
 
 MeshMaterialList {
  5;
  9;
  0,
  0,
  1,
  1,
  2,
  3,
  3,
  4,
  4;;
  Material {
   0.035000;0.000000;0.973000;0.500000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.008750;0.000000;0.243250;;
  }
  Material {
   0.188000;0.533000;1.000000;0.600000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.047000;0.133250;0.250000;;
  }
  Material {
   0.722000;0.855000;1.000000;0.700000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.180500;0.213750;0.250000;;
  }
  Material {
   0.100000;0.100000;0.373600;0.400000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.072157;0.065882;0.241569;0.200000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
 }
 MeshNormals {
  9;
  0.584710;0.811242;0.000000;,
  -0.584710;0.811242;0.000000;,
  -0.773342;0.633989;0.000000;,
  0.773342;0.633989;0.000000;,
  -0.229753;0.973249;0.000000;,
  0.229753;0.973249;0.000000;,
  -0.832050;0.554700;0.000000;,
  0.832050;0.554700;0.000000;,
  0.000000;1.000000;0.000000;;
  9;
  4;2,1,1,2;,
  4;0,3,3,0;,
  4;4,4,1,1;,
  4;5,0,0,5;,
  4;5,5,4,4;,
  4;2,6,6,2;,
  4;3,7,7,3;,
  4;8,8,8,8;,
  4;8,8,8,8;;
 }
}
