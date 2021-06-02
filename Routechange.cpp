#include "Routechange.h"
/**
 * @brief Конструктор, принимающий на вход ключ, который устанавливает кол-во столбцов
 * @param ws_key
 * @return Ничего не возвращает
 */
Cipher::Cipher(std::wstring & ws_key)
{
    pillar = getValidKey(ws_key);
}
/**
 * @brief Метод, принимающий на вход ключ, который устанавливает кол-во столбцов
 * @param ws_key
 * @return Ничего не возвращает
 */
void Cipher::set_key(std::wstring & ws_key)
{
    pillar = getValidKey(ws_key);
}
/**
 * @brief Метод, принимающий на вход текст для зашифровки
 * @details Данный метод принимает на вход длину текста и  формируется кол-во строк в таблице.
 * @param open_text
 */
void Cipher::set_text(const std::wstring& open_text)
{
    len_text = open_text.size();
    if (len_text>pillar) {
        rad = len_text/pillar;
        if (len_text%pillar >0) rad+=1;
    } else {
        rad = 1;
    }
}
/**
 * @brief Метод encrypt зашифровывает принятый текст. 
 * @param open_text
 * @return Возвращает зашифрованный текст
 */
std::wstring Cipher::encrypt( std::wstring& open_text)
{
    open_text = getValidOpenText(open_text);
    set_text(open_text);
    std::wstring table_chiper[rad][pillar];
    int nums_text = 0;
    for (int y=0; y<rad; y++) {
        for (int x=0; x<pillar; x++) {
            if (nums_text < len_text) {
                table_chiper[y][x] = open_text[nums_text];
            } else {
                table_chiper[y][x] = L"-";
            }
            nums_text++;
        }
    }
    std::wstring encrypt_text;
    for (int x=pillar-1; x>=0; x--) {
        for (int y=0; y<rad; y++) {
            encrypt_text+=table_chiper[y][x];
        }
    }
    return encrypt_text;
}
/**
 * @brief Метод decrypt расшифровывает текст. 
 * @param cipher_text
 * @return Возвращает расшифрованный текст.
 */
std::wstring Cipher::decrypt(const std::wstring& cipher_text)
{
    set_text(getValidCipherText(cipher_text));
    std::wstring table_chiper[rad][pillar];
    int nums_text = 0;
    for (int x=pillar-1; x>=0; x--) {
        for (int y=0; y<rad; y++) {
            table_chiper[y][x] = cipher_text[nums_text];
            nums_text++;
        }
    }
    std::wstring decrypt_text;
    for (int y=0; y<rad; y++) {
        for (int x=0; x<pillar; x++) {
            if (table_chiper[y][x] != L"-")
                decrypt_text+=table_chiper[y][x];
        }
    }
    return decrypt_text;
}
/**
 * @brief Метод проверяющий ключ на правильность.
 * @param ws_key
 * @return Ключ
 * @throw cipher_error, если ключ пустой или невалидный 
 */
inline int Cipher::getValidKey(std::wstring & ws_key)
{
    if (ws_key.empty())
        throw cipher_error("Пустой ключ");
    std::string s_key = codec.to_bytes(ws_key);
    for (auto & c:ws_key) {
        if (!iswdigit(c)) {
            throw cipher_error(std::string("Неправильный тип ключа") + s_key);
        }
    }
    int key = std::stoi(ws_key);
    if (key<=0) {
        throw cipher_error(std::string("Ключ не допустим. Введите число больше 0"));
    }
    return key;
}
/**
 * @brief Данный метод проверяет принятый текст на правильность. 
 * В данном методе строчные буквы превращаются в прописные. 
 * Когда встречаются знаки, цифры и пробелы они удаляются.
 * @param ws_open_text
 * @return Текст для расшифрования
 * @throw cipher_error, если текст пустой 
 */
inline std::wstring Cipher::getValidOpenText(const std::wstring & ws_open_text)
{
    std::wstring tmp;
    for (auto c:ws_open_text) {
        if (iswalpha(c)) {
            if (iswlower(c))
                tmp.push_back(towupper(c));
            else
                tmp.push_back(c);
        }
    }
    if (tmp.empty())
        throw cipher_error("Входной текст отстутвует");
    return tmp;
}
/**
 * @brief Данный метод проверяет зашифрованный текст на правильность. 
 * @param ws_cipher_text
 * @return Зашифрованный текст
 * @throw cipher_error, если текст пустой или невалидный 
 */
inline std::wstring Cipher::getValidCipherText(const std::wstring & ws_cipher_text)
{
    if (ws_cipher_text.empty())
        throw cipher_error("Выходной текст отстутвует");

    for (auto c:ws_cipher_text) {
        if (!iswupper(c)) {
            if (c!=L'-') {
                throw cipher_error(std::string("Неправильный тип выходного текста"));
            }
        }
    }
    return ws_cipher_text;
}
