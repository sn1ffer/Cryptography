//Шифровка, расшифровка и криптоанализ шифра простой замены, аффинного и аффинного рекуррентного 
//Для выполнения криптоанализа в cmake-build-debug необходимо поместить english_quadgrams

#include <iostream>
#include <random>
#include <vector>
#include <string>
#include <map>
#include <cmath>
#include <experimental/random>
#include "cstdio"
#include "fstream"

int gcd (int a, int b, int & x, int & y)
{
    if (a == 0)
    {
        x = 0; y = 1;
        return b;
    }
    int x1, y1;
    int d = gcd (b%a, a, x1, y1);
    x = y1 - (b / a) * x1;
    y = x1;
    return d;
}

std::string simple_substitute(bool to_encrypt, std::string alphabet, std::string message = "", std::vector<int> keyIn = {})
{
    //std::cout << "Выполняю шифр простой замены" << std::endl;

    int size_alphabet = alphabet.size();
    std::vector<int> keys(size_alphabet);

    if(keyIn.empty()) {

        std::cout << "Введите " << size_alphabet << " элементов перестановки" << std::endl;
        for (int i = 0; i < size_alphabet; i++) {
            std::cin >> keys[i];
        }

    }else keys = keyIn;

    std::string to_return;

    if(to_encrypt)
    {
        //std::cout << "Выполняю зашифрование" << std::endl;
        for(auto character: message)
        {
            int pos = std::find(alphabet.begin(), alphabet.end(), character) - alphabet.begin();
            char newLetter = alphabet[keys[pos]];
            to_return.push_back(newLetter);
        }
    }else
    {
        //std::cout << "Выполняю расшифрование" << std::endl;
        for(auto character: message)
        {
            int pos = std::find(alphabet.begin(), alphabet.end(), character) - alphabet.begin();
            int posFir = std::find(keys.begin(), keys.end(), pos) - keys.begin();
            char newLetter = alphabet[posFir];
            to_return.push_back(newLetter);
        }
    }

    return to_return;

}

std::string affine(bool to_encrypt, std::string alphabet, std::string message = "", std::vector<int> keyIn = {})
{
    int alpha, beta;
    int size_alphabet = alphabet.size();

    if(keyIn.empty()) {

        //std::cout << "Выполняю Аффинный шифр" << std::endl;
        std::cout << "Введите альфа и бета" << std::endl;

        std::cin >> alpha >> beta;
        int tmp1, tmp2;

        if(gcd(alpha, size_alphabet, tmp1, tmp2)!=1){
            std::cout << "Ошибка: Значения альфа и размера алфавита не являются взаимно простыми" << std::endl;
            return "";
        }

    }else {
        alpha = keyIn[0];
        beta = keyIn[1];
    }
    std::string to_return;

    if(to_encrypt)
    {
        //std::cout << "Выполняю зашифрование" << std::endl;
        for(auto elem: message)
        {
            int pos = std::find(alphabet.begin(), alphabet.end(), elem) - alphabet.begin();
            int num = (alpha*pos+beta)%size_alphabet;
            char newLetter = alphabet[num];
            to_return.push_back(newLetter);
        }
    }else
    {
        //std::cout << "Выполняю расшифрование" << std::endl;
        int alphaRev;
        int szRev;
        gcd(alpha, size_alphabet, alphaRev, szRev);
        alphaRev+=size_alphabet;
        for(auto elem: message)
        {
            int pos = std::find(alphabet.begin(), alphabet.end(), elem) - alphabet.begin();
            int num = ((pos-beta+size_alphabet)*alphaRev)%size_alphabet;
            char newLetter = alphabet[num];
            to_return.push_back(newLetter);

        }
    }
    return to_return;
}

std::string affine_recursive(bool to_encrypt, std::string alphabet, std::string message = "", std::vector<int> keyIn = {})
{

    int size_alphabet = alphabet.size();
    int alphaFir, betaFir, alphaSec, betaSec;

    if(keyIn.empty()) {

        //std::cout << "Выполняю аффинный рекуррентный шифр" << std::endl;
        std::cout << "Вставьте первую пару альфа и бета" << std::endl;

        std::cin >> alphaFir >> betaFir;
        std::cout << "Вставьте вторую пару альфа и бета" << std::endl;
        std::cin >> alphaSec >> betaSec;
    }else{
        alphaFir = keyIn[0];
        betaFir = keyIn[1];
        alphaSec = keyIn[2];
        betaSec = keyIn[3];
    }

    int tmp1, tmp2;

    if(gcd(alphaFir, size_alphabet, tmp1, tmp2)!=1 || gcd(alphaSec, size_alphabet, tmp1, tmp2)!=1){
        std::cout << "Ошибка: Значения альфа и размера алфавита не являются взаимно простыми" << std::endl;
        return "";
    }

    std::string to_return;
    if(to_encrypt){
        //std::cout << "Выполняю зашифрование" << std::endl;
        for(int i = 0; i<message.size(); i++)
        {
            auto elem = message[i];
            int pos = std::find(alphabet.begin(), alphabet.end(), elem) - alphabet.begin();

            int alpha;
            int beta;

            if(i == 0)
            {
                alpha = alphaFir;
                beta = betaFir;
            }
            else if(i == 1)
            {
                alpha = alphaSec;
                beta = betaSec;
            }
            else
            {
                alpha = (alphaFir*alphaSec)%size_alphabet;
                beta = (betaFir+betaSec)%size_alphabet;

                alphaFir = alphaSec;
                alphaSec = alpha;
                betaFir = betaSec;
                betaSec = beta;
            }
            int num = (alpha*pos+beta)%size_alphabet;
            char newLetter = alphabet[num];
            to_return.push_back(newLetter);
        }

    }else {
        //std::cout << "Выполняю расшифрование" << std::endl;
        for(int i = 0; i<message.size(); i++)
        {
            auto elem = message[i];
            int alpha;
            int beta;
            if(i == 0)
            {
                alpha = alphaFir;
                beta = betaFir;
            }
            else if(i == 1)
            {
                alpha = alphaSec;
                beta = betaSec;
            }
            else
            {
                alpha = (alphaFir*alphaSec)%size_alphabet;
                beta = (betaFir+betaSec)%size_alphabet;

                alphaFir = alphaSec;
                alphaSec = alpha;
                betaFir = betaSec;
                betaSec = beta;
            }
            int alphaRev;
            int szRev;
            gcd(alpha, size_alphabet, alphaRev, szRev);
            alphaRev+=size_alphabet;
            int pos = std::find(alphabet.begin(), alphabet.end(), elem) - alphabet.begin();
            int num = ((pos-beta+size_alphabet)*alphaRev)%size_alphabet;
            char newLetter = alphabet[num];
            to_return.push_back(newLetter);
        }
    }
    return to_return;
}



std::map<std::string, double> toCheckQuad;
const double sumof = 4224127912;

void map_init(){

    auto f = freopen("english_quadgrams", "r", stdin);
    for(int i = 0; i < 389373; i++) {

        std::string inQuad;
        int valueof;
        std::cin >> inQuad >> valueof;
        for (int k = 0; k<4; k++) {

            char temp = tolower(inQuad[k]);
            inQuad[k] = temp;

        }

        double toInsert = log10( ((float) valueof) / sumof);
        toCheckQuad.insert({inQuad, toInsert});

    }

}

double score(std::string text) {

    double score = 0;
    std::string ngrams = "english_quadgrams";

    if(toCheckQuad.empty()) map_init();

    double toround = log10(0.01 / sumof);

    for(int i = 0; i < text.size(); i++) {
        std::string nowAt;
        nowAt.push_back(text[i]);
        nowAt.push_back(text[i+1]);
        nowAt.push_back(text[i+2]);
        nowAt.push_back(text[i+3]);

        if (toCheckQuad[nowAt] != 0){
            score += toCheckQuad[nowAt];
        }
        else {
            score += toround;
        }
    }
    return score;
}

void cryptoanalysis_simple(std::string textIn, std::string alphabet) {

    int i = 0;
    std::vector<int> maxkey = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25};
    int maxscore = -100000000;
    double parentscore = maxscore;
    auto parentkey = maxkey;
    for(int q = 0; q<200; q++)
    {
        i++;
        std::shuffle(parentkey.begin(), parentkey.end(), std::mt19937(std::random_device()()));
        auto deciphered = simple_substitute(0, alphabet, textIn, parentkey);
        parentscore = score(deciphered);
        int count = 0;
        while (count < 1000)
        {
            int a = std::experimental::randint(0, 25);
            int b = std::experimental::randint(0, 25);
            auto child = parentkey;
            std::swap(child[a], child[b]);
            deciphered = simple_substitute(0, alphabet, textIn, child);
            double scoreNow = score(deciphered);
            if (scoreNow > parentscore) {
                parentscore = scoreNow;
                parentkey = child;
                count = 0;
            }
            count = count + 1;
        }
        if (parentscore > maxscore) {
            maxscore = parentscore;
            maxkey = parentkey;
            std::cout << "\nBest metrick: " << maxscore << "on iteration " << i << std::endl;
            auto answer = simple_substitute(0, alphabet, textIn, maxkey);
            std::cout << "Plain text: " << answer << std::endl;
        }
    }

}

void cryptoanalysis_affine(std::string textIn, std::string alphabet) {

    int i = 0;
    std::vector<int> maxkey = {1, 1};
    int maxscore = -100000000;
    double parentscore = maxscore;
    auto parentkey = maxkey;
    for (int k = 1; k<25; k++){
        for (int j = 1; j<25; j++){


            int tmp1 = 0;
            int tmp2 = 0;

            if (gcd(k, 26, tmp1, tmp2) != 1) {
                continue;
            }

            i++;
            auto deciphered = affine(0, alphabet, textIn, parentkey);
            parentscore = score(deciphered);

            std::vector<int> child = {k, j};
            deciphered = affine(0, alphabet, textIn, child);
            double scoreNow = score(deciphered);
            if (scoreNow > parentscore) {
                parentscore = scoreNow;
                parentkey = child;
            }

            if (parentscore > maxscore) {
                maxscore = parentscore;
                maxkey = parentkey;
                std::cout << "\nBest metrick: " << maxscore << "on iteration " << i << std::endl;
                auto answer = affine(0, alphabet, textIn, maxkey);
                std::cout << "Plain text: " << answer << std::endl;
            }

        }


    }

}


void cryptoanalysis_affine_recurrent(std::string textIn, std::string alphabet) {

    int i = 0;
    std::vector<int> maxkey = {1, 1, 1, 1};
    int maxscore = -100000000;
    double parentscore = maxscore;
    auto parentkey = maxkey;
    for(int t = 1; t<25; t++) {
        for (int q = 1; q < 25; q++) {
            for (int k = 1; k < 25; k++) {
                for (int j = 1; j < 25; j++) {


                    int tmp1 = 0;
                    int tmp2 = 0;

                    if (gcd(k, 26, tmp1, tmp2) != 1 || gcd(t, 26, tmp1, tmp2) != 1) {
                        continue;
                    }

                    i++;
                    auto deciphered = affine_recursive(0, alphabet, textIn, parentkey);
                    parentscore = score(deciphered);

                    std::vector<int> child = {t, q, k, j};
                    deciphered = affine_recursive(0, alphabet, textIn, child);
                    double scoreNow = score(deciphered);
                    if (scoreNow > parentscore) {
                        parentscore = scoreNow;
                        parentkey = child;
                    }

                    if (parentscore > maxscore) {
                        maxscore = parentscore;
                        maxkey = parentkey;
                        std::cout << "\nBest metrick: " << maxscore << "on iteration " << i << std::endl;
                        auto answer = affine_recursive(0, alphabet, textIn, maxkey);
                        std::cout << "Plain text: " << answer << std::endl;
                    }

                }
            }
        }
    }

}

int main() {

    std::cout << "Выполняется: Лабораторная 1 по КМЗИ" << std::endl;

    std::cout << "Хотите выполнить криптоанализ? (1)/(0)" << std::endl;

    bool ans;
    std::cin >> ans;
    if(ans == 1) {
        std::cout << "К какому алгоритму применяем криптоанализ?" << std::endl;
        std::cout << "1 - простой замены, 2 - аффинный шифр, 3 - аффинный рекуррентный шифр" << std::endl;
        int modeofAnalysys;
        std::cin >> modeofAnalysys;
        std::cout << "Введите сообщение для анализа:" << std::endl;
        std::string msgToBreak;
        std::cin >> msgToBreak;
        auto english_alph = "abcdefghijklmnopqrstuvwxyz";

        if (ans) {
            switch (modeofAnalysys) {

                case 1:
                    cryptoanalysis_simple(msgToBreak, english_alph);
                    break;
                case 2:
                    cryptoanalysis_affine(msgToBreak, english_alph);
                    break;
                case 3:
                    cryptoanalysis_affine_recurrent(msgToBreak, english_alph);
                default:
                    std::cout << "Неверный ввод данных" << std::endl;

                    //cryptoanalysis_simple("vpebqjsfovjovpvifipuwfsijdijibtfwzfoesipmfnqmjgfgxpnnqdijmeippeboejsjmmwvbqvifxfgpxbmpohvjnf", english_alph);
                    //cryptoanalysis_affine("rtdhradqhirepraqhqkpippopjqhbpnaqknqkneppepcuppa", english_alph);
                    //cryptoanalysis_affine_recurrent("lxbbiegbqgqpbuelsnjgkkbqbfkhjdrsehwpdtxliwvefpiqm", english_alph);

            }
            return 0;
        }
    }
    while(true)
    {

        std::cout << "Необходимо выполнить: encrypt (default) - зашифрование, decode - расшифрование, stop - завершение программы" << std::endl;
        std::string mode;
        std::cin >> mode;

        int to_encrypt = 1;

        if(mode == "decode") to_encrypt = 0;
        if(mode == "stop")
        {
            std::cout << "Выполнено завершение программы" << std::endl;
            return 0;

        }

        std::cout << "Выберите режим для криптографического алгоритма: 0 - Подстановочный 1 - Аффинный 2 - Аффинный рекуррентный" << std::endl;

        int algo;
        std::cin >> algo;

        std::cout << "Введите сообщение:" << std::endl;
        std::string message;
        std::cin >> message;

        std::cout << "Вы хотите использовать стандартный алфавит? (1 или 0)" << std::endl;
        int standart;
        std::cin >> standart;

        std::string alphabet;
        int sz;

        if(!standart)
        {
            std::cout << "В таком случае введите ваш алфавит:" << std::endl;
            std::cin >> alphabet;
            sz = alphabet.size();
        }else
        {
            std::cout << "Введите размер алфавита: 33 для русского или 26 для английского" << std::endl;
            std::cin >> sz;
            alphabet = "абвгдеёжзийклмнопрстуфхцчшщъыьэюя";
            if (sz == 26) alphabet = "abcdefghijklmnopqrstuvwxyz";
        }

        switch (algo)
        {
            case 0:
                std::cout << simple_substitute(to_encrypt, alphabet, message) << std::endl;
                break;
            case 1:
                std::cout << affine(to_encrypt, alphabet, message) << std::endl;
                break;
            case 2:
                std::cout << affine_recursive(to_encrypt, alphabet, message) << std::endl;
                break;
            default:
                std::cout << "Ошибка программы: не существует алгоритма" << std::endl;
                break;
        }

    }

    return 0;
}
