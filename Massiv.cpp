#include <iostream>
#include <string>
#include <vector>
#include <locale>

using namespace std;

// Функция для поиска гиперссылок в тексте
vector<string> findHyperlinks(string text) {
    vector<string> links; 
    string prefix1 = "http://";  
    string prefix2 = "https://";
    int pos = 0; 

    while (pos < text.length()) {
        int httpPos = text.find(prefix1, pos);
        int httpsPos = text.find(prefix2, pos);
        int linkStart;

        if (httpPos == -1 && httpsPos == -1) {
            break;
        }
        else if (httpPos == -1) {
            linkStart = httpsPos;
        }
        else if (httpsPos == -1) {
            linkStart = httpPos;
        }
        else {
            linkStart = (httpPos < httpsPos) ? httpPos : httpsPos;
        }

        int linkEnd = linkStart;
        while (linkEnd < text.length()) {
            char c = text[linkEnd];
            if (c == ' ' || c == '"' || c == '\'' || c == '<' || c == '>' || c == ')') {
                break;
            }
            linkEnd++;
        }

        string link = text.substr(linkStart, linkEnd - linkStart);
        links.push_back(link); 

        pos = linkEnd;
    }

    return links;
}

int main() {

    setlocale(LC_ALL, "Russian");

    string htmlText = "<p>Посетите <a href=\"https://www.susu.ru/ru\">наш сайт</a> "
        "или <a href=\"https://ya.ru/?npr=1&utm_referrer=https%3A%2F%2Fyandex.ru%2F\">Яндекс</a>. "
        "Архив: <a href=\"http://web-archive.com\">здесь</a>.</p>";

    cout << "Исходный текст:\n" << htmlText << "\n\n";

    vector<string> foundLinks = findHyperlinks(htmlText);

    cout << "Найденные гиперссылки:\n";
    for (int i = 0; i < foundLinks.size(); i++) {
        cout << i + 1 << ". " << foundLinks[i] << "\n";
    }

    return 0;
}

