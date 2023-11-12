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
 22;
 0.00000;-0.00000;3.60000;,
 1.10000;-0.00000;1.00000;,
 0.00000;1.00000;-0.00102;,
 3.40000;-0.00000;1.00000;,
 1.50000;0.00000;-0.60000;,
 -2.40000;0.00000;-3.00000;,
 -1.50000;0.00000;-0.60000;,
 2.40000;0.00000;-3.00000;,
 0.00000;0.00000;-1.30000;,
 -3.40000;0.00000;1.00000;,
 -1.10000;0.00000;1.00000;,
 0.00000;0.00000;3.60000;,
 0.00000;-1.00000;-0.00102;,
 1.10000;0.00000;1.00000;,
 3.40000;0.00000;1.00000;,
 1.50000;0.00000;-0.60000;,
 -2.40000;0.00000;-3.00000;,
 -1.50000;0.00000;-0.60000;,
 2.40000;0.00000;-3.00000;,
 0.00000;0.00000;-1.30000;,
 -3.40000;0.00000;1.00000;,
 -1.10000;0.00000;1.00000;;
 
 20;
 3;0,1,2;,
 3;3,4,2;,
 3;3,2,1;,
 3;5,6,2;,
 3;7,8,2;,
 3;2,6,9;,
 3;2,10,0;,
 3;2,9,10;,
 3;2,4,7;,
 3;2,8,5;,
 3;11,12,13;,
 3;14,12,15;,
 3;14,13,12;,
 3;16,12,17;,
 3;18,12,19;,
 3;12,20,17;,
 3;12,11,21;,
 3;12,21,20;,
 3;12,18,15;,
 3;12,16,19;;
 
 MeshMaterialList {
  4;
  20;
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
  0;;
  Material {
   0.925000;0.949000;0.510000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.231250;0.237250;0.127500;;
  }
  Material {
   0.690000;0.714000;1.000000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.172500;0.178500;0.250000;;
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
 }
 MeshNormals {
  30;
  -0.286865;0.816728;0.500663;,
  0.534517;0.814341;0.226142;,
  0.286865;0.816728;0.500663;,
  0.000000;0.999143;0.041387;,
  0.370118;0.818437;-0.439515;,
  0.519027;0.847067;-0.114405;,
  -0.396648;0.727392;-0.559974;,
  0.000000;0.792392;-0.610013;,
  -0.370118;0.818437;-0.439515;,
  -0.519027;0.847067;-0.114405;,
  -0.601143;0.766688;0.225428;,
  -0.286865;-0.816728;0.500663;,
  0.534517;-0.814341;0.226142;,
  0.286865;-0.816728;0.500663;,
  0.000000;-0.999143;0.041387;,
  0.370118;-0.818437;-0.439515;,
  0.519027;-0.847067;-0.114405;,
  -0.396648;-0.727392;-0.559974;,
  0.000000;-0.792392;-0.610013;,
  -0.370118;-0.818437;-0.439515;,
  -0.519027;-0.847067;-0.114405;,
  -0.601143;-0.766688;0.225428;,
  0.000000;0.707469;0.706745;,
  -0.534517;0.814341;0.226142;,
  0.601143;0.766688;0.225428;,
  0.396648;0.727392;-0.559974;,
  0.000000;-0.707469;0.706745;,
  -0.534517;-0.814341;0.226142;,
  0.601143;-0.766688;0.225428;,
  0.396648;-0.727392;-0.559974;;
  20;
  3;1,2,3;,
  3;4,5,3;,
  3;22,3,2;,
  3;10,9,3;,
  3;6,7,3;,
  3;3,9,8;,
  3;3,0,23;,
  3;3,22,0;,
  3;3,5,24;,
  3;3,7,25;,
  3;12,14,13;,
  3;15,14,16;,
  3;26,13,14;,
  3;21,14,20;,
  3;17,14,18;,
  3;14,19,20;,
  3;14,27,11;,
  3;14,11,26;,
  3;14,28,16;,
  3;14,29,18;;
 }
}
