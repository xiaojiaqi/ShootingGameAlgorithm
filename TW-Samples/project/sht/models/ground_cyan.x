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
 13;
 4.01479;0.09852;-3.21183;,
 3.21183;0.09852;-4.01479;,
 2.83531;0.90148;-2.83531;,
 -3.21183;0.09852;-4.01479;,
 -2.83531;0.90148;-2.83531;,
 -4.01479;0.09852;-3.21183;,
 -4.01479;0.09852;3.21183;,
 -2.83531;0.90148;2.83531;,
 -2.83531;0.90148;-2.83531;,
 2.83531;0.90148;2.83531;,
 4.01479;0.09852;3.21183;,
 -3.21183;0.09852;4.01479;,
 3.21183;0.09852;4.01479;;
 
 9;
 3;0,1,2;,
 4;1,3,4,2;,
 3;3,5,4;,
 4;6,7,8,5;,
 4;9,10,0,2;,
 4;7,9,2,8;,
 3;6,11,7;,
 4;11,12,9,7;,
 3;12,10,9;;
 
 MeshMaterialList {
  4;
  9;
  2,
  2,
  2,
  2,
  2,
  0,
  2,
  2,
  2;;
  Material {
   0.478000;0.898000;0.914000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.119500;0.224500;0.228500;;
  }
  Material {
   0.741000;0.741000;0.741000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.185250;0.185250;0.185250;;
  }
  Material {
   0.110000;0.800000;0.714000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.027500;0.200000;0.178500;;
  }
  Material {
   0.439000;0.416000;0.431000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.109750;0.104000;0.107750;;
  }
 }
 MeshNormals {
  12;
  0.262766;0.928390;-0.262766;,
  -0.213706;0.837920;-0.502215;,
  0.502214;0.837920;-0.213706;,
  0.213706;0.837920;-0.502215;,
  -0.502215;0.837920;-0.213706;,
  -0.502215;0.837920;0.213706;,
  -0.262766;0.928390;0.262766;,
  -0.294424;0.955675;0.000000;,
  0.262766;0.928390;0.262766;,
  0.502214;0.837921;0.213706;,
  -0.213706;0.837920;0.502215;,
  0.213705;0.837920;0.502214;;
  9;
  3;2,3,0;,
  4;3,1,1,0;,
  3;1,4,1;,
  4;5,6,7,4;,
  4;8,9,2,0;,
  4;6,8,0,7;,
  3;5,10,6;,
  4;10,11,8,6;,
  3;11,9,8;;
 }
}
