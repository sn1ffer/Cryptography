//Шифрока, расшифрока и криптоанализ шифра простой замены, аффинного и аффинного рекурретного шифров. 

#include <iostream>
#include <vector>
#include <string>

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

std::string simple_substitute(bool to_encrypt, std::string alphabet, std::string message = "")
{
    std::cout << "Выполняю шифр простой замены" << std::endl;

    int size_alphabet = alphabet.size();

    std::cout << "Введите " << size_alphabet << " элементов перестановки" << std::endl;
    std::vector<int> keys(size_alphabet);
    for(int i = 0; i<size_alphabet; i++)
    {
        std::cin >> keys[i];
    }

    std::string to_return;

    if(to_encrypt)
    {
        std::cout << "Выполняю зашифрование" << std::endl;
        for(auto character: message)
        {
            int pos = std::find(alphabet.begin(), alphabet.end(), character) - alphabet.begin();
            char newLetter = alphabet[keys[pos]];
            to_return.push_back(newLetter);
        }
    }else
    {
        std::cout << "Выполняю расшифрование" << std::endl;
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

std::string affine(bool to_encrypt, std::string alphabet, std::string message = "")
{
    int size_alphabet = alphabet.size();
    std::cout << "Выполняю Аффинный шифр" << std::endl;
    std::cout << "Введите альфа и бета" << std::endl;
    int alpha, beta;
    std::cin >> alpha >> beta;
    std::string to_return;
    if(to_encrypt)
    {
        std::cout << "Выполняю зашифрование" << std::endl;
        for(auto elem: message)
        {
            int pos = std::find(alphabet.begin(), alphabet.end(), elem) - alphabet.begin();
            int num = (alpha*pos+beta)%size_alphabet;
            char newLetter = alphabet[num];
            to_return.push_back(newLetter);
        }
    }else
    {
        std::cout << "Выполняю расшифрование" << std::endl;
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

std::string affine_recursive(bool to_encrypt, std::string alphabet, std::string message = "")
{
    int size_alphabet = alphabet.size();
    std::cout << "Выполняю аффинный рекуррентный шифр" << std::endl;
    std::cout << "Вставьте первую пару альфа и бета" << std::endl;
    int alphaFir, betaFir, alphaSec, betaSec;
    std::cin >> alphaFir >> betaFir;
    std::cout << "Вставьте вторую пару альфа и бета" << std::endl;
    std::cin >> alphaSec >> betaSec;
    std::string to_return;
    if(to_encrypt){
        std::cout << "Выполняю зашифрование" << std::endl;
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
        std::cout << "Выполняю расшифрование" << std::endl;
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

int main() {


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
