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
 28;
 -6.94720;0.55139;8.70390;,
 -5.17531;1.25915;9.34765;,
 -5.17531;1.25915;-9.34765;,
 -6.94720;0.55139;-8.70390;,
 -3.76745;1.66601;-9.71774;,
 -3.76745;1.66601;9.71774;,
 -8.09152;-0.00853;8.28814;,
 -8.09152;-0.00853;-8.28814;,
 5.17531;1.25915;9.34765;,
 6.94720;0.55139;8.70390;,
 6.94720;0.55139;-8.70390;,
 5.17531;1.25915;-9.34765;,
 8.09152;-0.00853;-8.28814;,
 8.09152;-0.00853;8.28814;,
 3.76745;1.66601;9.71774;,
 3.76745;1.66601;-9.71774;,
 -2.29380;1.96033;9.98545;,
 -2.29380;1.96033;-9.98545;,
 -0.65735;2.11580;-10.12687;,
 -0.65735;2.11580;10.12687;,
 2.29380;1.96033;9.98545;,
 2.29380;1.96033;-9.98545;,
 0.65735;2.11580;10.12687;,
 0.65735;2.11580;-10.12687;,
 -10.09225;-1.20727;-7.56124;,
 -10.09225;-1.20727;7.56124;,
 10.09225;-1.20727;7.56124;,
 10.09225;-1.20727;-7.56124;;
 
 13;
 4;0,1,2,3;,
 4;4,2,1,5;,
 4;6,0,3,7;,
 4;8,9,10,11;,
 4;12,10,9,13;,
 4;14,8,11,15;,
 4;16,17,4,5;,
 4;18,17,16,19;,
 4;20,14,15,21;,
 4;22,20,21,23;,
 4;22,23,18,19;,
 4;7,24,25,6;,
 4;13,26,27,12;;
 
 MeshMaterialList {
  5;
  13;
  0,
  1,
  3,
  0,
  3,
  1,
  1,
  2,
  1,
  2,
  2,
  3,
  3;;
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
   0.072000;0.065600;0.241600;0.200000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
 }
 MeshNormals {
  14;
  -0.405511;0.914090;0.000000;,
  -0.324682;0.945823;0.000000;,
  0.324682;0.945823;0.000000;,
  0.405511;0.914090;0.000000;,
  -0.145407;0.989372;0.000000;,
  -0.236953;0.971521;0.000000;,
  0.145407;0.989372;0.000000;,
  0.236953;0.971521;0.000000;,
  0.047345;0.998879;0.000000;,
  -0.047345;0.998879;0.000000;,
  -0.477165;0.878814;0.000000;,
  -0.513960;0.857814;0.000000;,
  0.477165;0.878814;0.000000;,
  0.513960;0.857814;0.000000;;
  13;
  4;0,1,1,0;,
  4;5,1,1,5;,
  4;10,0,0,10;,
  4;2,3,3,2;,
  4;12,3,3,12;,
  4;7,2,2,7;,
  4;4,4,5,5;,
  4;9,4,4,9;,
  4;6,7,7,6;,
  4;8,6,6,8;,
  4;8,8,9,9;,
  4;10,11,11,10;,
  4;12,13,13,12;;
 }
}
