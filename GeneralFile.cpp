#include"GeneralFile.h"

LLVMContext TheContext;

std::unique_ptr<Module> TheModule;

std::map<std::string, AllocaInst *> NamedValues;
map<string, int *> testMap;
IRBuilder<> Builder(TheContext);