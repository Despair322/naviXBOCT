#include "iterator.h"
#include <io.h>
#include <iostream>
#include <string.h>
//#include <windows.h>

Iterator::~Iterator(){
    if (it != NULL)
        delete it;
    if ((hFind != NULL) || (hFind != -1))
        _findclose(hFind);
    if (cache != NULL)
        delete cache;
}

bool Iterator::comparison(FileItem* a){
    std::string str1 = "*", str2 = "*.*";
    if ((name == str1) || (name == str2))
        return 1;
    if (a->fname == name)
        return 1;
    return 0;
}

FileItem* Iterator::searchInDir(){
    FileItem *a = NULL;
    struct _finddata_t file;
    std::string str = Mask + "\\*", str1 = ".", str2 = "..";
    bool i = 0;

	if (hFind == NULL){
		if ((hFind = _findfirst(str.c_str(),&file)) == -1L)
			return NULL;
	}
	else{
		if ((_findnext(hFind , &file)) != 0)
			return NULL;
	}
	a = new FileItem;
	if (file.attrib & _A_SUBDIR)
            i = 1;
    a->set(file.name, Mask, i);
	if ((a->fname == str1) || (a->fname == str2)){
		delete a;
		a = searchInDir();
	}

    return a;
}

FileItem* Iterator::doSearch(){
    FileItem* a = NULL;

	do {
	 if (it != NULL){
		 a = it->doSearch();
		 if (a != NULL)
			return a;
		 delete it;
		 it = NULL;
	 }
	 a = searchInDir();
	 if (a == NULL)
		 return NULL;
	 if (!a->isDir){
		 if (comparison(a))
			return a;
	 }
	 else 
		 it = new Iterator(a->fMask + "\\" + a->fname, name);
	 delete a;
	} while(1);

}

bool Iterator::hasMore(){
    if (cache == NULL) {
		if ((cache = doSearch()) == NULL)
			return 0;
	}
    return 1;
}

FileItem* Iterator::next(){
    if (!hasMore())
        throw "Not found\n";
	FileItem* a = cache;
	cache = doSearch();
    return a;
}

Iterator::Iterator(std::string mask, std::string Name){
    Mask = mask;
    name = Name;
    it = NULL;
    hFind = NULL;
	cache = NULL;
}
