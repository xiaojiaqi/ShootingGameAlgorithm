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
 48;
 3.00000;3.00000;0.50000;,
 3.50000;3.00000;0.50000;,
 3.50000;3.00000;-0.50000;,
 3.00000;3.00000;-0.50000;,
 2.00000;3.00000;0.50000;,
 2.50000;3.00000;0.50000;,
 2.50000;3.00000;-0.50000;,
 2.00000;3.00000;-0.50000;,
 1.00000;3.00000;0.50000;,
 1.50000;3.00000;0.50000;,
 1.50000;3.00000;-0.50000;,
 1.00000;3.00000;-0.50000;,
 -0.50000;3.00000;-3.50000;,
 -0.50000;3.00000;-3.00000;,
 0.50000;3.00000;-3.00000;,
 0.50000;3.00000;-3.50000;,
 -0.50000;3.00000;-2.50000;,
 -0.50000;3.00000;-2.00000;,
 0.50000;3.00000;-2.00000;,
 0.50000;3.00000;-2.50000;,
 -0.50000;3.00000;-1.50000;,
 -0.50000;3.00000;-1.00000;,
 0.50000;3.00000;-1.00000;,
 0.50000;3.00000;-1.50000;,
 -0.50000;3.00000;1.00000;,
 -0.50000;3.00000;1.50000;,
 0.50000;3.00000;1.50000;,
 0.50000;3.00000;1.00000;,
 -0.50000;3.00000;2.00000;,
 -0.50000;3.00000;2.50000;,
 0.50000;3.00000;2.50000;,
 0.50000;3.00000;2.00000;,
 -0.50000;3.00000;3.00000;,
 -0.50000;3.00000;3.50000;,
 0.50000;3.00000;3.50000;,
 0.50000;3.00000;3.00000;,
 -1.50000;3.00000;0.50000;,
 -1.00000;3.00000;0.50000;,
 -1.00000;3.00000;-0.50000;,
 -1.50000;3.00000;-0.50000;,
 -2.50000;3.00000;0.50000;,
 -2.00000;3.00000;0.50000;,
 -2.00000;3.00000;-0.50000;,
 -2.50000;3.00000;-0.50000;,
 -3.50000;3.00000;0.50000;,
 -3.00000;3.00000;0.50000;,
 -3.00000;3.00000;-0.50000;,
 -3.50000;3.00000;-0.50000;;
 
 12;
 4;0,1,2,3;,
 4;4,5,6,7;,
 4;8,9,10,11;,
 4;12,13,14,15;,
 4;16,17,18,19;,
 4;20,21,22,23;,
 4;24,25,26,27;,
 4;28,29,30,31;,
 4;32,33,34,35;,
 4;36,37,38,39;,
 4;40,41,42,43;,
 4;44,45,46,47;;
 
 MeshMaterialList {
  4;
  12;
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
  0;;
  Material {
   0.965000;0.984000;1.000000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.241250;0.246000;0.250000;;
  }
  Material {
   0.973000;0.439000;0.027000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.243250;0.109750;0.006750;;
  }
  Material {
   1.000000;0.000000;0.122000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.250000;0.000000;0.030500;;
  }
  Material {
   0.439000;0.416000;0.431000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.109750;0.104000;0.107750;;
  }
 }
 MeshNormals {
  1;
  0.000000;1.000000;0.000000;;
  12;
  4;0,0,0,0;,
  4;0,0,0,0;,
  4;0,0,0,0;,
  4;0,0,0,0;,
  4;0,0,0,0;,
  4;0,0,0,0;,
  4;0,0,0,0;,
  4;0,0,0,0;,
  4;0,0,0,0;,
  4;0,0,0,0;,
  4;0,0,0,0;,
  4;0,0,0,0;;
 }
}
