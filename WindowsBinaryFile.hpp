#pragma once

#include "BinaryFile.hpp"

#include <stdio.h>

namespace pankey{

    namespace FileSystem{

        class WindowsBinaryFile : public BinaryFile{
            public:
                ~WindowsBinaryFile(){
                    close();
                }

                bool openRead(const FilePath& a_path) override{
                    close();
                    if(a_path.isEmpty()){
                        return false;
                    }
                    m_file = fopen(a_path.getArrayPointer(), "rb");
                    return m_file != nullptr;
                }

                bool openWrite(const FilePath& a_path) override{
                    close();
                    if(a_path.isEmpty()){
                        return false;
                    }
                    m_file = fopen(a_path.getArrayPointer(), "wb");
                    return m_file != nullptr;
                }

                void close() override{
                    if(m_file != nullptr){
                        fclose(m_file);
                        m_file = nullptr;
                    }
                }

                bool isOpen() const override{
                    return m_file != nullptr;
                }

                bool skip(unsigned long long a_byte_count) override{
                    return m_file != nullptr
                        && _fseeki64(m_file, static_cast<__int64>(a_byte_count), SEEK_CUR) == 0;
                }

                bool seek(unsigned long long a_position) override{
                    return m_file != nullptr
                        && _fseeki64(m_file, static_cast<__int64>(a_position), SEEK_SET) == 0;
                }

                unsigned long long position() const override{
                    if(m_file == nullptr){
                        return 0;
                    }
                    const __int64 i_position = _ftelli64(m_file);
                    return i_position < 0 ? 0 : static_cast<unsigned long long>(i_position);
                }

            protected:
                bool readBytes(void* a_values, int a_byte_count) override{
                    return m_file != nullptr
                        && a_values != nullptr
                        && a_byte_count > 0
                        && fread(a_values, 1, a_byte_count, m_file) == a_byte_count;
                }

                bool writeBytes(const void* a_values, int a_byte_count) override{
                    return m_file != nullptr
                        && a_values != nullptr
                        && a_byte_count > 0
                        && fwrite(a_values, 1, a_byte_count, m_file) == a_byte_count;
                }

            private:
                FILE* m_file = nullptr;
        };
    }
}