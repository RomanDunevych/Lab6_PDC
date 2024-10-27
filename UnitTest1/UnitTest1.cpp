#include "pch.h"
#include "CppUnitTest.h"
#include "../Lab6/Lab6.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest1
{
	TEST_CLASS(UnitTest1)
	{
	public:

		TEST_METHOD(TestCreateAdjacencyMatrix)
		{
			
			int n = 4;  
			int m = 3;  

			int** edges = new int* [m];
			edges[0] = new int[2] { 1, 2 };
			edges[1] = new int[2] { 2, 3 };
			edges[2] = new int[2] { 4, 1 };

			int** adjacencyMatrix = createAdjacencyMatrix(n, m, edges);

			int expectedAdjacencyMatrix[4][4] = {
				{ 0, 1, 0, 0 },
				{ 0, 0, 1, 0 },
				{ 0, 0, 0, 0 },
				{ 1, 0, 0, 0 }
			};

			for (int i = 0; i < n; ++i) {
				for (int j = 0; j < n; ++j) {
					Assert::AreEqual(expectedAdjacencyMatrix[i][j], adjacencyMatrix[i][j]);
				}
			}

			deleteMatrix(adjacencyMatrix, n);
			for (int i = 0; i < m; ++i) {
				delete[] edges[i];
			}
			delete[] edges;
		}

		TEST_METHOD(TestCreateIncidenceMatrix)
		{

			int n = 4;  
			int m = 3;  

			int** edges = new int* [m];
			edges[0] = new int[2] { 1, 2 };
			edges[1] = new int[2] { 2, 3 };
			edges[2] = new int[2] { 4, 1 };

			int** incidenceMatrix = createIncidenceMatrix(n, m, edges);

			int expectedIncidenceMatrix[4][3] = {
				{ 1, 0, -1 },
				{ -1, 1, 0 },
				{ 0, -1, 0 },
				{ 0, 0, 1 }
			};

			for (int i = 0; i < n; ++i) {
				for (int j = 0; j < m; ++j) {
					Assert::AreEqual(expectedIncidenceMatrix[i][j], incidenceMatrix[i][j]);
				}
			}

			deleteMatrix(incidenceMatrix, n);
			for (int i = 0; i < m; ++i) {
				delete[] edges[i];
			}
			delete[] edges;
		}
	};
}
