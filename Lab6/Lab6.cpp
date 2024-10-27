#include <iostream>
#include <fstream>

using namespace std;

// Функція для зчитування графа з вхідного файлу
void readGraph(const string& filename, int& n, int& m, int**& edges) {
    ifstream inputFile(filename);
    if (!inputFile.is_open()) {
        cout << "Error opening file" << endl;
        return;
    }

    // Зчитуємо кількість вершин (n) та ребер (m)
    inputFile >> n >> m;

    // Ініціалізуємо масив для зберігання ребер
    edges = new int* [m];
    for (int i = 0; i < m; ++i) {
        edges[i] = new int[2];
        inputFile >> edges[i][0] >> edges[i][1];
    }

    inputFile.close();
}

// Функція для створення матриці суміжності
int** createAdjacencyMatrix(int n, int m, int** edges) {
    int** adjacencyMatrix = new int* [n];
    for (int i = 0; i < n; ++i) {
        adjacencyMatrix[i] = new int[n]();
    }

    for (int i = 0; i < m; ++i) {
        int v = edges[i][0] - 1; // Початок ребра
        int u = edges[i][1] - 1; // Кінець ребра
        adjacencyMatrix[v][u] = 1; // Вказуємо наявність ребра
    }

    return adjacencyMatrix;
}

// Функція для створення матриці інцидентності
int** createIncidenceMatrix(int n, int m, int** edges) {
    int** incidenceMatrix = new int* [n];
    for (int i = 0; i < n; ++i) {
        incidenceMatrix[i] = new int[m]();
    }

    for (int i = 0; i < m; ++i) {
        int v = edges[i][0] - 1;
        int u = edges[i][1] - 1;
        incidenceMatrix[v][i] = 1;
        incidenceMatrix[u][i] = -1;
    }

    return incidenceMatrix;
}

// Функція для виведення матриці на екран та у файл
void printMatrix(int** matrix, int rows, int cols, const string& matrixName, const string& outputFile) {
    ofstream outFile(outputFile, ios::app);
    cout << matrixName << ":\n";
    outFile << matrixName << ":\n";
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            cout << matrix[i][j] << " ";
            outFile << matrix[i][j] << " ";
        }
        cout << endl;
        outFile << endl;
    }
    cout << endl;
    outFile << endl;
    outFile.close();
}

// Функція для звільнення пам'яті матриці
void deleteMatrix(int** matrix, int rows) {
    for (int i = 0; i < rows; ++i) {
        delete[] matrix[i];
    }
    delete[] matrix;
}

int main() {
    int n, m;
    int** edges = nullptr;
    string inputFile, outputFile;

    cout << "Enter input file: ";
    cin >> inputFile;
    cout << "Enter output file: ";
    cin >> outputFile;

    // Зчитуємо граф з файлу
    readGraph(inputFile, n, m, edges);

    // Створюємо матрицю суміжності та інцидентності
    int** adjacencyMatrix = createAdjacencyMatrix(n, m, edges);
    int** incidenceMatrix = createIncidenceMatrix(n, m, edges);

    // Виводимо матриці у консоль та файл
    printMatrix(adjacencyMatrix, n, n, "Matrix sumizhnosti", outputFile);
    printMatrix(incidenceMatrix, n, m, "Matrix incydentnosti", outputFile);

    // Очищуємо виділену пам'ять
    deleteMatrix(adjacencyMatrix, n);
    deleteMatrix(incidenceMatrix, n);

    for (int i = 0; i < m; ++i) {
        delete[] edges[i];
    }
    delete[] edges;

    return 0;
}
