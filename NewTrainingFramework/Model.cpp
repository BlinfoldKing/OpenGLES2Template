#include "stdafx.h"
#include "Model.h"

Model::Model()
{
	glGenBuffers(1, &this->m_VBO);
	glGenBuffers(1, &this->m_IBO);
	this->m_indicesCount = 0;
	this->m_verticesCount = 0;
}

Model::~Model()
{
	glDeleteBuffers(1, &this->m_VBO);
	glDeleteBuffers(1, &this->m_IBO);
}

void Model::init(char* filename) 
{
	FILE* file = fopen(filename, "r");
	if (file == NULL) {
		printf(filename);
		printf("Impossible to open the file !\n");
	}
	else {
		int NrVertices;
		fscanf_s(file, "NrVertices: %d", &NrVertices);
		Vertex* verticesData = new Vertex[NrVertices];

		printf("%d\n", NrVertices);
		char* format = " %*d. pos:[%f, %f, %f]; norm:[%f, %f, %f]; binorm: [%f, %f, %f] ; tgt: [%f, %f, %f] ; uv: [%f, %f];\n";
		char* debugFormat = " %d. pos:[%f, %f, %f]; norm:[%f, %f, %f]; binorm: [%f, %f, %f] ; tgt: [%f, %f, %f] ; uv: [%f, %f];\n";
		for (int i = 0; i < NrVertices; i++) {
			Vertex v;
			fscanf_s(file, format,
				&v.pos.x, &v.pos.y, &v.pos.z,
				&v.norm.x, &v.norm.y, &v.norm.z,
				&v.binorm.x, &v.binorm.y, &v.binorm.z,
				&v.tgt.x, &v.tgt.y, &v.tgt.z,
				&v.uv.x, &v.uv.y
			);
			verticesData[i] = v;

			//printf(debugFormat, i,
			//	v.pos.x, v.pos.y, v.pos.z,
			//	v.norm.x, v.norm.y, v.norm.z,
			//	v.binorm.x, &v.binorm.y, v.binorm.z,
			//	v.tgt.x, v.tgt.y, v.tgt.z,
			//	v.uv.x, v.uv.y
			//);
		}
		this->m_verticesCount = NrVertices;


		int NrIndices;
		fscanf_s(file, "NrIndices: %d", &NrIndices);
		printf("%d\n", NrIndices);
		int* indicesdData = new int[NrIndices];
		format = "   %*d.    %d,    %d,    %d";
		debugFormat = "%d.    %d,    %d,    %d\n";
		for (int i = 0; i < NrIndices; i += 3) {
			fscanf_s(file, format,
				&indicesdData[i],
				&indicesdData[i + 1],
				&indicesdData[i + 2]
			);

//			printf(debugFormat, i,
//				indicesdData[i],
//				indicesdData[i + 1],
//				indicesdData[i + 2]
//			);
		}
		this->m_indicesCount = NrIndices;

		glBindBuffer(GL_ARRAY_BUFFER, this->m_VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * NrVertices, verticesData, GL_STATIC_DRAW);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->m_IBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(int) * NrIndices, indicesdData, GL_STATIC_DRAW);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

		delete[] verticesData;
		delete[] indicesdData;
	}
	fclose(file);
}

