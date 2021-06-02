/**
* @file Routechange.h
* @author Байбаков Н.М.
* @version 1.0
* @brief Шифрование методом табличной перестановки
* @date 21.05.2021
* @copyright ИБСТ ПГУ
*/
#pragma once
#include <vector>
#include <string>
#include <map>
#include <codecvt>
#include <locale>
#include <iostream>
/**
 * @class Cipher
 * @brief Описание класса Cipher
 * @details Ключ устанавливается в конструкторе,
 * Для зашифрования и расшифрования предназначены методы encrypt и decrypt.
 * @warning Реализация производится только для русского языка. С использованием wstring.
 */
class Cipher
{
private:
    std::wstring_convert<std::codecvt_utf8<wchar_t>, wchar_t> codec;  ///< для преобразования в широкий формат строки и обратно
    int pillar; ///< Ключ, обозначающий количество столбцов в таблице
    int rad; ///< Количество строк в таблице
    int len_text; ///< Количество символов в строке
public:
    Cipher()=delete; ///< Запрещающий конструктор без параметров
    Cipher(std::wstring & ws_key); ///< Конструктор принимает ключ
    std::wstring encrypt( std::wstring& ws_open_text); ///< Метод использующийся для зашифрования
    std::wstring decrypt(const std::wstring& ws_cipher_text); ///< Метод использующийся для расшифрования
    void set_text(const std::wstring& ws_text); ///< Формирует информацию о таблице
    void set_key(std::wstring & ws_key); ///< Установка нового ключа
    int getValidKey(std::wstring& ws_key); ///< Проверка на правильность ключа
    std::wstring getValidOpenText(const std::wstring & ws_open_text); ///< Проверка на правильность текста для зашифровки
    std::wstring getValidCipherText(const std::wstring & ws_cipher_text); ///< Проверка на правильность текста для расшифровки
};
/**
 * @class cipher_error
 * @file Routechange.h
 * @file Routechange.cpp
 * @brief Описание класса cipher_error
 */
class cipher_error: public std::invalid_argument
{
public:
    /**
    * @brief Принимает на вход строку, вызывает исключение
    * @param what_arg
    */
    explicit cipher_error (const std::string& what_arg):
        std::invalid_argument(what_arg) {}
    /**
    * @brief Принимает на вход си строку, вызывает исключение
    * @param what_arg
    */
    explicit cipher_error (const char* what_arg):
        std::invalid_argument(what_arg) {}
};
