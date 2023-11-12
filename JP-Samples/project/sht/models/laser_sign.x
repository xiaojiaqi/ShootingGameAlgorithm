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
 -0.28176;0.20000;1.27933;,
 -0.16905;0.31270;1.42984;,
 -0.16905;0.31270;-1.42984;,
 -0.28176;0.20000;-1.27933;,
 0.16905;0.31270;1.42984;,
 0.28176;0.20000;1.27933;,
 0.28176;0.20000;-1.27933;,
 0.16905;0.31270;-1.42984;,
 -0.05635;0.36905;1.50509;,
 -0.05635;0.36905;-1.50509;,
 0.05635;0.36905;1.50509;,
 0.05635;0.36905;-1.50509;,
 -0.39446;0.03095;-1.12882;,
 -0.39446;0.03095;1.12882;,
 0.39446;0.03095;1.12882;,
 0.39446;0.03095;-1.12882;;
 
 7;
 4;0,1,2,3;,
 4;4,5,6,7;,
 4;8,9,2,1;,
 4;10,4,7,11;,
 4;10,11,9,8;,
 4;3,12,13,0;,
 4;5,14,15,6;;
 
 MeshMaterialList {
  5;
  7;
  0,
  0,
  1,
  1,
  2,
  3,
  3;;
  Material {
   0.937255;0.956863;0.972549;0.500000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.234314;0.239216;0.243137;;
  }
  Material {
   0.890196;0.909804;0.921569;0.600000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.222549;0.227451;0.230392;;
  }
  Material {
   0.784314;0.792157;0.792157;0.700000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.196078;0.198039;0.198039;;
  }
  Material {
   0.345098;0.338824;0.332549;0.400000;;
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
  8;
  0.584710;0.811242;0.000000;,
  -0.584710;0.811242;0.000000;,
  -0.773342;0.633989;0.000000;,
  0.773342;0.633989;0.000000;,
  -0.229753;0.973249;0.000000;,
  0.229753;0.973249;0.000000;,
  -0.832050;0.554700;0.000000;,
  0.832050;0.554700;0.000000;;
  7;
  4;2,1,1,2;,
  4;0,3,3,0;,
  4;4,4,1,1;,
  4;5,0,0,5;,
  4;5,5,4,4;,
  4;2,6,6,2;,
  4;3,7,7,3;;
 }
}
