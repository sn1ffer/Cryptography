dictionary = ["a", "b", "c", "d", "e", 'f', 'g', 'h', 'i', 'j', 'k', 'l',
              'm', 'n','o','p','q','r','s','t','u','v','w','x','y','z']
#первые две строки в каждой функции - проверка на введение лишних символов, удаление пробелов и т.д.

def encode_repeat_key(word: str, key: str): #Шифрование с помощью создания гаммы путем повторения ключа
    key = "".join(r for r in key.lower() if (r.isalpha() and r in dictionary))
    word = "".join(q for q in word.lower() if (q.isalpha() and q in dictionary)); result = ''
    gamma = key*(len(word)//len(key)) + key[:len(word)-len(key*(len(word)//len(key)))]
    for (q, i) in zip(word, gamma):
        result += dictionary[(dictionary.index(q)+dictionary.index(i)) % len(dictionary)]
    return ''.join(result)
#print(encode_repeat_key("Acid rain is a great problem in our world. It causes fish and plants to die in our waters. It causes harm to our own race as well because we eat these fish, drink this water and, eat these plants. About 20 years ago scientists first believed that acid rain was due to entirely air pollution. They were partially right. Since the beginning of the Industrial Revolution in England, pollution had been affecting all the trees, soil and rivers in Europe and North America. The use of fossil fuels, such as coal and oil, are large to be blamed for almost half of the emissions of sulfur dioxide in the world. However, there is another cause. The other cause is naturally occurring sulfur dioxide. Natural sources which release this gas are volcanoes, sea spray, rotting vegetation, and plankton.The EPA {Environmental Protection Agency} has an acid rain program. This program is working to significantly reduce utilities’ emissions of sulfur dioxide and nitrogen oxides, the pollutants responsible for acid deposition. Across Europe, there is a project going on in the schools, whose main goal is to educate young people about the changing nature of acid rain and the response of environmental systems to these changes, called «Acid Rain 2000″. Schools are being invited to join the project from across continental Europe as well as the UK. Already the project has participants in Norway, Sweden, Finland, Poland, and Denmark. People can get more involved with wanting to solve this problem by becoming more aware of acid rain and spreading awareness as well. Awareness should start in schools. Students should be given the right perspective of acidic rain. Some people are under the impression that acidic lakes are grimy and gross when really they have a captivating beauty. Granted the reason the lakes are so clear and beautiful are for the wrong reasons, people should know what to look out for. Students should be taught to conserve fossil fuels at a very young age, for the fossil fuels will be gone one day. When conserving the fossil fuels, the students will also be limiting the amount of sulfur emitted into the air, which in turn lessens the amount of acidity in the rain. It will take a lot of time to end this problem. Even if we were to stop polluting today we would have this environmental problem for years to come because of the build-up we have left behind. If all goes well and people put their all into solving this problem, maybe it won’t be a problem in 50 years to come. After all, acid rain is an international problem and any study into its impact and the response of environmental systems must be international in approach.",'win'))
def decode_repeat_key(word: str,key: str): #Расшифровка с помощью создания гаммы путем повторения ключа
    key = "".join(r for r in key.lower() if (r.isalpha() and r in dictionary))
    word = "".join(q for q in word.lower() if (q.isalpha() and q in dictionary)); result = ''
    gamma = key * (len(word) // len(key)) + key[:len(word) - len(key * (len(word) // len(key)))]
    for (q, i) in zip(word, gamma):
        result += dictionary[(dictionary.index(q)-dictionary.index(i)) % len(dictionary)]
    return result
#print("Расшифровка с помощью создания гаммы повторением ключа", decode_repeat_key('mialqappvyxb', 'jin'))

def encode_Key_open_text(word: str,key: str): #Шифрование с помощью создания самоключа по открытому тексту
    key = "".join(r for r in key.lower() if (r.isalpha() and r in dictionary))
    word = "".join(q for q in word.lower() if (q.isalpha() and q in dictionary)); result = ''
    gamma = key[0] + word[:len(word)-1]
    for (q, i) in zip(word, gamma):
        result += dictionary[(dictionary.index(q)+dictionary.index(i)) % len(dictionary)]
    return result
#print("Шифрование с помощью создания самоключа по открытому тексту:", encode_Key_open_text("dancing hippo", 'Jin'))

def decode_Key_open_text(word: str,key: str): #расшифровка с помощью создания самоключа по открытому тексту
    key = "".join(r for r in key.lower() if (r.isalpha() and r in dictionary))
    word = "".join(q for q in word.lower() if (q.isalpha() and q in dictionary)); result = ''
    gamma = ''; gamma += key[0]
    for i in range(0, len(word)):
        j = i
        x = dictionary[(dictionary.index(word[i]) - dictionary.index(gamma[j])) % len(dictionary)]
        gamma += x
    for (q, i) in zip(word, gamma):
        result += dictionary[(dictionary.index(q)-dictionary.index(i)) % len(dictionary)]
    return result
#print("Расшифровка с помощью создания самоключа по открытому текст:", decode_Key_open_text("mdnpkvtnpxed", "Jin"))

def ciphertext(word: str,key: str): #шифрование с помощью создания самоключа по шифртексту
    key = "".join(r for r in key.lower() if (r.isalpha() and r in dictionary))
    word = "".join(q for q in word.lower() if (q.isalpha() and q in dictionary)); result = ''
    gamma = ''; gamma += key[0]
    for i in range(0, len(word)):
        j = i
        x = dictionary[(dictionary.index(word[i]) + dictionary.index(gamma[j])) % len(dictionary)]
        gamma += x
    for (q, i) in zip(word, gamma):
        result += dictionary[(dictionary.index(q)+dictionary.index(i)) % len(dictionary)]
    return result
#print("Шифрование с помощью создания самоключа по шифртексту:", ciphertext("dancing hippo", 'Jin'))

def decode_ciphertext(word: str,key: str): #расшифрование с помощью создания самоключа по шифртексту
    key = "".join(r for r in key.lower() if (r.isalpha() and r in dictionary))
    word = "".join(q for q in word.lower() if (q.isalpha() and q in dictionary)); result = ''
    gamma = ''; gamma += key[0] + word[:len(word)-1]
    for i in range(len(word)):
        q = i
        result += dictionary[(dictionary.index(word[i])-dictionary.index(gamma[q])) % len(dictionary)]
    return result
#print("Расшифрование с помощью создания самоключа по шифртексту:", decode_ciphertext("mmzbjwcjrgvj", 'Jin'))
continuation = 0
while continuation != 2:
    action = input("Выберите операцию: \n"
    "1) Шифрование с помощью создания гаммы путем повторения ключа \n"
    "2) Расшифровка с помощью создания гаммы путем повторения ключа \n"
    "3) Шифрование с помощью создания самоключа по открытому тексту \n"
    "4) Расшифрование с помощью создания самоключа по открытому тексту \n"
    "5) Шифрование с помощью создания самоключа по шифртексту \n"
    "6) Расшифровкак с помощью создания самоключа по открытому тексту\n"
    "Введите номер операции:")
    key = input("Введите ключ: ")
    word = input('Введите текст: ')
    if action == "1":
        print('Зашифрованный текст: ', encode_repeat_key(word, key))
    elif action == "2":
        print("Расшифрованный текст: ", decode_repeat_key(word, key))
    elif action == "3":
        print('Зашифрованный текст: ', encode_Key_open_text(word, key))
    elif action == "4":
        print("Расшифрованный текст: ", decode_Key_open_text(word, key))
    elif action == "5":
        print('Зашифрованный текст: ', ciphertext(word, key))
    else:
        print("Расшифрованный текст: ", decode_ciphertext(word, key))
    continuation = int(input("\n"
                             "Если Вы хотите выполнить другую операцию либо повторить эту - нажмите 1, если Вы желаете закончить - нажмите 2: "))
