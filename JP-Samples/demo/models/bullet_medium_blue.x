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
 21;
 -1.20000;0.00000;-0.70000;,
 -0.50000;0.50000;-0.50000;,
 -0.70000;0.00000;-1.20000;,
 0.50000;0.50000;-0.50000;,
 1.20000;0.00000;-0.70000;,
 0.70000;0.00000;-1.20000;,
 0.70000;0.00000;1.20000;,
 1.20000;0.00000;0.70000;,
 0.50000;0.50000;0.50000;,
 -1.20000;0.00000;0.70000;,
 -0.70000;0.00000;1.20000;,
 -0.50000;0.50000;0.50000;,
 -0.80000;0.50000;0.00000;,
 -1.50000;0.00000;0.00000;,
 1.50000;0.00000;0.00000;,
 0.80000;0.50000;0.00000;,
 0.00000;0.00000;1.50000;,
 0.00000;0.50000;0.80000;,
 0.00000;0.50000;-0.80000;,
 0.00000;0.00000;-1.50000;,
 0.00000;0.50000;0.00000;;
 
 16;
 3;0,1,2;,
 3;3,4,5;,
 3;6,7,8;,
 3;9,10,11;,
 4;12,1,0,13;,
 4;12,13,9,11;,
 4;14,4,3,15;,
 4;14,15,8,7;,
 4;16,6,8,17;,
 4;16,17,11,10;,
 4;18,3,5,19;,
 4;18,19,2,1;,
 4;18,1,12,20;,
 4;18,20,15,3;,
 4;20,12,11,17;,
 4;20,17,8,15;;
 
 MeshMaterialList {
  2;
  16;
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  1,
  1,
  1,
  1;;
  Material {
   0.208000;0.243000;1.000000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.052000;0.060750;0.250000;;
  }
  Material {
   0.541000;0.894000;1.000000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.135250;0.223500;0.250000;;
  }
 }
 MeshNormals {
  21;
  -0.486184;0.798420;-0.355178;,
  -0.324297;0.888630;-0.324297;,
  -0.355178;0.798420;-0.486184;,
  0.324297;0.888630;-0.324297;,
  0.486184;0.798420;-0.355178;,
  0.355178;0.798420;-0.486184;,
  0.355178;0.798420;0.486184;,
  0.486184;0.798420;0.355178;,
  0.324297;0.888630;0.324297;,
  -0.486184;0.798419;0.355178;,
  -0.355178;0.798419;0.486184;,
  -0.324297;0.888629;0.324297;,
  -0.551536;0.834151;-0.000000;,
  -0.282504;0.959266;-0.000000;,
  0.282504;0.959266;0.000000;,
  0.551536;0.834151;0.000000;,
  0.000000;0.959266;-0.282504;,
  0.000000;0.834151;-0.551536;,
  0.000000;0.834151;0.551536;,
  0.000000;0.959266;0.282504;,
  0.000000;1.000000;0.000000;;
  16;
  3;0,1,2;,
  3;3,4,5;,
  3;6,7,8;,
  3;9,10,11;,
  4;13,1,0,12;,
  4;13,12,9,11;,
  4;15,4,3,14;,
  4;15,14,8,7;,
  4;18,6,8,19;,
  4;18,19,11,10;,
  4;16,3,5,17;,
  4;16,17,2,1;,
  4;16,1,13,20;,
  4;16,20,14,3;,
  4;20,13,11,19;,
  4;20,19,8,14;;
 }
}
