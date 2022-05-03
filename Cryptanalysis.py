# -*- coding: utf-8 -*-
from collections import Counter
dictionary = ["a", "b", "c", "d", "e", 'f', 'g', 'h', 'i', 'j', 'k', 'l',
              'm', 'n','o','p','q','r','s','t','u','v','w','x','y','z']
#поиск длины ключа и индекса совпадений
def index_of_coincidence(msg):
    c = Counter(list(msg))
    return sum(x*(x-1) for x in c.values())/(len(msg)*(len(msg) - 1))
#mes = "wkvzznevvoitnmnpxekjyauvjwhnebntqebpwcfaaseauwvqltnjbfpwqemvjwhnenpmeoqgyihomfdieibbkcekeanipaifsmyhjryihomjamnpbuaarbqfdleevxppvoenpmewvqaigppromchiapanxwhpgrwzfwobokvavgeagonvnagxmyemialgdigwkvzznevjwaqqmgkmapqeatlwqelwyhcgewappruernmcwzgeiyhgeeoupavjkrpprxmtevaevtkngdmvjlhobeeiynmikthpqbjqaavthiazxbhthpqbjpnzjravnbnrybvjonhtgdmgnmroabetnjleedrnavjmhnwcaiazvbnbuwurnqpwbuacfawsbwfoqybcrhafqkuwapkiywvqkqywzrhiecmgkjrxtnimqbwewtzkagdiybwspprauvoavkvfknfqtsqzqewkelrevgdmjkzyzpbsmiazgdmeaqfwvbpprnknqarpprkbuazpwcfaqfjigqznhtlkkpqzeevtocybcezqbtqqavnpcewtfkceymfspvypeatrwarppvoonoieadbhknjwroarwacnilnwgpqacdrcmgwbvkvnjlchiagbbjbuamcwmarqekvzavgwtcnwgakgewaworjkldifwvnyqqnivjxekoewugdqflzbczniqfswegqacbboqtjqseknjbyuzrzcpacgetvpqromzeafewaowsocybcezqbtqqaiazvvpzbcmakfvzmfpprlwyhcgwvgozroxbjavxtrbwewkvzlrlwfebvkvnyzboarqzblmgdmeaqfwxekrrybtkqacwaevgdmfypbktfspbomzwqacwnhqfpwrzcpwbruwhjocawchmnxwhpbuakuwvtevtjigqzrknnyqqnivjiazbuazroxbjarknrjdvnwaimapiyogfpmzobbpprompdiacmfyiyhmqwkvzznevfypbktfwzrxmvjovjdvpmqpwwkqapprlzbfmppnekunyzboapkvgevrjbnhmhnwcaifsmyhifpprqsnhzrwllpprlzbfmpppnoxnnbvyqcwvgoqajwesiloerzmabqahiazxbhiaziazlrjunnscawchmpwvtabzkzreviktialjebusiapqacbbowyrmgdqflzbxtrijlxmpkuvjozkzrwennmbbipelewqawvqoxeaiqevtwennmaaafwajatywennmaaafopbqtqobnnbvjapdwbhafpcqavgoaukcyzjrcqiavgdmeeoupxrnacakgedrknnyqqekewqaowzaxrkxyaieacazmeppreucnmfoqbjbuwbnyqqekywsroieaoeeulwvqczboajdmanmnhtlpprupnrmnyicpqiwbvjooaihpgtniapmqpprnmnowapprhixaannmfkkyaiewvqxmnqbvbcywzrbwepprszbjoeaifkvflmbltropbqtqgvbseuwbgktbksbqbskzfpcqavgoaukcyzjrpihcpgpwpkvfazianboavhnhatfwbnrmeugbqvtworbwepprbwfoqybcrhajetyxmtkvrkvrzilsprjkbjarndvjogdmskafetsqmyobuaagqlrjbfsqyhiyowoatviqgevtpprwubqvgknfqtsqzriqgpmqevgkbuaivneuekuevgqzahmfomaobuaizkcapwswkvzqguqapprnivjqgsqyhbngmnhwgkngeurpwrjlgdqflzbxtrimiavvbersmeabbobblxbhthpqacbbzilsmjkcyzpnrmgdqfaviezbjurjbnhxekjyauskzlaieobbywzajryihombbbuajhetqqxjapnrmyangxmuevqennhttkmfsmyhiazxrkxyaxhpbuaqewtyevgkabhdvjogdqflzbxtriunujrebjkvgxmnlzbxtriqaumnnagkkbimnbbrniyhipelewqaeanjqapmejigewawtcnwohmzwvqwvlobhzgvjbbebfeucwkgwvqpprnmflwaombbmarqekvzavgwtfuagauficfpjrevgazawbvkvnhqawxcnwnyp"
#mes = "".join(r for r in mes.lower() if (r.isalpha() and r in dictionary))
#key_length = [(i, index_of_coincidence(mes[::i])) for i in range(1, 50) if index_of_coincidence(mes[::i]) >= 0.059]
#a = key_length[0][0]

#деление строки на строки, равные длине ключа
def groups(msg, key_dlina):
      result = [msg[i:i + key_dlina] for i in range(0, len(msg), key_dlina)]
      result.pop(0), result.pop(len(result)-1)

#сформируем список списков, полученных в результате объединения первых, вторых, третьих и т.д. элементов
      strings = []
      for i in range(key_dlina):
            string = []
            for x in result:
                  string.append(x[i])
            strings.append(string)

#найдем кол-во вхождений конкретной буквы в списки первых, вторых, третьих и т.д. элементов
      kol_vo = []
      for g in strings:
            col_vo_letter = []
            x = 0
            for k in range(len(g)):
                  if g.count(g[k]) not in col_vo_letter and g.count(g[k])>x:
                        col_vo_letter.clear()
                        col_vo_letter.append(g[k])
#                       col_vo_letter.append(g.count(g[k]))
                        x = g.count(g[k])
            kol_vo.append(col_vo_letter)
#найдем гамму
      key = ""
      for i in kol_vo:
            for q in i:
                  key += dictionary[(dictionary.index(q) - dictionary.index("e")) % 26]
      print('Предполагаемый ключ: ', key)
      key = input("Введите ключ(либо впишите предполагаемый, либо введите свой, если считаете, что в написании допущена ошибка: ")
      key = "".join(r for r in key.lower() if (r.isalpha() and r in dictionary))
      gamma = key * (len(msg) // len(key)) + key[:len(msg) - len(key * (len(msg) // len(key)))]
      result = ''
      for (q, i) in zip(msg, gamma):
            result += dictionary[(dictionary.index(q) - dictionary.index(i)) % len(dictionary)]
      return result

#print(groups(mes, a))

continuation = 0
while continuation != 2:
      mesg = input("Введите зашифрованный текст: ")
      mesg = "".join(r for r in mesg.lower() if (r.isalpha() and r in dictionary))
      key_length_1 = [(i, index_of_coincidence(mesg[::i])) for i in range(1, 50) if index_of_coincidence(mesg[::i]) >= 0.059]
      c = key_length_1[0][0]
      print('Длина ключа: ', c)
      print("Расшифрованный текст: ", groups(mesg, c))
      continuation = int(input("\n"
                               "Если Вы хотите выполнить криптоанализ другого текста - нажмите 1, если Вы желаете закончить - нажмите 2: "))
