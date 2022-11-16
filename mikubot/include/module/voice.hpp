#pragma once

#include "module.hpp"

class Voice : public Module
{
public:
   void init() override;

   inline const std::string desc() const override { return "voice related functionality. music, voice commands, etc."; }
};
