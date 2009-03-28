/*
 * Cppcheck - A tool for static C/C++ code analysis
 * Copyright (C) 2007-2009 Daniel Marjamäki, Reijo Tomperi, Nicolas Le Cam,
 * Leandro Penz, Kimmo Varis, Vesa Pikki
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/
 */


//---------------------------------------------------------------------------
#ifndef CheckOtherH
#define CheckOtherH
//---------------------------------------------------------------------------

#include "check.h"
#include "settings.h"

class Token;

class CheckOther : public Check
{
public:
    /** This constructor is used when registering the CheckClass */
    CheckOther() : Check()
    { }

    /** This constructor is used when running checks.. */
    CheckOther(const Tokenizer *tokenizer, const Settings *settings, ErrorLogger *errorLogger)
            : Check(tokenizer, settings, errorLogger)
    { }


    void runChecks(const Tokenizer *tokenizer, const Settings *settings, ErrorLogger *errorLogger)
    {
        CheckOther checkOther(tokenizer, settings, errorLogger);

        if (settings->_checkCodingStyle)
        {
            checkOther.CheckUnsignedDivision();
            checkOther.CheckCharVariable();
        }
    }

    void runSimplifiedChecks(const Tokenizer *tokenizer, const Settings *settings, ErrorLogger *errorLogger)
    {
        CheckOther checkOther(tokenizer, settings, errorLogger);

        if (settings->_checkCodingStyle)
        {
            checkOther.WarningOldStylePointerCast();
            checkOther.WarningRedundantCode();
            checkOther.WarningIf();
            checkOther.CheckVariableScope();
            checkOther.CheckConstantFunctionParameter();
            checkOther.CheckStructMemberUsage();
            checkOther.CheckIncompleteStatement();
        }

        checkOther.strPlusChar();
        checkOther.returnPointerToStackData();
        checkOther.InvalidFunctionUsage();
        checkOther.nullPointer();
        checkOther.CheckZeroDivision();
    }

    // Casting
    void WarningOldStylePointerCast();

    // Redundant code
    void WarningRedundantCode();

    // Warning upon: if (condition);
    void WarningIf();

    // Invalid function usage..
    void InvalidFunctionUsage();

    // Check for unsigned division that might create bad results
    void CheckUnsignedDivision();

    // Check scope of variables
    void CheckVariableScope();

    // Check for constant function parameter
    void CheckConstantFunctionParameter();

    // Check that all struct members are used
    void CheckStructMemberUsage();

    // Using char variable as array index / as operand in bit operation
    void CheckCharVariable();

    // Incomplete statement. A statement that only contains a constant or variable
    void CheckIncompleteStatement();

    /** str plus char */
    void strPlusChar();

    /** Returning pointer to local data */
    void returnPointerToStackData();

    /** possible null pointer dereference */
    void nullPointer();

    /** Check zero division*/
    void CheckZeroDivision();

protected:
    void CheckVariableScope_LookupVar(const Token *tok1, const char varname[]);

    // Redundant condition
    // if (haystack.find(needle) != haystack.end())
    //    haystack.remove(needle);
    void redundantCondition2();

private:
    // Error messages..
    void cstyleCastError(const Token *tok);
    void redundantIfDelete0Error(const Token *tok);
    void redundantIfRemoveError(const Token *tok);
    void dangerousUsageStrtolError(const Token *tok);
    void ifNoActionError(const Token *tok);
    void sprintfOverlappingDataError(const Token *tok, const std::string &varname);
    void udivError(const Token *tok);
    void udivWarning(const Token *tok);
    void unusedStructMemberError(const Token *tok, const std::string &structname, const std::string &varname);
    void passedByValueError(const Token *tok, const std::string &parname);
    void constStatementError(const Token *tok, const std::string &type);
    void charArrayIndexError(const Token *tok);
    void charBitOpError(const Token *tok);
    void variableScopeError(const Token *tok, const std::string &varname);
    void conditionAlwaysTrueFalse(const Token *tok, const std::string &truefalse);
    void strPlusChar(const Token *tok);
    void returnLocalVariable(const Token *tok);
    void nullPointerError(const Token *tok);
    void zerodivWarning(const Token *tok);

    void getErrorMessages()
    {
        cstyleCastError(0);
        redundantIfDelete0Error(0);
        redundantIfRemoveError(0);
        dangerousUsageStrtolError(0);
        ifNoActionError(0);
        sprintfOverlappingDataError(0, "varname");
        udivError(0);
        udivWarning(0);
        unusedStructMemberError(0, "structname", "varname");
        passedByValueError(0, "parname");
        constStatementError(0, "type");
        charArrayIndexError(0);
        charBitOpError(0);
        variableScopeError(0, "varname");
        conditionAlwaysTrueFalse(0, "true/false");
        strPlusChar(0);
        returnLocalVariable(0);
        nullPointerError(0);
        zerodivWarning(0);
    }

};

//---------------------------------------------------------------------------
#endif

