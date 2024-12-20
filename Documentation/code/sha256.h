#pragma once

#include <string>

#include <cryptopp/sha.h>
#include <cryptopp/hex.h>
#include <cryptopp/osrng.h>
#include <cryptopp/filters.h>

using namespace std;
using namespace CryptoPP;

/**
 * @brief Вычисляет SHA256 хеш для заданных данных.
 * @param data Строка данных для хеширования.
 * @return Строка, содержащая хеш в шестнадцатеричном формате.
 */
string sha256(const string &data);
