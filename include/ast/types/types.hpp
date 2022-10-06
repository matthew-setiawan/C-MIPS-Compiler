#ifndef main_types
#define main_types

#include <iomanip>
#include <string>

class types : public exprr {};

static void typedec(std::ostream& file, root& context, double value, float value2, int opt){
      if(opt==0){
		file << "li.d $f0, " << value << std::endl;
		file << "swc1 $f0, " << context.retSP() << "($30)" << std::endl;
      }
      if(opt==1){
            file << "li.s $f0, " << value2 << std::endl;
            file << "swc1 " << "$f0" << "," << context.retSP() << "($30)" << std::endl;
      }
}

#include "type_integer.hpp"
#include "type_unsigned.hpp"
#include "type_float.hpp"
#include "type_double.hpp"
#include "type_character.hpp"
#include "type_indentifier.hpp"
#endif