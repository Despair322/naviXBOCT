#ifndef ITERATOR_H
#define ITERATOR_H

#include <String>
#include <iostream>

class FileItem {
public:
    std::string fname; // Название файла
    bool isDir;   // 1 - Диоектория; 0 - Файл
    std::string fMask; // Путь к файлу или Директории
    void set(char name[], std::string Mask, bool c) {fname = name; fMask = Mask; isDir = c;}
};

class Iterator {
    Iterator *it;
    FileItem *cache;
    std::string Mask;
    std::string name;
    intptr_t hFind;

    bool comparison(FileItem*); // Сравнение cash->fname и name, 1 - равны 0 - не равны
    FileItem* searchInDir(); // ищёт очередной файл/каталог внутри Mask (0 - файл, 1 - директория)
    FileItem* doSearch(); // ищет внутри Mask и подкатолагах очередной файл, удовлет.name

public:
    bool hasMore();   // Есть ли файл по пути Mask
    FileItem* next();// Показывает и переходит к следущиму файлу с названием name по пути Mask
    Iterator(std::string, std::string);

    ~Iterator();
};

#endif // ITERATOR_H
