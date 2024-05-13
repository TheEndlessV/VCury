#ifndef VCRYPTER_H
#define VCRYPTER_H

#include <iostream>
#include <string>
#include <cryptopp/aes.h>
#include <cryptopp/modes.h>
#include <cryptopp/filters.h>
#include <cryptopp/hex.h>
#include <cryptopp/base64.h>
#include <cryptopp/zlib.h>

#include <QWidget>

std::string toStdStr(QString qstr){
    return qstr.toStdString();
}

QString toQstr(std::string str){
    return QString::fromStdString(str);
}

std::string Compress(const std::string& data) {
    std::string compressed;
    CryptoPP::StringSource(data, true,
        new CryptoPP::ZlibCompressor(new CryptoPP::StringSink(compressed))
    );
    return compressed;
}

std::string Decompress(const std::string& compressed) {
    std::string decompressed;
    CryptoPP::StringSource(compressed, true,
        new CryptoPP::ZlibDecompressor(new CryptoPP::StringSink(decompressed))
    );
    return decompressed;
}

std::string AESEncrypt(const std::string& plaintext, const std::string& key, const std::string& iv) {
    //std::string plaintext = Compress(zplaintext);
    std::string ciphertext;

    CryptoPP::AES::Encryption aesEncryption((CryptoPP::byte*)key.c_str(), CryptoPP::AES::DEFAULT_KEYLENGTH);
    CryptoPP::CBC_Mode_ExternalCipher::Encryption cbcEncryption(aesEncryption, (CryptoPP::byte*)iv.data());

    CryptoPP::StringSource(plaintext, true,
        new CryptoPP::StreamTransformationFilter(cbcEncryption,
            new CryptoPP::Base64Encoder(
                new CryptoPP::StringSink(ciphertext),
                false // do not insert line breaks
            )
        )
    );

    return ciphertext;
}

std::string AESDecrypt(const std::string& ciphertext, const std::string& key, const std::string& iv) {
    //std::string ciphertext = Decompress(zciphertext);
    std::string decryptedtext;

    CryptoPP::AES::Decryption aesDecryption((CryptoPP::byte*)key.c_str(), CryptoPP::AES::DEFAULT_KEYLENGTH);
    CryptoPP::CBC_Mode_ExternalCipher::Decryption cbcDecryption(aesDecryption, (CryptoPP::byte*)iv.data());

    CryptoPP::StringSource(ciphertext, true,
        new CryptoPP::Base64Decoder(
            new CryptoPP::StreamTransformationFilter(cbcDecryption,
                new CryptoPP::StringSink(decryptedtext)
            )
        )
    );

    return decryptedtext;
}

#endif /* VCRYPTER_H */

