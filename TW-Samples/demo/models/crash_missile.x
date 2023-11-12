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
 96;
 0.00000;0.00000;-2.52400;,
 0.00000;0.00000;-1.99500;,
 0.76345;0.00000;-1.84314;,
 0.96589;0.00000;-2.33187;,
 1.41068;0.00000;-1.41068;,
 1.78474;0.00000;-1.78474;,
 1.84314;0.00000;-0.76345;,
 2.33187;0.00000;-0.96589;,
 1.99500;0.00000;0.00000;,
 2.52400;0.00000;0.00000;,
 1.84314;0.00000;0.76345;,
 2.33187;0.00000;0.96589;,
 1.41068;0.00000;1.41068;,
 1.78474;0.00000;1.78474;,
 0.76345;0.00000;1.84314;,
 0.96589;0.00000;2.33187;,
 0.00000;0.00000;1.99500;,
 0.00000;0.00000;2.52400;,
 -0.76345;0.00000;1.84314;,
 -0.96589;0.00000;2.33187;,
 -1.41068;0.00000;1.41068;,
 -1.78474;0.00000;1.78474;,
 -1.84314;0.00000;0.76345;,
 -2.33187;0.00000;0.96589;,
 -1.99500;0.00000;0.00000;,
 -2.52400;0.00000;0.00000;,
 -1.84314;0.00000;-0.76345;,
 -2.33187;0.00000;-0.96589;,
 -1.41068;0.00000;-1.41068;,
 -1.78474;0.00000;-1.78474;,
 -0.76345;0.00000;-1.84314;,
 -0.96589;0.00000;-2.33187;,
 0.00000;0.00000;-1.76251;,
 0.00000;0.00000;-1.39311;,
 0.53312;0.00000;-1.28707;,
 0.67448;0.00000;-1.62835;,
 0.98508;0.00000;-0.98508;,
 1.24628;0.00000;-1.24628;,
 1.28707;0.00000;-0.53312;,
 1.62835;0.00000;-0.67448;,
 1.39311;0.00000;0.00000;,
 1.76251;0.00000;0.00000;,
 1.28707;0.00000;0.53312;,
 1.62835;0.00000;0.67448;,
 0.98508;0.00000;0.98508;,
 1.24628;0.00000;1.24628;,
 0.53312;0.00000;1.28707;,
 0.67448;0.00000;1.62835;,
 0.00000;0.00000;1.39311;,
 0.00000;0.00000;1.76251;,
 -0.53312;0.00000;1.28707;,
 -0.67448;0.00000;1.62835;,
 -0.98508;0.00000;0.98508;,
 -1.24628;0.00000;1.24628;,
 -1.28707;0.00000;0.53312;,
 -1.62835;0.00000;0.67448;,
 -1.39311;0.00000;0.00000;,
 -1.76251;0.00000;0.00000;,
 -1.28707;0.00000;-0.53312;,
 -1.62835;0.00000;-0.67448;,
 -0.98508;0.00000;-0.98508;,
 -1.24628;0.00000;-1.24628;,
 -0.53312;0.00000;-1.28707;,
 -0.67448;0.00000;-1.62835;,
 0.00000;0.00000;-1.11949;,
 0.00000;0.00000;-0.88486;,
 0.33862;0.00000;-0.81750;,
 0.42841;0.00000;-1.03427;,
 0.62569;0.00000;-0.62569;,
 0.79160;0.00000;-0.79160;,
 0.81750;0.00000;-0.33862;,
 1.03427;0.00000;-0.42841;,
 0.88486;0.00000;0.00000;,
 1.11949;0.00000;0.00000;,
 0.81750;0.00000;0.33862;,
 1.03427;0.00000;0.42841;,
 0.62569;0.00000;0.62569;,
 0.79160;0.00000;0.79160;,
 0.33862;0.00000;0.81750;,
 0.42841;0.00000;1.03427;,
 0.00000;0.00000;0.88486;,
 0.00000;0.00000;1.11949;,
 -0.33862;0.00000;0.81750;,
 -0.42841;0.00000;1.03427;,
 -0.62569;0.00000;0.62569;,
 -0.79160;0.00000;0.79160;,
 -0.81750;0.00000;0.33862;,
 -1.03427;0.00000;0.42841;,
 -0.88486;0.00000;0.00000;,
 -1.11949;0.00000;0.00000;,
 -0.81750;0.00000;-0.33862;,
 -1.03427;0.00000;-0.42841;,
 -0.62569;0.00000;-0.62569;,
 -0.79160;0.00000;-0.79160;,
 -0.33862;0.00000;-0.81750;,
 -0.42841;0.00000;-1.03427;;
 
 96;
 4;0,1,2,3;,
 4;0,3,2,1;,
 4;3,2,4,5;,
 4;3,5,4,2;,
 4;5,4,6,7;,
 4;5,7,6,4;,
 4;7,6,8,9;,
 4;7,9,8,6;,
 4;9,8,10,11;,
 4;9,11,10,8;,
 4;11,10,12,13;,
 4;11,13,12,10;,
 4;13,12,14,15;,
 4;13,15,14,12;,
 4;15,14,16,17;,
 4;15,17,16,14;,
 4;17,16,18,19;,
 4;17,19,18,16;,
 4;19,18,20,21;,
 4;19,21,20,18;,
 4;21,20,22,23;,
 4;21,23,22,20;,
 4;23,22,24,25;,
 4;23,25,24,22;,
 4;25,24,26,27;,
 4;25,27,26,24;,
 4;27,26,28,29;,
 4;27,29,28,26;,
 4;29,28,30,31;,
 4;29,31,30,28;,
 4;31,30,1,0;,
 4;31,0,1,30;,
 4;32,33,34,35;,
 4;32,35,34,33;,
 4;35,34,36,37;,
 4;35,37,36,34;,
 4;37,36,38,39;,
 4;37,39,38,36;,
 4;39,38,40,41;,
 4;39,41,40,38;,
 4;41,40,42,43;,
 4;41,43,42,40;,
 4;43,42,44,45;,
 4;43,45,44,42;,
 4;45,44,46,47;,
 4;45,47,46,44;,
 4;47,46,48,49;,
 4;47,49,48,46;,
 4;49,48,50,51;,
 4;49,51,50,48;,
 4;51,50,52,53;,
 4;51,53,52,50;,
 4;53,52,54,55;,
 4;53,55,54,52;,
 4;55,54,56,57;,
 4;55,57,56,54;,
 4;57,56,58,59;,
 4;57,59,58,56;,
 4;59,58,60,61;,
 4;59,61,60,58;,
 4;61,60,62,63;,
 4;61,63,62,60;,
 4;63,62,33,32;,
 4;63,32,33,62;,
 4;64,65,66,67;,
 4;64,67,66,65;,
 4;67,66,68,69;,
 4;67,69,68,66;,
 4;69,68,70,71;,
 4;69,71,70,68;,
 4;71,70,72,73;,
 4;71,73,72,70;,
 4;73,72,74,75;,
 4;73,75,74,72;,
 4;75,74,76,77;,
 4;75,77,76,74;,
 4;77,76,78,79;,
 4;77,79,78,76;,
 4;79,78,80,81;,
 4;79,81,80,78;,
 4;81,80,82,83;,
 4;81,83,82,80;,
 4;83,82,84,85;,
 4;83,85,84,82;,
 4;85,84,86,87;,
 4;85,87,86,84;,
 4;87,86,88,89;,
 4;87,89,88,86;,
 4;89,88,90,91;,
 4;89,91,90,88;,
 4;91,90,92,93;,
 4;91,93,92,90;,
 4;93,92,94,95;,
 4;93,95,94,92;,
 4;95,94,65,64;,
 4;95,64,65,94;;
 
 MeshMaterialList {
  3;
  96;
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
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2;;
  Material {
   0.800000;0.364000;0.037600;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.800000;0.680800;0.216800;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.800000;0.800000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
 }
 MeshNormals {
  2;
  0.000000;1.000000;0.000000;,
  0.000000;-1.000000;-0.000000;;
  96;
  4;0,0,0,0;,
  4;1,1,1,1;,
  4;0,0,0,0;,
  4;1,1,1,1;,
  4;0,0,0,0;,
  4;1,1,1,1;,
  4;0,0,0,0;,
  4;1,1,1,1;,
  4;0,0,0,0;,
  4;1,1,1,1;,
  4;0,0,0,0;,
  4;1,1,1,1;,
  4;0,0,0,0;,
  4;1,1,1,1;,
  4;0,0,0,0;,
  4;1,1,1,1;,
  4;0,0,0,0;,
  4;1,1,1,1;,
  4;0,0,0,0;,
  4;1,1,1,1;,
  4;0,0,0,0;,
  4;1,1,1,1;,
  4;0,0,0,0;,
  4;1,1,1,1;,
  4;0,0,0,0;,
  4;1,1,1,1;,
  4;0,0,0,0;,
  4;1,1,1,1;,
  4;0,0,0,0;,
  4;1,1,1,1;,
  4;0,0,0,0;,
  4;1,1,1,1;,
  4;0,0,0,0;,
  4;1,1,1,1;,
  4;0,0,0,0;,
  4;1,1,1,1;,
  4;0,0,0,0;,
  4;1,1,1,1;,
  4;0,0,0,0;,
  4;1,1,1,1;,
  4;0,0,0,0;,
  4;1,1,1,1;,
  4;0,0,0,0;,
  4;1,1,1,1;,
  4;0,0,0,0;,
  4;1,1,1,1;,
  4;0,0,0,0;,
  4;1,1,1,1;,
  4;0,0,0,0;,
  4;1,1,1,1;,
  4;0,0,0,0;,
  4;1,1,1,1;,
  4;0,0,0,0;,
  4;1,1,1,1;,
  4;0,0,0,0;,
  4;1,1,1,1;,
  4;0,0,0,0;,
  4;1,1,1,1;,
  4;0,0,0,0;,
  4;1,1,1,1;,
  4;0,0,0,0;,
  4;1,1,1,1;,
  4;0,0,0,0;,
  4;1,1,1,1;,
  4;0,0,0,0;,
  4;1,1,1,1;,
  4;0,0,0,0;,
  4;1,1,1,1;,
  4;0,0,0,0;,
  4;1,1,1,1;,
  4;0,0,0,0;,
  4;1,1,1,1;,
  4;0,0,0,0;,
  4;1,1,1,1;,
  4;0,0,0,0;,
  4;1,1,1,1;,
  4;0,0,0,0;,
  4;1,1,1,1;,
  4;0,0,0,0;,
  4;1,1,1,1;,
  4;0,0,0,0;,
  4;1,1,1,1;,
  4;0,0,0,0;,
  4;1,1,1,1;,
  4;0,0,0,0;,
  4;1,1,1,1;,
  4;0,0,0,0;,
  4;1,1,1,1;,
  4;0,0,0,0;,
  4;1,1,1,1;,
  4;0,0,0,0;,
  4;1,1,1,1;,
  4;0,0,0,0;,
  4;1,1,1,1;,
  4;0,0,0,0;,
  4;1,1,1,1;;
 }
}