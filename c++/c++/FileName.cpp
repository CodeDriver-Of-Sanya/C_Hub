#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

int main() {
    std::ifstream sourceFile("source.json"); // ��Դ�ļ�
    std::ofstream destFile("output.json"); // ��������Ŀ���ļ�

    if (!sourceFile.is_open() || !destFile.is_open()) {
        std::cerr << "Error opening file" << std::endl;
        return -1;
    }

    std::string line, json_object;
    bool is_first_object = true;

    while (std::getline(sourceFile, line)) {
        // ɾ��ÿ��ĩβ�Ķ���
        size_t commaPos = line.find_last_of(',');
        if (commaPos != std::string::npos) {
            line.erase(commaPos, 1);
        }

        json_object += line;

        if (line.find('}') != std::string::npos) { // ���ұպϵĴ�����
            // ÿ�� JSON ������涼�ỻ�У�������Ӷ���
            destFile << json_object << "\n";
            json_object.clear(); // ���������һ�� JSON ����
            is_first_object = false;
        }
    }

    sourceFile.close(); // �ر�Դ�ļ�
    destFile.close(); // �ر�Ŀ���ļ�
    return 0;
}


