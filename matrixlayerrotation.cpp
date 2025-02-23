#include <bits/stdc++.h>
using namespace std;

// Helper functions
string ltrim(const string &);
string rtrim(const string &);
vector<string> split(const string &);

// Function to rotate the elements of a layer
vector<int> rotateLayer(vector<int> layer, int r) {
    int n = layer.size();
    r = r % n; // If r is larger than the layer size, take modulo
    if (r < 0) r += n; // Handle negative rotation

    // Perform the rotation
    rotate(layer.begin(), layer.begin() + r, layer.end());
    return layer;
}

// Function to extract a layer from the matrix
vector<int> extractLayer(const vector<vector<int>>& matrix, int layerNum, int m, int n) {
    vector<int> layer;

    // Top row (left to right)
    for (int i = layerNum; i < n - layerNum; ++i) {
        layer.push_back(matrix[layerNum][i]);
    }

    // Right column (top to bottom)
    for (int i = layerNum + 1; i < m - layerNum; ++i) {
        layer.push_back(matrix[i][n - layerNum - 1]);
    }

    // Bottom row (right to left)
    for (int i = n - layerNum - 2; i >= layerNum; --i) {
        layer.push_back(matrix[m - layerNum - 1][i]);
    }

    // Left column (bottom to top)
    for (int i = m - layerNum - 2; i > layerNum; --i) {
        layer.push_back(matrix[i][layerNum]);
    }

    return layer;
}

// Function to place a layer back into the matrix
void placeLayer(vector<vector<int>>& matrix, const vector<int>& layer, int layerNum, int m, int n) {
    int idx = 0;

    // Top row (left to right)
    for (int i = layerNum; i < n - layerNum; ++i) {
        matrix[layerNum][i] = layer[idx++];
    }

    // Right column (top to bottom)
    for (int i = layerNum + 1; i < m - layerNum; ++i) {
        matrix[i][n - layerNum - 1] = layer[idx++];
    }

    // Bottom row (right to left)
    for (int i = n - layerNum - 2; i >= layerNum; --i) {
        matrix[m - layerNum - 1][i] = layer[idx++];
    }

    // Left column (bottom to top)
    for (int i = m - layerNum - 2; i > layerNum; --i) {
        matrix[i][layerNum] = layer[idx++];
    }
}

// Main function to handle matrix rotation
void matrixRotation(vector<vector<int>> matrix, int r) {
    int m = matrix.size();
    int n = matrix[0].size();
    int layers = min(m, n) / 2;

    // Rotate each layer
    for (int layerNum = 0; layerNum < layers; ++layerNum) {
        vector<int> layer = extractLayer(matrix, layerNum, m, n);
        layer = rotateLayer(layer, r);  // Rotate the layer
        placeLayer(matrix, layer, layerNum, m, n);  // Place it back into the matrix
    }

    // Output the rotated matrix
    for (const auto& row : matrix) {
        for (int num : row) {
            cout << num << " ";
        }
        cout << endl;
    }
}

int main() {
    string first_multiple_input_temp;
    getline(cin, first_multiple_input_temp);

    vector<string> first_multiple_input = split(rtrim(first_multiple_input_temp));

    int m = stoi(first_multiple_input[0]);
    int n = stoi(first_multiple_input[1]);
    int r = stoi(first_multiple_input[2]);

    vector<vector<int>> matrix(m);

    for (int i = 0; i < m; i++) {
        matrix[i].resize(n);

        string matrix_row_temp_temp;
        getline(cin, matrix_row_temp_temp);

        vector<string> matrix_row_temp = split(rtrim(matrix_row_temp_temp));

        for (int j = 0; j < n; j++) {
            int matrix_row_item = stoi(matrix_row_temp[j]);
            matrix[i][j] = matrix_row_item;
        }
    }

    matrixRotation(matrix, r);

    return 0;
}

// Helper functions for string manipulation
string ltrim(const string &str) {
    string s(str);
    s.erase(
        s.begin(),
        find_if(s.begin(), s.end(), not1(ptr_fun<int, int>(isspace)))
    );
    return s;
}

string rtrim(const string &str) {
    string s(str);
    s.erase(
        find_if(s.rbegin(), s.rend(), not1(ptr_fun<int, int>(isspace))).base(),
        s.end()
    );
    return s;
}

vector<string> split(const string &str) {
    vector<string> tokens;
    string::size_type start = 0;
    string::size_type end = 0;

    while ((end = str.find(" ", start)) != string::npos) {
        tokens.push_back(str.substr(start, end - start));
        start = end + 1;
    }

    tokens.push_back(str.substr(start));
    return tokens;
}
