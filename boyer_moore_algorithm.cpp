
/* -------------------------------------------------------------------------- */
/*                     Criado por Matheus Cândido Teixeira                    */
/*                                                                            */
/*                  Implementação do algoritmo de Boyer Moore                 */
/*                                                                            */
/*   https://wikipedia.org/wiki/Boyer%E2%80%93Moore_string-search_algorithm   */
/*                                                                            */
/* -------------------------------------------------------------------------- */

#include <iostream>
#include <string>

using namespace std;

// Verifica se há correspondencia entre a porção de text com target. A compara-
// ção ocorre de trás para frente.
// O parâmetro "from" indica a onde a comparação deve iniciar em text e
// decrescer a partir daí.
// O parâmetro "divergencePoint" inica a partir de qual caractere as strings
// passaram a ser diferentes.
// Ex: ABCDEF e VBWDEF => Ponto de divergência: 2, porque a partir da posição
// 2 ('C', para o primeiro, e 'W' para o segundo) eles começaram a divergir.
bool compareStringBackward(
    const string& text,
    int from,
    const string& target,
    int *divergencePoint = nullptr)
{
    const int targetSize = target.length();

    for (int i = 0; i < targetSize; ++i) {
        if (text[from - i] != target[targetSize - i - 1]) {
            *divergencePoint = from - i;
            return false;
        }
    }

    return true;
}

// Retorna o quão distante do fim de target está o caractere em "pattern".
int findHowMuchToAdvance(const string &target, char pattern) {
    int targetSize = target.length();

    for (int i = 0; i < targetSize; ++i)
        if (target[targetSize - i - 1] == pattern)
            return i;

    return targetSize;
}

// Retorna a primeira ocorrência de "target" em "text" e -1, caso contrário.
int boyerMooreAlgorithm(string text, string target) {
    constexpr int notFinded    = -1;
    const     int targetLength = target.length();
    const     int textLength   = text.length();
    int       curPosition      = targetLength - 1;

    if (textLength < targetLength) return notFinded;

    while (curPosition >= 0 && curPosition < textLength) {
        // Compara se são iguais, caso contrário, coloque o cursor sobre o
        // ponto de divergência sobre o caractere de "text" que divergiu de
        // "target".
        if (compareStringBackward(text, curPosition, target, &curPosition))
            return curPosition - targetLength + 1;

        // Procure quantas posições avançar para que target tenha o mesmo
        // caractere que "text" na posição de curPosition.
        int howMuchToAdvance =
            findHowMuchToAdvance(target, text[curPosition]);

        curPosition += howMuchToAdvance;
    }

    // Se alcançou este ponto, o valor especificado em "target" não está
    // presente.
    return notFinded;
}

int main(int argc, char** argv) {
    if (argc < 3) {
        cout << "Usage: " << endl;
        cout << "   boyer_moore_algorithm [text] [target]" << endl;
        return -1;
    }

    string text = argv[1];
    string target = argv[2];

    cout << boyerMooreAlgorithm(text, target) << endl;

    return 0;
}