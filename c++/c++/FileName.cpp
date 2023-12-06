#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

int main() {
    std::ifstream sourceFile("source.json"); // 打开源文件
    std::ofstream destFile("output.json"); // 创建并打开目标文件

    if (!sourceFile.is_open() || !destFile.is_open()) {
        std::cerr << "Error opening file" << std::endl;
        return -1;
    }

    std::string line, json_object;
    bool is_first_object = true;

    while (std::getline(sourceFile, line)) {
        // 删除每行末尾的逗号
        size_t commaPos = line.find_last_of(',');
        if (commaPos != std::string::npos) {
            line.erase(commaPos, 1);
        }

        json_object += line;

        if (line.find('}') != std::string::npos) { // 查找闭合的大括号
            // 每个 JSON 对象后面都会换行，不再添加逗号
            destFile << json_object << "\n";
            json_object.clear(); // 清空用于下一个 JSON 对象
            is_first_object = false;
        }
    }

    sourceFile.close(); // 关闭源文件
    destFile.close(); // 关闭目标文件
    return 0;
}


