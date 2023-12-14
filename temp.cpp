// Функция для нахождения определителя матрицы
int determinant(int matrix[2][2]) {
    int det = matrix[0][0] * matrix[1][1] - matrix[0][1] * matrix[1][0];
    return det;
}

int main() {
    int matrix[2][2] = {{1, 2}, {3, 4}};
    int det = determinant(matrix);
    cout << "Определитель матрицы: " << det << endl;
    return 0;
}
