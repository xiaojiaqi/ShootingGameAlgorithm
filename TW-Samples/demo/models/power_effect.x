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
 16;
 0.00000;-6.00000;4.18363;,
 1.67345;-6.00000;-0.41836;,
 0.00000;-6.00000;-2.61477;,
 -1.67345;-6.00000;-0.41836;,
 1.56886;-6.00000;1.04591;,
 4.70658;-6.00000;-2.82395;,
 0.52295;-6.00000;-1.15050;,
 1.88263;-6.00000;-0.41836;,
 2.82395;-6.00000;-4.18363;,
 0.20918;-6.00000;-1.25509;,
 -1.56886;-6.00000;1.04591;,
 -0.52295;-6.00000;-1.15050;,
 -4.70658;-6.00000;-2.82395;,
 -1.88263;-6.00000;-0.41836;,
 -0.20918;-6.00000;-1.25509;,
 -2.82395;-6.00000;-4.18363;;
 
 5;
 4;0,1,2,3;,
 3;4,5,6;,
 3;7,8,9;,
 3;10,11,12;,
 3;13,14,15;;
 
 MeshMaterialList {
  5;
  5;
  0,
  0,
  0,
  0,
  0;;
  Material {
   0.145000;0.682000;0.992000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.036250;0.170500;0.248000;;
  }
  Material {
   0.741000;0.741000;0.741000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.185250;0.185250;0.185250;;
  }
  Material {
   0.706000;0.612000;0.325000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.176500;0.153000;0.081250;;
  }
  Material {
   0.439000;0.416000;0.431000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.109750;0.104000;0.107750;;
  }
  Material {
   0.800000;0.527200;0.150400;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
 }
 MeshNormals {
  2;
  0.000000;1.000000;0.000000;,
  0.000000;1.000000;0.000000;;
  5;
  4;0,0,0,0;,
  3;1,1,1;,
  3;0,0,0;,
  3;1,1,1;,
  3;0,0,0;;
 }
}
