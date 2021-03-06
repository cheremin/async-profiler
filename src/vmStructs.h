/*
 * Copyright 2017 Andrei Pangin
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef _VMSTRUCTS_H
#define _VMSTRUCTS_H

#include <stdint.h>


class VMStructs {
  private:
    static uintptr_t getGlobalVar(const char* name);

  protected:
    static int _klass_name_offset;
    static int _symbol_length_offset;
    static int _symbol_body_offset;

    const char* at(int offset) {
        return (const char*)this + offset;
    }

  public:
    static void init();

    static bool available() {
        return _klass_name_offset >= 0
            && _symbol_length_offset >= 0
            && _symbol_body_offset >= 0;
    }
};


class VMSymbol : VMStructs {
  public:
    unsigned short length() {
        return *(unsigned short*) at(_symbol_length_offset);
    }

    const char* body() {
        return at(_symbol_body_offset);
    }
};

class VMKlass : VMStructs {
  public:
    VMSymbol* name() {
        return *(VMSymbol**) at(_klass_name_offset);
    }
};

#endif // _VMSTRUCTS_H
